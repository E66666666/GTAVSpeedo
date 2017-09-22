#pragma once
#include <string>
#include <array>

const int numNOSItemsStage1 = 2;
const int numNOSItemsStage2 = 4;
const int numNOSItemsStage3 = 6;

// DRAG
const int numDragHeat = 8;

struct SpeedoStuff {
	std::string SpeedoName;

	bool FPVHide;
	float FadeSpeed;

	float SpeedoXpos;
	float SpeedoYpos;
	float SpeedoSize;

	float RPMBgXpos;
	float RPMBgYpos;
	float RPMBgSize;

	float RPMNumXpos;
	float RPMNumYpos;
	float RPMNumSize;

	float RPMDialXpos;
	float RPMDialYpos;
	float RPMDialSize;

	float RPMRedXpos;
	float RPMRedYpos;
	float RPMRedSize;

	float TurboBgXpos;
	float TurboBgYpos;
	float TurboBgSize;

	float TurboNumXpos;
	float TurboNumYpos;
	float TurboNumSize;

	float TurboTextXpos;
	float TurboTextYpos;
	float TurboTextSize;

	float TurboDialXpos;
	float TurboDialYpos;
	float TurboDialSize;

	float TurboRed0Xpos;
	float TurboRed0Ypos;
	float TurboRed0Size;

	float TurboRed1Xpos;
	float TurboRed1Ypos;
	float TurboRed1Size;

	float SpeedXpos;
	float SpeedYpos;
	float SpeedSize;

	float UnitXpos;
	float UnitYpos;
	float UnitSize;

	float GearXpos;
	float GearYpos;
	float GearSize;

	float NOSTextXpos;
	float NOSTextYpos;
	float NOSTextSize;

	// TODO - Group them together and translate by size???
	std::array<float, numNOSItemsStage1> NOSStage1Xpos;
	std::array<float, numNOSItemsStage1> NOSStage1Ypos;
	std::array<float, numNOSItemsStage1> NOSStage1Size;

	std::array<float, numNOSItemsStage2> NOSStage2Xpos;
	std::array<float, numNOSItemsStage2> NOSStage2Ypos;
	std::array<float, numNOSItemsStage2> NOSStage2Size;

	std::array<float, numNOSItemsStage3> NOSStage3Xpos;
	std::array<float, numNOSItemsStage3> NOSStage3Ypos;
	std::array<float, numNOSItemsStage3> NOSStage3Size;
	
	// DRAG SPRITES
	float DragRPMBgXpos;
	float DragRPMBgYpos;
	float DragRPMBgSize;

	float DragLinesXpos;
	float DragLinesYpos;
	float DragLinesSize;

	float DragNosLinesXpos;
	float DragNosLinesYpos;
	float DragNosLinesSize;
	
	float DragHeatLinesXpos;
	float DragHeatLinesYpos;
	float DragHeatLinesSize;

	float DragRPMDialXpos;
	float DragRPMDialYpos;
	float DragRPMDialSize;

	float DragRPMRedXpos;
	float DragRPMRedYpos;
	float DragRPMRedSize;

	float DragHeatAlertXpos;
	float DragHeatAlertYpos;
	float DragHeatAlertSize;

	float DragShiftLightXpos;
	float DragShiftLightYpos;
	float DragShiftLightSize;
	
	float DragRPMBoxXpos;
	float DragRPMBoxYpos;
	float DragRPMBoxSize;

	float DragSpeedBoxXpos;
	float DragSpeedBoxYpos;
	float DragSpeedBoxSize;

	float DragSpeedXpos;
	float DragSpeedYpos;
	float DragSpeedSize;

	float DragUnitXpos;
	float DragUnitYpos;
	float DragUnitSize;

	float DragGearXpos;
	float DragGearYpos;
	float DragGearSize;

	float DragTurboXpos;
	float DragTurboYpos;
	float DragTurboSize;

	float DragTurboDialXpos;
	float DragTurboDialYpos;
	float DragTurboDialSize;

	float DragTurboRed1Xpos;
	float DragTurboRed1Ypos;
	float DragTurboRed2Xpos;
	float DragTurboRed2Ypos;
	float DragTurboRedSize;

	std::array<float, numDragHeat> DragHeatXpos;
	std::array<float, numDragHeat> DragHeatYpos;
	std::array<float, numDragHeat> DragHeatSize;

	std::array<float, numNOSItemsStage1> DragNOSStage1Xpos;
	std::array<float, numNOSItemsStage1> DragNOSStage1Ypos;
	std::array<float, numNOSItemsStage1> DragNOSStage1Size;

	std::array<float, numNOSItemsStage2> DragNOSStage2Xpos;
	std::array<float, numNOSItemsStage2> DragNOSStage2Ypos;
	std::array<float, numNOSItemsStage2> DragNOSStage2Size;

	std::array<float, numNOSItemsStage3> DragNOSStage3Xpos;
	std::array<float, numNOSItemsStage3> DragNOSStage3Ypos;
	std::array<float, numNOSItemsStage3> DragNOSStage3Size;
};

enum class UnitType {
	Metric = 0,
	Imperial = 1,
};

class ScriptSettings {
public:
	ScriptSettings();
	void SetFiles(const std::string &general);
	void Read();
	void SaveGeneral() const;
	void Normalize(SpeedoStuff &coords);
	bool Enable;
	SpeedoStuff SpeedoSettings;
	UnitType Unit;
	bool ShowPlacementMenu;
private:
	void parseSettingsGeneral();

	std::string settingsGeneralFile;
	std::string settingsMenuFile;
};
