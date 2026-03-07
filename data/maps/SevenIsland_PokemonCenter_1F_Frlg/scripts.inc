SevenIsland_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SevenIsland_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

SevenIsland_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_SEVEN_ISLAND
	end

SevenIsland_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

SevenIsland_PokemonCenter_1F_EventScript_OldMan::
	msgbox SevenIsland_PokemonCenter_1F_Text_EventsDependingOnConnections, MSGBOX_NPC
	end

SevenIsland_PokemonCenter_1F_EventScript_Sailor::
	msgbox SevenIsland_PokemonCenter_1F_Text_DidYouRideSeagallopHere, MSGBOX_NPC
	end

SevenIsland_PokemonCenter_1F_EventScript_Beauty::
	msgbox SevenIsland_PokemonCenter_1F_Text_CheckOutTrainerTower, MSGBOX_NPC
	end

SevenIsland_PokemonCenter_1F_Text_EventsDependingOnConnections::
    .string "在这岛上，不同的事件\n"
    .string "都有着一定的关联。\p"
    .string "这都是些什么关联？\p"
    .string "这就要靠你\n"
    .string "自己去探索了。$"

SevenIsland_PokemonCenter_1F_Text_DidYouRideSeagallopHere::
    .string "你是乘坐海烈焰马号\n"
    .string "来到这里的吗？\p"
    .string "这里至少有十艘\n"
    .string "这种高速船。\p"
    .string "不过我都不知道\n"
    .string "它们会航行到哪里。$"

SevenIsland_PokemonCenter_1F_Text_CheckOutTrainerTower::
    .string "如果你够自信，你可以\n"
    .string "去训练家之塔。$"

