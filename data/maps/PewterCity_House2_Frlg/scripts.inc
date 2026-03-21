PewterCity_House2_Frlg_MapScripts::
	.byte 0

PewterCity_House2_EventScript_OldMan::
	msgbox PewterCity_House2_Text_MonsLearnTechniquesAsTheyGrow, MSGBOX_NPC
	end

PewterCity_House2_EventScript_LittleBoy::
	msgbox PewterCity_House2_Text_MonsEasierCatchIfStatused, MSGBOX_NPC
	end

PewterCity_House2_Text_MonsLearnTechniquesAsTheyGrow::
    .string "宝可梦在成长过程中\n"
    .string "可以学到新的技能。\p"
    .string "但是有一些必须要有人教\n"
    .string "它们才能学会。$"

PewterCity_House2_Text_MonsEasierCatchIfStatused::
    .string "当一只宝可梦进入异常状态时\n"
    .string "会容易收服一些。\p"
    .string "睡眠，中毒，烧伤，或者麻痹……\n"
    .string "这些都能对其造成影响。\p"
    .string "但是收服一只宝可梦\n"
    .string "从来都不是件容易的事！$"

