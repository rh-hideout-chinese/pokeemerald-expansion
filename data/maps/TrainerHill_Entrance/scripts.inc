.set LOCALID_ATTENDANT, 1
.set LOCALID_NURSE, 2
.set LOCALID_GIRL, 4
.set LOCALID_MAN, 5

TrainerHill_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TrainerHill_Entrance_OnResume
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, TrainerHill_Entrance_OnReturn
	map_script MAP_SCRIPT_ON_TRANSITION, TrainerHill_Entrance_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, TrainerHill_Entrance_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrainerHill_Entrance_OnFrame
	.byte 0

TrainerHill_Entrance_OnTransition:
	setflag FLAG_LANDMARK_TRAINER_HILL
	getplayerxy VAR_TEMP_D, VAR_RESULT
	end

@ Unused
TrainerHill_Entrance_OnWarp:
	end

TrainerHill_Entrance_OnResume:
	trainerhill_resumetimer
	setvar VAR_TEMP_0, 0
	trainerhill_getusingereader
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_TryFaceAttendant  @ VAR_RESULT always FALSE here
	setobjectxy OBJ_EVENT_ID_PLAYER, 9, 6
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_TryFaceAttendant::
	trainerhill_getwon
	goto_if_eq VAR_RESULT, TRUE, TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant::
	end

TrainerHill_Entrance_OnReturn:
	addobject LOCALID_NURSE
	addobject LOCALID_ATTENDANT
	addobject LOCALID_MAN
	addobject LOCALID_GIRL
	end

TrainerHill_Entrance_OnLoad:
	call_if_eq VAR_TEMP_D, 17, TrainerHill_Entrance_EventScript_OpenCounterDoor
	end

TrainerHill_Entrance_EventScript_OpenCounterDoor::
	setmetatile 17, 10, METATILE_TrainerHill_GreenFloorTile, FALSE
	return

TrainerHill_Entrance_OnFrame:
	map_script_2 VAR_TEMP_0, 0, TrainerHill_Entrance_EventScript_ExitChallenge
	map_script_2 VAR_TEMP_D, 17, TrainerHill_Entrance_EventScript_ExitElevator
	map_script_2 VAR_TEMP_5, 1, TrainerHill_Entrance_EventScript_EntryTrigger
	map_script_2 VAR_TEMP_1, 1, TrainerHill_EventScript_WarpToEntranceCounter
	.2byte 0

TrainerHill_Entrance_EventScript_ExitElevator::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerExitElevator
	waitmovement 0
	setmetatile 17, 10, METATILE_TrainerHill_CounterDoor, TRUE
	special DrawWholeMapView
	playse SE_CLICK
	waitse
	setvar VAR_TEMP_D, 0
	releaseall
	end

TrainerHill_Entrance_EventScript_ExitChallenge::
	setvar VAR_TEMP_0, 1
	trainerhill_getstatus
	switch VAR_RESULT
	case TRAINER_HILL_PLAYER_STATUS_LOST, TrainerHill_Entrance_EventScript_ExitChallengeLost
	case TRAINER_HILL_PLAYER_STATUS_ECARD_SCANNED, TrainerHill_Entrance_EventScript_ExitChallengeECard
	case TRAINER_HILL_PLAYER_STATUS_NORMAL, TrainerHill_Entrance_EventScript_EndExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeLost::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_TooBadTremendousEffort, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_PlayerExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeECard::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_MovedReceptionHereForSwitch, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_PlayerExitChallenge::
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 0
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	releaseall
TrainerHill_Entrance_EventScript_EndExitChallenge::
	end

TrainerHill_Entrance_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

TrainerHill_Entrance_EventScript_Attendant::
	lock
	faceplayer
	trainerhill_inchallenge
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_ThanksForPlaying
	msgbox TrainerHill_Entrance_Text_HopeYouGiveItYourBest, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AttendantEnd

TrainerHill_Entrance_EventScript_ThanksForPlaying::
	msgbox TrainerHill_Entrance_Text_ThankYouForPlaying, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AttendantEnd::
	release
	end

TrainerHill_Entrance_EventScript_EntryTrigger::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_Closed
	msgbox TrainerHill_Entrance_Text_WelcomeToTrainerHill, MSGBOX_DEFAULT
	trainerhill_getsaved
	call_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_SaveGame
	trainerhill_allfloorsused
	goto_if_eq VAR_RESULT, TRUE, TrainerHill_Entrance_EventScript_AllFloorsUsed
	msgbox TrainerHill_Entrance_Text_TrainersUpToFloorX, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers

TrainerHill_Entrance_EventScript_AllFloorsUsed::
	msgbox TrainerHill_Entrance_Text_TrainersInEveryRoom, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AskChallengeTrainers::
	message TrainerHill_Entrance_Text_LikeToChallengeTrainers
	waitmessage
	multichoice 15, 6, MULTI_YESNOINFO, FALSE
	switch VAR_RESULT
	case 0, TrainerHill_Entrance_EventScript_ChooseChallenge
	case 1, TrainerHill_Entrance_EventScript_CancelEntry
	case 2, TrainerHill_Entrance_EventScript_Info
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Info::
	msgbox TrainerHill_Entrance_Text_ExplainTrainerHill, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers
	end

TrainerHill_Entrance_EventScript_ChooseChallenge::
	multichoice 13, 2, MULTI_TAG_MATCH_TYPE, FALSE
	switch VAR_RESULT
	case 4, TrainerHill_Entrance_EventScript_CancelEntry
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	trainerhill_setmode VAR_RESULT
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 1
	setvar VAR_TEMP_5, 0
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	msgbox TrainerHill_Entrance_Text_TimeProgessGetSetGo, MSGBOX_DEFAULT
	trainerhill_start
	releaseall
	end

TrainerHill_Entrance_EventScript_CancelEntry::
	setvar VAR_TEMP_5, 0
	msgbox TrainerHill_Entrance_Text_PleaseVisitUsAgain, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_EventScript_SaveGame::
	msgbox TrainerHill_Entrance_Text_SaveGameBeforeEnter, MSGBOX_DEFAULT
	trainerhill_setsaved
	setvar VAR_TEMP_5, 1
	call Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_SaveFailed
	trainerhill_setsaved
	return

TrainerHill_Entrance_EventScript_SaveFailed::
	trainerhill_clearsaved
	goto TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Closed::
	msgbox TrainerHill_Entrance_Text_StillGettingReady, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_Movement_PlayerFaceAttendant:
	face_right
	step_end

TrainerHill_Entrance_Movement_PushPlayerBackFromCounter:
	walk_down
	step_end

@ Unused
TrainerHill_Entrance_Movement_FaceUp:
	face_up
	step_end

TrainerHill_Entrance_Movement_PlayerExitElevator:
	walk_down
	walk_down
	step_end

TrainerHill_Entrance_EventScript_Records::
	lockall
	fadescreen FADE_TO_BLACK
	special ShowTrainerHillRecords
	waitstate
	releaseall
	end

TrainerHill_Entrance_EventScript_Man::
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ManTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_ManTrainerHillClosed::
	msgbox TrainerHill_Entrance_Text_CantWaitToTestTheWaters, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_Girl::
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_GirlTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_GirlTrainerHillClosed::
	msgbox TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ExpandedPokemart
	pokemart TrainerHill_Entrance_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TrainerHill_Entrance_Pokemart_Basic:
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	pokemartlistend

TrainerHill_Entrance_EventScript_ExpandedPokemart::
	pokemart TrainerHill_Entrance_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TrainerHill_Entrance_Pokemart_Expanded:
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	pokemartlistend

TrainerHill_Entrance_Text_StillGettingReady:
    .string "这里是训练师之山，\n你可以在这里与许多其他训练师\l组队战斗。\p不过很抱歉，我们正在进行准备，\n请您下次再来！$"

TrainerHill_Entrance_Text_WelcomeToTrainerHill:
    .string "欢迎！\p这里是训练师之山，\n在这里你可以与其他的\l训练师进行对战！$"

TrainerHill_Entrance_Text_SaveGameBeforeEnter:
    .string "你是第一次来这儿吗？\p在进入之前，请先\n保存进度。$"

TrainerHill_Entrance_Text_TrainersUpToFloorX:
    .string "唔，我看看…\n现在这儿的训练师正在…\p{STR_VAR_1}楼。$"

TrainerHill_Entrance_Text_TrainersInEveryRoom:
    .string "唔，我看看…\n现在这儿的训练师正在…\p好像每间房间里\n都有训练师。$"

TrainerHill_Entrance_Text_LikeToChallengeTrainers:
    .string "你想要挑战\n等候着的训练师吗？$"

TrainerHill_Entrance_Text_TimeProgessGetSetGo:
    .string "我会为你计时的，\n祝你好运！\p记下你的成绩…\p创造自己的纪录…\p去吧！$"

TrainerHill_Entrance_Text_PleaseVisitUsAgain:
    .string "下次再来！$"

TrainerHill_Entrance_Text_TooBadTremendousEffort:
    .string "真不幸。\p你一定为战斗付出了\n极大的努力。\p再来试试吧！$"

TrainerHill_Entrance_Text_HopeYouGiveItYourBest:
    .string "希望你能尽力。$"

TrainerHill_Entrance_Text_MovedReceptionHereForSwitch:
    .string "训练师移动的时候，\n就显得有些混乱。\p为避免这种情况，\n我们就把接待处搬到这儿来了。\p很抱歉对你造成了不便。$"

TrainerHill_Entrance_Text_ThankYouForPlaying:
    .string "感谢你来此游玩！$"

TrainerHill_Entrance_Text_ExplainTrainerHill:
    .string "我们训练师之山这里有一种\n叫做限时进攻的活动，\p是计算你从这个\n柜台跑到顶层老板\l那里的用时的游戏。\p最快的成绩会贴在那边的\n时间板上。跟你的\l朋友比试吧。\p一路上的战斗中，\n你既不能获得经验点数，\l也不能获得金钱。$"

@ Unused
TrainerHill_Entrance_Text_NeedAtLeastTwoPokemon:
    .string "哦，对不起，但是\n你只有一只宝可梦。\p你最少需要两只宝可梦\n来参加这个活动。$"

TrainerHill_Roof_Text_YouFinallyCameBravo:
    .string "嗯，嗯！\p你终于来了！\n是啊，你来了！\p等！不要说话！\n我知道你为什么会\l一个人单独走到这里来！\p你要来见我这个\n训练师之山的老板，因为…\p你希望和我组队！\n呀—呵！\p…呃？\n不是吗？\p不管怎样，我一路看着你上来。\n完美的战斗！勇气可嘉！$"

TrainerHill_Roof_Text_HaveTheMostMarvelousGift:
    .string "像你这样杰出的人，当然\n只有最杰出的礼物才配得上你！$"

TrainerHill_Roof_Text_FullUpBeBackLaterForThis:
    .string "哦，不，背包已经塞满了！\n以后再来拿走这个吧！$"

TrainerHill_Roof_Text_GotHereMarvelouslyQuickly:
    .string "啊，等等！\n你来得可真快啊。\p真让我吃惊！你不必\n这么急着来见我的！\p真棒，接待处的\n时间板需要更新了！$"

TrainerHill_Roof_Text_YouWerentVeryQuick:
    .string "呃，噢…\n你来得并不是很快。$"

TrainerHill_Roof_Text_ArriveZippierNextTime:
    .string "也许下次你快一点来\n我会更高兴的。\p那样，我将会很高兴\n和你一同组队！\p下次再见，朋友！$"

@ Unused
TrainerHill_Roof_Text_BuiltTrainerHillToFindPartner:
    .string "我建这训练师之山\n的原因只有一个！\p就是要找到最合适的\n搭档来组成职业队伍！$"

TrainerHill_Entrance_Text_ChallengeTime:
    .string "{STR_VAR_1}分{STR_VAR_2}。{STR_VAR_3}秒。$"

TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead:
    .string "谁关心前面会有什么样的\n训练师和宝可梦的组合呢？\p我只知道，我要打倒每一个\n挡住我的路的人！$"

TrainerHill_Entrance_Text_CantWaitToTestTheWaters:
    .string "听说各地的强大训练师\n都会来到训练师之山。\p我已经跃跃欲试了！\p我要打倒每一个\n挡住我的路的人！$"

TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop:
    .string "看到那边的时间板了吗？\p我和朋友正在比试\n谁能更快到达山顶。$"

TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen:
    .string "你知道这里什么时候\n才会开门吗？\p我一直在这儿等着\n成为这里的第一个挑战者！$"

TrainerHill_Elevator_Text_ReturnToReception:
    .string "现在请你回到\n接待处好吗？$"
