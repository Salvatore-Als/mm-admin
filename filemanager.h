// https://github.com/Source2ZE/CS2Fixes/blob/main/playermanager.h

#pragma once

#include "abstract.h"
#include <string>
#include "KeyValues.h"
#include <ctime>

extern IFileSystem *g_fileSystem;

class CFileManager
{
public:
    CFileManager()
    {
    }

    bool IsAdminExist(const char *steamid);
    bool IsBanExist(const char *steamid);
    void WriteBan(const char *steamid, int banTime);
    void RemoveBan(const char *steamid);
    void WriteLog(char log);
};

extern CFileManager *g_fileManager;