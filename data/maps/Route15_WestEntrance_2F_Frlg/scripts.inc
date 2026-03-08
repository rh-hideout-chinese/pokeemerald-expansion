.equ REQUIRED_CAUGHT_MONS, 50

Route15_WestEntrance_2F_Frlg_MapScripts::
	.byte 0

Route15_WestEntrance_2F_EventScript_LeftBinoculars::
	lockall
	msgbox Route15_WestEntrance_2F_Text_LargeShiningBird
	showmonpic SPECIES_ARTICUNO, 10, 3
	delay 20
	waitbuttonpress
	hidemonpic
	setvar VAR_0x8004, SPECIES_ARTICUNO
	special SetSeenMon
	releaseall
	end

Route15_WestEntrance_2F_EventScript_RightBinoculars::
	msgbox Route15_WestEntrance_2F_Text_SmallIslandOnHorizon, MSGBOX_SIGN
	end

Route15_WestEntrance_2F_EventScript_Aide::
	lock
	faceplayer
	call Route15_WestEntrance_2F_EventScript_GetAideRequestInfo
	goto_if_set FLAG_GOT_EXP_SHARE_FROM_OAKS_AIDE, Route15_WestEntrance_2F_EventScript_AlreadyGotExpShare
	msgbox Route15_WestEntrance_2F_Text_GiveItemIfCaughtEnough, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Aide_EventScript_DeclineCheckMons
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetFrlgPokedexCount
	buffernumberstring STR_VAR_3, VAR_0x8006
	call Route15_WestEntrance_2F_EventScript_GetAideRequestInfo
	goto_if_lt VAR_0x8006, REQUIRED_CAUGHT_MONS, Aide_EventScript_HaventCaughtEnough
	msgbox Route15_WestEntrance_2F_Text_GreatHereYouGo
	checkitemspace ITEM_EXP_SHARE
	goto_if_eq VAR_RESULT, FALSE, Aide_EventScript_NoRoomForItem
	giveitem_msg Route15_WestEntrance_2F_Text_ReceivedItemFromAide, ITEM_EXP_SHARE
	setflag FLAG_GOT_EXP_SHARE_FROM_OAKS_AIDE
	msgbox Route15_WestEntrance_2F_Text_ExplainExpShare
	release
	end

Route15_WestEntrance_2F_EventScript_AlreadyGotExpShare::
	msgbox Route15_WestEntrance_2F_Text_ExplainExpShare
	release
	end

Route15_WestEntrance_2F_EventScript_GetAideRequestInfo::
	buffernumberstring STR_VAR_1, REQUIRED_CAUGHT_MONS
	bufferitemname STR_VAR_2, ITEM_EXP_SHARE
	return

Route15_WestEntrance_2F_Text_GiveItemIfCaughtEnough::
    .string "嗨！还记得我吗？\n"
    .string "我是大木博士的助手之一。\p"
    .string "如果你的宝可梦图鉴已经收集了\n"
    .string "{STR_VAR_1}种数据，我就会给你\l"
    .string "一个奖励。\p"
    .string "大木博士委托我把\n"
    .string "{STR_VAR_2}给你。\p"
    .string "那么{PLAYER}，让我问问你。\p"
    .string "你已经收集到了至少\n"
    .string "{STR_VAR_1}种宝可梦了吗？$"

Route15_WestEntrance_2F_Text_GreatHereYouGo::
    .string "太棒了！你已经拥有了\n"
    .string "{STR_VAR_3}宝可梦！\p"
    .string "恭喜！\n"
    .string "奖励，拿去吧。$"

Route15_WestEntrance_2F_Text_ReceivedItemFromAide::
    .string "{PLAYER}从助手那儿\n"
    .string "得到了{STR_VAR_2}$"

Route15_WestEntrance_2F_Text_ExplainExpShare::
    .string "学习装置是一个可以\n"
    .string "被宝可梦携带的道具。\p"
    .string "这只宝可梦就算不战斗\n"
    .string "也可以分享\l"
    .string "一部分经验值$"

Route15_WestEntrance_2F_Text_LargeShiningBird::
    .string "一架望远镜……\n"
    .string "我来看看……\p"
    .string "哦！一只漂亮的大鸟\n"
    .string "正向着大海飞去。$"

Route15_WestEntrance_2F_Text_SmallIslandOnHorizon::
    .string "一架望远镜……\n"
    .string "我来看看……\p"
    .string "这……看上去地平线上\n"
    .string "有一座小岛！$"

