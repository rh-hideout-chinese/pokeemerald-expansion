.equ REQUIRED_CAUGHT_MONS, 40

Route16_NorthEntrance_2F_Frlg_MapScripts::
	.byte 0

Route16_NorthEntrance_2F_EventScript_LittleBoy::
	msgbox Route16_NorthEntrance_2F_Text_OnBikeRideWithGirlfriend, MSGBOX_NPC
	end

Route16_NorthEntrance_2F_EventScript_LittleGirl::
	msgbox Route16_NorthEntrance_2F_Text_RidingTogetherOnNewBikes, MSGBOX_NPC
	end

Route16_NorthEntrance_2F_EventScript_LeftBinoculars::
	msgbox Route16_NorthEntrance_2F_Text_ItsCeladonDeptStore, MSGBOX_SIGN
	end

Route16_NorthEntrance_2F_EventScript_RightBinoculars::
	msgbox Route16_NorthEntrance_2F_Text_LongPathOverWater, MSGBOX_SIGN
	end

Route16_NorthEntrance_2F_EventScript_Aide::
	lock
	faceplayer
	call Route16_NorthEntrance_2F_EventScript_GetAideRequestInfo
	goto_if_set FLAG_GOT_AMULET_COIN_FROM_OAKS_AIDE, Route16_NorthEntrance_2F_EventScript_AlreadyGotAmuletCoin
	msgbox Route16_NorthEntrance_2F_Text_GiveAmuletCoinIfCaught40, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Aide_EventScript_DeclineCheckMons
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetFrlgPokedexCount
	buffernumberstring STR_VAR_3, VAR_0x8006
	call Route16_NorthEntrance_2F_EventScript_GetAideRequestInfo
	goto_if_lt VAR_0x8006, REQUIRED_CAUGHT_MONS, Aide_EventScript_HaventCaughtEnough
	msgbox Route16_NorthEntrance_2F_Text_GreatHereYouGo
	checkitemspace ITEM_AMULET_COIN
	goto_if_eq VAR_RESULT, FALSE, Aide_EventScript_NoRoomForItem
	giveitem_msg Route16_NorthEntrance_2F_Text_ReceivedAmuletCoinFromAide, ITEM_AMULET_COIN
	setflag FLAG_GOT_AMULET_COIN_FROM_OAKS_AIDE
	msgbox Route16_NorthEntrance_2F_Text_ExplainAmuletCoin
	release
	end

Route16_NorthEntrance_2F_EventScript_AlreadyGotAmuletCoin::
	msgbox Route16_NorthEntrance_2F_Text_ExplainAmuletCoin
	release
	end

Route16_NorthEntrance_2F_EventScript_GetAideRequestInfo::
	buffernumberstring STR_VAR_1, REQUIRED_CAUGHT_MONS
	bufferitemname STR_VAR_2, ITEM_AMULET_COIN
	return

Route16_NorthEntrance_2F_Text_OnBikeRideWithGirlfriend::
    .string "我正在和我的女友\n"
    .string "一起飙车放松呢！$"

Route16_NorthEntrance_2F_Text_RidingTogetherOnNewBikes::
    .string "我们将会骑着我们的\n"
    .string "新自行车一起飞驶。$"

Route16_NorthEntrance_2F_Text_ItsCeladonDeptStore::
    .string "一架望远镜……\n"
    .string "我来看看……\p"
    .string "那是玉虹百货大楼！$"

Route16_NorthEntrance_2F_Text_LongPathOverWater::
    .string "一家望远镜……\n"
    .string "我来看看……\p"
    .string "在水上有一条\n"
    .string "通往远方的路。$"

Route16_NorthEntrance_2F_Text_GiveAmuletCoinIfCaught40::
    .string "嗨，还记得我吗？\n"
    .string "我是大木博士的助手之一。\p"
    .string "如果你的宝可梦图鉴已经收集了\n"
    .string "40种数据 我就会\l"
    .string "给你奖励。\p"
    .string "大木博士拜托我把\n"
    .string "护符金币给你。\p"
    .string "那么，{PLAYER}让我来问问你。\p"
    .string "你至少已经取得了\n"
    .string "40种宝可梦了吗？$"

Route16_NorthEntrance_2F_Text_GreatHereYouGo::
    .string "太棒了！你已经拥有了\n"
    .string "{STR_VAR_3}多种宝可梦了！\p"
    .string "恭喜！\n"
    .string "奖励，拿去吧！$"

Route16_NorthEntrance_2F_Text_ReceivedAmuletCoinFromAide::
    .string "{PLAYER}从助手那儿得到了\n"
    .string "护符金币。$"

Route16_NorthEntrance_2F_Text_ExplainAmuletCoin::
    .string "护符金币是一个\n"
    .string "由宝可梦携带的道具。\p"
    .string "如果这只宝可梦赢得了战斗，\n"
    .string "你将会得到更多钱！$"

