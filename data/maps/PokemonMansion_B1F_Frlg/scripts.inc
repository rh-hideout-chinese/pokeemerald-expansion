PokemonMansion_B1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PokemonMansion_B1F_OnLoad
	.byte 0

PokemonMansion_B1F_OnLoad::
	call_if_set FLAG_POKEMON_MANSION_SWITCH_STATE, PokemonMansion_EventScript_PressSwitch_B1F
	end

PokemonMansion_B1F_EventScript_Statue::
	lockall
	setvar VAR_0x8004, 3
	call PokemonMansion_EventScript_SecretSwitch
	playse SE_UNLOCK
	special DrawWholeMapView
	waitse
	releaseall
	end

PokemonMansion_B1F_EventScript_DiarySep1st::
	msgbox PokemonMansion_B1F_Text_MewtwoIsFarTooPowerful, MSGBOX_SIGN
	end

PokemonMansion_B1F_EventScript_Lewis::
	trainerbattle_single TRAINER_BURGLAR_LEWIS, PokemonMansion_B1F_Text_LewisIntro, PokemonMansion_B1F_Text_LewisDefeat
	msgbox PokemonMansion_B1F_Text_LewisPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonMansion_B1F_EventScript_Ivan::
	trainerbattle_single TRAINER_SCIENTIST_IVAN, PokemonMansion_B1F_Text_IvanIntro, PokemonMansion_B1F_Text_IvanDefeat
	msgbox PokemonMansion_B1F_Text_IvanPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonMansion_B1F_Text_LewisIntro::
    .string "哇啊……\n"
    .string "我现在在哪里？$"

PokemonMansion_B1F_Text_LewisDefeat::
    .string "哇啊！$"

PokemonMansion_B1F_Text_LewisPostBattle::
    .string "你可以发现到处都是散落的东西。\n"
    .string "一定是居民们丢下的。$"

PokemonMansion_B1F_Text_IvanIntro::
    .string "这里是建造实验室的理想地方。\n"
    .string "看看这儿。$"

PokemonMansion_B1F_Text_IvanDefeat::
    .string "那是用来干什么的？$"

PokemonMansion_B1F_Text_IvanPostBattle::
    .string "我喜欢这里。\n"
    .string "它有助于我的研究。$"

PokemonMansion_B1F_Text_MewtwoIsFarTooPowerful::
    .string "日记：9月1号\n"
    .string "超梦太强大了。\p"
    .string "我们不能控制它了，\n"
    .string "它越来越邪恶了……$"

