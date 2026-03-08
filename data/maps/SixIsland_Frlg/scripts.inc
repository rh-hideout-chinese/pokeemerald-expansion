SixIsland_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SixIsland_OnTransition
	.byte 0

SixIsland_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SIX_ISLAND
	end

SixIsland_EventScript_Hiker::
	msgbox SixIsland_Text_ThatWayToWaterPathRuinValley, MSGBOX_NPC
	end

SixIsland_EventScript_Boy::
	msgbox SixIsland_Text_SkyAtNightIsFantastic, MSGBOX_NPC
	end

SixIsland_EventScript_IslandSign::
	msgbox SixIsland_Text_IslandSign, MSGBOX_SIGN
	end

SixIsland_Text_IslandSign::
    .string "六之岛\n"
    .string "古代智慧传承之岛$"

SixIsland_Text_ThatWayToWaterPathRuinValley::
    .string "继续沿着这条路走\n"
    .string "就是水之步道。\p"
    .string "在那里转一转的话\n"
    .string "就能找到遗迹山谷。$"

SixIsland_Text_SkyAtNightIsFantastic::
    .string "在离城市那么远的地方，\n"
    .string "夜晚的天空可是相当迷人。$"

