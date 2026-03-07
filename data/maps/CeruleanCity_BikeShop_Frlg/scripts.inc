CeruleanCity_BikeShop_Frlg_MapScripts::
	.byte 0

CeruleanCity_BikeShop_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BICYCLE, CeruleanCity_BikeShop_EventScript_AlreadyGotBicycle
	goto_if_set FLAG_GOT_BIKE_VOUCHER, CeruleanCity_BikeShop_EventScript_ExchangeBikeVoucher
	showmoneybox 0, 0
	message CeruleanCity_BikeShop_Text_WelcomeToBikeShop
	waitmessage
	multichoice 11, 0, MULTI_BIKE_SHOP, FALSE
	hidemoneybox
	showmoneybox 0, 0
	switch VAR_RESULT
	case 0, CeruleanCity_BikeShop_EventScript_TryPurchaseBicycle
	case 1, CeruleanCity_BikeShop_EventScript_ClerkGoodbye
	case 127, CeruleanCity_BikeShop_EventScript_ClerkGoodbye
	end

@ The Bicycle price / players money is never actually checked
CeruleanCity_BikeShop_EventScript_TryPurchaseBicycle::
	msgbox CeruleanCity_BikeShop_Text_SorryYouCantAffordIt
	goto CeruleanCity_BikeShop_EventScript_ClerkGoodbye
	end

CeruleanCity_BikeShop_EventScript_ClerkGoodbye::
	msgbox CeruleanCity_BikeShop_Text_ThankYouComeAgain
	hidemoneybox
	release
	end

CeruleanCity_BikeShop_EventScript_ExchangeBikeVoucher::
	msgbox CeruleanCity_BikeShop_Text_OhBikeVoucherHereYouGo
	msgreceiveditem CeruleanCity_BikeShop_Text_ExchangedVoucherForBicycle, ITEM_BICYCLE, 1, MUS_RG_OBTAIN_KEY_ITEM
	setflag FLAG_GOT_BICYCLE
	additem ITEM_BICYCLE
	removeitem ITEM_BIKE_VOUCHER
	msgbox CeruleanCity_BikeShop_Text_ThankYouComeAgain
	release
	end

CeruleanCity_BikeShop_EventScript_AlreadyGotBicycle::
	msgbox CeruleanCity_BikeShop_Text_HowDoYouLikeNewBicycle
	release
	end

@ Unused
CeruleanCity_BikeShop_EventScript_NoRoomForBicycle::
	msgbox CeruleanCity_BikeShop_Text_MakeRoomForBicycle
	release
	end

CeruleanCity_BikeShop_EventScript_Woman::
	msgbox CeruleanCity_BikeShop_Text_CityBikeGoodEnoughForMe, MSGBOX_NPC
	end

CeruleanCity_BikeShop_EventScript_Youngster::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BICYCLE, CeruleanCity_BikeShop_EventScript_YoungsterHaveBike
	msgbox CeruleanCity_BikeShop_Text_BikesCoolButExpensive
	release
	end

CeruleanCity_BikeShop_EventScript_YoungsterHaveBike::
	msgbox CeruleanCity_BikeShop_Text_WowYourBikeIsCool
	release
	end

CeruleanCity_BikeShop_EventScript_Bicycle::
	msgbox CeruleanCity_BikeShop_Text_ShinyNewBicycle, MSGBOX_SIGN
	end

CeruleanCity_BikeShop_Text_WelcomeToBikeShop::
    .string "嗨！\n"
    .string "欢迎来到我们的自行车行。\p"
    .string "我们已经为你挑选了这个自行车！$"

CeruleanCity_BikeShop_Text_SorryYouCantAffordIt::
    .string "对不起！\n"
    .string "你付不起这个钱啊！$"

CeruleanCity_BikeShop_Text_OhBikeVoucherHereYouGo::
    .string "哦，那是……\p"
    .string "一张自行车兑换券！\p"
    .string "好的！\n"
    .string "给你！$"

CeruleanCity_BikeShop_Text_ExchangedVoucherForBicycle::
    .string "{PLAYER}用自行车兑换券\n"
    .string "兑换了一辆自行车。$"

CeruleanCity_BikeShop_Text_ThankYouComeAgain::
    .string "谢谢！\n"
    .string "欢迎下次光临！$"

CeruleanCity_BikeShop_Text_HowDoYouLikeNewBicycle::
    .string "你喜欢你的新自行车吗？\n"
    .string "你喜欢这样骑着它吗？\p"
    .string "你可以在单车路\n"
    .string "甚至在洞穴里骑着它！$"

CeruleanCity_BikeShop_Text_MakeRoomForBicycle::
    .string "你最好留出空间\n"
    .string "来装你的自行车！$"

CeruleanCity_BikeShop_Text_CityBikeGoodEnoughForMe::
    .string "一辆普通的城市自行车\n"
    .string "对我来说足够了。\p"
    .string "毕竟，你无法把一个购物篮\n"
    .string "挂在一辆山地车上。$"

CeruleanCity_BikeShop_Text_BikesCoolButExpensive::
    .string "这些自行车太酷了，\n"
    .string "但是它们都很贵！$"

CeruleanCity_BikeShop_Text_WowYourBikeIsCool::
    .string "哇。\n"
    .string "你的自行车真的很帅！$"

@ Unused
CeruleanCity_BikeShop_Text_GermanFoldableBicyleFinallyOnMarket::
	.string "ついに　はつばい！\p"
	.string "ドイツ　せい　さいこうきゅう\n"
	.string "おりたたみ　じてんしゃ！$"

CeruleanCity_BikeShop_Text_ShinyNewBicycle::
    .string "一辆闪亮的新自行车！$"

