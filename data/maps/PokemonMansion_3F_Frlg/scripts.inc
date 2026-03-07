PokemonMansion_3F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PokemonMansion_3F_OnLoad
	.byte 0

PokemonMansion_3F_OnLoad::
	call_if_set FLAG_POKEMON_MANSION_SWITCH_STATE, PokemonMansion_EventScript_PressSwitch_3F
	end

PokemonMansion_3F_EventScript_Statue::
	lockall
	setvar VAR_0x8004, 2
	call PokemonMansion_EventScript_SecretSwitch
	playse SE_UNLOCK
	special DrawWholeMapView
	waitse
	releaseall
	end

PokemonMansion_3F_EventScript_DiaryFeb6th::
	msgbox PokemonMansion_1F_Text_MewGaveBirthToMewtwo, MSGBOX_SIGN
	end

PokemonMansion_3F_EventScript_Simon::
	trainerbattle_single TRAINER_BURGLAR_SIMON, PokemonMansion_1F_Text_SimonIntro, PokemonMansion_1F_Text_SimonDefeat
	msgbox PokemonMansion_1F_Text_SimonPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonMansion_3F_EventScript_Braydon::
	trainerbattle_single TRAINER_SCIENTIST_BRAYDON, PokemonMansion_1F_Text_BraydonIntro, PokemonMansion_1F_Text_BraydonDefeat
	msgbox PokemonMansion_1F_Text_BraydonPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonMansion_1F_Text_SimonIntro::
    .string "这个地方，真的，好大啊！$"

PokemonMansion_1F_Text_SimonDefeat::
    .string "啊啊！$"

PokemonMansion_1F_Text_SimonPostBattle::
    .string "我不知道我的同伙去哪儿了。$"

PokemonMansion_1F_Text_BraydonIntro::
    .string "我的导师曾经住在这里。$"

PokemonMansion_1F_Text_BraydonDefeat::
    .string "呼！\n"
    .string "让人喘不过气来！$"

PokemonMansion_1F_Text_BraydonPostBattle::
    .string "所以，你被卡住了吗？\n"
    .string "试着从那边跳下去！$"

PokemonMansion_1F_Text_MewGaveBirthToMewtwo::
    .string "日记：2月6号\n"
    .string "梦幻生产了。\p"
    .string "我们把新生的宝可梦称作超梦。$"

