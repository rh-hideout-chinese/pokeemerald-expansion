ViridianCity_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianCity_OnTransition
	.byte 0

ViridianCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_VIRIDIAN_CITY
	call_if_eq VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 0, ViridianCity_EventScript_SetOldManBlockingRoad
	call_if_eq VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 1, ViridianCity_EventScript_SetOldManStandingByRoad
	call_if_ge VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 2, ViridianCity_EventScript_SetOldManNormal
	call_if_eq VAR_MAP_SCENE_VIRIDIAN_CITY_GYM_DOOR, 0, ViridianCity_EventScript_TryUnlockGym
	end

ViridianCity_EventScript_SetOldManNormal::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_OLD_MAN_1
	return

ViridianCity_EventScript_SetOldManStandingByRoad::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_OLD_MAN_1
	setobjectxyperm LOCALID_TUTORIAL_MAN, 21, 8
	setobjectmovementtype LOCALID_TUTORIAL_MAN, MOVEMENT_TYPE_LOOK_AROUND
	return

ViridianCity_EventScript_SetOldManBlockingRoad::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_OLD_MAN_LYING_DOWN
	setobjectxyperm LOCALID_TUTORIAL_MAN, 21, 11
	setobjectmovementtype LOCALID_TUTORIAL_MAN, MOVEMENT_TYPE_FACE_DOWN
	return

ViridianCity_EventScript_TryUnlockGym::
	goto_if_unset FLAG_BADGE02_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE03_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE04_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE05_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE06_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE07_GET, Common_EventScript_NopReturn
	setvar VAR_MAP_SCENE_VIRIDIAN_CITY_GYM_DOOR, 1
	return

ViridianCity_EventScript_GymDoorLocked::
	lockall
	textcolor NPC_TEXT_COLOR_NEUTRAL
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	msgbox ViridianCity_Text_GymDoorsAreLocked
	closemessage
	applymovement LOCALID_PLAYER, ViridianCity_Movement_JumpDownLedge
	waitmovement 0
	releaseall
	end

ViridianCity_Movement_JumpDownLedge::
	jump_2_down
	step_end

ViridianCity_EventScript_CitySign::
	msgbox ViridianCity_Text_CitySign, MSGBOX_SIGN
	end

ViridianCity_EventScript_TrainerTips1::
	msgbox ViridianCity_Text_CatchMonsForEasierBattles, MSGBOX_SIGN
	end

ViridianCity_EventScript_TrainerTips2::
	msgbox ViridianCity_Text_MovesLimitedByPP, MSGBOX_SIGN
	end

ViridianCity_EventScript_GymSign::
	msgbox ViridianCity_Text_GymSign, MSGBOX_SIGN
	end

ViridianCity_EventScript_GymDoor::
	msgbox ViridianCity_Text_GymDoorsAreLocked, MSGBOX_SIGN
	end

ViridianCity_EventScript_Boy::
	msgbox ViridianCity_Text_CanCarryMonsAnywhere, MSGBOX_NPC
	end

@ Other old man, not the tutorial old man
ViridianCity_EventScript_OldMan::
	lock
	faceplayer
	goto_if_eq VAR_MAP_SCENE_VIRIDIAN_CITY_GYM_DOOR, 1, ViridianCity_EventScript_OldManGymLeaderReturned
	msgbox ViridianCity_Text_GymClosedWonderWhoLeaderIs
	closemessage
	applymovement LOCALID_VIRIDIAN_OLD_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

ViridianCity_EventScript_OldManGymLeaderReturned::
	msgbox ViridianCity_Text_ViridiansGymLeaderReturned
	release
	end

ViridianCity_EventScript_TutorialOldMan::
	lock
	faceplayer
	goto_if_set FLAG_BADGE01_GET, ViridianCity_EventScript_AskIfTeachyTVHelpful
	goto_if_ge VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 2, ViridianCity_EventScript_TutorialCompleted
	goto_if_eq VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 1, ViridianCity_EventScript_TutorialStart
	goto_if_eq VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 0, ViridianCity_EventScript_TutorialNotReady
	end

ViridianCity_EventScript_AskIfTeachyTVHelpful::
	msgbox ViridianCity_Text_HowsTeachyTVHelping, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ViridianCity_EventScript_TeachyTVNotHelpful
	msgbox ViridianCity_Text_MyGrandsonOnTheShow
	release
	end

ViridianCity_EventScript_TeachyTVNotHelpful::
	msgbox ViridianCity_Text_TooBusyForTeachyTV
	release
	end

ViridianCity_EventScript_TutorialCompleted::
	msgbox ViridianCity_Text_WeakenMonsFirstToCatch
	release
	end

ViridianCity_EventScript_TutorialStart::
	call ViridianCity_EventScript_DoTutorialBattle
	release
	end

@ Unused
ViridianCity_EventScript_WatchToLearnBasics::
	msgbox ViridianCity_Text_WatchThatToLearnBasics
	release
	end

@ Unused. Starts battle after the post battle text, which is odd.
ViridianCity_EventScript_TutorialUnused::
	msgbox ViridianCity_Text_ThatWasEducationalTakeThis
	special StartOldManTutorialBattle
	waitstate
	release
	end

ViridianCity_EventScript_TutorialNotReady::
	msgbox ViridianCity_Text_ThisIsPrivateProperty
	closemessage
	release
	end

ViridianCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox ViridianCity_Text_WantToKnowAboutCaterpillarMons, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, ViridianCity_EventScript_YoungsterExplainCaterpillars
	goto_if_eq VAR_RESULT, NO, ViridianCity_EventScript_YoungsterDeclineExplanation
	end

ViridianCity_EventScript_YoungsterExplainCaterpillars::
	msgbox ViridianCity_Text_ExplainCaterpieWeedle
	release
	end

ViridianCity_EventScript_YoungsterDeclineExplanation::
	msgbox ViridianCity_Text_OhOkayThen
	release
	end

ViridianCity_EventScript_Woman::
	lock
	faceplayer
	goto_if_eq VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 0, ViridianCity_EventScript_WomanRoadBlocked
	msgbox ViridianCity_Text_GoShoppingInPewterOccasionally
	release
	end

ViridianCity_EventScript_WomanRoadBlocked::
	msgbox ViridianCity_Text_GrandpaHasntHadCoffeeYet
	closemessage
	applymovement LOCALID_VIRIDIAN_WOMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

ViridianCity_EventScript_DreamEaterTutor::
	goto EventScript_DreamEaterTutor
	end

ViridianCity_EventScript_RoadBlocked::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	msgbox ViridianCity_Text_ThisIsPrivateProperty
	closemessage
	applymovement LOCALID_PLAYER, ViridianCity_Movement_WalkDown
	waitmovement 0
	releaseall
	end

ViridianCity_Movement_WalkDown::
	walk_down
	step_end

ViridianCity_EventScript_TutorialTriggerLeft::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_TUTORIAL_MAN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	call ViridianCity_EventScript_DoTutorialBattle
	release
	end

ViridianCity_EventScript_TutorialTriggerRight::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_TUTORIAL_MAN, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	call ViridianCity_EventScript_DoTutorialBattle
	release
	end

ViridianCity_EventScript_DoTutorialBattle::
	msgbox ViridianCity_Text_ShowYouHowToCatchMons
	closemessage
	special StartOldManTutorialBattle
	waitstate
	lock
	faceplayer
	msgbox ViridianCity_Text_ThatWasEducationalTakeThis
	setvar VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 2
	giveitem ITEM_TEACHY_TV
	msgbox ViridianCity_Text_WatchThatToLearnBasics
	return

ViridianCity_Text_CanCarryMonsAnywhere::
    .string "你腰上挂着的这些精灵球！\n"
    .string "你有宝可梦，是吧？\p"
    .string "太棒了！无论何时何地，\n"
    .string "你都能携带并使用宝可梦。$"

ViridianCity_Text_GymClosedWonderWhoLeaderIs::
    .string "这个宝可梦道馆总是关闭着。\p"
    .string "我很想到底知道谁是馆主？$"

ViridianCity_Text_ViridiansGymLeaderReturned::
    .string "常青道馆的馆主回来了！$"

ViridianCity_Text_WantToKnowAboutCaterpillarMons::
    .string "你想知道两种\n"
    .string "虫属性宝可梦的区别吗？$"

ViridianCity_Text_OhOkayThen::
    .string "噢，好吧！$"

ViridianCity_Text_ExplainCaterpieWeedle::
    .string "绿毛虫没有毒，\n"
    .string "但是独角虫有毒。\p"
    .string "当心你的宝可梦别被独角虫的\n"
    .string "毒针给刺中了。$"

ViridianCity_Text_GrandpaHasntHadCoffeeYet::
    .string "噢，爷爷！\n"
    .string "别这么任性啊！\p"
    .string "真的很抱歉。\n"
    .string "他还没喝咖啡。$"

ViridianCity_Text_GoShoppingInPewterOccasionally::
    .string "我有时候会去深灰市买东西。\p"
    .string "我每次去的时候，都必须\n"
    .string "在常青森林中走一段蜿蜒的小路。$"

ViridianCity_Text_ThisIsPrivateProperty::
    .string "我绝不允许你通过这里！\p"
    .string "这里是私人领地！$"

ViridianCity_Text_ShowYouHowToCatchMons::
    .string "刚刚我喝过咖啡了。\n"
    .string "喝咖啡可是我每天的必修课！\p"
    .string "嗯？\n"
    .string "你手上拿着的那个红色盒子是什么？\p"
    .string "噢，你在完成你的宝可梦图鉴啊。\p"
    .string "那么让我给你一些建议吧。\p"
    .string "宝可梦图鉴会在\n"
    .string "你收服到宝可梦时\l"
    .string "自动更新数据。\p"
    .string "……你不知道该怎么收服宝可梦？\p"
    .string "那我想我应该教你怎么做！$"

ViridianCity_Text_ThatWasEducationalTakeThis::
    .string "怎么样？\n"
    .string "是不是受益匪浅啊？\p"
    .string "把这个也带上吧。$"

ViridianCity_Text_WatchThatToLearnBasics::
    .string "如果有什么你不懂的，\n"
    .string "一定要仔细看它。\p"
    .string "它将教会你如何成为\n"
    .string "一名合格的宝可梦训练家。$"

ViridianCity_Text_WeakenMonsFirstToCatch::
    .string "我已经喝过咖啡了。\n"
    .string "喝咖啡可是我每天的必修课！\p"
    .string "但是我泡得太浓了。\n"
    .string "现在我头有点痛……\p"
    .string "顺便说一下，\n"
    .string "你完成了你的宝可梦图鉴吗？\p"
    .string "首先，要使宝可梦变弱，\n"
    .string "然后才能试图抓住它。$"

ViridianCity_Text_HowsTeachyTVHelping::
    .string "我刚刚喝过咖啡了。\n"
    .string "喝咖啡可是我每天的必修课！\p"
    .string "但是我泡得太浓了，\n"
    .string "喝得我头都痛了……\p"
    .string "顺便，我那台旧的教学电视机\n"
    .string "帮到你了吗？$"

ViridianCity_Text_MyGrandsonOnTheShow::
    .string "哇哈哈！\n"
    .string "电视上的是我孙子！\p"
    .string "既然是他在教的话\n"
    .string "你就得好好学。$"

ViridianCity_Text_TooBusyForTeachyTV::
    .string "嗯……你忙得甚至抽不出\n"
    .string "时间来看教学电视机了……\p"
    .string "时间就是金钱，这两者\n"
    .string "都不应当被虚耗……$"

ViridianCity_Text_CitySign::
    .string "常青市\n"
    .string "永远的绿色天堂$"

ViridianCity_Text_CatchMonsForEasierBattles::
    .string "训练家贴士\p"
    .string "收服宝可梦\n"
    .string "增加你的收集数。\p"
    .string "你拥有得越多，\n"
    .string "战斗就越轻松。$"

ViridianCity_Text_MovesLimitedByPP::
    .string "训练家贴士\p"
    .string "宝可梦的技能受到它们的\n"
    .string "技能点 也就是PP值的限制。\p"
    .string "想要回复PP的话将你疲惫的\n"
    .string "宝可梦放到宝可梦中心休息吧。$"

ViridianCity_Text_GymSign::
    .string "常青市宝可梦道馆$"

ViridianCity_Text_GymDoorsAreLocked::
    .string "常青道馆的门锁上了……$"

