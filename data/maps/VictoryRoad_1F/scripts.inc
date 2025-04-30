.set LOCALID_WALLY_ENTRANCE, 4

VictoryRoad_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VictoryRoad_1F_OnTransition
	.byte 0

VictoryRoad_1F_OnTransition:
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 1, VictoryRoad_1F_EventScript_SetEntranceWallyPos1
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 2, VictoryRoad_1F_EventScript_SetEntranceWallyPos2
	end

VictoryRoad_1F_EventScript_SetEntranceWallyPos1::
	setobjectxyperm LOCALID_WALLY_ENTRANCE, 2, 24
	setobjectmovementtype LOCALID_WALLY_ENTRANCE, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_SetEntranceWallyPos2::
	setobjectxyperm LOCALID_WALLY_ENTRANCE, 3, 24
	setobjectmovementtype LOCALID_WALLY_ENTRANCE, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_WallyBattleTrigger1::
	lockall
	setvar VAR_0x8008, 1
	addobject LOCALID_WALLY_ENTRANCE
	applymovement LOCALID_WALLY_ENTRANCE, VictoryRoad_1F_Movement_WallyApproachPlayer1
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyBattleTrigger2::
	lockall
	setvar VAR_0x8008, 2
	addobject LOCALID_WALLY_ENTRANCE
	applymovement LOCALID_WALLY_ENTRANCE, VictoryRoad_1F_Movement_WallyApproachPlayer2
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyEntranceBattle::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_VR_1, VictoryRoad_1F_Text_WallyEntranceDefeat
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	copyobjectxytoperm LOCALID_WALLY_ENTRANCE
	setflag FLAG_DEFEATED_WALLY_VICTORY_ROAD
	copyvar VAR_VICTORY_ROAD_1F_STATE, VAR_0x8008
	releaseall
	end

VictoryRoad_1F_Movement_WallyApproachPlayer1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

VictoryRoad_1F_Movement_WallyApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

@ This Wally appears near the entrance once his battle is triggered and remains there until the Hall of Fame is entered
VictoryRoad_1F_EventScript_EntranceWally::
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_NPC
	end

@ This Wally appears and remains at the exit after the Hall of Fame is entered
VictoryRoad_1F_EventScript_ExitWally::
	trainerbattle_single TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, VictoryRoad_1F_EventScript_RematchWally
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_RematchWally::
	trainerbattle_rematch TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Edgar::
	trainerbattle_single TRAINER_EDGAR, VictoryRoad_1F_Text_EdgarIntro, VictoryRoad_1F_Text_EdgarDefeat
	msgbox VictoryRoad_1F_Text_EdgarPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Albert::
	trainerbattle_single TRAINER_ALBERT, VictoryRoad_1F_Text_AlbertIntro, VictoryRoad_1F_Text_AlbertDefeat
	msgbox VictoryRoad_1F_Text_AlbertPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Hope::
	trainerbattle_single TRAINER_HOPE, VictoryRoad_1F_Text_HopeIntro, VictoryRoad_1F_Text_HopeDefeat
	msgbox VictoryRoad_1F_Text_HopePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Quincy::
	trainerbattle_single TRAINER_QUINCY, VictoryRoad_1F_Text_QuincyIntro, VictoryRoad_1F_Text_QuincyDefeat
	msgbox VictoryRoad_1F_Text_QuincyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Katelynn::
	trainerbattle_single TRAINER_KATELYNN, VictoryRoad_1F_Text_KatelynnIntro, VictoryRoad_1F_Text_KatelynnDefeat
	msgbox VictoryRoad_1F_Text_KatelynnPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore:
    .string "满充：嗨！{PLAYER}！\p你肯定想不到我会在这儿吧！\p我能来到这儿\n还是托你的福呢！\p{PLAYER}，要不是上次败给了你，\n我是不会变强的！\p但我不会再输了！\p我会赢的！为了给了我\n勇气和力量的宝可梦们！\p好了……上吧！$"

VictoryRoad_1F_Text_WallyEntranceDefeat:
    .string "哇！\n{PLAYER}，看来你也变强了！$"

VictoryRoad_1F_Text_WallyPostEntranceBattle:
    .string "满充：这次我还是没能打败你，\n{PLAYER}，但是，总有一天\l我会超过你！$"

VictoryRoad_1F_Text_WallyIntro:
    .string "满充：嗨！{PLAYER}！\p这一回我又变得更强了！\n给你看看我的实力吧，{PLAYER}！\p好了……上吧！$"

VictoryRoad_1F_Text_WallyDefeat:
    .string "哇！\n{PLAYER}，看来你也变强了！$"

VictoryRoad_1F_Text_WallyPostBattle:
    .string "满充：这次我还是赢不了你……\n但是，{PLAYER}，总有一天\l我会超过你……\p去挑战宝可梦联盟！$"

VictoryRoad_1F_Text_EdgarIntro:
    .string "我花了这么长时间到达这里，\n但这最后一段路实在是太长了……$"

VictoryRoad_1F_Text_EdgarDefeat:
    .string "我的梦想要再次终结了吗……$"

VictoryRoad_1F_Text_EdgarPostBattle:
    .string "既然好不容易来到这里，\n就顺着这势头冲向冠军吧！\l要说谁能做到的话，那就是你！$"

VictoryRoad_1F_Text_AlbertIntro:
    .string "我千里迢迢来这里可不是为了失败的。\n那是绝对不可能的事情！$"

VictoryRoad_1F_Text_AlbertDefeat:
    .string "不可能……\n我输了？$"

VictoryRoad_1F_Text_AlbertPostBattle:
    .string "我输在了这里……\p这就是说我没有\n成为冠军的资格……$"

VictoryRoad_1F_Text_HopeIntro:
    .string "这条无尽却艰险的道路\n不愧于冠军之名。$"

VictoryRoad_1F_Text_HopeDefeat:
    .string "你的战斗风格真完美……$"

VictoryRoad_1F_Text_HopePostBattle:
    .string "看起来你有成为\n冠军的潜力。$"

VictoryRoad_1F_Text_QuincyIntro:
    .string "冠军之路是什么？\n如果你赢了，我会告诉你的！$"

VictoryRoad_1F_Text_QuincyDefeat:
    .string "嘿！\n干得漂亮！$"

VictoryRoad_1F_Text_QuincyPostBattle:
    .string "顺利地通过这里——这是\n对所有想成为宝可梦冠军\l的训练家们的最终考验。\p这也是它被称作\n冠军之路的原因。$"

VictoryRoad_1F_Text_KatelynnIntro:
    .string "我对来到这里的人\n没有什么话可说。上吧！$"

VictoryRoad_1F_Text_KatelynnDefeat:
    .string "太丢脸了……$"

VictoryRoad_1F_Text_KatelynnPostBattle:
    .string "唔，继续走吧。\n我不介意。$"
