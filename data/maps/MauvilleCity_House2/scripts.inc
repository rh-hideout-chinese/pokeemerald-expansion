MauvilleCity_House2_MapScripts::
	.byte 0

MauvilleCity_House2_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_COIN_CASE, MauvilleCity_House2_EventScript_ReceivedCoinCase
	msgbox MauvilleCity_House2_Text_BuyHarborMailAtSlateport, MSGBOX_DEFAULT
	checkitem ITEM_HARBOR_MAIL
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_House2_EventScript_AskToTradeForHarborMail
	release
	end

MauvilleCity_House2_EventScript_AskToTradeForHarborMail::
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_House2_Text_TradeHarborMailForCoinCase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_House2_EventScript_AcceptTrade
	goto_if_eq VAR_RESULT, NO, MauvilleCity_House2_EventScript_DeclineTrade
	end

MauvilleCity_House2_EventScript_AcceptTrade::
	msgbox MauvilleCity_House2_Text_IllTradeYouCoinCase, MSGBOX_DEFAULT
	giveitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	removeitem ITEM_HARBOR_MAIL
	setflag FLAG_RECEIVED_COIN_CASE
	goto MauvilleCity_House2_EventScript_ReceivedCoinCase
	end

MauvilleCity_House2_EventScript_ReceivedCoinCase::
	msgbox MauvilleCity_House2_Text_UseCoinCaseAtGameCorner, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_EventScript_DeclineTrade::
	msgbox MauvilleCity_House2_Text_ThatsDisappointing, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_Text_BuyHarborMailAtSlateport:
    .string "要是我也有自行车，骑车去\n凯那市买东西就更方便了，\p这样我就能去凯那市的\n宝可梦商业中心买港口信纸…$"

MauvilleCity_House2_Text_TradeHarborMailForCoinCase:
    .string "呀！你有港口信纸？\n愿意用它换个代币盒吗？$"

MauvilleCity_House2_Text_IllTradeYouCoinCase:
    .string "哈哈，太高兴了！\n好，我用代币盒跟你交换！$"

MauvilleCity_House2_Text_UseCoinCaseAtGameCorner:
    .string "你可以在游戏中心里\n使用代币盒。$"

MauvilleCity_House2_Text_ThatsDisappointing:
    .string "哎，真失望。\p要在游戏中心玩游戏\n必须有代币盒。$"

