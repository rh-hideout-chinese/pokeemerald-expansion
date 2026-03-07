ViridianCity_House_Frlg_MapScripts::
	.byte 0

ViridianCity_House_EventScript_BaldingMan::
	msgbox ViridianCity_House_Text_NicknamingIsFun, MSGBOX_NPC
	end

ViridianCity_House_EventScript_LittleGirl::
	msgbox ViridianCity_House_Text_MyDaddyLovesMonsToo, MSGBOX_NPC
	end

ViridianCity_House_EventScript_Speary::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SPEAROW, CRY_MODE_NORMAL
	msgbox ViridianCity_House_Text_Speary
	waitmoncry
	release
	end

ViridianCity_House_EventScript_NicknameSign::
	msgbox ViridianCity_House_Text_SpearowNameSpeary, MSGBOX_SIGN
	end

ViridianCity_House_Text_NicknamingIsFun::
	.string "想一个昵称是很有乐趣的，\n"
	.string "但是这并不容易。\p"
	.string "一个聪明的名字很美好，\n"
	.string "但是简单的名字更好记。$"

ViridianCity_House_Text_MyDaddyLovesMonsToo::
	.string "我爸爸也喜欢宝可梦。$"

ViridianCity_House_Text_Speary::
    .string "小烈：特唔$"

ViridianCity_House_Text_SpearowNameSpeary::
	.string "烈雀\n"
	.string "名字：小烈$"

