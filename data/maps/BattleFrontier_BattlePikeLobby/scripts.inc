.set LOCALID_ATTENDANT, 1

BattleFrontier_BattlePikeLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePikeLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePikeLobby_OnWarp
	.byte 0

BattleFrontier_BattlePikeLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePikeLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePikeLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePikeLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePikeLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattlePikeLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePikeLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattlePikeLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePikeLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattlePikeLobby_EventScript_QuitWithoutSaving::
	special HealPlayerParty
	pike_resethelditems
	lockall
	msgbox BattleFrontier_BattlePikeLobby_Text_FailedToSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	pike_set PIKE_DATA_WIN_STREAK, 0
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePikeLobby_EventScript_DefeatedQueen
	msgbox BattleFrontier_BattlePikeLobby_Text_PossessLuckInAbundance, MSGBOX_DEFAULT
	waitmessage
	goto BattleFrontier_BattlePikeLobby_EventScript_GiveBattlePoints

BattleFrontier_BattlePikeLobby_EventScript_DefeatedQueen::
	msgbox BattleFrontier_BattlePikeLobby_Text_SnatchedVictoryFromQueen, MSGBOX_DEFAULT
	waitmessage
BattleFrontier_BattlePikeLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	frontier_checkairshow
	pike_get PIKE_DATA_TOTAL_STREAKS
	addvar VAR_RESULT, 1
	pike_set PIKE_DATA_TOTAL_STREAKS, VAR_RESULT
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	pike_resethelditems
	message BattleFrontier_BattlePikeLobby_Text_ShallRecordResults
	waitmessage
	pike_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattlePikeLobby_Text_ChallengeEndedRecordResults
	waitmessage
	frontier_checkairshow
	frontier_set FRONTIER_DATA_BATTLE_NUM, 0
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, FALSE
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	pike_resethelditems
	pike_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PIKE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattlePikeLobby_Text_WelcomeToBattlePike, MSGBOX_DEFAULT
BattleFrontier_BattlePikeLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattlePikeLobby_Text_TakeChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattlePikeLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattlePikeLobby_Text_WhichChallengeMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePikeLobby_Text_PleaseChooseThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattlePikeLobby_Text_SaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattlePikeLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_1, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	pike_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, TRUE
	pike_savehelditems
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	pike_savehelditems
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePikeLobby_EventScript_CancelChallengeSaveFailed
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePikeLobby_Text_StepThisWay, MSGBOX_DEFAULT
	closemessage
	frontier_settrainers
	call BattleFrontier_BattlePikeLobby_EventScript_WalkToCorridor
	special HealPlayerParty
	call BattleFrontier_BattlePike_EventScript_CloseCurtain
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PIKE_CORRIDOR, 6, 7
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattlePikeLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainBattlePike, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou, MSGBOX_DEFAULT
BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattlePikeLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_PIKE
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_WalkToCorridor::
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePikeLobby_Movement_AttendantWalkToCorridor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePikeLobby_Movement_PlayerWalkToCorridor
	waitmovement 0
	return

BattleFrontier_BattlePikeLobby_Movement_PlayerWalkToCorridor:
	walk_up
BattleFrontier_BattlePikeLobby_Movement_AttendantWalkToCorridor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePikeLobby_EventScript_Hiker::
	msgbox BattleFrontier_BattlePikeLobby_Text_OneRoomAwayFromGoal, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_Twin::
	msgbox BattleFrontier_BattlePikeLobby_Text_NeverHadToBattleTrainer, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_Beauty::
	msgbox BattleFrontier_BattlePikeLobby_Text_ThinkAbilitiesUsefulHere, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattlePikeLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattlePikeLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 16, 4, MULTI_BATTLE_PIKE_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeLobby_EventScript_RulesPokenavBag
	case 1, BattleFrontier_BattlePikeLobby_EventScript_RulesHeldItems
	case 2, BattleFrontier_BattlePikeLobby_EventScript_RulesMonOrder
	case 3, BattleFrontier_BattlePikeLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_ExitRules
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesPokenavBag::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainPokenavBagRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesHeldItems::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainHeldItemRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesMonOrder::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainMonOrderRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattlePike_EventScript_CloseCurtain::
	playse SE_PIKE_CURTAIN_CLOSE
	special CloseBattlePikeCurtain
	waitstate
	waitse
	return

BattleFrontier_BattlePikeLobby_Text_WelcomeToBattlePike:
    .string "在这里，训练师的运气将\n受到考验…\p欢迎来到对战水管…\p我是你对战水管的指导…$"

BattleFrontier_BattlePikeLobby_Text_TakeChallenge:
    .string "你要进行对战水管\n的挑战吗？$"

BattleFrontier_BattlePikeLobby_Text_ExplainBattlePike:
    .string "我们在这里进行名叫\n选择式对战的比赛。\p选择式对战的规则\n很简单…\p在三条道路中选择一条\n在对战水管的最后\l要到达目的地房间。这很简单。\p然而，在选择的道路上会\n发生什么事完全取决于\l挑战者的运气…\p如果你达到了目标，你会被\n授予对战点数。\p如果你要中断挑战，\n请和路上大房间里的\l人员谈话。\p如果在中断之前不保存，\n就无法继续挑战。$"

BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou:
    .string "我们期待着在别的场合\n见到你…$"

BattleFrontier_BattlePikeLobby_Text_WhichChallengeMode:
    .string "你有两个选择，\n50级和自由级。\l你要挑战哪个？$"

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLv50:
    .string "请原谅，但…\p你没有三只符合选择式对战\n条件的宝可梦。\p你要参加必须要有\n三只不同的50级以下的宝可梦。\p他们还不能持有相同\n的道具。\p蛋{STR_VAR_1}是不行的。\p请你准备好了\n来见我…$"

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLvOpen:
    .string "请原谅，但…\p你没有三只符合选择式对战\n条件的宝可梦。\p你要参加必须要有\n三只不同的宝可梦。\p他们还不能持有相同\n的道具。\p蛋{STR_VAR_1}是不行的。\p请你准备好了\n来见我…$"

BattleFrontier_BattlePikeLobby_Text_PleaseChooseThreeMons:
    .string "请选择三只你要参加\n挑战的宝可梦…$"

BattleFrontier_BattlePikeLobby_Text_SaveBeforeChallenge:
    .string "在你开始战斗之前，\n我必须保存游戏。\l可以吗？$"

BattleFrontier_BattlePikeLobby_Text_StepThisWay:
    .string "请走这边…$"

BattleFrontier_BattlePikeLobby_Text_ChallengeEndedRecordResults:
    .string "你的挑战结束了…\p我要记录你的结果。\n请稍等…$"

BattleFrontier_BattlePikeLobby_Text_PossessLuckInAbundance:
    .string "你完成了挑战…\p我必须说…你好像拥有\n巨大的运气…$"

BattleFrontier_BattlePikeLobby_Text_ShallRecordResults:
    .string "我要记录你的结果。\n请稍等…$"

@ Unused
BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints2:
    .string "为庆祝你完成\n对战水管的挑战，我们\l授予你这些对战点数…$"

@ Unused
BattleFrontier_BattlePikeLobby_Text_ReachedBattlePointLimit:
    .string "看起来你已经得到足够多\n的对战点数…\p请用对战点数\n交换奖品后再回来…$"

BattleFrontier_BattlePikeLobby_Text_FailedToSaveBeforeQuitting:
    .string "请原谅，但…\p你上次退出挑战之前\n没有存档。\p因为这，到目前为止你的\n挑战无效。很抱歉…$"

BattleFrontier_BattlePikeLobby_Text_SnatchedVictoryFromQueen:
    .string "恭喜…\p你从水管皇后那取得了胜利\n并完成了任务…$"

BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints:
    .string "为了对你非凡的运气表示认可，\n我们授予你这些对战点数…$"

BattleFrontier_BattlePikeLobby_Text_OneRoomAwayFromGoal:
    .string "啊！我失去了机会！\n我走错了房间！\p在这里，你要当心\n毒，冰冻，等其它的。$"

BattleFrontier_BattlePikeLobby_Text_NeverHadToBattleTrainer:
    .string "我已经完成了10次挑战，\n但我从来没有要同一个\l训练师战斗。$"

BattleFrontier_BattlePikeLobby_Text_ThinkAbilitiesUsefulHere:
    .string "听着！听着！\p你难道不认为宝可梦的\n特殊能力在这里会很有\l用吗？$"

@ Unused
BattleFrontier_BattlePikeLobby_Text_TrainersWhicheverPathIChoose:
    .string "这个怪异的地方是什么？\n我根本弄不明白！\p我已经进行挑战好多次了\n但无论我选哪个路线\l还是要遇到训练师。$"

BattleFrontier_BattlePikeLobby_Text_RulesAreListed:
    .string "选择式对战的规则如下。$"

BattleFrontier_BattlePikeLobby_Text_ReadWhichHeading:
    .string "你要读哪个标题？$"

BattleFrontier_BattlePikeLobby_Text_ExplainPokenavBagRules:
    .string "在选择式对战的挑战中\n背包和口袋领航员不能使用。$"

BattleFrontier_BattlePikeLobby_Text_ExplainHeldItemRules:
    .string "在一次选择式对战的挑战中，\n宝可梦持有的任何树果或者药草\l只能一次有效。$"

BattleFrontier_BattlePikeLobby_Text_ExplainMonOrderRules:
    .string "在一次选择式对战的挑战中，\n宝可梦的顺序不能\l改变。\p顺序必须在你挑战之前\n安排好。$"

