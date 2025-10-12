Route110_TrickHousePuzzle4_MapScripts::
	.byte 0

Route110_TrickHousePuzzle4_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_4_STATE, 0, Route110_TrickHousePuzzle4_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle4_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_4_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle4_EventScript_Cora::
	trainerbattle_single TRAINER_CORA, Route110_TrickHousePuzzle4_Text_CoraIntro, Route110_TrickHousePuzzle4_Text_CoraDefeat
	msgbox Route110_TrickHousePuzzle4_Text_CoraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Yuji::
	trainerbattle_single TRAINER_YUJI, Route110_TrickHousePuzzle4_Text_YujiIntro, Route110_TrickHousePuzzle4_Text_YujiDefeat
	msgbox Route110_TrickHousePuzzle4_Text_YujiPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Paula::
	trainerbattle_single TRAINER_PAULA, Route110_TrickHousePuzzle4_Text_PaulaIntro, Route110_TrickHousePuzzle4_Text_PaulaDefeat
	msgbox Route110_TrickHousePuzzle4_Text_PaulaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_Text_WroteSecretCodeLockOpened:
    .string "{PLAYER}在门上写下\n密码。\p“戏法大王真棒”\n…… …… …… ……\p锁“咔嗒”一声开了！$"

Route110_TrickHousePuzzle4_Text_CoraIntro:
    .string "思考这些太麻烦了，\n我只想战斗而已！$"

Route110_TrickHousePuzzle4_Text_CoraDefeat:
    .string "就算会输，我还是喜欢\n挑战高手！$"

Route110_TrickHousePuzzle4_Text_CoraPostBattle:
    .string "只要有训练家的地方，\n都是我的目的地。\l你也是这么想的吧？$"

Route110_TrickHousePuzzle4_Text_YujiIntro:
    .string "哈！像这样的小石头，\n我用一根手指头就能推走！$"

Route110_TrickHousePuzzle4_Text_YujiDefeat:
    .string "我能推动这些小石头，但\n我解不开谜题……$"

Route110_TrickHousePuzzle4_Text_YujiPostBattle:
    .string "四肢发达并不完全是好事……\n你必须要动脑子！$"

Route110_TrickHousePuzzle4_Text_PaulaIntro:
    .string "戏法屋的谜题越来越难了，\n不是吗？$"

Route110_TrickHousePuzzle4_Text_PaulaDefeat:
    .string "哇啊！$"

Route110_TrickHousePuzzle4_Text_PaulaPostBattle:
    .string "有人成功走到头了吗？$"

