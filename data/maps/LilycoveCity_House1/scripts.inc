LilycoveCity_House1_MapScripts::
	.byte 0

LilycoveCity_House1_EventScript_ExpertM::
	msgbox LilycoveCity_House1_Text_PokemonPartnersNotTools, MSGBOX_NPC
	end

LilycoveCity_House1_EventScript_Kecleon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KECLEON, CRY_MODE_NORMAL
	msgbox LilycoveCity_House1_Text_Kecleon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LilycoveCity_House1_Text_PokemonPartnersNotTools:
    .string "宝可梦是人们的伙伴，\n而不是工具。\p可惜的是，有些人\n并不明白这点…$"

LilycoveCity_House1_Text_Kecleon:
    .string "变隐龙：艾露露？$"

