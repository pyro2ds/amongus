#pragma once
#ifndef BINDS_H
#define BINDS_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <vector>
#include <io.h>
#include "il2cpp-appdata.h"
#include "helpers.h"
using namespace app;
namespace binds {
    GameOptionsData__Fields& getGameOptionFields();
    GameOptionsData__StaticFields*& getGameOptionStaticFields();
    GameData_PlayerInfo*& getPlayerInfo(PlayerControl* plr);
    PlayerControl*& getLocalPlayer();

    const char* getGlobalString();
    void setGlobalString(const char* in);
    String* stringCreator(uint16_t len, const char* string);
    std::string string_to_Chars(String* str);
    Vector3 getPlayerPos(PlayerControl* plr);
}

#endif