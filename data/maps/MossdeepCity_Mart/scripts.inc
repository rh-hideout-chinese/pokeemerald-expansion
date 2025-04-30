MossdeepCity_Mart_MapScripts::
	.byte 0

MossdeepCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MossdeepCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MossdeepCity_Mart_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	pokemartlistend

MossdeepCity_Mart_EventScript_Woman::
	msgbox MossdeepCity_Mart_Text_ReviveIsFantastic, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Boy::
	msgbox MossdeepCity_Mart_Text_MaxRepelLastsLongest, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Sailor::
	msgbox MossdeepCity_Mart_Text_NetAndDiveBallsRare, MSGBOX_NPC
	end

MossdeepCity_Mart_Text_ReviveIsFantastic:
    .string "活力碎片太神奇了！\p把它给昏厥的宝可梦的话，\n宝可梦就会醒来。\p但要小心，活力碎片并不能恢复\n招式被用掉的PP。$"

MossdeepCity_Mart_Text_MaxRepelLastsLongest:
    .string "黄金喷雾能赶走所有弱小的宝可梦。\p所有的喷雾器之中，\n它的持续时间最久。$"

MossdeepCity_Mart_Text_NetAndDiveBallsRare:
    .string "捕网球和潜水球是\n只有绿岭市才卖的稀有精灵球。\p捕网球捉虫属性和\n水属性宝可梦很有效，\p潜水球则容易捉\n海底的宝可梦。$"

