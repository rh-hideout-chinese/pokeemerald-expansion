.set LOCALID_ATTENDANT, 1

BattleFrontier_BattleArenaLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleArenaLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleArenaLobby_OnWarp
	.byte 0

BattleFrontier_BattleArenaLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleArenaLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleArenaLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleArenaLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown, MSGBOX_DEFAULT
	closemessage
	arena_set ARENA_DATA_WIN_STREAK, 0
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints

BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon::
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleArenaLobby_Text_RecordAchievement
	waitmessage
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave
	waitmessage
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	arena_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge
	message BattleFrontier_BattleArenaLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge
	case 0, BattleFrontier_BattleArenaLobby_EventScript_RecordMatch
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge

BattleFrontier_BattleArenaLobby_EventScript_RecordMatch::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge::
	return

BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame
	waitmessage
	arena_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge

BattleFrontier_BattleArenaLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_ARENA
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattleArenaLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleArenaLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_OkayToSave, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	arena_init
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleArenaLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattleArenaLobby_Text_GuideYouToArena, MSGBOX_DEFAULT
	closemessage
	frontier_get FRONTIER_DATA_LVL_MODE
	call_if_eq VAR_RESULT, FRONTIER_LVL_50, BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50
	call_if_eq VAR_RESULT, FRONTIER_LVL_OPEN, BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen
	warp MAP_BATTLE_FRONTIER_BATTLE_ARENA_CORRIDOR, 9, 13
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50::
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor
	waitmovement 0
	opendoor 2, 2
	waitdooranim
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen::
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor
	waitmovement 0
	opendoor 11, 2
	waitdooranim
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 11, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

BattleFrontier_BattleArenaLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_ARENA
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_Youngster::
	msgbox BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Man::
	msgbox BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Camper::
	msgbox BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Woman::
	msgbox BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 2, MULTI_BATTLE_ARENA_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_BattleRules
	case 1, BattleFrontier_BattleArenaLobby_EventScript_MindRules
	case 2, BattleFrontier_BattleArenaLobby_EventScript_SkillRules
	case 3, BattleFrontier_BattleArenaLobby_EventScript_BodyRules
	case 4, BattleFrontier_BattleArenaLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_ExitRules
	end

BattleFrontier_BattleArenaLobby_EventScript_BattleRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_MindRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainMindRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_SkillRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_BodyRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena:
    .string "在这里，训练师的战斗意志将\n受到考验！\p欢迎来到对战竞技场！\p我是你的三回合定胜负锦标赛的指导！$"

BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge:
    .string "那么，你想要进行\n对战竞技场挑战吗？$"

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge:
    .string "我们将在另外的场合下\n等待你的挑战！$"

BattleFrontier_BattleArenaLobby_Text_ExplainChallenge:
    .string "在对战竞技场中，我们开展\n三回定胜负锦标赛\p所有的参赛者以三只宝可梦\n组成的一个队参加。\p这三只宝可梦必须要以他们\n出现的顺序安排好先后次序。\p在战斗中，宝可梦会以事先\n安排好的顺序每次出现一只。\p一旦一只宝可梦加入了战斗，\n他就必须一直持续到比赛结束。\p如果一场比赛经过三个回合还无结果，\n那就要进行裁决。\p如果你要中断挑战，\n请先保存游戏。\p如果你不保存，你下次就不能继续\n你的挑战。\p如果你能成功击败七个\n训练师的话，\l我们会给你对战点数。$"

BattleFrontier_BattleArenaLobby_Text_OkayToSave:
    .string "在带你进入对战竞技场之前你必须存档。\n可以了吗？$"

BattleFrontier_BattleArenaLobby_Text_WhichLevelMode:
    .string "对战竞技场提供两个等级的\n挑战，50级和自由级。\l你要选择哪个？$"

BattleFrontier_BattleArenaLobby_Text_SelectThreeMons:
    .string "好的，现在请选三只\n宝可梦。$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen:
    .string "亲爱的挑战者！\p你没有三只能参加比赛的\n宝可梦。\p要有参赛资格，你要带有三只不同\n种类的宝可梦。\p他们还不能持有相同\n的道具。\p蛋{STR_VAR_1}是不行的。\p当你都准备好了，\n请再回来。$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50:
    .string "亲爱的挑战者！\p你没有三只能参加比赛的\n宝可梦。\p要有参赛资格，你要带有三只不同\n种类的宝可梦。\p三只不同种类的宝可梦必须\n都在50级以下。\p他们还不能持有相同\n的道具。\p蛋{STR_VAR_1}是不行的。\p当你都准备好了，\n请再回来。$"

BattleFrontier_BattleArenaLobby_Text_GuideYouToArena:
    .string "我会为你做对战竞技场的\n指导。$"

BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown:
    .string "亲爱的挑战者！\p你在关机之前没有\n存档，是不是？\p很不幸，但这是由于你在挑战中\n失去比赛资格\l所造成的。\p当然，你可以开始一次新的\n挑战。$"

BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins:
    .string "我们恭喜你一连串漂亮地战胜了\n七个训练师！$"

BattleFrontier_BattleArenaLobby_Text_RecordAchievement:
    .string "你的成绩将被记录。\n在我记录游戏时请稍等。$"

@ Unused
BattleFrontier_BattleArenaLobby_Text_PresentYouWithPrize:
    .string "作为7连胜的奖励，\n我们送你这个奖品$"

@ Unused
BattleFrontier_BattleArenaLobby_Text_ReceivedPrize:
    .string "{PLAYER}得到了奖品\n{STR_VAR_1}。$"

@ Unused
BattleFrontier_BattleArenaLobby_Text_BagFullReturnForPrize:
    .string "哎？\n你的背包满了。\p整理空间后\n再来拿你的奖品。$"

BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave:
    .string "非常感谢你的参与！\p在我记录游戏时请稍等。$"

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2:
    .string "我们将在另外的场合下\n等待你的挑战！$"

BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame:
    .string "我们早已期待你的\n到来。$"

BattleFrontier_BattleArenaLobby_Text_RecordLastMatch:
    .string "要我把你上次的对战竞技场比赛记录\n在你的开拓区通行证上吗？$"

BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack:
    .string "我对裁判的决定感到困惑…\p我认为只防守而不进攻是\n行不通的…$"

BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked:
    .string "我的判断正确！\p降落到对手的宝可梦身上的连续打击\n这招果然行得通！$"

BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw:
    .string "我们的比赛被判为平局。\p当时间到时，我和\n我对手的宝可梦\l都剩下等量的HP。$"

BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant:
    .string "在对战竞技场中，宝可梦的顺序\n十分重要。\p比如说，如果你的第一只宝可梦\n有某种弱点，\l那你就该安排让你的第二只宝可梦能\l非常有效地\l对付第一只。\p我认为这会是组成一支有效队伍的\n好方法。$"

BattleFrontier_BattleArenaLobby_Text_RulesAreListed:
    .string "三回合定胜负锦标赛的规则如下。$"

BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading:
    .string "你要读哪个标题的？$"

BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules:
    .string "三回合定胜负锦标赛有特殊规则，\n而不像常规战斗。\p第一，每场战斗只进行\n三个回合。\p如果在三个回合之后还未\n分胜负，就要进行裁决。\p裁判会根据宝可梦的战斗情况\n判出胜者。\p同样，宝可梦在出比赛结果之前\n不能调换出的。$"

BattleFrontier_BattleArenaLobby_Text_ExplainMindRules:
    .string "第一个裁决因素是“战术”。\n这个因素评价战斗者的进攻\l意识。\p裁决依据的是训练师\n下达进攻行动的命令的\l频繁程度。$"

BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules:
    .string "第二个裁决因素是“技术”。\n这个因素评价宝可梦的\l行动效率。\p如果一次行动成功了，\n技术的值就上升。\p如果一次行动失败了，\n技术的值就下降。\p对于进攻行动，如果行动是“非常有效”\n技术的值就上升\l如果是“没什么效果”\l技术的值就下降。\p对于像保护和见切的行动\n技术的值是不会上升的。\p如果对手采取了保护或是见切\n的行动，并且你的宝可梦没能\l打击成功，技术的值也\l不会下降。$"

BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules:
    .string "第三个裁决因素是“血量”。\n这个因素评价在战斗结束后\lHP还剩下多少。\p这个值把宝可梦\n战斗开始时的HP\l和战斗结束后还剩下的HP都加以考虑。$"

BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon:
    .string "从斗王手里得到了胜利，\n并且干掉了七个训练师！\p恭喜你的挑战\n干得漂亮！$"

BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints:
    .string "亲爱的挑战者，为了对你那不屈的\n意志表示认可，请接受这些\l对战点数吧。$"
