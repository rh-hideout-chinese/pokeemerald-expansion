MagmaHideout_2F_1R_MapScripts::
	.byte 0

MagmaHideout_2F_1R_EventScript_Grunt14::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_14, MagmaHideout_2F_1R_Text_Grunt14Intro, MagmaHideout_2F_1R_Text_Grunt14Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt14PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_3, MagmaHideout_2F_1R_Text_Grunt3Intro, MagmaHideout_2F_1R_Text_Grunt3Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_4, MagmaHideout_2F_1R_Text_Grunt4Intro, MagmaHideout_2F_1R_Text_Grunt4Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_5, MagmaHideout_2F_1R_Text_Grunt5Intro, MagmaHideout_2F_1R_Text_Grunt5Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_Text_Grunt14Intro:
    .string "什么，什么，什么？\p只有火岩队\n才准进来！\p但你没穿火岩队的\n制服…\p你很可疑！\n和我对战吧！$"

MagmaHideout_2F_1R_Text_Grunt14Defeat:
    .string "哎呀呀…\n我做为火岩队成员的荣誉啊…$"

MagmaHideout_2F_1R_Text_Grunt14PostBattle:
    .string "如果你怕冷，那就加入\n火岩队吧。$"

MagmaHideout_2F_1R_Text_Grunt3Intro:
    .string "站住！\p你真以为我会傻傻地站在这里，\n看着你从我眼前跑过去？$"

MagmaHideout_2F_1R_Text_Grunt3Defeat:
    .string "哇啊！\n我认输！$"

MagmaHideout_2F_1R_Text_Grunt3PostBattle:
    .string "或许我不应该挑战你，\n直接放你过去算了…$"

MagmaHideout_2F_1R_Text_Grunt4Intro:
    .string "啊！\n有入侵者！$"

MagmaHideout_2F_1R_Text_Grunt4Defeat:
    .string "哇啊啊！$"

MagmaHideout_2F_1R_Text_Grunt4PostBattle:
    .string "我已经输了。\p那还有必要\n在这儿转圈吗？$"

MagmaHideout_2F_1R_Text_Grunt5Intro:
    .string "哦，哦！\n有入侵者！$"

MagmaHideout_2F_1R_Text_Grunt5Defeat:
    .string "切…$"

MagmaHideout_2F_1R_Text_Grunt5PostBattle:
    .string "事实上我不擅长对战…$"

