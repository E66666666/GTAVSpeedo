#pragma once
#include <string>
#include <array>
#include <vector>

struct SpeedoInfo;

enum class UnitType {
	Metric = 0,
	Imperial = 1,
};

class ScriptSettings {
public:
	ScriptSettings();
	void SetFiles(const std::string &general);
	void Read();
	std::vector<std::string> EnumerateSkins();
	void SaveGeneral() const;
	void SaveSkin(std::string name);
	void Normalize(SpeedoInfo &coords);
	void SetModPath(const std::string & cs);
	SpeedoInfo ReadSkin(std::string name);
	bool Enable;
	//SpeedoInfo SpeedoSettings;
	UnitType Unit;
	bool ShowPlacementMenu;

	bool FPVHide;
	float FadeSpeed;
	std::string modPath;

private:
	void parseSettingsGeneral();

	std::string settingsGeneralFile;
	std::string settingsMenuFile;
};
