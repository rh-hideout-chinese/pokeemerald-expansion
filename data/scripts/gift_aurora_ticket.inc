MysteryGiftScript_AuroraTicket::
	setvaddress MysteryGiftScript_AuroraTicket
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_AURORA_TICKET, AuroraTicket_Obtained
	vgoto_if_set FLAG_BATTLED_DEOXYS, AuroraTicket_Obtained
	checkitem ITEM_AURORA_TICKET
	vgoto_if_eq VAR_RESULT, TRUE, AuroraTicket_Obtained
	vmessage sText_AuroraTicketForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_AURORA_TICKET
	vgoto_if_eq VAR_RESULT, FALSE, AuroraTicket_NoBagSpace
	giveitem ITEM_AURORA_TICKET
	setflag FLAG_ENABLE_SHIP_BIRTH_ISLAND
	setflag FLAG_RECEIVED_AURORA_TICKET
	vmessage sText_AuroraTicketUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

AuroraTicket_NoBagSpace:
	vmessage sText_AuroraTicketBagFull
	waitmessage
	waitbuttonpress
	release
	end

AuroraTicket_Obtained:
	vmessage sText_AuroraTicketThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_AuroraTicketForYou:
	.string "感谢使用\n"
	.string "神秘礼物系统。\p"
	.string "你一定是{PLAYER}。\n"
	.string "这是给你的票。$"

sText_AuroraTicketUseAtPort:
	.string "看起来是在\n"
	.string "水静市港口使用的。\p"
	.string "为什么不试一下\n"
	.string "看看它到底怎么用？$"

sText_AuroraTicketThankYou:
	.string "感谢使用\n"
	.string "神秘礼物系统。$"

sText_AuroraTicketBagFull:
	.string "哦，抱歉，{PLAYER}。\n"
	.string "你的包包里放重要物品的口袋满了。\p"
	.string "请存一些东西到电脑\n"
	.string "然后回来拿这个吧。$"
