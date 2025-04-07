SeafloorCavern_Room4_MapScripts::
	.byte 0

SeafloorCavern_Room4_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_3, SeafloorCavern_Room4_Text_Grunt3Intro, SeafloorCavern_Room4_Text_Grunt3Defeat
	msgbox SeafloorCavern_Room4_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room4_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_4, SeafloorCavern_Room4_Text_Grunt4Intro, SeafloorCavern_Room4_Text_Grunt4Defeat
	msgbox SeafloorCavern_Room4_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room4_Text_Grunt3Intro:
    .string "你是谁？\n从哪儿进来的？$"

SeafloorCavern_Room4_Text_Grunt3Defeat:
    .string "输了…$"

SeafloorCavern_Room4_Text_Grunt3PostBattle:
    .string "我找不到出去的路了！\p别误会，我不是害怕！$"

SeafloorCavern_Room4_Text_Grunt4Intro:
    .string "你是谁？\n想上哪儿去？$"

SeafloorCavern_Room4_Text_Grunt4Defeat:
    .string "我赢不了！$"

SeafloorCavern_Room4_Text_Grunt4PostBattle:
    .string "我的搭档把地图忘在\n潜水艇上了！\p这人怎么那么没用啊？$"

