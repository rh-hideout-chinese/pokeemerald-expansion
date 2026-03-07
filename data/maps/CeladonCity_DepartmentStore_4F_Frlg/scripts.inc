CeladonCity_DepartmentStore_4F_Frlg_MapScripts::
	.byte 0

CeladonCity_DepartmentStore_4F_EventScript_Man::
	msgbox CeladonCity_DepartmentStore_4F_Text_GettingPokeDollAsPresent, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_4F_EventScript_Youngster::
	msgbox CeladonCity_DepartmentStore_4F_Text_CanRunAwayWithPokeDoll, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_4F_EventScript_FloorSign::
	msgbox CeladonCity_DepartmentStore_4F_Text_FloorSign, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_4F_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart CeladonCity_DepartmentStore_4F_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
CeladonCity_DepartmentStore_4F_Items::
	.2byte ITEM_POKE_DOLL
	.2byte ITEM_RETRO_MAIL
	.2byte ITEM_FIRE_STONE
	.2byte ITEM_THUNDER_STONE
	.2byte ITEM_WATER_STONE
	.2byte ITEM_LEAF_STONE
	.2byte ITEM_NONE
	release
	end

CeladonCity_DepartmentStore_4F_Text_GettingPokeDollAsPresent::
	.string "我在为我女朋友挑礼物。\p"
	.string "我觉得皮皮玩偶不错。\n"
	.string "这东西很流行。$"

CeladonCity_DepartmentStore_4F_Text_CanRunAwayWithPokeDoll::
    .string "告诉你个有用的信息。\p"
    .string "如果野生的宝可梦出现，你能\n"
    .string "用皮皮玩偶转移它的注意力。\p"
    .string "你就能趁机逃离和它的战斗了。$"

CeladonCity_DepartmentStore_4F_Text_FloorSign::
	.string "请尽情挑选礼物！\n"
	.string "四楼：神秘的礼物\p"
	.string "进化专场！\n"
	.string "进化石特价热卖中！$"
