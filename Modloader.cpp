#include "Console.h"
#include "Patch.h"
#include <stdlib.h>
#include <cstdint>

namespace ModloaderMain {

	//Opens the defaultPrefs.cs file the system configured text editor
	BuiltInFunction("modloader::editDefaultPrefs", _mlEditDefaultPrefs) {

		//Used to check if this function is implemented without executing the rest of the function
		if (argc >= 1)
		{
			return "true";
			exit;
		}
		ShellExecuteA(0, "edit", "defaultPrefs.cs", NULL, NULL, SW_SHOWDEFAULT);
		return "true";
	}

	//Opens the mods directory
	BuiltInFunction("modloader::openDir", _mlOpenDir) {
		if (argc >= 1)
		{
			return "true";
			exit;
		}
		CreateDirectory(".\\mods", NULL);
		ShellExecute(0, "explore", ".\\mods", NULL, NULL, SW_SHOWNORMAL);
		return "true";
	}

	BuiltInFunction("subroutine", _hc) {
		typedef int (*FunctionType)();
		FunctionType hardcallf = (FunctionType)0x0046662C; //0x004458A4
		hardcallf();
		return "true";
	}
	// CodePatch Opengl_widescreen = {
		// 0x0064B74B,
		// "",
		// "\x3D\xC8\x00\x00\x00\x0F\x82\xFB\x00\x00\x00\x3D\x80\x16\x00\x00\x0F\x87\xF0\x00\x00\x00\x8B\x54\x24\x74\x81\xFA\xA0\x00\x00\x00\x0F\x82\xE0\x00\x00\x00\x8B\x4C\x24\x74\x81\xF9\x80\x16\x00\x00\x0F\x87\xD0\x00\x00\x00\x8B\x44\x24\x6C\x90\x90\x90\x90\x90\x90\x90\x90\x90",
		// 67,
		// false
	// };

	struct Init2 {
		Init2() {
			// Opengl_widescreen.Apply(true);
		}
	} init2;
}; // namespace ExtendedPatchFunc