#ifndef INTEROP_H
#define INTEROP_H
#pragma once

using namespace System;

typedef unsigned int uint;
typedef unsigned long ulong;

#ifdef _WIN64

typedef unsigned long long uintptr_t;

#else

typedef unsigned int uintptr_t;

#endif

static inline void string_to_char_array(System::String^ str, char* outchar, int buffer_size) {
    IntPtr str_ptr = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str);

    char* native_string = static_cast<char*>(str_ptr.ToPointer());

    strncpy_s(outchar, buffer_size + 1, native_string, _TRUNCATE); // +1 bcuz char padding

    System::Runtime::InteropServices::Marshal::FreeHGlobal(str_ptr);
}

[System::Runtime::InteropServices::DllImport("user32.dll")]
extern bool SetCursorPos(int x, int y);

[System::Runtime::InteropServices::DllImport("user32.dll")]
extern IntPtr GetSubMenu(IntPtr hMenu, int nPos);

[System::Runtime::InteropServices::DllImport("user32.dll")]
extern IntPtr GetDC(IntPtr hWnd);

[System::Runtime::InteropServices::DllImport("gdi32.dll")]
extern ulong GetPixel(IntPtr hdc, int x, int y);

[System::Runtime::InteropServices::DllImport("user32.dll")]
extern int ReleaseDC(IntPtr hWnd, IntPtr hdc);

[System::Runtime::InteropServices::DllImport("user32.dll")]
extern int GetSystemMetrics(int nIndex);

[System::Runtime::InteropServices::DllImport("user32.dll", SetLastError = true)]
extern int RegisterHotKey(IntPtr hWnd, int id, uint fsModifiers, uint vk);

[System::Runtime::InteropServices::DllImport("user32.dll", SetLastError = true)]
extern int UnregisterHotKey(IntPtr hWnd, int id);

[System::Runtime::InteropServices::DllImport("kernel32.dll", SetLastError = true)]
extern int Beep(Int32 dwFreq, Int32 dwDuration);

[System::Runtime::InteropServices::DllImport("user32.dll")]
extern long SendMessage(IntPtr hWnd, uint Msg, IntPtr wParam, IntPtr lParam);

[System::Runtime::InteropServices::DllImport("user32.dll")]
extern int ShowWindow(uintptr_t hWnd, int sw_cmd);
[System::Runtime::InteropServices::DllImport("user32.dll")]
extern int ShowWindow(IntPtr hWnd, int sw_cmd);

[System::Runtime::InteropServices::DllImport("user32.dll")]
extern bool SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int X, int Y, int cx, int cy, unsigned int uFlags);

[System::Runtime::InteropServices::DllImport("user32.dll")]
extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);

[System::Runtime::InteropServices::DllImport("user32.dll", SetLastError = true)]
extern int GetWindowLong(IntPtr window, int index);

[System::Runtime::InteropServices::DllImport("user32.dll")]
extern IntPtr GetForegroundWindow();

[System::Runtime::InteropServices::DllImport("user32.dll")]
extern IntPtr GetWindow(IntPtr hWnd, UInt32 uCmd);

[System::Runtime::InteropServices::DllImport("user32.dll")]
extern int GetWindowText(IntPtr hWnd, System::Text::StringBuilder^ lpString, int nMaxCount);

[System::Runtime::InteropServices::DllImport("kernel32.dll", SetLastError = true)]
extern int Beep(Int32 dwFreq, Int32 dwDuration);

[System::Runtime::InteropServices::DllImport("uxtheme.dll")]
extern int SetWindowTheme(IntPtr hwnd, String^ pszSubAppName, String^ pszSubIdList);

[System::Runtime::InteropServices::DllImport("user32.dll")]
extern int GetSysColor(int nIndex);

#endif