#include <filemanager.h>

bool CFileManager::IsAdminExist(const char *steamid)
{
    bool value = false;

    KeyValues *kv = new KeyValues("Config");
    kv->LoadFromFile(g_fileSystem, ADMIN_FILE);
    value = kv->GetBool(steamid);

    Debug("trying to fetch %s, value is %d", steamid, value);

    delete kv;
    return value;
}

bool CFileManager::IsBanExist(const char *steamid)
{
    bool value = false;

    KeyValues *kv = new KeyValues("Config");
    kv->LoadFromFile(g_fileSystem, BAN_FILE);

    if (kv->GetInt(steamid) > time(0))
    {
        value = true;
    }

    delete kv;
    return value;
}

void CFileManager::WriteBan(const char *steamid, int banTime)
{
    KeyValues *kv = new KeyValues("Config");
    kv->LoadFromFile(g_fileSystem, BAN_FILE);
    kv->SetInt(steamid, time(0) + (banTime * 60));
    kv->SaveToFile(g_fileSystem, BAN_FILE);
    delete kv;
}

void CFileManager::RemoveBan(const char *steamid)
{
    KeyValues *kv = new KeyValues("Config");
    kv->LoadFromFile(g_fileSystem, BAN_FILE);
    kv->SetInt(steamid, -1); // Setting -1, b'cause IDK how to remove it from the file :(
    kv->SaveToFile(g_fileSystem, BAN_FILE);
    delete kv;
}

void CFileManager::WriteLog(char log)
{
    // Boring
}