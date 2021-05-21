#pragma once

#include <inc/natives.h>
#include <inc/main.h>
#include <inc/types.h>

#include <string>

#define DISPLAY_VERSION "v0.0.8"
const std::string modDir = "\\iktSpeedo";

class ScriptSettings;

void ScriptMain();
void update_menu();
void menuInit();
void menuClose();
void onMenuOpen();
void changeSkin(std::string skinTemp);
