#include "hooks.h"

typedef void(__cdecl* rpcsetinfected)(PlayerControl*, GameData_PlayerInfo__Array*, MethodInfo*);
typedef void(__cdecl* SetInfected)(PlayerControl*, Byte__Array*, MethodInfo*);
typedef void(__cdecl* RpcSetName)(PlayerControl*, String*, MethodInfo*);
typedef bool(__cdecl* RpcSendChat)(PlayerControl*, String*, MethodInfo*);
typedef void(__cdecl* chatsendcontrol)(ChatController*, MethodInfo*);
typedef void(__cdecl* shipselectinfected)(ShipStatus*, MethodInfo*);
typedef void(__cdecl* setname)(PlayerControl*, String*, MethodInfo*);
typedef GameData_PlayerInfo*(__cdecl* getHost)(GameData*, MethodInfo*);
typedef ClientData*(__cdecl* get_gameinfo)(InnerNetClient*, int32_t, MethodInfo*);
typedef String*(__cdecl* get_gamename)(int32_t, MethodInfo*);
typedef ClientData *(__cdecl* findclient)(InnerNetClient *, int32_t, MethodInfo *);
typedef bool*(__cdecl* getAmhost)(InnerNetClient *, MethodInfo*);
typedef void*(__cdecl* checkName)(PlayerControl*, String*, MethodInfo*);
typedef void*(__cdecl* checkName2)(PlayerControl*, String*, MethodInfo*);
typedef void*(__cdecl* messagewrite_write_6)(MessageWriter*, String*, MethodInfo*);
typedef void*(__cdecl* messagewrite_write_bs)(MessageWriter*, Byte__Array*, MethodInfo*);
typedef void*(__cdecl* pc_handlerpc)(PlayerControl* pc, uint8_t callid, MessageReader *reader, MethodInfo *method);

rpcsetinfected fpPlayerControl_RpcSetInfected = nullptr;
SetInfected fpPlayerControl_SetInfected = nullptr;
RpcSetName fpPlayerControl_RpcSetName = nullptr;
setname fpPlayerControl_SetName = nullptr;
RpcSendChat fpPlayerControl_RpcSendChat = nullptr;
chatsendcontrol fpChatController_SendChat = nullptr;
shipselectinfected fpShipStatus_SelectInfected = nullptr;
getHost fpGameData_GetHost = nullptr;
get_gameinfo fpInnerNetClient_GetOrCreateClient = nullptr;
get_gamename fpGameCode_IntToGameName = nullptr;
findclient fpInnerNetClient_FindClientById = nullptr;
getAmhost fpInnerNetClient_get_AmHost = nullptr;
checkName fpPlayerControl_CmdCheckName = nullptr;
checkName2 fpPlayerControl_CheckName = nullptr;
messagewrite_write_6 fpMessageWriter_Write_6 = nullptr;
messagewrite_write_bs fpMessageWriter_WriteBytesAndSize = nullptr;
pc_handlerpc fpPlayerControl_HandleRpc = nullptr;

void __cdecl hooks::hkPlayerControl_RpcSetInfected(PlayerControl * pc, GameData_PlayerInfo__Array * infected, MethodInfo * method) {
    for (int i = 0; i < infected->max_length; i++) {
        std::cout << infected->vector[i]->fields.IsImpostor
            << ":"
            << string_to_Chars(infected->vector[i]->fields.PlayerName)
            << "\n";
       
    }

    fpPlayerControl_RpcSetInfected(pc, infected, method);
    return;
}

void __cdecl hooks::hkPlayerControl_SetInfected(PlayerControl* pc, Byte__Array* infected, MethodInfo* method) {
    pc = getLocalPlayer();
    fpPlayerControl_SetInfected(pc, infected, method);
    return;
}

void __cdecl hooks::hkPlayerControl_RpcSetName(PlayerControl* pc, String* name, MethodInfo* method) {
    fpPlayerControl_RpcSetName(pc, name, method);
    return;
}


bool __cdecl hooks::hkPlayerControl_RpcSendChat(PlayerControl* pc, String* chatText, MethodInfo* method) {
    char str[2048];
    strcpy_s(str, customText);
    std::cout << "from rpcsendchat " << str << "\n";
    String* custName = stringCreator(strlen(str), str);
    chatText = custName;
    fpPlayerControl_RpcSendChat(pc, chatText, NULL);
    return true;
}

void __cdecl hooks::hkChatController_SendChat(ChatController* cc, MethodInfo* method) {
    std::cout << "hooked from chatController" << "\n";
    cc->fields.TimeSinceLastMessage = 3.05f;
    fpChatController_SendChat(cc, method);
    return;
}

void __cdecl hooks::ShipStatus_SelectInfected(ShipStatus *ship, MethodInfo *method) {
	
	fpShipStatus_SelectInfected(ship, method);
	return;
}
void __cdecl hooks::hkPlayerControl_SetName(PlayerControl *pc, String *name, MethodInfo *method) {
	String* newName = stringCreator(5, "userg");
	fpPlayerControl_SetName(pc, name, method);
	return;
}

GameData_PlayerInfo *hooks::hkGameData_GetHost(GameData *gd, MethodInfo *method) {
	return PlayerControl_get_Data(getLocalPlayer(), 0);
}

ClientData * hooks::hkInnerNetClient_GetOrCreateClient(InnerNetClient *innernet, int32_t clientId, MethodInfo *method) {
	ClientData* temp = fpInnerNetClient_GetOrCreateClient(innernet, clientId, method);
	//std::cout << "HOOKED FROM innernetclient getOrCreateClient" << "\n";
	if (temp) {
		if (temp->fields.Character) {
			GameData_PlayerInfo* temp_data = PlayerControl_get_Data(temp->fields.Character, NULL);
			std::cout << temp->fields.Character->fields.PlayerId << "\n";
			if (temp_data) {
				std::cout << string_to_Chars(temp_data->fields.PlayerName) << (temp_data->fields.IsImpostor ? "is the impostor" : "is not the impostor") << "\n";
			}
		}
	}
	return temp;
}
String *hooks::hkGameCode_IntToGameName(int32_t gameId, MethodInfo *method) {
	String* gameName = fpGameCode_IntToGameName(gameId, method);
	//std::cout << string_to_Chars(gameName) << "\n";
	return gameName;
}

ClientData *hooks::hkInnerNetClient_FindClientById(InnerNetClient *innernet, int32_t id, MethodInfo *method) {
	ClientData* temp = fpInnerNetClient_FindClientById(innernet, id, method);
	String* newName = stringCreator(5, "userg");
	String* playerName = nullptr;
	//std::cout << "hkInnerNetClient_FindClientById  " << "\n";
	if (temp) {
		if (temp->fields.Character) {
			GameData_PlayerInfo* temp_data = PlayerControl_get_Data(temp->fields.Character, NULL);
			if (temp_data) playerName = temp_data->fields.PlayerName;
			if (playerName) {
				std::cout << string_to_Chars(playerName) << "\n";
				//temp_data->fields.PlayerName = newName;
			}
		}
	}

	return temp;
}

bool hooks::hkInnerNetClient_get_AmHost(InnerNetClient *innernet, MethodInfo *method) {
	std::cout << "get_AmHost called" << "\n";
	return true;
}

void hooks::hkPlayerControl_CmdCheckName(PlayerControl *pc, String *name, MethodInfo *method) {
	if(name) std::cout << string_to_Chars(name) << "\n";
	return;
}
void hooks::hkPlayerControl_CheckName(PlayerControl *pc, String *name, MethodInfo *method) {
	if(name) std::cout << string_to_Chars(name) << "\n";
	return;
}
void hooks::hkMessageWriter_Write_6(MessageWriter *mw, String *value, MethodInfo *method) {
	String* newName = stringCreator(strlen(customName), customName);
	if (value){
		if (string_to_Chars(value) == "nbot5" || value == newName){
			value = newName;
		}
		std::cout << string_to_Chars(value) << "\n";
	}
	fpMessageWriter_Write_6(mw, value, method);
	return;
}

void hooks::hkMessageWriter_WriteBytesAndSize(MessageWriter *mw, Byte__Array *bytes, MethodInfo *method) {
	
	if (bytes) {
		//printf("\n");
		for (int i = 0; i < bytes->max_length; i++) {
			//printf("%x ", bytes->vector[i]);
		}
	}
	fpMessageWriter_WriteBytesAndSize(mw, bytes, method);
	return;
}

void hooks::hkPlayerControl_HandleRpc(PlayerControl *pc, uint8_t callId, MessageReader *reader, MethodInfo *method) {
	printf("CALL ID: %d from HandleRpc\n", callId);
	if (callId == 0x4 && pc == getLocalPlayer()) {
		return;
	}
	if (pc == getLocalPlayer() && callId == 0x12)
		printf("u murder\n");
		fpPlayerControl_HandleRpc(pc, 0x3, reader, method);
	fpPlayerControl_HandleRpc(pc, callId, reader, method);
	return;
}
void hooks::init() { // ...
    MH_Initialize();

    MH_STATUS rpcSetInfectedHook = MH_CreateHook(
        PlayerControl_RpcSetInfected,
        hooks::hkPlayerControl_RpcSetInfected,
        reinterpret_cast<LPVOID*>(&fpPlayerControl_RpcSetInfected)
	);

    MH_STATUS setInfected = MH_CreateHook(
        app::PlayerControl_SetInfected,
        hooks::hkPlayerControl_SetInfected,
        reinterpret_cast<LPVOID*>(&fpPlayerControl_SetInfected)
	);

    MH_STATUS RpcSetName = MH_CreateHook(
        app::PlayerControl_RpcSetName,
        hooks::hkPlayerControl_RpcSetName,
        reinterpret_cast<LPVOID*>(&fpPlayerControl_RpcSetName)
	);

    MH_STATUS RpcSendChat = MH_CreateHook(
        app::PlayerControl_RpcSendChat,
        hooks::hkPlayerControl_RpcSendChat,
        reinterpret_cast<LPVOID*>(&fpPlayerControl_RpcSendChat)
	);

    MH_STATUS chatcontrollerSend = MH_CreateHook(
        app::ChatController_SendChat,
        hooks::hkChatController_SendChat,
        reinterpret_cast<LPVOID*>(&fpChatController_SendChat)
	);

	MH_STATUS SetNameL = MH_CreateHook(
		app::PlayerControl_SetName,
		hooks::hkPlayerControl_SetName,
		reinterpret_cast<LPVOID*>(&fpPlayerControl_SetName)
	);

	MH_STATUS GetHost = MH_CreateHook(
		app::GameData_GetHost,
		hooks::hkGameData_GetHost,
		reinterpret_cast<LPVOID*>(&fpGameData_GetHost)
	);
	MH_STATUS GetGameName = MH_CreateHook(
		app::InnerNetClient_GetOrCreateClient,
		hooks::hkInnerNetClient_GetOrCreateClient,
		reinterpret_cast<LPVOID*>(&fpInnerNetClient_GetOrCreateClient)
	); 	
	MH_STATUS GetGameNamev2 = MH_CreateHook(
		app::GameCode_IntToGameName,
		hooks::hkGameCode_IntToGameName,
		reinterpret_cast<LPVOID*>(&fpGameCode_IntToGameName)
	); 	
	MH_STATUS findclient = MH_CreateHook(
		app::InnerNetClient_FindClientById,
		hooks::hkInnerNetClient_FindClientById,
		reinterpret_cast<LPVOID*>(&fpInnerNetClient_FindClientById)
	); 		
	MH_STATUS checkname = MH_CreateHook(
		app::PlayerControl_CmdCheckName,
		hooks::hkPlayerControl_CmdCheckName,
		reinterpret_cast<LPVOID*>(&fpPlayerControl_CmdCheckName)
	); 	
	MH_STATUS checkname2 = MH_CreateHook(
		app::PlayerControl_CheckName,
		hooks::hkPlayerControl_CheckName,
		reinterpret_cast<LPVOID*>(&fpPlayerControl_CheckName)
	); 	
	MH_STATUS mw_write_6 = MH_CreateHook(
		app::MessageWriter_Write_6,
		hooks::hkMessageWriter_Write_6,
		reinterpret_cast<LPVOID*>(&fpMessageWriter_Write_6)
	); 		
	MH_STATUS mw_write_bs = MH_CreateHook(
		app::MessageWriter_WriteBytesAndSize,
		hooks::hkMessageWriter_WriteBytesAndSize,
		reinterpret_cast<LPVOID*>(&fpMessageWriter_WriteBytesAndSize)
	); 	
	MH_STATUS handleRpcPc = MH_CreateHook(
		app::PlayerControl_HandleRpc,
		hooks::hkPlayerControl_HandleRpc,
		reinterpret_cast<LPVOID*>(&fpPlayerControl_HandleRpc)
	); 	
	//MH_STATUS get_amhost = MH_CreateHook(
	//	app::InnerNetClient_get_AmHost,
	//	hooks::hkInnerNetClient_get_AmHost,
	//	reinterpret_cast<LPVOID*>(&fpInnerNetClient_get_AmHost)
	//); 
	
}

void hooks::end() {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}