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
	
	void Normalize(SpeedoInfo &coords);
	void SetModPath(const std::string & cs);

	/*
	 * full path to the directory with your files
	 */
	SpeedoInfo ReadSkin(std::string path);

	/*
	 * full path to the directory with your files
	 */
	void SaveSkin(std::string path, SpeedoInfo &info);


	// global settings
	bool Enable;
	UnitType Unit;
	bool FPVHide;
	float FadeSpeed;
	std::string DefaultSkin;

	bool ShowPlacementMenu;

private:
	void parseSettingsGeneral();

	std::string settingsGeneralFile;
	std::string settingsMenuFile;
	std::string modPath;
};
