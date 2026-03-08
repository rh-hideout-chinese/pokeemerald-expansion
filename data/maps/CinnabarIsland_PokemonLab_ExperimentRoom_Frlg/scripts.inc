.equ HELIX_FOSSIL, 1
.equ DOME_FOSSIL,  2
.equ OLD_AMBER,    3

CinnabarIsland_PokemonLab_ExperimentRoom_Frlg_MapScripts::
	.byte 0

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_Garett::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_SEEL
	call EventScript_GetInGameTradeSpeciesInfo
	goto_if_set FLAG_DID_SEELOR_TRADE, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_AlreadyTraded
	msgbox Trade_Text_LookingForMonWannaTradeForMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DeclineTrade
	call EventScript_ChooseMonForInGameTrade
	goto_if_ge VAR_0x8004, PARTY_SIZE, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DeclineTrade
	call EventScript_GetInGameTradeSpecies
	goto_if_ne VAR_RESULT, VAR_0x8009, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_NotRequestedMon
	call EventScript_DoInGameTrade
	msgbox Trade_Text_HeyThanks
	setflag FLAG_DID_SEELOR_TRADE
	release
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DeclineTrade::
	msgbox Trade_Text_AwwOhWell
	release
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox Trade_Text_WhatThatsNoMon
	release
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_AlreadyTraded::
	msgbox Trade_Text_IsntMyOldMonGreat
	release
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_FossilScientist::
	lock
	faceplayer
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_REVIVED_AMBER, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_CheckRevivedMtMoonFossil
	goto_if_eq VAR_RESULT, TRUE, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_RevivedAllFossils
	goto_if_eq VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_REVIVE_STATE, 2, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveRevivedMon
	goto_if_eq VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_REVIVE_STATE, 1, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_FossilStillReviving
	call CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_CheckAddHelixFossilToList
	goto_if_eq VAR_RESULT, TRUE, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ChooseFossilHelix
	call CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_CheckAddDomeFossilToList
	goto_if_eq VAR_RESULT, TRUE, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ChooseFossilDome
	call CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_CheckAddOldAmberToList
	goto_if_eq VAR_RESULT, TRUE, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ChooseFossilAmber
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_HaveYouAFossilForMe
	goto CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DontShowFossil
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_CheckAddHelixFossilToList::
	goto_if_unset FLAG_GOT_HELIX_FOSSIL, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_SetResultFalse
	goto_if_set FLAG_REVIVED_HELIX, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_SetResultFalse
	setvar VAR_RESULT, TRUE
	return

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_CheckAddDomeFossilToList::
	goto_if_unset FLAG_GOT_DOME_FOSSIL, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_SetResultFalse
	goto_if_set FLAG_REVIVED_DOME, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_SetResultFalse
	setvar VAR_RESULT, TRUE
	return

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_CheckAddOldAmberToList::
	goto_if_unset FLAG_GOT_OLD_AMBER, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_SetResultFalse
	goto_if_set FLAG_REVIVED_AMBER, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_SetResultFalse
	setvar VAR_RESULT, TRUE
	return

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_SetResultFalse::
	setvar VAR_RESULT, FALSE
	return

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DontShowFossil::
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_NoIsTooBad
	release
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ChooseFossilHelix::
	message CinnabarIsland_PokemonLab_ExperimentRoom_Text_HaveYouAFossilForMe
	waitmessage
	call CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_CheckAddOldAmberToList
	goto_if_eq VAR_RESULT, TRUE, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ChooseFossilHelixAmber
	multichoice 0, 0, MULTI_HELIX, FALSE
	switch VAR_RESULT
	case 0, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ShowHelixFossil
	case 1, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DontShowFossil
	case 127, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DontShowFossil
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ChooseFossilDome::
	message CinnabarIsland_PokemonLab_ExperimentRoom_Text_HaveYouAFossilForMe
	waitmessage
	call CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_CheckAddOldAmberToList
	goto_if_eq VAR_RESULT, TRUE, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ChooseFossilDomeAmber
	multichoice 0, 0, MULTI_DOME, FALSE
	switch VAR_RESULT
	case 0, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ShowDomeFossil
	case 1, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DontShowFossil
	case 127, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DontShowFossil
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ChooseFossilAmber::
	message CinnabarIsland_PokemonLab_ExperimentRoom_Text_HaveYouAFossilForMe
	waitmessage
	multichoice 0, 0, MULTI_AMBER, FALSE
	switch VAR_RESULT
	case 0, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ShowOldAmber
	case 1, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DontShowFossil
	case 127, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DontShowFossil
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ChooseFossilHelixAmber::
	multichoice 0, 0, MULTI_HELIX_AMBER, FALSE
	switch VAR_RESULT
	case 0, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ShowHelixFossil
	case 1, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ShowOldAmber
	case 2, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DontShowFossil
	case 127, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DontShowFossil
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ChooseFossilDomeAmber::
	multichoice 0, 0, MULTI_DOME_AMBER, FALSE
	switch VAR_RESULT
	case 0, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ShowDomeFossil
	case 1, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ShowOldAmber
	case 2, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DontShowFossil
	case 127, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DontShowFossil
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ShowHelixFossil::
	bufferspeciesname STR_VAR_1, SPECIES_OMANYTE
	bufferitemname STR_VAR_2, ITEM_HELIX_FOSSIL
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_ThatFossilIsOfMonMakeItLiveAgain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DeclineReviveFossil
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_HandedFossilToWeirdDoctor
	textcolor NPC_TEXT_COLOR_MALE
	removeitem ITEM_HELIX_FOSSIL
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_TakesTimeGoForWalk
	setvar VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_REVIVE_STATE, 1
	setvar VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_WHICH_FOSSIL, HELIX_FOSSIL
	release
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ShowDomeFossil::
	bufferspeciesname STR_VAR_1, SPECIES_KABUTO
	bufferitemname STR_VAR_2, ITEM_DOME_FOSSIL
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_ThatFossilIsOfMonMakeItLiveAgain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DeclineReviveFossil
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_HandedFossilToWeirdDoctor
	textcolor NPC_TEXT_COLOR_MALE
	removeitem ITEM_DOME_FOSSIL
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_TakesTimeGoForWalk
	setvar VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_REVIVE_STATE, 1
	setvar VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_WHICH_FOSSIL, DOME_FOSSIL
	release
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ShowOldAmber::
	bufferspeciesname STR_VAR_1, SPECIES_AERODACTYL
	bufferitemname STR_VAR_2, ITEM_OLD_AMBER
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_ThatFossilIsOfMonMakeItLiveAgain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DeclineReviveFossil
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_HandedFossilToWeirdDoctor
	textcolor NPC_TEXT_COLOR_MALE
	removeitem ITEM_OLD_AMBER
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_TakesTimeGoForWalk
	setvar VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_REVIVE_STATE, 1
	setvar VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_WHICH_FOSSIL, OLD_AMBER
	release
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_DeclineReviveFossil::
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_YouComeAgain
	release
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_FossilStillReviving::
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_TakesTimeGoForWalk
	release
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveRevivedMon::
	goto_if_eq VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_WHICH_FOSSIL, HELIX_FOSSIL, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveOmanyte
	goto_if_eq VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_WHICH_FOSSIL, DOME_FOSSIL, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveKabuto
	goto_if_eq VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_WHICH_FOSSIL, OLD_AMBER, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveAerodactyl
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveOmanyte::
	setvar VAR_TEMP_1, SPECIES_OMANYTE
	bufferspeciesname STR_VAR_1, SPECIES_OMANYTE
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_FossilMonBackToLife
	givemon SPECIES_OMANYTE, 5
	goto_if_eq VAR_RESULT, 2, Common_EventScript_NoMoreRoomForPokemon
	setflag FLAG_REVIVED_HELIX
	goto_if_eq VAR_RESULT, 0, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_NicknameMonParty
	goto_if_eq VAR_RESULT, 1, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_NicknameMonPC
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveKabuto::
	setvar VAR_TEMP_1, SPECIES_KABUTO
	bufferspeciesname STR_VAR_1, SPECIES_KABUTO
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_FossilMonBackToLife
	givemon SPECIES_KABUTO, 5
	goto_if_eq VAR_RESULT, 2, Common_EventScript_NoMoreRoomForPokemon
	setflag FLAG_REVIVED_DOME
	goto_if_eq VAR_RESULT, 0, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_NicknameMonParty
	goto_if_eq VAR_RESULT, 1, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_NicknameMonPC
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveAerodactyl::
	setvar VAR_TEMP_1, SPECIES_AERODACTYL
	bufferspeciesname STR_VAR_1, SPECIES_AERODACTYL
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_FossilMonBackToLife
	givemon SPECIES_AERODACTYL, 5
	goto_if_eq VAR_RESULT, 2, Common_EventScript_NoMoreRoomForPokemon
	setflag FLAG_REVIVED_AMBER
	goto_if_eq VAR_RESULT, 0, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_NicknameMonParty
	goto_if_eq VAR_RESULT, 1, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_NicknameMonPC
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_NicknameMonParty::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	playfanfare MUS_LEVEL_UP
	message CinnabarIsland_PokemonLab_ExperimentRoom_Text_ReceivedMonFromDoctor
	waitmessage
	waitfanfare
	setvar VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_REVIVE_STATE, 0
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_EndGiveMon
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_EndGiveMon
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_NicknameMonPC::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	playfanfare MUS_LEVEL_UP
	message CinnabarIsland_PokemonLab_ExperimentRoom_Text_ReceivedMonFromDoctor
	waitmessage
	waitfanfare
	setvar VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_REVIVE_STATE, 0
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_MonSentToPC
	call Common_EventScript_NameReceivedBoxMon
	goto CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_MonSentToPC
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_MonSentToPC::
	call Common_EventScript_TransferredToPC
	goto CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_EndGiveMon
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_EndGiveMon::
	release
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_RevivedAllFossils::
	msgbox CinnabarIsland_PokemonLab_ExperimentRoom_Text_YouComeAgain
	release
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_CheckRevivedMtMoonFossil::
	goto_if_set FLAG_GOT_HELIX_FOSSIL, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_CheckRevivedHelix
	goto_if_set FLAG_GOT_DOME_FOSSIL, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_CheckRevivedDome
	goto CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_SetResultFalse
	end

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_CheckRevivedHelix::
	goto_if_unset FLAG_REVIVED_HELIX, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_SetResultFalse
	setvar VAR_RESULT, TRUE
	return

CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_CheckRevivedDome::
	goto_if_unset FLAG_REVIVED_DOME, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_SetResultFalse
	setvar VAR_RESULT, TRUE
	return

Text_MetronomeTeach::
    .string "喔嚯嚯嚯！\n"
    .string "我想要教你一个有趣的技能！\p"
    .string "把它教给宝可梦，\n"
    .string "然后开心地看着它用出来的那一刻！\p"
    .string "这个技能的大名叫做挥指。\n"
    .string "你心动了吗？$"

Text_MetronomeDeclined::
    .string "我告诉你，真的很有趣！$"

Text_MetronomeWhichMon::
    .string "很好！\n"
    .string "哪只宝可梦想要学会这个技能？$"

Text_MetronomeTaught::
    .string "喔嚯嚯嚯！\n"
    .string "我来告诉你挥指的原理吧！\p"
    .string "它能刺激宝可梦的大脑\n"
    .string "来用出它并不会的技能！$"

CinnabarIsland_PokemonLab_ExperimentRoom_Text_HaveYouAFossilForMe::
    .string "嘿！\p"
    .string "我是一个十二分重要的研究员。\n"
    .string "没错，十二分的重要。\p"
    .string "看，我在研究宝可梦的化石。\n"
    .string "每时每刻，我都在进行研究。\p"
    .string "你！\n"
    .string "有化石带给我吗？$"

CinnabarIsland_PokemonLab_ExperimentRoom_Text_NoIsTooBad::
    .string "噢！\n"
    .string "太不好了！$"

@ Unused
CinnabarIsland_PokemonLab_ExperimentRoom_Text_TakesTimeGoForWalkJP::
	.string "ちょっと　じかん　かかるよ！\p"
	.string "そこらへんを　すこし\n"
	.string "ブラブラ　してくると　よろしー！$"

CinnabarIsland_PokemonLab_ExperimentRoom_Text_FossilMonBackToLife::
    .string "你来晚了。\n"
    .string "你跑哪儿去了？\p"
    .string "你的化石复活了！\n"
    .string "正如我所预料的那样，是一只{STR_VAR_1}！$"

CinnabarIsland_PokemonLab_ExperimentRoom_Text_ReceivedMonFromDoctor::
    .string "{PLAYER}从研究员的手中\n"
    .string "得到了{STR_VAR_1}。$"

@ Unused
CinnabarIsland_PokemonLab_ExperimentRoom_Text_NoRoomForPokemon::
	.string "ポケモン　いっぱいで　もてないね！$"

CinnabarIsland_PokemonLab_ExperimentRoom_Text_ThatFossilIsOfMonMakeItLiveAgain::
    .string "喔！\n"
    .string "那正是{STR_VAR_2}，我没看错！\p"
    .string "那是{STR_VAR_1}的化石，\n"
    .string "一种被认为灭绝了的宝可梦！\p"
    .string "我研制的复活机器\n"
    .string "能让那只宝可梦回到这个世界！$"

@ TODO: Resolve text dump error below?
CinnabarIsland_PokemonLab_ExperimentRoom_Text_HandedFossilToWeirdDoctor::
    .string "所以呢！\n"
    .string "你得快点把它交给我！\p"
    .string "{FONT_NORMAL}{PLAYER}把\n"
    .string "{STR_VAR_2}交给了这个奇怪的研究员$"

CinnabarIsland_PokemonLab_ExperimentRoom_Text_TakesTimeGoForWalk::
    .string "我只需要一点点时间！\n"
    .string "现在你可以出去走走！$"

CinnabarIsland_PokemonLab_ExperimentRoom_Text_YouComeAgain::
    .string "哎哎！\n"
    .string "你又来了！$"

