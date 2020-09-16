#pragma once
#include <iostream>
#include <string>
#include "framework/il2cpp-appdata.h"
#include "..\binds.h"
#include "..\hooks.h"
#include "..\features.h"
#include "..\mainLoop.h"
#ifndef GLOBALS_H
#define GLOBALS_H
extern bool cheat;
extern bool hookPressed;
extern bool hook;
extern bool impostorMode;
extern bool TeleportAll;
extern char customText[2048];
extern char customName[2048];
#endif