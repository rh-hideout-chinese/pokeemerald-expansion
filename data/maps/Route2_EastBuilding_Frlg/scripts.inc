.equ REQUIRED_SEEN_MONS, 10

Route2_EastBuilding_Frlg_MapScripts::
	.byte 0

Route2_EastBuilding_EventScript_Aide::
	lock
	faceplayer
	call Route2_EastBuilding_EventScript_GetAideRequestInfo
	goto_if_set FLAG_GOT_HM05, Route2_EastBuilding_EventScript_AlreadyGotHM05
	msgbox Route2_EastBuilding_Text_GiveHM05IfSeen10Mons, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Aide_EventScript_DeclineCheckMons
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetFrlgPokedexCount
	buffernumberstring STR_VAR_3, VAR_0x8006
	call Route2_EastBuilding_EventScript_GetAideRequestInfo
	goto_if_lt VAR_0x8006, REQUIRED_SEEN_MONS, Aide_EventScript_HaventCaughtEnough
	msgbox Route2_EastBuilding_Text_GreatHereYouGo
	checkitemspace ITEM_HM05
	goto_if_eq VAR_RESULT, FALSE, Aide_EventScript_NoRoomForItem
	giveitem_msg Route2_EastBuilding_Text_ReceivedHM05FromAide, ITEM_HM05
	setflag FLAG_GOT_HM05
	msgbox Route2_EastBuilding_Text_ExplainHM05
	release
	end

Route2_EastBuilding_EventScript_AlreadyGotHM05::
	msgbox Route2_EastBuilding_Text_ExplainHM05
	release
	end

Route2_EastBuilding_EventScript_GetAideRequestInfo::
	buffernumberstring STR_VAR_1, REQUIRED_SEEN_MONS
	bufferitemname STR_VAR_2, ITEM_HM05
	return

Route2_EastBuilding_EventScript_Rocker::
	msgbox Route2_EastBuilding_Text_CanGetThroughRockTunnel, MSGBOX_NPC
	end

Route2_EastBuilding_Text_GiveHM05IfSeen10Mons::
    .string "嗨！还记得我吗？\n"
    .string "我是一个大木博士的助手。\p"
    .string "如果你的宝可梦图鉴收集了十个\n"
    .string "数据，我会给你\l"
    .string "一个小奖品。\p"
    .string "大木博士委托我带\n"
    .string "HM05给你。\p"
    .string "{PLAYER}，我问问你。\p"
    .string "你收集了十个不同\n"
    .string "的宝可梦数据了吗？$"

Route2_EastBuilding_Text_GreatHereYouGo::
    .string "太好了！你已经拥有了\n"
    .string "{STR_VAR_3}种宝可梦的数据！\p"
    .string "恭喜你！\n"
    .string "它是你的了！$"

Route2_EastBuilding_Text_ReceivedHM05FromAide::
    .string "{PLAYER}从助手那里\n"
    .string "得到了HM05。$"

Route2_EastBuilding_Text_ExplainHM05::
    .string "HM05包含了隐藏技能\n"
    .string "闪光。\p"
    .string "闪光能照亮黑暗的洞穴\n"
    .string "和隧道。$"

Route2_EastBuilding_Text_CanGetThroughRockTunnel::
    .string "一旦有宝可梦学会了闪光，\n"
    .string "你就能通过岩山隧道了。$"

