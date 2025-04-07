MagmaHideout_3F_2R_MapScripts::
	.byte 0

MagmaHideout_3F_2R_EventScript_Grunt10::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_10, MagmaHideout_3F_2R_Text_Grunt10Intro, MagmaHideout_3F_2R_Text_Grunt10Defeat
	msgbox MagmaHideout_3F_2R_Text_Grunt10PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_2R_Text_Grunt10Intro:
    .string "我明白头儿所说的话。\n但你知道吗？\p挖掘太古时期的宝可梦\n以及抢夺别人的陨石\l这种事…\p我觉得有些过分。\n你怎么想？$"

MagmaHideout_3F_2R_Text_Grunt10Defeat:
    .string "嗯，我们确实做错了\n一些事情。$"

MagmaHideout_3F_2R_Text_Grunt10PostBattle:
    .string "说实话，输给你后我的大脑清醒了许多，\p下次见到老大的时候，\n我会找他谈谈的。$"

