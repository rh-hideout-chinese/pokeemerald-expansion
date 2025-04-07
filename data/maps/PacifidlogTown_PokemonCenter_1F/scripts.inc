.set LOCALID_NURSE, 1

PacifidlogTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

PacifidlogTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_PACIFIDLOG_TOWN
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Girl::
	msgbox PacifidlogTown_PokemonCenter_1F_Text_WhatColorTrainerCard, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Woman::
	msgbox PacifidlogTown_PokemonCenter_1F_Text_OnColonyOfCorsola, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_EventScript_OldMan::
	msgbox PacifidlogTown_PokemonCenter_1F_Text_AncestorsLivedOnBoats, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_Text_WhatColorTrainerCard:
    .string "你的训练师卡片是什么颜色？\n我的是褐色的！$"

PacifidlogTown_PokemonCenter_1F_Text_OnColonyOfCorsola:
    .string "暮水镇浮在\n大群太阳珊瑚上。\p我这么说的话，\n你会相信吗？$"

PacifidlogTown_PokemonCenter_1F_Text_AncestorsLivedOnBoats:
    .string "据说暮水镇人的\n祖先在船上出生，\l在船上生活，\l在船上死亡。\p我想，他们过着那种\n生活的目的，是为了\l寻找什么。$"

