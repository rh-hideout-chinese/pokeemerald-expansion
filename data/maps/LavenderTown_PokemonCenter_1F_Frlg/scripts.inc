LavenderTown_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavenderTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

LavenderTown_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_LAVENDER_TOWN
	end

LavenderTown_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

LavenderTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox LavenderTown_PokemonCenter_1F_Text_RocketsDoAnythingForMoney, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_1F_EventScript_Lass::
	msgbox LavenderTown_PokemonCenter_1F_Text_CubonesMotherKilledByRockets, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_1F_EventScript_Youngster::
	msgbox LavenderTown_PokemonCenter_1F_Text_PeoplePayForCuboneSkulls, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_1F_Text_RocketsDoAnythingForMoney::
    .string "火箭队为了钱\n"
    .string "什么都能做！\p"
    .string "世界上没有比这更肮脏的事情，\n"
    .string "更可耻的行为，和更恶劣的罪行了。$"

LavenderTown_PokemonCenter_1F_Text_CubonesMotherKilledByRockets::
    .string "我看见卡拉卡拉的妈妈\n"
    .string "曾努力从火箭队手中逃跑。\p"
    .string "但是它在逃跑过程中被杀了……$"

LavenderTown_PokemonCenter_1F_Text_PeoplePayForCuboneSkulls::
    .string "你知道卡拉卡拉头上都带着\n"
    .string "骨头吗？\p"
    .string "人们会花大价钱买一个的。$"

