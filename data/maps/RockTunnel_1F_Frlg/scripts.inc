RockTunnel_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RockTunnel_1F_OnTransition
	.byte 0

RockTunnel_1F_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_ROCK_TUNNEL_1F
	end

RockTunnel_1F_EventScript_RouteSign::
	msgbox RockTunnel_1F_Text_RouteSign, MSGBOX_SIGN
	end

RockTunnel_1F_EventScript_Lenny::
	trainerbattle_single TRAINER_HIKER_LENNY, RockTunnel_1F_Text_LennyIntro, RockTunnel_1F_Text_LennyDefeat
	msgbox RockTunnel_1F_Text_LennyPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_1F_EventScript_Oliver::
	trainerbattle_single TRAINER_HIKER_OLIVER, RockTunnel_1F_Text_OliverIntro, RockTunnel_1F_Text_OliverDefeat
	msgbox RockTunnel_1F_Text_OliverPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_1F_EventScript_Lucas::
	trainerbattle_single TRAINER_HIKER_LUCAS, RockTunnel_1F_Text_LucasIntro, RockTunnel_1F_Text_LucasDefeat
	msgbox RockTunnel_1F_Text_LucasPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_1F_EventScript_Ashton::
	trainerbattle_single TRAINER_POKEMANIAC_ASHTON, RockTunnel_1F_Text_AshtonIntro, RockTunnel_1F_Text_AshtonDefeat
	msgbox RockTunnel_1F_Text_AshtonPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_1F_EventScript_Leah::
	trainerbattle_single TRAINER_PICNICKER_LEAH, RockTunnel_1F_Text_LeahIntro, RockTunnel_1F_Text_LeahDefeat
	msgbox RockTunnel_1F_Text_LeahPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_1F_EventScript_Ariana::
	trainerbattle_single TRAINER_PICNICKER_ARIANA, RockTunnel_1F_Text_ArianaIntro, RockTunnel_1F_Text_ArianaDefeat
	msgbox RockTunnel_1F_Text_ArianaPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_1F_EventScript_Dana::
	trainerbattle_single TRAINER_PICNICKER_DANA, RockTunnel_1F_Text_DanaIntro, RockTunnel_1F_Text_DanaDefeat
	msgbox RockTunnel_1F_Text_DanaPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_1F_Text_LennyIntro::
    .string "这条隧道有很长的路，孩子！$"

RockTunnel_1F_Text_LennyDefeat::
    .string "啊哇！\n"
    .string "你赢了！$"

RockTunnel_1F_Text_LennyPostBattle::
    .string "大岩蛇的很少在这出没，\n"
    .string "但要是在寻找的时候，\p"
    .string "遇上了高等级大岩蛇，\n"
    .string "会给你造成重创！$"

RockTunnel_1F_Text_OliverIntro::
    .string "嗯哼。\n"
    .string "我也许在这里迷路了……$"

RockTunnel_1F_Text_OliverDefeat::
    .string "放松！\n"
    .string "我在做什么？\l"
    .string "出去的路是哪条？$"

RockTunnel_1F_Text_OliverPostBattle::
    .string "12号道路上那只沉睡的宝可梦\n"
    .string "让我不得不绕道而行。$"

RockTunnel_1F_Text_LucasIntro::
    .string "像你这种外行\n"
    .string "在我面前\n"
    .string "给我放尊重点！$"

RockTunnel_1F_Text_LucasDefeat::
    .string "我投降！$"

RockTunnel_1F_Text_LucasPostBattle::
    .string "你已经有足够的能力去登山了！$"

RockTunnel_1F_Text_AshtonIntro::
    .string "宝可梦！\n"
    .string "准备！\n"
    .string "战斗开始！$"

RockTunnel_1F_Text_AshtonDefeat::
    .string "游戏结束了！$"

RockTunnel_1F_Text_AshtonPostBattle::
    .string "好吧，我一会儿就去抓只超音蝠！$"

RockTunnel_1F_Text_LeahIntro::
    .string "喂！\p"
    .string "这里这么黑，\n"
    .string "别想在这里耍小花招！$"

RockTunnel_1F_Text_LeahDefeat::
    .string "太暗了…$"

RockTunnel_1F_Text_LeahPostBattle::
    .string "我在隧道里见过腕力。$"

RockTunnel_1F_Text_DanaIntro::
    .string "我走了这么远\n"
    .string "就是为了寻找宝可梦！$"

RockTunnel_1F_Text_DanaDefeat::
    .string "我的宝可梦全倒下了！$"

RockTunnel_1F_Text_DanaPostBattle::
    .string "你看起来很可爱，\n"
    .string "而且无公害。\n"
    .string "莫非是我想错了么！$"

RockTunnel_1F_Text_ArianaIntro::
    .string "你带着宝可梦！\n"
    .string "那么战个痛快吧！$"

RockTunnel_1F_Text_ArianaDefeat::
    .string "你打得可真卖命！$"

RockTunnel_1F_Text_ArianaPostBattle::
    .string "哇哦！\n"
    .string "我现在汗流浃背。$"

RockTunnel_1F_Text_RouteSign::
    .string "岩山隧道\n"
    .string "华蓝市 - 紫苑镇$"

