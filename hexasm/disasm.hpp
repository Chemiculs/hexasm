#ifndef DISASM_H
#define DISASM_H

#ifdef _WIN64

#pragma comment(lib, "extern/capstone64.lib")
#include "extern/capstone64/include/capstone/capstone.h"

#else 

#pragma comment(lib, "extern/capstone32.lib")
#include "extern/capstone32/include/capstone/capstone.h"

#endif

#include <string>
#include <exception>
#include <vector>

namespace hexasm {

	namespace native {

		

		typedef struct disasm_package_t {

			bool success;
			cs_insn instruction;
			size_t memory_size;

		} disasm_package;

		typedef struct disasm_package_full_t {

			bool success;
			cs_insn* instructions;
			size_t instruction_count;

		} disasm_package_full;

		class disasm_t {

		private:

			csh handle_16, handle_32, handle_64;

#pragma region X86

			static const cs_arch arch_86 = CS_ARCH_X86;

			static const cs_mode mode_16 = CS_MODE_16;

			static const cs_mode mode_32 = CS_MODE_32;

			static const cs_mode mode_64 = CS_MODE_64;

#pragma endregion

#pragma region ARM

			csh handle_a32, handle_a64;

			static const cs_mode mode_arm = CS_MODE_ARM;

			static const cs_arch arch_arm32 = CS_ARCH_ARM;

			static const cs_arch arch_arm64 = CS_ARCH_ARM64;

#pragma endregion

#pragma region PowerPC

			csh handle_ppc_be, handle_ppc_le;

			static const cs_arch arch_ppc = CS_ARCH_PPC;
			
			static const cs_mode mode_be = CS_MODE_BIG_ENDIAN;

			static const cs_mode mode_le = CS_MODE_LITTLE_ENDIAN;

#pragma endregion

#pragma region MIPS

			csh handle_m32, handle_m64;

			static const cs_arch arch_mips = CS_ARCH_MIPS;

			static const cs_mode mode_mips32 = CS_MODE_MIPS32;

			static const cs_mode mode_mips64 = CS_MODE_MIPS64;

#pragma endregion

		public:

#pragma region Ctor / Dtor

			inline __cdecl disasm_t() {

				if (cs_open(arch_86, mode_16, &handle_16) != CS_ERR_OK)
					throw std::bad_alloc();

				if (cs_open(arch_86, mode_32, &handle_32) != CS_ERR_OK)
					throw std::bad_alloc();

				if (cs_open(arch_86, mode_64, &handle_64) != CS_ERR_OK)
					throw std::bad_alloc();

				if (cs_open(arch_arm32, mode_arm, &handle_a32) != CS_ERR_OK)
					throw std::bad_alloc();

				if (cs_open(arch_arm64, mode_arm, &handle_a64) != CS_ERR_OK)
					throw std::bad_alloc();

				if (cs_open(arch_ppc, mode_be, &handle_ppc_be) != CS_ERR_OK)
					throw std::bad_alloc();

				if (cs_open(arch_ppc, mode_le, &handle_ppc_le) != CS_ERR_OK)
					throw std::bad_alloc();

				if (cs_open(arch_mips, CS_MODE_MIPS32, &handle_m32) != CS_ERR_OK)
					throw std::bad_alloc();

				if (cs_open(arch_mips, CS_MODE_MIPS64, &handle_m64) != CS_ERR_OK)
					throw std::bad_alloc();

				cs_option(handle_16, CS_OPT_DETAIL, CS_OPT_ON);
				cs_option(handle_32, CS_OPT_DETAIL, CS_OPT_ON);
				cs_option(handle_64, CS_OPT_DETAIL, CS_OPT_ON);
				cs_option(handle_a32, CS_OPT_DETAIL, CS_OPT_ON);
				cs_option(handle_a64, CS_OPT_DETAIL, CS_OPT_ON);
				cs_option(handle_ppc_be, CS_OPT_DETAIL, CS_OPT_ON);
				cs_option(handle_ppc_le, CS_OPT_DETAIL, CS_OPT_ON);
				cs_option(handle_m32, CS_OPT_DETAIL, CS_OPT_ON);
				cs_option(handle_m64, CS_OPT_DETAIL, CS_OPT_ON);

			}

			inline __cdecl ~disasm_t() {
				try {

					cs_close(&handle_16);
					cs_close(&handle_32);
					cs_close(&handle_a32);
					cs_close(&handle_a64);
					cs_close(&handle_ppc_be);
					cs_close(&handle_ppc_le);
					cs_close(&handle_m32);
					cs_close(&handle_m64);

				}
				catch (std::exception& except) {}
			}

#pragma endregion

#pragma region X86 Disassembly

			inline disasm_package_t __fastcall disasm_16_single(void* buffer, size_t size, uintptr_t begin_address = static_cast<uintptr_t>(0x0)) {

				cs_insn* instructions;
				size_t instruction_count = static_cast<size_t>(0x0);

				if (instruction_count = cs_disasm(handle_16, reinterpret_cast<const uint8_t*>(buffer), size, begin_address, size, &instructions)) {

					disasm_package_t _return {
						true,
						instructions[0],
						instructions[0].size
					};

					cs_free(instructions, instruction_count);

					return _return;
				}

				return disasm_package_t{ false };
			}

			inline disasm_package_t __fastcall disasm_32_single(void* buffer, size_t size, uintptr_t begin_address = static_cast<uintptr_t>(0x0)) {

				cs_insn* instructions;
				size_t instruction_count = static_cast<size_t>(0x0);

				if (instruction_count = cs_disasm(handle_32, reinterpret_cast<const uint8_t*>(buffer), size, begin_address, size, &instructions)) {

					disasm_package_t _return{
						true,
						instructions[0],
						instructions[0].size
					};

					cs_free(instructions, instruction_count);

					return _return;
				}

				return disasm_package_t{ false };
			}

			inline disasm_package_full_t __fastcall disasm_32(void* buffer, size_t size, uintptr_t begin_address = static_cast<uintptr_t>(0x0)) {

				cs_insn* instructions;
				size_t instruction_count = static_cast<size_t>(0x0);

				if (instruction_count = cs_disasm(handle_32, reinterpret_cast<const uint8_t*>(buffer), size, begin_address, 0, &instructions)) {

					disasm_package_full_t _return{
						true,
						instructions,
						instruction_count
					};

					return _return;
				}

				return disasm_package_full_t{ false };
			}

			inline disasm_package_t __fastcall disasm_64_single(void* buffer, size_t size, uintptr_t begin_address = static_cast<uintptr_t>(0x0)) {

				cs_insn* instructions;
				size_t instruction_count = static_cast<size_t>(0x0);

				if (instruction_count = cs_disasm(handle_64, reinterpret_cast<const uint8_t*>(buffer), size, begin_address, size, &instructions)) {

					disasm_package_t _return{
						true,
						instructions[0],
						instructions[0].size
					};

					cs_free(instructions, instruction_count);

					return _return;
				}

				return disasm_package_t{ false };
			}

			// TODO: JUST LOOP THROUGH THE .TEXT SECTION INSTRUCTION BY INSTRUCTION AND APPEND SIZEOF(INSTRUCITON) ETC IT IS EASIER AND WILL WORK BETTER

			inline disasm_package_full_t __fastcall disasm_64( void* buffer, size_t size, uintptr_t begin_address = static_cast<uintptr_t>(0x0) ){

				cs_insn* instructions;
				size_t instruction_count = static_cast<size_t>(0x0);

				uintptr_t offset_ = reinterpret_cast<uintptr_t>(buffer);

				std::vector<cs_insn> instructions_v{};

				while (offset_ < (reinterpret_cast<uintptr_t>(buffer) + size)) {

					if (instruction_count = cs_disasm(handle_64, reinterpret_cast<const uint8_t*>(offset_), 16, begin_address + (offset_ - reinterpret_cast<uintptr_t>(buffer)), 0, &instructions)) {
						
						instructions_v.push_back(instructions[0]);

						offset_ += instructions[0].size;
					}
					else {

						offset_ += 2; // bad instruction, increment offset
					}

				}

				auto* return_insn = reinterpret_cast<cs_insn*>(malloc(sizeof(cs_insn) * instructions_v.size()));

				memcpy(return_insn, instructions_v.data(), sizeof(cs_insn) * instructions_v.size());

				return disasm_package_full_t{
					true,
					return_insn,
					instructions_v.size()
				};


			}

#pragma endregion

#pragma region ARM Disassembly

			inline disasm_package_t __fastcall disasm_a32_single(void* buffer, size_t size, uintptr_t begin_address = static_cast<uintptr_t>(0x0)) {

				cs_insn* instructions;
				size_t instruction_count = static_cast<size_t>(0x0);

				if (instruction_count = cs_disasm(handle_a32, reinterpret_cast<const uint8_t*>(buffer), size, begin_address, size, &instructions)) {

					disasm_package_t _return{
						true,
						instructions[0],
						instructions[0].size
					};

					cs_free(instructions, instruction_count);

					return _return;
				}

				return disasm_package_t{ false };
			}

			inline disasm_package_t __fastcall disasm_a64_single(void* buffer, size_t size, uintptr_t begin_address = static_cast<uintptr_t>(0x0)) {

				cs_insn* instructions;
				size_t instruction_count = static_cast<size_t>(0x0);

				if (instruction_count = cs_disasm(handle_a64, reinterpret_cast<const uint8_t*>(buffer), size, begin_address, size, &instructions)) {

					disasm_package_t _return{
						true,
						instructions[0],
						instructions[0].size
					};

					cs_free(instructions, instruction_count);

					return _return;
				}

				return disasm_package_t{ false };
			}

#pragma endregion

#pragma region PowerPC Disssembly

			inline disasm_package_t __fastcall disasm_ppc_be_single(void* buffer, size_t size, uintptr_t begin_address = static_cast<uintptr_t>(0x0)) {

				cs_insn* instructions;
				size_t instruction_count = static_cast<size_t>(0x0);

				if (instruction_count = cs_disasm(handle_ppc_be, reinterpret_cast<const uint8_t*>(buffer), size, begin_address, size, &instructions)) {

					disasm_package_t _return{
						true,
						instructions[0],
						instructions[0].size
					};

					cs_free(instructions, instruction_count);

					return _return;
				}

				return disasm_package_t{ false };
			}

			inline disasm_package_t __fastcall disasm_ppc_le_single(void* buffer, size_t size, uintptr_t begin_address = static_cast<uintptr_t>(0x0)) {

				cs_insn* instructions;
				size_t instruction_count = static_cast<size_t>(0x0);

				if (instruction_count = cs_disasm(handle_ppc_le, reinterpret_cast<const uint8_t*>(buffer), size, begin_address, size, &instructions)) {

					disasm_package_t _return{
						true,
						instructions[0],
						instructions[0].size
					};

					cs_free(instructions, instruction_count);

					return _return;
				}

				return disasm_package_t{ false };
			}

#pragma endregion

#pragma region MIPS Disassembly

			inline disasm_package_t __fastcall disasm_m32_single(void* buffer, size_t size, uintptr_t begin_address = static_cast<uintptr_t>(0x0)) {

				cs_insn* instructions;
				size_t instruction_count = static_cast<size_t>(0x0);

				if (instruction_count = cs_disasm(handle_m32, reinterpret_cast<const uint8_t*>(buffer), size, begin_address, size, &instructions)) {

					disasm_package_t _return{
						true,
						instructions[0],
						instructions[0].size
					};

					cs_free(instructions, instruction_count);

					return _return;
				}

				return disasm_package_t{ false };
			}

			inline disasm_package_t __fastcall disasm_m64_single(void* buffer, size_t size, uintptr_t begin_address = static_cast<uintptr_t>(0x0)) {

				cs_insn* instructions;
				size_t instruction_count = static_cast<size_t>(0x0);

				if (instruction_count = cs_disasm(handle_m64, reinterpret_cast<const uint8_t*>(buffer), size, begin_address, size, &instructions)) {

					disasm_package_t _return{
						true,
						instructions[0],
						instructions[0].size
					};

					cs_free(instructions, instruction_count);

					return _return;
				}

				return disasm_package_t{ false };
			}

#pragma endregion

		};

	}
}

#endif