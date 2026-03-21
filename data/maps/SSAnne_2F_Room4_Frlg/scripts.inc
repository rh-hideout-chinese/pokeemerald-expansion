SSAnne_2F_Room4_Frlg_MapScripts::
	.byte 0

SSAnne_2F_Room4_EventScript_Lamar::
	trainerbattle_single TRAINER_GENTLEMAN_LAMAR, SSAnne_2F_Room4_Text_LamarIntro, SSAnne_2F_Room4_Text_LamarDefeat
	msgbox SSAnne_2F_Room4_Text_LamarPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_2F_Room4_EventScript_Dawn::
	trainerbattle_single TRAINER_LASS_DAWN, SSAnne_2F_Room4_Text_DawnIntro, SSAnne_2F_Room4_Text_DawnDefeat
	msgbox SSAnne_2F_Room4_Text_DawnPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_2F_Room4_Text_LamarIntro::
    .string "你认为哪个更有价值，\n"
    .string "强大的还是罕见的宝可梦？$"

SSAnne_2F_Room4_Text_LamarDefeat::
    .string "我必须问问你！$"

SSAnne_2F_Room4_Text_LamarPostBattle::
    .string "就我个人而言，我更喜欢\n"
    .string "强大和罕见的宝可梦。$"

SSAnne_2F_Room4_Text_DawnIntro::
    .string "我该不会曾在聚会上\n"
    .string "遇到过你吧？$"

SSAnne_2F_Room4_Text_DawnDefeat::
    .string "别着急！$"

SSAnne_2F_Room4_Text_DawnPostBattle::
    .string "哦，我非常喜欢你强大的宝可梦！\n"
    .string "哦，我为他们而嫉妒你！$"

