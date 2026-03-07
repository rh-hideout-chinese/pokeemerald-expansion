Route16_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Route16_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route16_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route16_OnWarp
	.byte 0

Route16_OnResume::
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Route16_EventScript_RemoveSnorlax
	end

Route16_EventScript_RemoveSnorlax::
	removeobject VAR_LAST_TALKED
	return

Route16_OnTransition::
	call_if_eq VAR_MAP_SCENE_ROUTE16, 1, Route16_OnTransitionCyclingRoad
	end

Route16_OnTransitionCyclingRoad::
	setflag FLAG_SYS_ON_CYCLING_ROAD
	return

Route16_OnWarp::
	map_script_2 VAR_MAP_SCENE_ROUTE16, 1, Route16_OnWarpCyclingRoad
	.2byte 0

Route16_OnWarpCyclingRoad::
	special ForcePlayerOntoBike
	end

Route16_EventScript_Snorlax::
	lock
	faceplayer
	goto_if_unset FLAG_GOT_POKE_FLUTE, Route16_EventScript_SnorlaxNoPokeFlute
	msgbox Text_WantToUsePokeFlute, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route16_EventScript_DontUsePokeFlute
	call EventScript_AwakenSnorlax
	setwildbattle SPECIES_SNORLAX, 30
	waitse
	playmoncry SPECIES_SNORLAX, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_HIDE_ROUTE_16_SNORLAX
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route16_EventScript_FoughtSnorlax
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route16_EventScript_FoughtSnorlax
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Route16_EventScript_FoughtSnorlax
	release
	end

Route16_EventScript_DontUsePokeFlute::
	release
	end

Route16_EventScript_FoughtSnorlax::
	msgbox Text_SnorlaxReturnedToMountains
	release
	end

Route16_EventScript_SnorlaxNoPokeFlute::
	msgbox Route16_Text_MonSprawledOutInSlumber
	release
	end

Route16_EventScript_CyclingRoadSign::
	msgbox Route16_Text_CyclingRoadSign, MSGBOX_SIGN
	end

Route16_EventScript_RouteSign::
	msgbox Route16_Text_RouteSign, MSGBOX_SIGN
	end

Route16_Text_LaoIntro::
    .string "你想要干什么？$"

Route16_Text_LaoDefeat::
    .string "你竟敢嘲笑我！$"

Route16_Text_LaoPostBattle::
    .string "我们喜欢在这里游荡。\n"
    .string "你呢？$"

Route16_Text_KojiIntro::
    .string "漂亮的自行车！\n"
    .string "交出来！$"

Route16_Text_KojiDefeat::
    .string "我晕了！$"

Route16_Text_KojiPostBattle::
    .string "刚才我啥也没说，谁想要你的自行车！$"

Route16_Text_LukeIntro::
    .string "出来打一架吧，胆小鬼！$"

Route16_Text_LukeDefeat::
    .string "你胆子有点大啊！$"

Route16_Text_LukePostBattle::
    .string "输掉什么的最讨厌了！\n"
    .string "赶快从我眼前消失！$"

Route16_Text_HideoIntro::
    .string "嘿，你刚才撞着我了！$"

Route16_Text_HideoDefeat::
    .string "可恶！$"

Route16_Text_HideoPostBattle::
    .string "管你看的顺不顺眼，\n"
    .string "我们就爱在这儿周围转。\p"
    .string "你可以沿着海岸从浅红\n"
    .string "绕路去枯叶。$"

Route16_Text_CamronIntro::
    .string "我感到又饿又心烦！\n"
    .string "我需要一个出气筒！$"

Route16_Text_CamronDefeat::
    .string "糟糕，麻烦，太颓了！$"

Route16_Text_CamronPostBattle::
    .string "要是我有了宝可梦，\n"
    .string "他们必将成为我的凶器。\p"
    .string "我会用它们\n"
    .string "把我的敌人撕烂。$"

Route16_Text_RubenIntro::
    .string "喂，朋友！\n"
    .string "来玩儿一把怎么样！$"

Route16_Text_RubenDefeat::
    .string "我要疯了！$"

Route16_Text_RubenPostBattle::
    .string "我和我讨厌的宝可梦通过骚扰人们\n"
    .string "来获得快乐。\p"
    .string "它们吓唬人可是能手，\n"
    .string "当然了，咬人也不差。$"

Route16_Text_MonSprawledOutInSlumber::
    .string "一只宝可梦躺在那儿，\n"
    .string "睡得无比香甜。$"

Route16_Text_CyclingRoadSign::
    .string "享受斜坡吧！\n"
    .string "单车路$"

Route16_Text_RouteSign::
    .string "16号道路\n"
    .string "玉虹市-浅红市$"

Route16_Text_JedIntro::
    .string "阿神：我们的爱是无穷无尽的。\n"
    .string "就在此向你展示吧！$"

Route16_Text_JedDefeat::
    .string "阿神：噢，不！\n"
    .string "我的爱见证了我的失败！$"

Route16_Text_JedPostBattle::
    .string "阿神：听着，嘉穗。\n"
    .string "别对我白花心思了。$"

Route16_Text_JedNotEnoughMons::
    .string "阿神：你眼里只有宝可梦？\n"
    .string "你心里没有爱吗？$"

Route16_Text_LeaIntro::
    .string "嘉穗：有时，过于强烈的爱\n"
    .string "使我感到害怕。$"

Route16_Text_LeaDefeat::
    .string "嘉穗：噢！尽管输了，\n"
    .string "阿神还是看起来很帅！$"

Route16_Text_LeaPostBattle::
    .string "嘉穗：呵呵，不好意思。\n"
    .string "阿神太帅了。$"

Route16_Text_LeaNotEnoughMons::
    .string "嘉穗 哦，你没有两只宝可梦\n"
    .string "和你一起？\p"
    .string "你和你的宝可梦\n"
    .string "不感到孤独吗？$"
