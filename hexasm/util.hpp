#ifndef UTIL_H
#define UTIL_H

#pragma once
using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;

using namespace Be::Windows::Forms;

#include "native.hpp"
#include "interop.hpp"
#include "def.hpp"

static ref class util {
	
public:

	static inline array<find_data_entry^>^ find_all(HexBox^% control_h, FindOptions^% options, bool* cancel) {

		if (!control_h->ByteProvider->Length)
			return nullptr;

		Int64 found_address = 0;

		options->Direction = FindDirection::Forward;

		List<find_data_entry^>^ _return = gcnew List<find_data_entry^>();

		while ( (found_address = control_h->Find(options, false)) >= 0 ) {

			if (*cancel)
				return nullptr;

			find_data_entry^ entry = gcnew find_data_entry();

			entry->address = found_address;
			
			entry->found_data_arr = ( options->FindBufferUpper ? control_h->ByteProvider->ReadBytes(found_address, options->FindBuffer->Length) : (options->Type == FindType::AoB ? control_h->ByteProvider->ReadBytes(found_address, options->AoB->Length) : options->FindBuffer));

			_return->Add(entry);

			options->StartPosition = found_address + (options->Type == FindType::AoB ? options->AoB->Length : options->FindBuffer->Length);
		}

		return _return->ToArray();
	}

	static inline bool is_theme_dark(System::IntPtr hWnd)
	{
		System::IntPtr hdc = GetDC(hWnd);
		unsigned long pixelColor = GetPixel(hdc, 0, 0);
		ReleaseDC(hWnd, hdc);

		auto red = GETR(pixelColor);
		auto green = GETG(pixelColor);
		auto blue = GETB(pixelColor);

		double luminance = (0.2126 * red) + (0.7152 * green) + (0.0722 * blue);
		// Define a threshold to determine if the color is dark or light
		double threshold = 127.5;
		return luminance < threshold;
	}

	static inline bool __clrcall is_color_dark(System::Drawing::Color color) {
		auto color_raw = color.ToArgb();
		auto red = GETR(color_raw);
		auto green = GETG(color_raw);
		auto blue = GETB(color_raw);
		auto luminance = (0.2126 * red) + (0.7152 * green) + (0.0722 * blue);
		auto threshold = 127.5f;
		return luminance < threshold;
	}

	static array<unsigned char>^ __clrcall read_bytes_from_provider(IByteProvider^ provider, Int64 offset, Int64 length) {
		auto _return = gcnew array<unsigned char>(length);

		for (auto i = offset; i < (offset + length); ++i) {
			_return[i - offset] = provider->ReadByte(i);
		}

		return _return;
	}

	static inline String^ __clrcall reverse_hex_string_endian(String^% string_) {
		StringBuilder^ builder = gcnew StringBuilder();

		if (string_->Length % 2)
			string_ = string_->Insert(0, "0");

		for (auto i = (string_->Length - 2); i > -1; i -= 2) {
			auto sub_string = string_->Substring(i, 2);

			auto char1 = sub_string[0];
			auto char2 = sub_string[1];

			builder->Append(char2);
			builder->Append(char1);

		}

		return builder->ToString();
	}

	template<typename T>
	static inline bool __clrcall try_parse_hex_string(String^ hex_string, T% result, bool swap_endian)
	{
		if (hex_string->Length != (sizeof(T) * 2))
			return false;

		String^ string_i = hex_string;

		if (swap_endian)
			string_i = reverse_hex_string_endian(hex_string);

		try
		{
			switch (sizeof(T)) {
				case 1: {
					result = Convert::ToByte(string_i, 16);
					break;
				}
				case 2: {
					result = Convert::ToUInt16(string_i, 16);
					break;
				}
				case 4: {
					result = Convert::ToUInt32(string_i, 16);
					break;
				}
				case 8: {
					result = Convert::ToUInt64(string_i, 16);
					break;
				}
			}
		}
		catch (FormatException^){ return false; }

		return true;
	}

	static inline bool __clrcall try_parse_hex_string(String^ hex_string, array<Byte>^% buffer) {

		if (!hex_string->Length)
			return false;

		String^ trimmed_str = hex_string->Replace(" ", "");

		if (trimmed_str->Length % 2)
			return false;

		array<Byte>^ buffer_r = gcnew array<Byte>(trimmed_str->Length / 2);

		for (Int64 i = 0; i < trimmed_str->Length; i += 2) {

			Byte parsed;
			if (try_parse_hex_string(trimmed_str->Substring(i, 2), parsed, false)) {
				buffer_r[!i ? 0 : i / 2] = parsed;
			}
			else {
				return false;
			}
		}

		if (buffer)
			delete buffer;

		buffer = buffer_r;

		return true;
	}

	template<typename T>
	static inline T __clrcall parse_hex_string(String^ hex_string, bool swap_endian) {
		T _return{};

		if (!try_parse_hex_string(hex_string, _return, swap_endian))
			return static_cast<T>(0x0);

		return _return;
	}

	static inline array<Byte>^ __clrcall parse_hex_string(String^ hex_string) {

		array<Byte>^ buffer;

		if (!try_parse_hex_string(hex_string, buffer))
			return nullptr;
		
		return buffer;
	}

	static inline String^ __clrcall byte_array_to_hex_string(array<Byte>^ buffer) {
		
		StringBuilder^ _return = gcnew StringBuilder();

		for (auto i = 0; i < buffer->Length; ++i)
			_return->Append(buffer[i].ToString("X2"));

		auto return_s = _return->ToString();

		delete _return;

		return return_s;
	}

	static inline array<Byte>^ __clrcall native_array_to_managed(void* native, size_t size) {
		auto _return = gcnew array<Byte>(size);

		for (auto i = 0; i < size; ++i)
			_return[i] = reinterpret_cast<Byte*>(native)[i];

		return _return;
	}

	static inline Byte* __clrcall managed_array_to_native(array<Byte>^ buffer) {

		auto* buffer_n = reinterpret_cast<Byte*>(malloc(buffer->Length));

		for (auto i = 0; i < buffer->Length; ++i)
			buffer_n[i] = buffer[i];

		return buffer_n;
	}

	static inline Image^ __clrcall image_from_array(array<Byte>^ data) {
		auto stream_m = gcnew MemoryStream(data);

		auto _return = Image::FromStream(stream_m);

		stream_m->Close();
		delete stream_m;

		return _return;
	}
	

	static inline Image^ __clrcall image_from_native_array(void* native, size_t size) {
		auto array_m = native_array_to_managed(native, size);
		
		auto _return = image_from_array(array_m);

		delete array_m;

		return _return;
	}
};

#endif