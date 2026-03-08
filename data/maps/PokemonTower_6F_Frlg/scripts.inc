PokemonTower_6F_Frlg_MapScripts::
	.byte 0

PokemonTower_6F_EventScript_MarowakGhost::
	lockall
	textcolor NPC_TEXT_COLOR_MON
	msgbox PokemonTower_6F_Text_BeGoneIntruders
	setwildbattle SPECIES_MAROWAK, 30
	special StartMarowakBattle
	waitstate
	goto_if_eq VAR_RESULT, FALSE, PokemonTower_6F_EventScript_DefeatedMarowakGhost  @ VAR_RESULT set by CB2_EndMarowakBattle
	applymovement LOCALID_PLAYER, PokemonTower_6F_Movement_ForcePlayerUp
	waitmovement 0
	releaseall
	end

PokemonTower_6F_EventScript_DefeatedMarowakGhost::
	message PokemonTower_6F_Text_GhostWasCubonesMother
	waitmessage
	waitse
	playmoncry SPECIES_MAROWAK, CRY_MODE_NORMAL
	waitbuttonpress
	waitmoncry
	msgbox PokemonTower_6F_Text_MothersSpiritWasCalmed
	setvar VAR_MAP_SCENE_POKEMON_TOWER_6F, 1
	releaseall
	end

PokemonTower_6F_Movement_ForcePlayerUp::
	walk_up
	step_end

PokemonTower_6F_EventScript_Angelica::
	trainerbattle_single TRAINER_CHANNELER_ANGELICA, PokemonTower_6F_Text_AngelicaIntro, PokemonTower_6F_Text_AngelicaDefeat
	msgbox PokemonTower_6F_Text_AngelicaPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_6F_EventScript_Emilia::
	trainerbattle_single TRAINER_CHANNELER_EMILIA, PokemonTower_6F_Text_EmiliaIntro, PokemonTower_6F_Text_EmiliaDefeat
	msgbox PokemonTower_6F_Text_EmiliaPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_6F_EventScript_Jennifer::
	trainerbattle_single TRAINER_CHANNELER_JENNIFER, PokemonTower_6F_Text_JenniferIntro, PokemonTower_6F_Text_JenniferDefeat
	msgbox PokemonTower_6F_Text_JenniferPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_6F_Text_AngelicaIntro::
    .string "给……我……\n"
    .string "血……$"

PokemonTower_6F_Text_AngelicaDefeat::
    .string "咕哇！$"

PokemonTower_6F_Text_AngelicaPostBattle::
    .string "我感到乏力而虚弱……$"

PokemonTower_6F_Text_EmiliaIntro::
    .string "呃……\n"
    .string "嗬啊！$"

PokemonTower_6F_Text_EmiliaDefeat::
    .string "有东西掉出来了！$"

PokemonTower_6F_Text_EmiliaPostBattle::
    .string "我头发才没有掉出来！\n"
    .string "那是一个邪恶的幽灵！$"

PokemonTower_6F_Text_JenniferIntro::
    .string "咳……咳……咳……\n"
    .string "咳……咳……咳！$"

PokemonTower_6F_Text_JenniferDefeat::
    .string "咳！$"

PokemonTower_6F_Text_JenniferPostBattle::
    .string "这儿发生了什么事？$"

PokemonTower_6F_Text_BeGoneIntruders::
    .string "离开这里……\n"
    .string "入侵者……$"

PokemonTower_6F_Text_GhostWasCubonesMother::
    .string "这个幽灵是卡拉卡拉母亲\n"
    .string "不能安息的灵魂！$"

PokemonTower_6F_Text_MothersSpiritWasCalmed::
    .string "母亲的灵魂平静了下来。\p"
    .string "它转世投胎去了……$"

