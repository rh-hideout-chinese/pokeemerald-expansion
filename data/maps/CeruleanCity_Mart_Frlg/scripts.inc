CeruleanCity_Mart_Frlg_MapScripts::
	.byte 0

CeruleanCity_Mart_EventScript_Youngster::
	msgbox CeruleanCity_Mart_Text_RepelWorksOnWeakMons, MSGBOX_NPC
	end

CeruleanCity_Mart_EventScript_Woman::
	msgbox CeruleanCity_Mart_Text_DoYouKnowAboutRareCandy, MSGBOX_NPC
	end

CeruleanCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart CeruleanCity_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
CeruleanCity_Mart_Items::
	.2byte ITEM_POKE_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_NONE
	release
	end

CeruleanCity_Mart_Text_RepelWorksOnWeakMons::
    .string "除虫喷雾不仅使虫属性的无法接近，\n"
    .string "还会作用于弱小的宝可梦。\p"
    .string "把你最强的宝可梦放在\n"
    .string "宝可梦列表的最左边。\p"
    .string "如果你的第一只宝可梦很强。\n"
    .string "除虫喷雾的作用就会更明显。$"

CeruleanCity_Mart_Text_DoYouKnowAboutRareCandy::
    .string "你知道神奇糖果吗？\n"
    .string "在商店没有卖的。\p"
    .string "它能迅速的提高宝可梦的实力。$"

