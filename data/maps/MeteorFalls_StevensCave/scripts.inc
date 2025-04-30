.set LOCALID_STEVEN, 1

MeteorFalls_StevensCave_MapScripts::
	.byte 0

MeteorFalls_StevensCave_EventScript_Steven::
	lock
	goto_if_set FLAG_DEFEATED_METEOR_FALLS_STEVEN, MeteorFalls_StevensCave_EventScript_Defeated
	waitse
	playse SE_PIN
	applymovement LOCALID_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN, MeteorFalls_StevensCave_Text_StevenDefeat
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_METEOR_FALLS_STEVEN
	release
	end

MeteorFalls_StevensCave_EventScript_Defeated::
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst:
    .string "大吾：咦，{PLAYER}{KUN}，\n你居然知道我在这里。\p你是不是，嗯……认为我是\n个普通的石头狂人？\p……不对，\p我们在绿岭市宇宙中心\n共同战斗过，\p你应该很清楚\n我的实力。\p好吧，{PLAYER}{KUN}，如果你真的\n想挑战我，做好觉悟吧！$"

MeteorFalls_StevensCave_Text_StevenDefeat:
    .string "你……\n我居然没发现你已经这么强了……$"

MeteorFalls_StevensCave_Text_MyPredictionCameTrue:
    .string "大吾：这么想来，自从在\n武斗镇的石之洞窟\l碰到你，我就有了一种感觉，\p我感觉你最终能\n成为冠军。\p我的预感总是对的。\p那么……接下来你要去的地方是……\p…… …… ……\n…… …… ……\p呵呵呵，即使是我也不知道呀。$"

