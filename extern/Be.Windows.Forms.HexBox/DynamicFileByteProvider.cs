using System;
using System.Text;
using System.IO;
using System.Runtime.Remoting.Messaging;
using System.Collections.Generic;
using System.Reflection;
using System.Linq;

namespace Be.Windows.Forms
{
    /// <summary>
    /// Implements a fully editable byte provider for file data of any size.
    /// </summary>
    /// <remarks>
    /// Only changes to the file are stored in memory with reads from the
    /// original data occurring as required.
    /// </remarks>
    public sealed class DynamicFileByteProvider : IByteProvider, IDisposable
    {

        public event UndoActionQueued UndoActionQueued;
		public event RedoActionQueued RedoActionQueued;
        public event UndoActionQueued UndoActionPerformed;
		public event RedoActionQueued RedoActionPerformed;
        public event EventHandler ChangesApplied;

        public List<HexAction> undo_actions_ 
        {
            get
            {
                return undo_actions;
            }
            set
            {
                undo_actions = value;
            }
        } private List<HexAction> undo_actions;
		public List<HexAction> redo_actions_ 
        {
            get
            {
                return redo_actions;
            }
            set
            {
                redo_actions = value;
            }
        } private List<HexAction> redo_actions;
        public ProviderType Type { get; set; }

        const int COPY_BLOCK_SIZE = 4096;

        string _fileName;

        public Stream stream
        {
            get { return _stream; }
            set { _stream = value; }
        }
        Stream _stream;

        DataMap _dataMap;
        long _totalLength;
        bool _readOnly;

        /// <summary>
        /// Constructs a new <see cref="DynamicFileByteProvider" /> instance.
        /// </summary>
        /// <param name="fileName">The name of the file from which bytes should be provided.</param>
        public DynamicFileByteProvider(string fileName) : this(fileName, false) { }

        /// <summary>
        /// Constructs a new <see cref="DynamicFileByteProvider" /> instance.
        /// </summary>
        /// <param name="fileName">The name of the file from which bytes should be provided.</param>
        /// <param name="readOnly">True, opens the file in read-only mode.</param>
        public DynamicFileByteProvider(string fileName, bool readOnly)
        {
            undo_actions_ = new List<HexAction>();
            redo_actions_ = new List<HexAction>();

            Type = ProviderType.File;

            _fileName = fileName;

            if (!readOnly)
            {
                _stream = File.Open(fileName, FileMode.Open, FileAccess.ReadWrite, FileShare.Read);
            }
            else
            {
                _stream = File.Open(fileName, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
            }

            _readOnly = readOnly;

            ReInitialize();
        }

        /// <summary>
        /// Constructs a new <see cref="DynamicFileByteProvider" /> instance.
        /// </summary>
        /// <param name="stream">the stream containing the data.</param>
        /// <remarks>
        /// The stream must supported seek operations.
        /// </remarks>
        public DynamicFileByteProvider(Stream stream)
        {
            undo_actions_ = new List<HexAction>();
            redo_actions_ = new List<HexAction>();

            Type = ProviderType.File;

            if (stream == null)
                throw new ArgumentNullException("stream");
            if (!stream.CanSeek)
                throw new ArgumentException("stream must supported seek operations(CanSeek)");

            _stream = stream;
            _readOnly = !stream.CanWrite;
            ReInitialize();
        }

        #region IByteProvider Members
        /// <summary>
        /// See <see cref="IByteProvider.LengthChanged" /> for more information.
        /// </summary>
        public event EventHandler LengthChanged;

        /// <summary>
        /// See <see cref="IByteProvider.Changed" /> for more information.
        /// </summary>
        public event EventHandler Changed;


        public void Undo() 
        { 
            if(undo_actions_.Count <= 0)
				return;

			HexAction action = undo_actions_.Last();

			switch (action.type_)
			{
                case HexActionType.Write:
                {
                    long blockOffset;
                    DataBlock block = GetDataBlock(action.position_, out blockOffset);

                    // If the byte is already in a memory block, modify it.
                    MemoryDataBlock memoryBlock = block as MemoryDataBlock;
                    if (memoryBlock != null)
                    {
                        memoryBlock.Data[action.position_ - blockOffset] = action.data_old_[0];
                        break;
                    }

                    FileDataBlock fileBlock = (FileDataBlock)block;

                    // If the byte changing is the first byte in the block and the previous block is a memory block, extend that.
                    if (blockOffset == action.position_ && block.PreviousBlock != null)
                    {
                        MemoryDataBlock previousMemoryBlock = block.PreviousBlock as MemoryDataBlock;
                        if (previousMemoryBlock != null)
                        {
                            previousMemoryBlock.AddByteToEnd(action.data_old_[0]);
                            fileBlock.RemoveBytesFromStart(1);
                            if (fileBlock.Length == 0)
                            {
                                _dataMap.Remove(fileBlock);
                            }
                            break;
                        }
                    }

                    // If the byte changing is the last byte in the block and the next block is a memory block, extend that.
                    if (blockOffset + fileBlock.Length - 1 == action.position_ && block.NextBlock != null)
                    {
                        MemoryDataBlock nextMemoryBlock = block.NextBlock as MemoryDataBlock;
                        if (nextMemoryBlock != null)
                        {
                            nextMemoryBlock.AddByteToStart(action.data_old_[0]);
                            fileBlock.RemoveBytesFromEnd(1);
                            if (fileBlock.Length == 0)
                            {
                                _dataMap.Remove(fileBlock);
                            }
                            break;
                        }
                    }

                    // Split the block into a prefix and a suffix and place a memory block in-between.
                    FileDataBlock prefixBlock = null;
                    if (action.position_ > blockOffset)
                    {
                        prefixBlock = new FileDataBlock(fileBlock.FileOffset, action.position_ - blockOffset);
                    }

                    FileDataBlock suffixBlock = null;
                    if (action.position_ < blockOffset + fileBlock.Length - 1)
                    {
                        suffixBlock = new FileDataBlock(
                            fileBlock.FileOffset + action.position_ - blockOffset + 1,
                            fileBlock.Length - (action.position_ - blockOffset + 1));
                    }

			        block = _dataMap.Replace(block, new MemoryDataBlock(action.data_old_[0]));

                    if (prefixBlock != null)
                    {
                        _dataMap.AddBefore(block, prefixBlock);
                    }

                    if (suffixBlock != null)
                    {
                        _dataMap.AddAfter(block, suffixBlock);
                    }
                    OnChanged(EventArgs.Empty);
                    break;
                }
                case HexActionType.WriteMany:
                {
                    for(int i = 0 ; i < action.length_; ++i)
                    {
                        var index = action.position_ + i;

                        // Find the block affected.
                        long blockOffset;
                        DataBlock block = GetDataBlock(index, out blockOffset);

                        // If the byte is already in a memory block, modify it.
                        MemoryDataBlock memoryBlock = block as MemoryDataBlock;
                        if (memoryBlock != null)
                        {
                            memoryBlock.Data[index - blockOffset] = action.data_old_[i];
                            continue;
                        }

                        FileDataBlock fileBlock = (FileDataBlock)block;

                        // If the byte changing is the first byte in the block and the previous block is a memory block, extend that.
                        if (blockOffset == index && block.PreviousBlock != null)
                        {
                            MemoryDataBlock previousMemoryBlock = block.PreviousBlock as MemoryDataBlock;
                            if (previousMemoryBlock != null)
                            {
                                previousMemoryBlock.AddByteToEnd(action.data_old_[i]);
                                fileBlock.RemoveBytesFromStart(1);
                                if (fileBlock.Length == 0)
                                {
                                    _dataMap.Remove(fileBlock);
                                }
                                continue;
                            }
                        }

                        // If the byte changing is the last byte in the block and the next block is a memory block, extend that.
                        if (blockOffset + fileBlock.Length - 1 == index && block.NextBlock != null)
                        {
                            MemoryDataBlock nextMemoryBlock = block.NextBlock as MemoryDataBlock;
                            if (nextMemoryBlock != null)
                            {
                                nextMemoryBlock.AddByteToStart(action.data_old_[i]);
                                fileBlock.RemoveBytesFromEnd(1);
                                if (fileBlock.Length == 0)
                                {
                                    _dataMap.Remove(fileBlock);
                                }
                                continue;
                            }
                        }

                        // Split the block into a prefix and a suffix and place a memory block in-between.
                        FileDataBlock prefixBlock = null;
                        if (index > blockOffset)
                        {
                            prefixBlock = new FileDataBlock(fileBlock.FileOffset, index - blockOffset);
                        }

                        FileDataBlock suffixBlock = null;
                        if (index < blockOffset + fileBlock.Length - 1)
                        {
                            suffixBlock = new FileDataBlock(
                                fileBlock.FileOffset + index - blockOffset + 1,
                                fileBlock.Length - (index - blockOffset + 1));
                        }

			            block = _dataMap.Replace(block, new MemoryDataBlock(action.data_old_[i]));

                        if (prefixBlock != null)
                        {
                            _dataMap.AddBefore(block, prefixBlock);
                        }

                        if (suffixBlock != null)
                        {
                            _dataMap.AddAfter(block, suffixBlock);
                        }
                    }
                    OnChanged(EventArgs.Empty);
                    break;
                }
                case HexActionType.Insert:
                {
                    try
                    {
                        long bytesToDelete = action.length_;

                        // Find the first block affected.
                        long blockOffset;
                        DataBlock block = GetDataBlock(action.position_, out blockOffset);

                        // Truncate or remove each block as necessary.
                        while ((bytesToDelete > 0) && (block != null))
                        {
                            long blockLength = block.Length;
                            DataBlock nextBlock = block.NextBlock;

                            // Delete the appropriate section from the block (this may result in two blocks or a zero length block).
                            long count = Math.Min(bytesToDelete, blockLength - (action.position_ - blockOffset));
                    
                            block.RemoveBytes(action.position_ - blockOffset, count);

                            if (block.Length == 0)
                            {
                                _dataMap.Remove(block);
                                if (_dataMap.FirstBlock == null)
                                {
                                    _dataMap.AddFirst(new MemoryDataBlock(new byte[0]));
                                }
                            }
                    
                            bytesToDelete -= count;
                            blockOffset += block.Length;
                            block = (bytesToDelete > 0) ? nextBlock : null;
                        }
                    }
                    finally
                    {
                        _totalLength -= action.length_;
                        OnLengthChanged(EventArgs.Empty);
                        OnChanged(EventArgs.Empty);
                    }
                    break;
                }
                case HexActionType.Delete:
                {
                    try
                    {
                        // Find the block affected.
                        long blockOffset;
                        DataBlock block = GetDataBlock(action.position_, out blockOffset);

                        // If the insertion point is in a memory block, just insert it.
                        MemoryDataBlock memoryBlock = block as MemoryDataBlock;
                        if (memoryBlock != null)
                        {
                            memoryBlock.InsertBytes(action.position_ - blockOffset, action.data_old_);
                            break;
                        }

                        FileDataBlock fileBlock = (FileDataBlock)block;

                        // If the insertion point is at the start of a file block, and the previous block is a memory block, append it to that block.
                        if (blockOffset == action.position_ && block.PreviousBlock != null)
                        {
                            MemoryDataBlock previousMemoryBlock = block.PreviousBlock as MemoryDataBlock;
                            if (previousMemoryBlock != null)
                            {
                                previousMemoryBlock.InsertBytes(previousMemoryBlock.Length, action.data_old_);
                                break;
                            }
                        }

                        // Split the block into a prefix and a suffix and place a memory block in-between.
                        FileDataBlock prefixBlock = null;
                        if (action.position_ > blockOffset)
                        {
                            prefixBlock = new FileDataBlock(fileBlock.FileOffset, action.position_ - blockOffset);
                        }

                        FileDataBlock suffixBlock = null;
                        if (action.position_ < blockOffset + fileBlock.Length)
                        {
                            suffixBlock = new FileDataBlock(
                                fileBlock.FileOffset + action.position_ - blockOffset,
                                fileBlock.Length - (action.position_ - blockOffset));
                        }

				        block = _dataMap.Replace(block, new MemoryDataBlock(action.data_old_));

                        if (prefixBlock != null)
                        {
                            _dataMap.AddBefore(block, prefixBlock);
                        }

                        if (suffixBlock != null)
                        {
                            _dataMap.AddAfter(block, suffixBlock);
                        }
                    }
                    finally
                    {
                        _totalLength += action.data_old_.Length;
                        OnLengthChanged(EventArgs.Empty);
                        OnChanged(EventArgs.Empty);
                    }
                    break;
                }
            }

            undo_actions_.RemoveAt(undo_actions_.Count - 1);
			redo_actions_.Add(action);

            if(UndoActionPerformed != null)
			{
				UndoActionPerformed.Invoke(this, action);
			}
        }
        public void Redo() 
        {
            if(redo_actions_.Count <= 0)
				return;

			HexAction action = redo_actions_.Last();

			switch (action.type_)
			{
                case HexActionType.Write:
                {
                    long blockOffset;
                    DataBlock block = GetDataBlock(action.position_, out blockOffset);

                    // If the byte is already in a memory block, modify it.
                    MemoryDataBlock memoryBlock = block as MemoryDataBlock;
                    if (memoryBlock != null)
                    {
                        memoryBlock.Data[action.position_ - blockOffset] = action.data_new_[0];
                        break;
                    }

                    FileDataBlock fileBlock = (FileDataBlock)block;

                    // If the byte changing is the first byte in the block and the previous block is a memory block, extend that.
                    if (blockOffset == action.position_ && block.PreviousBlock != null)
                    {
                        MemoryDataBlock previousMemoryBlock = block.PreviousBlock as MemoryDataBlock;
                        if (previousMemoryBlock != null)
                        {
                            previousMemoryBlock.AddByteToEnd(action.data_new_[0]);
                            fileBlock.RemoveBytesFromStart(1);
                            if (fileBlock.Length == 0)
                            {
                                _dataMap.Remove(fileBlock);
                            }
                            break;
                        }
                    }

                    // If the byte changing is the last byte in the block and the next block is a memory block, extend that.
                    if (blockOffset + fileBlock.Length - 1 == action.position_ && block.NextBlock != null)
                    {
                        MemoryDataBlock nextMemoryBlock = block.NextBlock as MemoryDataBlock;
                        if (nextMemoryBlock != null)
                        {
                            nextMemoryBlock.AddByteToStart(action.data_new_[0]);
                            fileBlock.RemoveBytesFromEnd(1);
                            if (fileBlock.Length == 0)
                            {
                                _dataMap.Remove(fileBlock);
                            }
                            break;
                        }
                    }

                    // Split the block into a prefix and a suffix and place a memory block in-between.
                    FileDataBlock prefixBlock = null;
                    if (action.position_ > blockOffset)
                    {
                        prefixBlock = new FileDataBlock(fileBlock.FileOffset, action.position_ - blockOffset);
                    }

                    FileDataBlock suffixBlock = null;
                    if (action.position_ < blockOffset + fileBlock.Length - 1)
                    {
                        suffixBlock = new FileDataBlock(
                            fileBlock.FileOffset + action.position_ - blockOffset + 1,
                            fileBlock.Length - (action.position_ - blockOffset + 1));
                    }

			        block = _dataMap.Replace(block, new MemoryDataBlock(action.data_new_[0]));

                    if (prefixBlock != null)
                    {
                        _dataMap.AddBefore(block, prefixBlock);
                    }

                    if (suffixBlock != null)
                    {
                        _dataMap.AddAfter(block, suffixBlock);
                    }
                    OnChanged(EventArgs.Empty);
                    break;
                }
                case HexActionType.WriteMany:
                {
                    for(int i = 0 ; i < action.length_; ++i)
                    {
                        var index = action.position_ + i;

                        // Find the block affected.
                        long blockOffset;
                        DataBlock block = GetDataBlock(index, out blockOffset);

                        // If the byte is already in a memory block, modify it.
                        MemoryDataBlock memoryBlock = block as MemoryDataBlock;
                        if (memoryBlock != null)
                        {
                            memoryBlock.Data[index - blockOffset] = action.data_new_[i];
                            continue;
                        }

                        FileDataBlock fileBlock = (FileDataBlock)block;

                        // If the byte changing is the first byte in the block and the previous block is a memory block, extend that.
                        if (blockOffset == index && block.PreviousBlock != null)
                        {
                            MemoryDataBlock previousMemoryBlock = block.PreviousBlock as MemoryDataBlock;
                            if (previousMemoryBlock != null)
                            {
                                previousMemoryBlock.AddByteToEnd(action.data_new_[i]);
                                fileBlock.RemoveBytesFromStart(1);
                                if (fileBlock.Length == 0)
                                {
                                    _dataMap.Remove(fileBlock);
                                }
                                continue;
                            }
                        }

                        // If the byte changing is the last byte in the block and the next block is a memory block, extend that.
                        if (blockOffset + fileBlock.Length - 1 == index && block.NextBlock != null)
                        {
                            MemoryDataBlock nextMemoryBlock = block.NextBlock as MemoryDataBlock;
                            if (nextMemoryBlock != null)
                            {
                                nextMemoryBlock.AddByteToStart(action.data_new_[i]);
                                fileBlock.RemoveBytesFromEnd(1);
                                if (fileBlock.Length == 0)
                                {
                                    _dataMap.Remove(fileBlock);
                                }
                                continue;
                            }
                        }

                        // Split the block into a prefix and a suffix and place a memory block in-between.
                        FileDataBlock prefixBlock = null;
                        if (index > blockOffset)
                        {
                            prefixBlock = new FileDataBlock(fileBlock.FileOffset, index - blockOffset);
                        }

                        FileDataBlock suffixBlock = null;
                        if (index < blockOffset + fileBlock.Length - 1)
                        {
                            suffixBlock = new FileDataBlock(
                                fileBlock.FileOffset + index - blockOffset + 1,
                                fileBlock.Length - (index - blockOffset + 1));
                        }

			            block = _dataMap.Replace(block, new MemoryDataBlock(action.data_new_[i]));

                        if (prefixBlock != null)
                        {
                            _dataMap.AddBefore(block, prefixBlock);
                        }

                        if (suffixBlock != null)
                        {
                            _dataMap.AddAfter(block, suffixBlock);
                        }
                    }
                    OnChanged(EventArgs.Empty);
                    break;
                }
                case HexActionType.Insert:
                {
                    try
                    {
                        // Find the block affected.
                        long blockOffset;
                        DataBlock block = GetDataBlock(action.position_, out blockOffset);

                        // If the insertion point is in a memory block, just insert it.
                        MemoryDataBlock memoryBlock = block as MemoryDataBlock;
                        if (memoryBlock != null)
                        {
                            memoryBlock.InsertBytes(action.position_ - blockOffset, action.data_new_);
                            break;
                        }

                        FileDataBlock fileBlock = (FileDataBlock)block;

                        // If the insertion point is at the start of a file block, and the previous block is a memory block, append it to that block.
                        if (blockOffset == action.position_ && block.PreviousBlock != null)
                        {
                            MemoryDataBlock previousMemoryBlock = block.PreviousBlock as MemoryDataBlock;
                            if (previousMemoryBlock != null)
                            {
                                previousMemoryBlock.InsertBytes(previousMemoryBlock.Length, action.data_new_);
                                break;
                            }
                        }

                        // Split the block into a prefix and a suffix and place a memory block in-between.
                        FileDataBlock prefixBlock = null;
                        if (action.position_ > blockOffset)
                        {
                            prefixBlock = new FileDataBlock(fileBlock.FileOffset, action.position_ - blockOffset);
                        }

                        FileDataBlock suffixBlock = null;
                        if (action.position_ < blockOffset + fileBlock.Length)
                        {
                            suffixBlock = new FileDataBlock(
                                fileBlock.FileOffset + action.position_ - blockOffset,
                                fileBlock.Length - (action.position_ - blockOffset));
                        }

				        block = _dataMap.Replace(block, new MemoryDataBlock(action.data_new_));

                        if (prefixBlock != null)
                        {
                            _dataMap.AddBefore(block, prefixBlock);
                        }

                        if (suffixBlock != null)
                        {
                            _dataMap.AddAfter(block, suffixBlock);
                        }
                    }
                    finally
                    {
                        _totalLength += action.data_new_.Length;
                        OnLengthChanged(EventArgs.Empty);
                        OnChanged(EventArgs.Empty);
                    }

                    break;
                }
                case HexActionType.Delete:
                {
                    try
                    {
                        long bytesToDelete = action.length_;

                        // Find the first block affected.
                        long blockOffset;
                        DataBlock block = GetDataBlock(action.position_, out blockOffset);

                        // Truncate or remove each block as necessary.
                        while ((bytesToDelete > 0) && (block != null))
                        {
                            long blockLength = block.Length;
                            DataBlock nextBlock = block.NextBlock;

                            // Delete the appropriate section from the block (this may result in two blocks or a zero length block).
                            long count = Math.Min(bytesToDelete, blockLength - (action.position_ - blockOffset));
                    
                            block.RemoveBytes(action.position_ - blockOffset, count);

                            if (block.Length == 0)
                            {
                                _dataMap.Remove(block);
                                if (_dataMap.FirstBlock == null)
                                {
                                    _dataMap.AddFirst(new MemoryDataBlock(new byte[0]));
                                }
                            }
                    
                            bytesToDelete -= count;
                            blockOffset += block.Length;
                            block = (bytesToDelete > 0) ? nextBlock : null;
                        }
                    }
                    finally
                    {
                        _totalLength -= action.length_;
                        OnLengthChanged(EventArgs.Empty);
                        OnChanged(EventArgs.Empty);
                    }
                    break;
                }
            }

            redo_actions_.RemoveAt(redo_actions_.Count - 1);
			undo_actions_.Add(action);

            if(RedoActionPerformed != null)
			{
				RedoActionPerformed.Invoke(this, action);
			}
        }


        /// <summary>
        /// See <see cref="IByteProvider.ReadByte" /> for more information.
        /// </summary>
        public byte ReadByte(long index)
        {
            long blockOffset;
            DataBlock block = GetDataBlock(index, out blockOffset);
            FileDataBlock fileBlock = block as FileDataBlock;
            if (fileBlock != null)
            {
                return ReadByteFromFile(fileBlock.FileOffset + index - blockOffset);
            }
            else
            {
                MemoryDataBlock memoryBlock = (MemoryDataBlock)block;
                return memoryBlock.Data[index - blockOffset];
            }
        }

        public byte[] ReadBytes(long offset, long size)
        {
            /*
            long block_offset;
            DataBlock block = GetDataBlock(offset, out block_offset);
            FileDataBlock file_block = block as FileDataBlock;

            if(file_block != null)
            {
                return ReadBytesFromFile(offset, size);
            }
            else
            {
                MemoryDataBlock memory_block = (MemoryDataBlock)block;
                byte[] buffer = new byte[size];
                for(var i = offset ; i < offset + size; ++i) {

                    long block_offset_;
                    DataBlock block_ = GetDataBlock(i, out block_offset_);
                    FileDataBlock file_block_ = block_ as FileDataBlock;

                    if(file_block_ != null) { 
                        buffer[i - offset] = memory_block.Data[i - block_offset];
                    }
                    else { 
                        var buffer_ = ReadBytesFromFile(i, (offset + size) - i);
                        Array.Copy(buffer_, buffer_.Length, buffer, i - offset, (offset + size) - i );
                        break;
                    }
                }

                return buffer;
            }
            */
            byte[] buffer = new byte[size];

            for(var i = 0 ; i < size; ++i)
            {
                if( (offset + i) >= this.Length)
                    break;

                buffer[i] = ReadByte(offset + i);
            }

            return buffer;
        }

        public long WriteBytes(long offset, byte[] buffer, long length)
        {

            byte[] original = ReadBytes(offset, length);

            long bytes_written = 0;

            for(long i = 0 ; i < length; ++i)
            {

                var index = offset + i;

                if(index >= this.Length)
                    break;

                // Find the block affected.
                long blockOffset;
                DataBlock block = GetDataBlock(index, out blockOffset);

                // If the byte is already in a memory block, modify it.
                MemoryDataBlock memoryBlock = block as MemoryDataBlock;
                if (memoryBlock != null)
                {
                    memoryBlock.Data[index - blockOffset] = buffer[i];
                     continue;
                }

                FileDataBlock fileBlock = (FileDataBlock)block;

                // If the byte changing is the first byte in the block and the previous block is a memory block, extend that.
                if (blockOffset == index && block.PreviousBlock != null)
                {
                    MemoryDataBlock previousMemoryBlock = block.PreviousBlock as MemoryDataBlock;
                    if (previousMemoryBlock != null)
                    {
                        previousMemoryBlock.AddByteToEnd(buffer[i]);
                        fileBlock.RemoveBytesFromStart(1);
                        if (fileBlock.Length == 0)
                        {
                            _dataMap.Remove(fileBlock);
                        }
                        continue;
                    }
                }

                // If the byte changing is the last byte in the block and the next block is a memory block, extend that.
                if (blockOffset + fileBlock.Length - 1 == index && block.NextBlock != null)
                {
                    MemoryDataBlock nextMemoryBlock = block.NextBlock as MemoryDataBlock;
                    if (nextMemoryBlock != null)
                    {
                        nextMemoryBlock.AddByteToStart(buffer[i]);
                        fileBlock.RemoveBytesFromEnd(1);
                        if (fileBlock.Length == 0)
                        {
                            _dataMap.Remove(fileBlock);
                        }
                        continue;
                    }
                }

                // Split the block into a prefix and a suffix and place a memory block in-between.
                FileDataBlock prefixBlock = null;
                if (index > blockOffset)
                {
                    prefixBlock = new FileDataBlock(fileBlock.FileOffset, index - blockOffset);
                }

                FileDataBlock suffixBlock = null;
                if (index < blockOffset + fileBlock.Length - 1)
                {
                    suffixBlock = new FileDataBlock(
                        fileBlock.FileOffset + index - blockOffset + 1,
                        fileBlock.Length - (index - blockOffset + 1));
                }

			    block = _dataMap.Replace(block, new MemoryDataBlock(buffer[i]));

                if (prefixBlock != null)
                {
                    _dataMap.AddBefore(block, prefixBlock);
                }

                if (suffixBlock != null)
                {
                    _dataMap.AddAfter(block, suffixBlock);
                }

                ++bytes_written;
            }

            if(bytes_written == 0)
                return 0;

            HexAction action = new HexAction();
            action.type_ = HexActionType.WriteMany;
            action.data_new_ = buffer;
            action.data_old_ = original;
            action.length_ = bytes_written;
            action.position_ = offset;

            undo_actions_.Add(action);

            if(UndoActionQueued != null)
			{
				UndoActionQueued.Invoke(this, action);
			}

            OnChanged(EventArgs.Empty);

            return bytes_written;
        }

        /// <summary>
        /// See <see cref="IByteProvider.WriteByte" /> for more information.
        /// </summary>
        public void WriteByte(long index, byte value)
        {

            byte[] original = new byte[1] { ReadByte(index) };
            byte[] modified = new byte[1] { value };
            // Find the block affected.
            long blockOffset;
            DataBlock block = GetDataBlock(index, out blockOffset);

            // If the byte is already in a memory block, modify it.
            MemoryDataBlock memoryBlock = block as MemoryDataBlock;
            if (memoryBlock != null)
            {
                memoryBlock.Data[index - blockOffset] = value;
                 goto push_back_action;
            }

            FileDataBlock fileBlock = (FileDataBlock)block;

            // If the byte changing is the first byte in the block and the previous block is a memory block, extend that.
            if (blockOffset == index && block.PreviousBlock != null)
            {
                MemoryDataBlock previousMemoryBlock = block.PreviousBlock as MemoryDataBlock;
                if (previousMemoryBlock != null)
                {
                    previousMemoryBlock.AddByteToEnd(value);
                    fileBlock.RemoveBytesFromStart(1);
                    if (fileBlock.Length == 0)
                    {
                        _dataMap.Remove(fileBlock);
                    }
                     goto push_back_action;
                }
            }

            // If the byte changing is the last byte in the block and the next block is a memory block, extend that.
            if (blockOffset + fileBlock.Length - 1 == index && block.NextBlock != null)
            {
                MemoryDataBlock nextMemoryBlock = block.NextBlock as MemoryDataBlock;
                if (nextMemoryBlock != null)
                {
                    nextMemoryBlock.AddByteToStart(value);
                    fileBlock.RemoveBytesFromEnd(1);
                    if (fileBlock.Length == 0)
                    {
                        _dataMap.Remove(fileBlock);
                    }
                     goto push_back_action;
                }
            }

            // Split the block into a prefix and a suffix and place a memory block in-between.
            FileDataBlock prefixBlock = null;
            if (index > blockOffset)
            {
                prefixBlock = new FileDataBlock(fileBlock.FileOffset, index - blockOffset);
            }

            FileDataBlock suffixBlock = null;
            if (index < blockOffset + fileBlock.Length - 1)
            {
                suffixBlock = new FileDataBlock(
                    fileBlock.FileOffset + index - blockOffset + 1,
                    fileBlock.Length - (index - blockOffset + 1));
            }

			block = _dataMap.Replace(block, new MemoryDataBlock(value));

            if (prefixBlock != null)
            {
                _dataMap.AddBefore(block, prefixBlock);
            }

            if (suffixBlock != null)
            {
                _dataMap.AddAfter(block, suffixBlock);
            }

        push_back_action:

            HexAction action = new HexAction();
            action.type_ = HexActionType.Write;
            action.data_new_ = modified;
            action.data_old_ = original;
            action.length_ = 1;
            action.position_ = index;

            undo_actions_.Add(action);

            if(UndoActionQueued != null)
			{
				UndoActionQueued.Invoke(this, action);
			}

            OnChanged(EventArgs.Empty);
        }

        /// <summary>
        /// See <see cref="IByteProvider.InsertBytes" /> for more information.
        /// </summary>
        public void InsertBytes(long index, byte[] bs)
        {
            // Find the block affected.
            long blockOffset;
            DataBlock block = GetDataBlock(index, out blockOffset);

            // If the insertion point is in a memory block, just insert it.
            MemoryDataBlock memoryBlock = block as MemoryDataBlock;
            if (memoryBlock != null)
            {
                memoryBlock.InsertBytes(index - blockOffset, bs);
                 goto push_back_action;
            }

            FileDataBlock fileBlock = (FileDataBlock)block;

            // If the insertion point is at the start of a file block, and the previous block is a memory block, append it to that block.
            if (blockOffset == index && block.PreviousBlock != null)
            {
                MemoryDataBlock previousMemoryBlock = block.PreviousBlock as MemoryDataBlock;
                if (previousMemoryBlock != null)
                {
                    previousMemoryBlock.InsertBytes(previousMemoryBlock.Length, bs);
                     goto push_back_action;
                }
            }

            // Split the block into a prefix and a suffix and place a memory block in-between.
            FileDataBlock prefixBlock = null;
            if (index > blockOffset)
            {
                prefixBlock = new FileDataBlock(fileBlock.FileOffset, index - blockOffset);
            }

            FileDataBlock suffixBlock = null;
            if (index < blockOffset + fileBlock.Length)
            {
                suffixBlock = new FileDataBlock(
                    fileBlock.FileOffset + index - blockOffset,
                    fileBlock.Length - (index - blockOffset));
            }

			block = _dataMap.Replace(block, new MemoryDataBlock(bs));

            if (prefixBlock != null)
            {
                _dataMap.AddBefore(block, prefixBlock);
            }

            if (suffixBlock != null)
            {
                _dataMap.AddAfter(block, suffixBlock);
            }

        push_back_action:

            HexAction action = new HexAction();
            action.type_ = HexActionType.Insert;
            action.data_new_ = bs;
            action.data_old_ = null;
            action.length_ = bs.Length;
            action.position_ = index;

            undo_actions_.Add(action);

            if(UndoActionQueued != null)
			{
				UndoActionQueued.Invoke(this, action);
            }

            _totalLength += bs.Length;
            OnLengthChanged(EventArgs.Empty);
            OnChanged(EventArgs.Empty);
            
        }

        /// <summary>
        /// See <see cref="IByteProvider.DeleteBytes" /> for more information.
        /// </summary>
        public void DeleteBytes(long index, long length)
        {
            byte[] old_data = this.ReadBytes(index, length);

            try
            {
                long bytesToDelete = length;

                // Find the first block affected.
                long blockOffset;
                DataBlock block = GetDataBlock(index, out blockOffset);

                // Truncate or remove each block as necessary.
                while ((bytesToDelete > 0) && (block != null))
                {
                    long blockLength = block.Length;
                    DataBlock nextBlock = block.NextBlock;

                    // Delete the appropriate section from the block (this may result in two blocks or a zero length block).
                    long count = Math.Min(bytesToDelete, blockLength - (index - blockOffset));
                    
                    block.RemoveBytes(index - blockOffset, count);

                    if (block.Length == 0)
                    {
                        _dataMap.Remove(block);
                        if (_dataMap.FirstBlock == null)
                        {
                            _dataMap.AddFirst(new MemoryDataBlock(new byte[0]));
                        }
                    }
                    
                    bytesToDelete -= count;
                    blockOffset += block.Length;
                    block = (bytesToDelete > 0) ? nextBlock : null;
                }
            }
            finally
            {
                HexAction action = new HexAction();
                action.type_ = HexActionType.Delete;
                action.data_new_ = null;
                action.data_old_ = old_data;
                action.length_ = length;
                action.position_ = index;

                undo_actions_.Add(action);

                if(UndoActionQueued != null)
			    {
				    UndoActionQueued.Invoke(this, action);
			    }

                _totalLength -= length;
                OnLengthChanged(EventArgs.Empty);
                OnChanged(EventArgs.Empty);
            }
        }

        /// <summary>
        /// See <see cref="IByteProvider.Length" /> for more information.
        /// </summary>
        public long Length
        {
            get
            {
                return _totalLength;
            }
        }

        /// <summary>
        /// See <see cref="IByteProvider.HasChanges" /> for more information.
        /// </summary>
        public bool HasChanges()
        {
            if (_readOnly)
                return false;

            if (_totalLength != _stream.Length)
            {
                return true;
            }

            long offset = 0;
            for (DataBlock block = _dataMap.FirstBlock; block != null; block = block.NextBlock)
            {
                FileDataBlock fileBlock = block as FileDataBlock;
                if (fileBlock == null)
                {
                    return true;
                }

                if (fileBlock.FileOffset != offset)
                {
                    return true;
                }

                offset += fileBlock.Length;
            }
            return (offset != _stream.Length);
        }

        public void SaveToStream(Stream stream)
        {
            // This method is implemented to efficiently save the changes to the same file stream opened for reading.
            // Saving to a separate file would be a much simpler implementation.

            // Firstly, extend the file length (if necessary) to ensure that there is enough disk space.
            if (_totalLength > stream.Length)
            {
                stream.SetLength(_totalLength);

            }

            stream.Position = 0;
            _stream.Position = 0;

            long position_ = 0;

            byte[] block_buffer = new byte[4096];

            // copy original data to output file
            while(position_ < _stream.Length)
            {
                long bytes_to_read = ( ( _stream.Length - position_ ) >= 4096 ? 4096 : _stream.Length - _stream.Position );

                _stream.Read(block_buffer, 0, (int)bytes_to_read);

                stream.Write(block_buffer, 0, (int)bytes_to_read);

                position_ += bytes_to_read;
            }

            // Secondly, shift around any file sections that have moved.
            long dataOffset = 0;
            for (DataBlock block = _dataMap.FirstBlock; block != null; block = block.NextBlock)
            {
                FileDataBlock fileBlock = block as FileDataBlock;
                if (fileBlock != null && fileBlock.FileOffset != dataOffset)
                {
                    MoveFileBlockEx(fileBlock, dataOffset, stream);
                }
                dataOffset += block.Length;
            }

            // Next, write in-memory changes.
            dataOffset = 0;
            for (DataBlock block = _dataMap.FirstBlock; block != null; block = block.NextBlock)
            {
                MemoryDataBlock memoryBlock = block as MemoryDataBlock;
                if (memoryBlock != null)
                {
                    stream.Position = dataOffset;
                    for (int memoryOffset = 0; memoryOffset < memoryBlock.Length; memoryOffset += COPY_BLOCK_SIZE)
                    {
                        stream.Write(memoryBlock.Data, memoryOffset, (int)Math.Min(COPY_BLOCK_SIZE, memoryBlock.Length - memoryOffset));
                    }
                }
                dataOffset += block.Length;
            }

            // Finally, if the file has shortened, truncate the stream.
            stream.SetLength(_totalLength);
        }

        /// <summary>
        /// See <see cref="IByteProvider.ApplyChanges" /> for more information.
        /// </summary>
        public void ApplyChanges()
        {
            if (_readOnly)
                throw new OperationCanceledException("File is in read-only mode");

            // This method is implemented to efficiently save the changes to the same file stream opened for reading.
            // Saving to a separate file would be a much simpler implementation.

            // Firstly, extend the file length (if necessary) to ensure that there is enough disk space.
            if (_totalLength > _stream.Length)
            {
                _stream.SetLength(_totalLength);
            }

            // Secondly, shift around any file sections that have moved.
            long dataOffset = 0;
            for (DataBlock block = _dataMap.FirstBlock; block != null; block = block.NextBlock)
            {
                FileDataBlock fileBlock = block as FileDataBlock;
                if (fileBlock != null && fileBlock.FileOffset != dataOffset)
                {
                    MoveFileBlock(fileBlock, dataOffset);
                }
                dataOffset += block.Length;
            }

            // Next, write in-memory changes.
            dataOffset = 0;
            for (DataBlock block = _dataMap.FirstBlock; block != null; block = block.NextBlock)
            {
                MemoryDataBlock memoryBlock = block as MemoryDataBlock;
                if (memoryBlock != null)
                {
                    _stream.Position = dataOffset;
                    for (int memoryOffset = 0; memoryOffset < memoryBlock.Length; memoryOffset += COPY_BLOCK_SIZE)
                    {
                        _stream.Write(memoryBlock.Data, memoryOffset, (int)Math.Min(COPY_BLOCK_SIZE, memoryBlock.Length - memoryOffset));
                    }
                }
                dataOffset += block.Length;
            }

            // Finally, if the file has shortened, truncate the stream.
            _stream.SetLength(_totalLength);
            ReInitialize();

            if(UndoActionPerformed != null)
			{
				undo_actions_.Clear();
				redo_actions_.Clear();
				UndoActionQueued.Invoke(this, null);
			}

            if(ChangesApplied != null)
            {
                ChangesApplied.Invoke(this, null);
            }
        }

        /// <summary>
        /// See <see cref="IByteProvider.SupportsWriteByte" /> for more information.
        /// </summary>
        public bool SupportsWriteByte()
        {
            return !_readOnly;
        }

        /// <summary>
        /// See <see cref="IByteProvider.SupportsInsertBytes" /> for more information.
        /// </summary>
        public bool SupportsInsertBytes()
        {
            return !_readOnly;
        }

        /// <summary>
        /// See <see cref="IByteProvider.SupportsDeleteBytes" /> for more information.
        /// </summary>
        public bool SupportsDeleteBytes()
        {
            return !_readOnly;
        }
        #endregion

        #region IDisposable Members
        /// <summary>
        /// See <see cref="Object.Finalize" /> for more information.
        /// </summary>
        ~DynamicFileByteProvider()
        {
            Dispose();
        }

        /// <summary>
        /// See <see cref="IDisposable.Dispose" /> for more information.
        /// </summary>
        public void Dispose()
        {
            if (_stream != null)
            {
                _stream.Close();
                _stream = null;
            }
            _fileName = null;
            _dataMap = null;
            GC.SuppressFinalize(this);
        }
        #endregion

        /// <summary>
        /// Gets a value, if the file is opened in read-only mode.
        /// </summary>
        public bool ReadOnly
        {
            get { return _readOnly; }
        }

        void OnLengthChanged(EventArgs e)
        {
            if (LengthChanged != null)
                LengthChanged(this, e);
        }

        void OnChanged(EventArgs e)
        {
            if (Changed != null)
            {
                Changed(this, e);
            }
        }

        DataBlock GetDataBlock(long findOffset, out long blockOffset)
        {
            if (findOffset < 0 || findOffset > _totalLength)
            {
                throw new ArgumentOutOfRangeException("findOffset");
            }

            // Iterate over the blocks until the block containing the required offset is encountered.
            blockOffset = 0;
            for (DataBlock block = _dataMap.FirstBlock; block != null; block = block.NextBlock)
            {
                if ((blockOffset <= findOffset && blockOffset + block.Length > findOffset) || block.NextBlock == null)
                {
                    return block;
                }
                blockOffset += block.Length;
            }
            return null;
        }

        FileDataBlock GetNextFileDataBlock(DataBlock block, long dataOffset, out long nextDataOffset)
        {
            // Iterate over the remaining blocks until a file block is encountered.
            nextDataOffset = dataOffset + block.Length;
            block = block.NextBlock;
            while (block != null)
            {
                FileDataBlock fileBlock = block as FileDataBlock;
                if (fileBlock != null)
                {
                    return fileBlock;
                }
                nextDataOffset += block.Length;
                block = block.NextBlock;
            }
            return null;
        }

        byte ReadByteFromFile(long fileOffset)
        {
            // Move to the correct position and read the byte.
            if (_stream.Position != fileOffset)
            {
                _stream.Position = fileOffset;
            }
            return (byte)_stream.ReadByte();
        }

        byte[] ReadBytesFromFile(long offset, long length)
        {
            _stream.Position = offset;

            byte[] buffer = new byte[length];

            _stream.Read(buffer, 0, (int)length);
            return buffer;
        }

        void MoveFileBlock(FileDataBlock fileBlock, long dataOffset)
        {
            // First, determine whether the next file block needs to move before this one.
            long nextDataOffset;
			FileDataBlock nextFileBlock = GetNextFileDataBlock(fileBlock, dataOffset, out nextDataOffset);
            if (nextFileBlock != null && dataOffset + fileBlock.Length > nextFileBlock.FileOffset)
            {
                // The next block needs to move first, so do that now.
                MoveFileBlock(nextFileBlock, nextDataOffset);
            }

            // Now, move the block.
            if (fileBlock.FileOffset > dataOffset)
            {
                // Move the section to earlier in the file stream (done in chunks starting at the beginning of the section).
                byte[] buffer = new byte[COPY_BLOCK_SIZE];
                for (long relativeOffset = 0; relativeOffset < fileBlock.Length; relativeOffset += buffer.Length)
                {
                    long readOffset = fileBlock.FileOffset + relativeOffset;
                    int bytesToRead = (int)Math.Min(buffer.Length, fileBlock.Length - relativeOffset);
                    _stream.Position = readOffset;
                    _stream.Read(buffer, 0, bytesToRead);

                    long writeOffset = dataOffset + relativeOffset;
                    _stream.Position = writeOffset;
                    _stream.Write(buffer, 0, bytesToRead);
                }
            }
            else
            {
                // Move the section to later in the file stream (done in chunks starting at the end of the section).
                byte[] buffer = new byte[COPY_BLOCK_SIZE];
                for (long relativeOffset = 0; relativeOffset < fileBlock.Length; relativeOffset += buffer.Length)
                {
                    int bytesToRead = (int)Math.Min(buffer.Length, fileBlock.Length - relativeOffset);
                    long readOffset = fileBlock.FileOffset + fileBlock.Length - relativeOffset - bytesToRead;
                    _stream.Position = readOffset;
                    _stream.Read(buffer, 0, bytesToRead);

                    long writeOffset = dataOffset + fileBlock.Length - relativeOffset - bytesToRead;
                    _stream.Position = writeOffset;
                    _stream.Write(buffer, 0, bytesToRead);
                }
            }

			// This block now points to a different position in the file.
			fileBlock.SetFileOffset(dataOffset);
        }

        void MoveFileBlockEx(FileDataBlock fileBlock, long dataOffset, Stream stream)
        {
            // First, determine whether the next file block needs to move before this one.
            long nextDataOffset;
			FileDataBlock nextFileBlock = GetNextFileDataBlock(fileBlock, dataOffset, out nextDataOffset);
            if (nextFileBlock != null && dataOffset + fileBlock.Length > nextFileBlock.FileOffset)
            {
                // The next block needs to move first, so do that now.
                MoveFileBlockEx(nextFileBlock, nextDataOffset, stream);
            }

            // Now, move the block.
            if (fileBlock.FileOffset > dataOffset)
            {
                // Move the section to earlier in the file stream (done in chunks starting at the beginning of the section).
                byte[] buffer = new byte[COPY_BLOCK_SIZE];
                for (long relativeOffset = 0; relativeOffset < fileBlock.Length; relativeOffset += buffer.Length)
                {
                    long readOffset = fileBlock.FileOffset + relativeOffset;
                    int bytesToRead = (int)Math.Min(buffer.Length, fileBlock.Length - relativeOffset);
                    _stream.Position = readOffset;
                    _stream.Read(buffer, 0, bytesToRead);

                    long writeOffset = dataOffset + relativeOffset;
                    stream.Position = writeOffset;
                    stream.Write(buffer, 0, bytesToRead);
                }
            }
            else
            {
                // Move the section to later in the file stream (done in chunks starting at the end of the section).
                byte[] buffer = new byte[COPY_BLOCK_SIZE];
                for (long relativeOffset = 0; relativeOffset < fileBlock.Length; relativeOffset += buffer.Length)
                {
                    int bytesToRead = (int)Math.Min(buffer.Length, fileBlock.Length - relativeOffset);
                    long readOffset = fileBlock.FileOffset + fileBlock.Length - relativeOffset - bytesToRead;
                    _stream.Position = readOffset;
                    _stream.Read(buffer, 0, bytesToRead);

                    long writeOffset = dataOffset + fileBlock.Length - relativeOffset - bytesToRead;
                    stream.Position = writeOffset;
                    stream.Write(buffer, 0, bytesToRead);
                }
            }

			// This block now points to a different position in the file.
			fileBlock.SetFileOffsetEx(dataOffset);
        }


        void ReInitialize()
        {
            _dataMap = new DataMap();
            _dataMap.AddFirst(new FileDataBlock(0, _stream.Length));
            _totalLength = _stream.Length;
        }
    }
}
