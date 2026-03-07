FuchsiaCity_House3_Frlg_MapScripts::
	.byte 0

FuchsiaCity_House3_EventScript_MoveDeleter::
	lock
	faceplayer
	msgbox FuchsiaCity_House3_Text_WouldYouLikeToForgetMove, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FuchsiaCity_House3_EventScript_ChooseMonForMoveDeleter
	goto FuchsiaCity_House3_EventScript_CancelForgetMove
	end

FuchsiaCity_House3_EventScript_ChooseMonForMoveDeleter::
	msgbox FuchsiaCity_House3_Text_WhichMonShouldForgetMove
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, FuchsiaCity_House3_EventScript_CancelForgetMove
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, FuchsiaCity_House3_EventScript_CantForgetMoveEgg
	special GetNumMovesSelectedMonHas
	goto_if_eq VAR_RESULT, 1, FuchsiaCity_House3_EventScript_CantForgetOnlyMove
	msgbox FuchsiaCity_House3_Text_WhichMoveShouldBeForgotten
	fadescreen FADE_TO_BLACK
	special MoveDeleterChooseMoveToForget
	fadescreen FADE_FROM_BLACK
	goto_if_eq VAR_0x8005, MAX_MON_MOVES, FuchsiaCity_House3_EventScript_ChooseMonForMoveDeleter
	special BufferMoveDeleterNicknameAndMove
	msgbox FuchsiaCity_House3_Text_MonsMoveShouldBeForgotten, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FuchsiaCity_House3_EventScript_ForgetMove
	goto FuchsiaCity_House3_EventScript_CancelForgetMove
	end

FuchsiaCity_House3_EventScript_ForgetMove::
	special MoveDeleterForgetMove
	playfanfare MUS_MOVE_DELETED
	waitfanfare
	msgbox FuchsiaCity_House3_Text_MonHasForgottenMoveCompletely
	release
	end

FuchsiaCity_House3_EventScript_CantForgetOnlyMove::
	special BufferMoveDeleterNicknameAndMove
	msgbox FuchsiaCity_House3_Text_MonOnlyKnowsOneMove
	release
	end

FuchsiaCity_House3_EventScript_CantForgetMoveEgg::
	msgbox FuchsiaCity_House3_Text_NoEggShouldKnowMoves
	release
	end

FuchsiaCity_House3_EventScript_CancelForgetMove::
	msgbox FuchsiaCity_House3_Text_ComeAgainToForgetOtherMoves
	release
	end

FuchsiaCity_House3_Text_WouldYouLikeToForgetMove::
    .string "呃……我想说什么来着？\n"
    .string "我想起来了，我就是遗忘大师。\p"
    .string "我能让宝可梦忘记\n"
    .string "它们学会的技能。\p"
    .string "你需要我展示一下这门绝活吗？$"

FuchsiaCity_House3_Text_WhichMonShouldForgetMove::
    .string "哪一只宝可梦想要\n"
    .string "忘记技能？$"

FuchsiaCity_House3_Text_WhichMoveShouldBeForgotten::
    .string "要忘记哪个技能？$"

FuchsiaCity_House3_Text_MonOnlyKnowsOneMove::
    .string "{STR_VAR_1}好像只会\n"
    .string "一个技能……$"

FuchsiaCity_House3_Text_MonsMoveShouldBeForgotten::
    .string "嗯！{STR_VAR_1}的{STR_VAR_2}吗？\n"
    .string "要忘记这个技能？$"

FuchsiaCity_House3_Text_MonHasForgottenMoveCompletely::
    .string "完美搞定！\p"
    .string "{STR_VAR_1}已经将\n"
    .string "{STR_VAR_2}忘得一干二净了。$"

FuchsiaCity_House3_Text_ComeAgainToForgetOtherMoves::
    .string "如果你有别的技能想要忘记\n"
    .string "那么欢迎再次光临。$"

FuchsiaCity_House3_Text_NoEggShouldKnowMoves::
    .string "你在想什么？\n"
    .string "蛋怎么可能会学技能。$"

