/*
THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
http://dev-c.com
(C) Alexander Blade 2015
*/

#include "script.h"
#include "Util/Paths.h"
#include "Util/Logger.hpp"
#include "Util/Versions.h"

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved) {
	std::string logFile = Paths::GetModuleFolder(hInstance) + modDir +
		"\\" + Paths::GetModuleNameWithoutExtension(hInstance) + ".log";
	logger.SetFile(logFile);
	Paths::SetOurModuleHandle(hInstance);

	switch (reason) {
		case DLL_PROCESS_ATTACH: {
			scriptRegister(hInstance, ScriptMain);
			logger.Clear();
			logger.Write("GTAVSpeedo " + std::string(DISPLAY_VERSION));
			logger.Write("Game version " + eGameVersionToString(getGameVersion()));
			logger.Write("Script registered");
			break;
		}
		case DLL_PROCESS_DETACH: {
			logger.Write("Init shutdown");
			scriptUnregister(hInstance);
			break;
		}
	}
	return TRUE;
}
