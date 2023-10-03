// https://github.com/Source2ZE/CS2Fixes/blob/main/playermanager.h

#pragma once

#include "utlvector.h"
#include <playerslot.h>
#include "platform.h"
#include "irecipientfilter.h"
#include "abstract.h"
#include "filemanager.h"

extern IVEngineServer *g_engine;
extern CFileManager *g_fileManager;

class MMPlayer
{
public:
    MMPlayer()
    {
        m_bIsAdmin = false;
        m_bIsConnected = false;
        m_slotId = -1;
    }

    bool IsAdmin() { return m_bIsAdmin; }
    void SetAdmin() { m_bIsAdmin = true; }

    // Don't use it for now, make a fucking crash ...
    uint64 GetSteamId64() { return m_SteamID->ConvertToUint64(); }
    const CSteamID *GetSteamId() { return m_SteamID; }
    void SetSteamId(const CSteamID *steamID) { m_SteamID = steamID; }

    const char *GetAuthId() { return m_szAuthId; }
    void SetAuthId(const char *authId) { m_szAuthId = authId; }

    const int GetSlotId() { return m_slotId; }
    void SetSlotId(const int slotId) { m_slotId = slotId; }

    bool isConnected() { return m_bIsConnected; }
    void Disconnect() { m_bIsConnected = false; }
    void Connect() { m_bIsConnected = true; }

private:
    bool m_bIsAdmin;
    bool m_bIsConnected;
    const CSteamID *m_SteamID;
    const char *m_szAuthId;
    int m_slotId;
};

class CPlayerManager
{
public:
    CPlayerManager()
    {
        V_memset(m_vecPlayers, 0, sizeof(m_vecPlayers));
    }

    void OnClientConnected(CPlayerSlot slot, const char *pszNetworkID);
    void OnClientDisconnect(CPlayerSlot slot);
    void Kick(MMPlayer *player);
    void Ban(MMPlayer *player, int time);
    void UnBan(const char *steamid);
    bool IsBanned(const char *steamid);

    MMPlayer *getPlayer(CPlayerSlot slot)
    {
        if (slot.Get() < 0)
        {
            return nullptr;
        }

        return m_vecPlayers[slot.Get()];
    }

private:
    MMPlayer *m_vecPlayers[65];
};

extern CPlayerManager *g_playerManager;