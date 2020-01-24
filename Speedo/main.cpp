#include "script.h"
#include "Util/Paths.h"
#include "Util/Logger.hpp"
#include <GTAVManualTransmission/Gears/Memory/Versions.h>

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved) {
	std::string logFile = Paths::GetModuleFolder(hInstance) + modDir +
		"\\" + Paths::GetModuleNameWithoutExtension(hInstance) + ".log";
	logger.SetFile(logFile);
	Paths::SetOurModuleHandle(hInstance);

	switch (reason) {
		case DLL_PROCESS_ATTACH: {
			scriptRegister(hInstance, ScriptMain);
			logger.Clear();
			logger.Write(INFO, "GTAVSpeedo " + std::string(DISPLAY_VERSION));
			logger.Write(INFO, "Game version " + eGameVersionToString(getGameVersion()));
			logger.Write(INFO, "Script registered");
			break;
		}
		case DLL_PROCESS_DETACH: {
			logger.Write(INFO, "Init shutdown");
			scriptUnregister(hInstance);
			break;
		}
	}
	return TRUE;
}
