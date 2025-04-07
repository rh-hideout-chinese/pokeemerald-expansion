.set LOCALID_ATTENDANT, 1
.set LOCALID_HINT_GIVER, 2

BattleFrontier_BattlePyramidLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleDomeLobby_OnWarp
	.byte 0

@ Unused. Pyramid uses Dome's OnWarp (presumably by mistake). Their effects are identical
BattleFrontier_BattlePyramidLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth:
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePyramidLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving::
	lockall
	message BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	closemessage
	pyramid_set PYRAMID_DATA_WIN_STREAK, 0
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints

BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing::
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints::
	special DoBattlePyramidMonsHaveHeldItem
	call_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag
	clearflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
	frontier_checkairshow
	special LoadPlayerParty
	pyramid_clearhelditems
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	message BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept
	waitmessage
	playse SE_EXP_MAX
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait
	waitmessage
	pyramid_setprize
	pyramid_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	pyramid_clearhelditems
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	lockall
	message BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait
	waitmessage
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, FALSE
	pyramid_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge::
	goto BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge

BattleFrontier_BattlePyramidLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PYRAMID
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	pyramid_init
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	pyramid_seedfloor
	pyramid_settrainers
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_RESULT, 0
	special HealPlayerParty
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR, 1, 1
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattlePyramidLobby_EventScript_HintGiver::
	lockall
	applymovement LOCALID_HINT_GIVER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait, MSGBOX_DEFAULT
	call BattleFrontier_BattlePyramidLobby_EventScript_GiveHint
	msgbox BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot, MSGBOX_DEFAULT
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_GiveHint::
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLvOpen
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePyramidLobby_EventScript_NoHint
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_NoHint
	return

@ Shouldnt occur
BattleFrontier_BattlePyramidLobby_EventScript_NoHint::
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLv50::
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_50
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLv50Streak
	setvar VAR_RESULT, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLv50Streak::
	pyramid_get PYRAMID_DATA_WIN_STREAK_50
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLvOpen::
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_OPEN
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLvOpenStreak
	setvar VAR_RESULT, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLvOpenStreak::
	pyramid_get PYRAMID_DATA_WIN_STREAK_OPEN
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment::
	copyvar VAR_0x8004, VAR_RESULT
	special GetBattlePyramidHint
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_HintPoison
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_HintBurn
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate
	case 5, BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility
	case 6, BattleFrontier_BattlePyramidLobby_EventScript_HintIce
	case 7, BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion
	case 8, BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic
	case 9, BattleFrontier_BattlePyramidLobby_EventScript_HintRock
	case 10, BattleFrontier_BattlePyramidLobby_EventScript_HintFighting
	case 11, BattleFrontier_BattlePyramidLobby_EventScript_HintWeather
	case 12, BattleFrontier_BattlePyramidLobby_EventScript_HintBug
	case 13, BattleFrontier_BattlePyramidLobby_EventScript_HintDark
	case 14, BattleFrontier_BattlePyramidLobby_EventScript_HintWater
	case 15, BattleFrontier_BattlePyramidLobby_EventScript_HintGhost
	case 16, BattleFrontier_BattlePyramidLobby_EventScript_HintSteel
	case 17, BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon
	case 18, BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve
	case 19, BattleFrontier_BattlePyramidLobby_EventScript_HintNormal
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintParalysis, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPoison::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPoison, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintBurn::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBurn, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPPWaste, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintLevitate, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintIce::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintIce, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintExplosion, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPsychic, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintRock::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintRock, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintFighting::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFighting, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintWeather::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWeather, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintBug::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBug, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintDark::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintDark, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintWater::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWater, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintGhost::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintGhost, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintSteel::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintSteel, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintNormal::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintNormal, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_PYRAMID
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag::
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag

BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag::
	message BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel
	waitmovement 0
	return

BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_down
	step_end

BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside:
	walk_right
	face_left
	step_end

BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel:
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake, MSGBOX_DEFAULT
	setflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
	special TryStoreHeldItemsInPyramidBag
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag
	message BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag, MSGBOX_DEFAULT
	return

@ When exiting Battle Pyramid with a full pyramid bag and held items the player must select to keep/toss party held items and make room for any kept items by tossing from the pyramid bag
BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep::
	multichoice 17, 6, MULTI_FRONTIER_ITEM_CHOOSE, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems
	end

BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag::
	special ChooseItemsToTossFromPyramidBag
	waitstate
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty::
	special BattlePyramidChooseMonHeldItems
	waitstate
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems::
	special DoBattlePyramidMonsHaveHeldItem
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems
	return

BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems::
	msgbox BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem, MSGBOX_DEFAULT
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_Woman::
	msgbox BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning, MSGBOX_NPC
	end

BattleFrontier_BattlePyramidLobby_EventScript_FatMan::
	msgbox BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems, MSGBOX_NPC
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattlePyramidLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 15, 2, MULTI_BATTLE_PYRAMID_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_RulesBag
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid:
    .string "欢迎来到\n对战金字塔！\p在这里测试的是\p训练师的勇气！\n我是对战任务的向导。$"

BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge:
    .string "你有开始挑战\n追寻式对战的勇气吗？$"

BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge:
    .string "我们会等你以后来挑战！$"

BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid:
    .string "在追寻式对战中，\n你需要探索金字塔\l内部，并努力攀到顶峰。\p金字塔中有七层迷宫，\n里面不仅有强大的训练师，\l还有野生宝可梦。\p你需要带三只宝可梦进入，\n并且它们不能携带物品。\p攀登的过程中，你可以\n得到一个战斗背包来装物品，\p如果挑战失败，放在战斗背包中的\n物品都会消失。\p如果要中断挑战，\n请选择“休息”\l并保存游戏，\p中断前未作保存\n则视为放弃挑战。$"

BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode:
    .string "金字塔挑战有两种等级，\n50级和自由级，\l你要参加哪一种？$"

BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons:
    .string "好的，现在，请选择三只\n你想要携带的宝可梦。$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen:
    .string "冒险者啊，你遇到点小麻烦！\p你没有带足三只能够\n参加挑战的宝可梦。\p别忘了把宝可梦携带的\n物品取下来。\p蛋{STR_VAR_1}不能参加。\p准备好的话，\n就告诉我一声。$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50:
    .string "冒险者啊，你遇到点小麻烦！\p你没有带足三只能够\n参加挑战的宝可梦。\p必须是三只不同的宝可梦，\n而且它们都要在50级以下。\p别忘了把宝可梦携带的\n物品取下来。\p蛋{STR_VAR_1}不能参加。\p准备好的话，\n就告诉我一声。$"

BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge:
    .string "进入对战金字塔之前\n需要先存档，如何？$"

BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid:
    .string "好的，现在请进入\n对战金字塔吧。$"

BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping:
    .string "{PLAYER}，在你探索的时候，\n我们会暂时替你保管你的背包。$"

BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag:
    .string "同时，请带上你之前用过的\n这个战斗背包。$"

BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag:
    .string "同时，请带上\n这个战斗背包。$"

BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag:
    .string "{PLAYER}把背包换成了\n战斗背包。$"

BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel:
    .string "每一层当你走到这样的\n地板上之后，就会把你\l传送到金字塔更高\p的楼层，祝你\n一路顺风！$"

BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag:
    .string "冒险者啊，你碰上了一个大问题！\p上回退出挑战时\n你没有进行记录，\p因此，很抱歉，\n你的挑战中断了。\p这是你寄放在我们\n这里的背包。\p{PLAYER}拿回了背包。$"

BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid:
    .string "欢迎回来！\p你征服了金字塔！\n恭喜你！$"

BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake:
    .string "啊，有点小问题，\p有的宝可梦\n携带了物品。\p抱歉，你不能带走金字塔中\n得到的物品。$"

BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag:
    .string "你的宝可梦携带的所有物品\n都会放回到战斗背包中，{PLAYER}。$"

BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep:
    .string "很抱歉，战斗背包装不下\n所有的物品，\p请选择你需要保留在\n战斗背包中的物品。$"

BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem:
    .string "还有宝可梦\n携带了物品。$"

BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep:
    .string "请选择你需要保留在\n战斗背包中的物品。$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ReturnedEverythingMonsHeld:
    .string "{PLAYER}留下了宝可梦\n持有的物品。$"

BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept:
    .string "我们会保存你所使用的战斗背包\n以便你进行下一次挑战。\p{PLAYER}取下战斗背包，\n换回了背包。$"

BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait:
    .string "正在记录你的结果，\n请稍等。$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ForConqueringPyramidTakeThis:
    .string "作为攻克对战金字塔\n的纪念品，请收下这个。$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ReceivedPrizeItem:
    .string "{PLAYER}获得了奖品\n{STR_VAR_1}。$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_BagIsFull:
    .string "…啊…\n你的背包已经满了。\p请整理好背包\n以后再来。$"

BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag:
    .string "真遗憾…\p这是我们为你\n保管的背包。\p{PLAYER}取回了背包。$"

BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge:
    .string "期待你下次的\n挑战！$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_HereIsPrize:
    .string "我们恭候\n你的到来！\p这是征服金字塔\n的奖品。$"

BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait:
    .string "欢迎…\p我会告诉你金字塔中\n有什么灾祸在等待着…$"

BattleFrontier_BattlePyramidLobby_Text_Aah:
    .string "… … … … …\n… … … … …\p… … … … …\n啊啊！$"

BattleFrontier_BattlePyramidLobby_Text_HintParalysis:
    .string "我看到了大片的电火花…\p…你被麻痹的宝可梦\n正在其中挣扎…$"

BattleFrontier_BattlePyramidLobby_Text_HintPoison:
    .string "我看到了毒…\p…你的宝可梦\n正忍受着中毒的苦…$"

BattleFrontier_BattlePyramidLobby_Text_HintBurn:
    .string "我看到了闪亮的火焰…\p…你的宝可梦\n正在被烧灼着…$"

BattleFrontier_BattlePyramidLobby_Text_HintPPWaste:
    .string "我感受到了无尽的怒火\n产生出的庞大的压力…\p是诅咒…\p…你的宝可梦没有了\n招式点数，\l只有无助地挣扎…$"

BattleFrontier_BattlePyramidLobby_Text_HintLevitate:
    .string "我看到了天空中翱翔的宝可梦…\p…你擅长地上系招式的\n宝可梦被完全挫败…$"

BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility:
    .string "我感觉到地面下升起\n恐怖的力量…\p…你的宝可梦根本\n无法摆脱这力量的威胁…$"

BattleFrontier_BattlePyramidLobby_Text_HintIce:
    .string "我看到了冰系的宝可梦…\p…你的宝可梦正在\n坚冰中与寒冷对抗着…$"

BattleFrontier_BattlePyramidLobby_Text_HintExplosion:
    .string "我看到了很多会使自己\n受伤的招式…\p…你的宝可梦\n正败在此处…$"

BattleFrontier_BattlePyramidLobby_Text_HintPsychic:
    .string "我看到了超能系的宝可梦…\p…你的宝可梦正在被\n超能力招式折磨着…$"

BattleFrontier_BattlePyramidLobby_Text_HintRock:
    .string "我看到了岩石系的宝可梦…\p…你的宝可梦正在\n遭受岩石招式的打击…$"

BattleFrontier_BattlePyramidLobby_Text_HintFighting:
    .string "我看到了格斗系的宝可梦…\p…你的宝可梦正在\n被格斗招式不断攻击…$"

BattleFrontier_BattlePyramidLobby_Text_HintWeather:
    .string "乞雨…大晴天…\n沙暴…冰雹…\p我看到了在这些天气下\n变得更强的宝可梦…\p…你的宝可梦正在各种各样的\n招式影响下不知所措…$"

BattleFrontier_BattlePyramidLobby_Text_HintBug:
    .string "我看到了虫系的宝可梦…\p…你的宝可梦正在\n忍受各种各样的攻击…$"

BattleFrontier_BattlePyramidLobby_Text_HintDark:
    .string "我看到了恶系的宝可梦…\p…你的宝可梦正在被\n恶系招式攻击着…$"

BattleFrontier_BattlePyramidLobby_Text_HintWater:
    .string "我看到了水系的宝可梦…\p…你的宝可梦正在被\n水系招式攻击着…$"

BattleFrontier_BattlePyramidLobby_Text_HintGhost:
    .string "我看到了幽灵系的宝可梦…\p…你的宝可梦正在被\n幽灵系招式攻击着…$"

BattleFrontier_BattlePyramidLobby_Text_HintSteel:
    .string "我看到了钢系的宝可梦…\p…你的宝可梦正在苦苦\n抵挡着强力的攻击…$"

BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon:
    .string "我看到了飞在天上的宝可梦…\p…你的宝可梦正在被\n强力的招式攻击着…$"

BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve:
    .string "我看到了得到石头的力量\n而得以进化的宝可梦们…\p我感受到了火、水\n还有雷电…\p…你的宝可梦正在忍受\n这三种力量的攻击…$"

BattleFrontier_BattlePyramidLobby_Text_HintNormal:
    .string "我看到了一般系的宝可梦…\p…你的宝可梦正在苦苦\n抵挡着强力的攻击…$"

BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot:
    .string "无论是否相信我的预言，\n选择权依然在你的手中…\p未来随时都可能被改变…\n愿你能平安通过这里…$"

BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning:
    .string "知道吗？\p如果你跑太快，训练师就会\n注意到你，然后追上来向你挑战。\p所以要躲过训练师的话，\n不要让他们看到你，\l要偷偷摸摸地绕过他们。$"

BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems:
    .string "哇啊啊啊啊啊啊！\p我已经攒了那么多物品，却一不小心\n失败了，现在物品全没了！\p哇啊啊啊啊啊啊！$"

BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing:
    .string "欢迎回来！\n你的能力真让人不敢相信！\p你打败了金字塔法老，\n征服了对战金字塔！$"

BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints:
    .string "年轻的冒险者啊！\n为了表彰你的勇气，\l我们赠与你这些对战点数！$"

BattleFrontier_BattlePyramidLobby_Text_RulesAreListed:
    .string "上面写着追寻式对战的规则。$"

BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading:
    .string "想读哪一条？$"

BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules:
    .string "当有人征服了金字塔之后，\n里面的野生宝可梦会\l换成另外的类型，\p仔细探索，仔细观察，尽量去\n了解你可能碰上什么样的宝可梦。$"

BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules:
    .string "在金字塔里面会有训练师\n等着向你挑战。\p每层最多会有\n八个训练师。\p你每打败一个训练师，就会\n得到一条有用的提示。$"

BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules:
    .string "每次进入金字塔后迷宫\n都会重新组合，\p迷宫里很暗，\n必须小心探索。\p每打败一个训练师或一只野生\n宝可梦，里面都会稍微变亮一些。$"

BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules:
    .string "在金字塔中，你可以像使用\n你的背包一样使用战斗背包。\p有两种不同的战斗背包——\n分别是为50级和\l自由级的冒险而准备的。\p两种背包都可以携带10种物品，\n每种物品99个。\p如果在探索中失败的话\n战斗背包里的东西都会丢失。$"

