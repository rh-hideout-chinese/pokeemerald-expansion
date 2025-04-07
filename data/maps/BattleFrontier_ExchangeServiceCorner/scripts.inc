BattleFrontier_ExchangeServiceCorner_MapScripts::
	.byte 0

BattleFrontier_ExchangeServiceCorner_EventScript_ClerkWelcome::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize, MSGBOX_DEFAULT
	special ShowBattlePointsWindow
	return

BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ThankYouVisitWithPoints, MSGBOX_DEFAULT
	special CloseBattlePointsWindow
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize::
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_ExchangeServiceCorner_EventScript_TryGivePrize
	msgbox BattleFrontier_ExchangeServiceCorner_Text_DontHaveEnoughPoints, MSGBOX_DEFAULT
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_DECOR1_CLERK, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_DECOR2_CLERK, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_VITAMIN_CLERK, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	end

BattleFrontier_ExchangeServiceCorner_EventScript_TryGivePrize::
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_DECOR1_CLERK, BattleFrontier_ExchangeServiceCorner_EventScript_TryGiveDecor
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_DECOR2_CLERK, BattleFrontier_ExchangeServiceCorner_EventScript_TryGiveDecor
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryGiveItem
	end

BattleFrontier_ExchangeServiceCorner_EventScript_TryGiveDecor::
	checkdecorspace VAR_0x8009
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ExchangeServiceCorner_EventScript_NoRoomForDecor
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	adddecoration VAR_0x8009
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WellSendItToPC, MSGBOX_DEFAULT
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_DECOR1_CLERK, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	end

BattleFrontier_ExchangeServiceCorner_EventScript_NoRoomForDecor::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_PCIsFull, MSGBOX_DEFAULT
	special CloseBattlePointsWindow
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_TryGiveItem::
	checkitemspace VAR_0x8009
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ExchangeServiceCorner_EventScript_BagFull
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	additem VAR_0x8009
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox BattleFrontier_ExchangeServiceCorner_Text_HereIsYourPrize, MSGBOX_DEFAULT
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_VITAMIN_CLERK, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	end

BattleFrontier_ExchangeServiceCorner_EventScript_BagFull::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_DontHaveSpaceToHoldIt, MSGBOX_DEFAULT
	special CloseBattlePointsWindow
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_DecorClerk1::
	lock
	faceplayer
	setvar VAR_TEMP_2, EXCHANGE_CORNER_DECOR1_CLERK
	call BattleFrontier_ExchangeServiceCorner_EventScript_ClerkWelcome
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1::
	setvar VAR_0x8004, SCROLL_MULTI_BF_EXCHANGE_CORNER_DECOR_VENDOR_1
	special ShowFrontierExchangeCornerItemIconWindow
	special ShowScrollableMultichoice
	waitstate
	special CloseFrontierExchangeCornerItemIconWindow
	switch VAR_RESULT
	case 0, BattleFrontier_ExchangeServiceCorner_EventScript_KissPoster
	case 1, BattleFrontier_ExchangeServiceCorner_EventScript_KissCushion
	case 2, BattleFrontier_ExchangeServiceCorner_EventScript_SmoochumDoll
	case 3, BattleFrontier_ExchangeServiceCorner_EventScript_TogepiDoll
	case 4, BattleFrontier_ExchangeServiceCorner_EventScript_MeowthDoll
	case 5, BattleFrontier_ExchangeServiceCorner_EventScript_ClefairyDoll
	case 6, BattleFrontier_ExchangeServiceCorner_EventScript_DittoDoll
	case 7, BattleFrontier_ExchangeServiceCorner_EventScript_CyndaquilDoll
	case 8, BattleFrontier_ExchangeServiceCorner_EventScript_ChikoritaDoll
	case 9, BattleFrontier_ExchangeServiceCorner_EventScript_TotodileDoll
	case 10, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	case MULTI_B_PRESSED, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	end

BattleFrontier_ExchangeServiceCorner_EventScript_KissPoster::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmKissPoster, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 16
	setvar VAR_0x8009, DECOR_KISS_POSTER
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_KissCushion::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmKissCushion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 32
	setvar VAR_0x8009, DECOR_KISS_CUSHION
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_SmoochumDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmSmoochumDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 32
	setvar VAR_0x8009, DECOR_SMOOCHUM_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_TogepiDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmTogepiDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, DECOR_TOGEPI_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_MeowthDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmMeowthDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, DECOR_MEOWTH_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ClefairyDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmClefairyDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, DECOR_CLEFAIRY_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_DittoDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmDittoDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, DECOR_DITTO_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_CyndaquilDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmCyndaquilDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 80
	setvar VAR_0x8009, DECOR_CYNDAQUIL_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChikoritaDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmChikoritaDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 80
	setvar VAR_0x8009, DECOR_CHIKORITA_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_TotodileDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmTotodileDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 80
	setvar VAR_0x8009, DECOR_TOTODILE_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_DecorClerk2::
	lock
	faceplayer
	setvar VAR_TEMP_2, EXCHANGE_CORNER_DECOR2_CLERK
	call BattleFrontier_ExchangeServiceCorner_EventScript_ClerkWelcome
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2::
	setvar VAR_0x8004, SCROLL_MULTI_BF_EXCHANGE_CORNER_DECOR_VENDOR_2
	special ShowFrontierExchangeCornerItemIconWindow
	special ShowScrollableMultichoice
	waitstate
	special CloseFrontierExchangeCornerItemIconWindow
	switch VAR_RESULT
	case 0, BattleFrontier_ExchangeServiceCorner_EventScript_LaprasDoll
	case 1, BattleFrontier_ExchangeServiceCorner_EventScript_SnorlaxDoll
	case 2, BattleFrontier_ExchangeServiceCorner_EventScript_VenusaurDoll
	case 3, BattleFrontier_ExchangeServiceCorner_EventScript_CharizardDoll
	case 4, BattleFrontier_ExchangeServiceCorner_EventScript_BlastoiseDoll
	case 5, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	case MULTI_B_PRESSED, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	end

BattleFrontier_ExchangeServiceCorner_EventScript_LaprasDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmLaprasDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	setvar VAR_0x8008, 128
	setvar VAR_0x8009, DECOR_LAPRAS_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_SnorlaxDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmSnorlaxDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	setvar VAR_0x8008, 128
	setvar VAR_0x8009, DECOR_SNORLAX_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_VenusaurDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmVenusaurDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	setvar VAR_0x8008, 256
	setvar VAR_0x8009, DECOR_VENUSAUR_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_CharizardDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmCharizardDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	setvar VAR_0x8008, 256
	setvar VAR_0x8009, DECOR_CHARIZARD_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_BlastoiseDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmBlastoiseDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	setvar VAR_0x8008, 256
	setvar VAR_0x8009, DECOR_BLASTOISE_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_VitaminClerk::
	lock
	faceplayer
	setvar VAR_TEMP_2, EXCHANGE_CORNER_VITAMIN_CLERK
	call BattleFrontier_ExchangeServiceCorner_EventScript_ClerkWelcome
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin::
	setvar VAR_0x8004, SCROLL_MULTI_BF_EXCHANGE_CORNER_VITAMIN_VENDOR
	special ShowFrontierExchangeCornerItemIconWindow
	special ShowScrollableMultichoice
	waitstate
	special CloseFrontierExchangeCornerItemIconWindow
	switch VAR_RESULT
	case 0, BattleFrontier_ExchangeServiceCorner_EventScript_Protein
	case 1, BattleFrontier_ExchangeServiceCorner_EventScript_Calcium
	case 2, BattleFrontier_ExchangeServiceCorner_EventScript_Iron
	case 3, BattleFrontier_ExchangeServiceCorner_EventScript_Zinc
	case 4, BattleFrontier_ExchangeServiceCorner_EventScript_Carbos
	case 5, BattleFrontier_ExchangeServiceCorner_EventScript_HPUp
	case 6, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	case MULTI_B_PRESSED, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Protein::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmProtein, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, ITEM_PROTEIN
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Calcium::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmCalcium, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, ITEM_CALCIUM
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Iron::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmIron, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, ITEM_IRON
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Zinc::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmZinc, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, ITEM_ZINC
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Carbos::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmCarbos, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, ITEM_CARBOS
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_HPUp::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmHPUp, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, ITEM_HP_UP
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_HoldItemClerk::
	lock
	faceplayer
	setvar VAR_TEMP_2, EXCHANGE_CORNER_HOLD_ITEM_CLERK
	call BattleFrontier_ExchangeServiceCorner_EventScript_ClerkWelcome
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem::
	setvar VAR_0x8004, SCROLL_MULTI_BF_EXCHANGE_CORNER_HOLD_ITEM_VENDOR
	special ShowFrontierExchangeCornerItemIconWindow
	special ShowScrollableMultichoice
	waitstate
	special CloseFrontierExchangeCornerItemIconWindow
	switch VAR_RESULT
	case 0, BattleFrontier_ExchangeServiceCorner_EventScript_Leftovers
	case 1, BattleFrontier_ExchangeServiceCorner_EventScript_WhiteHerb
	case 2, BattleFrontier_ExchangeServiceCorner_EventScript_QuickClaw
	case 3, BattleFrontier_ExchangeServiceCorner_EventScript_MentalHerb
	case 4, BattleFrontier_ExchangeServiceCorner_EventScript_Brightpowder
	case 5, BattleFrontier_ExchangeServiceCorner_EventScript_ChoiceBand
	case 6, BattleFrontier_ExchangeServiceCorner_EventScript_KingsRock
	case 7, BattleFrontier_ExchangeServiceCorner_EventScript_FocusBand
	case 8, BattleFrontier_ExchangeServiceCorner_EventScript_ScopeLens
	case 9, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	case MULTI_B_PRESSED, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Leftovers::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmLeftovers, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, ITEM_LEFTOVERS
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_WhiteHerb::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmWhiteHerb, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, ITEM_WHITE_HERB
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_QuickClaw::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmQuickClaw, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, ITEM_QUICK_CLAW
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_MentalHerb::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmMentalHerb, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, ITEM_MENTAL_HERB
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Brightpowder::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmBrightpowder, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 64
	setvar VAR_0x8009, ITEM_BRIGHT_POWDER
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChoiceBand::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmChoiceBand, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 64
	setvar VAR_0x8009, ITEM_CHOICE_BAND
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_KingsRock::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmKingsRock, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 64
	setvar VAR_0x8009, ITEM_KINGS_ROCK
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_FocusBand::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmFocusBand, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 64
	setvar VAR_0x8009, ITEM_FOCUS_BAND
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ScopeLens::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmScopeLens, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 64
	setvar VAR_0x8009, ITEM_SCOPE_LENS
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Man::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_GoGetYourOwnDoll, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Sailor::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ItemsWillGetMonTougher, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_EventScript_PokefanF::
	lock
	msgbox BattleFrontier_ExchangeServiceCorner_Text_GetYouAnythingYouWant, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_RichBoy::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WishIHadAllDolls, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Girl::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_MoreBattlePointsForRecord, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize::
    .string "你好，这里是交换服务\n中心。\p我们用可爱的奖品同你收集到的\n对战点数进行交换。\p请在列表上选择一个奖品。$"

@ Unused
BattleFrontier_ExchangeServiceCorner_Text_PleaseChoosePrize::
    .string "请选择一个奖品。$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmKissPoster::
    .string "你选择了亲吻的海报。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmKissCushion::
    .string "你选择了亲吻的垫子。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmSmoochumDoll::
    .string "你选择了迷唇姐玩偶。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmTogepiDoll::
    .string "你选择了波克比玩偶。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmMeowthDoll::
    .string "你选择了喵喵玩偶。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmClefairyDoll::
    .string "你选择了皮皮玩偶。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmDittoDoll::
    .string "你选择了百变怪玩偶。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmCyndaquilDoll::
    .string "你选择了火球鼠玩偶。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmChikoritaDoll::
    .string "你选择了菊草叶玩偶。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmTotodileDoll::
    .string "你选择了小锯鳄玩偶。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmLaprasDoll::
    .string "你选择了乘龙玩偶。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmSnorlaxDoll::
    .string "你选择了卡比兽玩偶。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmVenusaurDoll::
    .string "你选择了妙蛙花玩偶。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmCharizardDoll::
    .string "你选择了喷火龙玩偶。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmBlastoiseDoll::
    .string "你选择了水箭龟玩偶。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmProtein::
    .string "你选择了蛋白药剂。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmCalcium::
    .string "你选择了补钙药剂。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmIron::
    .string "你选择了补铁药剂。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmZinc::
    .string "你选择了补锌药剂。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmCarbos::
    .string "你选择了补碳药剂。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmHPUp::
    .string "你选择了HP提升剂。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmBrightpowder::
    .string "你选择了亮光之粉。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmWhiteHerb::
    .string "你选择了白色药草。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmQuickClaw::
    .string "你选择了先攻之爪。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmMentalHerb::
    .string "你选择了心灵药草。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmChoiceBand::
    .string "你选择了专爱头巾。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmKingsRock::
    .string "你选择了王者之证。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmFocusBand::
    .string "你选择了气息头巾。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmScopeLens::
    .string "你选择了对焦镜片。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmLeftovers::
    .string "你选择了剩饭。\n可以吗？$"

BattleFrontier_ExchangeServiceCorner_Text_WellSendItToPC::
    .string "谢谢！\n我们会把它送到你家的电脑上的。$"

BattleFrontier_ExchangeServiceCorner_Text_HereIsYourPrize::
    .string "这里是你的奖品！$"

BattleFrontier_ExchangeServiceCorner_Text_DontHaveEnoughPoints::
    .string "很抱歉…\n你没有足够多的对战点数…$"

BattleFrontier_ExchangeServiceCorner_Text_PCIsFull::
    .string "很抱歉…\n你的电脑好像满了…$"

BattleFrontier_ExchangeServiceCorner_Text_DontHaveSpaceToHoldIt::
    .string "很抱歉…\n你没有空间拿它…$"

BattleFrontier_ExchangeServiceCorner_Text_ThankYouVisitWithPoints::
    .string "非常感谢。\p当你存够了对战点数\n请再来见我们。$"

BattleFrontier_ExchangeServiceCorner_Text_WishIHadAllDolls::
    .string "哦，它们真漂亮！\n我想要它们！\l漂亮的垫子！\l大号豪华的玩偶！\l小号豪华的玩偶！\l我希望能全部得到！$"

BattleFrontier_ExchangeServiceCorner_Text_GetYouAnythingYouWant::
    .string "交给你的妈妈吧！\p无论什么你想要的，我会通过\n任何途径为你得到，我的小宝贝！$"

BattleFrontier_ExchangeServiceCorner_Text_ItemsWillGetMonTougher::
    .string "如果我能拿到这里的道具，\n我的宝可梦会变得更强。\p你要相信它们肯定会的！\n毫无疑问！$"

BattleFrontier_ExchangeServiceCorner_Text_GoGetYourOwnDoll::
    .string "啊？\n你在呆望什么？\p我不喜欢你那样盯着\n我的漂亮娃娃看。\p如果你想要，自己去弄一只！\n这不很好吗，迷唇娃？$"

BattleFrontier_ExchangeServiceCorner_Text_MoreBattlePointsForRecord::
    .string "你知道吗？\p如果你能在任何战斗场\n创造新记录，他们会给你\l更多更多对战点数。$"

BattleFrontier_ExchangeServiceCorner_Text_KissPosterDesc::
    .string "一大幅有迷唇姐签名的贴画。$"

BattleFrontier_ExchangeServiceCorner_Text_KissCushionDesc::
    .string "一个迷唇姐垫子。\n把它放在席子或桌子上。$"

BattleFrontier_ExchangeServiceCorner_Text_SmoochumDollDesc::
    .string "一个迷唇姐玩偶。\n把它放在席子或桌子上。$"

BattleFrontier_ExchangeServiceCorner_Text_TogepiDollDesc::
    .string "一个波克比玩偶。\n把它放在席子或桌子上。$"

BattleFrontier_ExchangeServiceCorner_Text_MeowthDollDesc::
    .string "一个喵喵玩偶。\n把它放在席子或桌子上。$"

BattleFrontier_ExchangeServiceCorner_Text_ClefairyDollDesc::
    .string "一个皮皮玩偶。\n把它放在席子或桌子上。$"

BattleFrontier_ExchangeServiceCorner_Text_DittoDollDesc::
    .string "一个百变怪玩偶。\n把它放在席子或桌子上。$"

BattleFrontier_ExchangeServiceCorner_Text_CyndaquilDollDesc::
    .string "一个火球鼠。\n把它放在席子或桌子上。$"

BattleFrontier_ExchangeServiceCorner_Text_ChikoritaDollDesc::
    .string "一个菊草叶。\n把它放在席子或桌子上。$"

BattleFrontier_ExchangeServiceCorner_Text_TotodileDollDesc::
    .string "一个小锯鳄。\n把它放在席子或桌子上。$"

BattleFrontier_ExchangeServiceCorner_Text_LargeDollDesc::
    .string "一个巨大的玩偶。\n把它放在席子或桌子上。$"

BattleFrontier_ExchangeServiceCorner_Text_ProteinDesc::
    .string "提升宝可梦的攻击\n能力。$"

BattleFrontier_ExchangeServiceCorner_Text_CalciumDesc::
    .string "提升宝可梦的特攻\n能力。$"

BattleFrontier_ExchangeServiceCorner_Text_IronDesc::
    .string "提升宝可梦的防御\n能力。$"

BattleFrontier_ExchangeServiceCorner_Text_ZincDesc::
    .string "提升宝可梦的特防\n能力。$"

BattleFrontier_ExchangeServiceCorner_Text_CarbosDesc::
    .string "提升宝可梦的速度\n能力。$"

BattleFrontier_ExchangeServiceCorner_Text_HPUpDesc::
    .string "提升宝可梦的HP。$"

BattleFrontier_ExchangeServiceCorner_Text_LeftoversDesc::
    .string "一件能在战斗中逐渐\n回复HP的道具。$"

BattleFrontier_ExchangeServiceCorner_Text_WhiteHerbDesc::
    .string "一件能回复所有能力\n的道具。$"

BattleFrontier_ExchangeServiceCorner_Text_QuickClawDesc::
    .string "一件能随机发生先制\n攻击的道具。$"

BattleFrontier_ExchangeServiceCorner_Text_MentalHerbDesc::
    .string "一件能解除宝可梦昏迷\n的道具。$"

BattleFrontier_ExchangeServiceCorner_Text_BrightpowderDesc::
    .string "一件能射出眩目的光降低\n准确度的道具。$"

BattleFrontier_ExchangeServiceCorner_Text_ChoiceBandDesc::
    .string "提升招式的力量，但只针对\n那个招式而言。$"

BattleFrontier_ExchangeServiceCorner_Text_KingsRockDesc::
    .string "一件在遇到敌人时能使敌人\n退缩的道具。$"

BattleFrontier_ExchangeServiceCorner_Text_FocusBandDesc::
    .string "一件能偶尔防止濒死\n的道具。$"

BattleFrontier_ExchangeServiceCorner_Text_ScopeLensDesc::
    .string "一件能提高会心率的\n道具。$"
