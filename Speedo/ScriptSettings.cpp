#include "ScriptSettings.hpp"

#include <vector>
#include <simpleini/SimpleIni.h>

#include "Util/Util.hpp"
#include <filesystem>
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
	namespace fs = std::filesystem;
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
	HideInFPV = settingsGeneral.GetBoolValue("SETTINGS", "HideInFPV", false);
	HideOnVehicleName = settingsGeneral.GetBoolValue("SETTINGS", "HideOnVehicleName", false);
	HideAreaName = settingsGeneral.GetBoolValue("SETTINGS", "HideAreaName", false);
	FadeSpeed = static_cast<float>(settingsGeneral.GetDoubleValue("SETTINGS", "FadeSpeed", 0.05));
	DefaultSkin = settingsGeneral.GetValue("SETTINGS", "Default", "default");

	std::string unit = "kph";
	unit = settingsGeneral.GetValue("SETTINGS", "Unit", "kph");
	if (unit == "kph") Unit = UnitType::KPH;
	if (unit == "mph") Unit = UnitType::MPH;

	ShowPlacementMenu = settingsGeneral.GetBoolValue("DEV", "ShowPlacementMenu", false);
}


void ScriptSettings::SaveGeneral() const {
	CSimpleIniA settingsGeneral;
	settingsGeneral.SetUnicode();
	settingsGeneral.LoadFile(settingsGeneralFile.c_str());
	settingsGeneral.SetBoolValue("SETTINGS", "Enable", Enable);
	settingsGeneral.SetBoolValue("SETTINGS", "HideInFPV", HideInFPV);
	settingsGeneral.SetBoolValue("SETTINGS", "HideOnVehicleName", HideOnVehicleName);
	settingsGeneral.SetBoolValue("SETTINGS", "HideAreaName", HideAreaName);
	settingsGeneral.SetDoubleValue("SETTINGS", "FadeSpeed", FadeSpeed);

	std::string unit = "kph";
	if (Unit == UnitType::KPH) unit = "kph";
	if (Unit == UnitType::MPH) unit = "mph";
	settingsGeneral.SetValue("SETTINGS", "Unit", unit.c_str());

	settingsGeneral.SaveFile(settingsGeneralFile.c_str());
}

void ScriptSettings::SaveSkin(std::string path, SpeedoInfo &speedoInfo) {
	CSimpleIniA skinSettings;
	skinSettings.SetUnicode();
	skinSettings.LoadFile((path + ".ini").c_str());

	skinSettings.SetDoubleValue("LAYOUT", "SpeedoXpos", speedoInfo.SpeedoXpos);
	skinSettings.SetDoubleValue("LAYOUT", "SpeedoYpos", speedoInfo.SpeedoYpos);
	skinSettings.SetDoubleValue("LAYOUT", "SpeedoSize", speedoInfo.SpeedoSize);

	skinSettings.SetDoubleValue("LAYOUT", "RPMBgXpos", speedoInfo.RPMBgXpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMBgYpos", speedoInfo.RPMBgYpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMBgSize", speedoInfo.RPMBgSize);

	skinSettings.SetDoubleValue("LAYOUT", "RPMNumXpos", speedoInfo.RPMNumXpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMNumYpos", speedoInfo.RPMNumYpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMNumSize", speedoInfo.RPMNumSize);

	skinSettings.SetDoubleValue("LAYOUT", "RPMDialXpos", speedoInfo.RPMDialXpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMDialYpos", speedoInfo.RPMDialYpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMDialSize", speedoInfo.RPMDialSize);

	skinSettings.SetDoubleValue("LAYOUT", "RPMRedXpos", speedoInfo.RPMRedXpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMRedYpos", speedoInfo.RPMRedYpos);
	skinSettings.SetDoubleValue("LAYOUT", "RPMRedSize", speedoInfo.RPMRedSize);

	skinSettings.SetDoubleValue("LAYOUT", "TurboBgXpos", speedoInfo.TurboBgXpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboBgYpos", speedoInfo.TurboBgYpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboBgSize", speedoInfo.TurboBgSize);
	
	skinSettings.SetDoubleValue("LAYOUT", "TurboNumXpos", speedoInfo.TurboNumXpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboNumYpos", speedoInfo.TurboNumYpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboNumSize", speedoInfo.TurboNumSize);

	skinSettings.SetDoubleValue("LAYOUT", "TurboTextXpos", speedoInfo.TurboTextXpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboTextYpos", speedoInfo.TurboTextYpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboTextSize", speedoInfo.TurboTextSize);

	skinSettings.SetDoubleValue("LAYOUT", "TurboDialXpos", speedoInfo.TurboDialXpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboDialYpos", speedoInfo.TurboDialYpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboDialSize", speedoInfo.TurboDialSize);

	skinSettings.SetDoubleValue("LAYOUT", "TurboRed0Xpos", speedoInfo.TurboRed0Xpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboRed0Ypos", speedoInfo.TurboRed0Ypos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboRed0Size", speedoInfo.TurboRed0Size);

	skinSettings.SetDoubleValue("LAYOUT", "TurboRed1Xpos", speedoInfo.TurboRed1Xpos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboRed1Ypos", speedoInfo.TurboRed1Ypos);
	skinSettings.SetDoubleValue("LAYOUT", "TurboRed1Size", speedoInfo.TurboRed1Size);

	skinSettings.SetDoubleValue("LAYOUT", "SpeedXpos", speedoInfo.SpeedXpos);
	skinSettings.SetDoubleValue("LAYOUT", "SpeedYpos", speedoInfo.SpeedYpos);
	skinSettings.SetDoubleValue("LAYOUT", "SpeedSize", speedoInfo.SpeedSize);

	skinSettings.SetDoubleValue("LAYOUT", "UnitXpos", speedoInfo.UnitXpos);
	skinSettings.SetDoubleValue("LAYOUT", "UnitYpos", speedoInfo.UnitYpos);
	skinSettings.SetDoubleValue("LAYOUT", "UnitSize", speedoInfo.UnitSize);

	skinSettings.SetDoubleValue("LAYOUT", "GearXpos", speedoInfo.GearXpos);
	skinSettings.SetDoubleValue("LAYOUT", "GearYpos", speedoInfo.GearYpos);
	skinSettings.SetDoubleValue("LAYOUT", "GearSize", speedoInfo.GearSize);

	skinSettings.SetDoubleValue("LAYOUT", "NOSTextXpos", speedoInfo.NOSTextXpos);
	skinSettings.SetDoubleValue("LAYOUT", "NOSTextYpos", speedoInfo.NOSTextYpos);
	skinSettings.SetDoubleValue("LAYOUT", "NOSTextSize", speedoInfo.NOSTextSize);

	skinSettings.SetDoubleValue("LAYOUT", "ShiftLightXpos", speedoInfo.ShiftLightXpos);
	skinSettings.SetDoubleValue("LAYOUT", "ShiftLightYpos", speedoInfo.ShiftLightYpos);
	skinSettings.SetDoubleValue("LAYOUT", "ShiftLightSize", speedoInfo.ShiftLightSize);

	for (int i = 0; i < numNOSItemsStage1; i++) {
		skinSettings.SetDoubleValue("LAYOUT", ("NOSStage1_" + std::to_string(i) + "Xpos").c_str(), speedoInfo.NOSStage1Xpos[i]);
		skinSettings.SetDoubleValue("LAYOUT", ("NOSStage1_" + std::to_string(i) + "Ypos").c_str(), speedoInfo.NOSStage1Ypos[i]);
		skinSettings.SetDoubleValue("LAYOUT", ("NOSStage1_" + std::to_string(i) + "Size").c_str(), speedoInfo.NOSStage1Size[i]);
	}											      		    					   
												      		    					   
	for (int i = 0; i < numNOSItemsStage2; i++) {     		    					   
		skinSettings.SetDoubleValue("LAYOUT", ("NOSStage2_" + std::to_string(i) + "Xpos").c_str(), speedoInfo.NOSStage2Xpos[i]);
		skinSettings.SetDoubleValue("LAYOUT", ("NOSStage2_" + std::to_string(i) + "Ypos").c_str(), speedoInfo.NOSStage2Ypos[i]);
		skinSettings.SetDoubleValue("LAYOUT", ("NOSStage2_" + std::to_string(i) + "Size").c_str(), speedoInfo.NOSStage2Size[i]);
	}											      		  					   
												      		  					   
	for (int i = 0; i < numNOSItemsStage3; i++) {     		  					   
		skinSettings.SetDoubleValue("LAYOUT", ("NOSStage3_" + std::to_string(i) + "Xpos").c_str(), speedoInfo.NOSStage3Xpos[i]);
		skinSettings.SetDoubleValue("LAYOUT", ("NOSStage3_" + std::to_string(i) + "Ypos").c_str(), speedoInfo.NOSStage3Ypos[i]);
		skinSettings.SetDoubleValue("LAYOUT", ("NOSStage3_" + std::to_string(i) + "Size").c_str(), speedoInfo.NOSStage3Size[i]);
	}

	skinSettings.SetDoubleValue("ROTATE", "RPMDialCenterX", speedoInfo.RPMDialCenterX);
	skinSettings.SetDoubleValue("ROTATE", "RPMDialCenterY", speedoInfo.RPMDialCenterY);
	skinSettings.SetDoubleValue("ROTATE", "RPMDialZeroRot", speedoInfo.RPMDialZeroRot);
	skinSettings.SetDoubleValue("ROTATE", "RPMDialFullRot", speedoInfo.RPMDialFullRot);
	
	skinSettings.SetDoubleValue("ROTATE", "TurboDialCenterX", speedoInfo.TurboDialCenterX);
	skinSettings.SetDoubleValue("ROTATE", "TurboDialCenterY", speedoInfo.TurboDialCenterY);
	skinSettings.SetDoubleValue("ROTATE", "TurboDialZeroRot", speedoInfo.TurboDialZeroRot);
	skinSettings.SetDoubleValue("ROTATE", "TurboDialFullRot", speedoInfo.TurboDialFullRot);

	skinSettings.SaveFile((path + ".ini").c_str());
}

SpeedoInfo ScriptSettings::ReadSkin(std::string path) {
	SpeedoInfo speedoInfo;

	CSimpleIniA skinSettings;
	skinSettings.SetUnicode();
	skinSettings.LoadFile((path+ ".ini").c_str());

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
		speedoInfo.NOSStage1Xpos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOSStage1_" + std::to_string(i) + "Xpos").c_str()));
		speedoInfo.NOSStage1Ypos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOSStage1_" + std::to_string(i) + "Ypos").c_str()));
		speedoInfo.NOSStage1Size[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOSStage1_" + std::to_string(i) + "Size").c_str()));
	}																							   		    					   
																								   		    					   
	for (int i = 0; i < numNOSItemsStage2; i++) {												   		    					   
		speedoInfo.NOSStage2Xpos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOSStage2_" + std::to_string(i) + "Xpos").c_str()));
		speedoInfo.NOSStage2Ypos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOSStage2_" + std::to_string(i) + "Ypos").c_str()));
		speedoInfo.NOSStage2Size[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOSStage2_" + std::to_string(i) + "Size").c_str()));
	}																							   		  					   
																								   		  					   
	for (int i = 0; i < numNOSItemsStage3; i++) {												   		  					   
		speedoInfo.NOSStage3Xpos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOSStage3_" + std::to_string(i) + "Xpos").c_str()));
		speedoInfo.NOSStage3Ypos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOSStage3_" + std::to_string(i) + "Ypos").c_str()));
		speedoInfo.NOSStage3Size[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOSStage3_" + std::to_string(i) + "Size").c_str()));
	}

	speedoInfo.RPMDialCenterX = static_cast<float>(skinSettings.GetDoubleValue("ROTATE", "RPMDialCenterX"));
	speedoInfo.RPMDialCenterY = static_cast<float>(skinSettings.GetDoubleValue("ROTATE", "RPMDialCenterY"));
	speedoInfo.RPMDialZeroRot = static_cast<float>(skinSettings.GetDoubleValue("ROTATE", "RPMDialZeroRot"));
	speedoInfo.RPMDialFullRot = static_cast<float>(skinSettings.GetDoubleValue("ROTATE", "RPMDialFullRot"));

	speedoInfo.TurboDialCenterX = static_cast<float>(skinSettings.GetDoubleValue("ROTATE", "TurboDialCenterX"));
	speedoInfo.TurboDialCenterY = static_cast<float>(skinSettings.GetDoubleValue("ROTATE", "TurboDialCenterY"));
	speedoInfo.TurboDialZeroRot = static_cast<float>(skinSettings.GetDoubleValue("ROTATE", "TurboDialZeroRot"));
	speedoInfo.TurboDialFullRot = static_cast<float>(skinSettings.GetDoubleValue("ROTATE", "TurboDialFullRot"));

	// Drag-specific stuff but also allow others to use it if they provide the correct config lines
	if (skinSettings.GetSectionSize("EXTRA") != -1) {
		speedoInfo.ExtraHUDComponents = true;

		speedoInfo.GearBgXpos = static_cast<float>(skinSettings.GetDoubleValue("EXTRA", "GearBgXpos"));
		speedoInfo.GearBgYpos = static_cast<float>(skinSettings.GetDoubleValue("EXTRA", "GearBgYpos"));
		speedoInfo.GearBgSize = static_cast<float>(skinSettings.GetDoubleValue("EXTRA", "GearBgSize"));

		speedoInfo.SpeedBgXpos = static_cast<float>(skinSettings.GetDoubleValue("EXTRA", "SpeedBgXpos"));
		speedoInfo.SpeedBgYpos = static_cast<float>(skinSettings.GetDoubleValue("EXTRA", "SpeedBgYpos"));
		speedoInfo.SpeedBgSize = static_cast<float>(skinSettings.GetDoubleValue("EXTRA", "SpeedBgSize"));

		speedoInfo.HeatAlertXpos = static_cast<float>(skinSettings.GetDoubleValue("EXTRA", "HeatAlertXpos"));
		speedoInfo.HeatAlertYpos = static_cast<float>(skinSettings.GetDoubleValue("EXTRA", "HeatAlertYpos"));
		speedoInfo.HeatAlertSize = static_cast<float>(skinSettings.GetDoubleValue("EXTRA", "HeatAlertSize"));

		speedoInfo.HeatNumXpos = static_cast<float>(skinSettings.GetDoubleValue("EXTRA", "HeatNumXpos"));
		speedoInfo.HeatNumYpos = static_cast<float>(skinSettings.GetDoubleValue("EXTRA", "HeatNumYpos"));
		speedoInfo.HeatNumSize = static_cast<float>(skinSettings.GetDoubleValue("EXTRA", "HeatNumSize"));

		for (int i = 0; i < numDragHeat; i++) {
			speedoInfo.HeatXpos[i] = static_cast<float>(skinSettings.GetDoubleValue("EXTRA", ("Heat" + std::to_string(i) + "Xpos").c_str()));
			speedoInfo.HeatYpos[i] = static_cast<float>(skinSettings.GetDoubleValue("EXTRA", ("Heat" + std::to_string(i) + "Ypos").c_str()));
			speedoInfo.HeatSize[i] = static_cast<float>(skinSettings.GetDoubleValue("EXTRA", ("Heat" + std::to_string(i) + "Size").c_str()));
		}
	}
	else {
		speedoInfo.ExtraHUDComponents = false;
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
