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
#include "SpeedoInfo.h"

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

enum eDecorType {
	DECOR_TYPE_FLOAT = 1,
	DECOR_TYPE_BOOL,
	DECOR_TYPE_INT,
	DECOR_TYPE_UNK,
	DECOR_TYPE_TIME
};

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

std::string settingsGeneralFile;
std::string settingsMenuFile;
std::string skinDir;
std::string absoluteModPath;

// muh sprites
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
SpriteInfo spriteShiftLight;

SpriteInfo spriteNOSText;
std::vector<SpriteInfo> spritesNOSStage1;
std::vector<SpriteInfo> spritesNOSStage2;
std::vector<SpriteInfo> spritesNOSStage3;

// Extra components
SpriteInfo spriteGearBg;
SpriteInfo spriteSpeedBg;
SpriteInfo spriteHeatAlert;
SpriteInfo spriteHeatNum;
std::vector<SpriteInfo> spritesHeat;


// globals yo idk why

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

SpeedoInfo currentSpeedo;

std::vector<std::string> skins;
int currSkinIndex;

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
		currentSpeedo.NOSTextSize, static_cast<float>(spriteNOSText.Height) * (currentSpeedo.NOSTextSize / static_cast<float>(spriteNOSText.Width)),
		0.5f, 0.5f,
		currentSpeedo.NOSTextXpos + offsetX, currentSpeedo.NOSTextYpos + offsetY,
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
		for (auto size : currentSpeedo.NOSStage1Size) { nosBarSize.push_back(size); }
		for (auto xpos : currentSpeedo.NOSStage1Xpos) { nosBarXpos.push_back(xpos); }
		for (auto ypos : currentSpeedo.NOSStage1Ypos) { nosBarYpos.push_back(ypos); }
		break;
	}
	case 2: {
		numNOSItems = numNOSItemsStage2;
		nosSprites = spritesNOSStage2;
		for (auto size : currentSpeedo.NOSStage2Size) { nosBarSize.push_back(size); }
		for (auto xpos : currentSpeedo.NOSStage2Xpos) { nosBarXpos.push_back(xpos); }
		for (auto ypos : currentSpeedo.NOSStage2Ypos) { nosBarYpos.push_back(ypos); }
		break;
	}
	default:
	case 3: {
		numNOSItems = numNOSItemsStage3;
		nosSprites = spritesNOSStage3;
		for (auto size : currentSpeedo.NOSStage3Size) { nosBarSize.push_back(size); }
		for (auto xpos : currentSpeedo.NOSStage3Xpos) { nosBarXpos.push_back(xpos); }
		for (auto ypos : currentSpeedo.NOSStage3Ypos) { nosBarYpos.push_back(ypos); }
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

void drawRPM(float rpm, float screencorrection, float offsetX, float offsetY) {
	displayRPM = lerp(displayRPM, rpm, 15.0f * GAMEPLAY::GET_FRAME_TIME());
	float rpmRot = displayRPM * currentSpeedo.RPMDialFullRot + currentSpeedo.RPMDialZeroRot;

	drawTexture(spriteRPMBg.Id, 0, -9999, 100, 
	            currentSpeedo.RPMBgSize, static_cast<float>(spriteRPMBg.Height) * (currentSpeedo.RPMBgSize / static_cast<float>(spriteRPMBg.Width)),
	            0.5f, 0.5f, 
	            currentSpeedo.RPMBgXpos + offsetX, currentSpeedo.RPMBgYpos + offsetY,
	            0.0f, screencorrection, 1.0f, 1.0f, 1.0f, 0.75f * speedoAlpha);
	drawTexture(spriteRPMNum.Id, 0, -9998, 100,
	            currentSpeedo.RPMNumSize, static_cast<float>(spriteRPMNum.Height) * (currentSpeedo.RPMNumSize / static_cast<float>(spriteRPMNum.Width)),
	            0.5f, 0.5f,
	            currentSpeedo.RPMNumXpos + offsetX, currentSpeedo.RPMNumYpos + offsetY,
	            0.0f, screencorrection, 80.0f / 255.0f, 175.0f / 255.0f, 255.0f / 255.0f, 1.0f * speedoAlpha);
	drawTexture(spriteRPMDial.Id, 0, -9990, 100, 
	            currentSpeedo.RPMDialSize, static_cast<float>(spriteRPMDial.Height) * (currentSpeedo.RPMDialSize / static_cast<float>(spriteRPMDial.Width)),
	            currentSpeedo.RPMDialCenterX, currentSpeedo.RPMDialCenterY,
	            currentSpeedo.RPMDialXpos + offsetX, currentSpeedo.RPMDialYpos + offsetY,
	            rpmRot, screencorrection, 1.0f, 1.0f, 1.0f, 0.9f * speedoAlpha);
	drawTexture(spriteRPMRed.Id, 0, -9997, 100,
	            currentSpeedo.RPMRedSize, static_cast<float>(spriteRPMRed.Height) * (currentSpeedo.RPMRedSize / static_cast<float>(spriteRPMRed.Width)),
	            0.5f, 0.5f,
	            currentSpeedo.RPMRedXpos + offsetX, currentSpeedo.RPMRedYpos + offsetY,
	            0.0f, screencorrection, 1.0f, 0.0f, 0.0f, 0.6f* speedoAlpha);
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

	float turboRot = displayTurboRot * currentSpeedo.TurboDialFullRot + currentSpeedo.TurboDialZeroRot;

	drawTexture(spriteTurboBg.Id, 0, -9999, 100,
	            currentSpeedo.TurboBgSize, static_cast<float>(spriteTurboBg.Height) * (currentSpeedo.TurboBgSize / static_cast<float>(spriteTurboBg.Width)),
	            0.5f, 0.5f,
	            currentSpeedo.TurboBgXpos + offsetX, currentSpeedo.TurboBgYpos + offsetY,
	            0.0f, screencorrection, 1.0f, 1.0f, 1.0f, 0.75f*turboalpha * speedoAlpha);
	drawTexture(spriteTurboNum.Id, 0, -9998, 100,
	            currentSpeedo.TurboNumSize, static_cast<float>(spriteTurboNum.Height) * (currentSpeedo.TurboNumSize / static_cast<float>(spriteTurboNum.Width)),
	            0.5f, 0.5f,
	            currentSpeedo.TurboNumXpos + offsetX, currentSpeedo.TurboNumYpos + offsetY,
	            0.0f, screencorrection, 80.0f / 255.0f, 175.0f / 255.0f, 255.0f / 255.0f, 1.0f * turboalpha* speedoAlpha);
	drawTexture(spriteTurboDial.Id, 0, -9990, 100,
	            currentSpeedo.TurboDialSize, static_cast<float>(spriteTurboDial.Height) * (currentSpeedo.TurboDialSize / static_cast<float>(spriteTurboDial.Width)),
	            currentSpeedo.TurboDialCenterX, currentSpeedo.TurboDialCenterY,
	            currentSpeedo.TurboDialXpos + offsetX, currentSpeedo.TurboDialYpos + offsetY,
	            turboRot, screencorrection, 1.0f, 1.0f, 1.0f, 0.9f * turboalpha* speedoAlpha);

	drawTexture(spriteTurboText.Id, 0, -9990, 100,
	            currentSpeedo.TurboTextSize, static_cast<float>(spriteTurboText.Height) * (currentSpeedo.TurboTextSize / static_cast<float>(spriteTurboText.Width)),
	            0.5f, 0.5f,
	            currentSpeedo.TurboTextXpos + offsetX, currentSpeedo.TurboTextYpos + offsetY,
	            0.0f, screencorrection, 0.54f, 0.69f, 0.93f, 1.0f*turboalpha* speedoAlpha);
	drawTexture(spriteTurboRed0.Id, 0, -9997, 100,
	            currentSpeedo.TurboRed0Size, static_cast<float>(spriteTurboRed0.Height) * (currentSpeedo.TurboRed0Size / static_cast<float>(spriteTurboRed0.Width)),
	            0.5f, 0.5f,
	            currentSpeedo.TurboRed0Xpos + offsetX, currentSpeedo.TurboRed0Ypos + offsetY,
	            0.0f, screencorrection, 1.0f, 0.0f, 0.0f, 0.6f*turboalpha* speedoAlpha);
	drawTexture(spriteTurboRed1.Id, 0, -9997, 100,
	            currentSpeedo.TurboRed1Size, static_cast<float>(spriteTurboRed1.Height) * (currentSpeedo.TurboRed1Size / static_cast<float>(spriteTurboRed1.Width)),
	            0.5f, 0.5f,
	            currentSpeedo.TurboRed1Xpos + offsetX, currentSpeedo.TurboRed1Ypos + offsetY,
	            0.0f, screencorrection, 1.0f, 0.0f, 0.0f, 0.6f*turboalpha* speedoAlpha);
}

void drawSpeedUnit(UnitType type, float &speed, float screencorrection, float offsetX, float offsetY) {
	SpriteInfo spriteUnit;
	if (type == UnitType::MPH) {
		speed = speed / 0.44704f;
		spriteUnit = spriteMPH;
	}
	else {
		speed = speed * 3.6f;
		spriteUnit = spriteKMH;
	}
	drawTexture(spriteUnit.Id, 0, -9990, 100,
	            currentSpeedo.UnitSize, static_cast<float>(spriteUnit.Height) * (currentSpeedo.UnitSize / static_cast<float>(spriteUnit.Width)),
	            0.5f, 0.5f,
	            currentSpeedo.UnitXpos + offsetX, currentSpeedo.UnitYpos + offsetY,
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
		            currentSpeedo.SpeedSize, static_cast<float>(si.Height) * (currentSpeedo.SpeedSize / static_cast<float>(si.Width)),
		            0.5f, 0.5f,
		            currentSpeedo.SpeedXpos + offsetX + currentSpeedo.SpeedSize * charNum, currentSpeedo.SpeedYpos + offsetY,
		            0.0f, screencorrection, 0.0f, 0.5f, 0.74f, 1.0f * speedoAlpha);
		charNum++;
	}
}

void drawGear(int gear, bool neutral, int shift_indicator, int charNum, float screencorrection, float offsetX, float offsetY, long long displayTime) {
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

	int level = -9990;
	if (neutral || shift_indicator || ext.GetHandbrake(vehicle)) {
		c.r = 0.99f;
		c.g = 0.5f;
		c.b = 0.25f;
		level = -9989;
	}

	drawTexture(spriteGear.Id, charNum, level, (int)displayTime,
	            currentSpeedo.GearSize, static_cast<float>(spriteGear.Height) * (currentSpeedo.GearSize / static_cast<float>(spriteGear.Width)),
	            0.5f, 0.5f,
	            currentSpeedo.GearXpos + offsetX, currentSpeedo.GearYpos + offsetY,
	            0.0f, screencorrection, c.r, c.g, c.b, c.a * speedoAlpha);

	if (shift_indicator != 0) {
		Colorf indicatorColor = { 0.0f, 0.5f, 0.74f, 1.0f };
		if (shift_indicator == 1) {
			indicatorColor.r = 0.99f;
			indicatorColor.g = 0.5f;
			indicatorColor.b = 0.25f;
		}

		drawTexture(spriteShiftLight.Id, charNum, level, (int)displayTime,
			currentSpeedo.ShiftLightSize, static_cast<float>(spriteShiftLight.Height) * (currentSpeedo.ShiftLightSize / static_cast<float>(spriteShiftLight.Width)),
			0.5f, 0.5f,
			currentSpeedo.ShiftLightXpos + offsetX, currentSpeedo.ShiftLightYpos + offsetY,
			0.0f, screencorrection, indicatorColor.r, indicatorColor.g, indicatorColor.b, indicatorColor.a * speedoAlpha);
	}
}

void drawHeating(float heatVal, float screencorrection, float offsetX, float offsetY) {
	float maxVal = 1.0f;
	float val = heatVal;

	float baseAlpha = 1.0f;

	int i = 0;
	float portion = maxVal / numDragHeat;
	for (auto sprite : spritesHeat) {
		float min = maxVal - portion * (i + 1);

		float res = (val - min) / portion;
		if (res > 1.0f) res = 1.0f;
		if (res < 0.0f) res = 0.0f;

		float finalAlpha = 0.0f;
		if (res < 1.0f) finalAlpha = 0.0f;
		if (res == 1.0f) finalAlpha = 1.0f;

		drawTexture(sprite.Id, i, -9998, 100,
			currentSpeedo.HeatSize[i], static_cast<float>(sprite.Height) * (currentSpeedo.HeatSize[i] / static_cast<float>(sprite.Width)),
			0.5f, 0.5f,
			currentSpeedo.HeatXpos[i] + offsetX, currentSpeedo.HeatYpos[i] + offsetY,
			0.0f, screencorrection, 1.0f, 1.0f, 0.0f, finalAlpha * speedoAlpha);
		i++;
	}

	drawTexture(spriteHeatNum.Id, i, -9998, 100,
		currentSpeedo.HeatNumSize, static_cast<float>(spriteHeatNum.Height) * (currentSpeedo.HeatNumSize / static_cast<float>(spriteHeatNum.Width)),
		0.5f, 0.5f,
		currentSpeedo.HeatNumXpos + offsetX, currentSpeedo.HeatNumYpos + offsetY,
		0.0f, screencorrection, 1.0f, 1.0f, 1.0f, speedoAlpha);
}

void drawHeatAlert(float screencorrection, float offsetX, float offsetY) {
	drawTexture(spriteHeatAlert.Id, 0, -9999, 100,
		currentSpeedo.HeatAlertSize, static_cast<float>(spriteHeatAlert.Height) * (currentSpeedo.HeatAlertSize / static_cast<float>(spriteHeatAlert.Width)),
		0.5f, 0.5f,
		currentSpeedo.HeatAlertXpos + offsetX, currentSpeedo.HeatAlertYpos + offsetY,
		0.0f, screencorrection, 0.6f, 0.0f, 0.0f, 0.75f * speedoAlpha);
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
	int shift_indicator = 0;
	bool hasNOS = false;
	bool hasBoost = false;
	float boostVal = 0.0f;
	float nosVal = 0.0f;
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
		shift_indicator = DECORATOR::DECOR_GET_INT(vehicle, (char*)decorMTShiftIndicator);
		if (getGameVersion() >= G_VER_1_0_944_2_STEAM) {
			hasBoost = VEHICLE::_HAS_VEHICLE_ROCKET_BOOST(vehicle);
			boostVal = ext.GetRocketBoostCharge(vehicle);
		}
		if (DECORATOR::DECOR_GET_INT(vehicle, (char*)decorNOS) == 1) {
			hasNOS = true;
			nosVal = DECORATOR::_DECOR_GET_FLOAT(vehicle, (char*)decorNOSLevel);
		}
		switch(DECORATOR::DECOR_GET_INT(vehicle, (char*)decorMTGetShiftMode)) {
			case 1: shiftMode = ShiftMode::Sequential;
			case 2: shiftMode = ShiftMode::HPattern;
			case 3: shiftMode = ShiftMode::Automatic;
			default: shiftMode = ShiftMode::Default;
		}
	}
	if (!engineOn) rpm = 0.0f;

	float screencorrection = invoke<float>(0xF1307EF624A80D87, FALSE);
	float offsetX = currentSpeedo.SpeedoXpos;
	float offsetY = currentSpeedo.SpeedoYpos;

	auto now = std::chrono::steady_clock::now().time_since_epoch();
	auto newDisplayTime = now - previousDisplayTime;
	previousDisplayTime = now;
	auto lastFrameTime = std::chrono::duration_cast<std::chrono::microseconds>(newDisplayTime).count(); // in microseconds!
	auto nextFrameTime = lastFrameTime/1000;
	if (lastFrameTime < 16666) { // cap refresh @ 60 fps
		nextFrameTime = 16666/1000;
	}
	nextFrameTime = static_cast<long long>(nextFrameTime * 1.5);
	
	drawRPM(rpm, screencorrection, offsetX, offsetY);
	drawTurbo(turbo, screencorrection, offsetX, offsetY);
	drawSpeedUnit(type, speed, screencorrection, offsetX, offsetY);

	int charNum; // each sprite can be drawn multiple times so just assign incremental IDs to not clash
	drawSpeed(speed, charNum, screencorrection, offsetX, offsetY, nextFrameTime);
	drawGear(gear, neutral, shift_indicator, charNum, screencorrection, offsetX, offsetY, nextFrameTime);

	if (hasBoost || hasNOS) {
		drawNOSBars(hasBoost, boostVal, nosVal, screencorrection, offsetX, offsetY);
	}

	// yeah so this does the drag hud thingy
	if (currentSpeedo.ExtraHUDComponents) {
		float heatVal;
		if (DECORATOR::DECOR_IS_REGISTERED_AS_TYPE((char*)decorDragHeat, DECOR_TYPE_FLOAT)) {
			heatVal = DECORATOR::_DECOR_GET_FLOAT(vehicle, (char*)decorDragHeat);;
		}
		else {
			heatVal = 0.0f;
		}

		drawHeating(heatVal, screencorrection, offsetX, offsetY);
		
		if (heatVal >= 0.625f) {
			drawHeatAlert(screencorrection, offsetX, offsetY);
		}

		drawTexture(spriteGearBg.Id, 0, -9990, 100,
			currentSpeedo.GearBgSize, static_cast<float>(spriteGearBg.Height) * (currentSpeedo.GearBgSize / static_cast<float>(spriteGearBg.Width)),
			0.5f, 0.5f,
			currentSpeedo.GearBgXpos + offsetX, currentSpeedo.GearBgYpos + offsetY,
			0.0f, screencorrection, 1.0f, 1.0f, 1.0f, 0.3f * speedoAlpha);

		drawTexture(spriteSpeedBg.Id, 0, -9990, 100,
			currentSpeedo.SpeedBgSize, static_cast<float>(spriteSpeedBg.Height) * (currentSpeedo.SpeedBgSize / static_cast<float>(spriteSpeedBg.Width)),
			0.5f, 0.5f,
			currentSpeedo.SpeedBgXpos + offsetX, currentSpeedo.SpeedBgYpos + offsetY,
			0.0f, screencorrection, 1.0f, 1.0f, 1.0f, 0.3f * speedoAlpha);
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
		settings.FPVHide && CAM::GET_FOLLOW_VEHICLE_CAM_VIEW_MODE() == 4) {
		if (speedoAlpha > 0.0f) {
			speedoAlpha -= settings.FadeSpeed;
		}
	}
	else if (speedoAlpha < 1.0f) {
			speedoAlpha += settings.FadeSpeed;
	}

	if (speedoAlpha > 0.01f) {
		DECORATOR::DECOR_SET_BOOL(vehicle, (char*)decoriktSpeedoActive, true);
	}
	else {
		DECORATOR::DECOR_SET_BOOL(vehicle, (char*)decoriktSpeedoActive, false);
	}

	if (VEHICLE::IS_TOGGLE_MOD_ON(vehicle, VehicleToggleModTurbo) && turboalpha < 1.0f) {
		turboalpha += settings.FadeSpeed;
	}
	if (!VEHICLE::IS_TOGGLE_MOD_ON(vehicle, VehicleToggleModTurbo) && turboalpha > 0.0f) {
		turboalpha -= settings.FadeSpeed;
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

	bool dragHUDRegistered = DECORATOR::DECOR_IS_REGISTERED_AS_TYPE((char*)decorDragShowHud, DECOR_TYPE_BOOL);
	bool useDragHUD = false;
	if (dragHUDRegistered) {
		if (DECORATOR::DECOR_GET_BOOL(vehicle, (char*)decorDragShowHud))
			useDragHUD = true;
	}
	if (useDragHUD && skins[currSkinIndex] != "default-drag") {
		changeSkin("default-drag");
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
		std::vector<unsigned char> image;
		unsigned error = lodepng::decode(image, info->Width, info->Height, resource);
		return createTexture(resource.c_str());
	}
	logger.Write("ERROR: " + resource + " does not exist.");
	return -1;
}

void createTextures(std::string skin) {
	std::string skinPath = Paths::GetModuleFolder(Paths::GetOurModuleHandle()) + modDir + skin;

	spriteRPMBg.Id = createTextureDefault(skinPath + "\\RPMBg.png", &spriteRPMBg);
	spriteRPMNum.Id = createTextureDefault(skinPath + "\\RPMNum.png", &spriteRPMNum);
	spriteRPMRed.Id = createTextureDefault(skinPath + "\\RPMRed.png", &spriteRPMRed);
	spriteRPMDial.Id = createTextureDefault(skinPath + "\\RPMDial.png", &spriteRPMDial);

	spriteTurboBg.Id = createTextureDefault(skinPath + "\\TurboBg.png", &spriteTurboBg);
	spriteTurboNum.Id = createTextureDefault(skinPath + "\\TurboNum.png", &spriteTurboNum);
	spriteTurboText.Id = createTextureDefault(skinPath + "\\TurboText.png", &spriteTurboText);
	spriteTurboRed0.Id = createTextureDefault(skinPath + "\\TurboRed0.png", &spriteTurboRed0);
	spriteTurboRed1.Id = createTextureDefault(skinPath + "\\TurboRed1.png", &spriteTurboRed1);
	spriteTurboDial.Id = createTextureDefault(skinPath + "\\TurboDial.png", &spriteTurboDial);

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

	spriteKMH.Id = createTextureDefault(skinPath + "\\UnitKmh.png", &spriteKMH);
	spriteMPH.Id = createTextureDefault(skinPath + "\\UnitMph.png", &spriteMPH);

	spriteShiftLight.Id = createTextureDefault(skinPath + "\\ShiftLight.png", &spriteShiftLight);

	spriteNOSText.Id = createTextureDefault(skinPath + "\\NOSText.png", &spriteNOSText);

	spritesNOSStage1.clear();
	spritesNOSStage2.clear();
	spritesNOSStage3.clear();
	for (int i = 0; i < numNOSItemsStage1; i++) {
		SpriteInfo sprite;
		sprite.Id = createTextureDefault(skinPath + "\\NOSL0_" + std::to_string(i) + ".png", &sprite);
		spritesNOSStage1.push_back(sprite);
	}
	for (int i = 0; i < numNOSItemsStage2; i++) {
		SpriteInfo sprite;
		sprite.Id = createTextureDefault(skinPath + "\\NOSL1_" + std::to_string(i) + ".png", &sprite);
		spritesNOSStage2.push_back(sprite);
	}
	for (int i = 0; i < numNOSItemsStage3; i++) {
		SpriteInfo sprite;
		sprite.Id = createTextureDefault(skinPath + "\\NOSL2_" + std::to_string(i) + ".png", &sprite);
		spritesNOSStage3.push_back(sprite);
	}
	logger.Write("Finished loading resources for " + skin);

	if (currentSpeedo.ExtraHUDComponents) {
		spriteGearBg.Id = createTextureDefault(skinPath + "\\_GearBg.png", &spriteGearBg);
		spriteSpeedBg.Id = createTextureDefault(skinPath + "\\_SpeedBg.png", &spriteSpeedBg);
		spriteHeatAlert.Id = createTextureDefault(skinPath + "\\_HeatAlert.png", &spriteHeatAlert);
		spriteHeatNum.Id = createTextureDefault(skinPath + "\\_HeatNum.png", &spriteHeatNum);

		for (int i = numDragHeat-1; i >= 0; i--) {
			SpriteInfo sprite;
			sprite.Id = createTextureDefault(skinPath + "\\_Heat" + std::to_string(i) + ".png", &sprite);
			spritesHeat.push_back(sprite);
		}

		logger.Write("Finished loading extra resources for " + skin);
	}
}

void onMenuOpen() {
	settings.Read();

	skins = settings.EnumerateSkins();
	for (auto skin : skins) {
		logger.Write("Found skin: " + skin);
	}
}

void changeSkin(std::string skinTemp) {
	skinDir = "\\" + skinTemp;

	logger.Write("Loading " + absoluteModPath + skinDir);
	currentSpeedo = settings.ReadSkin(absoluteModPath + skinDir);
	logger.Write("Finished loading " + skinTemp);

	createTextures(skinDir);
}

void main() {
	logger.Write("Script started");
	mem::init();
	logger.Write("Setting up globals");
	if (!setupGlobals()) {
		logger.Write("Global setup failed!");
	}

	absoluteModPath = Paths::GetModuleFolder(Paths::GetOurModuleHandle()) + modDir;
	settingsGeneralFile = absoluteModPath + "\\settings_general.ini";
	settingsMenuFile = absoluteModPath + "\\settings_menu.ini";

	settings.SetFiles(settingsGeneralFile);
	settings.SetModPath(absoluteModPath);

	menu.RegisterOnMain(std::bind(menuInit));
	menu.RegisterOnExit(std::bind(menuClose));
	menu.SetFiles(settingsMenuFile);
	
	settings.Read();
	menu.ReadSettings();

	skins = settings.EnumerateSkins();
	for (auto skin : skins) {
		logger.Write("Found skin: " + skin);
	}

	if (skins.size() == 0 || std::find(skins.begin(), skins.end(), settings.DefaultSkin) == skins.end()) {
		logger.Write("FATAL: No \"" + settings.DefaultSkin + "\" skin, quitting...");
		return;
	}
	int i = 0;
	for (auto skin : skins) {
		if (skin == settings.DefaultSkin) currSkinIndex = i;
		i++;
	}
	changeSkin(settings.DefaultSkin);

	previousDisplayTime = std::chrono::steady_clock::now().time_since_epoch();
	while (true) {
		update();
		update_menu();
		WAIT(0);
	}
}

void ScriptMain() {
	srand(GetTickCount());
	main();
}
