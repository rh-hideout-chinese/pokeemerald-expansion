SaffronCity_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

SaffronCity_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_SAFFRON_CITY
	end

SaffronCity_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

SaffronCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox SaffronCity_PokemonCenter_1F_Text_SilphCoVictimOfFame, MSGBOX_NPC
	end

SaffronCity_PokemonCenter_1F_EventScript_Woman::
	msgbox SaffronCity_PokemonCenter_1F_Text_GrowthRatesDifferBySpecies, MSGBOX_NPC
	end

SaffronCity_PokemonCenter_1F_EventScript_Youngster::
	lock
	faceplayer
	goto_if_eq VAR_MAP_SCENE_SILPH_CO_11F, 1, SaffronCity_PokemonCenter_1F_EventScript_YoungsterRocketsGone
	msgbox SaffronCity_PokemonCenter_1F_Text_GreatIfEliteFourCameBeatRockets
	release
	end

SaffronCity_PokemonCenter_1F_EventScript_YoungsterRocketsGone::
	msgbox SaffronCity_PokemonCenter_1F_Text_TeamRocketTookOff
	release
	end

SaffronCity_PokemonCenter_1F_Text_GrowthRatesDifferBySpecies::
    .string "不同的宝可梦成长速度\n"
    .string "不一样。$"

SaffronCity_PokemonCenter_1F_Text_SilphCoVictimOfFame::
    .string "西尔佛公司的名声远扬。\p"
    .string "它的名气吸引了\n"
    .string "火箭队。$"

SaffronCity_PokemonCenter_1F_Text_GreatIfEliteFourCameBeatRockets::
    .string "唉……\n"
    .string "这样的话不就好了？\p"
    .string "让四天王赶来\n"
    .string "灭了火箭队？$"

SaffronCity_PokemonCenter_1F_Text_TeamRocketTookOff::
    .string "火箭队离开了！\n"
    .string "我们又可以安全地出行了！\l"
    .string "太棒了！$"

