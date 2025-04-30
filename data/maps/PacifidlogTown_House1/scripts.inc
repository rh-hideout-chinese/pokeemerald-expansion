PacifidlogTown_House1_MapScripts::
	.byte 0

PacifidlogTown_House1_EventScript_Man::
	msgbox PacifidlogTown_House1_Text_RegiStory, MSGBOX_NPC
	end

PacifidlogTown_House1_EventScript_Woman::
	msgbox PacifidlogTown_House1_Text_SixDotsOpenThreeDoors, MSGBOX_NPC
	end

PacifidlogTown_House1_Text_RegiStory:
    .string "在丰缘地区有\n三只宝可梦，分别代表\l岩石、冰雪、钢铁的力量，\p据说它们都躲藏在\n某些山洞的深处。\p这是我孩提时\n听过的传说。$"

PacifidlogTown_House1_Text_SixDotsOpenThreeDoors:
    .string "“六个点打开三扇门”。\p爷爷经常这么说，\n但我不知道是什么意思。$"

