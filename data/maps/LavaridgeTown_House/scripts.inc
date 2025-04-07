LavaridgeTown_House_MapScripts::
	.byte 0

LavaridgeTown_House_EventScript_OldMan::
	msgbox LavaridgeTown_House_Text_WifeWarmingEggInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_House_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox LavaridgeTown_House_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LavaridgeTown_House_Text_WifeWarmingEggInHotSprings:
    .string "我妻子告诉我，她在温泉里\n养了一只蛋。\p她在抚养家寄存了两只宝可梦，\n然后就发现了那个蛋！$"

LavaridgeTown_House_Text_Zigzagoon:
    .string "蛇纹熊：噗休！$"

