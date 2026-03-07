.equ RECEIVED_TOWN_MAP, VAR_TEMP_1

PalletTown_RivalsHouse_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PalletTown_RivalsHouse_OnTransition
	.byte 0

PalletTown_RivalsHouse_OnTransition::
	call_if_lt VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 2, PalletTown_RivalsHouse_EventScript_MoveDaisyToTable
	call_if_ge VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 2, PalletTown_RivalsHouse_EventScript_AlreadyReceivedTownMap
	end

PalletTown_RivalsHouse_EventScript_MoveDaisyToTable::
	setobjectmovementtype LOCALID_DAISY, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_DAISY, 5, 4
	return

PalletTown_RivalsHouse_EventScript_AlreadyReceivedTownMap::
	setvar RECEIVED_TOWN_MAP, TRUE
	return

PalletTown_RivalsHouse_EventScript_Daisy::
	lock
	faceplayer
	famechecker FAMECHECKER_DAISY, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	goto_if_set FLAG_SYS_GAME_CLEAR, PalletTown_RivalsHouse_EventScript_GroomMon
	goto_if_eq RECEIVED_TOWN_MAP, TRUE, PalletTown_RivalsHouse_EventScript_PleaseGiveMonsRest
	goto_if_eq VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 2, PalletTown_RivalsHouse_EventScript_ExplainTownMap
	goto_if_eq VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 1, PalletTown_RivalsHouse_EventScript_GiveTownMap
	goto_if_ge VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 1, PalletTown_RivalsHouse_EventScript_HeardBattledRival
	msgbox PalletTown_RivalsHouse_Text_HiBrothersAtLab
	closemessage
	applymovement LOCALID_DAISY, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

PalletTown_RivalsHouse_EventScript_HeardBattledRival::
	msgbox PalletTown_RivalsHouse_Text_HeardYouBattledRival
	release
	end

PalletTown_RivalsHouse_EventScript_GroomMon::
	goto_if_lt VAR_MASSAGE_COOLDOWN_STEP_COUNTER, 500, PalletTown_RivalsHouse_EventScript_RateMonFriendship
	msgbox PalletTown_RivalsHouse_Text_LikeMeToGroomMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PalletTown_RivalsHouse_EventScript_DeclineGrooming
	msgbox PalletTown_RivalsHouse_Text_GroomWhichOne
	special ChoosePartyMon
	waitstate
	lock
	faceplayer
	goto_if_ge VAR_0x8004, PARTY_SIZE, PalletTown_RivalsHouse_EventScript_DeclineGrooming
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, PalletTown_RivalsHouse_EventScript_CantGroomEgg
	msgbox PalletTown_RivalsHouse_Text_LookingNiceInNoTime
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special DaisyMassageServices
	fadescreen FADE_FROM_BLACK
	special BufferMonNickname
	msgbox PalletTown_RivalsHouse_Text_ThereYouGoAllDone
	release
	end

PalletTown_RivalsHouse_EventScript_CantGroomEgg::
	msgbox PalletTown_RivalsHouse_Text_CantGroomAnEgg
	release
	end

PalletTown_RivalsHouse_EventScript_DeclineGrooming::
	msgbox PalletTown_RivalsHouse_Text_DontNeedAnyGrooming
	release
	end

PalletTown_RivalsHouse_EventScript_RateMonFriendship::
	msgbox PalletTown_RivalsHouse_Text_MayISeeFirstMon
	specialvar VAR_RESULT, GetLeadMonFriendship
	switch VAR_RESULT
	case 0, PalletTown_RivalsHouse_EventScript_MonFriendshipLowest
	case 1, PalletTown_RivalsHouse_EventScript_MonFriendshipLower
	case 2, PalletTown_RivalsHouse_EventScript_MonFriendshipLow
	case 3, PalletTown_RivalsHouse_EventScript_MonFriendshipMid
	case 4, PalletTown_RivalsHouse_EventScript_MonFriendshipHigh
	case 5, PalletTown_RivalsHouse_EventScript_MonFriendshipHigher
	case 6, PalletTown_RivalsHouse_EventScript_MonFriendshipHighest
	end

PalletTown_RivalsHouse_EventScript_MonFriendshipLowest::
	msgbox PalletTown_RivalsHouse_Text_WhyWouldMonHateYouSoMuch
	release
	end

PalletTown_RivalsHouse_EventScript_MonFriendshipLower::
	msgbox PalletTown_RivalsHouse_Text_DontLikeWayItGlaresAtYou
	release
	end

PalletTown_RivalsHouse_EventScript_MonFriendshipLow::
	msgbox PalletTown_RivalsHouse_Text_NotFamiliarWithYouYet
	release
	end

PalletTown_RivalsHouse_EventScript_MonFriendshipMid::
	msgbox PalletTown_RivalsHouse_Text_ItsWarmingUpToYou
	release
	end

PalletTown_RivalsHouse_EventScript_MonFriendshipHigh::
	msgbox PalletTown_RivalsHouse_Text_ItsQuiteFriendly
	release
	end

PalletTown_RivalsHouse_EventScript_MonFriendshipHigher::
	msgbox PalletTown_RivalsHouse_Text_ItLooksVeryHappy
	release
	end

PalletTown_RivalsHouse_EventScript_MonFriendshipHighest::
	msgbox PalletTown_RivalsHouse_Text_CouldntLoveYouMore
	release
	end

PalletTown_RivalsHouse_EventScript_PleaseGiveMonsRest::
	msgbox PalletTown_RivalsHouse_Text_PleaseGiveMonsRest
	release
	end

PalletTown_RivalsHouse_EventScript_GiveTownMap::
	msgbox PalletTown_RivalsHouse_Text_ErrandForGrandpaThisWillHelp
	closemessage
	checkitemspace ITEM_TOWN_MAP
	goto_if_eq VAR_RESULT, FALSE, PalletTown_RivalsHouse_EventScript_NoRoomForTownMap
	applymovement LOCALID_DAISY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	removeobject LOCALID_TOWN_MAP
	setvar VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 2
	delay 15
	applymovement LOCALID_DAISY, Common_Movement_FacePlayer
	waitmovement 0
	delay 12
	giveitem_msg PalletTown_RivalsHouse_Text_ReceivedTownMapFromDaisy, ITEM_TOWN_MAP, 1, MUS_RG_OBTAIN_KEY_ITEM
	release
	end

PalletTown_RivalsHouse_EventScript_NoRoomForTownMap::
	msgbox PalletTown_RivalsHouse_Text_DontHaveSpaceForThis
	release
	end

PalletTown_RivalsHouse_EventScript_ExplainTownMap::
	msgbox PalletTown_RivalsHouse_Text_ExplainTownMap
	release
	end

PalletTown_RivalsHouse_EventScript_TownMap::
	msgbox PalletTown_RivalsHouse_Text_ItsBigMapOfKanto, MSGBOX_NPC
	end

PalletTown_RivalsHouse_EventScript_Bookshelf::
	msgbox PalletTown_RivalsHouse_Text_ShelvesCrammedFullOfBooks, MSGBOX_SIGN
	end

PalletTown_RivalsHouse_EventScript_Picture::
	msgbox PalletTown_RivalsHouse_Text_LovelyAndSweetClefairy, MSGBOX_SIGN
	end

PalletTown_RivalsHouse_Text_HiBrothersAtLab::
    .string "奈奈美：嗨，{PLAYER}！\p"
    .string "{RIVAL}是我的弟弟，\n"
    .string "他在爷爷的研究所里。$"

PalletTown_RivalsHouse_Text_HeardYouBattledRival::
    .string "奈奈美：{PLAYER}，我听说\n"
    .string "你和{RIVAL}进行了一场战斗。\p"
    .string "我真想看啊！$"

PalletTown_RivalsHouse_Text_ErrandForGrandpaThisWillHelp::
    .string "爷爷要你帮他跑趟腿？\p"
    .string "噢，他可真懒。\n"
    .string "给你，这个会帮到你的。$"

PalletTown_RivalsHouse_Text_ReceivedTownMapFromDaisy::
    .string "{PLAYER}从奈奈美那儿得到了城镇地图。$"

PalletTown_RivalsHouse_Text_DontHaveSpaceForThis::
    .string "你背包里没有空间装这个了。$"

PalletTown_RivalsHouse_Text_ExplainTownMap::
    .string "你可以用城镇地图确认你的方位，\n"
    .string "或者查看\l"
    .string "那些地区的名字。$"

PalletTown_RivalsHouse_Text_PleaseGiveMonsRest::
    .string "奈奈美：和人一样，宝可梦\n"
    .string "是活生生的生物。\p"
    .string "当他们疲倦的时候，\n"
    .string "请让它们休息一下。$"

PalletTown_RivalsHouse_Text_ItsBigMapOfKanto::
    .string "这是关都地区的一个大地图。\n"
    .string "它肯定会很有用的！$"

PalletTown_RivalsHouse_Text_ShelvesCrammedFullOfBooks::
    .string "书架子上摆满了\n"
    .string "关于宝可梦的读物。$"

PalletTown_RivalsHouse_Text_LikeMeToGroomMon::
    .string "奈奈美：嗨，{PLAYER}！\n"
    .string "来得正好。\p"
    .string "我正打算喝点茶。\n"
    .string "要不要来点儿？\p"
    .string "噢，你看看。\n"
    .string "你的宝可梦有一点脏了。\p"
    .string "你想让我帮它们梳理一下毛发吗？$"

PalletTown_RivalsHouse_Text_DontNeedAnyGrooming::
    .string "你不需要我帮忙梳理它们？\n"
    .string "好吧，我们喝茶吧。$"

PalletTown_RivalsHouse_Text_GroomWhichOne::
    .string "需要我梳理哪一只的毛发？$"

PalletTown_RivalsHouse_Text_LookingNiceInNoTime::
    .string "奈奈美：好的，\n"
    .string "我马上让它变得漂亮。$"

PalletTown_RivalsHouse_Text_ThereYouGoAllDone::
#ifdef BUGFIX @ The localizers missed what should be a textcolor change in the localizations.
	.string "{COLOR DARK_GRAY}{STR_VAR_1} looks dreamily content…\p"
	.string "{COLOR RED}DAISY: There you go! All done.\n"
#else @ In the JP games, gender-based text used a different font instead of different colors.
	.string "{FONT_NORMAL}{STR_VAR_1} looks dreamily content…\p"
	.string "{FONT_FEMALE}DAISY: There you go! All done.\n"
#endif
	.string "See? Doesn't it look nice?\p"
	.string "Giggle…\n"
	.string "It's such a cute POKéMON.$"

PalletTown_RivalsHouse_Text_CantGroomAnEgg::
    .string "噢，对不起。我真的\n"
    .string "不能梳理一个蛋。$"

PalletTown_RivalsHouse_Text_MayISeeFirstMon::
    .string "奈奈美：如果你用爱培育你的的宝可梦，\n"
    .string "它们会和你很亲近。\p"
    .string "比如说，{PLAYER}，\n"
    .string "我能看看你的第一只宝可梦吗？$"

PalletTown_RivalsHouse_Text_CouldntLoveYouMore::
    .string "它非常非常喜欢你。\p"
    .string "你的宝可梦高兴得无法形容了。$"

PalletTown_RivalsHouse_Text_ItLooksVeryHappy::
    .string "它看起来很高兴。\p"
    .string "我希望{RIVAL}也能看见这一幕，\n"
    .string "然后从中学到些什么。$"

PalletTown_RivalsHouse_Text_ItsQuiteFriendly::
    .string "它对你很友好。\n"
    .string "继续好好地照顾它！$"

PalletTown_RivalsHouse_Text_ItsWarmingUpToYou::
    .string "它正在跟你建立感情。\n"
    .string "你们之间必须建立信任。$"

PalletTown_RivalsHouse_Text_NotFamiliarWithYouYet::
    .string "它和你不是很亲密。\p"
    .string "当你第一次得到宝可梦时，\n"
    .string "它们通常都很警惕。$"

PalletTown_RivalsHouse_Text_DontLikeWayItGlaresAtYou::
    .string "{PLAYER}，我不喜欢它看你时\n"
    .string "愤怒的目光。\p"
    .string "你能对它稍微好一点吗？$"

PalletTown_RivalsHouse_Text_WhyWouldMonHateYouSoMuch::
    .string "……唔，我不好说什么，\n"
    .string "但是……\p"
    .string "宝可梦如此的憎恨你，\n"
    .string "是不是有什么原因？$"

PalletTown_RivalsHouse_Text_LovelyAndSweetClefairy::
    .string "“可爱又甜蜜的皮皮”$"

