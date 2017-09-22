#define NOMINMAX
#include "script.h"

#include <string>
#include <sstream>
#include <iomanip>

#include <lodepng/lodepng.h>
#include <menu.h>

#include "../../GTAVManualTransmission/Gears/Memory/NativeMemory.hpp"
#include "../../GTAVManualTransmission/Gears/Memory/VehicleExtensions.hpp"

#include "Util/Logger.hpp"
#include "Util/Util.hpp"
#include "Util/Paths.h"
#include "Util/MathExt.h"

#include "ScriptSettings.hpp"
#include "newNatives.h"
#include <chrono>
#include "../../GTAVManualTransmission/Gears/Memory/Versions.h"

const char* decoriktSpeedoActive    = "ikt_speedo_active";
const char* decorMTGear             = "mt_gear";
const char* decorMTNeutral          = "mt_neutral";
const char* decorMTShiftIndicator   = "mt_shift_indicator";
const char* decorMTGetShiftMode     = "mt_get_shiftmode";
const char* decorNOS                = "ikt_speedo_nos";
const char* decorNOSLevel           = "ikt_speedo_nos_level";
const char* decorNOSStage           = "nfsnitro_stage";
const char* decorDragHeat           = "nfsdrag_heat";
const char* decorDragShowHud        = "nfsdrag_showhud";

struct Colorf {
	float r;
	float g;
	float b;
	float a;
};

struct SpriteInfo {
	int Id;
	unsigned Width;
	unsigned Height;
};

enum eDecorType {
	DECOR_TYPE_FLOAT = 1,
	DECOR_TYPE_BOOL,
	DECOR_TYPE_INT,
	DECOR_TYPE_UNK,
	DECOR_TYPE_TIME
};

std::string settingsGeneralFile;
std::string settingsMenuFile;
std::string skinDir;

SpriteInfo spriteRPMBg;
SpriteInfo spriteRPMNum;
SpriteInfo spriteRPMDial;
SpriteInfo spriteRPMRed;

SpriteInfo spriteTurboBg;
SpriteInfo spriteTurboText;
SpriteInfo spriteTurboNum;
SpriteInfo spriteTurboDial;
SpriteInfo spriteTurboRed0;
SpriteInfo spriteTurboRed1;

SpriteInfo spriteN0;
SpriteInfo spriteN1;
SpriteInfo spriteN2;
SpriteInfo spriteN3;
SpriteInfo spriteN4;
SpriteInfo spriteN5;
SpriteInfo spriteN6;
SpriteInfo spriteN7;
SpriteInfo spriteN8;
SpriteInfo spriteN9;
SpriteInfo spriteNN;
SpriteInfo spriteNR;
SpriteInfo spriteNE;

SpriteInfo spriteKMH;
SpriteInfo spriteMPH;

SpriteInfo spriteNOSText;
std::vector<SpriteInfo> spritesNOSStage1;
std::vector<SpriteInfo> spritesNOSStage2;
std::vector<SpriteInfo> spritesNOSStage3;

// DRAG
SpriteInfo spriteDragRPMBg;
SpriteInfo spriteDragLines;
SpriteInfo spriteDragNosLines;
SpriteInfo spriteDragHeatLines;
SpriteInfo spriteDragRPMDial;
SpriteInfo spriteDragRPMRed;
SpriteInfo spriteDragHeatAlert;
SpriteInfo spriteDragShiftLight;
SpriteInfo spriteDragRPMBox;
SpriteInfo spriteDragSpeedBox;
SpriteInfo spriteDragTurboBack;
SpriteInfo spriteDragTurboMeter;
SpriteInfo spriteDragTurboDial;
SpriteInfo spriteDragTurboRed1;
SpriteInfo spriteDragTurboRed2;
std::vector<SpriteInfo> spritesDragHeat;
std::vector<SpriteInfo> spritesDragNOSStage1;
std::vector<SpriteInfo> spritesDragNOSStage2;
std::vector<SpriteInfo> spritesDragNOSStage3;

float displayRPM = 0.0f;

NativeMenu::Menu menu;
ScriptSettings settings;

Player player;
Ped playerPed;
Vehicle vehicle;
Vehicle prevVehicle;
VehicleExtensions ext;
bool hasDashSpeedo = false;

int prevNotification = 0;

float speedoAlpha = 0.0f;
float turboalpha = 0.0f;

std::chrono::steady_clock::duration previousDisplayTime;

enum class ShiftMode {
	Default,
	Sequential,
	HPattern, 
	Automatic,
};

void drawNOSBars(bool hasBoost, float boostVal, float nosVal, float screencorrection, float offsetX, float offsetY) {
	float maxVal;
	float val;
	if (hasBoost) {
		maxVal = 1.25f;
		val = boostVal;
	}
	else {
		maxVal = 1.0f;
		val = nosVal;
	}

	float baseAlpha = 1.0f;
	drawTexture(spriteNOSText.Id, 0, -9998, 100,
		settings.SpeedoSettings.NOSTextSize, static_cast<float>(spriteNOSText.Height) * (settings.SpeedoSettings.NOSTextSize / static_cast<float>(spriteNOSText.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.NOSTextXpos + offsetX, settings.SpeedoSettings.NOSTextYpos + offsetY,
		0.0f, screencorrection, 1.0f, 1.0f, 1.0f, 1.0f * speedoAlpha);


	int numNOSItems;
	int nosStage = 3;

	bool isStageUsed = DECORATOR::DECOR_IS_REGISTERED_AS_TYPE((char*)decorNOSStage, DECOR_TYPE_INT);
	if (isStageUsed) {
		nosStage = DECORATOR::DECOR_GET_INT(vehicle, (char*)decorNOSStage);
	}
	
	std::vector<SpriteInfo> nosSprites;
	std::vector<float> nosBarSize;
	std::vector<float> nosBarXpos;
	std::vector<float> nosBarYpos;

	switch (nosStage) {
	case 1: {
		numNOSItems = numNOSItemsStage1;
		nosSprites = spritesNOSStage1;
		std::copy_n(nosBarSize.begin(), numNOSItems, settings.SpeedoSettings.NOSStage1Size.begin());
		std::copy_n(nosBarXpos.begin(), numNOSItems, settings.SpeedoSettings.NOSStage1Xpos.begin());
		std::copy_n(nosBarYpos.begin(), numNOSItems, settings.SpeedoSettings.NOSStage1Ypos.begin());
		break;
	}
	case 2: {
		numNOSItems = numNOSItemsStage2;
		nosSprites = spritesNOSStage2;
		std::copy_n(nosBarSize.begin(), numNOSItems, settings.SpeedoSettings.NOSStage2Size.begin());
		std::copy_n(nosBarXpos.begin(), numNOSItems, settings.SpeedoSettings.NOSStage2Xpos.begin());
		std::copy_n(nosBarYpos.begin(), numNOSItems, settings.SpeedoSettings.NOSStage2Ypos.begin());
		break;
	}
	default:
	case 3: {
		numNOSItems = numNOSItemsStage3;
		nosSprites = spritesNOSStage3;
		std::copy_n(nosBarSize.begin(), numNOSItems, settings.SpeedoSettings.NOSStage3Size.begin());
		std::copy_n(nosBarXpos.begin(), numNOSItems, settings.SpeedoSettings.NOSStage3Xpos.begin());
		std::copy_n(nosBarYpos.begin(), numNOSItems, settings.SpeedoSettings.NOSStage3Ypos.begin());
		break;
	}
	}

	float portion = maxVal / numNOSItems;
	int i = 0;
	for (auto sprite : nosSprites) {
		float min = maxVal - portion * (i + 1);

		float res = (val - min) / portion;
		if (res > 1.0f) res = 1.0f;
		if (res < 0.0f) res = 0.0f;

		drawTexture(sprite.Id, i, -9998, 100,
			nosBarSize[i], static_cast<float>(sprite.Height) * (nosBarSize[i] / static_cast<float>(sprite.Width)),
			0.5f, 0.5f,
			nosBarXpos[i] + offsetX, nosBarYpos[i] + offsetY,
			0.0f, screencorrection, 0.0f, 1.0f, 0.0f, baseAlpha * res * speedoAlpha);
		i++;
	}
}

void drawDragNOSBars(bool hasBoost, float boostVal, float nosVal, float screencorrection, float offsetX, float offsetY) {
	float maxVal;
	float val;
	if (hasBoost) {
		maxVal = 1.25f;
		val = boostVal;
	}
	else {
		maxVal = 1.0f;
		val = nosVal;
	}

	float baseAlpha = 1.0f;

	int numNOSItems;
	int nosStage = 3;

	bool isStageUsed = DECORATOR::DECOR_IS_REGISTERED_AS_TYPE((char*)decorNOSStage, DECOR_TYPE_INT);
	if (isStageUsed) {
		nosStage = DECORATOR::DECOR_GET_INT(vehicle, (char*)decorNOSStage);
	}

	std::vector<SpriteInfo> nosSprites;
	std::vector<float> nosBarSize;
	std::vector<float> nosBarXpos;
	std::vector<float> nosBarYpos;

	switch (nosStage) {
	case 1: {
		numNOSItems = numNOSItemsStage1;
		nosSprites = spritesDragNOSStage1;
		std::copy_n(nosBarSize.begin(), numNOSItems, settings.SpeedoSettings.DragNOSStage1Size.begin());
		std::copy_n(nosBarXpos.begin(), numNOSItems, settings.SpeedoSettings.DragNOSStage1Xpos.begin());
		std::copy_n(nosBarYpos.begin(), numNOSItems, settings.SpeedoSettings.DragNOSStage1Ypos.begin());
		break;
	}
	case 2: {
		numNOSItems = numNOSItemsStage2;
		nosSprites = spritesDragNOSStage2;
		std::copy_n(nosBarSize.begin(), numNOSItems, settings.SpeedoSettings.DragNOSStage2Size.begin());
		std::copy_n(nosBarXpos.begin(), numNOSItems, settings.SpeedoSettings.DragNOSStage2Xpos.begin());
		std::copy_n(nosBarYpos.begin(), numNOSItems, settings.SpeedoSettings.DragNOSStage2Ypos.begin());
		break;
	}
	default:
	case 3: {
		numNOSItems = numNOSItemsStage3;
		nosSprites = spritesDragNOSStage3;
		std::copy_n(nosBarSize.begin(), numNOSItems, settings.SpeedoSettings.DragNOSStage3Size.begin());
		std::copy_n(nosBarXpos.begin(), numNOSItems, settings.SpeedoSettings.DragNOSStage3Xpos.begin());
		std::copy_n(nosBarYpos.begin(), numNOSItems, settings.SpeedoSettings.DragNOSStage3Ypos.begin());
		break;
	}
	}

	float portion = maxVal / numNOSItems;
	int i = 0;
	for (auto sprite : nosSprites) {
		float min = maxVal - portion * (i + 1);

		float res = (val - min) / portion;
		if (res > 1.0f) res = 1.0f;
		if (res < 0.0f) res = 0.0f;

		drawTexture(sprite.Id, i, -9998, 100,
			nosBarSize[i], static_cast<float>(sprite.Height) * (nosBarSize[i] / static_cast<float>(sprite.Width)),
			0.5f, 0.5f,
			nosBarXpos[i] + offsetX, nosBarYpos[i] + offsetY,
			0.0f, screencorrection, 0.0f, 1.0f, 0.0f, baseAlpha * res * speedoAlpha);
		i++;
	}
}

void drawDragEngineHeating(float heatVal, float screencorrection, float offsetX, float offsetY) {
	float maxVal = 1.0f;
	float val = heatVal;

	float baseAlpha = 1.0f;

	int i = 0;
	float portion = maxVal / numDragHeat;
	for (auto sprite : spritesDragHeat) {
		float min = maxVal - portion * (i + 1);

		float res = (val - min) / portion;
		if (res > 1.0f) res = 1.0f;
		if (res < 0.0f) res = 0.0f;

		float finalAlpha;
		if (res < 1.0f) finalAlpha = 0.0f;
		if (res == 1.0f) finalAlpha = 1.0f;

		drawTexture(sprite.Id, i, -9998, 100,
			settings.SpeedoSettings.DragHeatSize[i], static_cast<float>(sprite.Height) * (settings.SpeedoSettings.DragHeatSize[i] / static_cast<float>(sprite.Width)),
			0.5f, 0.5f,
			settings.SpeedoSettings.DragHeatXpos[i] + offsetX, settings.SpeedoSettings.DragHeatYpos[i] + offsetY,
			0.0f, screencorrection, 1.0f, 1.0f, 0.0f, finalAlpha * speedoAlpha);
		i++;
	}
}

void drawRPM(float rpm, float screencorrection, float offsetX, float offsetY) {
	displayRPM = lerp(displayRPM, rpm, 15.0f * GAMEPLAY::GET_FRAME_TIME());
	float rpmRot = displayRPM / 2.0f + 0.125f;

	drawTexture(spriteRPMBg.Id, 0, -9999, 100, 
	            settings.SpeedoSettings.RPMBgSize, static_cast<float>(spriteRPMBg.Height) * (settings.SpeedoSettings.RPMBgSize / static_cast<float>(spriteRPMBg.Width)),
	            0.5f, 0.5f, 
	            settings.SpeedoSettings.RPMBgXpos + offsetX, settings.SpeedoSettings.RPMBgYpos + offsetY,
	            0.0f, screencorrection, 1.0f, 1.0f, 1.0f, 0.75f * speedoAlpha);
	drawTexture(spriteRPMNum.Id, 0, -9998, 100,
	            settings.SpeedoSettings.RPMNumSize, static_cast<float>(spriteRPMNum.Height) * (settings.SpeedoSettings.RPMNumSize / static_cast<float>(spriteRPMNum.Width)),
	            0.5f, 0.5f,
	            settings.SpeedoSettings.RPMNumXpos + offsetX, settings.SpeedoSettings.RPMNumYpos + offsetY,
	            0.0f, screencorrection, 80.0f / 255.0f, 175.0f / 255.0f, 255.0f / 255.0f, 1.0f * speedoAlpha);
	drawTexture(spriteRPMDial.Id, 0, -9990, 100, 
	            settings.SpeedoSettings.RPMDialSize, static_cast<float>(spriteRPMDial.Height) * (settings.SpeedoSettings.RPMDialSize / static_cast<float>(spriteRPMDial.Width)),
	            0.5f, 0.5f,
	            settings.SpeedoSettings.RPMDialXpos + offsetX, settings.SpeedoSettings.RPMDialYpos + offsetY,
	            rpmRot, screencorrection, 1.0f, 1.0f, 1.0f, 0.9f * speedoAlpha);
	drawTexture(spriteRPMRed.Id, 0, -9997, 100,
	            settings.SpeedoSettings.RPMRedSize, static_cast<float>(spriteRPMRed.Height) * (settings.SpeedoSettings.RPMRedSize / static_cast<float>(spriteRPMRed.Width)),
	            0.5f, 0.5f,
	            settings.SpeedoSettings.RPMRedXpos + offsetX, settings.SpeedoSettings.RPMRedYpos + offsetY,
	            0.0f, screencorrection, 1.0f, 0.0f, 0.0f, 0.6f* speedoAlpha);
}

void drawDragHeatAlert(float screencorrection, float offsetX, float offsetY) {
	drawTexture(spriteDragHeatAlert.Id, 0, -9999, 100,
		settings.SpeedoSettings.DragHeatAlertSize, static_cast<float>(spriteDragHeatAlert.Height) * (settings.SpeedoSettings.DragHeatAlertSize / static_cast<float>(spriteDragHeatAlert.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragHeatAlertXpos + offsetX, settings.SpeedoSettings.DragHeatAlertYpos + offsetY,
		0.0f, screencorrection, 0.6f, 0.0f, 0.0f, 0.75f * speedoAlpha);
}

void drawDragShiftLight(float rpm, float screencorrection, float offsetX, float offsetY) {
	float baseR = 1.0f;
	float baseG = 1.0f;
	float baseB = 1.0f;
	float baseAlpha = 0.0f;

	if (rpm < 0.65f) {
		baseAlpha = 0.0f;
	}
	else if (rpm >= 0.65f && rpm < 0.73f) {
		baseR = 0.26f;
		baseG = 0.52f;
		baseB = 0.96f;
		baseAlpha = 1.0f;
	}
	else if (rpm >= 0.73f && rpm < 0.85f) {
		baseR = 0.0f;
		baseG = 1.0f;
		baseB = 0.0f;
		baseAlpha = 1.0f;
	}
	else if (rpm >= 0.85f) {
		baseR = 0.8f;
		baseG = 0.0f;
		baseB = 0.0f;
		baseAlpha = 1.0f;
	}

	drawTexture(spriteDragShiftLight.Id, 0, -9999, 100,
		settings.SpeedoSettings.DragShiftLightSize, static_cast<float>(spriteDragShiftLight.Height) * (settings.SpeedoSettings.DragShiftLightSize / static_cast<float>(spriteDragShiftLight.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragShiftLightXpos + offsetX, settings.SpeedoSettings.DragShiftLightYpos + offsetY,
		0.0f, screencorrection, baseR, baseG, baseB, baseAlpha * speedoAlpha);
}

void drawDragHUD(float rpm, float screencorrection, float offsetX, float offsetY) {
	displayRPM = lerp(displayRPM, rpm, 15.0f * GAMEPLAY::GET_FRAME_TIME());
	float rpmRot = displayRPM / 3.3f + 0.070f;
	// Short shift: 1.0f, 1.0f, 1.0f
	// Good shift: 0.26f, 0.52f, 0.96f
	// Perfect shift: 0.0f, 1.0f, 0.0f
	// Overrev shift: 1.0f, 0.0f, 0.0f

	float dialR = 1.0f;
	float dialG = 1.0f;
	float dialB = 1.0f;

	if (displayRPM < 0.65f) {
		dialR = 1.0f;
		dialG = 1.0f;
		dialB = 1.0f;
	}
	else if (displayRPM >= 0.65f && displayRPM < 0.73f) {
		dialR = 0.26f;
		dialG = 0.52f;
		dialB = 0.96f;
	}
	else if (displayRPM >= 0.73f && displayRPM < 0.85f) {
		dialR = 0.0f;
		dialG = 1.0f;
		dialB = 0.0f;
	}
	else if (displayRPM >= 0.85f) {
		dialR = 0.8f;
		dialG = 0.0f;
		dialB = 0.0f;
	}

	drawTexture(spriteDragRPMBg.Id, 0, -9999, 100,
		settings.SpeedoSettings.DragRPMBgSize, static_cast<float>(spriteDragRPMBg.Height) * (settings.SpeedoSettings.DragRPMBgSize / static_cast<float>(spriteDragRPMBg.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragRPMBgXpos + offsetX, settings.SpeedoSettings.DragRPMBgYpos + offsetY,
		0.0f, screencorrection, 1.0f, 1.0f, 1.0f, 0.75f * speedoAlpha);
	drawTexture(spriteDragLines.Id, 0, -9998, 100,
		settings.SpeedoSettings.DragLinesSize, static_cast<float>(spriteDragLines.Height) * (settings.SpeedoSettings.DragLinesSize / static_cast<float>(spriteDragLines.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragLinesXpos + offsetX, settings.SpeedoSettings.DragLinesYpos + offsetY,
		0.0f, screencorrection, 80.0f / 255.0f, 175.0f / 255.0f, 255.0f / 255.0f, 1.0f * speedoAlpha);
	drawTexture(spriteDragNosLines.Id, 0, -9998, 100,
		settings.SpeedoSettings.DragNosLinesSize, static_cast<float>(spriteDragNosLines.Height) * (settings.SpeedoSettings.DragNosLinesSize / static_cast<float>(spriteDragNosLines.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragNosLinesXpos + offsetX, settings.SpeedoSettings.DragNosLinesYpos + offsetY,
		0.0f, screencorrection, 80.0f / 255.0f, 175.0f / 255.0f, 255.0f / 255.0f, 1.0f * speedoAlpha);
	drawTexture(spriteDragHeatLines.Id, 0, -9998, 100,
		settings.SpeedoSettings.DragHeatLinesSize, static_cast<float>(spriteDragHeatLines.Height) * (settings.SpeedoSettings.DragHeatLinesSize / static_cast<float>(spriteDragHeatLines.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragHeatLinesXpos + offsetX, settings.SpeedoSettings.DragHeatLinesYpos + offsetY,
		0.0f, screencorrection, 80.0f / 255.0f, 175.0f / 255.0f, 255.0f / 255.0f, 1.0f * speedoAlpha);
	drawTexture(spriteDragRPMDial.Id, 0, -9990, 100,
		settings.SpeedoSettings.DragRPMDialSize, static_cast<float>(spriteDragRPMDial.Height) * (settings.SpeedoSettings.DragRPMDialSize / static_cast<float>(spriteDragRPMDial.Width)),
		0.5f, -0.5f,
		settings.SpeedoSettings.DragRPMDialXpos + offsetX, settings.SpeedoSettings.DragRPMDialYpos + offsetY,
		rpmRot, screencorrection, dialR, dialG, dialB, 0.9f * speedoAlpha);
	drawTexture(spriteDragRPMRed.Id, 0, -9991, 100,
		settings.SpeedoSettings.DragRPMRedSize, static_cast<float>(spriteDragRPMRed.Height) * (settings.SpeedoSettings.DragRPMRedSize / static_cast<float>(spriteDragRPMRed.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragRPMRedXpos + offsetX, settings.SpeedoSettings.DragRPMRedYpos + offsetY,
		0.0f, screencorrection, 0.8f, 0.0f, 0.0f, 1.0f * speedoAlpha);
	drawTexture(spriteDragRPMBox.Id, 0, -9990, 100,
		settings.SpeedoSettings.DragRPMBoxSize, static_cast<float>(spriteDragRPMBox.Height) * (settings.SpeedoSettings.DragRPMBoxSize / static_cast<float>(spriteDragRPMBox.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragRPMBoxXpos + offsetX, settings.SpeedoSettings.DragRPMBoxYpos + offsetY,
		0.0f, screencorrection, 0.0f, 0.0f, 0.0f, 0.3f * speedoAlpha);
	drawTexture(spriteDragSpeedBox.Id, 0, -9990, 100,
		settings.SpeedoSettings.DragSpeedBoxSize, static_cast<float>(spriteDragRPMBox.Height) * (settings.SpeedoSettings.DragSpeedBoxSize / static_cast<float>(spriteDragRPMBox.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragSpeedBoxXpos + offsetX, settings.SpeedoSettings.DragSpeedBoxYpos + offsetY,
		0.0f, screencorrection, 0.0f, 0.0f, 0.0f, 0.3f * speedoAlpha);
}

void drawDragSpeedUnit(UnitType type, float &speed, float screencorrection, float offsetX, float offsetY) {
	SpriteInfo spriteUnit;
	if (type == UnitType::Imperial) {
		speed = speed / 0.44704f;
		spriteUnit = spriteMPH;
	}
	else {
		speed = speed * 3.6f;
		spriteUnit = spriteKMH;
	}
	drawTexture(spriteUnit.Id, 0, -9980, 100,
		settings.SpeedoSettings.DragUnitSize, static_cast<float>(spriteUnit.Height) * (settings.SpeedoSettings.DragUnitSize / static_cast<float>(spriteUnit.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragUnitXpos + offsetX, settings.SpeedoSettings.DragUnitYpos + offsetY,
		0.0f, screencorrection, 0.54f, 0.69f, 0.93f, 1.0f* speedoAlpha);
}

void drawDragSpeed(float speed, int &charNum, float screencorrection, float offsetX, float offsetY, long long displayTime) {
	std::stringstream speedoFormat;
	speedoFormat << std::setfill('_') << std::setw(3) << std::to_string(static_cast<int>(std::round(speed)));
	std::string speedoTxt = speedoFormat.str();

	charNum = 0;
	for (char c : speedoTxt) {
		SpriteInfo si;
		switch (c) {
		case '0': si = spriteN0; break;
		case '1': si = spriteN1; break;
		case '2': si = spriteN2; break;
		case '3': si = spriteN3; break;
		case '4': si = spriteN4; break;
		case '5': si = spriteN5; break;
		case '6': si = spriteN6; break;
		case '7': si = spriteN7; break;
		case '8': si = spriteN8; break;
		case '9': si = spriteN9; break;
		default: si = spriteNE; break;
		}

		drawTexture(si.Id, charNum, -9980, (int)displayTime,
			settings.SpeedoSettings.DragSpeedSize, static_cast<float>(si.Height) * (settings.SpeedoSettings.DragSpeedSize / static_cast<float>(si.Width)),
			0.5f, 0.5f,
			settings.SpeedoSettings.DragSpeedXpos + offsetX + settings.SpeedoSettings.DragSpeedSize * charNum, settings.SpeedoSettings.DragSpeedYpos + offsetY,
			0.0f, screencorrection, 0.0f, 0.5f, 0.74f, 1.0f * speedoAlpha);
		charNum++;
	}
}

void drawDragGear(int gear, bool neutral, bool shift_indicator, int charNum, float screencorrection, float offsetX, float offsetY, long long displayTime) {
	SpriteInfo spriteGear;
	Colorf c = { 0.0f, 0.5f, 0.74f, 1.0f };

	if (neutral) spriteGear = spriteNN;
	else if (gear == 0) spriteGear = spriteNR;
	else if (gear == 1) spriteGear = spriteN1;
	else if (gear == 2) spriteGear = spriteN2;
	else if (gear == 3) spriteGear = spriteN3;
	else if (gear == 4) spriteGear = spriteN4;
	else if (gear == 5) spriteGear = spriteN5;
	else if (gear == 6) spriteGear = spriteN6;
	else if (gear == 7) spriteGear = spriteN7;
	else spriteGear = spriteN9;

	if (neutral || shift_indicator || ext.GetHandbrake(vehicle)) {
		c.r = 0.99f;
		c.g = 0.5f;
		c.b = 0.25f;
	}

	drawTexture(spriteGear.Id, charNum, -9980, (int)displayTime,
		settings.SpeedoSettings.DragGearSize, static_cast<float>(spriteGear.Height) * (settings.SpeedoSettings.DragGearSize / static_cast<float>(spriteGear.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragGearXpos + offsetX, settings.SpeedoSettings.DragGearYpos + offsetY,
		0.0f, screencorrection, c.r, c.g, c.b, c.a * speedoAlpha);
}

void drawDragTurbo(float turbo, float screencorrection, float offsetX, float offsetY) {
	float displayTurboRot;
	if (turbo < -0.5f) {
		displayTurboRot = map(turbo, -1.0f, -0.5f, -1.0f, 0.25f);
	}
	else if (turbo <= 0.9f) {
		displayTurboRot = map(turbo, -0.5f, 0.9f, 0.25f, 0.75f);
	}
	else {
		displayTurboRot = map(turbo, 0.9f, 1.0f, 0.75f, 1.0f);
	}

	float turboRot = displayTurboRot / 4.8f - 0.04f;

	drawTexture(spriteDragTurboBack.Id, 0, -9999, 100,
		settings.SpeedoSettings.DragTurboSize, static_cast<float>(spriteDragTurboBack.Height) * (settings.SpeedoSettings.DragTurboSize / static_cast<float>(spriteDragTurboBack.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragTurboXpos + offsetX, settings.SpeedoSettings.DragTurboYpos + offsetY,
		0.0f, screencorrection, 0.0f, 0.0f, 0.0f, 0.75f * turboalpha * speedoAlpha);
	drawTexture(spriteDragTurboMeter.Id, 0, -9998, 100,
		settings.SpeedoSettings.DragTurboSize, static_cast<float>(spriteDragTurboMeter.Height) * (settings.SpeedoSettings.DragTurboSize / static_cast<float>(spriteDragTurboMeter.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragTurboXpos + offsetX, settings.SpeedoSettings.DragTurboYpos + offsetY,
		0.0f, screencorrection, 80.0f / 255.0f, 175.0f / 255.0f, 255.0f / 255.0f, 0.75f * turboalpha * speedoAlpha);
	drawTexture(spriteDragTurboDial.Id, 0, -9990, 100,
		settings.SpeedoSettings.DragTurboDialSize, static_cast<float>(spriteDragTurboDial.Height) * (settings.SpeedoSettings.DragTurboDialSize / static_cast<float>(spriteDragTurboDial.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragTurboDialXpos + offsetX, settings.SpeedoSettings.DragTurboDialYpos + offsetY,
		turboRot, screencorrection, 1.0f, 1.0f, 1.0f, 0.9f * turboalpha * speedoAlpha);
	drawTexture(spriteDragTurboRed1.Id, 0, -9990, 100,
		settings.SpeedoSettings.DragTurboRedSize, static_cast<float>(spriteDragTurboRed1.Height) * (settings.SpeedoSettings.DragTurboRedSize / static_cast<float>(spriteDragTurboRed1.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragTurboRed1Xpos + offsetX, settings.SpeedoSettings.DragTurboRed1Ypos + offsetY,
		0.0f, screencorrection, 1.0f, 1.0f, 1.0f, 0.9f * turboalpha * speedoAlpha);
	drawTexture(spriteDragTurboRed2.Id, 0, -9990, 100,
		settings.SpeedoSettings.DragTurboRedSize, static_cast<float>(spriteDragTurboRed2.Height) * (settings.SpeedoSettings.DragTurboRedSize / static_cast<float>(spriteDragTurboRed2.Width)),
		0.5f, 0.5f,
		settings.SpeedoSettings.DragTurboRed2Xpos + offsetX, settings.SpeedoSettings.DragTurboRed2Ypos + offsetY,
		0.0f, screencorrection, 1.0f, 1.0f, 1.0f, 0.9f * turboalpha * speedoAlpha);
}

void drawTurbo(float turbo, float screencorrection, float offsetX, float offsetY) {
	float displayTurboRot;
	if (turbo < -0.5f) {
		displayTurboRot = map(turbo, -1.0f, -0.5f, -1.0f, 0.25f);
	}
	else if (turbo <= 0.9f) {
		displayTurboRot = map(turbo, -0.5f, 0.9f, 0.25f, 0.75f);
	}
	else {
		displayTurboRot = map(turbo, 0.9f, 1.0f, 0.75f, 1.0f);
	}

	float turboRot = displayTurboRot / 4.0f + 0.320f;

	drawTexture(spriteTurboBg.Id, 0, -9999, 100,
	            settings.SpeedoSettings.TurboBgSize, static_cast<float>(spriteTurboBg.Height) * (settings.SpeedoSettings.TurboBgSize / static_cast<float>(spriteTurboBg.Width)),
	            0.5f, 0.5f,
	            settings.SpeedoSettings.TurboBgXpos + offsetX, settings.SpeedoSettings.TurboBgYpos + offsetY,
	            0.0f, screencorrection, 1.0f, 1.0f, 1.0f, 0.75f*turboalpha * speedoAlpha);
	drawTexture(spriteTurboNum.Id, 0, -9998, 100,
	            settings.SpeedoSettings.TurboNumSize, static_cast<float>(spriteTurboNum.Height) * (settings.SpeedoSettings.TurboNumSize / static_cast<float>(spriteTurboNum.Width)),
	            0.5f, 0.5f,
	            settings.SpeedoSettings.TurboNumXpos + offsetX, settings.SpeedoSettings.TurboNumYpos + offsetY,
	            0.0f, screencorrection, 80.0f / 255.0f, 175.0f / 255.0f, 255.0f / 255.0f, 1.0f * turboalpha* speedoAlpha);
	drawTexture(spriteTurboDial.Id, 0, -9990, 100,
	            settings.SpeedoSettings.TurboDialSize, static_cast<float>(spriteTurboDial.Height) * (settings.SpeedoSettings.TurboDialSize / static_cast<float>(spriteTurboDial.Width)),
	            0.5f, 0.5f,
	            settings.SpeedoSettings.TurboDialXpos + offsetX, settings.SpeedoSettings.TurboDialYpos + offsetY,
	            turboRot, screencorrection, 1.0f, 1.0f, 1.0f, 0.9f * turboalpha* speedoAlpha);

	drawTexture(spriteTurboText.Id, 0, -9990, 100,
	            settings.SpeedoSettings.TurboTextSize, static_cast<float>(spriteTurboText.Height) * (settings.SpeedoSettings.TurboTextSize / static_cast<float>(spriteTurboText.Width)),
	            0.5f, 0.5f,
	            settings.SpeedoSettings.TurboTextXpos + offsetX, settings.SpeedoSettings.TurboTextYpos + offsetY,
	            0.0f, screencorrection, 0.54f, 0.69f, 0.93f, 1.0f*turboalpha* speedoAlpha);
	drawTexture(spriteTurboRed0.Id, 0, -9997, 100,
	            settings.SpeedoSettings.TurboRed0Size, static_cast<float>(spriteTurboRed0.Height) * (settings.SpeedoSettings.TurboRed0Size / static_cast<float>(spriteTurboRed0.Width)),
	            0.5f, 0.5f,
	            settings.SpeedoSettings.TurboRed0Xpos + offsetX, settings.SpeedoSettings.TurboRed0Ypos + offsetY,
	            0.0f, screencorrection, 1.0f, 0.0f, 0.0f, 0.6f*turboalpha* speedoAlpha);
	drawTexture(spriteTurboRed1.Id, 0, -9997, 100,
	            settings.SpeedoSettings.TurboRed1Size, static_cast<float>(spriteTurboRed1.Height) * (settings.SpeedoSettings.TurboRed1Size / static_cast<float>(spriteTurboRed1.Width)),
	            0.5f, 0.5f,
	            settings.SpeedoSettings.TurboRed1Xpos + offsetX, settings.SpeedoSettings.TurboRed1Ypos + offsetY,
	            0.0f, screencorrection, 1.0f, 0.0f, 0.0f, 0.6f*turboalpha* speedoAlpha);
}

void drawSpeedUnit(UnitType type, float &speed, float screencorrection, float offsetX, float offsetY) {
	SpriteInfo spriteUnit;
	if (type == UnitType::Imperial) {
		speed = speed / 0.44704f;
		spriteUnit = spriteMPH;
	}
	else {
		speed = speed * 3.6f;
		spriteUnit = spriteKMH;
	}
	drawTexture(spriteUnit.Id, 0, -9990, 100,
	            settings.SpeedoSettings.UnitSize, static_cast<float>(spriteUnit.Height) * (settings.SpeedoSettings.UnitSize / static_cast<float>(spriteUnit.Width)),
	            0.5f, 0.5f,
	            settings.SpeedoSettings.UnitXpos + offsetX, settings.SpeedoSettings.UnitYpos + offsetY,
	            0.0f, screencorrection, 0.54f, 0.69f, 0.93f, 1.0f* speedoAlpha);
}

void drawSpeed(float speed, int &charNum, float screencorrection, float offsetX, float offsetY, long long displayTime) {
	std::stringstream speedoFormat;
	speedoFormat << std::setfill('_') << std::setw(3) << std::to_string(static_cast<int>(std::round(speed)));
	std::string speedoTxt = speedoFormat.str();

	charNum = 0;
	for (char c : speedoTxt) {
		SpriteInfo si;
		switch (c) {
			case '0': si = spriteN0; break;
			case '1': si = spriteN1; break;
			case '2': si = spriteN2; break;
			case '3': si = spriteN3; break;
			case '4': si = spriteN4; break;
			case '5': si = spriteN5; break;
			case '6': si = spriteN6; break;
			case '7': si = spriteN7; break;
			case '8': si = spriteN8; break;
			case '9': si = spriteN9; break;
			default: si = spriteNE; break;
		}

		drawTexture(si.Id, charNum, -9990, (int)displayTime,
		            settings.SpeedoSettings.SpeedSize, static_cast<float>(si.Height) * (settings.SpeedoSettings.SpeedSize / static_cast<float>(si.Width)),
		            0.5f, 0.5f,
		            settings.SpeedoSettings.SpeedXpos + offsetX + settings.SpeedoSettings.SpeedSize * charNum, settings.SpeedoSettings.SpeedYpos + offsetY,
		            0.0f, screencorrection, 0.0f, 0.5f, 0.74f, 1.0f * speedoAlpha);
		charNum++;
	}
}

void drawGear(int gear, bool neutral, bool shift_indicator, int charNum, float screencorrection, float offsetX, float offsetY, long long displayTime) {
	SpriteInfo spriteGear;
	Colorf c = { 0.0f, 0.5f, 0.74f, 1.0f };

	if (neutral) spriteGear = spriteNN;
	else if (gear == 0) spriteGear = spriteNR;
	else if (gear == 1) spriteGear = spriteN1;
	else if (gear == 2) spriteGear = spriteN2;
	else if (gear == 3) spriteGear = spriteN3;
	else if (gear == 4) spriteGear = spriteN4;
	else if (gear == 5) spriteGear = spriteN5;
	else if (gear == 6) spriteGear = spriteN6;
	else if (gear == 7) spriteGear = spriteN7;
	else spriteGear = spriteN9;

	if (neutral || shift_indicator || ext.GetHandbrake(vehicle)) {
		c.r = 0.99f;
		c.g = 0.5f;
		c.b = 0.25f;
	}

	drawTexture(spriteGear.Id, charNum, -9990, (int)displayTime,
	            settings.SpeedoSettings.GearSize, static_cast<float>(spriteGear.Height) * (settings.SpeedoSettings.GearSize / static_cast<float>(spriteGear.Width)),
	            0.5f, 0.5f,
	            settings.SpeedoSettings.GearXpos + offsetX, settings.SpeedoSettings.GearYpos + offsetY,
	            0.0f, screencorrection, c.r, c.g, c.b, c.a * speedoAlpha);
}

/*
 * Was it really necessary to distribute your speedometer sprites 
 * over multiple files and chop it up in multiple tiny bits?!
 * EA Black Box pls
 */
void drawSpeedo(UnitType type, bool turboActive, bool engineOn) {
	float speed = 0.0f;
	float turbo = 0.0f;
	float rpm = 0.0f;
	int gear = 1;
	bool neutral = true;
	bool shift_indicator = false;
	bool hasNOS = false;
	bool hasBoost = false;
	float boostVal = 0.0f;
	float nosVal = 0.0f;
	float heatVal = 0.0f;
	ShiftMode shiftMode;
	if (!vehicle || !ENTITY::DOES_ENTITY_EXIST(vehicle) ||
		playerPed != VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, -1)) {
		hasDashSpeedo = false;
		shiftMode = ShiftMode::Default;
	}
	else {
		speed = ext.GetDashSpeed(vehicle);
		if (speed > 0.5f && !hasDashSpeedo) {
			hasDashSpeedo = true;
		}
		if (!hasDashSpeedo) {
			speed = abs(ENTITY::GET_ENTITY_SPEED_VECTOR(vehicle, true).y);
		}

		turbo = ext.GetTurbo(vehicle);
		rpm = ext.GetCurrentRPM(vehicle);
		gear = ext.GetGearCurr(vehicle);
		neutral = DECORATOR::DECOR_GET_INT(vehicle, (char*)decorMTNeutral);
		shift_indicator = DECORATOR::DECOR_GET_INT(vehicle, (char*)decorMTShiftIndicator) > 0;
		if (getGameVersion() >= G_VER_1_0_944_2_STEAM) {
			hasBoost = VEHICLE::_HAS_VEHICLE_ROCKET_BOOST(vehicle);
			boostVal = ext.GetRocketBoostCharge(vehicle);
		}
		if (DECORATOR::DECOR_GET_INT(vehicle, (char*)decorNOS) == 1) {
			hasNOS = true;
			nosVal = DECORATOR::_DECOR_GET_FLOAT(vehicle, (char*)decorNOSLevel);
		}
		heatVal = DECORATOR::_DECOR_GET_FLOAT(vehicle, (char*)decorDragHeat);
		switch(DECORATOR::DECOR_GET_INT(vehicle, (char*)decorMTGetShiftMode)) {
			case 1: shiftMode = ShiftMode::Sequential;
			case 2: shiftMode = ShiftMode::HPattern;
			case 3: shiftMode = ShiftMode::Automatic;
			default: shiftMode = ShiftMode::Default;
		}
	}
	if (!engineOn) rpm = 0.0f;

	float screencorrection = invoke<float>(0xF1307EF624A80D87, FALSE);
	float offsetX = settings.SpeedoSettings.SpeedoXpos;
	float offsetY = settings.SpeedoSettings.SpeedoYpos;

	bool dragHUDRegistered = DECORATOR::DECOR_IS_REGISTERED_AS_TYPE((char*)decorDragShowHud, DECOR_TYPE_BOOL);
	bool useDragHUD = false;
	if (dragHUDRegistered) {
		if (DECORATOR::DECOR_GET_BOOL(vehicle, (char*)decorDragShowHud))
			useDragHUD = true;
	}

	auto now = std::chrono::steady_clock::now().time_since_epoch();
	auto displayTime = now - previousDisplayTime;
	previousDisplayTime = now;
	int charNum; // each sprite can be drawn multiple times so just assign incremental IDs to not clash

	if (useDragHUD) {
		drawDragHUD(rpm, screencorrection, 0.0f, 0.0f);
		drawDragEngineHeating(heatVal, screencorrection, 0.0f, 0.0f);
		drawDragShiftLight(rpm, screencorrection, 0.0f, 0.0f);
		drawDragTurbo(turbo, screencorrection, 0.0f, 0.0f);
		drawDragSpeedUnit(type, speed, screencorrection, 0.0f, 0.0f);
		drawDragSpeed(speed, charNum, screencorrection, 0.0f, 0.0f, 2 * std::chrono::duration_cast<std::chrono::milliseconds>(displayTime).count());
		drawDragGear(gear, neutral, shift_indicator, charNum, screencorrection, 0.0f, 0.0f, 2 * std::chrono::duration_cast<std::chrono::milliseconds>(displayTime).count());
		if (heatVal >= 0.625f) {
			drawDragHeatAlert(screencorrection, 0.0f, 0.0f);
		}
		if (hasBoost || hasNOS) {
			drawDragNOSBars(hasBoost, boostVal, nosVal, screencorrection, 0.0f, 0.0f);
		}
	}
	else {
		drawRPM(rpm, screencorrection, offsetX, offsetY);
		drawTurbo(turbo, screencorrection, offsetX, offsetY);
		drawSpeedUnit(type, speed, screencorrection, offsetX, offsetY);

		drawSpeed(speed, charNum, screencorrection, offsetX, offsetY, 2 * std::chrono::duration_cast<std::chrono::milliseconds>(displayTime).count());
		drawGear(gear, neutral, shift_indicator, charNum, screencorrection, offsetX, offsetY, 2 * std::chrono::duration_cast<std::chrono::milliseconds>(displayTime).count());

		if (hasBoost || hasNOS) {
			drawNOSBars(hasBoost, boostVal, nosVal, screencorrection, offsetX, offsetY);
		}

		// Shift mode
		// todo: mt shift mode integration?
	}
}

void update() {
	player = PLAYER::PLAYER_ID();
	playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed) ||
		!PLAYER::IS_PLAYER_CONTROL_ON(player) ||
		ENTITY::IS_ENTITY_DEAD(playerPed) ||
		PLAYER::IS_PLAYER_BEING_ARRESTED(player, TRUE)) {
		return;
	}

	vehicle = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
	if (vehicle != prevVehicle) {
		hasDashSpeedo = false;
		prevVehicle = vehicle;
	}

	if (!settings.Enable || !vehicle || !ENTITY::DOES_ENTITY_EXIST(vehicle) || 
		playerPed != VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, -1) ||
		PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(playerPed) ||
		settings.SpeedoSettings.FPVHide && CAM::GET_FOLLOW_VEHICLE_CAM_VIEW_MODE() == 4) {
		if (speedoAlpha > 0.0f) {
			speedoAlpha -= settings.SpeedoSettings.FadeSpeed;
		}
	}
	else if (speedoAlpha < 1.0f) {
			speedoAlpha += settings.SpeedoSettings.FadeSpeed;
	}

	if (speedoAlpha > 0.01f) {
		DECORATOR::DECOR_SET_BOOL(vehicle, (char*)decoriktSpeedoActive, true);
	}
	else {
		DECORATOR::DECOR_SET_BOOL(vehicle, (char*)decoriktSpeedoActive, false);
	}

	if (VEHICLE::IS_TOGGLE_MOD_ON(vehicle, VehicleToggleModTurbo) && turboalpha < 1.0f) {
		turboalpha += settings.SpeedoSettings.FadeSpeed;
	}
	if (!VEHICLE::IS_TOGGLE_MOD_ON(vehicle, VehicleToggleModTurbo) && turboalpha > 0.0f) {
		turboalpha -= settings.SpeedoSettings.FadeSpeed;
	}
	if (turboalpha > 1.0f) {
		turboalpha = 1.0f;
	}
	if (turboalpha < 0.0f) {
		turboalpha = 0.0f;
	}
	if (speedoAlpha > 0.0f) {		
		drawSpeedo(settings.Unit, true, VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(vehicle));
	}
}

// @Unknown Modder
BYTE* g_bIsDecorRegisterLockedPtr = nullptr;

void registerDecorator(const char *thing, eDecorType type) {
	std::string strType = "?????";
	switch(type) {
	case DECOR_TYPE_FLOAT: strType = "float"; break;
	case DECOR_TYPE_BOOL: strType = "bool"; break;
	case DECOR_TYPE_INT: strType = "int"; break;
	case DECOR_TYPE_UNK: strType = "unknown"; break;
	case DECOR_TYPE_TIME: strType = "time"; break;
	}

	if (!DECORATOR::DECOR_IS_REGISTERED_AS_TYPE((char*)thing, type)) {
		DECORATOR::DECOR_REGISTER((char*)thing, type);
		logger.Write("DECOR: Registered \""+ std::string(thing)+"\" as " + strType);
	}
}

bool setupGlobals() {
	auto addr = mem::FindPattern("\x40\x53\x48\x83\xEC\x20\x80\x3D\x00\x00\x00\x00\x00\x8B\xDA\x75\x29",
								 "xxxxxxxx????xxxxx");
	if (!addr)
		return false;

	g_bIsDecorRegisterLockedPtr = (BYTE*)(addr + *(int*)(addr + 8) + 13);
	*g_bIsDecorRegisterLockedPtr = 0;

	registerDecorator(decoriktSpeedoActive, DECOR_TYPE_BOOL);
	registerDecorator(decorMTShiftIndicator, DECOR_TYPE_INT);
	registerDecorator(decorMTGear, DECOR_TYPE_INT);
	registerDecorator(decorMTNeutral, DECOR_TYPE_INT);
	registerDecorator(decorNOS, DECOR_TYPE_INT);
	registerDecorator(decorNOSLevel, DECOR_TYPE_FLOAT);
	registerDecorator(decorDragShowHud, DECOR_TYPE_BOOL);
	*g_bIsDecorRegisterLockedPtr = 1;
	return true;
}

int createTextureDefault(std::string resource, SpriteInfo *info) {
	if (FileExists(resource)) {
		//GetPNGDimensions(resource, &info->Width, &info->Height);
		std::vector<unsigned char> image;
		unsigned error = lodepng::decode(image, info->Width, info->Height, resource);
		return createTexture(resource.c_str());
	}
	logger.Write("ERROR: " + resource + " does not exist.");
	return -1;
}

void createTextures(std::string skin) {
	std::string skinPath = Paths::GetModuleFolder(Paths::GetOurModuleHandle()) + modDir + skin;

	spriteRPMBg.Id = createTextureDefault(skinPath + "\\bgRPM.png", &spriteRPMBg);
	spriteRPMNum.Id = createTextureDefault(skinPath + "\\numRPM.png", &spriteRPMNum);
	spriteRPMRed.Id = createTextureDefault(skinPath + "\\redRPM.png", &spriteRPMRed);
	spriteRPMDial.Id = createTextureDefault(skinPath + "\\dialRPM.png", &spriteRPMDial);

	spriteTurboBg.Id = createTextureDefault(skinPath + "\\bgTurbo.png", &spriteTurboBg);
	spriteTurboNum.Id = createTextureDefault(skinPath + "\\numTurbo.png", &spriteTurboNum);
	spriteTurboText.Id = createTextureDefault(skinPath + "\\textTurbo.png", &spriteTurboText);
	spriteTurboRed0.Id = createTextureDefault(skinPath + "\\redTurbo0.png", &spriteTurboRed0);
	spriteTurboRed1.Id = createTextureDefault(skinPath + "\\redTurbo1.png", &spriteTurboRed1);
	spriteTurboDial.Id = createTextureDefault(skinPath + "\\dialTurbo.png", &spriteTurboDial);

	spriteN0.Id = createTextureDefault(skinPath + "\\N0.png", &spriteN0);
	spriteN1.Id = createTextureDefault(skinPath + "\\N1.png", &spriteN1);
	spriteN2.Id = createTextureDefault(skinPath + "\\N2.png", &spriteN2);
	spriteN3.Id = createTextureDefault(skinPath + "\\N3.png", &spriteN3);
	spriteN4.Id = createTextureDefault(skinPath + "\\N4.png", &spriteN4);
	spriteN5.Id = createTextureDefault(skinPath + "\\N5.png", &spriteN5);
	spriteN6.Id = createTextureDefault(skinPath + "\\N6.png", &spriteN6);
	spriteN7.Id = createTextureDefault(skinPath + "\\N7.png", &spriteN7);
	spriteN8.Id = createTextureDefault(skinPath + "\\N8.png", &spriteN8);
	spriteN9.Id = createTextureDefault(skinPath + "\\N9.png", &spriteN9);
	spriteNN.Id = createTextureDefault(skinPath + "\\NN.png", &spriteNN);
	spriteNR.Id = createTextureDefault(skinPath + "\\NR.png", &spriteNR);
	spriteNE.Id = createTextureDefault(skinPath + "\\NE.png", &spriteNE);

	spriteKMH.Id = createTextureDefault(skinPath + "\\kmh.png", &spriteKMH);
	spriteMPH.Id = createTextureDefault(skinPath + "\\mph.png", &spriteMPH);

	spriteNOSText.Id = createTextureDefault(skinPath + "\\nosText.png", &spriteNOSText);

	spritesNOSStage1.clear();
	spritesNOSStage2.clear();
	spritesNOSStage3.clear();
	for (int i = 0; i < numNOSItemsStage1; i++) {
		SpriteInfo sprite;
		sprite.Id = createTextureDefault(skinPath + "\\nos0_" + std::to_string(i) + ".png", &sprite);
		spritesNOSStage1.push_back(sprite);
	}
	for (int i = 0; i < numNOSItemsStage2; i++) {
		SpriteInfo sprite;
		sprite.Id = createTextureDefault(skinPath + "\\nos1_" + std::to_string(i) + ".png", &sprite);
		spritesNOSStage2.push_back(sprite);
	}
	for (int i = 0; i < numNOSItemsStage3; i++) {
		SpriteInfo sprite;
		sprite.Id = createTextureDefault(skinPath + "\\nos2_" + std::to_string(i) + ".png", &sprite);
		spritesNOSStage3.push_back(sprite);
	}
	
	// DRAG
	spriteDragRPMBg.Id = createTextureDefault(skinPath + "\\drag\\bgDragRPM.png", &spriteDragRPMBg);
	spriteDragLines.Id = createTextureDefault(skinPath + "\\drag\\rpmLines.png", &spriteDragLines);
	spriteDragNosLines.Id = createTextureDefault(skinPath + "\\drag\\nosLines.png", &spriteDragNosLines);
	spriteDragHeatLines.Id = createTextureDefault(skinPath + "\\drag\\heatLines.png", &spriteDragHeatLines);
	spriteDragRPMDial.Id = createTextureDefault(skinPath + "\\drag\\rpmDial.png", &spriteDragRPMDial);
	spriteDragRPMRed.Id = createTextureDefault(skinPath + "\\drag\\rpmRed.png", &spriteDragRPMRed);
	spriteDragHeatAlert.Id = createTextureDefault(skinPath + "\\drag\\heatAlert.png", &spriteDragHeatAlert);
	spriteDragShiftLight.Id = createTextureDefault(skinPath + "\\drag\\shiftLight.png", &spriteDragShiftLight);
	spriteDragRPMBox.Id = createTextureDefault(skinPath + "\\drag\\rpmBox.png", &spriteDragRPMBox);
	spriteDragSpeedBox.Id = createTextureDefault(skinPath + "\\drag\\speedBox.png", &spriteDragSpeedBox);

	spritesDragHeat.clear();
	for (int i = numDragHeat; i > 0; i--) {
		SpriteInfo sprite;
		sprite.Id = createTextureDefault(skinPath + "\\drag\\heat" + std::to_string(i - 1) + ".png", &sprite);
		spritesDragHeat.push_back(sprite);
	}

	spritesDragNOSStage1.clear();
	spritesDragNOSStage2.clear();
	spritesDragNOSStage3.clear();
	for (int i = 0; i < numNOSItemsStage1; i++) {
		SpriteInfo sprite;
		sprite.Id = createTextureDefault(skinPath + "\\drag\\nos0_" + std::to_string(i) + ".png", &sprite);
		spritesDragNOSStage1.push_back(sprite);
	}
	for (int i = 0; i < numNOSItemsStage2; i++) {
		SpriteInfo sprite;
		sprite.Id = createTextureDefault(skinPath + "\\drag\\nos1_" + std::to_string(i) + ".png", &sprite);
		spritesDragNOSStage2.push_back(sprite);
	}
	for (int i = 0; i < numNOSItemsStage3; i++) {
		SpriteInfo sprite;
		sprite.Id = createTextureDefault(skinPath + "\\drag\\nos2_" + std::to_string(i) + ".png", &sprite);
		spritesDragNOSStage3.push_back(sprite);
	}

	spriteDragTurboBack.Id = createTextureDefault(skinPath + "\\drag\\turboBack.png", &spriteDragTurboBack);
	spriteDragTurboMeter.Id = createTextureDefault(skinPath + "\\drag\\turboMeter.png", &spriteDragTurboMeter);
	spriteDragTurboDial.Id = createTextureDefault(skinPath + "\\drag\\turboDial.png", &spriteDragTurboDial);
	spriteDragTurboRed1.Id = createTextureDefault(skinPath + "\\drag\\turboRed1.png", &spriteDragTurboRed1);
	spriteDragTurboRed2.Id = createTextureDefault(skinPath + "\\drag\\turboRed2.png", &spriteDragTurboRed2);
}

void main() {
	logger.Write("Script started");
	mem::init();
	logger.Write("Setting up globals");
	if (!setupGlobals()) {
		logger.Write("Global setup failed!");
	}

	std::string absoluteModPath = Paths::GetModuleFolder(Paths::GetOurModuleHandle()) + modDir;
	settingsGeneralFile = absoluteModPath + "\\settings_general.ini";
	settingsMenuFile = absoluteModPath + "\\settings_menu.ini";

	settings.SetFiles(settingsGeneralFile);

	menu.RegisterOnMain(std::bind(menuInit));
	menu.RegisterOnExit(std::bind(menuClose));
	menu.SetFiles(settingsMenuFile);
	
	settings.Read();
	menu.ReadSettings();

	skinDir = "\\default";
	createTextures(skinDir);

	while (true) {
		update();
		update_menu();
		WAIT(0);
	}
}

void ScriptMain() {
	srand(GetTickCount());
	previousDisplayTime = std::chrono::steady_clock::now().time_since_epoch();
	main();
}
