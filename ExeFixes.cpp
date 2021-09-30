#include "Console.h"
#include "Patch.h"

namespace ExeFixes {
	CodePatch Opengl_widescreen = {
		0x0064B74B,
		"",
		"\x3D\x00\x01\x00\x00\x0F\x82\xFB\x00\x00\x00\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90",
		54,
		false
	};
	CodePatch Software_widescreen = {
		0x00658032,
		"",
		"\x3D\x00\x05\x00\x00\x7F\x0B\x8B\x55\xFC\x81\xFA\x00\x04",
		14,
		false
	};

	//                                                 |.  8DBD 38FFFFFF     LEA EDI,DWORD PTR SS:[EBP-C8]
	CodePatch dosfix = {
		0x0068C6B2,
		"",
		"\xE9OSFX",
		5,
		false
	};

	static const u32 fnBitStreamReadInt = 0x0056D4A0, fnReadPacketAcksResume = 0x0068C6E9;
	static const char* crashAttempt = "DoSFiX: Crash Attempt by %s";

	NAKED void DosFix() {
		__asm {
			push ebx
			lea edi, [ebp - 0xc8]
			lea ebx, [edi + (0x1a * 0x8)]
			jmp __primed_jump
			__read_ack_loop :
			lea eax, [ebp - 0xf0]
				mov edx, 0x5
				call[fnBitStreamReadInt]
				mov[edi - 0x4], eax
				inc dword ptr[ebp - 0x28]
				add edi, 0x8
				__primed_jump:
			lea eax, [ebp - 0xf0]
				mov edx, 0x3
				call[fnBitStreamReadInt]
				mov[edi], eax
				cmp edi, ebx
				jae __crash_attempt
				test eax, eax
				jnz __read_ack_loop
				__leave_loop :
			pop ebx
				jmp[fnReadPacketAcksResume]

				__crash_attempt :
				lea eax, [ebp + 0x28]
				push eax
				mov eax, [crashAttempt]
				push eax
				call Console::echo
				add esp, 0x8
				jmp __leave_loop
		}
	}

	struct Init {
		Init() {
			Opengl_widescreen.Apply(true);
			Software_widescreen.Apply(true);
			dosfix.DoctorRelative((u32)DosFix, 1).Apply(true);
		}
	} init;
}; // namespace ExeFixes