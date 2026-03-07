PokemonTower_3F_Frlg_MapScripts::
	.byte 0

PokemonTower_3F_EventScript_Patricia::
	trainerbattle_single TRAINER_CHANNELER_PATRICIA, PokemonTower_3F_Text_PatriciaIntro, PokemonTower_3F_Text_PatriciaDefeat
	msgbox PokemonTower_3F_Text_PatriciaPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_3F_EventScript_Carly::
	trainerbattle_single TRAINER_CHANNELER_CARLY, PokemonTower_3F_Text_CarlyIntro, PokemonTower_3F_Text_CarlyDefeat
	msgbox PokemonTower_3F_Text_CarlyPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_3F_EventScript_Hope::
	trainerbattle_single TRAINER_CHANNELER_HOPE, PokemonTower_3F_Text_HopeIntro, PokemonTower_3F_Text_HopeDefeat
	msgbox PokemonTower_3F_Text_HopePostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_3F_Text_HopeIntro::
    .string "呃……哇……\n"
    .string "呼呼……嘎嘎……$"

PokemonTower_3F_Text_HopeDefeat::
    .string "哗！\n"
    .string "得救了！$"

PokemonTower_3F_Text_HopePostBattle::
    .string "用西尔佛观测镜\n"
    .string "可以看清鬼的真面目！$"

PokemonTower_3F_Text_CarlyIntro::
    .string "呵呵呵……\n"
    .string "咔哇哇哇哇哈！$"

PokemonTower_3F_Text_CarlyDefeat::
    .string "嗯？\n"
    .string "我在做什么？$"

PokemonTower_3F_Text_CarlyPostBattle::
    .string "抱歉！\n"
    .string "我刚才有些失态！$"

PokemonTower_3F_Text_PatriciaIntro::
    .string "滚！\n"
    .string "邪恶的幽灵！$"

PokemonTower_3F_Text_PatriciaDefeat::
    .string "呃！\n"
    .string "幽灵终于消失了！！$"

PokemonTower_3F_Text_PatriciaPostBattle::
    .string "上面的人……\n"
    .string "他们一定被鬼迷心窍了。$"

