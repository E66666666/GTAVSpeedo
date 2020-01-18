/*
THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
http://dev-c.com
(C) Alexander Blade 2015
*/

#pragma once

#define DISPLAY_VERSION "v0.0.5"

#include <inc/natives.h>
#include <inc/main.h>
#include <inc/types.h>

#include <string>
const std::string modDir = "\\iktSpeedo";

class ScriptSettings;

void ScriptMain();
void update_menu();
void menuInit();
void menuClose();
void onMenuOpen();
void changeSkin(std::string skinTemp);
