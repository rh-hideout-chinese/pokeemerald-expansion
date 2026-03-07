PokemonMansion_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PokemonMansion_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, PokemonMansion_1F_OnTransition
	.byte 0

PokemonMansion_1F_OnLoad::
	call_if_set FLAG_POKEMON_MANSION_SWITCH_STATE, PokemonMansion_EventScript_PressSwitch_1F
	end

PokemonMansion_1F_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_POKEMON_MANSION_1F
	end

PokemonMansion_1F_EventScript_Statue::
	lockall
	setvar VAR_0x8004, 0
	call PokemonMansion_EventScript_SecretSwitch
	playse SE_UNLOCK
	special DrawWholeMapView
	waitse
	releaseall
	end

PokemonMansion_1F_EventScript_Ted::
	trainerbattle_single TRAINER_SCIENTIST_TED, PokemonMansion_1F_Text_TedIntro, PokemonMansion_1F_Text_TedDefeat
	msgbox PokemonMansion_1F_Text_TedPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonMansion_1F_EventScript_Johnson::
	trainerbattle_single TRAINER_YOUNGSTER_JOHNSON, PokemonMansion_1F_Text_JohnsonIntro, PokemonMansion_1F_Text_JohnsonDefeat
	msgbox PokemonMansion_1F_Text_JohnsonPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonMansion_1F_Text_TedIntro::
    .string "你是谁？\n"
    .string "这里不应该有任何人。$"

PokemonMansion_1F_Text_TedDefeat::
    .string "哎呦！$"

PokemonMansion_1F_Text_TedPostBattle::
    .string "一把钥匙？我不知道\n"
    .string "你在说什么。$"

PokemonMansion_1F_Text_JohnsonIntro::
    .string "哇哇哇！你把我吓了一跳！\n"
    .string "我以为你是鬼呢。$"

PokemonMansion_1F_Text_JohnsonDefeat::
    .string "啊啊！\n"
    .string "我没有得到过哪怕是一场胜利。$"

PokemonMansion_1F_Text_JohnsonPostBattle::
    .string "我一个人到这里来探索，\n"
    .string "但我觉得很害怕。\p"
    .string "我还是尽快离开这里吧。$"

