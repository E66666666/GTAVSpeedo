#include "ScriptSettings.hpp"

#include <vector>
#include <simpleini/SimpleIni.h>

#include "Util/Util.hpp"
#include <experimental/filesystem>


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
	Enable = settingsGeneral.GetBoolValue("SPEEDO", "Enable");

	ShowPlacementMenu = settingsGeneral.GetBoolValue("SPEEDO", "ShowPlacementMenu", false);

	FPVHide = static_cast<float>(settingsGeneral.GetBoolValue("SPEEDO", "FPVHide", false));
	FadeSpeed = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "FadeSpeed", 0.05));
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

void ScriptSettings::SaveSkin(std::string name) {
	// TODO: Implement skin saving
	/*
	
	settingsGeneral.SetValue("SPEEDO", "Name", SpeedoSettings.SpeedoName.c_str());

	settingsGeneral.SetDoubleValue("SPEEDO", "SpeedoXpos", SpeedoSettings.SpeedoXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "SpeedoYpos", SpeedoSettings.SpeedoYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "SpeedoSize", SpeedoSettings.SpeedoSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "RPMBgXpos", SpeedoSettings.RPMBgXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "RPMBgYpos", SpeedoSettings.RPMBgYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "RPMBgSize", SpeedoSettings.RPMBgSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "RPMNumXpos", SpeedoSettings.RPMNumXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "RPMNumYpos", SpeedoSettings.RPMNumYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "RPMNumSize", SpeedoSettings.RPMNumSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "RPMDialXpos", SpeedoSettings.RPMDialXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "RPMDialYpos", SpeedoSettings.RPMDialYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "RPMDialSize", SpeedoSettings.RPMDialSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "RPMRedXpos", SpeedoSettings.RPMRedXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "RPMRedYpos", SpeedoSettings.RPMRedYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "RPMRedSize", SpeedoSettings.RPMRedSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "TurboBgXpos", SpeedoSettings.TurboBgXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboBgYpos", SpeedoSettings.TurboBgYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboBgSize", SpeedoSettings.TurboBgSize);
	
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboNumXpos", SpeedoSettings.TurboNumXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboNumYpos", SpeedoSettings.TurboNumYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboNumSize", SpeedoSettings.TurboNumSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "TurboTextXpos", SpeedoSettings.TurboTextXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboTextYpos", SpeedoSettings.TurboTextYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboTextSize", SpeedoSettings.TurboTextSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "TurboDialXpos", SpeedoSettings.TurboDialXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboDialYpos", SpeedoSettings.TurboDialYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboDialSize", SpeedoSettings.TurboDialSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "TurboRed0Xpos", SpeedoSettings.TurboRed0Xpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboRed0Ypos", SpeedoSettings.TurboRed0Ypos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboRed0Size", SpeedoSettings.TurboRed0Size);

	settingsGeneral.SetDoubleValue("SPEEDO", "TurboRed1Xpos", SpeedoSettings.TurboRed1Xpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboRed1Ypos", SpeedoSettings.TurboRed1Ypos);
	settingsGeneral.SetDoubleValue("SPEEDO", "TurboRed1Size", SpeedoSettings.TurboRed1Size);

	settingsGeneral.SetDoubleValue("SPEEDO", "SpeedXpos", SpeedoSettings.SpeedXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "SpeedYpos", SpeedoSettings.SpeedYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "SpeedSize", SpeedoSettings.SpeedSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "UnitXpos", SpeedoSettings.UnitXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "UnitYpos", SpeedoSettings.UnitYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "UnitSize", SpeedoSettings.UnitSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "GearXpos", SpeedoSettings.GearXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "GearYpos", SpeedoSettings.GearYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "GearSize", SpeedoSettings.GearSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "NOSTextXpos", SpeedoSettings.NOSTextXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "NOSTextYpos", SpeedoSettings.NOSTextYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "NOSTextSize", SpeedoSettings.NOSTextSize);

	for (int i = 0; i < numNOSItemsStage1; i++) {
		settingsGeneral.SetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Stage1Xpos").c_str(), SpeedoSettings.NOSStage1Xpos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Stage1Ypos").c_str(), SpeedoSettings.NOSStage1Ypos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Stage1Size").c_str(), SpeedoSettings.NOSStage1Size[i]);
	}

	for (int i = 0; i < numNOSItemsStage2; i++) {
		settingsGeneral.SetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Stage2Xpos").c_str(), SpeedoSettings.NOSStage2Xpos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Stage2Ypos").c_str(), SpeedoSettings.NOSStage2Ypos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Stage2Size").c_str(), SpeedoSettings.NOSStage2Size[i]);
	}

	for (int i = 0; i < numNOSItemsStage3; i++) {
		settingsGeneral.SetDoubleValue("SPEEDO", ("NOS"+std::to_string(i)+"Stage3Xpos").c_str(), SpeedoSettings.NOSStage3Xpos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("NOS"+std::to_string(i)+"Stage3Ypos").c_str(), SpeedoSettings.NOSStage3Ypos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("NOS"+std::to_string(i)+"Stage3Size").c_str(), SpeedoSettings.NOSStage3Size[i]);
	}
	
	*/
}

void ScriptSettings::ReadSkin(std::string skinName) {
	CSimpleIniA skinSettings;
	skinSettings.SetUnicode();
	skinSettings.LoadFile((skinName+ ".ini").c_str());

	SpeedoSettings.SpeedoName = skinSettings.GetValue("LAYOUT", "Name");

	SpeedoSettings.SpeedoXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "SpeedoXpos", 0.0));
	SpeedoSettings.SpeedoYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "SpeedoYpos", 0.0));
	SpeedoSettings.SpeedoSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "SpeedoSize", 1.0));

	SpeedoSettings.RPMBgXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMBgXpos"));
	SpeedoSettings.RPMBgYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMBgYpos"));
	SpeedoSettings.RPMBgSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMBgSize"));

	SpeedoSettings.RPMNumXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMNumXpos"));
	SpeedoSettings.RPMNumYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMNumYpos"));
	SpeedoSettings.RPMNumSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMNumSize"));

	SpeedoSettings.RPMDialXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMDialXpos"));
	SpeedoSettings.RPMDialYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMDialYpos"));
	SpeedoSettings.RPMDialSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMDialSize"));

	SpeedoSettings.RPMRedXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMRedXpos"));
	SpeedoSettings.RPMRedYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMRedYpos"));
	SpeedoSettings.RPMRedSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "RPMRedSize"));

	SpeedoSettings.TurboBgXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboBgXpos"));
	SpeedoSettings.TurboBgYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboBgYpos"));
	SpeedoSettings.TurboBgSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboBgSize"));
	
	SpeedoSettings.TurboNumXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboNumXpos"));
	SpeedoSettings.TurboNumYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboNumYpos"));
	SpeedoSettings.TurboNumSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboNumSize"));

	SpeedoSettings.TurboTextXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboTextXpos"));
	SpeedoSettings.TurboTextYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboTextYpos"));
	SpeedoSettings.TurboTextSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboTextSize"));

	SpeedoSettings.TurboDialXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboDialXpos"));
	SpeedoSettings.TurboDialYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboDialYpos"));
	SpeedoSettings.TurboDialSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboDialSize"));

	SpeedoSettings.TurboRed0Xpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboRed0Xpos"));
	SpeedoSettings.TurboRed0Ypos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboRed0Ypos"));
	SpeedoSettings.TurboRed0Size = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboRed0Size"));

	SpeedoSettings.TurboRed1Xpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboRed1Xpos"));
	SpeedoSettings.TurboRed1Ypos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboRed1Ypos"));
	SpeedoSettings.TurboRed1Size = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "TurboRed1Size"));

	SpeedoSettings.SpeedXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "SpeedXpos"));
	SpeedoSettings.SpeedYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "SpeedYpos"));
	SpeedoSettings.SpeedSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "SpeedSize"));

	SpeedoSettings.UnitXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "UnitXpos"));
	SpeedoSettings.UnitYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "UnitYpos"));
	SpeedoSettings.UnitSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "UnitSize"));

	SpeedoSettings.GearXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "GearXpos"));
	SpeedoSettings.GearYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "GearYpos"));
	SpeedoSettings.GearSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "GearSize"));

	SpeedoSettings.NOSTextXpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "NOSTextXpos"));
	SpeedoSettings.NOSTextYpos = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "NOSTextYpos"));
	SpeedoSettings.NOSTextSize = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", "NOSTextSize"));

	for (int i = 0; i < numNOSItemsStage1; i++) {
		SpeedoSettings.NOSStage1Xpos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage1Xpos").c_str()));
		SpeedoSettings.NOSStage1Ypos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage1Ypos").c_str()));
		SpeedoSettings.NOSStage1Size[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage1Size").c_str()));
	}

	for (int i = 0; i < numNOSItemsStage2; i++) {
		SpeedoSettings.NOSStage2Xpos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage2Xpos").c_str()));
		SpeedoSettings.NOSStage2Ypos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage2Ypos").c_str()));
		SpeedoSettings.NOSStage2Size[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage2Size").c_str()));
	}

	for (int i = 0; i < numNOSItemsStage3; i++) {
		SpeedoSettings.NOSStage3Xpos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage3Xpos").c_str()));
		SpeedoSettings.NOSStage3Ypos[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage3Ypos").c_str()));
		SpeedoSettings.NOSStage3Size[i] = static_cast<float>(skinSettings.GetDoubleValue("LAYOUT", ("NOS" + std::to_string(i) + "Stage3Size").c_str()));
	}
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
