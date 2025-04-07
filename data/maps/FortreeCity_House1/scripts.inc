FortreeCity_House1_MapScripts::
	.byte 0

FortreeCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_FORTREE_NPC_TRADE_COMPLETED, FortreeCity_House1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_PLUSLE
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox FortreeCity_House1_Text_YouWillTradeWontYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FortreeCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FortreeCity_House1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, FortreeCity_House1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox FortreeCity_House1_Text_MonYouTakeCare, MSGBOX_DEFAULT
	setflag FLAG_FORTREE_NPC_TRADE_COMPLETED
	release
	end

FortreeCity_House1_EventScript_DeclineTrade::
	msgbox FortreeCity_House1_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox FortreeCity_House1_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_TradeCompleted::
	msgbox FortreeCity_House1_Text_GoingToMakeVolbeatStrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_ExpertF::
	msgbox FortreeCity_House1_Text_TradingMemoriesWithOthers, MSGBOX_NPC
	end

FortreeCity_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox FortreeCity_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House1_Text_YouWillTradeWontYou:
    .string "唔啊啊啊！我想要！\n我想要只{STR_VAR_1}！\l我会拼尽全力找到它的！\p…呃…被你听到了吗？\n被你听到了我那发自内心的呼喊？\p既然听见了，就用\n{STR_VAR_1}来换我的{STR_VAR_2}吧，\l好吗？$"

FortreeCity_House1_Text_MonYouTakeCare:
    .string "哦，耶，对！\p欢迎，{STR_VAR_1}！\n你要照顾好{STR_VAR_2}！$"

FortreeCity_House1_Text_ThisIsntAMon:
    .string "呃，不，我想\n这不是{STR_VAR_1}。$"

FortreeCity_House1_Text_YouWontTradeMe:
    .string "不？你不跟我换？\n即使你看到了我的真心也不肯换？$"

FortreeCity_House1_Text_GoingToMakeVolbeatStrong:
    .string "从现在开始，我要把甜甜萤\n养得壮壮的！\p你也要善待正电拍拍啊！$"

FortreeCity_House1_Text_TradingMemoriesWithOthers:
    .string "和别人交换宝可梦…\p就像跟别人交换\n自己的记忆一样。$"

FortreeCity_House1_Text_Zigzagoon:
    .string "蛇纹熊：米西米西滴？$"

