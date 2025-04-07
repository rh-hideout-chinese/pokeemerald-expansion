MagmaHideout_3F_1R_MapScripts::
	.byte 0

MagmaHideout_3F_1R_EventScript_Grunt9::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_9, MagmaHideout_3F_1R_Text_Grunt9Intro, MagmaHideout_3F_1R_Text_Grunt9Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt9PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_EventScript_Grunt16::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_16, MagmaHideout_3F_1R_Text_Grunt16Intro, MagmaHideout_3F_1R_Text_Grunt16Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt16PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_Text_Grunt9Intro:
    .string "我怎么会被分配到这个\n岗位上？\p我的左耳发热了！$"

MagmaHideout_3F_1R_Text_Grunt9Defeat:
    .string "热量耗尽了…$"

MagmaHideout_3F_1R_Text_Grunt9PostBattle:
    .string "你是不是很奇怪我们为什么\n在满是岩浆的火山里面戴着风帽？$"

MagmaHideout_3F_1R_Text_Grunt16Intro:
    .string "我们加入团队，为的是\n帮助头儿实现他的雄图伟业。\p我不管你是水舰队的人\n还是偶尔路过的小毛贼，\p只要惹了我们\n都不会有好下场！$"

MagmaHideout_3F_1R_Text_Grunt16Defeat:
    .string "哦，不！\n真是不可轻视！$"

MagmaHideout_3F_1R_Text_Grunt16PostBattle:
    .string "听我说，\n火岩队才是正确的！\p别听水舰队的，\n不要相信他们的谎言！$"

