.set LOCALID_MOVE_RELEARNER, 1

FallarborTown_MoveRelearnersHouse_MapScripts::
	.byte 0

FallarborTown_MoveRelearnersHouse_EventScript_MoveRelearner::
	lockall
	applymovement LOCALID_MOVE_RELEARNER, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_set FLAG_TEMP_1, FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove
	msgbox FallarborTown_MoveRelearnersHouse_Text_ImTheMoveTutor, MSGBOX_DEFAULT
	setflag FLAG_TEMP_1
	goto FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove
	end

FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove::
	checkitem ITEM_HEART_SCALE
	goto_if_eq VAR_RESULT, FALSE, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	msgbox FallarborTown_MoveRelearnersHouse_Text_ThatsAHeartScaleWantMeToTeachMove, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TutorWhichMon, MSGBOX_DEFAULT
	special ChooseMonForMoveRelearner
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_MoveRelearnersHouse_EventScript_CantTeachEgg
	goto_if_eq VAR_0x8005, 0, FallarborTown_MoveRelearnersHouse_EventScript_NoMoveToTeachMon
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMove
	end

FallarborTown_MoveRelearnersHouse_EventScript_ChooseMove::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	waitstate
	goto_if_eq VAR_0x8004, 0, FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	msgbox FallarborTown_MoveRelearnersHouse_Text_HandedOverHeartScale, MSGBOX_DEFAULT
	removeitem ITEM_HEART_SCALE
	goto FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	end

FallarborTown_MoveRelearnersHouse_EventScript_NoMoveToTeachMon::
	msgbox FallarborTown_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_CantTeachEgg::
	msgbox FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale::
	msgbox FallarborTown_MoveRelearnersHouse_Text_ComeBackWithHeartScale, MSGBOX_DEFAULT
	releaseall
	end

FallarborTown_MoveRelearnersHouse_Text_ImTheMoveTutor:
    .string "我是招式导师，\p我知道宝可梦的\n每一个招式，也能教\l宝可梦学会这些招式。\p如果你愿意，我可以教你的\n宝可梦一个招式，\p条件是我要一个心之鳞片。\n我现在正在收集这些东西。$"

FallarborTown_MoveRelearnersHouse_Text_ThatsAHeartScaleWantMeToTeachMove:
    .string "那个！那是真真正正的\n心之鳞片！\p我猜，你是想让我\n教授招式吧？$"

FallarborTown_MoveRelearnersHouse_Text_TutorWhichMon:
    .string "要教哪只宝可梦？$"

FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove:
    .string "教什么招式？$"

FallarborTown_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon:
    .string "抱歉……\p似乎我没法再教\n这只宝可梦什么招式了。$"

FallarborTown_MoveRelearnersHouse_Text_HandedOverHeartScale:
    .string "{PLAYER}拿出一个心之鳞片\n作为交换。$"

FallarborTown_MoveRelearnersHouse_Text_ComeBackWithHeartScale:
    .string "如果你想要你的宝可梦学习招式，\n带一个心之鳞片来吧。$"

FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg:
    .string "呃？我可没法教一只蛋\n什么招式。$"

