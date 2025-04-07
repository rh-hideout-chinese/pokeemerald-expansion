MagmaHideout_2F_2R_MapScripts::
	.byte 0

MagmaHideout_2F_2R_EventScript_Grunt15::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_15, MagmaHideout_2F_2R_Text_Grunt15Intro, MagmaHideout_2F_2R_Text_Grunt15Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt15PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_6, MagmaHideout_2F_2R_Text_Grunt6Intro, MagmaHideout_2F_2R_Text_Grunt6Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt7::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_7, MagmaHideout_2F_2R_Text_Grunt7Intro, MagmaHideout_2F_2R_Text_Grunt7Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt7PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_8, MagmaHideout_2F_2R_Text_Grunt8Intro, MagmaHideout_2F_2R_Text_Grunt8Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_Text_Grunt15Intro:
    .string "我不想找你的麻烦，\n我只是在服从命令！$"

MagmaHideout_2F_2R_Text_Grunt15Defeat:
    .string "我或许输了，可是…$"

MagmaHideout_2F_2R_Text_Grunt15PostBattle:
    .string "我们挖掘到了不可思议的东西！\n是蓝色宝珠！\p只要头儿能…\n哼哼哼…哈哈哈哈！$"

MagmaHideout_2F_2R_Text_Grunt6Intro:
    .string "我怕热。或许我应该\n加入水舰队才对…$"

MagmaHideout_2F_2R_Text_Grunt6Defeat:
    .string "嗯，我或许真的不适合\n加入火岩队…$"

MagmaHideout_2F_2R_Text_Grunt6PostBattle:
    .string "你不觉得在这种地方\n很容易爱上大海？$"

MagmaHideout_2F_2R_Text_Grunt7Intro:
    .string "在这里有时能感觉到晃动。\p难道是火山喷发？\n还是固…\p哎呀！\n不，不，没什么！$"

MagmaHideout_2F_2R_Text_Grunt7Defeat:
    .string "你的进攻真猛烈，\n就像火山一样！$"

MagmaHideout_2F_2R_Text_Grunt7PostBattle:
    .string "这次算你走运。\n不过不要紧，\p火岩队的目标就要\n达到了！$"

MagmaHideout_2F_2R_Text_Grunt8Intro:
    .string "我们中的一个人慌慌张张地说\n他弄丢了他的火岩徽章…\p等一下！\n是不是被你捡到了？$"

MagmaHideout_2F_2R_Text_Grunt8Defeat:
    .string "真是难以置信…$"

MagmaHideout_2F_2R_Text_Grunt8PostBattle:
    .string "我预感我们的计划\n最终会失败…$"

