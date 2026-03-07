Route18_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route18_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route18_OnWarp
	.byte 0

Route18_OnTransition::
	call_if_eq VAR_MAP_SCENE_ROUTE16, 1, Route18_OnTransitionCyclingRoad
	end

Route18_OnTransitionCyclingRoad::
	setflag FLAG_SYS_ON_CYCLING_ROAD
	return

Route18_OnWarp::
	map_script_2 VAR_MAP_SCENE_ROUTE16, 1, Route18_OnWarpCyclingRoad
	.2byte 0

Route18_OnWarpCyclingRoad::
	special ForcePlayerOntoBike
	end

Route18_EventScript_RouteSign::
	msgbox Route18_Text_RouteSign, MSGBOX_SIGN
	end

Route18_EventScript_CyclingRoadSign::
	msgbox Route18_Text_CyclingRoadSign, MSGBOX_SIGN
	end

Route18_Text_WiltonIntro::
    .string "我总是踏遍每一个草丛\n"
    .string "来寻找新的宝可梦。$"

Route18_Text_WiltonDefeat::
    .string "呃！$"

Route18_Text_WiltonPostBattle::
    .string "我希望有一辆自行车！$"

Route18_Text_RamiroIntro::
    .string "咕咕！\n"
    .string "你喜欢我学的鸟叫声吗？$"

Route18_Text_RamiroDefeat::
    .string "我不得不打扰你！$"

Route18_Text_RamiroPostBattle::
    .string "我在周末喜欢收集海洋的宝可梦，\n"
    .string "因为大海离我太近了。$"

Route18_Text_JacobIntro::
    .string "这是我的草地！\n"
    .string "快出去！$"

Route18_Text_JacobDefeat::
    .string "见鬼！$"

Route18_Text_JacobPostBattle::
    .string "这是我最喜欢收服\n"
    .string "宝可梦的地方。$"

Route18_Text_RouteSign::
    .string "18号道路\n"
    .string "玉虹市-浅红市$"

Route18_Text_CyclingRoadSign::
    .string "单车路\n"
    .string "不允许步行的人进入！$"

