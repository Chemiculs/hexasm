using System;
using System.IO;
using System.Collections.Generic;

namespace Be.Windows.Forms
{
	public enum ProviderType
	{
		File,
		Memory,
		Process
	}

	public enum HexActionType
	{
		Write,
		WriteMany,
		Insert,
		Delete
	}
	public class HexAction
	{
		public HexActionType type_;
		public byte[] data_new_;
		public byte[] data_old_;
		public long length_;
		public long position_;
	}

	public delegate void UndoActionQueued(object sender, HexAction action);
	public delegate void RedoActionQueued(object sender, HexAction action);

	/// <summary>
	/// Defines a byte provider for HexBox control
	/// </summary>
	public interface IByteProvider
	{

		event UndoActionQueued UndoActionQueued;
		event RedoActionQueued RedoActionQueued;
		event UndoActionQueued UndoActionPerformed;
		event RedoActionQueued RedoActionPerformed;
		event EventHandler ChangesApplied;

		ProviderType Type { get; set; }
		List<HexAction> undo_actions_ { get; set;}
		List<HexAction> redo_actions_ { get; set;}

		void Undo();

		void Redo();
		byte[] ReadBytes(long offset, long size);
		/// <summary>
		/// Reads a byte from the provider
		/// </summary>
		/// <param name="index">the index of the byte to read</param>
		/// <returns>the byte to read</returns>
		byte ReadByte(long index);
		/// <summary>
		/// Writes a byte into the provider
		/// </summary>
		/// <param name="index">the index of the byte to write</param>
		/// <param name="value">the byte to write</param>
		void WriteByte(long index, byte value);

		long WriteBytes(long index, byte[] buffer, long length);
		/// <summary>
		/// Inserts bytes into the provider
		/// </summary>
		/// <param name="index"></param>
		/// <param name="bs"></param>
		/// <remarks>This method must raise the LengthChanged event.</remarks>
		void InsertBytes(long index, byte[] bs);
		/// <summary>
		/// Deletes bytes from the provider
		/// </summary>
		/// <param name="index">the start index of the bytes to delete</param>
		/// <param name="length">the length of the bytes to delete</param>
		/// <remarks>This method must raise the LengthChanged event.</remarks>
		void DeleteBytes(long index, long length);

		void SaveToStream(Stream stream);

		/// <summary>
		/// Returns the total length of bytes the byte provider is providing.
		/// </summary>
        long Length { get; }
		/// <summary>
		/// Occurs, when the Length property changed.
		/// </summary>
		event EventHandler LengthChanged;

		/// <summary>
		/// True, when changes are done.
		/// </summary>
		bool HasChanges();
		/// <summary>
		/// Applies changes.
		/// </summary>
		void ApplyChanges();
		/// <summary>
		/// Occurs, when bytes are changed.
		/// </summary>
		event EventHandler Changed;

		/// <summary>
		/// Returns a value if the WriteByte methods is supported by the provider.
		/// </summary>
		/// <returns>True, when it´s supported.</returns>
		bool SupportsWriteByte();
		/// <summary>
		/// Returns a value if the InsertBytes methods is supported by the provider.
		/// </summary>
		/// <returns>True, when it´s supported.</returns>
		bool SupportsInsertBytes();
		/// <summary>
		/// Returns a value if the DeleteBytes methods is supported by the provider.
		/// </summary>
		/// <returns>True, when it´s supported.</returns>
		bool SupportsDeleteBytes();
	}
}
