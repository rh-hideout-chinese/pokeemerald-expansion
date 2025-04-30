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
	special ChoosePartyMon
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
    .string "你好，你好！\n我是姓名鉴定师！\p我可以为你鉴定\n宝可梦的名字的好坏。$"

SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname:
    .string "要我看看哪只\n宝可梦的名字？$"

SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne:
    .string "唔……{STR_VAR_1}是吗？\n你给它起了个好名字，\p但是，我能给它起个\n更好的名字，怎么样？$"

SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe:
    .string "啊，好，那么，\n该叫什么呢？$"

SlateportCity_NameRatersHouse_Text_MonShallBeKnownAsName:
    .string "好了！现在开始，这只宝可梦\n就叫{STR_VAR_1}了！\p这个名字比以前更好！\n你真幸运！$"

SlateportCity_NameRatersHouse_Text_DoVisitAgain:
    .string "知道了。\n欢迎再来。$"

SlateportCity_NameRatersHouse_Text_NameNoDifferentYetSuperior:
    .string "好了！现在开始，这只宝可梦\n就叫{STR_VAR_1}了！\p虽然跟以前没什么不同，\n但这是个绝佳的名字！\p你真幸运！$"

SlateportCity_NameRatersHouse_Text_MagnificentName:
    .string "唔……是{STR_VAR_1}！\p绝妙的名字！\n没什么可以修正的地方！\p你一定要好好珍惜\n你的{STR_VAR_1}。$"

SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnEgg:
    .string "哎呀哎呀，\n这只是个蛋而已！$"

