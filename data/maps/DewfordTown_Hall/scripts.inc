.set LOCALID_EXPERT_M, 4
.set LOCALID_TWIN, 5
.set LOCALID_SCHOOL_KID_M, 7
.set LOCALID_PSYCHIC_M, 8

DewfordTown_Hall_MapScripts::
	.byte 0

DewfordTown_Hall_EventScript_Girl::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special IsTrendyPhraseBoring
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_Hall_EventScript_GirlBoredOfTrend
	msgbox DewfordTown_Hall_Text_CantImagineLifeWithoutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_GirlBoredOfTrend::
	msgbox DewfordTown_Hall_Text_GettingBoredOfTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Woman::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_TeachingMonAboutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Man::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special BufferDeepLinkPhrase
	msgbox DewfordTown_Hall_Text_DeepLinkBetweenXAndY, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DewfordTown_Hall_EventScript_ConfirmTrendLink
	goto_if_eq VAR_RESULT, NO, DewfordTown_Hall_EventScript_RejectTrendLink
	end

DewfordTown_Hall_EventScript_ConfirmTrendLink::
	msgbox DewfordTown_Hall_Text_MyHunchWasRight, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_RejectTrendLink::
	msgbox DewfordTown_Hall_Text_NotEasyToKeepUp, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_ExpertM::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_TVShowAboutTrend, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_EXPERT_M, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_Twin::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TWIN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_LittleBoy::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_CollectTrendMerchandise, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Bookshelf::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_BooksAboutTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_Painting::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordTown_Hall_EventScript_ScreamTitle
	case 4, DewfordTown_Hall_EventScript_ScreamTitle
	case 1, DewfordTown_Hall_EventScript_SmileTitle
	case 5, DewfordTown_Hall_EventScript_ScreamTitle
	case 2, DewfordTown_Hall_EventScript_LastTitle
	case 6, DewfordTown_Hall_EventScript_LastTitle
	case 3, DewfordTown_Hall_EventScript_BirthTitle
	case 7, DewfordTown_Hall_EventScript_LastTitle
	end

DewfordTown_Hall_EventScript_ScreamTitle::
	msgbox DewfordTown_Hall_Text_TrendsScream, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_SmileTitle::
	msgbox DewfordTown_Hall_Text_TrendsSmile, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_LastTitle::
	msgbox DewfordTown_Hall_Text_LastTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_BirthTitle::
	msgbox DewfordTown_Hall_Text_BirthOfTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_SchoolKidM::
	lockall
	setvar VAR_0x8008, 0
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_PsychicM::
	lockall
	setvar VAR_0x8008, 1
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_DoTrendDebate::
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordTown_Hall_EventScript_TrendDebate1
	case 1, DewfordTown_Hall_EventScript_TrendDebate1
	case 2, DewfordTown_Hall_EventScript_TrendDebate2
	case 3, DewfordTown_Hall_EventScript_TrendDebate2
	case 4, DewfordTown_Hall_EventScript_TrendDebate3
	case 5, DewfordTown_Hall_EventScript_TrendDebate3
	case 6, DewfordTown_Hall_EventScript_TrendDebate4
	case 7, DewfordTown_Hall_EventScript_TrendDebate5
	end

DewfordTown_Hall_EventScript_TrendDebate1::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_SawTrendCoolestThing, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_AllegedTrendNotAuthentic, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate2::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_ComposedTrendThemeSong, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WorkOnYourSinging, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate3::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_OrganizeTrendParty, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_BrilliantIndeed, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate4::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_TrendHasBecomePartOfLife, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate5::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WellBeTrendDuo, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_DontMovePlayer1::
	return

DewfordTown_Hall_EventScript_DebateReact1::
	applymovement LOCALID_PSYCHIC_M, DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactWest
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_DontMovePlayer2
	end

DewfordTown_Hall_EventScript_PlayerReactWest::
	goto_if_eq VAR_FACING, DIR_EAST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

DewfordTown_Hall_EventScript_DontMovePlayer2::
	return

DewfordTown_Hall_EventScript_DebateReact2::
	applymovement LOCALID_SCHOOL_KID_M, DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactNorthSouth
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_PlayerReactEast
	end

DewfordTown_Hall_EventScript_PlayerReactNorthSouth::
	call_if_eq VAR_FACING, DIR_NORTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp
	call_if_eq VAR_FACING, DIR_SOUTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerReactEast::
	goto_if_eq VAR_FACING, DIR_WEST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft:
	walk_in_place_left
	step_end

DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight:
	walk_in_place_right
	step_end

DewfordTown_Hall_EventScript_SludgeBombMan::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	goto_if_set FLAG_RECEIVED_TM_SLUDGE_BOMB, DewfordTown_Hall_EventScript_ReceivedSludgeBomb
	msgbox DewfordTown_Hall_Text_GiveYouSludgeBomb, MSGBOX_DEFAULT
	giveitem ITEM_TM_SLUDGE_BOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_SLUDGE_BOMB
	release
	end

DewfordTown_Hall_EventScript_ReceivedSludgeBomb::
	msgbox DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_Text_CantImagineLifeWithoutTrend:
    .string "现在流行什么？哎，当然是\n“{STR_VAR_1}”！\p不敢相信生活中没有\n“{STR_VAR_1}”会怎么样！$"

DewfordTown_Hall_Text_GettingBoredOfTrend:
    .string "现在流行什么？哎，当然是\n“{STR_VAR_1}”！\p但我对它已经有些腻了，\p我该去找找下面会流行什么。$"

DewfordTown_Hall_Text_TeachingMonAboutTrend:
    .string "我想把“{STR_VAR_1}”\n这个词教给我的宝可梦，\l但好像不太顺利。\p我想这对它来说太困难了。$"

DewfordTown_Hall_Text_DeepLinkBetweenXAndY:
    .string "我正在研究现今十分流行的\n“{STR_VAR_1}”。\p“{STR_VAR_1}”和\n“{STR_VAR_2}”之间\l是不是有很深的联系呢？$"

DewfordTown_Hall_Text_MyHunchWasRight:
    .string "啊！\n我的直觉是对的！\p我抢在了潮流的\n前面，万岁！$"

DewfordTown_Hall_Text_NotEasyToKeepUp:
    .string "什么？！\n真的？！\p对我这样的老人来说，\n已经很难追上潮流了！$"

DewfordTown_Hall_Text_TVShowAboutTrend:
    .string "说到关于\n“{STR_VAR_1}”的事……\l不是有部关于它的电视剧吗？$"

DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea:
    .string "在海的另一侧……\p“{STR_VAR_1}”\n比这里更流行吗？$"

DewfordTown_Hall_Text_CollectTrendMerchandise:
    .string "我收集经过官方认证的\n“{STR_VAR_1}”\l商品。\p我有官方\n“{STR_VAR_1}”玩偶……\p“{STR_VAR_1}”牌\n服装的真品……\p还有官方认证的\n“{STR_VAR_1}”\l图画书。\p呵呵呵，全是我的！\n我什么也不会给你！$"

DewfordTown_Hall_Text_BooksAboutTrend:
    .string "确认好的\n“{STR_VAR_1}”&\l坏的“{STR_VAR_1}”……\p这两者\n“{STR_VAR_1}”和\l宝可梦之间的关系……\p有用的\n“{STR_VAR_1}”……\p整整齐齐地排列着关于\n“{STR_VAR_1}”的书。$"

DewfordTown_Hall_Text_TrendsScream:
    .string "标题是“{STR_VAR_1}的\n尖叫”。$"

DewfordTown_Hall_Text_TrendsSmile:
    .string "标题是“{STR_VAR_1}的\n微笑”。$"

DewfordTown_Hall_Text_LastTrend:
    .string "标题是“最后\n{STR_VAR_1}”。$"

DewfordTown_Hall_Text_BirthOfTrend:
    .string "标题是“{STR_VAR_1}\n的诞生”。$"

DewfordTown_Hall_Text_SawTrendCoolestThing:
    .string "我看过“{STR_VAR_1}”！\n厉害吧？\p它就像，呃，最酷的东西！\p非常棒！\n都是真的！$"

DewfordTown_Hall_Text_AllegedTrendNotAuthentic:
    .string "啊，不不不。\p你说你看到过的\n“{STR_VAR_1}”\l——那是不可能的。\p有凭有据的文章更……\n怎么说，\l更尖锐，更丰富！\p啊，没什么，太惊讶了！$"

DewfordTown_Hall_Text_ComposedTrendThemeSong:
    .string "嘿，听好，我为\n“{STR_VAR_1}”作了曲。\p“{STR_VAR_1}”\n现在真的非常流行。\p好了，听着！\n……\p哦！\n{STR_VAR_1}！\p美丽的\n{STR_VAR_1}！$"

DewfordTown_Hall_Text_WorkOnYourSinging:
    .string "……\p我说，小子，\n你沉迷进\l“{STR_VAR_1}”之前\l能不能先学会怎么唱歌？$"

DewfordTown_Hall_Text_OrganizeTrendParty:
    .string "无论如何，就像我\n之前说的，我们该在\l这个小岛上开个\l“{STR_VAR_1}”聚会。$"

DewfordTown_Hall_Text_BrilliantIndeed:
    .string "啊，真美妙的主意！\p我们可以邀请\n所有热爱\l“{STR_VAR_1}”的人。\l绝妙的主意，真的！\p今天就开始吧，我们生活的中心就是\n“{STR_VAR_1}”！$"

DewfordTown_Hall_Text_TrendHasBecomePartOfLife:
    .string "我想……\p你不认为\n“{STR_VAR_1}”已\l超越了潮流，成为\l我们日常生活的一部分了吗？$"

DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind:
    .string "什么？\n刚才你说的什么？\p但是，无论你醒着还是睡着，\n“{STR_VAR_1}”\l在你心中无疑都\l占有重大的地位。\p毫无疑问，你是\n“{STR_VAR_1}”\l博士！$"

DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible:
    .string "如果我们两人组合起来，任何\n“{STR_VAR_1}”的事\l都难不倒我们！$"

DewfordTown_Hall_Text_WellBeTrendDuo:
    .string "完全正确，好朋友！\p我们就是\n“{STR_VAR_1}”铛！\p这不是最适合的形象吗？\n哈哈哈哈！$"

DewfordTown_Hall_Text_GiveYouSludgeBomb:
    .string "对我来说，泥爆弹才是\n最最流行的。\p嗯？你说你不知道\n泥爆弹？\p真可惜。\n我给你一个吧。$"

DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo:
    .string "我喜欢泥爆弹。\p但会\n“{STR_VAR_1}”的\l宝可梦也很棒。$"

