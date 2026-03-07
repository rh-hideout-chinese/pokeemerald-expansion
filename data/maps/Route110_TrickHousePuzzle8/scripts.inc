Route110_TrickHousePuzzle8_MapScripts::
	.byte 0

Route110_TrickHousePuzzle8_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_8_STATE, 0, Route110_TrickHousePuzzle8_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle8_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_8_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle8_EventScript_Vincent::
	trainerbattle_single TRAINER_VINCENT, Route110_TrickHousePuzzle8_Text_VincentIntro, Route110_TrickHousePuzzle8_Text_VincentDefeat
	msgbox Route110_TrickHousePuzzle8_Text_VincentPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Keira::
	trainerbattle_single TRAINER_KEIRA, Route110_TrickHousePuzzle8_Text_KeiraIntro, Route110_TrickHousePuzzle8_Text_KeiraDefeat
	msgbox Route110_TrickHousePuzzle8_Text_KeiraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Leroy::
	trainerbattle_single TRAINER_LEROY, Route110_TrickHousePuzzle8_Text_LeroyIntro, Route110_TrickHousePuzzle8_Text_LeroyDefeat
	msgbox Route110_TrickHousePuzzle8_Text_LeroyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_Text_WroteSecretCodeLockOpened:
    .string "{PLAYER}在门上写下\n密码。\p“我爱戏法大王”\n…… …… …… ……\p锁“咔嗒”一声开了！$"

Route110_TrickHousePuzzle8_Text_VincentIntro:
    .string "没有多少训练家 \n能到达这里。$"

Route110_TrickHousePuzzle8_Text_VincentDefeat:
    .string "这就意味着你也非常强大……$"

Route110_TrickHousePuzzle8_Text_VincentPostBattle:
    .string "你已经打败了宝可梦联盟冠军？\n太厉害了！$"

Route110_TrickHousePuzzle8_Text_KeiraIntro:
    .string "跟我对战，\n你应该感到非常幸运！$"

Route110_TrickHousePuzzle8_Text_KeiraDefeat:
    .string "这不可能！\n我怎么会输！$"

Route110_TrickHousePuzzle8_Text_KeiraPostBattle:
    .string "你能打败我真是奇迹，\n你可以引以为傲了。$"

Route110_TrickHousePuzzle8_Text_LeroyIntro:
    .string "你也在艰难地挑战这\n戏法屋啊。$"

Route110_TrickHousePuzzle8_Text_LeroyDefeat:
    .string "明白了……\n你的行事风格很特别。$"

Route110_TrickHousePuzzle8_Text_LeroyPostBattle:
    .string "见到你这样的人\n戏法大王应该会很高兴吧。$"

