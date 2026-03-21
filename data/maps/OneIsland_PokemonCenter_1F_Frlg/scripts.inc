OneIsland_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OneIsland_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	map_script MAP_SCRIPT_ON_LOAD, OneIsland_PokemonCenter_1F_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OneIsland_PokemonCenter_1F_OnFrame
	.byte 0

OneIsland_PokemonCenter_1F_OnLoad::
	call_if_ge VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 5, OneIsland_PokemonCenter_1F_EventScript_SetRubyMetatile
	call_if_set FLAG_IS_CHAMPION, OneIsland_PokemonCenter_1F_EventScript_SetNetworkMachineOn
	end

OneIsland_PokemonCenter_1F_EventScript_SetRubyMetatile::
	setmetatile 13, 4, METATILE_PokemonCenterFrlg_NetworkMachine_Ruby, 1
	return

OneIsland_PokemonCenter_1F_EventScript_SetSapphireMetatile::
	setmetatile 16, 4, METATILE_PokemonCenterFrlg_NetworkMachine_Sapphire, 1
	return

OneIsland_PokemonCenter_1F_EventScript_SetNetworkMachineOn::
	call OneIsland_PokemonCenter_1F_EventScript_SetSapphireMetatile
	setmetatile 14, 4, METATILE_PokemonCenterFrlg_NetworkMachine_ScreenLeft_On, 1
	setmetatile 15, 4, METATILE_PokemonCenterFrlg_NetworkMachine_ScreenRight_On, 1
	return

OneIsland_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_ONE_ISLAND
	call_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 6, OneIsland_PokemonCenter_1F_EventScript_SetCelioQuestDone
	call_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 0, OneIsland_PokemonCenter_1F_EventScript_SetBillCelioFirstMeetingPos
	call_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 2, OneIsland_PokemonCenter_1F_EventScript_SetBillCelioReadyToLeavePos
	end

OneIsland_PokemonCenter_1F_EventScript_SetCelioQuestDone::
	setvar VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 7
	return

OneIsland_PokemonCenter_1F_EventScript_SetBillCelioFirstMeetingPos::
	setobjectxyperm LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, 9, 8
	setobjectmovementtype LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, MOVEMENT_TYPE_FACE_UP
	setobjectxyperm LOCALID_CELIO, 15, 6
	setobjectmovementtype LOCALID_CELIO, MOVEMENT_TYPE_FACE_UP
	return

OneIsland_PokemonCenter_1F_EventScript_SetBillCelioReadyToLeavePos::
	setobjectxyperm LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, 14, 7
	setobjectmovementtype LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, MOVEMENT_TYPE_FACE_LEFT
	setobjectxyperm LOCALID_CELIO, 14, 8
	setobjectmovementtype LOCALID_CELIO, MOVEMENT_TYPE_FACE_LEFT
	return

OneIsland_PokemonCenter_1F_OnFrame::
	map_script_2 VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 0, OneIsland_PokemonCenter_1F_EventScript_MeetCelioScene
	.2byte 0

OneIsland_PokemonCenter_1F_EventScript_MeetCelioScene::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_PLAYER, OneIsland_PokemonCenter_1F_Movement_PlayerWalkToCelio
	applymovement LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, OneIsland_PokemonCenter_1F_Movement_BillWalkToCelio
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_BillHeyThereCelio
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_CELIO, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_CELIO, Common_Movement_Delay48
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_CelioCantBelieveYouCameOut
	msgbox OneIsland_PokemonCenter_1F_Text_BillHowsYourResearchComing
	applymovement LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_ThisIsMyBuddyCelio
	applymovement LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	call_if_set FLAG_SYS_GAME_CLEAR, OneIsland_PokemonCenter_1F_EventScript_IntroducePlayerChamp
	call_if_unset FLAG_SYS_GAME_CLEAR, OneIsland_PokemonCenter_1F_EventScript_IntroducePlayerNotChamp
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_CelioThatsReallyImpressive
	msgbox OneIsland_PokemonCenter_1F_Text_BillBringMeUpToSpeed
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_CelioPCsCantLinkWithYours
	closemessage
	applymovement LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_BillLetMeHelpYou
	applymovement LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_CanYouDeliverThisMeteoritePlayer
	msgreceiveditem OneIsland_PokemonCenter_1F_Text_AcceptedMeteoriteFromBill, ITEM_METEORITE, 1, MUS_RG_OBTAIN_KEY_ITEM
	additem ITEM_METEORITE
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_CelioPleaseTakeThis
	giveitem_msg OneIsland_PokemonCenter_1F_Text_ObtainedTriPass, ITEM_TRI_PASS, 1, MUS_RG_OBTAIN_KEY_ITEM
	msgbox OneIsland_PokemonCenter_1F_Text_PassLetsYouTravelBetweenIslands
	call_if_ge VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 2, OneIsland_PokemonCenter_1F_EventScript_ReceiveTownMapPage
	call_if_lt VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 2, OneIsland_PokemonCenter_1F_EventScript_ReceiveTownMap
	setflag FLAG_SYS_SEVII_MAP_123
	msgbox OneIsland_PokemonCenter_1F_Text_BillCatchYouLater
	closemessage
	applymovement LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	setflag FLAG_SYS_PC_STORAGE_DISABLED
	setvar VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 1
	releaseall
	end

OneIsland_PokemonCenter_1F_EventScript_IntroducePlayerChamp::
	msgbox OneIsland_PokemonCenter_1F_Text_PlayerIsReigningPokemonChamp
	return

OneIsland_PokemonCenter_1F_EventScript_IntroducePlayerNotChamp::
	msgbox OneIsland_PokemonCenter_1F_Text_PlayerIsRisingPokemonChamp
	return

OneIsland_PokemonCenter_1F_EventScript_ReceiveTownMapPage::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message OneIsland_PokemonCenter_1F_Text_ReceivedExtraPageForTownMap
	waitmessage
	waitfanfare
	call EventScript_RestorePrevTextColor
	return

OneIsland_PokemonCenter_1F_EventScript_ReceiveTownMap::
	setflag FLAG_HIDE_TOWN_MAP
	setvar VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 2
	giveitem_msg OneIsland_PokemonCenter_1F_Text_ReceivedTownMap, ITEM_TOWN_MAP, 1, MUS_RG_OBTAIN_KEY_ITEM
	return

OneIsland_PokemonCenter_1F_Movement_PlayerWalkToCelio::
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

OneIsland_PokemonCenter_1F_Movement_BillWalkToCelio::
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_in_place_faster_right
	step_end

@ Unused
OneIsland_PokemonCenter_1F_Movement_WalkUp:
	walk_up
	step_end

@ Unused
OneIsland_PokemonCenter_1F_Movement_StepAsideLeft::
	walk_left
	walk_in_place_faster_right
	step_end

OneIsland_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

OneIsland_PokemonCenter_1F_EventScript_Bill::
	lock
	goto_if_set FLAG_SEVII_DETOUR_FINISHED, OneIsland_PokemonCenter_1F_EventScript_BillGoTakeStroll
	msgbox OneIsland_PokemonCenter_1F_Text_HmmHowAboutLikeThis
	release
	end

OneIsland_PokemonCenter_1F_EventScript_BillGoTakeStroll::
	applymovement LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, Common_Movement_FacePlayer
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_GotPCWorkingStrollAWhileMore
	release
	end

OneIsland_PokemonCenter_1F_EventScript_Celio::
	lock
	faceplayer
	goto_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 7, OneIsland_PokemonCenter_1F_EventScript_CelioGiveBillFact
	goto_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 6, OneIsland_PokemonCenter_1F_EventScript_CelioJustGivenSapphire
	goto_if_set FLAG_RECOVERED_SAPPHIRE, OneIsland_PokemonCenter_1F_EventScript_GiveCelioSapphire
	goto_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 5, OneIsland_PokemonCenter_1F_EventScript_ExplainRainbowPass
	goto_if_set FLAG_GOT_RUBY, OneIsland_PokemonCenter_1F_EventScript_GiveCelioRuby
	goto_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 4, OneIsland_PokemonCenter_1F_EventScript_CelioWaitingForRuby
	specialvar VAR_RESULT, IsNationalPokedexEnabled
	goto_if_eq VAR_RESULT, TRUE, OneIsland_PokemonCenter_1F_EventScript_CelioRequestRuby
	goto_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 3, OneIsland_PokemonCenter_1F_EventScript_CelioPlayerMissingNationalDex
	msgbox OneIsland_PokemonCenter_1F_Text_SorryForBeingPoorHost
	closemessage
	applymovement LOCALID_CELIO, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

OneIsland_PokemonCenter_1F_EventScript_CelioGiveBillFact::
	msgbox OneIsland_PokemonCenter_1F_Text_CelioHearingRumorsAboutYou
	random 3
	goto_if_eq VAR_RESULT, 0, OneIsland_PokemonCenter_1F_EventScript_BillFact1
	goto_if_eq VAR_RESULT, 1, OneIsland_PokemonCenter_1F_EventScript_BillFact2
	famechecker FAMECHECKER_BILL, 5
	msgbox OneIsland_PokemonCenter_1F_Text_BillCantStomachMilk
	release
	end

OneIsland_PokemonCenter_1F_EventScript_BillFact1::
	famechecker FAMECHECKER_BILL, 3
	msgbox OneIsland_PokemonCenter_1F_Text_BillsFirstMonWasAbra
	release
	end

OneIsland_PokemonCenter_1F_EventScript_BillFact2::
	famechecker FAMECHECKER_BILL, 4
	msgbox OneIsland_PokemonCenter_1F_Text_BillsHometownInGoldenrod
	release
	end

OneIsland_PokemonCenter_1F_EventScript_CelioJustGivenSapphire::
	msgbox OneIsland_PokemonCenter_1F_Text_WishYouBestOfLuck
	release
	end

OneIsland_PokemonCenter_1F_EventScript_GiveCelioSapphire::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	playfanfare MUS_OBTAIN_TMHM
	message OneIsland_PokemonCenter_1F_Text_HandedSapphireToCelio
	waitmessage
	waitfanfare
	call EventScript_RestorePrevTextColor
	removeitem ITEM_SAPPHIRE
	msgbox OneIsland_PokemonCenter_1F_Text_ThankYouGiveMeTime
	closemessage
	applymovement LOCALID_CELIO, OneIsland_PokemonCenter_1F_Movement_CelioPutGemInMachine
	waitmovement 0
	playse SE_CLICK
	call OneIsland_PokemonCenter_1F_EventScript_SetSapphireMetatile
	special DrawWholeMapView
	msgbox OneIsland_PokemonCenter_1F_Text_OkayThisIsGood
	closemessage
	delay 60
	applymovement LOCALID_CELIO, OneIsland_PokemonCenter_1F_Movement_CelioCheckMachine
	waitmovement 0
	delay 30
	applymovement LOCALID_CELIO, OneIsland_PokemonCenter_1F_Movement_CelioCheckMachine
	waitmovement 0
	delay 40
	playse SE_PC_ON
	call OneIsland_PokemonCenter_1F_EventScript_SetNetworkMachineOn
	special DrawWholeMapView
	msgbox OneIsland_PokemonCenter_1F_Text_LinkedUpWithLanette
	applymovement LOCALID_CELIO, Common_Movement_FacePlayer
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_ManagedToLinkWithHoennThankYou
	special SetPostgameFlags
	setflag FLAG_IS_CHAMPION
	setflag FLAG_HIDE_CERULEAN_CAVE_GUARD
	setflag FLAG_HIDE_LORELEI_IN_HER_HOUSE
	setvar VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 6
	special InitRoamer
	release
	end

OneIsland_PokemonCenter_1F_EventScript_ExplainRainbowPass::
	msgbox OneIsland_PokemonCenter_1F_Text_PassLetYouGetToAllIslands
	release
	end

OneIsland_PokemonCenter_1F_EventScript_GiveCelioRuby::
	msgbox OneIsland_PokemonCenter_1F_Text_OhThats
	textcolor NPC_TEXT_COLOR_NEUTRAL
	playfanfare MUS_OBTAIN_TMHM
	message OneIsland_PokemonCenter_1F_Text_HandedRubyToCelio
	waitmessage
	waitfanfare
	call EventScript_RestorePrevTextColor
	closemessage
	applymovement LOCALID_CELIO, OneIsland_PokemonCenter_1F_Movement_CelioPutGemInMachine
	waitmovement 0
	playse SE_CLICK
	call OneIsland_PokemonCenter_1F_EventScript_SetRubyMetatile
	special DrawWholeMapView
	delay 30
	applymovement LOCALID_CELIO, Common_Movement_FacePlayer
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_MayIAskOneMoreFavor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, OneIsland_PokemonCenter_1F_EventScript_DeclineHelpCelio
	goto OneIsland_PokemonCenter_1F_EventScript_GiveRainbowPass
	end

OneIsland_PokemonCenter_1F_EventScript_DeclineHelpCelio::
	msgbox OneIsland_PokemonCenter_1F_Text_PleaseINeedYourHelp, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, OneIsland_PokemonCenter_1F_EventScript_DeclineHelpCelio
	goto OneIsland_PokemonCenter_1F_EventScript_GiveRainbowPass
	end

OneIsland_PokemonCenter_1F_EventScript_GiveRainbowPass::
	msgbox OneIsland_PokemonCenter_1F_Text_AnotherGemstoneInSeviiIslands
	removeitem ITEM_RUBY
	removeitem ITEM_TRI_PASS
	setvar VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 5
	additem ITEM_RAINBOW_PASS
	setflag FLAG_SYS_SEVII_MAP_4567
	textcolor NPC_TEXT_COLOR_NEUTRAL
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message OneIsland_PokemonCenter_1F_Text_ReturnedTriPassForRainbowPass
	waitmessage
	waitfanfare
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message OneIsland_PokemonCenter_1F_Text_ObtainedExtraMapPage
	waitmessage
	waitfanfare
	call EventScript_RestorePrevTextColor
	goto OneIsland_PokemonCenter_1F_EventScript_ExplainRainbowPass
	end

OneIsland_PokemonCenter_1F_EventScript_CelioWaitingForRuby::
	msgbox OneIsland_PokemonCenter_1F_Text_TryingToFindGem
	release
	end

OneIsland_PokemonCenter_1F_EventScript_CelioRequestRuby::
	msgbox OneIsland_PokemonCenter_1F_Text_CelioCaughtMoreMonMaybeICanBeUseful
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_YoullBeTradingFromTrainersFarAway
	applymovement LOCALID_CELIO, Common_Movement_FacePlayer
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_NeedsSpecialGemstone
	setvar VAR_MAP_SCENE_MT_EMBER_EXTERIOR, 1
	setvar VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 4
	release
	end

OneIsland_PokemonCenter_1F_EventScript_CelioPlayerMissingNationalDex::
	msgbox OneIsland_PokemonCenter_1F_Text_CelioImModifyingMyNetworkMachine
	release
	end

OneIsland_PokemonCenter_1F_Movement_CelioCheckMachine::
	walk_in_place_up
	delay_8
	walk_in_place_up
	step_end

OneIsland_PokemonCenter_1F_Movement_CelioPutGemInMachine::
	walk_in_place_faster_up
	walk_in_place_up
	delay_16
	walk_in_place_up
	walk_in_place_up
	step_end

OneIsland_PokemonCenter_1F_EventScript_LittleBoy::
	msgbox OneIsland_PokemonCenter_1F_Text_CameFromPalletDontKnowIt, MSGBOX_NPC
	end

OneIsland_PokemonCenter_1F_EventScript_Hiker::
	msgbox OneIsland_PokemonCenter_1F_Text_EnormousVolcanoOnIsland, MSGBOX_NPC
	end

OneIsland_PokemonCenter_1F_EventScript_BattleGirl::
	lock
	faceplayer
	goto_if_set FLAG_IS_CHAMPION, OneIsland_PokemonCenter_1F_EventScript_BattleGirlHoennLinked
	msgbox OneIsland_PokemonCenter_1F_Text_WishICouldTradeWithBoyfriend
	release
	end

OneIsland_PokemonCenter_1F_EventScript_BattleGirlHoennLinked::
	msgbox OneIsland_PokemonCenter_1F_Text_TradedWithFarAwayBoyfriend
	release
	end

OneIsland_PokemonCenter_1F_EventScript_NetworkMachine::
	lockall
	goto_if_set FLAG_IS_CHAMPION, OneIsland_PokemonCenter_1F_EventScript_NetworkMachineLinkedWithHoenn
	goto_if_set FLAG_SEVII_DETOUR_FINISHED, OneIsland_PokemonCenter_1F_EventScript_NetworkMachineLinkedWithKanto
	msgbox OneIsland_PokemonCenter_1F_Text_MachineUnderAdjustment
	releaseall
	end

OneIsland_PokemonCenter_1F_EventScript_NetworkMachineLinkedWithKanto::
	msgbox OneIsland_PokemonCenter_1F_Text_MachineLinkedWithKanto
	releaseall
	end

OneIsland_PokemonCenter_1F_EventScript_NetworkMachineLinkedWithHoenn::
	msgbox OneIsland_PokemonCenter_1F_Text_MachineLinkedWithKantoAndHoenn
	releaseall
	end

OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandTriggerTop::
	lockall
	setvar VAR_TEMP_1, 1
	goto OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandScene
	end

OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandTriggerMidTop::
	lockall
	setvar VAR_TEMP_1, 2
	goto OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandScene
	end

OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandTriggerMidBottom::
	lockall
	setvar VAR_TEMP_1, 3
	goto OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandScene
	end

OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandTriggerBottom::
	lockall
	setvar VAR_TEMP_1, 4
	goto OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandScene
	end

OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandScene::
	textcolor NPC_TEXT_COLOR_MALE
	playse SE_PIN
	applymovement LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_BillOhHeyPlayer
	closemessage
	call_if_eq VAR_TEMP_1, 1, OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillTop
	call_if_eq VAR_TEMP_1, 2, OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillMidTop
	call_if_eq VAR_TEMP_1, 3, OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillMidBottom
	call_if_eq VAR_TEMP_1, 4, OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillBottom
	delay 10
	msgbox OneIsland_PokemonCenter_1F_Text_BillWeGotItDone
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_CelioJobWentQuick
	applymovement LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_BillYouveLearnedALot
	msgbox OneIsland_PokemonCenter_1F_Text_CelioOhReallyEhehe
	closemessage
	applymovement LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 10
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 15
	msgbox OneIsland_PokemonCenter_1F_Text_BillWeShouldHeadBackToKanto
	closemessage
	applymovement LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 15
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox OneIsland_PokemonCenter_1F_Text_CelioPromiseIllShowYouAroundSometime
	closemessage
	delay 25
	applymovement LOCALID_PLAYER, OneIsland_PokemonCenter_1F_Movement_PlayerExit
	applymovement LOCALID_ONE_ISLAND_POKEMON_CENTER_BILL, OneIsland_PokemonCenter_1F_Movement_BillExit
	waitmovement 0
	playse SE_EXIT
	setflag FLAG_HIDE_ONE_ISLAND_POKECENTER_BILL
	setvar VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 3
	clearflag FLAG_HIDE_CINNABAR_BILL
	setvar VAR_MAP_SCENE_CINNABAR_ISLAND, 3
	setvar VAR_0x8004, SEAGALLOP_ONE_ISLAND
	setvar VAR_0x8006, SEAGALLOP_CINNABAR_ISLAND
	goto EventScript_SetSail
	end

OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillTop::
	applymovement LOCALID_PLAYER, OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillTop
	waitmovement 0
	return

OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillMidTop::
	applymovement LOCALID_PLAYER, OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillMidTop
	waitmovement 0
	return

OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillMidBottom::
	applymovement LOCALID_PLAYER, OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillMidBottom
	waitmovement 0
	return

OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillBottom::
	applymovement LOCALID_PLAYER, OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillBottom
	waitmovement 0
	return

OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillTop::
	walk_right
	walk_down
	walk_in_place_faster_right
	step_end

OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillMidTop::
	walk_right
	step_end

OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillMidBottom::
	walk_right
	walk_up
	walk_in_place_faster_right
	step_end

OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillBottom::
	walk_right
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

@ Unused
OneIsland_PokemonCenter_1F_Movement_DelayWalkInPlaceLeft::
	delay_16
	delay_16
	delay_4
	walk_in_place_faster_left
	step_end

@ Unused
OneIsland_PokemonCenter_1F_Movement_WalkInPlaceDown::
	walk_in_place_fast_down
	step_end

OneIsland_PokemonCenter_1F_Movement_PlayerExit::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

OneIsland_PokemonCenter_1F_Movement_BillExit::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

OneIsland_PokemonCenter_1F_Text_BillHeyThereCelio::
    .string "正辉：哟，这边这边！\n"
    .string "锦辉！$"

OneIsland_PokemonCenter_1F_Text_CelioCantBelieveYouCameOut::
    .string "锦辉：正辉！\n"
    .string "你还真的来这儿了。$"

OneIsland_PokemonCenter_1F_Text_BillHowsYourResearchComing::
    .string "正辉：嗯，当然了！\n"
    .string "你的研究进行的怎么样了？\p"
    .string "……噢，等一下。$"

OneIsland_PokemonCenter_1F_Text_ThisIsMyBuddyCelio::
    .string "{PLAYER}，这是我的好友锦辉。\n"
    .string "他是个专业的电脑狂！$"

OneIsland_PokemonCenter_1F_Text_PlayerIsRisingPokemonChamp::
    .string "锦辉，这是{PLAYER}，一个向着\n"
    .string "宝可梦联盟发起冲击的新星！$"

OneIsland_PokemonCenter_1F_Text_PlayerIsReigningPokemonChamp::
    .string "锦辉，这是{PLAYER}，\n"
    .string "本届的宝可梦冠军！$"

OneIsland_PokemonCenter_1F_Text_CelioThatsReallyImpressive::
    .string "锦辉：这真让人印象深刻。\p"
    .string "我不喜欢这样说，不过\n"
    .string "我对战斗没有兴趣。\p"
    .string "怎样都好，幸会幸会。$"

OneIsland_PokemonCenter_1F_Text_BillBringMeUpToSpeed::
    .string "正辉：所以，回到正题吧。\n"
    .string "你的机器运行得怎样了？$"

OneIsland_PokemonCenter_1F_Text_CelioPCsCantLinkWithYours::
    .string "锦辉：它们工作正常，不过\n"
    .string "我们这边比较偏僻。\p"
    .string "岛上的电脑跟你的电脑 \n"
    .string "连接不上。$"

OneIsland_PokemonCenter_1F_Text_BillLetMeHelpYou::
    .string "正辉：喔，这样？\n"
    .string "好吧，让我看看吧。\p"
    .string "……等下……\n"
    .string "我想我们能把它弄好。\l"
    .string "让我来帮忙，好吗？$"

OneIsland_PokemonCenter_1F_Text_CanYouDeliverThisMeteoritePlayer::
    .string "{PLAYER}，你可以在这里\n"
    .string "等我一会吗？\p"
    .string "……事实上我想请你\n"
    .string "帮我一个忙。\p"
    .string "这个岛旁边的另一个岛\n"
    .string "叫做二之岛。\p"
    .string "那里有个经营\n"
    .string "游戏厅的男人。\p"
    .string "他有很多珍贵的石头\n"
    .string "和宝石。\p"
    .string "作为共同的研究狂，\n"
    .string "我们一直保持着联系，哈哈。\p"
    .string "所以，能请你帮我\n"
    .string "把这陨石交给他吗？$"

OneIsland_PokemonCenter_1F_Text_AcceptedMeteoriteFromBill::
    .string "{PLAYER}从正辉手上\n"
    .string "接过陨石。$"

OneIsland_PokemonCenter_1F_Text_CelioPleaseTakeThis::
    .string "锦辉：{PLAYER}，如果你要去\n"
    .string "二之岛，带上这个吧。$"

OneIsland_PokemonCenter_1F_Text_PassLetsYouTravelBetweenIslands::
    .string "这是这边的群岛的\n"
    .string "渡轮准乘证。\p"
    .string "拿着它你就可以去\n"
    .string "一之岛、二之岛和三之岛了。\p"
    .string "噢，把这也拿着吧。$"

OneIsland_PokemonCenter_1F_Text_ReceivedExtraPageForTownMap::
    .string "{PLAYER}城镇地图得到了\n"
    .string "新的一页。$"

OneIsland_PokemonCenter_1F_Text_ReceivedTownMap::
    .string "{PLAYER}得到了\n"
    .string "一张城镇地图！$"

OneIsland_PokemonCenter_1F_Text_BillCatchYouLater::
    .string "正辉：我等会会追上你的！\n"
    .string "代我向他问好！$"

OneIsland_PokemonCenter_1F_Text_HmmHowAboutLikeThis::
    .string "嗯……\p"
    .string "我们不如试试这样做吧……$"

OneIsland_PokemonCenter_1F_Text_GotPCWorkingStrollAWhileMore::
    .string "噢，这边，{PLAYER}！\p"
    .string "看到了吗？\n"
    .string "我们把电脑弄好了！\p"
    .string "我有点东西 \n"
    .string "想给锦辉看看。\p"
    .string "你可以先到外面\n"
    .string "等等我吗？$"

OneIsland_PokemonCenter_1F_Text_SorryForBeingPoorHost::
    .string "很抱歉占用了\n"
    .string "正辉这么多时间。\p"
    .string "同时我也为没能尽\n"
    .string "地主之谊而道歉。$"

OneIsland_PokemonCenter_1F_Text_UsualPCServicesUnavailable::
    .string "电脑服务\n"
    .string "现在不能使用……$"

OneIsland_PokemonCenter_1F_Text_BillOhHeyPlayer::
    .string "正辉：噢，这边！\n"
    .string "{PLAYER}！$"

OneIsland_PokemonCenter_1F_Text_BillWeGotItDone::
    .string "正辉：这儿有什么使你陶醉的东西吗？\n"
    .string "还是已经感觉腻了吗？\p"
    .string "这边的事都处理好了。\n"
    .string "这些电脑都能正常运作了！$"

OneIsland_PokemonCenter_1F_Text_CelioJobWentQuick::
    .string "锦辉：这事处理得真快。\p"
    .string "正辉真是个了不起的家伙……$"

OneIsland_PokemonCenter_1F_Text_BillYouveLearnedALot::
    .string "正辉：不，不！这没剩下\n"
    .string "什么我可以做的事了。\p"
    .string "锦辉，这边交给你了。\n"
    .string "相信你也学到了不少吧。$"

OneIsland_PokemonCenter_1F_Text_CelioOhReallyEhehe::
    .string "锦辉：噢，真的？\n"
    .string "嘿嘿……$"

OneIsland_PokemonCenter_1F_Text_BillWeShouldHeadBackToKanto::
    .string "正辉：好了，就这么简单。\n"
    .string "我已经完成了我的工作了。\l"
    .string "我们回关都去吧。\p"
    .string "锦辉，下次再见了。$"

OneIsland_PokemonCenter_1F_Text_CelioPromiseIllShowYouAroundSometime::
    .string "锦辉：{PLAYER}，今天没能\n"
    .string "让你享受一下，真的很抱歉。\p"
    .string "我保证，下次你来的时候\n"
    .string "我会带你在这些岛上逛逛。$"

OneIsland_PokemonCenter_1F_Text_CelioImModifyingMyNetworkMachine::
    .string "锦辉：你好！\n"
    .string "你看来跟平时一样的忙。\p"
    .string "我？\p"
    .string "嗯，我最近在调整\n"
    .string "我的网络服务器。\p"
    .string "我弄好了之后，\n"
    .string "我希望你是第一个试用的，\l"
    .string "{PLAYER}。$"

OneIsland_PokemonCenter_1F_Text_CelioCaughtMoreMonMaybeICanBeUseful::
    .string "锦辉：{PLAYER}，\n"
    .string "你最近过的怎样？\p"
    .string "噢，这样？\n"
    .string "你最近抓到很多宝可梦。\p"
    .string "知道不？\n"
    .string "也许我能帮上你的忙。$"

OneIsland_PokemonCenter_1F_Text_YoullBeTradingFromTrainersFarAway::
    .string "我正在调整 \n"
    .string "我的网络服务器。\p"
    .string "我正在把它设定成\n"
    .string "可以远距离的传送。\p"
    .string "我完成后，你可以\n"
    .string "跟远方的训练家 \l"
    .string "交换宝可梦。$"

OneIsland_PokemonCenter_1F_Text_NeedsSpecialGemstone::
    .string "不过，现在有点小问题。\p"
    .string "要让这运行，它要\n"
    .string "装上一个特别的宝石。\p"
    .string "听说有一个在一之岛上，\n"
    .string "不过我一直找不到。\p"
    .string "天晓得它在哪儿。$"

OneIsland_PokemonCenter_1F_Text_TryingToFindGem::
    .string "我甚至在读书的时候 \n"
    .string "也一直试着找到它。\p"
    .string "结果，我不能兼顾好\n"
    .string "研究和读书的事……\p"
    .string "如果我找正辉的话，我相信\n"
    .string "研究一定会很顺利。\p"
    .string "不过，这次我想靠\n"
    .string "自己来完成。$"

OneIsland_PokemonCenter_1F_Text_OhThats::
    .string "噢！\n"
    .string "这……这是……$"

OneIsland_PokemonCenter_1F_Text_HandedRubyToCelio::
    .string "{PLAYER}把红宝石\n"
    .string "交给了锦辉。$"

OneIsland_PokemonCenter_1F_Text_MayIAskOneMoreFavor::
    .string "谢谢你！\n"
    .string "{PLAYER}，你真的是太棒了。\p"
    .string "…… …… ……\p"
    .string "嗯……我可以请你\n"
    .string "帮我另一个忙吗？$"

OneIsland_PokemonCenter_1F_Text_PleaseINeedYourHelp::
    .string "这……这不是什么奇怪的事，\n"
    .string "请你一定要帮我，拜托了。$"

OneIsland_PokemonCenter_1F_Text_AnotherGemstoneInSeviiIslands::
    .string "当我研究宝石时，\n"
    .string "我发现了很重要的事。\p"
    .string "世上还存在着\n"
    .string "跟红宝石凑成一对的宝石。\p"
    .string "我认为宝石\n"
    .string "会在七岛上。\p"
    .string "{PLAYER}，拜托了，请你\n"
    .string "帮我去找出它们吧。\p"
    .string "{PLAYER}，我可以看看你的\n"
    .string "渡轮票跟城镇地图吗$"

OneIsland_PokemonCenter_1F_Text_ReturnedTriPassForRainbowPass::
    .string "{PLAYER}归还了三岛通行证，\n"
    .string "并得到了彩虹通行证。$"

OneIsland_PokemonCenter_1F_Text_ObtainedExtraMapPage::
    .string "得到了城镇地图\n"
    .string "的补充页！$"

OneIsland_PokemonCenter_1F_Text_PassLetYouGetToAllIslands::
    .string "这是我的渡轮票。\p"
    .string "这能让你在\n"
    .string "七岛间穿梭。\p"
    .string "{PLAYER}，拜托了，我没了你\n"
    .string "我什么都做不到。$"

OneIsland_PokemonCenter_1F_Text_HandedSapphireToCelio::
    .string "{PLAYER}把蓝宝石\n"
    .string "交给锦辉。$"

OneIsland_PokemonCenter_1F_Text_ThankYouGiveMeTime::
    .string "锦辉：那么这就是能跟\n"
    .string "红宝石凑成一对的宝石……\p"
    .string "{PLAYER}，你为此付出了\n"
    .string "很多努力，对吧？\p"
    .string "你不用告诉我。我知道\n"
    .string "这一定不简单。\p"
    .string "非常的感谢你！\p"
    .string "现在是我回报你的时候了！\n"
    .string "请给我一点时间。$"

OneIsland_PokemonCenter_1F_Text_OkayThisIsGood::
    .string "行了，这就好了……$"

OneIsland_PokemonCenter_1F_Text_LinkedUpWithLanette::
    .string "我做到了！\n"
    .string "我跟真由美连接上了！$"

OneIsland_PokemonCenter_1F_Text_ManagedToLinkWithHoennThankYou::
    .string "{PLAYER}……\n"
    .string "{PLAYER}，我做到了！\p"
    .string "我成功跟丰缘\n"
    .string "的训练家联系上了！\p"
    .string "终于，这个服务器\n"
    .string "可以正常运作了！\p"
    .string "{PLAYER}，这都是因为有你！\p"
    .string "感谢你，我的梦想\n"
    .string "终于成真了……$"

OneIsland_PokemonCenter_1F_Text_WishYouBestOfLuck::
    .string "我……\n"
    .string "我才没有哭。\p"
    .string "我已经很满足了！\p"
    .string "{PLAYER}，你会继续\n"
    .string "寻找珍稀的宝可梦的，对吧？\p"
    .string "我祝你好运！$"

OneIsland_PokemonCenter_1F_Text_CelioHearingRumorsAboutYou::
    .string "锦辉：你好！\p"
    .string "{PLAYER}，最近我常常听到\n"
    .string "有关你的传闻。$"

OneIsland_PokemonCenter_1F_Text_BillsFirstMonWasAbra::
    .string "{PLAYER}，你最喜欢\n"
    .string "哪一种宝可梦？\p"
    .string "正辉是个怪兽狂，\n"
    .string "所以他每一种都喜欢。\p"
    .string "不过，听说他的第一只\n"
    .string "宝可梦是凯西。$"

OneIsland_PokemonCenter_1F_Text_BillsHometownInGoldenrod::
    .string "说起来，{PLAYER}，你是从\n"
    .string "真新镇来的，对吧？\p"
    .string "我听说那里是一个\n"
    .string "很宁静跟和平的地方。\p"
    .string "正辉是从满金市过来的，\n"
    .string "他的家人还在那边住着。\p"
    .string "听说那边是个\n"
    .string "很热闹，很有活力的城市。\p"
    .string "我很想去见识一下。$"

OneIsland_PokemonCenter_1F_Text_BillCantStomachMilk::
    .string "{PLAYER}，你有没有什么\n"
    .string "忍受不了的事？\p"
    .string "听说，正辉的胃\n"
    .string "对牛奶过敏。$"

OneIsland_PokemonCenter_1F_Text_CameFromPalletDontKnowIt::
    .string "哦哦，陌生人啊！\n"
    .string "你好！你从哪儿来的？\p"
    .string "……真新镇？\n"
    .string "我听都没听过！$"

OneIsland_PokemonCenter_1F_Text_EnormousVolcanoOnIsland::
    .string "在这岛上，有个\n"
    .string "巨大的火山。\p"
    .string "最近都没爆发，\n"
    .string "去试试爬山怎么样？$"

OneIsland_PokemonCenter_1F_Text_WishICouldTradeWithBoyfriend::
    .string "我希望可以跟我那\n"
    .string "住很远的男朋友交换宝可梦……$"

OneIsland_PokemonCenter_1F_Text_TradedWithFarAwayBoyfriend::
    .string "我跟我住很远的男朋友\n"
    .string "交换到宝可梦了！\p"
    .string "每个人都说我们\n"
    .string "要感谢你跟锦辉。\p"
    .string "所以，谢谢你！$"

OneIsland_PokemonCenter_1F_Text_MachineUnderAdjustment::
    .string "网络服务器\n"
    .string "信号强度：0\p"
    .string "……宝可梦储存系统\n"
    .string "正在维护中……$"

OneIsland_PokemonCenter_1F_Text_MachineLinkedWithKanto::
    .string "网络服务器\n"
    .string "信号强度：1\p"
    .string "跟关都地区\n"
    .string "连接上。$"

OneIsland_PokemonCenter_1F_Text_MachineLinkedWithKantoAndHoenn::
    .string "网络服务器\n"
    .string "信号强度：2\p"
    .string "跟关都和丰缘地区\n"
    .string "连接上。$"

OneIsland_PokemonCenter_1F_Text_ObtainedTriPass::
    .string "得到了三岛通行证！$"

