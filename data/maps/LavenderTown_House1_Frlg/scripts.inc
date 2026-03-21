LavenderTown_House1_Frlg_MapScripts::
	.byte 0

LavenderTown_House1_EventScript_CooltrainerF::
	lock
	faceplayer
	goto_if_set FLAG_RESCUED_MR_FUJI, LavenderTown_House1_EventScript_CooltrainerFGhostGone
	msgbox LavenderTown_House1_Text_RocketsKilledCubonesMother
	release
	end

LavenderTown_House1_EventScript_CooltrainerFGhostGone::
	msgbox LavenderTown_House1_Text_GhostOfPokemonTowerIsGone
	release
	end

LavenderTown_House1_EventScript_Cubone::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CUBONE, CRY_MODE_NORMAL
	msgbox LavenderTown_House1_Text_Cubone
	waitmoncry
	release
	end

LavenderTown_House1_Text_Cubone::
    .string "卡拉卡拉：咔咕！$"

LavenderTown_House1_Text_RocketsKilledCubonesMother::
    .string "那恐怖的火箭队！\n"
    .string "绝不能饶恕他们！\p"
    .string "那可怜的卡拉卡拉的妈妈……\p"
    .string "在从火箭队手中逃跑时\n"
    .string "被杀了。$"

LavenderTown_House1_Text_GhostOfPokemonTowerIsGone::
    .string "宝可梦塔的幽灵走了！\p"
    .string "肯定有人安抚了它们不安的灵魂！$"

