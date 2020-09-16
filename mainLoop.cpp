
#include "..\framework\il2cpp-appdata.h"
#include "..\binds.h"
#include "..\hooks.h"
#include "..\features.h"
#include "..\mainLoop.h"

#include <Windows.h>
#include <iostream>
#include <vector>
#include <io.h>

using namespace app;
using namespace binds;

Transform* trans = nullptr;
Vector3 vec3 = { 0,0,0 };
List_1_PlayerControl_* entList = nullptr;
PlayerControl* localPlayer = nullptr;
bool once = true;

void mainLoop() {
    
    if (once) { hooks::init(); once = !once; }
	//SaveManager__TypeInfo->static_fields->lastPlayerName = stringCreator(strlen(customName), customName);

    if (cheat) {
        localPlayer = getLocalPlayer();
		
		
		Sleep(50);
        if (localPlayer) {
			GameOptionsData__Fields& gameOptionsPlayer = getGameOptionFields();
			GameOptionsData__StaticFields*& gameOptionsGlobal = getGameOptionStaticFields();
			entList = PlayerControl__TypeInfo->static_fields->AllPlayerControls;
            auto player_data = *(GameData_PlayerInfo**)&localPlayer->fields.moveable;

            if (TeleportAll) {
				Sleep(2000);
                features::TeleportAll(localPlayer, entList);
				TeleportAll = !TeleportAll;
                cheat = false;
            }
            else if (impostorMode) {

                gameOptionsPlayer.KillCooldown = 0.05f;
                gameOptionsPlayer.PlayerSpeedMod = 6.0f;
                gameOptionsPlayer.KillDistance = 1000;
                gameOptionsPlayer.NumImpostors = 5;
                gameOptionsPlayer.ImpostorLightMod = 1000.0f;

                gameOptionsGlobal->KillDistances->vector[2] = 1000;
                player_data->fields.IsImpostor = 1;
                player_data->fields.IsDead = 0;
				impostorMode = !impostorMode;
			
			}


        }

    }

    if (hookPressed) {
        hook = !hook;
        hookPressed = !hookPressed;
        (hook ? MH_EnableHook(MH_ALL_HOOKS) : MH_DisableHook(MH_ALL_HOOKS));
        //std::cout << (hook ? "hook on" : "hook off") << "\n";
    }

    
}
