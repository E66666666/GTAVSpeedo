#include "ScriptSettings.hpp"

#include <vector>
#include <simpleini/SimpleIni.h>

#include "Util/Util.hpp"

ScriptSettings::ScriptSettings() { }

void ScriptSettings::SetFiles(const std::string &general) {
	settingsGeneralFile = general;
}

void ScriptSettings::Read() {
	parseSettingsGeneral();
}

void ScriptSettings::SaveGeneral() const {
	CSimpleIniA settingsGeneral;
	settingsGeneral.SetUnicode();
	settingsGeneral.LoadFile(settingsGeneralFile.c_str());
	settingsGeneral.SetBoolValue("SPEEDO", "Enable", Enable);

	settingsGeneral.SetValue("SPEEDO", "Name", SpeedoSettings.SpeedoName.c_str());

	settingsGeneral.SetBoolValue("SPEEDO", "FPVHide", SpeedoSettings.FPVHide);
	settingsGeneral.SetDoubleValue("SPEEDO", "FadeSpeed", SpeedoSettings.FadeSpeed);

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

	for (int i = 0; i < numNOSItems; i++) {
		settingsGeneral.SetDoubleValue("SPEEDO", ("NOS"+std::to_string(i)+"Xpos").c_str(), SpeedoSettings.NOSXpos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("NOS"+std::to_string(i)+"Ypos").c_str(), SpeedoSettings.NOSYpos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("NOS"+std::to_string(i)+"Size").c_str(), SpeedoSettings.NOSSize[i]);
	}
	settingsGeneral.SaveFile(settingsGeneralFile.c_str());
}

void ScriptSettings::Normalize(SpeedoStuff &coords) {
	float minX = 1.0f;
	float minY = 1.0f;

	minX > coords.RPMBgXpos ? minX = coords.RPMBgXpos : minX = minX;
	minX > coords.RPMNumXpos ? minX = coords.RPMNumXpos : minX = minX;
	minX > coords.RPMDialXpos ? minX = coords.RPMDialXpos : minX = minX;
	minX > coords.RPMRedXpos ? minX = coords.RPMRedXpos : minX = minX;
	minX > coords.TurboBgXpos ? minX = coords.TurboBgXpos : minX = minX;
	minX > coords.TurboNumXpos ? minX = coords.TurboNumXpos : minX = minX;
	minX > coords.TurboTextXpos ? minX = coords.TurboTextXpos : minX = minX;
	minX > coords.TurboDialXpos ? minX = coords.TurboDialXpos : minX = minX;
	minX > coords.TurboRed0Xpos ? minX = coords.TurboRed0Xpos : minX = minX;
	minX > coords.TurboRed1Xpos ? minX = coords.TurboRed1Xpos : minX = minX;
	minX > coords.SpeedXpos ? minX = coords.SpeedXpos : minX = minX;
	minX > coords.UnitXpos ? minX = coords.UnitXpos : minX = minX;
	minX > coords.GearXpos ? minX = coords.GearXpos : minX = minX;
	minX > coords.NOSTextXpos ? minX = coords.NOSTextXpos : minX = minX;
	for (int i = 0; i < numNOSItems; i++) {
		minX > coords.NOSXpos[i] ? minX = coords.NOSXpos[i] : minX = minX;
	}


	minY > coords.RPMBgYpos ? minY = coords.RPMBgYpos : minY = minY;
	minY > coords.RPMNumYpos ? minY = coords.RPMNumYpos : minY = minY;
	minY > coords.RPMDialYpos ? minY = coords.RPMDialYpos : minY = minY;
	minY > coords.RPMRedYpos ? minY = coords.RPMRedYpos : minY = minY;
	minY > coords.TurboBgYpos ? minY = coords.TurboBgYpos : minY = minY;
	minY > coords.TurboNumYpos ? minY = coords.TurboNumYpos : minY = minY;
	minY > coords.TurboTextYpos ? minY = coords.TurboTextYpos : minY = minY;
	minY > coords.TurboDialYpos ? minY = coords.TurboDialYpos : minY = minY;
	minY > coords.TurboRed0Ypos ? minY = coords.TurboRed0Ypos : minY = minY;
	minY > coords.TurboRed1Ypos ? minY = coords.TurboRed1Ypos : minY = minY;
	minY > coords.SpeedYpos ? minY = coords.SpeedYpos : minY = minY;
	minY > coords.UnitYpos ? minY = coords.UnitYpos : minY = minY;
	minY > coords.GearYpos ? minY = coords.GearYpos : minY = minY;
	minY > coords.NOSTextYpos ? minY = coords.NOSTextYpos : minY = minY;
	for (int i = 0; i < numNOSItems; i++) {
		minY > coords.NOSYpos[i] ? minY = coords.NOSYpos[i] : minY = minY;
	}

	coords.RPMBgXpos = coords.RPMBgXpos - minX;
	coords.RPMNumXpos = coords.RPMNumXpos - minX;
	coords.RPMDialXpos = coords.RPMDialXpos - minX;
	coords.RPMRedXpos = coords.RPMRedXpos - minX;
	coords.TurboBgXpos = coords.TurboBgXpos - minX;
	coords.TurboNumXpos = coords.TurboNumXpos - minX;
	coords.TurboTextXpos = coords.TurboTextXpos - minX;
	coords.TurboDialXpos = coords.TurboDialXpos - minX;
	coords.TurboRed0Xpos = coords.TurboRed0Xpos - minX;
	coords.TurboRed1Xpos = coords.TurboRed1Xpos - minX;
	coords.SpeedXpos = coords.SpeedXpos - minX;
	coords.UnitXpos = coords.UnitXpos - minX;
	coords.GearXpos = coords.GearXpos - minX;
	coords.NOSTextXpos = coords.NOSTextXpos - minX;
	for (int i = 0; i < numNOSItems; i++) {
		coords.NOSXpos[i] = coords.NOSXpos[i] - minX;
	}

	coords.RPMBgYpos = coords.RPMBgYpos - minY;
	coords.RPMNumYpos = coords.RPMNumYpos - minY;
	coords.RPMDialYpos = coords.RPMDialYpos - minY;
	coords.RPMRedYpos = coords.RPMRedYpos - minY;
	coords.TurboBgYpos = coords.TurboBgYpos - minY;
	coords.TurboNumYpos = coords.TurboNumYpos - minY;
	coords.TurboTextYpos = coords.TurboTextYpos - minY;
	coords.TurboDialYpos = coords.TurboDialYpos - minY;
	coords.TurboRed0Ypos = coords.TurboRed0Ypos - minY;
	coords.TurboRed1Ypos = coords.TurboRed1Ypos - minY;
	coords.SpeedYpos = coords.SpeedYpos - minY;
	coords.UnitYpos = coords.UnitYpos - minY;
	coords.GearYpos = coords.GearYpos - minY;
	coords.NOSTextYpos = coords.NOSTextYpos - minY;
	for (int i = 0; i < numNOSItems; i++) {
		coords.NOSYpos[i] = coords.NOSYpos[i] - minY;
	}

	SaveGeneral();
}

void ScriptSettings::parseSettingsGeneral() {
	if (!FileExists(settingsGeneralFile)) {
		SaveGeneral();
	}
	CSimpleIniA settingsGeneral;
	settingsGeneral.SetUnicode();
	settingsGeneral.LoadFile(settingsGeneralFile.c_str());
	Enable = settingsGeneral.GetValue("SPEEDO", "Enable");

	SpeedoSettings.SpeedoName = settingsGeneral.GetValue("SPEEDO", "Name");
	SpeedoSettings.FPVHide = static_cast<float>(settingsGeneral.GetBoolValue("SPEEDO", "FPVHide", false));
	SpeedoSettings.FadeSpeed = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "FadeSpeed", 0.05));

	SpeedoSettings.SpeedoXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "SpeedoXpos", 0.0));
	SpeedoSettings.SpeedoYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "SpeedoYpos", 0.0));
	SpeedoSettings.SpeedoSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "SpeedoSize", 1.0));

	SpeedoSettings.RPMBgXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMBgXpos"));
	SpeedoSettings.RPMBgYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMBgYpos"));
	SpeedoSettings.RPMBgSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMBgSize"));

	SpeedoSettings.RPMNumXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMNumXpos"));
	SpeedoSettings.RPMNumYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMNumYpos"));
	SpeedoSettings.RPMNumSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMNumSize"));

	SpeedoSettings.RPMDialXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMDialXpos"));
	SpeedoSettings.RPMDialYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMDialYpos"));
	SpeedoSettings.RPMDialSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMDialSize"));

	SpeedoSettings.RPMRedXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMRedXpos"));
	SpeedoSettings.RPMRedYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMRedYpos"));
	SpeedoSettings.RPMRedSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "RPMRedSize"));

	SpeedoSettings.TurboBgXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboBgXpos"));
	SpeedoSettings.TurboBgYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboBgYpos"));
	SpeedoSettings.TurboBgSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboBgSize"));
	
	SpeedoSettings.TurboNumXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboNumXpos"));
	SpeedoSettings.TurboNumYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboNumYpos"));
	SpeedoSettings.TurboNumSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboNumSize"));

	SpeedoSettings.TurboTextXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboTextXpos"));
	SpeedoSettings.TurboTextYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboTextYpos"));
	SpeedoSettings.TurboTextSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboTextSize"));

	SpeedoSettings.TurboDialXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboDialXpos"));
	SpeedoSettings.TurboDialYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboDialYpos"));
	SpeedoSettings.TurboDialSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboDialSize"));

	SpeedoSettings.TurboRed0Xpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboRed0Xpos"));
	SpeedoSettings.TurboRed0Ypos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboRed0Ypos"));
	SpeedoSettings.TurboRed0Size = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboRed0Size"));

	SpeedoSettings.TurboRed1Xpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboRed1Xpos"));
	SpeedoSettings.TurboRed1Ypos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboRed1Ypos"));
	SpeedoSettings.TurboRed1Size = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "TurboRed1Size"));

	SpeedoSettings.SpeedXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "SpeedXpos"));
	SpeedoSettings.SpeedYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "SpeedYpos"));
	SpeedoSettings.SpeedSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "SpeedSize"));

	SpeedoSettings.UnitXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "UnitXpos"));
	SpeedoSettings.UnitYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "UnitYpos"));
	SpeedoSettings.UnitSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "UnitSize"));

	SpeedoSettings.GearXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "GearXpos"));
	SpeedoSettings.GearYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "GearYpos"));
	SpeedoSettings.GearSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "GearSize"));

	SpeedoSettings.NOSTextXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "NOSTextXpos"));
	SpeedoSettings.NOSTextYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "NOSTextYpos"));
	SpeedoSettings.NOSTextSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "NOSTextSize"));

	for (int i = 0; i < numNOSItems; i++) {
		SpeedoSettings.NOSXpos[i] = settingsGeneral.GetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Xpos").c_str());
		SpeedoSettings.NOSYpos[i] = settingsGeneral.GetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Ypos").c_str());
		SpeedoSettings.NOSSize[i] = settingsGeneral.GetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Size").c_str());
	}
}
