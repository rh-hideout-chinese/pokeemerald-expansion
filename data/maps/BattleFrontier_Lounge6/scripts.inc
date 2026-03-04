BattleFrontier_Lounge6_MapScripts::
	.byte 0

BattleFrontier_Lounge6_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_BATTLE_FRONTIER_TRADE_DONE, BattleFrontier_Lounge6_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_MEOWTH, BattleFrontier_Lounge6_Text_WouldYouLikeToTrade, BattleFrontier_Lounge6_EventScript_DeclineTrade, BattleFrontier_Lounge6_EventScript_NotRequestedMon, BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt
	setflag FLAG_BATTLE_FRONTIER_TRADE_DONE
	release
	end

BattleFrontier_Lounge6_EventScript_DeclineTrade::
	msgbox BattleFrontier_Lounge6_Text_WellThatsFineToo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_TradeCompleted::
	msgbox BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_Text_WouldYouLikeToTrade:
    .string "我的宝可梦是{STR_VAR_2}，\n你知道它吗？\l它很可爱，很讨人喜欢。\p我可是很自豪有这么一只\n能与别人交换！\p你想用{STR_VAR_1}\n换我的{STR_VAR_2}吗？$"

BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt:
    .string "哇，太可爱了！\n谢谢！\l我保证会好好照顾它的！\p啊，你也要好好照顾\n我的{STR_VAR_2}哦！$"

BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon:
    .string "啊，抱歉！\n我只想换一只\l{STR_VAR_1}。$"

BattleFrontier_Lounge6_Text_WellThatsFineToo:
    .string "哎，你不想换吗？\n唉，那就算了。\l下回再说吧。$"

BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined:
    .string "嘻嘻！\n向尾喵比我想象中可爱多了！\l太高兴了！$"
