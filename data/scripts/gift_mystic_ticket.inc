MysteryGiftScript_MysticTicket::
	setvaddress MysteryGiftScript_MysticTicket
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_MYSTIC_TICKET, MysticTicket_Obtained
	vgoto_if_set FLAG_CAUGHT_LUGIA, MysticTicket_Obtained
	vgoto_if_set FLAG_CAUGHT_HO_OH, MysticTicket_Obtained
	checkitem ITEM_MYSTIC_TICKET
	vgoto_if_eq VAR_RESULT, TRUE, MysticTicket_Obtained
	vmessage sText_MysticTicketForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_MYSTIC_TICKET
	vgoto_if_eq VAR_RESULT, FALSE, MysticTicket_NoBagSpace
	giveitem ITEM_MYSTIC_TICKET
	setflag FLAG_ENABLE_SHIP_NAVEL_ROCK
	setflag FLAG_RECEIVED_MYSTIC_TICKET
	vmessage sText_MysticTicketUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

MysticTicket_NoBagSpace:
	vmessage sText_MysticTicketBagFull
	waitmessage
	waitbuttonpress
	release
	end

MysticTicket_Obtained:
	vmessage sText_MysticTicketThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_MysticTicketForYou:
	.string "感谢使用\n"
	.string "神秘礼物系统。\p"
	.string "你一定是{PLAYER}。\n"
	.string "这是给你的票。$"

sText_MysticTicketUseAtPort:
	.string "看起来是在\n"
	.string "水静市港口使用的。\p"
	.string "为什么不试一下\n"
	.string "看看它到底怎么用？$"

sText_MysticTicketThankYou:
	.string "感谢使用\n"
	.string "神秘礼物系统。$"

sText_MysticTicketBagFull:
	.string "哦，抱歉，{PLAYER}。\n"
	.string "你的包包里放重要物品的口袋满了。\p"
	.string "请存一些东西到电脑\n"
	.string "然后回来拿这个吧。$"
