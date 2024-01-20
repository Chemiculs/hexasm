#ifndef NATIVE_H
#define NATIVE_H

#include <string>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>

static class native {

private:

	static __forceinline std::string __fastcall format_time(const char* timeString) {
		std::tm tm_;
		std::stringstream ss(timeString);

		ss >> std::get_time(&tm_, "%a %b %d %H:%M:%S %Y");

		std::stringstream format_time;
		format_time << std::put_time(&tm_, "%m/%d/%Y %I:%M:%S %p");

		return format_time.str();
	}

public:
	
	template<typename T>
	static inline std::string __fastcall t_to_bits(T value) {
		std::string _return;

		_return.reserve(sizeof(T) * 8); // should increase performance to avoid redundant reallocation calls
		
		for (int i = ( ( sizeof(T) * 8 ) - 1); i > -1; --i) {
			_return += static_cast<char>((value & static_cast<T>((1 << i)) ? '1' : '0'));
		}
		
		return _return;
	}

	static inline unsigned char __cdecl bits_to_t(char* data) {

		unsigned char _return = static_cast<unsigned char>(0x00);

		for (auto i = 0; i < 8; ++i)
			if (data[i] == '1')
				_return |= static_cast<unsigned char>(1 << (7 - i));

		return _return;
	}

	static inline std::string __fastcall t_to_ctime32_t(const uint32_t value) {
		char* tm_ = _ctime32(reinterpret_cast<const __time32_t*>(&value));
		return format_time(tm_);
	}

};

#endif