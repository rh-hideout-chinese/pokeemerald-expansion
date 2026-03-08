FourIsland_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FourIsland_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, FourIsland_OnFrame
	.byte 0

FourIsland_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_FOUR_ISLAND
	call_if_eq VAR_MAP_SCENE_FOUR_ISLAND, 0, FourIsland_EventScript_ShowRival
	call FourIsland_EventScript_TrySetDayCareManPos
	end

FourIsland_EventScript_ShowRival::
	clearflag FLAG_HIDE_FOUR_ISLAND_RIVAL
	return

FourIsland_EventScript_TrySetDayCareManPos::
	goto_if_unset FLAG_PENDING_DAYCARE_EGG, FourIsland_EventScript_EndSetDayCareManPos
	setobjectxyperm LOCALID_FOUR_ISLAND_DAYCARE_MAN, 16, 14
FourIsland_EventScript_EndSetDayCareManPos::
	return

FourIsland_OnFrame::
	map_script_2 VAR_MAP_SCENE_FOUR_ISLAND, 0, FourIsland_EventScript_RivalScene
	.2byte 0

FourIsland_EventScript_RivalScene::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_FOUR_ISLAND_RIVAL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_RIVAL, 0
	applymovement LOCALID_FOUR_ISLAND_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FOUR_ISLAND_RIVAL, Common_Movement_Delay48
	waitmovement 0
	delay 25
	applymovement LOCALID_FOUR_ISLAND_RIVAL, FourIsland_Movement_RivalApproach
	waitmovement 0
	msgbox FourIsland_Text_RivalAlreadyGotEggBeSmellingYa
	closemessage
	applymovement LOCALID_PLAYER, FourIsland_Movement_PlayerWatchRivalExit
	applymovement LOCALID_FOUR_ISLAND_RIVAL, FourIsland_Movement_RivalExit
	waitmovement 0
	fadedefaultbgm
	playse SE_EXIT
	delay 35
	removeobject LOCALID_FOUR_ISLAND_RIVAL
	setvar VAR_MAP_SCENE_FOUR_ISLAND, 1
	releaseall
	end

FourIsland_Movement_RivalApproach::
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

FourIsland_Movement_RivalExit::
	delay_16
	delay_4
	walk_down
	step_end

FourIsland_Movement_PlayerWatchRivalExit::
	walk_left
	walk_in_place_faster_right
	step_end

FourIsland_EventScript_DaycareMan::
	lock
	faceplayer
	special GetDaycareMonNicknames
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, FourIsland_EventScript_DaycareEggWaiting
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, FourIsland_EventScript_CheckOnOneMon
	goto_if_eq VAR_RESULT, DAYCARE_TWO_MONS, FourIsland_EventScript_CheckOnTwoMons
	msgbox DayCare_Text_ImDaycareManSpeakToMyWife
	release
	end

FourIsland_EventScript_DaycareEggWaiting::
	msgbox DayCare_Text_DoYouWantEgg, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FourIsland_EventScript_DaycareAcceptEgg
	msgbox DayCare_Text_IWillKeepDoYouWantIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FourIsland_EventScript_DaycareAcceptEgg
	msgbox DayCare_Text_IllKeepIt
	clearflag FLAG_PENDING_DAYCARE_EGG
	special RejectEggFromDayCare
	release
	end

FourIsland_EventScript_DaycareAcceptEgg::
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_ne VAR_RESULT, PARTY_SIZE, FourIsland_EventScript_DaycareReceivedEgg
	msgbox DayCare_Text_YouHaveNoRoomForIt
	release
	end

FourIsland_EventScript_DaycareReceivedEgg::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	message DayCare_Text_ReceivedEgg
	call EventScript_RestorePrevTextColor
	playfanfare MUS_LEVEL_UP
	waitfanfare
	waitbuttonpress
	msgbox DayCare_Text_TakeGoodCareOfIt
	special GiveEggFromDaycare
	clearflag FLAG_PENDING_DAYCARE_EGG
	release
	end

FourIsland_EventScript_CheckOnOneMon::
	special GetDaycareMonNicknames
	msgbox DayCare_Text_YourMonIsDoingFine
	release
	end

FourIsland_EventScript_CheckOnTwoMons::
	special GetDaycareMonNicknames
	msgbox DayCare_Text_YourMonsAreDoingFine
	special SetDaycareCompatibilityString
	special ShowFieldMessageStringVar4
	waitmessage
	waitbuttonpress
	release
	end

FourIsland_EventScript_OldWoman::
	lock
	faceplayer
	goto_if_set FLAG_IS_CHAMPION, FourIsland_EventScript_OldWomanLoreleiLeft
	msgbox FourIsland_Text_LoreleiHasReturned
	release
	end

FourIsland_EventScript_OldWomanLoreleiLeft::
	famechecker FAMECHECKER_LORELEI, 5
	msgbox FourIsland_Text_LoreleiMetLaprasAsChild
	release
	end

FourIsland_EventScript_LittleGirl::
	lock
	faceplayer
	famechecker FAMECHECKER_LORELEI, 4
	msgbox FourIsland_Text_LoreleiHasLotsOfStuffedDolls
	release
	end

FourIsland_EventScript_FatMan::
	msgbox FourIsland_Text_MadeSlushieUsingIcefallCaveIce, MSGBOX_NPC
	end

FourIsland_EventScript_IslandSign::
	msgbox FourIsland_Text_IslandSign, MSGBOX_SIGN
	end

FourIsland_EventScript_LoreleisHouseSign::
	msgbox FourIsland_Text_LoreleisHouse, MSGBOX_SIGN
	end

FourIsland_Text_IslandSign::
    .string "四之岛\n"
    .string "温暖的蓝色浮冰之岛$"

FourIsland_Text_LoreleiHasReturned::
    .string "科拿回来了。\p"
    .string "莫非是因为\n"
    .string "都市生活的压力太大了吗？$"

FourIsland_Text_LoreleiMetLaprasAsChild::
    .string "科拿已经回来了。\p"
    .string "我猜她的拉普拉斯就是那只\n"
    .string "她在很小时候就遇到的宝可梦。\p"
    .string "我想她是在冻瀑洞窟\n"
    .string "收服到拉普拉斯的。\p"
    .string "可能从那时起那只宝可梦\n"
    .string "就一直陪伴着她。$"

FourIsland_Text_RivalAlreadyGotEggBeSmellingYa::
    .string "{RIVAL}：嗨！\n"
    .string "{PLAYER}！\p"
    .string "你到七岛上来干什么？\p"
    .string "你不该老学我，\n"
    .string "知道吗？\p"
    .string "反正我已经拿到宝可梦的蛋了，\n"
    .string "在这岛上已经没什么事可做了。\p"
    .string "嘿，我打赌你都不知道\n"
    .string "什么是宝可梦的蛋。\p"
    .string "那你就永远别想\n"
    .string "完成全国宝可梦图鉴了。\p"
    .string "对了，我在这岛上遇到了\n"
    .string "一个我们都认识的人。\p"
    .string "如果你好奇的话，\n"
    .string "可以到处找找哦！\p"
    .string "我呢，没时间浪费在这里了。\p"

FourIsland_Text_LoreleiHasLotsOfStuffedDolls::
    .string "先闪啦！$"

FourIsland_Text_MadeSlushieUsingIcefallCaveIce::
    .string "啊，你发现我了！\n"
    .string "请别告诉科拿。\p"
    .string "你知道科拿有许多许多\n"
    .string "的毛绒娃娃吗？\p"
    .string "每次她回四之岛，\n"
    .string "她的收藏都会增加！$"

FourIsland_Text_LoreleisHouse::
    .string "哇，好冰！\p"
    .string "我用冻瀑洞窟里采集到的冰\n"
    .string "又做了一杯冰沙。\p"
    .string "冰爽又美味哦！$"

