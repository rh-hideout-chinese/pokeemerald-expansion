FiveIsland_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FiveIsland_OnTransition
	.byte 0

FiveIsland_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_FIVE_ISLAND
	end

FiveIsland_EventScript_IslandSign::
	msgbox FiveIsland_Text_IslandSign, MSGBOX_SIGN
	end

FiveIsland_EventScript_BugCatcher::
	msgbox FiveIsland_Text_WeirdBuildingInMeadow, MSGBOX_NPC
	end

FiveIsland_EventScript_Fisher::
	msgbox FiveIsland_Text_BeenGettingBusierAroundHere, MSGBOX_NPC
	end

FiveIsland_Text_IslandSign::
    .string "五之岛\n"
    .string "时间之岛：时间起源之处$"

FiveIsland_Text_WeirdBuildingInMeadow::
    .string "啊，真让人不爽。\n"
    .string "我想在空地里玩。\p"
    .string "但他们在那里造了个奇怪的建筑，\n"
    .string "让我没法去玩了。$"

FiveIsland_Text_BeenGettingBusierAroundHere::
    .string "最近这里变得\n"
    .string "越来越繁忙了。\p"
    .string "我很久都没钓到好点的鱼了。$"

