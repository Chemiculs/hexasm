#ifndef PE_H
#define PE_H

#include <vector>

#include "disasm.hpp"

namespace hexasm {

	namespace native {

		#define WIN32_LEAN_AND_MEAN
		#include <Windows.h>

#pragma pack(push, 1)

		typedef struct pe_file_information {

			IMAGE_DOS_HEADER header_dos;

			IMAGE_NT_HEADERS32 header_nt_32;
			IMAGE_NT_HEADERS64 header_nt_64;

			std::vector<IMAGE_SECTION_HEADER> image_section_headers;
		};

		typedef struct executable_section_subroutine {

			bool is_null_subroutine;
			bool is_entry_fn;

			cs_insn* instructions;
			size_t instruction_count;

			uintptr_t begin_offset;
			uintptr_t end_offset;

			IMAGE_SECTION_HEADER parent_section;

			inline void __cdecl free_() {

				free(instructions);
			}
		};

		typedef struct executable_section_code {

			IMAGE_SECTION_HEADER section;

			std::vector<executable_section_subroutine> subroutines;
			
			inline void __cdecl free_() {
				try {

					for (auto% sub : subroutines)
						sub.free_();

					subroutines.clear();
				}
				catch (std::exception& except) {}
			}

		};

#pragma pack(pop)

		class pe_file { // check machine architecture to determine if 32-bit or 64 and use appropriate structures

		private:

			void* raw_data_;
			size_t raw_size_;

			bool is_valid_pe_ = true;

			cs_mode mode_;

			pe_file_information information_;

			disasm_t* disassembler_;

			public: std::vector<executable_section_code>* section_decompilations_;

			static __declspec(noinline) IMAGE_DOS_HEADER __fastcall parse_dos_header(uint8_t* data) {

				return *reinterpret_cast<PIMAGE_DOS_HEADER>(data);
			}

			static __declspec(noinline) cs_mode __fastcall parse_architecture_t(uint8_t* data) {

				auto header_dos = *reinterpret_cast<PIMAGE_DOS_HEADER>(data);

				auto header_nt = *reinterpret_cast<PIMAGE_NT_HEADERS>(data + header_dos.e_lfanew);

				switch (header_nt.FileHeader.Machine) {
					case IMAGE_FILE_MACHINE_AMD64: {
						return CS_MODE_64;
						break;
					}
					case IMAGE_FILE_MACHINE_ARM64: {
						return CS_MODE_64;
						break;
					}
					case IMAGE_FILE_MACHINE_IA64: {
						return CS_MODE_64;
						break;
					}
					default: {
						return CS_MODE_32;
						break;
					}
				}
			}

			static __declspec(noinline) IMAGE_NT_HEADERS64 __fastcall parse_nt_headers64(uint8_t* data) noexcept {

				return *reinterpret_cast<PIMAGE_NT_HEADERS64>(data + reinterpret_cast<PIMAGE_DOS_HEADER>(data)->e_lfanew);
			}

			static __declspec(noinline) IMAGE_NT_HEADERS32 __fastcall parse_nt_headers32(uint8_t* data) noexcept {

				return *reinterpret_cast<PIMAGE_NT_HEADERS32>(data + reinterpret_cast<PIMAGE_DOS_HEADER>(data)->e_lfanew);
			}

			static __declspec(noinline) std::vector<IMAGE_SECTION_HEADER> __fastcall parse_sections(uint8_t* data, cs_mode mode) noexcept {

				std::vector<IMAGE_SECTION_HEADER> dir_list{};

				if (mode == CS_MODE_64) {

					auto headers_nt = reinterpret_cast<PIMAGE_NT_HEADERS64>(data + reinterpret_cast<PIMAGE_DOS_HEADER>(data)->e_lfanew);

					auto section_ptr = IMAGE_FIRST_SECTION(headers_nt);

					for (auto i = 0; i < headers_nt->FileHeader.NumberOfSections; ++i, ++section_ptr) {
						dir_list.push_back(*section_ptr);
					}
				}
				else {

					auto headers_nt = reinterpret_cast<PIMAGE_NT_HEADERS32>(data + reinterpret_cast<PIMAGE_DOS_HEADER>(data)->e_lfanew);

					auto section_ptr = IMAGE_FIRST_SECTION(headers_nt);

					for (auto i = 0; i < headers_nt->FileHeader.NumberOfSections; ++i, ++section_ptr) {
						dir_list.push_back(*section_ptr);
					}
				}

				return dir_list;
			}

			__declspec(noinline) std::vector<executable_section_subroutine> __fastcall decompile_image_section(uint8_t* data, IMAGE_SECTION_HEADER section_header) {
				
				auto section_start_rva = section_header.PointerToRawData + data;

				disasm_package_full_t disasm_pkg;

				if (mode_ == CS_MODE_32)
					disasm_pkg = disassembler_->disasm_32(section_start_rva, section_header.SizeOfRawData, section_header.PointerToRawData);
				else if (mode_ == CS_MODE_64)
					disasm_pkg = disassembler_->disasm_64(section_start_rva, section_header.SizeOfRawData, section_header.PointerToRawData);
				else
					return std::vector<executable_section_subroutine>{};
				// disassembler is failing to decompile whole text section
				auto entry_addr = ( (mode_ == CS_MODE_64 ? information_.header_nt_64.OptionalHeader.AddressOfEntryPoint : information_.header_nt_32.OptionalHeader.AddressOfEntryPoint) - section_header.VirtualAddress) + section_header.PointerToRawData;

				std::vector<executable_section_subroutine> subs_r{};

				uintptr_t last_sub_end = 0x0;

				for (size_t i = 0; i < disasm_pkg.instruction_count; ++i) {

					if (disasm_pkg.instructions[i].id == X86_INS_INT3) {
						++last_sub_end;
						continue;
					}

					if (disasm_pkg.instructions[i].id == X86_INS_RET || disasm_pkg.instructions[i].id == X86_INS_RETF || disasm_pkg.instructions[i].id == X86_INS_RETFQ ) {
						
						executable_section_subroutine sub{};

						//trim interrupt instructions from the subroutines - they will be at the beginning areas depending on alignment

						cs_insn* first_insn = &disasm_pkg.instructions[last_sub_end];
						int32_t insn_iterator = 0;
						while (first_insn->id == X86_INS_INT3) {
							if ((insn_iterator + last_sub_end) >= i) {
								// no interrupt padding 
								insn_iterator = 0;
								break;
							}

							++first_insn;
							++insn_iterator;
						}

						int32_t relocated_sub_end = last_sub_end + insn_iterator;

						sub.begin_offset = disasm_pkg.instructions[relocated_sub_end].address;
						sub.end_offset = disasm_pkg.instructions[i].address;

						auto insn_count = (i - relocated_sub_end) + 1; // +1 to include the ret insn 

						sub.instructions = reinterpret_cast<cs_insn*>(malloc(insn_count * sizeof(cs_insn)));

						for (auto x = relocated_sub_end; x < (relocated_sub_end + insn_count); ++x)
							sub.instructions[x - relocated_sub_end] = disasm_pkg.instructions[x];

						sub.instruction_count = insn_count;
						sub.parent_section = section_header;

						if (sub.instruction_count <= 1) {

							if (!sub.instruction_count)
								sub.is_null_subroutine = true;
							else if (sub.instructions[0].id == X86_INS_RET || sub.instructions[0].id == X86_INS_RETF || sub.instructions[0].id == X86_INS_RETFQ)
								sub.is_null_subroutine = true;
						}
						
						if (sub.begin_offset >= entry_addr)
							int x = entry_addr;

						if (sub.begin_offset <= entry_addr)
							if (sub.end_offset >= entry_addr)
								sub.is_entry_fn = true;

						subs_r.push_back(sub);

						last_sub_end = i + 1;
					}
				}

				//cs_free(disasm_pkg.instructions, disasm_pkg.instruction_count);
				free(disasm_pkg.instructions);

				return subs_r;
			}

		public:

#pragma region Ctor / Dtor

			__declspec(noinline) __fastcall pe_file(uint8_t* raw_file, size_t size) : raw_data_(raw_file), raw_size_(size) {

				if (!raw_file || !size) {
					is_valid_pe_ = false;
					return;
				}

				if (size < sizeof(IMAGE_DOS_HEADER)) {
					is_valid_pe_ = false;
					return;
				}

				auto header_dos = parse_dos_header(raw_file);

				if (header_dos.e_magic != 0x5A4D)
					is_valid_pe_ = false;

				if (size < header_dos.e_lfanew) {
					is_valid_pe_ = false;
					return;
				}

				mode_ = parse_architecture_t(raw_file);

				auto header_nt64 = parse_nt_headers64(raw_file);
				auto header_nt32 = parse_nt_headers32(raw_file);
				
				if (header_nt32.Signature != IMAGE_NT_SIGNATURE) {
					is_valid_pe_ = false;
					return;
				}

				auto section_headers = parse_sections(raw_file, mode_);

				information_ = pe_file_information{
					header_dos,
					header_nt32,
					header_nt64,
					section_headers
				};

				disassembler_ = new disasm_t();

				section_decompilations_ = new std::vector<executable_section_code>{};

				for (auto i = 0; i < information_.image_section_headers.size(); ++i)
					if ((information_.image_section_headers[i].Characteristics & IMAGE_SCN_CNT_CODE) == IMAGE_SCN_CNT_CODE)
						section_decompilations_->push_back(
							executable_section_code{
								information_.image_section_headers[i],
									decompile_image_section(raw_file, information_.image_section_headers[i]
								)}
						);

				int x = section_decompilations_->size();
			}

			inline __cdecl ~pe_file() {
				try {

					if(disassembler_)
						delete disassembler_;

					if(raw_data_)
						free(raw_data_);

					if(section_decompilations_)
						if(section_decompilations_->size())
							for (auto& sub_d : *section_decompilations_)
								sub_d.free_();
					
					if(section_decompilations_)
						delete section_decompilations_;

				}
				catch (std::exception& except) {}
			}

#pragma endregion

		};

	}
}

#endif