#include "Compatibility.h"

#include "Util/Logger.hpp"
#include <Windows.h>
#include <string>

namespace MTInternal {
    const char* (*GetVersion            )() = nullptr;
    bool        (*GetActive             )() = nullptr;
    void        (*SetActive             )(bool active) = nullptr;
    bool        (*NeutralGear           )() = nullptr;
    int         (*GetShiftMode          )() = nullptr;
    void        (*SetShiftMode          )(int mode) = nullptr;
    int         (*GetShiftIndicator     )() = nullptr;

    // This will be used to keep track for unloading.
    HMODULE GearsModule = nullptr;
    bool Available = false;
}

namespace MT {
    const char* GetVersion() {
        if (!MTInternal::Available)
            return "N/A";
        return MTInternal::GetVersion();
    }
    bool GetActive() {
        if (!MTInternal::Available)
            return false;
        return MTInternal::GetActive();
    }
    void SetActive(bool active) {
        if (!MTInternal::Available)
            return;
        MTInternal::SetActive(active);
    }
    bool NeutralGear() {
        if (!MTInternal::Available)
            return false;
        return MTInternal::NeutralGear();
    }
    int GetShiftMode() {
        if (!MTInternal::Available)
            return 0;
        return MTInternal::GetShiftMode();
    }
    void SetShiftMode(int mode) {
        if (!MTInternal::Available)
            return;
        MTInternal::SetShiftMode(mode);
    }
    int GetShiftIndicator() {
        if (!MTInternal::Available)
            return 0;
        return MTInternal::GetShiftIndicator();
    }
}

// This function checks if the supplied function is available in the given library.
template <typename T>
T CheckAddr(HMODULE lib, const std::string& funcName) {
    FARPROC func = GetProcAddress(lib, funcName.c_str());
    if (!func) {
        logger.Write(ERROR, "Couldn't get function [%s]", funcName.c_str());
        return nullptr;
    }
    logger.Write(DEBUG, "Found function [%s]", funcName.c_str());
    return reinterpret_cast<T>(func);
}

// The available functions are checked here. You could add more libraries here if needed.
bool setupCompatibility() {
    bool success = true;
    logger.Write(INFO, "Setting up Manual Transmission compatibility");
    MTInternal::GearsModule = GetModuleHandle(L"Gears.asi");
    if (!MTInternal::GearsModule) {
        logger.Write(ERROR, "Gears.asi not found");
        return false;
    }
    
    MTInternal::GetVersion = CheckAddr<const char* (*)()>(MTInternal::GearsModule, "MT_GetVersion");
    success &= MTInternal::GetVersion != nullptr;
    MTInternal::GetActive = CheckAddr<bool (*)()>(MTInternal::GearsModule, "MT_IsActive");
    success &= MTInternal::GetActive != nullptr;
    MTInternal::SetActive = CheckAddr<void (*)(bool)>(MTInternal::GearsModule, "MT_SetActive");
    success &= MTInternal::SetActive != nullptr;
    MTInternal::NeutralGear = CheckAddr<bool (*)()>(MTInternal::GearsModule, "MT_NeutralGear");
    success &= MTInternal::NeutralGear != nullptr;
    MTInternal::GetShiftMode = CheckAddr<int (*)()>(MTInternal::GearsModule, "MT_GetShiftMode");
    success &= MTInternal::GetShiftMode != nullptr;
    MTInternal::SetShiftMode = CheckAddr<void (*)(int)>(MTInternal::GearsModule, "MT_SetShiftMode");
    success &= MTInternal::SetShiftMode != nullptr;
    MTInternal::GetShiftIndicator = CheckAddr<int (*)()>(MTInternal::GearsModule, "MT_GetShiftIndicator");
    success &= MTInternal::GetShiftIndicator != nullptr;

    MTInternal::Available = success;

    return success;
}

void releaseCompatibility() {
    if (MTInternal::GearsModule) {
        // In this case GearsModule is gotten with GetModuleHandle, so no FreeLibrary is needed.
        // Just reset the pointer.
        MTInternal::GearsModule = nullptr;
    }
}
