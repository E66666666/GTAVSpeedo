#pragma once
#include <vector>
#include <string>

struct SpeedoInfo;

enum class UnitType {
    KPH = 0,
    MPH = 1,
};

class ScriptSettings {
public:
    ScriptSettings();
    void SetFiles(const std::string& general);
    void Read();
    std::vector<std::string> EnumerateSkins();
    void SaveGeneral() const;

    void Normalize(SpeedoInfo& coords);
    void SetModPath(const std::string& cs);

    /*
     * full path to the directory with your files
     */
    SpeedoInfo ReadSkin(std::string path);

    /*
     * full path to the directory with your files
     */
    void SaveSkin(std::string path, SpeedoInfo& info);


    // global settings
    bool Enable;
    UnitType Unit;
    bool HideInFPV;
    bool HideOnVehicleName;
    bool HideAreaName;

    float FadeSpeed;
    std::string DefaultSkin;

    bool ShowPlacementMenu;

    bool TurboScaling;
private:
    void parseSettingsGeneral();

    std::string settingsGeneralFile;
    std::string settingsMenuFile;
    std::string modPath;
};
