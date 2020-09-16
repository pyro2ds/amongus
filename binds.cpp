#include "binds.h"

const char* globalStr = "";
GameOptionsData__Fields& binds::getGameOptionFields() {
    return PlayerControl__TypeInfo->static_fields->GameOptions->fields;
}
GameOptionsData__StaticFields*& binds::getGameOptionStaticFields() {
    return GameOptionsData__TypeInfo->static_fields;
}
PlayerControl*& binds::getLocalPlayer() {
    return PlayerControl__TypeInfo->static_fields->LocalPlayer;
}
GameData_PlayerInfo*& binds::getPlayerInfo(PlayerControl* plr) {
    auto temp = PlayerControl_get_Data(plr, NULL);
    return temp;
}


String* binds::stringCreator(uint16_t len, const char* string) {
    String* temp = String_CreateString_6(NULL, 0x30, len, NULL);
    for (int i = 0; i < len; i++) {
        *(&temp->fields.m_firstChar + i) = string[i];
    }
    return temp;
}

std::string binds::string_to_Chars(String* str) {
    std::string temp = "";
	if (!str) {
		return temp;
	}
    for (int i = 0; i < str->fields.m_stringLength; i++) {
        temp.push_back(String_get_Chars(str, i, NULL));
    }
    return temp;
}

Vector3 binds::getPlayerPos(PlayerControl* plr) {
    return Transform_get_position(Component_get_transform((Component*)plr, NULL), NULL);
}

const char* binds::getGlobalString() {
    return globalStr;
}
void binds::setGlobalString(const char* in) {
    globalStr = in;
}