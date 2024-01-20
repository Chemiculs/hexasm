#ifndef DEF_H
#define DEF_H

using namespace System;
using namespace System::Collections::Generic;

#pragma region Type Definitions

enum endian_mode {

	little,
	big

};

enum encoding_mode {

	ANSI,
	ASCII,
	EBCDIC

};

ref struct find_data_entry {

	UInt64 address;
	array<unsigned char>^ found_data_arr;

};

ref struct aob_signature {

	List<short>^ scan_list;

};

#pragma endregion

#pragma region Macros

#define LOWORD(WPARAM) static_cast<short>(WPARAM & 0xFFFF)
#define GETR(uclr) static_cast<unsigned char>(uclr & 0xFF)
#define GETG(uclr) static_cast<unsigned char>((uclr >> 8) & 0xFF)
#define GETB(uclr) static_cast<unsigned char>((uclr >> 16) & 0xFF)

#pragma region Ghetto MessageBox Shit

static __forceinline void MB_ERR(System::String^ _text, System::String^ _caption) {
	
	System::Windows::Forms::MessageBox::Show(_text, (_caption && _caption->Length > 0) ? _caption : System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Name, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
}

static __forceinline void MB_INF(System::String^ _text, System::String^ _caption) {

	System::Windows::Forms::MessageBox::Show(_text, (_caption && _caption->Length > 0) ? _caption : System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Name, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Information);
}

static __forceinline void MB_EXC(System::String^ _text, System::String^ _caption) {

	System::Windows::Forms::MessageBox::Show(_text, (_caption && _caption->Length > 0) ? _caption : System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Name, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Exclamation);
}

static __forceinline void MB_AST(System::String^ _text, System::String^ _caption) {

	System::Windows::Forms::MessageBox::Show(_text, (_caption && _caption->Length > 0) ? _caption : System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Name, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Asterisk);
}

static __forceinline System::Windows::Forms::DialogResult MB_QUE(System::String^ _text, System::String^ _caption) {

	return System::Windows::Forms::MessageBox::Show(_text, (_caption && _caption->Length > 0) ? _caption : System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Name, System::Windows::Forms::MessageBoxButtons::YesNo, System::Windows::Forms::MessageBoxIcon::Question);
}

static __forceinline void MB_WRN(System::String^ _text, System::String^ _caption) {

	System::Windows::Forms::MessageBox::Show(_text, (_caption && _caption->Length > 0) ? _caption : System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Name, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Warning);
}

#pragma endregion

#pragma endregion

#endif