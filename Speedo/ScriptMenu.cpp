#define NOMINMAX

#include "script.h"
#include "menu.h"

#include "ScriptSettings.hpp"

extern ScriptSettings settings;
extern std::string settingsGeneralFile;

extern NativeMenu::Menu menu;

extern ScriptSettings settings;


///////////////////////////////////////////////////////////////////////////////
//                             Menu stuff
///////////////////////////////////////////////////////////////////////////////
void menuInit() {

}

void menuClose() {
	settings.SaveGeneral();
}

void update_menu() {
	menu.CheckKeys();

	/* Yes hello I am root */
	if (menu.CurrentMenu("mainmenu")) {
		menu.Title("Speedometer");
		menu.Subtitle(DISPLAY_VERSION);
		menu.BoolOption("Enable", settings.Enable);

		if (menu.Option("Reload pos") ) {
			settings.Read();
		}
		int currUnit = (int)settings.Unit;
		if (menu.StringArray("Units", { "km/h", "mph" }, currUnit)) {
			if (currUnit != (int)settings.Unit) {
				settings.Unit = (UnitType)currUnit;
			}
		}

		menu.BoolOption("FPVHide", settings.FPVHide);
		menu.FloatOption("Fade speed", settings.FadeSpeed, 0.0f, 1.0f, 0.005f);
		
		if (settings.ShowPlacementMenu) {
			menu.MenuOption("Placements", "placementmenu");
		}
	}

	if (menu.CurrentMenu("placementmenu")) {
		menu.FloatOption("OffsetX", settings.SpeedoSettings.SpeedoXpos, -1.0f, 1.0f, 0.005f);
		menu.FloatOption("OffsetY", settings.SpeedoSettings.SpeedoYpos, -1.0f, 1.0f, 0.005f);

		menu.MenuOption("RPM", "rpmposmenu");
		menu.MenuOption("Turbo", "turboposmenu");
		menu.MenuOption("Speed", "speedposmenu");
		menu.MenuOption("Gear", "gearposmenu");
		menu.MenuOption("NOS", "nosposmenu");
		if (menu.Option("Normalize speedo")) {
			settings.Normalize(settings.SpeedoSettings);
		}
	}

	if (menu.CurrentMenu("rpmposmenu")) {
		menu.Title("RPM");
		menu.Subtitle(DISPLAY_VERSION);
		menu.FloatOption("RPMBgXpos", settings.SpeedoSettings.RPMBgXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMBgYpos", settings.SpeedoSettings.RPMBgYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMBgSize", settings.SpeedoSettings.RPMBgSize, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMNumXpos", settings.SpeedoSettings.RPMNumXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMNumYpos", settings.SpeedoSettings.RPMNumYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMNumSize", settings.SpeedoSettings.RPMNumSize, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMDialXpos", settings.SpeedoSettings.RPMDialXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMDialYpos", settings.SpeedoSettings.RPMDialYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMDialSize", settings.SpeedoSettings.RPMDialSize, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMRedXpos", settings.SpeedoSettings.RPMRedXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMRedYpos", settings.SpeedoSettings.RPMRedYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("RPMRedSize", settings.SpeedoSettings.RPMRedSize, 0.0f, 1.0f, 0.001f);
	}

	if (menu.CurrentMenu("turboposmenu")) {
		menu.Title("Turbo");
		menu.Subtitle(DISPLAY_VERSION);
		menu.FloatOption("TurboBgXpos", settings.SpeedoSettings.TurboBgXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboBgYpos", settings.SpeedoSettings.TurboBgYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboBgSize", settings.SpeedoSettings.TurboBgSize, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboNumXpos", settings.SpeedoSettings.TurboNumXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboNumYpos", settings.SpeedoSettings.TurboNumYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboNumSize", settings.SpeedoSettings.TurboNumSize, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboTextXpos", settings.SpeedoSettings.TurboTextXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboTextYpos", settings.SpeedoSettings.TurboTextYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboTextSize", settings.SpeedoSettings.TurboTextSize, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboDialXpos", settings.SpeedoSettings.TurboDialXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboDialYpos", settings.SpeedoSettings.TurboDialYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboDialSize", settings.SpeedoSettings.TurboDialSize, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboRed0Xpos", settings.SpeedoSettings.TurboRed0Xpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboRed0Ypos", settings.SpeedoSettings.TurboRed0Ypos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboRed0Size", settings.SpeedoSettings.TurboRed0Size, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboRed1Xpos", settings.SpeedoSettings.TurboRed1Xpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboRed1Ypos", settings.SpeedoSettings.TurboRed1Ypos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("TurboRed1Size", settings.SpeedoSettings.TurboRed1Size, 0.0f, 1.0f, 0.001f);
	}

	if (menu.CurrentMenu("speedposmenu")) {
		menu.Title("Speed");
		menu.Subtitle(DISPLAY_VERSION);
		menu.FloatOption("SpeedXpos", settings.SpeedoSettings.SpeedXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("SpeedYpos", settings.SpeedoSettings.SpeedYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("SpeedSize", settings.SpeedoSettings.SpeedSize, 0.0f, 1.0f, 0.001f);

		menu.FloatOption("UnitXpos", settings.SpeedoSettings.UnitXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("UnitYpos", settings.SpeedoSettings.UnitYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("UnitSize", settings.SpeedoSettings.UnitSize, 0.0f, 1.0f, 0.001f);
	}

	if (menu.CurrentMenu("gearposmenu")) {
		menu.Title("Gear");
		menu.Subtitle(DISPLAY_VERSION);
		menu.FloatOption("GearXpos", settings.SpeedoSettings.GearXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("GearYpos", settings.SpeedoSettings.GearYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("GearSize", settings.SpeedoSettings.GearSize, 0.0f, 1.0f, 0.001f);
	}

	// fuck me
	if (menu.CurrentMenu("nosposmenu")) {
		menu.Title("NOS");
		menu.Subtitle(DISPLAY_VERSION);

		menu.FloatOption("NOSTextXpos", settings.SpeedoSettings.NOSTextXpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("NOSTextYpos", settings.SpeedoSettings.NOSTextYpos, 0.0f, 1.0f, 0.001f);
		menu.FloatOption("NOSTextSize", settings.SpeedoSettings.NOSTextSize, 0.0f, 1.0f, 0.001f);

		menu.FloatOption("NOS0Stage1Size", settings.SpeedoSettings.NOSStage1Size[0], 0.0f, 1.0f, 0.001f);
		menu.FloatOption("NOS0Stage2Size", settings.SpeedoSettings.NOSStage2Size[0], 0.0f, 1.0f, 0.001f);
		menu.FloatOption("NOS0Stage3Size", settings.SpeedoSettings.NOSStage3Size[0], 0.0f, 1.0f, 0.001f);
		for (int i = 1; i < numNOSItemsStage1; i++) {
			settings.SpeedoSettings.NOSStage1Size[i] = settings.SpeedoSettings.NOSStage1Size[0];
		}
		for (int i = 1; i < numNOSItemsStage2; i++) {
			settings.SpeedoSettings.NOSStage2Size[i] = settings.SpeedoSettings.NOSStage2Size[0];
		}
		for (int i = 1; i < numNOSItemsStage3; i++) {
			settings.SpeedoSettings.NOSStage3Size[i] = settings.SpeedoSettings.NOSStage3Size[0];
		}

		for (int i = 0; i < numNOSItemsStage1; i++) {
			menu.FloatOption("NOS" + std::to_string(i) + "Xpos", settings.SpeedoSettings.NOSStage1Xpos[i], 0.0f, 1.0f, 0.001f);
			menu.FloatOption("NOS" + std::to_string(i) + "Ypos", settings.SpeedoSettings.NOSStage1Ypos[i], 0.0f, 1.0f, 0.001f);
		}
		for (int i = 0; i < numNOSItemsStage2; i++) {
			menu.FloatOption("NOS" + std::to_string(i) + "Xpos", settings.SpeedoSettings.NOSStage2Xpos[i], 0.0f, 1.0f, 0.001f);
			menu.FloatOption("NOS" + std::to_string(i) + "Ypos", settings.SpeedoSettings.NOSStage2Ypos[i], 0.0f, 1.0f, 0.001f);
		}
		for (int i = 0; i < numNOSItemsStage3; i++) {
			menu.FloatOption("NOS"+std::to_string(i)+"Xpos", settings.SpeedoSettings.NOSStage3Xpos[i], 0.0f, 1.0f, 0.001f);
			menu.FloatOption("NOS"+std::to_string(i)+"Ypos", settings.SpeedoSettings.NOSStage3Ypos[i], 0.0f, 1.0f, 0.001f);
		}
	}
	
	menu.EndMenu();
}
