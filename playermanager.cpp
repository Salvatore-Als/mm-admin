// https://github.com/Source2ZE/CS2Fixes/blob/main/playermanager.cpp

#include "playermanager.h"

void CPlayerManager::OnClientConnected(CPlayerSlot slot, const char *pszNetworkID)
{
    Assert(m_vecPlayers[slot.Get()] == nullptr);

    m_vecPlayers[slot.Get()] = new MMPlayer();
    m_vecPlayers[slot.Get()]->SetSteamId(g_engine->GetClientSteamID(slot));
    m_vecPlayers[slot.Get()]->SetAuthId(pszNetworkID);
    m_vecPlayers[slot.Get()]->SetSlotId(slot.Get());

    if (g_fileManager->IsAdminExist(pszNetworkID))
    {
        m_vecPlayers[slot.Get()]->SetAdmin();
    }

    m_vecPlayers[slot.Get()]->Connect();

    Debug("---- Player connected ----");
    Debug("- AuthID: %s", pszNetworkID);
    Debug("- Slot: %d", slot.Get());
    Debug("- Admin: %s", m_vecPlayers[slot.Get()]->IsAdmin() ? "YES":"NO");
    Debug("---- ---------------- ----");
}

void CPlayerManager::OnClientDisconnect(CPlayerSlot slot)
{
    m_vecPlayers[slot.Get()]->Disconnect(); // Useless but just to be sure
    m_vecPlayers[slot.Get()] = nullptr;
}

void CPlayerManager::Kick(MMPlayer *player)
{
    g_engine->KickClient(player->GetSlotId(), (const char *)KICK_MSG, (char)KICK_MSG);
}

void CPlayerManager::Ban(MMPlayer *player, int time)
{
    g_fileManager->WriteBan(player->GetAuthId(), time);
    //g_engine->KickClient(player->GetSlotId(), (const char *)BAN_MSG, (char)BAN_MSG);
}

void CPlayerManager::UnBan(const char *steamid)
{
    g_fileManager->RemoveBan(steamid);
}

bool CPlayerManager::IsBanned(const char *steamid)
{
    return g_fileManager->IsBanExist(steamid);
}