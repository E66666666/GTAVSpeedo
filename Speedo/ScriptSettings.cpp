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
	
	// DRAG
	settingsGeneral.SetDoubleValue("SPEEDO", "DragRPMBgXpos", SpeedoSettings.DragRPMBgXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragRPMBgYpos", SpeedoSettings.DragRPMBgYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragRPMBgSize", SpeedoSettings.DragRPMBgSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "DragLinesXpos", SpeedoSettings.DragLinesXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragLinesYpos", SpeedoSettings.DragLinesYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragLinesSize", SpeedoSettings.DragLinesSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "DragNosLinesXpos", SpeedoSettings.DragNosLinesXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragNosLinesYpos", SpeedoSettings.DragNosLinesYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragNosLinesSize", SpeedoSettings.DragNosLinesSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "DragHeatLinesXpos", SpeedoSettings.DragHeatLinesXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragHeatLinesYpos", SpeedoSettings.DragHeatLinesYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragHeatLinesSize", SpeedoSettings.DragHeatLinesSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "DragRPMDialXpos", SpeedoSettings.DragRPMDialXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragRPMDialYpos", SpeedoSettings.DragRPMDialYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragRPMDialSize", SpeedoSettings.DragRPMDialSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "DragRPMRedXpos", SpeedoSettings.DragRPMRedXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragRPMRedYpos", SpeedoSettings.DragRPMRedYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragRPMRedSize", SpeedoSettings.DragRPMRedSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "DragHeatAlertXpos", SpeedoSettings.DragHeatAlertXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragHeatAlertYpos", SpeedoSettings.DragHeatAlertYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragHeatAlertSize", SpeedoSettings.DragHeatAlertSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "DragShiftLightXpos", SpeedoSettings.DragShiftLightXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragShiftLightYpos", SpeedoSettings.DragShiftLightYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragShiftLightSize", SpeedoSettings.DragShiftLightSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "DragRPMBoxXpos", SpeedoSettings.DragRPMBoxXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragRPMBoxYpos", SpeedoSettings.DragRPMBoxYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragRPMBoxSize", SpeedoSettings.DragRPMBoxSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "DragSpeedBoxXpos", SpeedoSettings.DragSpeedBoxXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragSpeedBoxYpos", SpeedoSettings.DragSpeedBoxYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragSpeedBoxSize", SpeedoSettings.DragSpeedBoxSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "DragSpeedXpos", SpeedoSettings.DragSpeedXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragSpeedYpos", SpeedoSettings.DragSpeedYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragSpeedSize", SpeedoSettings.DragSpeedSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "DragUnitXpos", SpeedoSettings.DragUnitXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragUnitYpos", SpeedoSettings.DragUnitYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragUnitSize", SpeedoSettings.DragUnitSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "DragGearXpos", SpeedoSettings.DragGearXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragGearYpos", SpeedoSettings.DragGearYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragGearSize", SpeedoSettings.DragGearSize);

	for (int i = 0; i < numDragHeat; i++) {
		settingsGeneral.SetDoubleValue("SPEEDO", ("DragHeat" + std::to_string(i) + "Xpos").c_str(), SpeedoSettings.DragHeatXpos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("DragHeat" + std::to_string(i) + "Ypos").c_str(), SpeedoSettings.DragHeatYpos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("DragHeat" + std::to_string(i) + "Size").c_str(), SpeedoSettings.DragHeatSize[i]);
	}

	for (int i = 0; i < numNOSItemsStage1; i++) {
		settingsGeneral.SetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage1Xpos").c_str(), SpeedoSettings.DragNOSStage1Xpos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage1Ypos").c_str(), SpeedoSettings.DragNOSStage1Ypos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage1Size").c_str(), SpeedoSettings.DragNOSStage1Size[i]);
	}

	for (int i = 0; i < numNOSItemsStage2; i++) {
		settingsGeneral.SetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage2Xpos").c_str(), SpeedoSettings.DragNOSStage2Xpos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage2Ypos").c_str(), SpeedoSettings.DragNOSStage2Ypos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage2Size").c_str(), SpeedoSettings.DragNOSStage2Size[i]);
	}

	for (int i = 0; i < numNOSItemsStage3; i++) {
		settingsGeneral.SetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage3Xpos").c_str(), SpeedoSettings.DragNOSStage3Xpos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage3Ypos").c_str(), SpeedoSettings.DragNOSStage3Ypos[i]);
		settingsGeneral.SetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage3Size").c_str(), SpeedoSettings.DragNOSStage3Size[i]);
	}

	settingsGeneral.SetDoubleValue("SPEEDO", "DragTurboXpos", SpeedoSettings.DragTurboXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragTurboYpos", SpeedoSettings.DragTurboYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragTurboSize", SpeedoSettings.DragTurboSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "DragTurboDialXpos", SpeedoSettings.DragTurboDialXpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragTurboDialYpos", SpeedoSettings.DragTurboDialYpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragTurboDialSize", SpeedoSettings.DragTurboDialSize);

	settingsGeneral.SetDoubleValue("SPEEDO", "DragTurboRed1Xpos", SpeedoSettings.DragTurboRed1Xpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragTurboRed1Ypos", SpeedoSettings.DragTurboRed1Ypos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragTurboRed2Xpos", SpeedoSettings.DragTurboRed2Xpos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragTurboRed2Ypos", SpeedoSettings.DragTurboRed2Ypos);
	settingsGeneral.SetDoubleValue("SPEEDO", "DragTurboDialSize", SpeedoSettings.DragTurboDialSize);
	
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
	for (int i = 0; i < numNOSItemsStage1; i++) {
		minX > coords.NOSStage1Xpos[i] ? minX = coords.NOSStage1Xpos[i] : minX = minX;
	}
	for (int i = 0; i < numNOSItemsStage2; i++) {
		minX > coords.NOSStage2Xpos[i] ? minX = coords.NOSStage2Xpos[i] : minX = minX;
	}
	for (int i = 0; i < numNOSItemsStage3; i++) {
		minX > coords.NOSStage3Xpos[i] ? minX = coords.NOSStage3Xpos[i] : minX = minX;
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
	for (int i = 0; i < numNOSItemsStage1; i++) {
		minY > coords.NOSStage1Ypos[i] ? minY = coords.NOSStage1Ypos[i] : minY = minY;
	}
	for (int i = 0; i < numNOSItemsStage2; i++) {
		minY > coords.NOSStage2Ypos[i] ? minY = coords.NOSStage2Ypos[i] : minY = minY;
	}
	for (int i = 0; i < numNOSItemsStage3; i++) {
		minY > coords.NOSStage3Ypos[i] ? minY = coords.NOSStage3Ypos[i] : minY = minY;		
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
	for (int i = 0; i < numNOSItemsStage1; i++) {
		coords.NOSStage1Xpos[i] = coords.NOSStage1Xpos[i] - minX;
	}
	for (int i = 0; i < numNOSItemsStage2; i++) {
		coords.NOSStage2Xpos[i] = coords.NOSStage2Xpos[i] - minX;
	}
	for (int i = 0; i < numNOSItemsStage3; i++) {
		coords.NOSStage3Xpos[i] = coords.NOSStage3Xpos[i] - minX;
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
	for (int i = 0; i < numNOSItemsStage1; i++) {
		coords.NOSStage1Ypos[i] = coords.NOSStage1Ypos[i] - minY;
	}
	for (int i = 0; i < numNOSItemsStage2; i++) {
		coords.NOSStage2Ypos[i] = coords.NOSStage2Ypos[i] - minY;
	}
	for (int i = 0; i < numNOSItemsStage3; i++) {
		coords.NOSStage3Ypos[i] = coords.NOSStage3Ypos[i] - minY;
	}
	
	// DRAG
	minX > coords.DragRPMBgXpos ? minX = coords.DragRPMBgXpos : minX = minX;
	minX > coords.DragLinesXpos ? minX = coords.DragLinesXpos : minX = minX;
	minX > coords.DragNosLinesXpos ? minX = coords.DragNosLinesXpos : minX = minX;
	minX > coords.DragHeatLinesXpos ? minX = coords.DragHeatLinesXpos : minX = minX;
	minX > coords.DragRPMDialXpos ? minX = coords.DragRPMDialXpos : minX = minX;
	minX > coords.DragRPMRedXpos ? minX = coords.DragRPMRedXpos : minX = minX;
	minX > coords.DragHeatAlertXpos ? minX = coords.DragHeatAlertXpos : minX = minX;
	minX > coords.DragShiftLightXpos ? minX = coords.DragShiftLightXpos : minX = minX;
	minX > coords.DragRPMBoxXpos ? minX = coords.DragRPMBoxXpos : minX = minX;
	minX > coords.DragSpeedBoxXpos ? minX = coords.DragSpeedBoxXpos : minX = minX;
	minX > coords.DragSpeedXpos ? minX = coords.DragSpeedXpos : minX = minX;
	minX > coords.DragUnitXpos ? minX = coords.DragUnitXpos : minX = minX;
	minX > coords.DragGearXpos ? minX = coords.DragGearXpos : minX = minX;
	for (int i = 0; i < numDragHeat; i++) {
		minX > coords.DragHeatXpos[i] ? minX = coords.DragHeatXpos[i] : minX = minX;
	}
	for (int i = 0; i < numNOSItemsStage1; i++) {
		minX > coords.DragNOSStage1Xpos[i] ? minX = coords.DragNOSStage1Xpos[i] : minX = minX;
	}
	for (int i = 0; i < numNOSItemsStage2; i++) {
		minX > coords.DragNOSStage2Xpos[i] ? minX = coords.DragNOSStage2Xpos[i] : minX = minX;
	}
	for (int i = 0; i < numNOSItemsStage3; i++) {
		minX > coords.DragNOSStage3Xpos[i] ? minX = coords.DragNOSStage3Xpos[i] : minX = minX;
	}
	minX > coords.DragTurboXpos ? minX = coords.DragTurboXpos : minX = minX;
	minX > coords.DragTurboDialXpos ? minX = coords.DragTurboDialXpos : minX = minX;
	minX > coords.DragTurboRed1Xpos ? minX = coords.DragTurboRed1Xpos : minX = minX;
	minX > coords.DragTurboRed2Xpos ? minX = coords.DragTurboRed2Xpos : minX = minX;


	minY > coords.DragRPMBgYpos ? minY = coords.DragRPMBgYpos : minY = minY;
	minY > coords.DragLinesYpos ? minY = coords.DragLinesYpos : minY = minY;
	minY > coords.DragNosLinesYpos ? minY = coords.DragNosLinesYpos : minY = minY;
	minY > coords.DragHeatLinesYpos ? minY = coords.DragHeatLinesYpos : minY = minY;
	minY > coords.DragRPMDialYpos ? minY = coords.DragRPMDialYpos : minY = minY;
	minY > coords.DragRPMRedYpos ? minY = coords.DragRPMRedYpos : minY = minY;
	minY > coords.DragHeatAlertYpos ? minX = coords.DragHeatAlertYpos : minY = minY;
	minY > coords.DragShiftLightYpos ? minX = coords.DragShiftLightYpos : minY = minY;
	minY > coords.DragRPMBoxYpos ? minY = coords.DragRPMBoxYpos : minY = minY;
	minY > coords.DragSpeedBoxYpos ? minY = coords.DragSpeedBoxYpos : minY = minY;
	minY > coords.DragSpeedYpos ? minY = coords.DragSpeedYpos : minY = minY;
	minY > coords.DragUnitYpos ? minY = coords.DragUnitYpos : minY = minY;
	minY > coords.DragGearYpos ? minY = coords.DragGearYpos : minY = minY;
	for (int i = 0; i < numDragHeat; i++) {
		minY > coords.DragHeatYpos[i] ? minY = coords.DragHeatYpos[i] : minY = minY;
	}
	for (int i = 0; i < numNOSItemsStage1; i++) {
		minY > coords.DragNOSStage1Ypos[i] ? minY = coords.DragNOSStage1Ypos[i] : minY = minY;
	}
	for (int i = 0; i < numNOSItemsStage2; i++) {
		minY > coords.DragNOSStage2Ypos[i] ? minY = coords.DragNOSStage2Ypos[i] : minY = minY;
	}
	for (int i = 0; i < numNOSItemsStage3; i++) {
		minY > coords.DragNOSStage3Ypos[i] ? minY = coords.DragNOSStage3Ypos[i] : minY = minY;
	}
	minY > coords.DragTurboYpos ? minY = coords.DragTurboYpos : minY = minY;
	minY > coords.DragTurboDialYpos ? minY = coords.DragTurboDialYpos : minY = minY;
	minY > coords.DragTurboRed1Ypos ? minY = coords.DragTurboRed1Ypos : minY = minY;
	minY > coords.DragTurboRed2Ypos ? minY = coords.DragTurboRed2Ypos : minY = minY;

	coords.DragRPMBgXpos = coords.DragRPMBgXpos - minX;
	coords.DragLinesXpos = coords.DragLinesXpos - minX;
	coords.DragNosLinesXpos = coords.DragNosLinesXpos - minX;
	coords.DragHeatLinesXpos = coords.DragHeatLinesXpos - minX;
	coords.DragRPMDialXpos = coords.DragRPMDialXpos - minX;
	coords.DragRPMRedXpos = coords.DragRPMRedXpos - minX;
	coords.DragHeatAlertXpos = coords.DragHeatAlertXpos - minX;
	coords.DragShiftLightXpos = coords.DragShiftLightXpos - minX;
	coords.DragRPMBoxXpos = coords.DragRPMBoxXpos - minX;
	coords.DragSpeedBoxXpos = coords.DragSpeedBoxXpos - minX;
	coords.DragSpeedXpos = coords.DragSpeedXpos - minX;
	coords.DragUnitXpos = coords.DragUnitXpos - minX;
	coords.DragGearXpos = coords.DragGearXpos - minX;
	for (int i = 0; i < numDragHeat; i++) {
		coords.DragHeatXpos[i] = coords.DragHeatXpos[i] - minX;
	}
	for (int i = 0; i < numNOSItemsStage1; i++) {
		coords.DragNOSStage1Xpos[i] = coords.DragNOSStage1Xpos[i] - minX;
	}
	for (int i = 0; i < numNOSItemsStage2; i++) {
		coords.DragNOSStage2Xpos[i] = coords.DragNOSStage2Xpos[i] - minX;
	}
	for (int i = 0; i < numNOSItemsStage3; i++) {
		coords.DragNOSStage3Xpos[i] = coords.DragNOSStage3Xpos[i] - minX;
	}
	coords.DragTurboXpos = coords.DragTurboXpos - minX;
	coords.DragTurboDialXpos = coords.DragTurboDialXpos - minX;
	coords.DragTurboRed1Xpos = coords.DragTurboRed1Xpos - minX;
	coords.DragTurboRed2Xpos = coords.DragTurboRed2Xpos - minX;

	coords.DragRPMBgYpos = coords.DragRPMBgYpos - minY;
	coords.DragLinesYpos = coords.DragLinesYpos - minY;
	coords.DragNosLinesYpos = coords.DragNosLinesYpos - minY;
	coords.DragHeatLinesYpos = coords.DragHeatLinesYpos - minY;
	coords.DragRPMDialYpos = coords.DragRPMDialYpos - minY;
	coords.DragRPMRedYpos = coords.DragRPMRedYpos - minY;
	coords.DragHeatAlertYpos = coords.DragHeatAlertYpos - minY;
	coords.DragShiftLightYpos = coords.DragShiftLightYpos - minY;
	coords.DragRPMBoxYpos = coords.DragRPMBoxYpos - minY;
	coords.DragSpeedBoxYpos = coords.DragSpeedBoxYpos - minY;
	coords.DragSpeedYpos = coords.DragSpeedYpos - minY;
	coords.DragUnitYpos = coords.DragUnitYpos - minY;
	coords.DragGearYpos = coords.DragGearYpos - minY;
	for (int i = 0; i < numDragHeat; i++) {
		coords.DragHeatYpos[i] = coords.DragHeatYpos[i] - minY;
	}
	for (int i = 0; i < numNOSItemsStage1; i++) {
		coords.DragNOSStage1Ypos[i] = coords.DragNOSStage1Ypos[i] - minY;
	}
	for (int i = 0; i < numNOSItemsStage2; i++) {
		coords.DragNOSStage2Ypos[i] = coords.DragNOSStage2Ypos[i] - minY;
	}
	for (int i = 0; i < numNOSItemsStage3; i++) {
		coords.DragNOSStage3Ypos[i] = coords.DragNOSStage3Ypos[i] - minY;
	}
	coords.DragTurboYpos = coords.DragTurboYpos - minY;
	coords.DragTurboDialYpos = coords.DragTurboDialYpos - minY;
	coords.DragTurboRed1Ypos = coords.DragTurboRed1Ypos - minY;
	coords.DragTurboRed2Ypos = coords.DragTurboRed2Ypos - minY;

	SaveGeneral();
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

	for (int i = 0; i < numNOSItemsStage1; i++) {
		SpeedoSettings.NOSStage1Xpos[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Stage1Xpos").c_str()));
		SpeedoSettings.NOSStage1Ypos[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Stage1Ypos").c_str()));
		SpeedoSettings.NOSStage1Size[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Stage1Size").c_str()));
	}

	for (int i = 0; i < numNOSItemsStage2; i++) {
		SpeedoSettings.NOSStage2Xpos[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Stage2Xpos").c_str()));
		SpeedoSettings.NOSStage2Ypos[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Stage2Ypos").c_str()));
		SpeedoSettings.NOSStage2Size[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Stage2Size").c_str()));
	}

	for (int i = 0; i < numNOSItemsStage3; i++) {
		SpeedoSettings.NOSStage3Xpos[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Stage3Xpos").c_str()));
		SpeedoSettings.NOSStage3Ypos[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Stage3Ypos").c_str()));
		SpeedoSettings.NOSStage3Size[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("NOS" + std::to_string(i) + "Stage3Size").c_str()));
	}
	
	// DRAG
	SpeedoSettings.DragRPMBgXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragRPMBgXpos"));
	SpeedoSettings.DragRPMBgYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragRPMBgYpos"));
	SpeedoSettings.DragRPMBgSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragRPMBgSize"));

	SpeedoSettings.DragLinesXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragLinesXpos"));
	SpeedoSettings.DragLinesYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragLinesYpos"));
	SpeedoSettings.DragLinesSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragLinesSize"));

	SpeedoSettings.DragNosLinesXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragNosLinesXpos"));
	SpeedoSettings.DragNosLinesYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragNosLinesYpos"));
	SpeedoSettings.DragNosLinesSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragNosLinesSize"));

	SpeedoSettings.DragHeatLinesXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragHeatLinesXpos"));
	SpeedoSettings.DragHeatLinesYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragHeatLinesYpos"));
	SpeedoSettings.DragHeatLinesSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragHeatLinesSize"));

	SpeedoSettings.DragRPMDialXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragRPMDialXpos"));
	SpeedoSettings.DragRPMDialYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragRPMDialYpos"));
	SpeedoSettings.DragRPMDialSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragRPMDialSize"));

	SpeedoSettings.DragRPMRedXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragRPMRedXpos"));
	SpeedoSettings.DragRPMRedYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragRPMRedYpos"));
	SpeedoSettings.DragRPMRedSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragRPMRedSize"));

	SpeedoSettings.DragHeatAlertXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragHeatAlertXpos"));
	SpeedoSettings.DragHeatAlertYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragHeatAlertYpos"));
	SpeedoSettings.DragHeatAlertSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragHeatAlertSize"));

	SpeedoSettings.DragShiftLightXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragShiftLightXpos"));
	SpeedoSettings.DragShiftLightYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragShiftLightYpos"));
	SpeedoSettings.DragShiftLightSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragShiftLightSize"));

	SpeedoSettings.DragRPMBoxXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragRPMBoxXpos"));
	SpeedoSettings.DragRPMBoxYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragRPMBoxYpos"));
	SpeedoSettings.DragRPMBoxSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragRPMBoxSize"));

	SpeedoSettings.DragSpeedBoxXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragSpeedBoxXpos"));
	SpeedoSettings.DragSpeedBoxYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragSpeedBoxYpos"));
	SpeedoSettings.DragSpeedBoxSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragSpeedBoxSize"));

	SpeedoSettings.DragSpeedXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragSpeedXpos"));
	SpeedoSettings.DragSpeedYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragSpeedYpos"));
	SpeedoSettings.DragSpeedSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragSpeedSize"));

	SpeedoSettings.DragUnitXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragUnitXpos"));
	SpeedoSettings.DragUnitYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragUnitYpos"));
	SpeedoSettings.DragUnitSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragUnitSize"));

	SpeedoSettings.DragGearXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragGearXpos"));
	SpeedoSettings.DragGearYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragGearYpos"));
	SpeedoSettings.DragGearSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragGearSize"));

	for (int i = 0; i < numDragHeat; i++) {
		SpeedoSettings.DragHeatXpos[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("DragHeat" + std::to_string(i) + "Xpos").c_str()));
		SpeedoSettings.DragHeatYpos[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("DragHeat" + std::to_string(i) + "Ypos").c_str()));
		SpeedoSettings.DragHeatSize[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("DragHeat" + std::to_string(i) + "Size").c_str()));
	}

	for (int i = 0; i < numNOSItemsStage1; i++) {
		SpeedoSettings.DragNOSStage1Xpos[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage1Xpos").c_str()));
		SpeedoSettings.DragNOSStage1Ypos[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage1Ypos").c_str()));
		SpeedoSettings.DragNOSStage1Size[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage1Size").c_str()));
	}

	for (int i = 0; i < numNOSItemsStage2; i++) {
		SpeedoSettings.DragNOSStage2Xpos[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage2Xpos").c_str()));
		SpeedoSettings.DragNOSStage2Ypos[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage2Ypos").c_str()));
		SpeedoSettings.DragNOSStage2Size[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage2Size").c_str()));
	}

	for (int i = 0; i < numNOSItemsStage3; i++) {
		SpeedoSettings.DragNOSStage3Xpos[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage3Xpos").c_str()));
		SpeedoSettings.DragNOSStage3Ypos[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage3Ypos").c_str()));
		SpeedoSettings.DragNOSStage3Size[i] = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", ("DragNOS" + std::to_string(i) + "Stage3Size").c_str()));
	}

	SpeedoSettings.DragTurboXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragTurboXpos"));
	SpeedoSettings.DragTurboYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragTurboYpos"));
	SpeedoSettings.DragTurboSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragTurboSize"));

	SpeedoSettings.DragTurboDialXpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragTurboDialXpos"));
	SpeedoSettings.DragTurboDialYpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragTurboDialYpos"));
	SpeedoSettings.DragTurboDialSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragTurboDialSize"));

	SpeedoSettings.DragTurboRed1Xpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragTurboRed1Xpos"));
	SpeedoSettings.DragTurboRed1Ypos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragTurboRed1Ypos"));
	SpeedoSettings.DragTurboRed2Xpos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragTurboRed2Xpos"));
	SpeedoSettings.DragTurboRed2Ypos = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragTurboRed2Ypos"));
	SpeedoSettings.DragTurboRedSize = static_cast<float>(settingsGeneral.GetDoubleValue("SPEEDO", "DragTurboRedSize"));
}
