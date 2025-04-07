SeafloorCavern_Room1_MapScripts::
	.byte 0

SeafloorCavern_Room1_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_1, SeafloorCavern_Room1_Text_Grunt1Intro, SeafloorCavern_Room1_Text_Grunt1Defeat
	msgbox SeafloorCavern_Room1_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room1_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_2, SeafloorCavern_Room1_Text_Grunt2Intro, SeafloorCavern_Room1_Text_Grunt2Defeat
	msgbox SeafloorCavern_Room1_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room1_Text_Grunt1Intro:
    .string "小孩子可不要在这儿乱逛！\n快回家去吧！$"

SeafloorCavern_Room1_Text_Grunt1Defeat:
    .string "该回家的是我…$"

SeafloorCavern_Room1_Text_Grunt1PostBattle:
    .string "真希望能晋升，这样就可以\n指挥小杂鱼们了…$"

SeafloorCavern_Room1_Text_Grunt2Intro:
    .string "那潜水艇…里面太小了。\n挤得真难受！$"

SeafloorCavern_Room1_Text_Grunt2Defeat:
    .string "失败让我更难受！$"

SeafloorCavern_Room1_Text_Grunt2PostBattle:
    .string "我们抢来的那潜水艇，天哪，\n坐起来太难受了。\l所有人都挤在一起！$"

