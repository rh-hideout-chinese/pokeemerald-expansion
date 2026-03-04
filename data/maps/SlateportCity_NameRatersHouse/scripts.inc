SlateportCity_NameRatersHouse_MapScripts::
	.byte 0

SlateportCity_NameRatersHouse_EventScript_NameRater::
	lock
	faceplayer
	msgbox SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate
	goto_if_eq VAR_RESULT, NO, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate::
	msgbox SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname, MSGBOX_DEFAULT
	chooseboxmon
	waitstate
	goto_if_ne VAR_0x8004, PARTY_NOTHING_CHOSEN, SlateportCity_NameRatersHouse_EventScript_RateMonNickname
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_DeclineNameRate::
	msgbox SlateportCity_NameRatersHouse_Text_DoVisitAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_RateMonNickname::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, SlateportCity_NameRatersHouse_EventScript_CantRateEgg
	special BufferMonNickname
	special IsMonOTIDNotPlayers
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	specialvar VAR_RESULT, MonOTNameNotPlayer
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	msgbox SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_NameRatersHouse_EventScript_ChangeNickname
	goto_if_eq VAR_RESULT, NO, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_CantRateEgg::
	msgbox SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnEgg, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT::
	msgbox SlateportCity_NameRatersHouse_Text_MagnificentName, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_ChangeNickname::
	msgbox SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe, MSGBOX_DEFAULT
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_RESULT, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_NewNameDifferent
	msgbox SlateportCity_NameRatersHouse_Text_NameNoDifferentYetSuperior, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_NewNameDifferent::
	msgbox SlateportCity_NameRatersHouse_Text_MonShallBeKnownAsName, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname:
    .string "看一看瞧一瞧啊！\n老夫乃姓名鉴定师。\l也就是看名字算命的。\p来，让老夫来算算\n你宝可梦的昵称吧。$"

SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname:
    .string "你想算哪只\n宝可梦的昵称啊？$"

SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne:
    .string "唔嗯……\n{STR_VAR_1}啊……\p这个昵称很有你的风范，\n取得不错嘛。\p不过～\n要不要老夫帮你\l取个更好的名字啊？$"

SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe:
    .string "是吗，那……\n取个什么昵称好呢？$"

SlateportCity_NameRatersHouse_Text_MonShallBeKnownAsName:
    .string "好！从今天起\n这只宝可梦就叫{STR_VAR_1}啦！\p比之前的名字好听太多了，\n太好了太好了！$"

SlateportCity_NameRatersHouse_Text_DoVisitAgain:
    .string "这样啊。\n知道了，你有空再来吧。$"

SlateportCity_NameRatersHouse_Text_NameNoDifferentYetSuperior:
    .string "好！从今天起\n这只宝可梦就叫{STR_VAR_1}啦！\p虽然听起来和之前的差不多，\n但这个更棒哦！\l太好了太好了！$"

SlateportCity_NameRatersHouse_Text_MagnificentName:
    .string "唔嗯……\n{STR_VAR_1}啊！\p这昵称好听到\n无可挑剔！\p今后你也要\n好好爱护{STR_VAR_1}哦！$"

SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnEgg:
    .string "喂喂……\n这不是颗蛋吗！$"

