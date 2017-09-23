#pragma once
#include <string>
#include <array>

const int numNOSItemsStage1 = 2;
const int numNOSItemsStage2 = 4;
const int numNOSItemsStage3 = 6;

const int numDragHeat = 8;

struct SpeedoInfo {
	std::string SpeedoName;

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

	std::array<float, numNOSItemsStage1> NOSStage1Xpos;
	std::array<float, numNOSItemsStage1> NOSStage1Ypos;
	std::array<float, numNOSItemsStage1> NOSStage1Size;

	std::array<float, numNOSItemsStage2> NOSStage2Xpos;
	std::array<float, numNOSItemsStage2> NOSStage2Ypos;
	std::array<float, numNOSItemsStage2> NOSStage2Size;

	std::array<float, numNOSItemsStage3> NOSStage3Xpos;
	std::array<float, numNOSItemsStage3> NOSStage3Ypos;
	std::array<float, numNOSItemsStage3> NOSStage3Size;
};

struct DragSpeedoInfo : SpeedoInfo {
	float DragHeatLinesXpos;
	float DragHeatLinesYpos;
	float DragHeatLinesSize;

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

	std::array<float, numDragHeat> DragHeatXpos;
	std::array<float, numDragHeat> DragHeatYpos;
	std::array<float, numDragHeat> DragHeatSize;
};
