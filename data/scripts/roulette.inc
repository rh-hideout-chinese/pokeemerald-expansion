Roulette_EventScript_Table1::
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 0
	getpokenewsactive POKENEWS_GAME_CORNER
	goto_if_eq VAR_RESULT, FALSE, Roulette_EventScript_Play
	addvar VAR_0x8004, ROULETTE_SPECIAL_RATE
	goto Roulette_EventScript_Play
	end

Roulette_EventScript_Table2::
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 1
	getpokenewsactive POKENEWS_GAME_CORNER
	goto_if_eq VAR_RESULT, FALSE, Roulette_EventScript_Play
	addvar VAR_0x8004, ROULETTE_SPECIAL_RATE
	goto Roulette_EventScript_Play
	end

Roulette_EventScript_Play::
	special PlayRoulette
	waitstate
	end

Roulette_Text_PlayMinimumWagerIsX::
	.string "这里是倍率为{STR_VAR_1}倍的轮盘台。\n"
	.string "要在这里玩轮盘吗？$"

Roulette_Text_NotEnoughCoins::
	.string "代币不足……$"

Roulette_Text_SpecialRateTable::
	.string "现在是特别倍率期间！$"

Roulette_Text_ControlsInstruction::
	.string "用十字键选择要下注的网格，\n"
	.string "按A键决定。$"

Roulette_Text_ItsAHit::
	.string "中了！$"

Roulette_Text_Jackpot::
	.string "中大奖了！$"

Roulette_Text_NothingDoing::
	.string "没中——$"

Roulette_Text_YouveWonXCoins::
	.string "恭喜中奖！\n"
	.string "获得了{STR_VAR_1}枚硬币！$"

Roulette_Text_NoCoinsLeft::
	.string "代币用光了……$"

Roulette_Text_KeepPlaying::
	.string "要继续玩吗？$"

Roulette_Text_BoardWillBeCleared::
	.string "清除现在\n"
	.string "台面上的钢珠。$"

@ Unused
Roulette_Text_YouDontHaveACoinCase::
	.string "没有代币盒……$"

Roulette_Text_CoinCaseIsFull::
	.string "代币盒满了！\n"
	.string "请去兑换奖品！$"
//TODO 汉化
