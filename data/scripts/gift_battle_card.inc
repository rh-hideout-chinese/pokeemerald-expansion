MysteryGiftScript_BattleCard::
	setvaddress MysteryGiftScript_BattleCard
	vgoto_if_set FLAG_MYSTERY_GIFT_DONE, MysteryGiftScript_BattleCardInfo
	setorcopyvar VAR_RESULT, GET_CARD_BATTLES_WON
	specialvar VAR_0x8008, GetMysteryGiftCardStat
	vgoto_if_ne VAR_0x8008, REQUIRED_CARD_BATTLES, MysteryGiftScript_BattleCardInfo
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard_WonPrize
	waitmessage
	waitbuttonpress
	giveitem ITEM_POTION
	release
	setflag FLAG_MYSTERY_GIFT_DONE
	end

MysteryGiftScript_BattleCardInfo:
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftBattleCountCard:
	.string "感谢使用\n"
	.string "神秘礼物系统。\p"
	.string "你的战斗积分卡保留着\n"
	.string "你和其他拥有相同卡的\l"
	.string "训练家战斗录像。\p"
	.string "寻找并和拥有与你有相同卡的训练家\n"
	.string "进行战斗吧。\p"
	.string "你可以检查最终排名\n"
	.string "通过阅读新闻。\p"
	.string "请一定要试试看！$"

sText_MysteryGiftBattleCountCard_WonPrize:
	.string "感谢使用\n"
	.string "神秘礼物系统。\p"
	.string "恭喜！\p"
	.string "你获得了赢取\n"
	.string "3场战斗的奖励！\p"
	.string "希望你再接再厉\n"
	.string "进行更多战斗。$"
