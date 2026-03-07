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
	turnobject LOCALID_PLAYER, DIR_NORTH
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
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
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
	applymovement LOCALID_PYRAMID_LOBBY_HINT_GIVER, Common_Movement_FacePlayer
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
	applymovement LOCALID_PYRAMID_LOBBY_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel
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
	applymovement LOCALID_PYRAMID_LOBBY_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside
	waitmovement 0
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel
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
    .string "训练家的勇气\n将在此接受考验！\p欢迎来到\n对战金字塔！\p我是您探索式对战的向导。$"

BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge:
    .string "有勇气挑战探索式对战吗？$"

BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge:
    .string "我们期待您未来的挑战！$"

BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid:
    .string "在探索式对战中，\n您需要探索金字塔内部，\l并努力抵达顶层。\p金字塔中有7层迷宫，\n每层不仅有强大的训练家，\l还有野生宝可梦。\p您需要带3只宝可梦进入，\n并且它们不能携带道具。\p登顶的过程中，\n您会获得一个战斗包包\l用于存放道具，\p如果挑战失败，战斗包包中的所有\n道具都会消失。\p如果您在中途想要暂停的话，\n请选择“休息”并写入记录，\p请确保在退出前完好地写下了记录。\n否则我们将视挑战为无效。$"

BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode:
    .string "金字塔挑战有2种等级，\nLv. 50级和自由等级，\l要参加哪一种？$"

BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons:
    .string "好的，请选择要参加挑战的\n3只宝可梦。$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen:
    .string "探险家啊，有点小问题！\p您能够参加对战的\n宝可梦不满3只。\p您需要准备3只\n不同种类的宝可梦，\p并且记得要取下它们携带的道具\n才可参加对战。\p此外，蛋{STR_VAR_1}！$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50:
    .string "探险家啊，有点小问题！\p您能够参加对战的\n宝可梦不满3只。\p您需要准备3只等级50以内的\n不同种类的宝可梦，\p并且记得要取下它们携带的道具\n才可参加对战。\p此外，蛋{STR_VAR_1}！$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsEnd:
    .string "准备就绪后，\n请告诉我一声。$"

BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge:
    .string "进入对战金字塔之前\n要先写入记录，可以吗？$"

BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid:
    .string "好的，现在我将带您进入\n对战金字塔。$"

BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping:
    .string "{PLAYER}，在探索期间，\n我们会暂时替您保管包包。$"

BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag:
    .string "作为交换，\n请带上您之前用过的这个战斗包包。$"

BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag:
    .string "作为交换，\n请带上这个战斗包包。$"

BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag:
    .string "{PLAYER}把包包换成了\n战斗包包。$"

BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel:
    .string "每当您踩上这样的地板，\n就会被传送到金字塔更高层，\p祝您的探索一路顺风！$"

BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag:
    .string "探险家啊，有个大问题！\p您在上次结束时\n没有写入记录。\p遗憾地告诉您，没有写入记录的\n挑战我们将视其为无效。\p这是您寄放在我们\n这里的包包。\p{PLAYER}拿回了包包。$"

BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid:
    .string "欢迎回来！\p您征服了金字塔！\n太了不起了！$"

BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake:
    .string "啊，有点小问题。\p有的宝可梦\n携带了道具。\p抱歉，您不能带走金字塔中\n得到的道具。$"

BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag:
    .string "您的宝可梦携带的所有道具\n都会放回到战斗包包中，{PLAYER}。$"

BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep:
    .string "很抱歉，战斗包包装不下\n所有的道具，\p请选择您需要保留在\n战斗包包中的道具。$"

BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem:
    .string "仍有宝可梦在\n携带着道具。$"

BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep:
    .string "请选择您需要保留在\n战斗包包中的道具。$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ReturnedEverythingMonsHeld:
    .string "{PLAYER}留下了宝可梦\n携带的道具。$"

BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept:
    .string "我们会寄存您所使用的战斗包包\n以便您进行下一次挑战。\p{PLAYER}取下战斗包包，\n换回了包包。$"

BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait:
    .string "正在记录您的成绩，\n请稍等。$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ForConqueringPyramidTakeThis:
    .string "作为攻克对战金字塔\n的纪念品，请收下这个。$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ReceivedPrizeItem:
    .string "{PLAYER}获得了奖品\n{STR_VAR_1}。$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_BagIsFull:
    .string "……啊……\n您的包包已经满了。\p请整理好包包\n以后再来。$"

BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag:
    .string "真遗憾……\p这是我们为您\n保管的包包。\p{PLAYER}取回了包包。$"

BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge:
    .string "随时恭候您再次挑战！$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_HereIsPrize:
    .string "我们恭候\n您的到来！\p这是征服金字塔\n的奖品。$"

BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait:
    .string "欢迎……\p我会告诉你金字塔中\n有什么不幸在等待着……$"

BattleFrontier_BattlePyramidLobby_Text_Aah:
    .string "…… …… ……\n…… …… ……\p…… …… ……\n啊啊！$"

BattleFrontier_BattlePyramidLobby_Text_HintParalysis:
    .string "我看到了大片的电火花……\p……你被麻痹的宝可梦\n正在其中挣扎……$"

BattleFrontier_BattlePyramidLobby_Text_HintPoison:
    .string "我看到了毒……\p……你的宝可梦\n正忍受着中毒的苦……$"

BattleFrontier_BattlePyramidLobby_Text_HintBurn:
    .string "我看到了闪亮的火焰……\p……你的宝可梦\n正在被烧灼着……$"

BattleFrontier_BattlePyramidLobby_Text_HintPPWaste:
    .string "我感受到了无尽的怒火\n产生出的庞大的压力……\p是诅咒……\p……你的宝可梦没有了\n招式点数，\l只有无助地挣扎……$"

BattleFrontier_BattlePyramidLobby_Text_HintLevitate:
    .string "我看到了天空中翱翔的宝可梦……\p……你擅长地面属性招式的\n宝可梦被完全挫败……$"

BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility:
    .string "我感觉到地底升起\n恐怖的力量……\p……你的宝可梦根本\n无法摆脱这力量的威胁……$"

BattleFrontier_BattlePyramidLobby_Text_HintIce:
    .string "我看到了冰属性的宝可梦……\p……你的宝可梦正在\n坚冰中与寒冷对抗着……$"

BattleFrontier_BattlePyramidLobby_Text_HintExplosion:
    .string "我看到了很多会使自己\n受伤的招式……\p……你的宝可梦\n正败在此处……$"

BattleFrontier_BattlePyramidLobby_Text_HintPsychic:
    .string "我看到了超能力属性的宝可梦……\p……你的宝可梦正在被\n超能力招式折磨着……$"

BattleFrontier_BattlePyramidLobby_Text_HintRock:
    .string "我看到了岩石属性的宝可梦……\p……你的宝可梦正在\n遭受岩石招式的打击……$"

BattleFrontier_BattlePyramidLobby_Text_HintFighting:
    .string "我看到了格斗属性的宝可梦……\p……你的宝可梦正在\n被格斗招式不断攻击……$"

BattleFrontier_BattlePyramidLobby_Text_HintWeather:
    .string "求雨……大晴天……\n沙暴……冰雹……\p我看到了在这些天气下\n变得更强的宝可梦……\p……你的宝可梦正在各种各样的\n招式影响下不知所措……$"

BattleFrontier_BattlePyramidLobby_Text_HintBug:
    .string "我看到了虫属性的宝可梦……\p……你的宝可梦正在\n忍受各种各样的攻击……$"

BattleFrontier_BattlePyramidLobby_Text_HintDark:
    .string "我看到了恶属性的宝可梦……\p……你的宝可梦正在被\n恶属性招式攻击着……$"

BattleFrontier_BattlePyramidLobby_Text_HintWater:
    .string "我看到了水属性的宝可梦……\p……你的宝可梦正在被\n水属性招式攻击着……$"

BattleFrontier_BattlePyramidLobby_Text_HintGhost:
    .string "我看到了幽灵属性的宝可梦……\p……你的宝可梦正在被\n幽灵属性招式攻击着……$"

BattleFrontier_BattlePyramidLobby_Text_HintSteel:
    .string "我看到了钢属性的宝可梦……\p……你的宝可梦正在苦苦\n抵挡着强力的攻击……$"

BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon:
    .string "我看到了飞在天上的宝可梦……\p……你的宝可梦正在被\n强力的招式攻击着……$"

BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve:
    .string "我看到了得到石头的力量\n而得以进化的宝可梦们……\p我感受到了火、水\n还有电……\p……你的宝可梦正在忍受\n这3种力量的攻击……$"

BattleFrontier_BattlePyramidLobby_Text_HintNormal:
    .string "我看到了一般属性的宝可梦……\p……你的宝可梦正在苦苦\n抵挡着强力的攻击……$"

BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot:
    .string "无论是否相信我的预言，\n选择权依然在你的手中……\p未来随时都可能被改变……\n愿你能平安通过这里……$"

BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning:
    .string "知道吗？\p如果你跑得太快，训练家就会\n注意到你，然后追上来向你挑战。\p所以要躲过训练家的话，\n不要让他们看到你，\l要偷偷摸摸地绕过他们。$"

BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems:
    .string "哇啊啊啊啊啊啊！\p我已经攒了那么多道具，却一不小心\n失败了，现在道具全没了！\p哇啊啊啊啊啊啊！$"

BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing:
    .string "欢迎回来！\n您完成了不可思议的壮举！\p您打败了金字塔法老，\n并征服了对战金字塔！$"

BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints:
    .string "年轻的探险家啊！\n为了表彰您的勇气，\l我们将向您呈上对战点数！$"

BattleFrontier_BattlePyramidLobby_Text_RulesAreListed:
    .string "上面列出了探索式对战的规则。$"

BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading:
    .string "要读哪一部分的说明？$"

BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules:
    .string "当征服金字塔后，\n里面的野生宝可梦会\l替换成其他的种类，\p仔细探索，仔细观察，尽量去了解\n您可能遇到什么样的宝可梦。$"

BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules:
    .string "在金字塔内会有训练家\n等着向您挑战。\p每层最多会有\n8个训练家。\p您每打败1个训练家，就会得到1条\n对探索有用的提示。$"

BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules:
    .string "每次进入金字塔后迷宫\n都会重新组合，\p迷宫里很暗，\n必须小心探索。\p每打败1个训练家或是1只野生宝可梦\n，里面都会稍微变亮一些。$"

BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules:
    .string "在金字塔中，您可以像使用\n您的包包一样使用战斗包包。\p有2种不同的战斗包包——\n分别是为Lv. 50级和\l自由等级的冒险而准备的。\p2种包包都可以携带10种道具，\n每种道具99个。\p如果在探索中失败的话，\n战斗包包里的东西都会丢失。$"

