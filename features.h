#pragma once
#ifndef FEATURES_H
#define FEATURES_H

#include <Windows.h>
#include <iostream>
#include "binds.h"

using namespace app;
namespace features {
	void TeleportAll(PlayerControl* localPlayer, List_1_PlayerControl_* entList);
}
#endif