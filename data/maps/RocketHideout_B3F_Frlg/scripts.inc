RocketHideout_B3F_Frlg_MapScripts::
	.byte 0

RocketHideout_B3F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_14, RocketHideout_B3F_Text_Grunt1Intro, RocketHideout_B3F_Text_Grunt1Defeat
	msgbox RocketHideout_B3F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

RocketHideout_B3F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_15, RocketHideout_B3F_Text_Grunt2Intro, RocketHideout_B3F_Text_Grunt2Defeat
	msgbox RocketHideout_B3F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

RocketHideout_B3F_Text_Grunt1Intro::
    .string "你给我站住，不许插手火箭队的\n"
    .string "事不然的话……！$"

RocketHideout_B3F_Text_Grunt1Defeat::
    .string "啊！\n"
    .string "被做掉了！$"

RocketHideout_B3F_Text_Grunt1PostBattle::
    .string "西尔佛观测镜？\n"
    .string "哦，那个老大偷走的机器啊。\p"
    .string "它应该就在附近。$"

RocketHideout_B3F_Text_Grunt2Intro::
    .string "我们得到了楼上的情报，\n"
    .string "就知道你会来这里！$"

RocketHideout_B3F_Text_Grunt2Defeat::
    .string "什么？\n"
    .string "我输了？不！！！$"

RocketHideout_B3F_Text_Grunt2PostBattle::
    .string "想进去就进去吧！\p"
    .string "但是没有电梯的钥匙的话，\n"
    .string "你就无法操作电梯。$"

