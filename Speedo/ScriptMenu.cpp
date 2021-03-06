#include "script.h"
#include "menu.h"

#include "ScriptSettings.hpp"
#include "SpeedoInfo.h"
#include "Util/Paths.h"

#define PROCESS_SUBMENU(name) \
    if (menu.CurrentMenu(#name)) { update_##name(); }\

extern ScriptSettings settings;
extern std::string settingsGeneralFile;
extern std::string skinDir;
extern std::vector<std::string> skins;
extern int currSkinIndex;

extern NativeMenu::Menu menu;

extern ScriptSettings settings;

extern SpeedoInfo currentSpeedo;


///////////////////////////////////////////////////////////////////////////////
//                             Menu stuff
///////////////////////////////////////////////////////////////////////////////
void menuInit() {
    onMenuOpen();
}

void menuClose() {
    settings.SaveGeneral();
    settings.SaveSkin(Paths::GetModuleFolder(Paths::GetOurModuleHandle()) + modDir + skinDir, currentSpeedo);
}

void update_mainmenu() {
    menu.Title("Speedometer");
    menu.Subtitle("~b~" + std::string(DISPLAY_VERSION) + "~w~");
    menu.BoolOption("Enable", settings.Enable);

    int currUnit = (int)settings.Unit;
    if (menu.StringArray("Units", { "km/h", "mph" }, currUnit)) {
        if (currUnit != (int)settings.Unit) {
            settings.Unit = (UnitType)currUnit;
        }
    }

    menu.BoolOption("Hide in first person view", settings.HideInFPV);
    menu.BoolOption("Hide on vehicle name", settings.HideOnVehicleName,
        { "Hides speedometer when vehicle name is on HUD." });
    menu.BoolOption("Hide area name", settings.HideAreaName,
        { "Hides area and street name when speedometer is visible." });

    menu.BoolOption("Use physical speed", settings.PhysicalSpeed,
        { "When turned on, shows actual (GPS) speed instead of speed from the wheels." });

    menu.FloatOption("Fade speed", settings.FadeSpeed, 0.0f, 1.0f, 0.005f,
        { "How fast the speedometer fades in and fades out." });

    menu.MenuOption("Skin options and placements", "skinmenu");

    if (menu.Option("Reload settings")) {
        settings.Read();
    }
}

void update_skinmenu() {
    menu.Title("Skin options");
    menu.Subtitle(DISPLAY_VERSION);

    if (menu.StringArray("Current skin", skins, currSkinIndex)) {
        changeSkin(skins[currSkinIndex]);
    }

    menu.MenuOption("Placements", "placementmenu");

    if (currentSpeedo.ExtraHUDComponents) {
        menu.MenuOption("Extra components", "extramenu");
    }
    else {
        menu.Option("~m~No extra components", { "This skin does not contain extra components." });
    }
}

void update_extramenu() {
    menu.Title("Drag");
    menu.Subtitle(DISPLAY_VERSION);

    menu.FloatOption("HeatNumXpos", currentSpeedo.HeatNumXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("HeatNumYpos", currentSpeedo.HeatNumYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("HeatNumSize", currentSpeedo.HeatNumSize, 0.0f, 1.0f, 0.001f);

    menu.FloatOption("HeatAlertXpos", currentSpeedo.HeatAlertXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("HeatAlertYpos", currentSpeedo.HeatAlertYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("HeatAlertSize", currentSpeedo.HeatAlertSize, 0.0f, 1.0f, 0.001f);

    menu.FloatOption("GearBgXpos", currentSpeedo.GearBgXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("GearBgYpos", currentSpeedo.GearBgYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("GearBgSize", currentSpeedo.GearBgSize, 0.0f, 1.0f, 0.001f);

    menu.FloatOption("SpeedBgXpos", currentSpeedo.SpeedBgXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("SpeedBgYpos", currentSpeedo.SpeedBgYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("SpeedBgSize", currentSpeedo.SpeedBgSize, 0.0f, 1.0f, 0.001f);

    menu.FloatOption("HeatSize", currentSpeedo.HeatSize[0], 0.0f, 1.0f, 0.001f);
    for (int i = 1; i < numDragHeat; i++) {
        currentSpeedo.HeatSize[i] = currentSpeedo.HeatSize[0];
    }
    for (int i = 0; i < numDragHeat; i++) {
        menu.FloatOption("Heat" + std::to_string(i) + "Xpos", currentSpeedo.HeatXpos[i], 0.0f, 1.0f, 0.001f);
        menu.FloatOption("Heat" + std::to_string(i) + "Ypos", currentSpeedo.HeatYpos[i], 0.0f, 1.0f, 0.001f);
    }
}

void update_placementmenu() {
    menu.Title("Placements");
    menu.Subtitle(DISPLAY_VERSION);

    menu.FloatOption("OffsetX", currentSpeedo.SpeedoXpos, -1.0f, 1.0f, 0.005f);
    menu.FloatOption("OffsetY", currentSpeedo.SpeedoYpos, -1.0f, 1.0f, 0.005f);

    menu.MenuOption("RPM", "rpmposmenu");
    menu.MenuOption("Turbo", "turboposmenu");
    menu.MenuOption("Speed", "speedposmenu");
    menu.MenuOption("Gear", "gearposmenu");
    menu.MenuOption("NOS", "nosposmenu");
    menu.MenuOption("Rotations", "rotationsmenu");

    //if (menu.Option("Normalize speedo")) {
    //	settings.Normalize(currentSpeedo);
    //}
}

void update_rpmposmenu() {
    menu.Title("RPM");
    menu.Subtitle(DISPLAY_VERSION);
    menu.FloatOption("RPMBgXpos", currentSpeedo.RPMBgXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("RPMBgYpos", currentSpeedo.RPMBgYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("RPMBgSize", currentSpeedo.RPMBgSize, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("RPMNumXpos", currentSpeedo.RPMNumXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("RPMNumYpos", currentSpeedo.RPMNumYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("RPMNumSize", currentSpeedo.RPMNumSize, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("RPMDialXpos", currentSpeedo.RPMDialXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("RPMDialYpos", currentSpeedo.RPMDialYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("RPMDialSize", currentSpeedo.RPMDialSize, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("RPMRedXpos", currentSpeedo.RPMRedXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("RPMRedYpos", currentSpeedo.RPMRedYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("RPMRedSize", currentSpeedo.RPMRedSize, 0.0f, 1.0f, 0.001f);
}

void update_turboposmenu() {
    menu.Title("Turbo");
    menu.Subtitle(DISPLAY_VERSION);
    menu.FloatOption("TurboBgXpos", currentSpeedo.TurboBgXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboBgYpos", currentSpeedo.TurboBgYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboBgSize", currentSpeedo.TurboBgSize, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboNumXpos", currentSpeedo.TurboNumXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboNumYpos", currentSpeedo.TurboNumYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboNumSize", currentSpeedo.TurboNumSize, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboTextXpos", currentSpeedo.TurboTextXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboTextYpos", currentSpeedo.TurboTextYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboTextSize", currentSpeedo.TurboTextSize, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboDialXpos", currentSpeedo.TurboDialXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboDialYpos", currentSpeedo.TurboDialYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboDialSize", currentSpeedo.TurboDialSize, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboRed0Xpos", currentSpeedo.TurboRed0Xpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboRed0Ypos", currentSpeedo.TurboRed0Ypos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboRed0Size", currentSpeedo.TurboRed0Size, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboRed1Xpos", currentSpeedo.TurboRed1Xpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboRed1Ypos", currentSpeedo.TurboRed1Ypos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboRed1Size", currentSpeedo.TurboRed1Size, 0.0f, 1.0f, 0.001f);
}

void update_speedposmenu() {
    menu.Title("Speed");
    menu.Subtitle(DISPLAY_VERSION);
    menu.FloatOption("SpeedXpos", currentSpeedo.SpeedXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("SpeedYpos", currentSpeedo.SpeedYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("SpeedSize", currentSpeedo.SpeedSize, 0.0f, 1.0f, 0.001f);

    menu.FloatOption("UnitXpos", currentSpeedo.UnitXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("UnitYpos", currentSpeedo.UnitYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("UnitSize", currentSpeedo.UnitSize, 0.0f, 1.0f, 0.001f);
}

void update_gearposmenu() {
    menu.Title("Gear");
    menu.Subtitle(DISPLAY_VERSION);
    menu.FloatOption("GearXpos", currentSpeedo.GearXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("GearYpos", currentSpeedo.GearYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("GearSize", currentSpeedo.GearSize, 0.0f, 1.0f, 0.001f);

    menu.FloatOption("ShiftLightXpos", currentSpeedo.ShiftLightXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("ShiftLightYpos", currentSpeedo.ShiftLightYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("ShiftLightSize", currentSpeedo.ShiftLightSize, 0.0f, 1.0f, 0.001f);
}

void update_nosposmenu() {
    menu.Title("NOS");
    menu.Subtitle(DISPLAY_VERSION);

    menu.FloatOption("NOSTextXpos", currentSpeedo.NOSTextXpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("NOSTextYpos", currentSpeedo.NOSTextYpos, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("NOSTextSize", currentSpeedo.NOSTextSize, 0.0f, 1.0f, 0.001f);

    menu.FloatOption("NOS0Stage1Size", currentSpeedo.NOSStage1Size[0], 0.0f, 1.0f, 0.001f);
    menu.FloatOption("NOS0Stage2Size", currentSpeedo.NOSStage2Size[0], 0.0f, 1.0f, 0.001f);
    menu.FloatOption("NOS0Stage3Size", currentSpeedo.NOSStage3Size[0], 0.0f, 1.0f, 0.001f);
    for (int i = 1; i < numNOSItemsStage1; i++) {
        currentSpeedo.NOSStage1Size[i] = currentSpeedo.NOSStage1Size[0];
    }
    for (int i = 1; i < numNOSItemsStage2; i++) {
        currentSpeedo.NOSStage2Size[i] = currentSpeedo.NOSStage2Size[0];
    }
    for (int i = 1; i < numNOSItemsStage3; i++) {
        currentSpeedo.NOSStage3Size[i] = currentSpeedo.NOSStage3Size[0];
    }

    for (int i = 0; i < numNOSItemsStage1; i++) {
        menu.FloatOption("NOS" + std::to_string(i) + "Xpos", currentSpeedo.NOSStage1Xpos[i], 0.0f, 1.0f, 0.001f);
        menu.FloatOption("NOS" + std::to_string(i) + "Ypos", currentSpeedo.NOSStage1Ypos[i], 0.0f, 1.0f, 0.001f);
    }
    for (int i = 0; i < numNOSItemsStage2; i++) {
        menu.FloatOption("NOS" + std::to_string(i) + "Xpos", currentSpeedo.NOSStage2Xpos[i], 0.0f, 1.0f, 0.001f);
        menu.FloatOption("NOS" + std::to_string(i) + "Ypos", currentSpeedo.NOSStage2Ypos[i], 0.0f, 1.0f, 0.001f);
    }
    for (int i = 0; i < numNOSItemsStage3; i++) {
        menu.FloatOption("NOS" + std::to_string(i) + "Xpos", currentSpeedo.NOSStage3Xpos[i], 0.0f, 1.0f, 0.001f);
        menu.FloatOption("NOS" + std::to_string(i) + "Ypos", currentSpeedo.NOSStage3Ypos[i], 0.0f, 1.0f, 0.001f);
    }
}

void update_rotationsmenu() {
    menu.Title("Rotate");
    menu.Subtitle(DISPLAY_VERSION);
    menu.FloatOption("RPMDialCenterX", currentSpeedo.RPMDialCenterX, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("RPMDialCenterY", currentSpeedo.RPMDialCenterY, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("RPMDialZeroRot", currentSpeedo.RPMDialZeroRot, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("RPMDialFullRot", currentSpeedo.RPMDialFullRot, 0.0f, 1.0f, 0.001f);

    menu.FloatOption("TurboDialCenterX", currentSpeedo.TurboDialCenterX, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboDialCenterY", currentSpeedo.TurboDialCenterY, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboDialZeroRot", currentSpeedo.TurboDialZeroRot, 0.0f, 1.0f, 0.001f);
    menu.FloatOption("TurboDialFullRot", currentSpeedo.TurboDialFullRot, 0.0f, 1.0f, 0.001f);
}

// These {} after PROCESS_SUBMENU are just visual, there's no
// actual nesting/scoping going on.
void update_menu() {
    menu.CheckKeys();

    PROCESS_SUBMENU(mainmenu); {
        PROCESS_SUBMENU(skinmenu); {
            PROCESS_SUBMENU(placementmenu); {
                PROCESS_SUBMENU(rpmposmenu);
                PROCESS_SUBMENU(turboposmenu);
                PROCESS_SUBMENU(speedposmenu);
                PROCESS_SUBMENU(gearposmenu);
                PROCESS_SUBMENU(nosposmenu);
                PROCESS_SUBMENU(rotationsmenu);
            }
            PROCESS_SUBMENU(extramenu);
        }
    }

    menu.EndMenu();
}
