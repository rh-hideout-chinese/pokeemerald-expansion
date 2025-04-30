DewfordTown_House1_MapScripts::
	.byte 0

DewfordTown_House1_EventScript_Man::
	msgbox DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Woman::
	msgbox DewfordTown_House1_Text_LifeGoesSlowlyOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox DewfordTown_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland:
    .string "住在这样的小岛上，\n与家人、宝可梦和睦共处，\l多么美妙！$"

DewfordTown_House1_Text_LifeGoesSlowlyOnIsland:
    .string "我跟丈夫结婚后就离开了\n凯那市的港口。\p在小岛上的时光过得很缓慢，\n但被美丽的大海环绕着——\l感觉真的很幸福。$"

DewfordTown_House1_Text_Zigzagoon:
    .string "蛇纹熊：咕咕！$"

