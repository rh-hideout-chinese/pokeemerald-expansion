MtPyre_6F_MapScripts::
	.byte 0

MtPyre_6F_EventScript_Valerie::
	trainerbattle_single TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieIntro, MtPyre_6F_Text_ValerieDefeat, MtPyre_6F_EventScript_RegisterValerie
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_6F_EventScript_RematchValerie
	msgbox MtPyre_6F_Text_ValeriePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_6F_EventScript_RegisterValerie::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_6F_Text_ValerieRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_VALERIE_1
	release
	end

MtPyre_6F_EventScript_RematchValerie::
	trainerbattle_rematch TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieRematchIntro, MtPyre_6F_Text_ValerieRematchDefeat
	msgbox MtPyre_6F_Text_ValeriePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_EventScript_Cedric::
	trainerbattle_single TRAINER_CEDRIC, MtPyre_6F_Text_CedricIntro, MtPyre_6F_Text_CedricDefeat
	msgbox MtPyre_6F_Text_CedricPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_Text_ValerieIntro:
    .string "当我来到这里……\n就会有一股奇异的力量涌进身体……$"

MtPyre_6F_Text_ValerieDefeat:
    .string "这股力量在消退……$"

MtPyre_6F_Text_ValeriePostBattle:
    .string "或许这股力量来自在此沉睡着\n的宝可梦的灵魂……$"

MtPyre_6F_Text_ValerieRegister:
    .string "呼呼呼……我输掉了比赛，但是……\n我可以这样……\p不必用手碰到你的\n宝可导航……嘿呀！$"

MtPyre_6F_Text_ValerieRematchIntro:
    .string "你后面……\n那是什么……$"

MtPyre_6F_Text_ValerieRematchDefeat:
    .string "好像有什么东西消失了……$"

MtPyre_6F_Text_ValeriePostRematch:
    .string "在这里沉眠的宝可梦……\n有时也会出来玩耍……$"

MtPyre_6F_Text_CedricIntro:
    .string "你迷失方向了吗？\n有我在，不用怕！$"

MtPyre_6F_Text_CedricDefeat:
    .string "你并没有迷路吗？$"

MtPyre_6F_Text_CedricPostBattle:
    .string "我觉得一个迷路的训练家\n会很惊慌，很容易就能打败。\p但那样太卑鄙了，我不会再那么做了……$"

