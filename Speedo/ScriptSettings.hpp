#pragma once
#include <string>
#include <array>

const int numNOSItems = 6;

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
private:
	void parseSettingsGeneral();

	std::string settingsGeneralFile;
	std::string settingsMenuFile;
};
