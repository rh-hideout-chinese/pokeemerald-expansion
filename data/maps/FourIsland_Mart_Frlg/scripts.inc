FourIsland_Mart_Frlg_MapScripts::
	.byte 0

FourIsland_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FourIsland_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
FourIsland_Mart_Items::
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_MAX_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

FourIsland_Mart_EventScript_Camper::
	msgbox FourIsland_Mart_Text_IcefallCaveIsFrigid, MSGBOX_NPC
	end

FourIsland_Mart_Text_LoreleiGrewUpOnThisIsland::
    .string "在这座岛上\n"
    .string "有一个伟大的训练家在这里长大。\p"
    .string "我猜你已经知道她是谁了。\n"
    .string "没错，\n"
    .string "她就是四天王的科拿！\p"
    .string "当科拿还是一个小孩子的时候，\n"
    .string "我教过她宝可梦的战斗。$"

FourIsland_Mart_Text_IcefallCaveIsFrigid::
    .string "七岛大部分位于\n"
    .string "温带地区。\p"
    .string "但是\n"
    .string "还有一个例外。\p"
    .string "就是冻瀑洞窟\p"
    .string "由于那里栖息着的宝可梦的关系，\n"
    .string "那里的气候十分冰冷。$"

