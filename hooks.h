#pragma once
#include "..\framework\il2cpp-appdata.h"
#include "..\binds.h"
#include "..\features.h"
#include "..\include\MinHook.h"
#include "..\global.h"
#pragma comment(lib, "libMinHook.x86.lib")
using namespace binds;
using namespace app;




namespace hooks {
    
    void init();
    void end();
    void __cdecl hkPlayerControl_RpcSetInfected(PlayerControl* pc, GameData_PlayerInfo__Array* infected, MethodInfo* method);
    void __cdecl hkPlayerControl_SetInfected(PlayerControl* pc, Byte__Array* infected, MethodInfo* method);
    void __cdecl hkPlayerControl_RpcSetName(PlayerControl* pc, String* name, MethodInfo* method);
    bool __cdecl hkPlayerControl_RpcSendChat(PlayerControl* pc, String* chatText, MethodInfo* method);
    void __cdecl hkChatController_SendChat(ChatController* cc, MethodInfo* method);
	void __cdecl ShipStatus_SelectInfected(ShipStatus *ship, MethodInfo *method);
	void __cdecl hkPlayerControl_SetName(PlayerControl *pc, String *name, MethodInfo *method);
	ClientData *hkInnerNetClient_GetOrCreateClient(InnerNetClient *innernet, int32_t clientId, MethodInfo *method);
	String *hkGameCode_IntToGameName(int32_t gameId, MethodInfo *method);
	GameData_PlayerInfo *hkGameData_GetHost(GameData *gd, MethodInfo *method);
	ClientData *hkInnerNetClient_FindClientById(InnerNetClient *innernet, int32_t id, MethodInfo *method);
	bool hkInnerNetClient_get_AmHost(InnerNetClient *innernet, MethodInfo *method);
	void hkPlayerControl_CmdCheckName(PlayerControl *pc, String *name, MethodInfo *method);
	void hkPlayerControl_CheckName(PlayerControl *pc, String *name, MethodInfo *method);
	void hkMessageWriter_Write_6(MessageWriter *mw, String *value, MethodInfo *method);
	void hkMessageWriter_WriteBytesAndSize(MessageWriter *mw, Byte__Array *bytes, MethodInfo *method);
	void hkPlayerControl_HandleRpc(PlayerControl *pc, uint8_t callId, MessageReader *reader, MethodInfo *method);
}


