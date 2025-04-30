PacifidlogTown_House3_MapScripts::
	.byte 0

PacifidlogTown_House3_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED, PacifidlogTown_House3_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_HORSEA
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox PacifidlogTown_House3_Text_WillingToTradeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PacifidlogTown_House3_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, PacifidlogTown_House3_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, PacifidlogTown_House3_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou, MSGBOX_DEFAULT
	setflag FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED
	release
	end

PacifidlogTown_House3_EventScript_DeclineTrade::
	msgbox PacifidlogTown_House3_Text_NotDesperateOrAnything, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_TradeCompleted::
	msgbox PacifidlogTown_House3_Text_ReallyWantedToGetBagon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_Girl::
	msgbox PacifidlogTown_House3_Text_IsThatAPokedex, MSGBOX_NPC
	end

PacifidlogTown_House3_Text_WillingToTradeIt:
    .string "看看这个{STR_VAR_2}！\p是我昨天为庆祝自己的生日\n捉到的{STR_VAR_2}！\p啊，看来你想要它！\n毕竟，它是无可估价的！\p但是，你如果愿意用{STR_VAR_1}\n跟我换的话，我可以考虑。$"

PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou:
    .string "呀，这个是{STR_VAR_1}？\p虽然跟{STR_VAR_2}有点像，\n但它们还是有不同之处。\p谢谢！$"

PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon:
    .string "不不不，除了真正的{STR_VAR_1}，\n我什么都不换！$"

PacifidlogTown_House3_Text_NotDesperateOrAnything:
    .string "哦？你不想\n考虑一下吗？\p也好，我也不是急着\n想交换的。$"

PacifidlogTown_House3_Text_ReallyWantedToGetBagon:
    .string "我知道我也能自己\n去找一只，但是……\p我真的很想要一只\n其他训练家捕捉的宝贝龙……$"

PacifidlogTown_House3_Text_IsThatAPokedex:
    .string "那是宝可梦图鉴吗？\p你见过了很多不同的\n宝可梦了吗？\p我要是也能像你一样多好。$"

