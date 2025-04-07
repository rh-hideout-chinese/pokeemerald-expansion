.set LOCALID_NURSE, 1

VerdanturfTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

VerdanturfTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_VERDANTURF_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

VerdanturfTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

VerdanturfTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_EventScript_ExpertM::
	msgbox VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon:
    .string "如果你不信任自己的宝可梦，\n你就不是一个真正的\l训练师。\p只有相信\n自己宝可梦的人\l才能笑到最后。$"

VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent:
    .string "大家都想来\n绿荫镇的原因…\p毫无疑问，\n是对战帐篷。\p还是说，你是来\n找朋友的？$"

