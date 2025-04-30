RustboroCity_PokemonSchool_MapScripts::
	.byte 0

RustboroCity_PokemonSchool_EventScript_Blackboard::
	lockall
	msgbox RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic::
	message RustboroCity_PokemonSchool_Text_ReadWhichTopic
	waitmessage
	multichoicegrid 8, 1, MULTI_STATUS_INFO, 3, FALSE
	switch VAR_RESULT
	case 0, RustboroCity_PokemonSchool_EventScript_Poison
	case 1, RustboroCity_PokemonSchool_EventScript_Paralysis
	case 2, RustboroCity_PokemonSchool_EventScript_Sleep
	case 3, RustboroCity_PokemonSchool_EventScript_Burn
	case 4, RustboroCity_PokemonSchool_EventScript_Freeze
	case 5, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	case MULTI_B_PRESSED, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	end

RustboroCity_PokemonSchool_EventScript_Poison::
	msgbox RustboroCity_PokemonSchool_Text_ExplainPoison, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Paralysis::
	msgbox RustboroCity_PokemonSchool_Text_ExplainParalysis, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Sleep::
	msgbox RustboroCity_PokemonSchool_Text_ExplainSleep, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Burn::
	msgbox RustboroCity_PokemonSchool_Text_ExplainBurn, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Freeze::
	msgbox RustboroCity_PokemonSchool_Text_ExplainFreeze, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ExitTopicSelect::
	releaseall
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid1::
	msgbox RustboroCity_PokemonSchool_Text_TradingRightNow, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid2::
	msgbox RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_RichBoy::
	msgbox RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_Lass::
	msgbox RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_SchoolKidM::
	msgbox RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_StudentNotebook::
	msgbox RustboroCity_PokemonSchool_Text_StudentsNotes, MSGBOX_SIGN
	end

RustboroCity_PokemonSchool_EventScript_Teacher::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_QUICK_CLAW, RustboroCity_PokemonSchool_EventScript_GaveQuickClaw
	call_if_eq VAR_FACING, DIR_EAST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast
	call_if_eq VAR_FACING, DIR_WEST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest
	msgbox RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_CLAW
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	setflag FLAG_RECEIVED_QUICK_CLAW
	release
	end

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast::
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest::
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_GaveQuickClaw::
	msgbox RustboroCity_PokemonSchool_Text_ExplainQuickClaw, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	release
	end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest:
	walk_left
	walk_down
	walk_down
	walk_right
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	walk_right
	step_end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast:
	walk_right
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_right
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

RustboroCity_PokemonSchool_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE, RustboroCity_PokemonSchool_EventScript_ScottWatchStudents
	goto_if_set FLAG_MET_SCOTT_RUSTBORO, RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_RUSTBORO
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready::
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge::
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge::
	msgbox RustboroCity_PokemonSchool_Text_ScottStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge::
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottWatchStudents::
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges:
    .string "黑板上写着可能影响\n宝可梦战斗的状态变化。$"

RustboroCity_PokemonSchool_Text_ReadWhichTopic:
    .string "想读哪一条？$"

RustboroCity_PokemonSchool_Text_ExplainPoison:
    .string "宝可梦中毒后，\n会慢慢损失体力，\p此效果在战斗后\n依然残留。\p在探险中，中毒的宝可梦的体力P\n也会不断减少。\p使用解毒药可解毒。$"

RustboroCity_PokemonSchool_Text_ExplainParalysis:
    .string "宝可梦麻痹后，\n速度会降低，\p战斗中有可能\n无法使用招式。\p此效果战斗后依然残留。\n使用解麻药可治愈。$"

RustboroCity_PokemonSchool_Text_ExplainSleep:
    .string "宝可梦睡着后，\n就无法攻击了。\p宝可梦有可能自己醒来，\n但如果战斗结束后\l它还在睡觉，那么它会一直睡着。\p用解眠药叫醒它。$"

RustboroCity_PokemonSchool_Text_ExplainBurn:
    .string "灼伤会降低攻击，\n同时会降低伤者的体力。\p战斗后灼伤还会留下。\n用灼伤药可以治愈。$"

RustboroCity_PokemonSchool_Text_ExplainFreeze:
    .string "宝可梦被冰冻后，\n它完全无法反击，\p战斗后依然会保持冻结。\n用解冻药为它解冻。$"

RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw:
    .string "对于偷懒的学生，\n我就让他们尝尝我的先制之爪。\p你是不是个好学生，\n只要看看你怎么用这件物品\l就能知道。$"

RustboroCity_PokemonSchool_Text_ExplainQuickClaw:
    .string "带着先制之爪的宝可梦\n偶尔会提高速度\l比对手先发动攻击。\p还有很多可以给宝可梦\n携带的东西，\p只是这一点就\n足够你学很久了！$"

RustboroCity_PokemonSchool_Text_TradingRightNow:
    .string "我刚才在和朋友\n交换宝可梦。$"

RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot:
    .string "我一直想要一只橡实果，\n现在终于有了！$"

RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems:
    .string "宝可梦可以带一些物品，\n但它们不会使用伤药或\l解毒药这样的人造物品。$"

RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself:
    .string "你知道某些宝可梦的招式\n可以使对手宝可梦混乱吗？\p混乱的宝可梦有时\n会不知为何攻击自己。\p但一旦它退出战斗，\n它就会恢复正常。$"

RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry:
    .string "带着树果的宝可梦\n能够自我治疗……\p许多物品都可以\n让宝可梦带上……\p唉，及时记下笔记\n太难了……$"

RustboroCity_PokemonSchool_Text_StudentsNotes:
    .string "这是这个学生的笔记本……\p用精灵球\n可以捕捉宝可梦。\p一个训练家最多可以\n同时携带六只宝可梦。\p训练家就是捕捉宝可梦，\n并养育它们，与它们\l共同战斗的人。\p训练家的任务是\n打败在宝可梦道馆中\l等待着的强大训练家。$"

RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut:
    .string "你好，我们以前见过面吧？\n我想是在橙华市见过。\p我来介绍一下自己。\n我叫亚希达，\p我是为了寻找\n出色的训练家而旅行，\p具体点说，就是\n寻找战斗的专家。\p可以问问你为什么会来学校吗？\n你也是训练家吗？\p你首先要做的是\n拥有一只会居合劈的宝可梦。\p如果我记得不错，\n这镇上就有人拥有居合劈。$"

RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown:
    .string "亚希达：嗯……\p不知道这里的学生天赋如何。\n也许有潜力的人并不在此。$"

RustboroCity_PokemonSchool_Text_ScottStoneBadge:
    .string "亚希达：哦，那是什么？\p岩石徽章是吗？\n真令人吃惊。\p但是，我更想看看\n你的战斗。\p仅凭一枚联盟徽章\n很难看出训练家的水平高低。$"

RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge:
    .string "你好，我们以前见过面吧？\n我想是在橙华市见过。\p我来介绍一下自己。\n我叫亚希达，\p我是为了寻找\n出色的训练家而旅行，\p具体点说，就是\n寻找战斗的专家。\p哦，那是什么？\p岩石徽章是吗？\p这对你这样的\n新人训练家来说很不错了。\p但是，我更想看看\n你的战斗。\p仅凭一枚联盟徽章\n很难看出训练家的水平高低。$"

