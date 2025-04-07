.set LOCALID_NURSE, 1

OldaleTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

OldaleTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_OLDALE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

OldaleTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Boy::
	msgbox OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEDEX_GET, OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable
	msgbox OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable::
	msgbox OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC:
    .string "那边角落里的电脑免费提供给\n所有宝可梦训练师使用，\p就是说，你也可以\n随意使用。$"

OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat:
    .string "宝可梦中心真棒！\p你可以随时使用他们\n提供的服务，而且完全免费，\l什么也不用担心！$"

OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable:
    .string "二楼的宝可梦无线俱乐部\n最近刚刚建好，\p但据说现在\n还在调整中。$"

OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub:
    .string "二楼的宝可梦无线俱乐部\n最近刚刚建好，\p我马上就去交换了宝可梦。$"

