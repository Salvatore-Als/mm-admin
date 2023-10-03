#include "mm_admin.h"
#include "iserver.h"
#include <string>
#include "abstract.h"

#include "playermanager.h"
#include "filemanager.h"

void Debug(const char *msg, ...)
{
	va_list args;
	va_start(args, msg);

	char buf[1024] = {};
	V_vsnprintf(buf, sizeof(buf) - 1, msg, args);

	META_CONPRINTF("%s\n", buf);

	va_end(args);
}

void PrintToChat(MMPlayer *player, const char *msg)
{
	if (player == nullptr)
	{
		return;
	}

	Debug(msg);

	// TODO: need to find the way
}

SH_DECL_HOOK5_void(IServerGameClients, ClientDisconnect, SH_NOATTRIB, 0, CPlayerSlot, int, const char *, uint64, const char *);
SH_DECL_HOOK6_void(IServerGameClients, OnClientConnected, SH_NOATTRIB, 0, CPlayerSlot, const char *, uint64, const char *, const char *, bool);

MMAdmin g_MMAdmin;

IServerGameClients *g_gameClients = NULL;
IVEngineServer *g_engine = NULL;
ICvar *g_iCvar = NULL;
IFileSystem *g_fileSystem = NULL;
CPlayerManager *g_playerManager = NULL;
CFileManager *g_fileManager = NULL;

PLUGIN_EXPOSE(MMAdmin, g_MMAdmin);
bool MMAdmin::Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();

	GET_V_IFACE_ANY(GetServerFactory, g_gameClients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);
	GET_V_IFACE_CURRENT(GetEngineFactory, g_engine, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
	GET_V_IFACE_CURRENT(GetEngineFactory, g_iCvar, ICvar, CVAR_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetFileSystemFactory, g_fileSystem, IFileSystem, FILESYSTEM_INTERFACE_VERSION);

	SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientDisconnect, g_gameClients, this, &MMAdmin::Hook_ClientDisconnect, true);
	SH_ADD_HOOK_MEMFUNC(IServerGameClients, OnClientConnected, g_gameClients, this, &MMAdmin::Hook_OnClientConnected, false);

	g_playerManager = new CPlayerManager();
	g_fileManager = new CFileManager();

	g_pCVar = g_iCvar;
	ConVar_Register(FCVAR_RELEASE | FCVAR_CLIENT_CAN_EXECUTE | FCVAR_GAMEDLL);

	Debug("- MM Admin loaded \n");

	return true;
}

bool MMAdmin::Unload(char *error, size_t maxlen)
{
	SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, ClientDisconnect, g_gameClients, this, &MMAdmin::Hook_ClientDisconnect, true);
	SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, OnClientConnected, g_gameClients, this, &MMAdmin::Hook_OnClientConnected, false);

	return true;
}

void MMAdmin::AllPluginsLoaded()
{
}

void MMAdmin::Hook_OnClientConnected(CPlayerSlot slot, const char *pszName, uint64 xuid, const char *pszNetworkID, const char *pszAddress, bool bFakePlayer)
{
	g_playerManager->OnClientConnected(slot, pszNetworkID);
}

void MMAdmin::Hook_ClientDisconnect(CPlayerSlot slot, int reason, const char *pszName, uint64 xuid, const char *pszNetworkID)
{
	g_playerManager->OnClientDisconnect(slot);
}

CON_COMMAND_EXTERN(mm_ban, Command_Ban, "Allow to ban a player");
void Command_Ban(const CCommandContext &context, const CCommand &args)
{
	CPlayerSlot slot = context.GetPlayerSlot();
	MMPlayer *player = g_playerManager->getPlayer(slot);

	if (player == nullptr)
	{
		return;
	}

	if (!player->IsAdmin())
	{
		PrintToChat(player, DENIED_REPLY);
		return;
	}

	MMPlayer *target = g_playerManager->getPlayer(atoi(args[1]));
	if (target == nullptr)
	{
		PrintToChat(player, PLAYER_NOUT_FOUND_REPLY);
		return;
	}

	g_playerManager->Ban(target, atoi(args[2]));
	PrintToChat(player, BAN_REPLY);
}

CON_COMMAND_EXTERN(mm_unban, Command_UnBan, "Allow to unban a player");
void Command_UnBan(const CCommandContext &context, const CCommand &args)
{
	CPlayerSlot slot = context.GetPlayerSlot();
	MMPlayer *player = g_playerManager->getPlayer(slot);

	if (player == nullptr)
	{
		return;
	}

	if (!player->IsAdmin())
	{
		PrintToChat(player, DENIED_REPLY);
		return;
	}

	auto authId = args[1];

	bool isBanned = g_playerManager->IsBanned(authId);
	if (!isBanned)
	{
		PrintToChat(player, PLAYER_NOT_BAN_REPLY);
		return;
	}

	g_playerManager->UnBan(authId);
	PrintToChat(player, UNBAN_REPLY);
}

CON_COMMAND_EXTERN(mm_kick, Command_Kick, "Allow to kick a player");
void Command_Kick(const CCommandContext &context, const CCommand &args)
{
	CPlayerSlot slot = context.GetPlayerSlot();
	MMPlayer *player = g_playerManager->getPlayer(slot);

	if (player == nullptr)
	{
		return;
	}

	if (!player->IsAdmin())
	{
		PrintToChat(player, DENIED_REPLY);
		return;
	}

	MMPlayer *target = g_playerManager->getPlayer(atoi(args[1]));
	if (target == nullptr)
	{
		PrintToChat(player, PLAYER_NOUT_FOUND_REPLY);
		return;
	}

	g_playerManager->Kick(target);
	PrintToChat(player, KICK_REPLY);
}

// ------

bool MMAdmin::Pause(char *error, size_t maxlen)
{
	return true;
}

bool MMAdmin::Unpause(char *error, size_t maxlen)
{
	return true;
}

const char *MMAdmin::GetLicense()
{
	return "Public Domain";
}

const char *MMAdmin::GetVersion()
{
	return "1.0.0.0";
}

const char *MMAdmin::GetDate()
{
	return __DATE__;
}

const char *MMAdmin::GetLogTag()
{
	return "MM Admin";
}

const char *MMAdmin::GetAuthor()
{
	return "Kriax";
}

const char *MMAdmin::GetDescription()
{
	return "Simple MM administration manager";
}

const char *MMAdmin::GetName()
{
	return "MM Admin";
}

const char *MMAdmin::GetURL()
{
	return "https://kriax.ovh";
}