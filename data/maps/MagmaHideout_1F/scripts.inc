MagmaHideout_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MagmaHideout_1F_OnTransition
	.byte 0

MagmaHideout_1F_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 0
	end

MagmaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_1, MagmaHideout_1F_Text_Grunt1Intro, MagmaHideout_1F_Text_Grunt1Defeat
	msgbox MagmaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_2, MagmaHideout_1F_Text_Grunt2Intro, MagmaHideout_1F_Text_Grunt2Defeat
	msgbox MagmaHideout_1F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_Text_Grunt1Intro:
    .string "当火岩队点名布置任务的时候，\n我们按照排队的顺序各自领到\l重要性不同的守卫任务。\p所以我才被安排到这个角落里，\n因为我点名的时候总是晚一步！$"

MagmaHideout_1F_Text_Grunt1Defeat:
    .string "我的训练也\n总是晚一步！\p不得不承认，我很弱…$"

MagmaHideout_1F_Text_Grunt1PostBattle:
    .string "好吧，我以后做事\n会尽量认真一点的…$"

MagmaHideout_1F_Text_Grunt2Intro:
    .string "我们头儿叫我们挖掘烟囱山，\n所以我们挖了半天。\p在挖的过程中，我们\n发现了一些不可思议的东西！\p究竟是什么？\p哇哈哈！\n打赢我的话就告诉你！$"

MagmaHideout_1F_Text_Grunt2Defeat:
    .string "啊！\n输了！$"

MagmaHideout_1F_Text_Grunt2PostBattle:
    .string "我不会告诉你的。\n你到了那里就知道了！\p悬念要保存到最后一刻，\n不是吗？$"

