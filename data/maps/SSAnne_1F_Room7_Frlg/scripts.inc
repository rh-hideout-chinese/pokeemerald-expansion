SSAnne_1F_Room7_Frlg_MapScripts::
	.byte 0

SSAnne_1F_Room7_EventScript_Thomas::
	trainerbattle_single TRAINER_GENTLEMAN_THOMAS, SSAnne_1F_Room7_Text_ThomasIntro, SSAnne_1F_Room7_Text_ThomasDefeat
	msgbox SSAnne_1F_Room7_Text_ThomasPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_1F_Room7_Text_ThomasIntro::
    .string "我是一个孤独的旅行者……\p"
    .string "我唯一的同伴和朋友\n"
    .string "只有我在旅途中抓到的宝可梦……$"

SSAnne_1F_Room7_Text_ThomasDefeat::
    .string "天哪，我的朋友……$"

SSAnne_1F_Room7_Text_ThomasPostBattle::
    .string "你应该友好的对待你的朋友！$"

