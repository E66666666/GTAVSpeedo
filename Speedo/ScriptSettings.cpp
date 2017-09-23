#include "ScriptSettings.hpp"

#include <vector>
#include <simpleini/SimpleIni.h>

#include "Util/Util.hpp"
#include <experimental/filesystem>
#include "SpeedoInfo.h"


ScriptSettings::ScriptSettings() { }

void ScriptSettings::SetFiles(const std::string &general) {
	settingsGeneralFile = general;
}

void ScriptSettings::SetModPath(const std::string &cs) {
	modPath = cs;
}

void ScriptSettings::Read() {
	parseSettingsGeneral();
}

/*
 * Inside the 'iktSpeedo' folder, it tries to find files + folders named this:
 * [skin_name]
 * [skin_name].ini
 * and that skin_name skin is then added to list of choosable skins
 */
std::vector<std::string> ScriptSettings::EnumerateSkins() {
	namespace fs = std::experimental::filesystem;
	std::vector<std::string> foundSkins;

	std::vector<std::string> folders;
	std::vector<std::string> files;

	for (auto &file : fs::directory_iterator(modPath)) {
		if (fs::is_directory(file)) {
			folders.push_back(fs::path(file).stem().string());
		}
		if (fs::is_regular_file(file) && fs::path(file).extension().string() == ".ini") {
			files.push_back(fs::path(file).stem().string());
		}
	}

	for (auto folder : folders) {
		for (auto file : files) {
			if (folder == file) foundSkins.push_back(file);
		}
	}

	return foundSkins;
}

void ScriptSettings::parseSettingsGeneral() {
	if (!FileExists(settingsGeneralFile)) {
		SaveGeneral();
	}
	CSimpleIniA settingsGeneral;
	settingsGeneral.SetUnicode();
	settingsGeneral.LoadFile(settingsGeneralFile.c_str());
	Enable = settingsGeneral.GetBoolValue("SETTINGS", "Enable");
	FPVHide = static_cast<float>(settingsGeneral.GetBoolValue("SETTINGS", "FPVHide", false));
	FadeSpeed = static_cast<float>(settingsGeneral.GetDoubleValue("SETTINGS", "FadeSpeed", 0.05));

	ShowPlacementMenu = settingsGeneral.GetBoolValue("DEV", "ShowPlacementMenu", false);

}


void ScriptSettings::SaveGeneral() const {
	CSimpleIniA settingsGeneral;
	settingsGeneral.SetUnicode();
	settingsGeneral.LoadFile(settingsGeneralFile.c_str());
	settingsGeneral.SetBoolValue("SETTINGS", "Enable", Enable);
	settingsGeneral.SetBoolValue("SETTINGS", "FPVHide", FPVHide);
	settingsGeneral.SetDoubleValue("SETTINGS", "FadeSpeed", FadeSpeed);

	settingsGeneral.SaveFile(settingsGeneralFile.c_str());
}

void ScriptSettings::SaveSkin(std::string path, SpeedoInfo &info) {
	CSimpleIniA skinSettings;
	skinSettings.SetUnicode();
	skinSettings.LoadFile((path + ".ini").c_str());

	skinSettings.SetValue("LAYOUT", "Name", info.SpeedoName.c_str());

	skinSettings.SetDoubleValue("LAYOUT", "SpeedoXpos", info.SpeedoXpos);
	skinSettings.SetDoubleValue("LAYOUT", "SpeedoYpos", info.SpeedoYpos);
	skinSettings.SetDoubleValue("LAYOUT", "SpeedoSize", info.SpeedoSize);

	skinSettings.SetDoubleValue("LAYOUT", "RPMBgXpos", info.RPMBgXpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMBgYpos", info.RPMBgYpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMBgSize", info.RPMBgSize);

	skinSettings.SetDoubleValue("LAYOUT", "RPMNumXpos", info.RPMNumXpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMNumYpos", info.RPMNumYpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMNumSize", info.RPMNumSize);

	skinSettings.SetDoubleValue("LAYOUT", "RPMDialXpos", info.RPMDialXpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMDialYpos", info.RPMDialYpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMDialSize", info.RPMDialSize);

	skinSettings.SetDoubleValue("LAYOUT", "RPMRedXpos", info.RPMRedXpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMRedYpos", info.RPMRedYpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMRedSize", info.RPMRedSize);

	skinSettings.SetDoubleValue("LAYOUT", "TurboBgXpos", info.TurboBgXpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboBgYpos", info.TurboBgYpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboBgSize", info.TurboBgSize);
	
	skinSettings.SetDoubleValue("LAYOUT", "TurboNumXpos", info.TurboNumXpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboNumYpos", info.TurboNumYpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboNumSize", info.TurboNumSize);

	skinSettings.SetDoubleValue("LAYOUT", "TurboTextXpos", info.TurboTextXpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboTextYpos", info.TurboTextYpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboTextSize", info.TurboTextSize);

	skinSettings.SetDoubleValue("LAYOUT", "TurboDialXpos", info.TurboDialXpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboDialYpos", info.TurboDialYpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboDialSize", info.TurboDialSize);

	skinSettings.SetDoubleValue("LAYOUT", "TurboRed0Xpos", info.TurboRed0Xpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboRed0Ypos", info.TurboRed0Ypos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboRed0Size", info.TurboRed0Size);

	skinSettings.SetDoubleValue("LAYOUT", "TurboRed1Xpos", info.TurboRed1Xpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboRed1Ypos", info.TurboRed1Ypos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboRed1Size", info.TurboRed1Size);

	skinSettings.SetDoubleValue("LAYOUT", "SpeedXpos", info.SpeedXpos);
	skinSettings.SetDoubleValue("LAYOUT", "SpeedYpos", info.SpeedYpos);
	skinSettings.SetDoubleValue("LAYOUT", "SpeedSize", info.SpeedSize);

	skinSettings.SetDoubleValue("LAYOUT", "UnitXpos", info.UnitXpos);
	skinSettings.SetDoubleValue("LAYOUT", "UnitYpos", info.UnitYpos);
	skinSettings.SetDoubleValue("LAYOUT", "UnitSize", info.UnitSize);

	skinSettings.SetDoubleValue("LAYOUT", "GearXpos", info.GearXpos);
	skinSettings.SetDoubleValue("LAYOUT", "GearYpos", info.GearYpos);
	skinSettings.SetDoubleValue("LAYOUT", "GearSize", info.GearSize);

	skinSettings.SetDoubleValue("LAYOUT", "NOSTextXpos", info.NOSTextXpos);
	skinSettings.SetDoubleValue("LAYOUT", "NOSTextYpos", info.NOSTextYpos);
	skinSettings.SetDoubleValue("LAYOUT", "NOSTextSize", info.NOSTextSize);

	skinSettings.SetDoubleValue("LAYOUT", "ShiftLightXpos", info.ShiftLightXpos);
	skinSettings.SetDoubleValue("LAYOUT", "ShiftLightYpos", info.ShiftLightYpos);
	skinSettings.SetDoubleValue("LAYOUT", "ShiftLightSize", info.ShiftLightSize);

	for (int i = 0; i < numNOSItemsStage1; i++) {
		skinSettings.SetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage1Xpos").c_str(), info.NOSStage1Xpos[i]);
		skinSettings.SetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage1Ypos").c_str(), info.NOSStage1Ypos[i]);
		skinSettings.SetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage1Size").c_str(), info.NOSStage1Size[i]);
	}

	for (int i = 0; i < numNOSItemsStage2; i++) {
		skinSettings.SetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage2Xpos").c_str(), info.NOSStage2Xpos[i]);
		skinSettings.SetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage2Ypos").c_str(), info.NOSStage2Ypos[i]);
		skinSettings.SetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage2Size").c_str(), info.NOSStage2Size[i]);
	}

	for (int i = 0; i < numNOSItemsStage3; i++) {
		skinSettings.SetDoubleValue("LAYOUT", ("NOS"+std::to_string(i)+"Stage3Xpos").c_str(), info.NOSStage3Xpos[i]);
		skinSettings.SetDoubleValue("LAYOUT", ("NOS"+std::to_string(i)+"Stage3Ypos").c_str(), info.NOSStage3Ypos[i]);
		skinSettings.SetDoubleValue("LAYOUT", ("NOS"+std::to_string(i)+"Stage3Size").c_str(), info.NOSStage3Size[i]);
	}

	skinSettings.SaveFile((path + ".ini").c_str());
}

SpeedoInfo ScriptSettings::ReadSkin(std::string path) {
	SpeedoInfo speedoInfo;

	CSimpleIniA skinSettings;
	skinSettings.SetUnicode();
	skinSettings.LoadFile((path+ ".ini").c_str());

	speedoInfo.SpeedoName = skinSettings.GetValue("LAYOUT", "Name");

	speedoInfo.SpeedoXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "SpeedoXpos", 0.0));
	speedoInfo.SpeedoYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "SpeedoYpos", 0.0));
	speedoInfo.SpeedoSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "SpeedoSize", 1.0));

	speedoInfo.RPMBgXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMBgXpos"));
	speedoInfo.RPMBgYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMBgYpos"));
	speedoInfo.RPMBgSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMBgSize"));

	speedoInfo.RPMNumXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMNumXpos"));
	speedoInfo.RPMNumYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMNumYpos"));
	speedoInfo.RPMNumSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMNumSize"));

	speedoInfo.RPMDialXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMDialXpos"));
	speedoInfo.RPMDialYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMDialYpos"));
	speedoInfo.RPMDialSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMDialSize"));

	speedoInfo.RPMRedXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMRedXpos"));
	speedoInfo.RPMRedYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMRedYpos"));
	speedoInfo.RPMRedSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMRedSize"));

	speedoInfo.TurboBgXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboBgXpos"));
	speedoInfo.TurboBgYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboBgYpos"));
	speedoInfo.TurboBgSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboBgSize"));
	
	speedoInfo.TurboNumXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboNumXpos"));
	speedoInfo.TurboNumYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboNumYpos"));
	speedoInfo.TurboNumSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboNumSize"));

	speedoInfo.TurboTextXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboTextXpos"));
	speedoInfo.TurboTextYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboTextYpos"));
	speedoInfo.TurboTextSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboTextSize"));

	speedoInfo.TurboDialXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboDialXpos"));
	speedoInfo.TurboDialYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboDialYpos"));
	speedoInfo.TurboDialSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboDialSize"));

	speedoInfo.TurboRed0Xpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboRed0Xpos"));
	speedoInfo.TurboRed0Ypos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboRed0Ypos"));
	speedoInfo.TurboRed0Size = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboRed0Size"));

	speedoInfo.TurboRed1Xpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboRed1Xpos"));
	speedoInfo.TurboRed1Ypos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboRed1Ypos"));
	speedoInfo.TurboRed1Size = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboRed1Size"));

	speedoInfo.SpeedXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "SpeedXpos"));
	speedoInfo.SpeedYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "SpeedYpos"));
	speedoInfo.SpeedSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "SpeedSize"));

	speedoInfo.UnitXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "UnitXpos"));
	speedoInfo.UnitYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "UnitYpos"));
	speedoInfo.UnitSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "UnitSize"));

	speedoInfo.GearXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "GearXpos"));
	speedoInfo.GearYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "GearYpos"));
	speedoInfo.GearSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "GearSize"));

	speedoInfo.NOSTextXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "NOSTextXpos"));
	speedoInfo.NOSTextYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "NOSTextYpos"));
	speedoInfo.NOSTextSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "NOSTextSize"));

	speedoInfo.ShiftLightXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "ShiftLightXpos"));
	speedoInfo.ShiftLightYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "ShiftLightYpos"));
	speedoInfo.ShiftLightSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "ShiftLightSize"));

	for (int i = 0; i < numNOSItemsStage1; i++) {
		speedoInfo.NOSStage1Xpos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage1Xpos").c_str()));
		speedoInfo.NOSStage1Ypos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage1Ypos").c_str()));
		speedoInfo.NOSStage1Size[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage1Size").c_str()));
	}

	for (int i = 0; i < numNOSItemsStage2; i++) {
		speedoInfo.NOSStage2Xpos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage2Xpos").c_str()));
		speedoInfo.NOSStage2Ypos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage2Ypos").c_str()));
		speedoInfo.NOSStage2Size[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage2Size").c_str()));
	}

	for (int i = 0; i < numNOSItemsStage3; i++) {
		speedoInfo.NOSStage3Xpos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage3Xpos").c_str()));
		speedoInfo.NOSStage3Ypos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage3Ypos").c_str()));
		speedoInfo.NOSStage3Size[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage3Size").c_str()));
	}

	return speedoInfo;
}

void ScriptSettings::Normalize(SpeedoInfo &coords) {
//	float minX = 1.0f;
//	float minY = 1.0f;
//
//	minX > coords.RPMBgXpos ? minX = coords.RPMBgXpos : minX = minX;
//	minX > coords.RPMNumXpos ? minX = coords.RPMNumXpos : minX = minX;
//	minX > coords.RPMDialXpos ? minX = coords.RPMDialXpos : minX = minX;
//	minX > coords.RPMRedXpos ? minX = coords.RPMRedXpos : minX = minX;
//	minX > coords.TurboBgXpos ? minX = coords.TurboBgXpos : minX = minX;
//	minX > coords.TurboNumXpos ? minX = coords.TurboNumXpos : minX = minX;
//	minX > coords.TurboTextXpos ? minX = coords.TurboTextXpos : minX = minX;
//	minX > coords.TurboDialXpos ? minX = coords.TurboDialXpos : minX = minX;
//	minX > coords.TurboRed0Xpos ? minX = coords.TurboRed0Xpos : minX = minX;
//	minX > coords.TurboRed1Xpos ? minX = coords.TurboRed1Xpos : minX = minX;
//	minX > coords.SpeedXpos ? minX = coords.SpeedXpos : minX = minX;
//	minX > coords.UnitXpos ? minX = coords.UnitXpos : minX = minX;
//	minX > coords.GearXpos ? minX = coords.GearXpos : minX = minX;
//	minX > coords.NOSTextXpos ? minX = coords.NOSTextXpos : minX = minX;
//	for (int i = 0; i < numNOSItemsStage1; i++) {
//		minX > coords.NOSStage1Xpos[i] ? minX = coords.NOSStage1Xpos[i] : minX = minX;
//	}
//	for (int i = 0; i < numNOSItemsStage2; i++) {
//		minX > coords.NOSStage2Xpos[i] ? minX = coords.NOSStage2Xpos[i] : minX = minX;
//	}
//	for (int i = 0; i < numNOSItemsStage3; i++) {
//		minX > coords.NOSStage3Xpos[i] ? minX = coords.NOSStage3Xpos[i] : minX = minX;
//	}
//
//	minY > coords.RPMBgYpos ? minY = coords.RPMBgYpos : minY = minY;
//	minY > coords.RPMNumYpos ? minY = coords.RPMNumYpos : minY = minY;
//	minY > coords.RPMDialYpos ? minY = coords.RPMDialYpos : minY = minY;
//	minY > coords.RPMRedYpos ? minY = coords.RPMRedYpos : minY = minY;
//	minY > coords.TurboBgYpos ? minY = coords.TurboBgYpos : minY = minY;
//	minY > coords.TurboNumYpos ? minY = coords.TurboNumYpos : minY = minY;
//	minY > coords.TurboTextYpos ? minY = coords.TurboTextYpos : minY = minY;
//	minY > coords.TurboDialYpos ? minY = coords.TurboDialYpos : minY = minY;
//	minY > coords.TurboRed0Ypos ? minY = coords.TurboRed0Ypos : minY = minY;
//	minY > coords.TurboRed1Ypos ? minY = coords.TurboRed1Ypos : minY = minY;
//	minY > coords.SpeedYpos ? minY = coords.SpeedYpos : minY = minY;
//	minY > coords.UnitYpos ? minY = coords.UnitYpos : minY = minY;
//	minY > coords.GearYpos ? minY = coords.GearYpos : minY = minY;
//	minY > coords.NOSTextYpos ? minY = coords.NOSTextYpos : minY = minY;
//	for (int i = 0; i < numNOSItemsStage1; i++) {
//		minY > coords.NOSStage1Ypos[i] ? minY = coords.NOSStage1Ypos[i] : minY = minY;
//	}
//	for (int i = 0; i < numNOSItemsStage2; i++) {
//		minY > coords.NOSStage2Ypos[i] ? minY = coords.NOSStage2Ypos[i] : minY = minY;
//	}
//	for (int i = 0; i < numNOSItemsStage3; i++) {
//		minY > coords.NOSStage3Ypos[i] ? minY = coords.NOSStage3Ypos[i] : minY = minY;		
//	}
//
//	coords.RPMBgXpos = coords.RPMBgXpos - minX;
//	coords.RPMNumXpos = coords.RPMNumXpos - minX;
//	coords.RPMDialXpos = coords.RPMDialXpos - minX;
//	coords.RPMRedXpos = coords.RPMRedXpos - minX;
//	coords.TurboBgXpos = coords.TurboBgXpos - minX;
//	coords.TurboNumXpos = coords.TurboNumXpos - minX;
//	coords.TurboTextXpos = coords.TurboTextXpos - minX;
//	coords.TurboDialXpos = coords.TurboDialXpos - minX;
//	coords.TurboRed0Xpos = coords.TurboRed0Xpos - minX;
//	coords.TurboRed1Xpos = coords.TurboRed1Xpos - minX;
//	coords.SpeedXpos = coords.SpeedXpos - minX;
//	coords.UnitXpos = coords.UnitXpos - minX;
//	coords.GearXpos = coords.GearXpos - minX;
//	coords.NOSTextXpos = coords.NOSTextXpos - minX;
//	for (int i = 0; i < numNOSItemsStage1; i++) {
//		coords.NOSStage1Xpos[i] = coords.NOSStage1Xpos[i] - minX;
//	}
//	for (int i = 0; i < numNOSItemsStage2; i++) {
//		coords.NOSStage2Xpos[i] = coords.NOSStage2Xpos[i] - minX;
//	}
//	for (int i = 0; i < numNOSItemsStage3; i++) {
//		coords.NOSStage3Xpos[i] = coords.NOSStage3Xpos[i] - minX;
//	}
//
//	coords.RPMBgYpos = coords.RPMBgYpos - minY;
//	coords.RPMNumYpos = coords.RPMNumYpos - minY;
//	coords.RPMDialYpos = coords.RPMDialYpos - minY;
//	coords.RPMRedYpos = coords.RPMRedYpos - minY;
//	coords.TurboBgYpos = coords.TurboBgYpos - minY;
//	coords.TurboNumYpos = coords.TurboNumYpos - minY;
//	coords.TurboTextYpos = coords.TurboTextYpos - minY;
//	coords.TurboDialYpos = coords.TurboDialYpos - minY;
//	coords.TurboRed0Ypos = coords.TurboRed0Ypos - minY;
//	coords.TurboRed1Ypos = coords.TurboRed1Ypos - minY;
//	coords.SpeedYpos = coords.SpeedYpos - minY;
//	coords.UnitYpos = coords.UnitYpos - minY;
//	coords.GearYpos = coords.GearYpos - minY;
//	coords.NOSTextYpos = coords.NOSTextYpos - minY;
//	for (int i = 0; i < numNOSItemsStage1; i++) {
//		coords.NOSStage1Ypos[i] = coords.NOSStage1Ypos[i] - minY;
//	}
//	for (int i = 0; i < numNOSItemsStage2; i++) {
//		coords.NOSStage2Ypos[i] = coords.NOSStage2Ypos[i] - minY;
//	}
//	for (int i = 0; i < numNOSItemsStage3; i++) {
//		coords.NOSStage3Ypos[i] = coords.NOSStage3Ypos[i] - minY;
//	}
//	
//	SaveGeneral();
}
