## **NOT FINISHED, WORK IN PROGRESS**

### TODO

- Activate the kick when the player is banned and try to connect
- Fix the admin checking, not working
- Fix the unban, not working (the file is not override)
- Create a PrintToChat function
- Create a findPlayerByName

### COMMANDS

mm_ban `"[U:1:58669676]"` TIME_IN_MINUTES

mm_kick `"[U:1:58669676]"`

mm_unban `"[U:1:58669676]"`

### CONFIG FILES

On folder /addons/configs/mm_admin/ create these files:

admin.ini
```
"Config"
{
	"[U:1:58669676]" "true"
}
```

bans.ini

```
"Config"
{

}
```

### BUILD
Like another plugin :)

------------


##### **Thanks to cs2fixes for PlayerManager ^^**
