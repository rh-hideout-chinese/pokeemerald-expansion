PokemonTower_5F_Frlg_MapScripts::
	.byte 0

PokemonTower_5F_EventScript_Channeler::
	msgbox PokemonTower_5F_Text_RestHereInPurifiedSpace, MSGBOX_NPC
	end

PokemonTower_5F_EventScript_PurifiedZone::
	lockall
	fadescreen FADE_TO_WHITE
	special HealPlayerParty
	fadescreen FADE_FROM_WHITE
	msgbox PokemonTower_5F_Text_PurifiedZoneMonsFullyHealed
	setvar VAR_TEMP_1, 1
	releaseall
	end

PokemonTower_5F_EventScript_ExitPurifiedZone::
	lockall
	setvar VAR_TEMP_1, 0
	releaseall
	end

PokemonTower_5F_EventScript_Tammy::
	trainerbattle_single TRAINER_CHANNELER_TAMMY, PokemonTower_5F_Text_TammyIntro, PokemonTower_5F_Text_TammyDefeat
	msgbox PokemonTower_5F_Text_TammyPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_5F_EventScript_Ruth::
	trainerbattle_single TRAINER_CHANNELER_RUTH, PokemonTower_5F_Text_RuthIntro, PokemonTower_5F_Text_RuthDefeat
	msgbox PokemonTower_5F_Text_RuthPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_5F_EventScript_Karina::
	trainerbattle_single TRAINER_CHANNELER_KARINA, PokemonTower_5F_Text_KarinaIntro, PokemonTower_5F_Text_KarinaDefeat
	msgbox PokemonTower_5F_Text_KarinaPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_5F_EventScript_Janae::
	trainerbattle_single TRAINER_CHANNELER_JANAE, PokemonTower_5F_Text_JanaeIntro, PokemonTower_5F_Text_JanaeDefeat
	msgbox PokemonTower_5F_Text_JanaePostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_5F_Text_RestHereInPurifiedSpace::
    .string "过来，孩子！\n"
    .string "我已经净化了这里！\l"
    .string "在这里回复体力吧。$"

PokemonTower_5F_Text_TammyIntro::
    .string "给……我……\n"
    .string "你的……全部……$"

PokemonTower_5F_Text_TammyDefeat::
    .string "呼！$"

PokemonTower_5F_Text_TammyPostBattle::
    .string "我被控制了。$"

PokemonTower_5F_Text_RuthIntro::
    .string "你……应该……\n"
    .string "加入……我们……$"

PokemonTower_5F_Text_RuthDefeat::
    .string "真是一场恶梦！$"

PokemonTower_5F_Text_RuthPostBattle::
    .string "我有些失态了。$"

PokemonTower_5F_Text_KarinaIntro::
    .string "僵尸！$"

PokemonTower_5F_Text_KarinaDefeat::
    .string "哈？$"

PokemonTower_5F_Text_KarinaPostBattle::
    .string "我恢复了理智。$"

PokemonTower_5F_Text_JanaeIntro::
    .string "恩……\n"
    .string "啊……$"

PokemonTower_5F_Text_JanaeDefeat::
    .string "哇！$"

PokemonTower_5F_Text_JanaePostBattle::
    .string "尽管我在山上不断地修行\n"
    .string "却还是堕入了邪念……$"

PokemonTower_5F_Text_PurifiedZoneMonsFullyHealed::
    .string "进入了净化和被保护的区域。\p"
    .string "{PLAYER}的宝可梦\n"
    .string "全都恢复了体力。$"

