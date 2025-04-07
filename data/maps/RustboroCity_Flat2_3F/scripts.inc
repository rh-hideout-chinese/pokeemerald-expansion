RustboroCity_Flat2_3F_MapScripts::
	.byte 0

RustboroCity_Flat2_3F_EventScript_DevonEmployee::
	msgbox RustboroCity_Flat2_3F_Text_PresidentCollectsRareStones, MSGBOX_NPC
	end

RustboroCity_Flat2_3F_EventScript_Woman::
	msgbox RustboroCity_Flat2_3F_Text_PresidentsSonAlsoCollectsRareStones, MSGBOX_NPC
	end

RustboroCity_Flat2_3F_Text_PresidentCollectsRareStones:
    .string "得文的董事长喜欢收集\n稀有的石头。$"

RustboroCity_Flat2_3F_Text_PresidentsSonAlsoCollectsRareStones:
    .string "我想董事长的儿子\n也喜欢收集稀有石头。$"

