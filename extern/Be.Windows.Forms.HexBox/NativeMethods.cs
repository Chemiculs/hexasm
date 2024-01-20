using System;
using System.Drawing;

namespace Be.Windows.Forms
{
	internal static class NativeMethods
	{
		// Caret definitions
		[System.Runtime.InteropServices.DllImport("user32.dll")]
		public static extern bool CreateCaret(IntPtr hWnd, IntPtr hBitmap, int nWidth, int nHeight);

		[System.Runtime.InteropServices.DllImport("user32.dll")]
		public static extern bool ShowCaret(IntPtr hWnd);

		[System.Runtime.InteropServices.DllImport("user32.dll")]
		public static extern bool DestroyCaret();

		[System.Runtime.InteropServices.DllImport("user32.dll")]
		public static extern bool SetCaretPos(int X, int Y);

		// Key definitions
		public const int WM_KEYDOWN = 0x100;
		public const int WM_KEYUP = 0x101;
		public const int WM_CHAR = 0x102;
	}
}
