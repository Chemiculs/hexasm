using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Security.Cryptography;

namespace Be.Windows.Forms
{
	
	/// <summary>
	/// Byte provider for a small amount of data.
	/// </summary>
	public class DynamicByteProvider : IByteProvider
	{

		public event UndoActionQueued UndoActionQueued;
		public event UndoActionQueued UndoActionPerformed;
		public event RedoActionQueued RedoActionQueued;
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
		}
		private List<HexAction> undo_actions = new List<HexAction>();	
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
		}
		private List<HexAction> redo_actions = new List<HexAction>();
		public ProviderType Type { get; set; }
		/// <summary>
		/// Contains information about changes.
		/// </summary>
		bool _hasChanges;
		/// <summary>
		/// Contains a byte collection.
		/// </summary>
		List<byte> _bytes;


		public void Undo()
		{
			if(undo_actions_.Count <= 0)
				return;

			HexAction action = undo_actions_.Last();

			switch (action.type_)
			{
				case HexActionType.Write :
				{
					_bytes[(int)action.position_] = action.data_old_[0];
					OnChanged(EventArgs.Empty);
					break;
				}
				case HexActionType.WriteMany:
				{
					for(int i = 0 ; i < action.length_; ++i)
					{
						_bytes[(int)action.position_ + i] = action.data_old_[i];
					}
					OnChanged(EventArgs.Empty);
					break;
				}
				case HexActionType.Insert:
				{
					_bytes.RemoveRange((int)action.position_, (int)action.length_); 

					OnLengthChanged(EventArgs.Empty);
					OnChanged(EventArgs.Empty);
					break;
				}
				case HexActionType.Delete:
				{
					_bytes.InsertRange((int)action.position_, action.data_old_); 

					OnLengthChanged(EventArgs.Empty);
					OnChanged(EventArgs.Empty);
					break;
				}
			}

			undo_actions_.RemoveAt(undo_actions_.Count - 1);
			redo_actions.Add(action);

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
				case HexActionType.Write :
				{
					_bytes[(int)action.position_] = action.data_new_[0];
					OnChanged(EventArgs.Empty);
					break;
				}
				case HexActionType.WriteMany:
				{
					for(int i = 0 ; i < action.length_; ++i)
					{
						_bytes[(int)action.position_ + i] = action.data_new_[i];
					}
					OnChanged(EventArgs.Empty);
					break;
				}
				case HexActionType.Insert:
				{
					_bytes.InsertRange((int)action.position_, action.data_new_); 

					OnLengthChanged(EventArgs.Empty);
					OnChanged(EventArgs.Empty);
					break;
				}
				case HexActionType.Delete:
				{
					int internal_index = (int)Math.Max(0, action.position_);
					int internal_length = (int)Math.Min((int)Length, action.position_);
					_bytes.RemoveRange(internal_index, internal_length); 

					OnLengthChanged(EventArgs.Empty);
					OnChanged(EventArgs.Empty);
					break;
				}
			}

			redo_actions_.RemoveAt(redo_actions_.Count - 1);
			undo_actions.Add(action);

			if(RedoActionPerformed != null)
			{
				RedoActionPerformed.Invoke(this, action);
			}
		}
		/// <summary>
		/// Initializes a new instance of the DynamicByteProvider class.
		/// </summary>
		/// <param name="data"></param>
		public DynamicByteProvider(byte[] data) : this(new List<Byte>(data)) 
		{
			undo_actions_ = new List<HexAction>();
			redo_actions_ = new List<HexAction>();
			Type = ProviderType.Memory;
		}

		/// <summary>
		/// Initializes a new instance of the DynamicByteProvider class.
		/// </summary>
		/// <param name="bytes"></param>
		public DynamicByteProvider(List<Byte> bytes)
		{
			undo_actions_ = new List<HexAction>();
			redo_actions_ = new List<HexAction>();
			Type = ProviderType.Memory;
			_bytes = bytes;
		}

		/// <summary>
		/// Raises the Changed event.
		/// </summary>
		void OnChanged(EventArgs e)
		{
			_hasChanges = true;

			if(Changed != null)
				Changed(this, e);
		}

		/// <summary>
		/// Raises the LengthChanged event.
		/// </summary>
		void OnLengthChanged(EventArgs e)
		{
			if(LengthChanged != null)
				LengthChanged(this, e);
		}

		/// <summary>
		/// Gets the byte collection.
		/// </summary>
		public List<Byte> Bytes
		{
			get { return _bytes; }
		}

		#region IByteProvider Members
		/// <summary>
		/// True, when changes are done.
		/// </summary>
		public bool HasChanges()
		{
			return _hasChanges;
		}

		/// <summary>
		/// Applies changes.
		/// </summary>
		public void ApplyChanges()
		{
			if(UndoActionPerformed != null)
			{
				undo_actions.Clear();
				redo_actions.Clear();
				UndoActionPerformed.Invoke(this, null);
			}
			_hasChanges = false;
		}

		public void SaveToStream(Stream stream)
		{
			stream.SetLength(Length);

			stream.Position = 0;

			stream.Write(_bytes.ToArray(), 0, _bytes.Count);

			_hasChanges = false;
		}

		/// <summary>
		/// Occurs, when the write buffer contains new changes.
		/// </summary>
		public event EventHandler Changed;

		/// <summary>
		/// Occurs, when InsertBytes or DeleteBytes method is called.
		/// </summary>
		public event EventHandler LengthChanged;


		/// <summary>
		/// Reads a byte from the byte collection.
		/// </summary>
		/// <param name="index">the index of the byte to read</param>
		/// <returns>the byte</returns>
		public byte ReadByte(long index)
		{ return _bytes[(int)index]; }

		public byte[] ReadBytes(long offset, long size)
		{
			return _bytes.GetRange((int)offset, (int)size).ToArray();
		}

		public long WriteBytes(long index, byte[] buffer, long length)
		{
			byte[] original = ReadBytes(index, length);

			long bytes_written = 0;

			for(int i = 0 ; i < length; ++i)
			{

				if( ( index + i ) >=  _bytes.Count )
					break;

				_bytes[(int)index + i] = buffer[i];

				++bytes_written;
			}

			if(bytes_written == 0)
				return 0;

			HexAction action = new HexAction();
            action.type_ = HexActionType.WriteMany;
            action.data_new_ = buffer;
            action.data_old_ = original;
            action.length_ = length;
            action.position_ = index;
			undo_actions_.Add(action);

			if(UndoActionQueued != null)
			{
				UndoActionQueued.Invoke(this, action);
			}

			OnChanged(EventArgs.Empty);

			return bytes_written;
		}

		/// <summary>
		/// Write a byte into the byte collection.
		/// </summary>
		/// <param name="index">the index of the byte to write.</param>
		/// <param name="value">the byte</param>
		public void WriteByte(long index, byte value)
		{
			byte[] old = new byte[1] { _bytes[(int)index] };
			byte[] buffer = new byte[1] { value };

			_bytes[(int)index] = value;

			HexAction action = new HexAction();
            action.type_ = HexActionType.Write;
            action.data_new_ = buffer;
            action.data_old_ = old;
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
		/// Deletes bytes from the byte collection.
		/// </summary>
		/// <param name="index">the start index of the bytes to delete.</param>
		/// <param name="length">the length of bytes to delete.</param>
		public void DeleteBytes(long index, long length)
		{
			byte[] buffer = ReadBytes(index, length);

			int internal_index = (int)Math.Max(0, index);
			int internal_length = (int)Math.Min((int)Length, length);
			_bytes.RemoveRange(internal_index, internal_length); 

			HexAction action = new HexAction();
            action.type_ = HexActionType.Delete;
            action.data_new_ = null;
            action.data_old_ = buffer;
            action.length_ = length;
            action.position_ = index;
			undo_actions_.Add(action);

			if(UndoActionQueued != null)
			{
				UndoActionQueued.Invoke(this, action);
			}

			OnLengthChanged(EventArgs.Empty);
			OnChanged(EventArgs.Empty);
		}

		/// <summary>
		/// Inserts byte into the byte collection.
		/// </summary>
		/// <param name="index">the start index of the bytes in the byte collection</param>
		/// <param name="bs">the byte array to insert</param>
		public void InsertBytes(long index, byte[] bs)
		{ 
			_bytes.InsertRange((int)index, bs); 

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

			OnLengthChanged(EventArgs.Empty);
			OnChanged(EventArgs.Empty);
		}

		/// <summary>
		/// Gets the length of the bytes in the byte collection.
		/// </summary>
		public long Length
		{
			get
			{
				return _bytes.Count;
			}
		}

		/// <summary>
		/// Returns true
		/// </summary>
		public bool SupportsWriteByte()
		{
			return true;
		}

		/// <summary>
		/// Returns true
		/// </summary>
		public bool SupportsInsertBytes()
		{
			return true;
		}

		/// <summary>
		/// Returns true
		/// </summary>
		public bool SupportsDeleteBytes()
		{
			return true;
		}
		#endregion

    }
}
