#include "framework/il2cpp-appdata.h"
#include "features.h"
using namespace binds;
void features::TeleportAll(PlayerControl* localPlayer, List_1_PlayerControl_* entList)
{
    for (int i = 0; i < 32; i++) {
        PlayerControl* iter = entList->fields._items[0].vector[i];
        if (!iter) break;
        Vector3 vec3 = getPlayerPos(iter);
        printf("x: %f, y: %f\n", vec3.x, vec3.y);
        Transform_set_position(Component_get_transform((Component*)localPlayer, NULL), vec3, NULL);
        Sleep(200);
    }
}
