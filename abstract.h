#pragma once

#define DENIED_REPLY "[Admin] You are not allowed to used this command."
#define BAN_REPLY "[Admin] Player has been banned from the server."
#define KICK_REPLY "[Admin] Player has been kicked from the server."
#define UNBAN_REPLY "[Admin] Player has been unban from the server."
#define PLAYER_NOT_BAN_REPLY "[Admin] This player is not ban from the server."
#define PLAYER_NOUT_FOUND_REPLY "[Admin] Player not found."

#define BAN_MSG "You have been banned from this server"
#define KICK_MSG "You have been kicked from this server"

#define ADMIN_FILE "addons/configs/mm_admin/admins.ini"
#define BAN_FILE "addons/configs/mm_admin/bans.ini"
#define LOG_FILE "addons/logs/mm_admin/%s.log"

#include "playermanager.h"

void Debug(const char *, ...);
void PrintToChat(MMPlayer *player, char *msg);