Route104_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route104_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, Route104_OnTransition
	.byte 0

Route104_OnFrame:
	map_script_2 VAR_BOARD_BRINEY_BOAT_STATE, 1, Route104_EventScript_StartSailToDewford
	.2byte 0

Route104_EventScript_StartSailToDewford::
	lockall
	goto Route104_EventScript_SailToDewford
	end

Route104_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call Route104_EventScript_TrySetRivalPos
	call Route104_EventScript_ShowOrHideWhiteHerbFlorist
	end

Route104_EventScript_ShowOrHideWhiteHerbFlorist::
	goto_if_unset FLAG_MET_PRETTY_PETAL_SHOP_OWNER, Route104_EventScript_HideWhiteHerbFlorist
	goto_if_unset FLAG_BADGE03_GET, Route104_EventScript_HideWhiteHerbFlorist
	clearflag FLAG_HIDE_ROUTE_104_WHITE_HERB_FLORIST
	return

Route104_EventScript_HideWhiteHerbFlorist::
	setflag FLAG_HIDE_ROUTE_104_WHITE_HERB_FLORIST
	return

Route104_EventScript_TrySetRivalPos::
	goto_if_ge VAR_BOARD_BRINEY_BOAT_STATE, 1, Route104_EventScript_DontSetRivalPos
	goto_if_set FLAG_MET_RIVAL_RUSTBORO, Route104_EventScript_DontSetRivalPos
	goto_if_unset FLAG_REGISTER_RIVAL_POKENAV, Route104_EventScript_DontSetRivalPos
	setobjectxyperm LOCALID_ROUTE104_RIVAL, 17, 52
	return

Route104_EventScript_DontSetRivalPos::
	return

Route104_EventScript_Rival::
	lockall
	setvar VAR_0x8008, 1
	applymovement LOCALID_ROUTE104_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	goto Route104_EventScript_RivalEncounter

Route104_EventScript_RivalTrigger::
	lockall
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setvar VAR_RUSTBORO_CITY_STATE, 8
	setvar VAR_ROUTE104_STATE, 2
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 10
	addobject LOCALID_ROUTE104_RIVAL
	clearflag FLAG_HIDE_ROUTE_104_RIVAL
	applymovement LOCALID_PLAYER, Route104_Movement_PlayerBackUp
	waitmovement 0
	applymovement LOCALID_ROUTE104_RIVAL, Route104_Movement_RivalExitBrineysCottage
	waitmovement 0
	delay 20
	setvar VAR_0x8008, 0
	call RustboroCity_EventScript_PlayRivalMusic
	playse SE_PIN
	applymovement LOCALID_ROUTE104_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_ROUTE104_RIVAL, Common_Movement_Delay48
	waitmovement 0
	goto Route104_EventScript_RivalEncounter

@ Unused, shares script with Rustboro encounter instead
Route104_EventScript_PlayRivalMusic::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route104_EventScript_PlayMayMusic
	goto_if_eq VAR_RESULT, FEMALE, Route104_EventScript_PlayBrendanMusic
	return

Route104_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

Route104_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

Route104_EventScript_RivalEncounter::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route104_EventScript_MayEncounter
	goto_if_eq VAR_RESULT, FEMALE, Route104_EventScript_BrendanEncounter
	end

Route104_EventScript_MayEncounter::
	goto_if_set FLAG_DEFEATED_RIVAL_ROUTE_104, Route104_EventScript_MayDefeated
	goto_if_set FLAG_REGISTER_RIVAL_POKENAV, Route104_EventScript_MayAskToBattle
	setflag FLAG_REGISTER_RIVAL_POKENAV
	msgbox Route104_Text_MayWeShouldRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route104_Text_RegisteredMay, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	applymovement LOCALID_PLAYER, Route104_Movement_PlayerFaceRival
	applymovement LOCALID_ROUTE104_RIVAL, Route104_Movement_RivalWalkSlowLeft
	msgbox Route104_Text_MayHowsYourPokedex, MSGBOX_DEFAULT
	closemessage
	waitmovement 0
	applymovement LOCALID_ROUTE104_RIVAL, Route104_Movement_RivalApproachPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_ROUTE104_RIVAL
	msgbox Route104_Text_MayMinesDecentLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleMay
	msgbox Route104_Text_MayHaventRaisedPokemon, MSGBOX_DEFAULT
	call Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_Movement_RivalWalkSlowLeft:
	walk_slow_left
	step_end

Route104_Movement_RivalApproachPlayer:
	walk_down
	face_right
	step_end

Route104_Movement_PlayerFaceRival:
	delay_4
	walk_in_place_faster_left
	step_end

Route104_EventScript_MayAskToBattle::
	msgbox Route104_Text_MayLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleMay
	msgbox Route104_Text_MayHaventRaisedPokemon, MSGBOX_DEFAULT
	releaseall
	end

Route104_EventScript_BattleMay::
	msgbox Route104_Text_MayIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route104_EventScript_BattleMayTreecko
	case 1, Route104_EventScript_BattleMayTorchic
	case 2, Route104_EventScript_BattleMayMudkip
	end

Route104_EventScript_MayDefeated::
	msgbox Route104_Text_MayPostBattle, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, 0, Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_EventScript_RestoreMusic::
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

Route104_EventScript_BattleMayTreecko::
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TREECKO, Route104_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_MayDefeated
	end

Route104_EventScript_BattleMayTorchic::
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TORCHIC, Route104_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_MayDefeated
	end

Route104_EventScript_BattleMayMudkip::
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_MUDKIP, Route104_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_MayDefeated
	end

Route104_EventScript_BrendanEncounter::
	goto_if_set FLAG_DEFEATED_RIVAL_ROUTE_104, Route104_EventScript_BrendanDefeated
	goto_if_set FLAG_REGISTER_RIVAL_POKENAV, Route104_EventScript_BrendanAskToBattle
	setflag FLAG_REGISTER_RIVAL_POKENAV
	msgbox Route104_Text_BrendanWeShouldRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route104_Text_RegisteredBrendan, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	applymovement LOCALID_PLAYER, Route104_Movement_PlayerFaceRival
	applymovement LOCALID_ROUTE104_RIVAL, Route104_Movement_RivalWalkSlowLeft
	msgbox Route104_Text_BrendanHowsYourPokedex, MSGBOX_DEFAULT
	closemessage
	waitmovement 0
	applymovement LOCALID_ROUTE104_RIVAL, Route104_Movement_RivalApproachPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_ROUTE104_RIVAL
	msgbox Route104_Text_BrendanDoingGreatLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleBrendan
	msgbox Route104_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	call Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_EventScript_BrendanAskToBattle::
	msgbox Route104_Text_BrendanLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleBrendan
	msgbox Route104_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	releaseall
	end

Route104_EventScript_BattleBrendan::
	msgbox Route104_Text_BrendanIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route104_EventScript_BattleBrendanTreecko
	case 1, Route104_EventScript_BattleBrendanTorchic
	case 2, Route104_EventScript_BattleBrendanMudkip
	end

Route104_EventScript_BrendanDefeated::
	msgbox Route104_Text_BrendanPostBattle, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, 0, Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_EventScript_BattleBrendanTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TREECKO, Route104_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_BrendanDefeated
	end

Route104_EventScript_BattleBrendanTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TORCHIC, Route104_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_BrendanDefeated
	end

Route104_EventScript_BattleBrendanMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_MUDKIP, Route104_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_BrendanDefeated
	end

Route104_Movement_PlayerBackUp:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

Route104_Movement_RivalExitBrineysCottage:
	walk_down
	step_end

Route104_EventScript_ExpertF::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CHESTO_BERRY_ROUTE_104, Route104_EventScript_ReceivedBerry
	msgbox Route104_Text_PlantBerriesInSoilTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_CHESTO_BERRY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CHESTO_BERRY_ROUTE_104
	msgbox Route104_Text_TrainersOftenMakeMonHoldBerries, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_ReceivedBerry::
	msgbox Route104_Text_TrainersOftenMakeMonHoldBerries, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_WhiteHerbFlorist::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_WHITE_HERB, Route104_EventScript_ReceivedWhiteHerb
	msgbox Route104_Text_DontNeedThisTakeIt, MSGBOX_DEFAULT
	giveitem ITEM_WHITE_HERB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_WHITE_HERB
	release
	end

Route104_EventScript_ReceivedWhiteHerb::
	msgbox Route104_Text_FlowerShopSellingSaplings, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Girl1::
	msgbox Route104_Text_BrineyLivesInSeasideCottage, MSGBOX_NPC
	end

Route104_EventScript_BugCatcher::
	msgbox Route104_Text_WhatsItLikeAtBottomOfSea, MSGBOX_SIGN
	end

Route104_EventScript_BrineysCottageSign::
	msgbox Route104_Text_MrBrineysCottage, MSGBOX_SIGN
	end

Route104_EventScript_RouteSignPetalburg::
	msgbox Route104_Text_RouteSignPetalburg, MSGBOX_SIGN
	end

Route104_EventScript_RouteSignRustboro::
	msgbox Route104_Text_RouteSignRustboro, MSGBOX_SIGN
	end

Route104_EventScript_FlowerShopSign::
	msgbox Route104_Text_PrettyPetalFlowShop, MSGBOX_SIGN
	end

Route104_EventScript_TrainerTipsDoubleBattles::
	msgbox Route104_Text_TrainerTipsDoubleBattles, MSGBOX_SIGN
	end

Route104_EventScript_Boy1::
	msgbox Route104_Text_ThrowBallAtWeakenedPokemon, MSGBOX_NPC
	end

Route104_EventScript_Woman::
	msgbox Route104_Text_OnlyThrowBallAtWildPokemon, MSGBOX_NPC
	end

Route104_EventScript_Boy2::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_BULLET_SEED, Route104_EventScript_ReceivedBulletSeed
	msgbox Route104_Text_LikeFillingMouthWithSeedsTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_BULLET_SEED
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_BULLET_SEED
	release
	end

Route104_EventScript_ReceivedBulletSeed::
	msgbox Route104_Text_TMsAreOneTimeUse, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Girl2::
	msgbox Route104_Text_ImNotATrainer, MSGBOX_NPC
	end

Route104_EventScript_SailToDewford::
	setobjectsubpriority LOCALID_ROUTE104_BRINEY, MAP_ROUTE104, 0
	setobjectsubpriority LOCALID_PLAYER, MAP_ROUTE104, 0
	applymovement LOCALID_ROUTE104_BRINEY, Route104_Movement_BrineyBoardBoat
	waitmovement 0
	removeobject LOCALID_ROUTE104_BRINEY
	applymovement LOCALID_PLAYER, Route104_Movement_PlayerBoardBoat
	waitmovement 0
	hideobjectat LOCALID_PLAYER, MAP_ROUTE104
	call Common_EventScript_PlayBrineysBoatMusic
	goto_if_set FLAG_ENABLE_NORMAN_MATCH_CALL, Route104_EventScript_SailToDewfordNoCall
	goto_if_unset FLAG_ENABLE_NORMAN_MATCH_CALL, Route104_EventScript_SailToDewfordDadCalls
	end

Route104_EventScript_SailToDewfordNoCall::
	applymovement LOCALID_ROUTE104_BOAT, Route104_Movement_SailToDewford
	applymovement LOCALID_PLAYER, Route104_Movement_SailToDewford
	waitmovement 0
	goto Route104_EventScript_ArriveInDewford

Route104_EventScript_SailToDewfordDadCalls::
	applymovement LOCALID_ROUTE104_BOAT, Route104_Movement_SailToDewfordBeforeDadCalls
	applymovement LOCALID_PLAYER, Route104_Movement_SailToDewfordBeforeDadCalls
	waitmovement 0
	pokenavcall Route104_Text_DadPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route104_Text_RegisteredDadInPokenav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_NORMAN_MATCH_CALL
	applymovement LOCALID_PLAYER, Route104_Movement_SailToDewfordAfterDadCalls
	applymovement LOCALID_ROUTE104_BOAT, Route104_Movement_SailToDewfordAfterDadCalls, MAP_ROUTE104
	waitmovement LOCALID_ROUTE104_BOAT, MAP_ROUTE104
	waitmovement 0
	goto Route104_EventScript_ArriveInDewford

Route104_EventScript_ArriveInDewford::
	delay 50
	applymovement LOCALID_PLAYER, Route104_Movement_PlayerExitBoat
	waitmovement 0
	call Common_EventScript_StopBrineysBoatMusic
	showobjectat LOCALID_PLAYER, MAP_DEWFORD_TOWN
	applymovement LOCALID_PLAYER, Route104_Movement_PlayerMoveForBriney
	waitmovement 0
	setobjectxyperm LOCALID_DEWFORD_BRINEY, 12, 8
	addobject LOCALID_DEWFORD_BRINEY
	setobjectsubpriority LOCALID_DEWFORD_BRINEY, MAP_DEWFORD_TOWN, 0
	clearflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	applymovement LOCALID_DEWFORD_BRINEY, Route104_Movement_BrineyExitBoat
	waitmovement 0
	addobject LOCALID_DEWFORD_BOAT
	clearflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	call Common_EventScript_StopBrineysBoatMusic
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	hideobjectat LOCALID_ROUTE104_BOAT, MAP_ROUTE104
	copyvar VAR_BRINEY_LOCATION, VAR_0x8008
	resetobjectsubpriority LOCALID_PLAYER, MAP_ROUTE104
	resetobjectsubpriority LOCALID_DEWFORD_BRINEY, MAP_DEWFORD_TOWN
	copyobjectxytoperm LOCALID_DEWFORD_BRINEY
	setvar VAR_BOARD_BRINEY_BOAT_STATE, 0
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, Route104_EventScript_DeliverLetterReminder
	goto_if_set FLAG_DELIVERED_STEVEN_LETTER, Route104_EventScript_LandedInDewford
	end

Route104_EventScript_DeliverLetterReminder::
	msgbox Route104_Text_LandedInDewfordDeliverLetter, MSGBOX_DEFAULT
	releaseall
	end

Route104_EventScript_LandedInDewford::
	msgbox DewfordTown_Text_BrineyLandedInDewford, MSGBOX_DEFAULT
	releaseall
	end

Route104_Movement_SailToDewfordBeforeDadCalls:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	step_end

Route104_Movement_SailToDewfordAfterDadCalls:
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_down
	walk_down
	step_end

Route104_Movement_SailToDewford:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_down
	walk_down
	step_end

Route104_Movement_PlayerBoardBoat:
	walk_left
	walk_down
	walk_down
	step_end

Route104_Movement_PlayerExitBoat:
	walk_down
	step_end

Route104_Movement_PlayerMoveForBriney:
	walk_down
	walk_left
	walk_in_place_faster_right
	step_end

Route104_Movement_BrineyBoardBoat:
	walk_down
	walk_down
	step_end

Route104_Movement_BrineyExitBoat:
	walk_down
	walk_in_place_faster_left
	step_end

Route104_EventScript_Ivan::
	trainerbattle_single TRAINER_IVAN, Route104_Text_IvanIntro, Route104_Text_IvanDefeat
	msgbox Route104_Text_IvanPostBattle, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Billy::
	trainerbattle_single TRAINER_BILLY, Route104_Text_BillyIntro, Route104_Text_BillyDefeat
	msgbox Route104_Text_BillyPostBattle, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Haley::
	trainerbattle_single TRAINER_HALEY_1, Route104_Text_HaleyIntro, Route104_Text_HaleyDefeat, Route104_EventScript_TryRegisterHaleyAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route104_EventScript_RematchHaley
	setvar VAR_0x8004, TRAINER_HALEY_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route104_EventScript_TryRegisterHaley
	msgbox Route104_Text_HaleyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_TryRegisterHaleyAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterHaleyAfterBattle
	release
	end

Route104_EventScript_RegisterHaleyAfterBattle::
	msgbox Route104_Text_HaleyRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_HALEY_1
	release
	end

Route104_EventScript_TryRegisterHaley::
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterHaley
	msgbox Route104_Text_HaleyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_RegisterHaley::
	msgbox Route104_Text_HaleyRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_HALEY_1
	release
	end

Route104_EventScript_RematchHaley::
	trainerbattle_rematch TRAINER_HALEY_1, Route104_Text_HaleyRematchIntro, Route104_Text_HaleyRematchDefeat
	msgbox Route104_Text_HaleyPostRematch, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Winston::
	trainerbattle_single TRAINER_WINSTON_1, Route104_Text_WinstonIntro, Route104_Text_WinstonDefeat, Route104_EventScript_TryRegisterWinstonAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route104_EventScript_RematchWinston
	setvar VAR_0x8004, TRAINER_WINSTON_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route104_EventScript_TryRegisterWinston
	msgbox Route104_Text_WinstonPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_TryRegisterWinstonAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterWinstonAfterBattle
	release
	end

Route104_EventScript_RegisterWinstonAfterBattle::
	msgbox Route104_Text_WinstonRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_WINSTON_1
	release
	end

Route104_EventScript_TryRegisterWinston::
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterWinston
	msgbox Route104_Text_WinstonPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_RegisterWinston::
	msgbox Route104_Text_WinstonRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_WINSTON_1
	release
	end

Route104_EventScript_RematchWinston::
	trainerbattle_rematch TRAINER_WINSTON_1, Route104_Text_WinstonRematchIntro, Route104_Text_WinstonRematchDefeat
	msgbox Route104_Text_WinstonPostRematch, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Cindy::
	trainerbattle_single TRAINER_CINDY_1, Route104_Text_CindyIntro, Route104_Text_CindyDefeat, Route104_EventScript_TryRegisterCindyAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route104_EventScript_RematchCindy
	setvar VAR_0x8004, TRAINER_CINDY_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route104_EventScript_TryRegisterCindy
	msgbox Route104_Text_CindyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_TryRegisterCindyAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterCindyAfterBattle
	release
	end

Route104_EventScript_RegisterCindyAfterBattle::
	msgbox Route104_Text_CindyRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_CINDY_1
	release
	end

Route104_EventScript_TryRegisterCindy::
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterCindy
	msgbox Route104_Text_CindyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_RegisterCindy::
	msgbox Route104_Text_CindyRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_CINDY_1
	release
	end

Route104_EventScript_RematchCindy::
	trainerbattle_rematch TRAINER_CINDY_1, Route104_Text_CindyRematchIntro, Route104_Text_CindyRematchDefeat
	msgbox Route104_Text_CindyPostRematch, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Gina::
	trainerbattle_double TRAINER_GINA_AND_MIA_1, Route104_Text_GinaIntro, Route104_Text_GinaDefeat, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route104_Text_GinaPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Mia::
	trainerbattle_double TRAINER_GINA_AND_MIA_1, Route104_Text_MiaIntro, Route104_Text_MiaDefeat, Route104_Text_MiaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route104_Text_MiaPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Darian::
	trainerbattle_single TRAINER_DARIAN, Route104_Text_DarianIntro, Route104_Text_DarianDefeat
	msgbox Route104_Text_DarianPostBattle, MSGBOX_AUTOCLOSE
	end

Route104_Text_BrineyLivesInSeasideCottage:
    .string "那就是哈奇老人住的海边小屋。\n他曾经是个伟大的水手，\p即使永远都是风雨交加，\n他也从未害怕过大海。$"

Route104_Text_WhatsItLikeAtBottomOfSea:
    .string "大海，嗯？\p不知道海底\n是什么样子的？$"

Route104_Text_ThrowBallAtWeakenedPokemon:
    .string "投出精灵球之前，\n要先让野生宝可梦变弱。\p如果它中毒或被灼伤、催眠的话，\n会更容易捕捉到它。$"

Route104_Text_OnlyThrowBallAtWildPokemon:
    .string "你不能偷\n别人的宝可梦，\p你只能向野生的宝可梦\n投掷精灵球。$"

Route104_Text_ImNotATrainer:
    .string "哦，不，\n我不是训练家，\p但要是被训练家看见的话，\n他们就会向你挑战。\p如果你不想对战，\n最好躲着他们的视线。$"

Route104_Text_LikeFillingMouthWithSeedsTakeThis:
    .string "我喜欢在嘴里塞满种子，\n然后飞速射出去！\p这个给你，你也可以试试！\p把它给宝可梦使用，宝可梦就能\n学会快速射出种子的招式。$"

Route104_Text_TMsAreOneTimeUse:
    .string "要提醒你！\pTM，就是招式学习器，\n只能使用一次。\p一旦你用了，它就会消失。\n所以使用之前要三思！$"

Route104_Text_DontNeedThisTakeIt:
    .string "这间花店最近\n开始卖小树，\p我太兴奋了，\n买了太多的东西。\p这个白色香草我不需要了，\n你想要吗？$"

Route104_Text_FlowerShopSellingSaplings:
    .string "这间花店最近\n开始卖小树，\p我太兴奋了，买了太多的东西。\n我该把它们放在哪儿呢？$"

Route104_Text_MrBrineysCottage:
    .string "哈奇老人的小屋$"

Route104_Text_RouteSignPetalburg:
    .string "1O4号道路\n{RIGHT_ARROW}橙华市$"

Route104_Text_RouteSignRustboro:
    .string "104号道路\n{UP_ARROW}卡那兹市$"

Route104_Text_PrettyPetalFlowShop:
    .string "圣橙华花店$"

Route104_Text_TrainerTipsDoubleBattles:
    .string "有用的公告牌！\p在丰缘地区中，一些结伴的训练家会向\n别人发起2对2的挑战，称作双打对战。\p在双打对战中，\n训练家要派出2只宝可梦，\l即列表左边的和最上边的。\l一定要注意宝可梦的排列顺序。$"

Route104_Text_MayWeShouldRegister:
    .string "小遥：啊，{PLAYER}{KUN}！\p得文给你的宝可导航装了\n对战寻呼系统对吧？\p我们互相登记一下信息吧，\n这样就能随时联系了。$"

Route104_Text_RegisteredMay:
    .string "{PLAYER}把小遥\n登记到宝可导航里了。$"

Route104_Text_MayHowsYourPokedex:
    .string "小遥：对了，{PLAYER}{KUN}，\n你的宝可梦图鉴进展如何？$"

Route104_Text_MayMinesDecentLetsBattle:
    .string "我这边已经很充实了。\n所以……\l要不要来场对战？$"

Route104_Text_MayHaventRaisedPokemon:
    .string "小遥：哎——为什么？\p你没有好好捕捉和培育\n宝可梦吗？\p作为训练家可不应该这样！$"

Route104_Text_MayLetsBattle:
    .string "小遥：所以，怎么样？\n要不要来场对战？$"

Route104_Text_MayIntro:
    .string "小遥：你刚刚成为训练家，\n{PLAYER}{KUN}。我可不会输哦！$"

Route104_Text_MayDefeat:
    .string "呜哇！\n比想象中厉害得多……$"

Route104_Text_MayPostBattle:
    .string "小遥：你的宝可梦\n培育得不错嘛！\p不过也不要只顾着战斗，\n像哈奇老人那样和宝可梦\l做朋友也很重要哦！$"

Route104_Text_BrendanWeShouldRegister:
    .string "小悠：嘿，{PLAYER}！\p得文给你的宝可导航\n装了对战寻呼系统吧？\p我们互相登记一下信息吧，\n这样我们就能随时联系了。$"

Route104_Text_RegisteredBrendan:
    .string "把小悠\n登记到宝可导航里了。$"

Route104_Text_BrendanHowsYourPokedex:
    .string "小悠：{PLAYER}，你的宝可梦图鉴进展如何？\n有几页了吗？$"

Route104_Text_BrendanDoingGreatLetsBattle:
    .string "我？我这边很顺利！\p来场对战让你看看\n我的成果如何？$"

Route104_Text_BrendanNoConfidence:
    .string "小悠：怎么了？\n对自己的宝可梦没信心吗？$"

Route104_Text_BrendanLetsBattle:
    .string "小悠：怎样？\n想和我来场对战吗？$"

Route104_Text_BrendanIntro:
    .string "小悠：虽然你刚成为训练家，\n但我不会手下留情哦！$"

Route104_Text_BrendanDefeat:
    .string "嘿……\n挺能干的嘛。$"

Route104_Text_BrendanPostBattle:
    .string "小悠：你在培育宝可梦方面\n很有天赋啊，\p但要知道，\n你不能只顾着让宝可梦战斗。\p像哈奇老人那样，\n和宝可梦做朋友也很重要。$"
