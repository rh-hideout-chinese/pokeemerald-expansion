CinnabarIsland_PokemonLab_Entrance_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CinnabarIsland_PokemonLab_Entrance_OnTransition
	.byte 0

CinnabarIsland_PokemonLab_Entrance_OnTransition::
	call_if_eq VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_REVIVE_STATE, 1, CinnabarIsland_PokemonLab_Entrance_EventScript_ReadyFossil
	end

CinnabarIsland_PokemonLab_Entrance_EventScript_ReadyFossil::
	setvar VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_REVIVE_STATE, 2
	return

CinnabarIsland_PokemonLab_Entrance_EventScript_Scientist::
	msgbox CinnabarIsland_PokemonLab_Entrance_Text_StudyMonsExtensively, MSGBOX_NPC
	end

CinnabarIsland_PokemonLab_Entrance_EventScript_DrFujiPhoto::
	msgbox CinnabarIsland_PokemonLab_Entrance_Text_PhotoOfLabFounderDrFuji, MSGBOX_SIGN
	end

CinnabarIsland_PokemonLab_Entrance_EventScript_MeetingRoomSign::
	msgbox CinnabarIsland_PokemonLab_Entrance_Text_MeetingRoomSign, MSGBOX_SIGN
	end

CinnabarIsland_PokemonLab_Entrance_EventScript_RAndDRoomSign::
	msgbox CinnabarIsland_PokemonLab_Entrance_Text_RAndDRoomSign, MSGBOX_SIGN
	end

CinnabarIsland_PokemonLab_Entrance_EventScript_TestingRoomSign::
	msgbox CinnabarIsland_PokemonLab_Entrance_Text_TestingRoomSign, MSGBOX_SIGN
	end

CinnabarIsland_Gym_Text_PhotoOfBlaineAndFuji::
    .string "这张照片上的人是夏伯和\n"
    .string "富士老人。\p"
    .string "他们咧着嘴笑着\n"
    .string "肩并肩的站在一起。$"

CinnabarIsland_PokemonLab_Entrance_Text_StudyMonsExtensively::
    .string "我们每天都要学习大量\n"
    .string "宝可梦的知识。\p"
    .string "人们经常带着稀有的宝可梦来\n"
    .string "作为对我们的考验。$"

CinnabarIsland_PokemonLab_Entrance_Text_PhotoOfLabFounderDrFuji::
    .string "一张研究所的创始人的照片……\n"
    .string "富士博士？！$"

CinnabarIsland_PokemonLab_Entrance_Text_MeetingRoomSign::
    .string "宝可梦实验室\n"
    .string "会客室$"

CinnabarIsland_PokemonLab_Entrance_Text_RAndDRoomSign::
    .string "宝可梦实验室\n"
    .string "研究与发展办公室$"

CinnabarIsland_PokemonLab_Entrance_Text_TestingRoomSign::
    .string "宝可梦实验室\n"
    .string "聊天室$"

