PokemonTower_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PokemonTower_1F_OnTransition
	.byte 0

PokemonTower_1F_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_POKEMON_TOWER_1F
	end

PokemonTower_1F_EventScript_Channeler::
	msgbox PokemonTower_1F_Text_SenseSpiritsUpToMischief, MSGBOX_NPC
	end

PokemonTower_1F_EventScript_Woman1::
	msgbox PokemonTower_1F_Text_GrowlitheWhyDidYouDie, MSGBOX_NPC
	end

PokemonTower_1F_EventScript_BaldingMan::
	msgbox PokemonTower_1F_Text_CameToPrayForDepartedClefairy, MSGBOX_NPC
	end

PokemonTower_1F_EventScript_Woman2::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, PokemonTower_1F_EventScript_Woman2MalePlayer
	msgbox PokemonTower_1F_Text_ComeToPayRespectsGirl
	release
	end

PokemonTower_1F_EventScript_Woman2MalePlayer::
	msgbox PokemonTower_1F_Text_ComeToPayRespectsSon
	release
	end

PokemonTower_1F_EventScript_WorkerF::
	msgbox PokemonTower_1F_Text_ErectedInMemoryOfDeadMons, MSGBOX_NPC
	end

PokemonTower_1F_Text_ErectedInMemoryOfDeadMons::
    .string "宝可梦塔是为了\n"
    .string "纪念死去的宝可梦而建立的。$"

PokemonTower_1F_Text_ComeToPayRespectsSon::
    .string "你是来这里祈福的么？\p"
    .string "孩子，\n"
    .string "保佑你那颗爱着宝可梦的心。$"

PokemonTower_1F_Text_ComeToPayRespectsGirl::
    .string "你是来这里祈福的么？\p"
    .string "孩子，\n"
    .string "保佑你那颗爱着宝可梦的心。$"

PokemonTower_1F_Text_CameToPrayForDepartedClefairy::
    .string "我来为我心爱的皮皮\n"
    .string "的灵魂送别！\p"
    .string "呜！\n"
    .string "我止不住眼泪…$"

PokemonTower_1F_Text_GrowlitheWhyDidYouDie::
    .string "我的卡蒂狗…\n"
    .string "你为什么死了？$"

PokemonTower_1F_Text_SenseSpiritsUpToMischief::
    .string "我是通灵师。\p"
    .string "有些灵魂喜欢搞恶作剧。\n"
    .string "在塔的高层，我能感觉到它们。$"

