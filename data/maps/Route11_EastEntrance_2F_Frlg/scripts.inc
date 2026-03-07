.equ REQUIRED_CAUGHT_MONS, 30

Route11_EastEntrance_2F_Frlg_MapScripts::
	.byte 0

Route11_EastEntrance_2F_EventScript_LeftBinoculars::
	lockall
	goto_if_set FLAG_WOKE_UP_ROUTE_12_SNORLAX, Route11_EastEntrance_2F_EventScript_LeftBinocularsSnorlaxGone
	msgbox Route11_EastEntrance_2F_Text_BigMonAsleepOnRoad
	releaseall
	end

Route11_EastEntrance_2F_EventScript_LeftBinocularsSnorlaxGone::
	msgbox Route11_EastEntrance_2F_Text_WhatABreathtakingView
	releaseall
	end

Route11_EastEntrance_2F_EventScript_RightBinoculars::
	msgbox Route11_EastEntrance_2F_Text_RockTunnelGoodRouteToLavender, MSGBOX_SIGN
	end

Route11_EastEntrance_2F_EventScript_Turner::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_NIDORINOA
	call EventScript_GetInGameTradeSpeciesInfo
	goto_if_set FLAG_DID_NINA_TRADE, Route11_EastEntrance_2F_EventScript_AlreadyTraded
	msgbox Trade_Text_LookingForMonWannaTradeForMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route11_EastEntrance_2F_EventScript_DeclineTrade
	call EventScript_ChooseMonForInGameTrade
	goto_if_ge VAR_0x8004, PARTY_SIZE, Route11_EastEntrance_2F_EventScript_DeclineTrade
	call EventScript_GetInGameTradeSpecies
	goto_if_ne VAR_RESULT, VAR_0x8009, Route11_EastEntrance_2F_EventScript_NotRequestedMon
	call EventScript_DoInGameTrade
	msgbox Trade_Text_HeyThanks
	setflag FLAG_DID_NINA_TRADE
	release
	end

Route11_EastEntrance_2F_EventScript_DeclineTrade::
	msgbox Trade_Text_AwwOhWell
	release
	end

Route11_EastEntrance_2F_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox Trade_Text_WhatThatsNoMon
	release
	end

Route11_EastEntrance_2F_EventScript_AlreadyTraded::
	msgbox Trade_Text_IsntMyOldMonGreat
	release
	end

Route11_EastEntrance_2F_EventScript_Aide::
	lock
	faceplayer
	call Route11_EastEntrance_2F_EventScript_GetAideRequestInfo
	goto_if_set FLAG_GOT_ITEMFINDER, Route11_EastEntrance_2F_EventScript_AlreadyGotItemfinder
	msgbox Route11_EastEntrance_2F_Text_GiveItemfinderIfCaught30, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Aide_EventScript_DeclineCheckMons
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetFrlgPokedexCount
	buffernumberstring STR_VAR_3, VAR_0x8006
	call Route11_EastEntrance_2F_EventScript_GetAideRequestInfo
	goto_if_lt VAR_0x8006, REQUIRED_CAUGHT_MONS, Aide_EventScript_HaventCaughtEnough
	msgbox Route11_EastEntrance_2F_Text_GreatHereYouGo
	checkitemspace ITEM_ITEMFINDER
	goto_if_eq VAR_RESULT, FALSE, Aide_EventScript_NoRoomForItem
	giveitem_msg Route11_EastEntrance_2F_Text_ReceivedItemfinderFromAide, ITEM_ITEMFINDER
	setflag FLAG_GOT_ITEMFINDER
	msgbox Route11_EastEntrance_2F_Text_ExplainItemfinder
	release
	end

Route11_EastEntrance_2F_EventScript_AlreadyGotItemfinder::
	msgbox Route11_EastEntrance_2F_Text_ExplainItemfinder
	release
	end

Route11_EastEntrance_2F_EventScript_GetAideRequestInfo::
	buffernumberstring STR_VAR_1, REQUIRED_CAUGHT_MONS
	bufferitemname STR_VAR_2, ITEM_ITEMFINDER
	return

Route11_EastEntrance_2F_Text_GiveItemfinderIfCaught30::
    .string "嗨！还记得我吗？\n"
    .string "我是大木博士的助手之一。\p"
    .string "如果你的宝可梦图鉴已经收集了\n"
    .string "{STR_VAR_1}个宝可梦的数据， 我就会\l"
    .string "给你一个奖励。\p"
    .string "大木博士委托我把\n"
    .string "{STR_VAR_2}给你。\p"
    .string "那么{PLAYER}让我问问你。\p"
    .string "你已经得到了至少\n"
    .string "{STR_VAR_1}种宝可梦了吗？$"

Route11_EastEntrance_2F_Text_GreatHereYouGo::
    .string "太棒了！你已经收集了\n"
    .string "{STR_VAR_3}种宝可梦了！\p"
    .string "恭喜！\n"
    .string "这是奖励，拿去吧！$"

Route11_EastEntrance_2F_Text_ReceivedItemfinderFromAide::
    .string "{PLAYER}从助手那儿\n"
    .string "得到了{STR_VAR_2}。$"

Route11_EastEntrance_2F_Text_ExplainItemfinder::
    .string "地面上有\n"
    .string "隐藏的道具。\p"
    .string "就用寻宝机器来找出\n"
    .string "在你周围的隐藏道具吧。\p"
    .string "由于这个机器机能有限，\n"
    .string "所以它不能直接探明道具的位置。\p"
    .string "它所做的\n"
    .string "只有指向道具所在的方向。\p"
    .string "找准方向之后，\n"
    .string "侦察一下你认为可疑的地方。$"

Route11_EastEntrance_2F_Text_BigMonAsleepOnRoad::
    .string "一架望远镜……\n"
    .string "我来看看……\p"
    .string "啊，一只体形巨大的宝可梦\n"
    .string "正在路上睡觉！$"

Route11_EastEntrance_2F_Text_WhatABreathtakingView::
    .string "一架望远镜……\n"
    .string "我来看看……\p"
    .string "哇哦，多么壮观的美景！$"

Route11_EastEntrance_2F_Text_RockTunnelGoodRouteToLavender::
    .string "一架望远镜……\n"
    .string "我来看看……\p"
    .string "从华蓝市\n"
    .string "再到紫苑镇…\p"
    .string "岩山隧道也许是一个\n"
    .string "不错的路线。$"

