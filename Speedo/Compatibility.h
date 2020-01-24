#pragma once
// Manual Transmission functions are grouped in a namespace. If desired,
// you could make your own class or something that encapsulates this in
// a prettier way.
//
// For full function descriptions, refer to 
// https://github.com/E66666666/GTAVManualTransmission/blob/master/Gears/ManualTransmission.h
namespace MT {
    const char* GetVersion();
    bool GetActive();
    void SetActive(bool active);
    bool NeutralGear();
    int GetShiftMode();
    void SetShiftMode(int mode);
    int GetShiftIndicator();
}

// The library is loaded and checked here. A boolean indicating success is returned.
// You can change this to whatever behavior is desired - for example, you could check
// each functions availability (!= nullptr), or disable integration altogether.
bool setupCompatibility();

// This should be called when your script shuts down or stops using integration,
// to release resources (the library).
void releaseCompatibility();
