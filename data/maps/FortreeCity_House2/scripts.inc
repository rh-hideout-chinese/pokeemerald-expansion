FortreeCity_House2_MapScripts::
	.byte 0

FortreeCity_House2_EventScript_HiddenPowerGiver::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_HIDDEN_POWER, FortreeCity_House2_EventScript_ExplainHiddenPower
	call_if_unset FLAG_MET_HIDDEN_POWER_GIVER, FortreeCity_House2_EventScript_Greeting
	msgbox FortreeCity_House2_Text_CoinInWhichHand, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 1, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_CorrectTryAgainWhichHand, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 1, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_CorrectTryAgainWhichHand2, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 0, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_YourHiddenPowerHasAwoken, MSGBOX_DEFAULT
	giveitem ITEM_TM_HIDDEN_POWER
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_HIDDEN_POWER
	msgbox FortreeCity_House2_Text_ExplainHiddenPower, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_Greeting::
	msgbox FortreeCity_House2_Text_HiddenPowersArousedByNature, MSGBOX_DEFAULT
	setflag FLAG_MET_HIDDEN_POWER_GIVER
	return

FortreeCity_House2_EventScript_ExplainHiddenPower::
	msgbox FortreeCity_House2_Text_ExplainHiddenPower, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_WrongGuess::
	msgbox FortreeCity_House2_Text_YouGuessedWrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_Text_HiddenPowersArousedByNature:
    .string "人类……宝可梦……\p他们隐蔽的潜能\n会被自然中的生活唤醒……$"

FortreeCity_House2_Text_CoinInWhichHand:
    .string "让我这老人看看\n你隐蔽的潜能是不是觉醒了……\p我手里有一枚硬币，\p告诉我，我是把它藏在了\n左手里呢，还有右手里？$"

FortreeCity_House2_Text_CorrectTryAgainWhichHand:
    .string "哎，没错，答对了！\p我们再试一次。\p我把硬币藏在哪儿？\n左手还是右手？$"

FortreeCity_House2_Text_CorrectTryAgainWhichHand2:
    .string "哎，没错，答对了！\p我们再试一次。\p我把硬币藏在哪儿？\n左手还是右手？$"

FortreeCity_House2_Text_YourHiddenPowerHasAwoken:
    .string "啊！完全正确！\n你的潜能觉醒了！\p来，这个给你，也唤醒\n你的宝可梦的潜能吧。$"

FortreeCity_House2_Text_ExplainHiddenPower:
    .string "觉醒力量是会随着使用\n它的宝可梦不同而改变的招式。$"

FortreeCity_House2_Text_YouGuessedWrong:
    .string "哎，真遗憾，\n你猜错了。$"

