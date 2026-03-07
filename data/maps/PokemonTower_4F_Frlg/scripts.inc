PokemonTower_4F_Frlg_MapScripts::
	.byte 0

PokemonTower_4F_EventScript_Paula::
	trainerbattle_single TRAINER_CHANNELER_PAULA, PokemonTower_4F_Text_PaulaIntro, PokemonTower_4F_Text_PaulaDefeat
	msgbox PokemonTower_4F_Text_PaulaPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_4F_EventScript_Laurel::
	trainerbattle_single TRAINER_CHANNELER_LAUREL, PokemonTower_4F_Text_LaurelIntro, PokemonTower_4F_Text_LaurelDefeat
	msgbox PokemonTower_4F_Text_LaurelPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_4F_EventScript_Jody::
	trainerbattle_single TRAINER_CHANNELER_JODY, PokemonTower_4F_Text_JodyIntro, PokemonTower_4F_Text_JodyDefeat
	msgbox PokemonTower_4F_Text_JodyPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_4F_Text_PaulaIntro::
    .string "鬼！不！\n"
    .string "咔哇哇哇哇哈！$"

PokemonTower_4F_Text_PaulaDefeat::
    .string "鬼在哪？$"

PokemonTower_4F_Text_PaulaPostBattle::
    .string "我刚刚一定在做梦……$"

PokemonTower_4F_Text_LaurelIntro::
    .string "让我诅咒你吧！\n"
    .string "咔哇哇哇哇哈！$"

PokemonTower_4F_Text_LaurelDefeat::
    .string "什么！$"

PokemonTower_4F_Text_LaurelPostBattle::
    .string "我们不能确定幽灵\n"
    .string "的真面目……$"

PokemonTower_4F_Text_JodyIntro::
    .string "呼呼呼……\n"
    .string "不要打我！$"

PokemonTower_4F_Text_JodyDefeat::
    .string "嘿？\n"
    .string "谁？什么？$"

PokemonTower_4F_Text_JodyPostBattle::
    .string "让死去的宝可梦\n"
    .string "安息吧……$"

