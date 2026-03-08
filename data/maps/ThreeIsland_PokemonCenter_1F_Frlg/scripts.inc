ThreeIsland_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ThreeIsland_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

ThreeIsland_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_THREE_ISLAND
	end

ThreeIsland_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

ThreeIsland_PokemonCenter_1F_EventScript_Sailor::
	msgbox ThreeIsland_PokemonCenter_1F_Text_ImpossibleToSurfBetweenIslands, MSGBOX_NPC
	end

ThreeIsland_PokemonCenter_1F_EventScript_Lass::
	msgbox ThreeIsland_PokemonCenter_1F_Text_AlwaysBerriesInBerryForest, MSGBOX_NPC
	end

ThreeIsland_PokemonCenter_1F_EventScript_Rocker::
	msgbox ThreeIsland_PokemonCenter_1F_Text_PCNetworkCanLinkWithKanto, MSGBOX_NPC
	end

ThreeIsland_PokemonCenter_1F_Text_PCNetworkCanLinkWithKanto::
	.string "嘿！你听新闻了吗？\p"
	.string "这里的电脑网络\n"
	.string "已经可以和关都的电脑连接了！\p"
	.string "我不知道怎么明白原理，\n"
	.string "但听起来真的很棒！$"

ThreeIsland_PokemonCenter_1F_Text_ImpossibleToSurfBetweenIslands::
	.string "在三个小岛中间\n"
	.string "不能使用冲浪。\p"
	.string "水流速度很快\n"
	.string "而且并非一直都是往一个方向流……$"

ThreeIsland_PokemonCenter_1F_Text_AlwaysBerriesInBerryForest::
	.string "让我们碾碎树果吧！\n"
	.string "……你说那会浪费树果？\p"
	.string "在树果森林的路面上\n"
	.string "你经常会找到树果！$"

