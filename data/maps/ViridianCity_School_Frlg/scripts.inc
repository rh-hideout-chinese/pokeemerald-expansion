ViridianCity_School_Frlg_MapScripts::
	.byte 0

ViridianCity_School_EventScript_Lass::
	lock
	faceplayer
	msgbox ViridianCity_School_Text_TryingToMemorizeNotes
	closemessage
	applymovement LOCALID_SCHOOL_LASS, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

ViridianCity_School_EventScript_Woman::
	lock
	faceplayer
	msgbox ViridianCity_School_Text_ReadBlackboardCarefully
	closemessage
	applymovement LOCALID_SCHOOL_WOMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

ViridianCity_School_EventScript_Notebook::
	lockall
	msgbox ViridianCity_School_Text_NotebookFirstPage
	msgbox ViridianCity_School_Text_TurnThePage, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ViridianCity_School_EventScript_StopReadingNotebook
	msgbox ViridianCity_School_Text_NotebookSecondPage
	msgbox ViridianCity_School_Text_TurnThePage, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ViridianCity_School_EventScript_StopReadingNotebook
	msgbox ViridianCity_School_Text_NotebookThirdPage
	msgbox ViridianCity_School_Text_TurnThePage, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ViridianCity_School_EventScript_StopReadingNotebook
	msgbox ViridianCity_School_Text_NotebookFourthPage
	applymovement LOCALID_SCHOOL_LASS, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox ViridianCity_School_Text_HeyDontLookAtMyNotes
	releaseall
	end

ViridianCity_School_EventScript_StopReadingNotebook::
	releaseall
	end

ViridianCity_School_EventScript_Blackboard::
	lockall
	msgbox ViridianCity_School_Text_BlackboardListsStatusProblems
	goto ViridianCity_School_EventScript_ChooseBlackboardTopic
	end

ViridianCity_School_EventScript_ChooseBlackboardTopic::
	message ViridianCity_School_Text_ReadWhichTopic
	waitmessage
	multichoicegrid 7, 1, MULTI_STATUS_INFO, 3, FALSE
	switch VAR_RESULT
	case 0, ViridianCity_School_EventScript_ReadSleep
	case 1, ViridianCity_School_EventScript_ReadPoison
	case 2, ViridianCity_School_EventScript_ReadParalysis
	case 3, ViridianCity_School_EventScript_ReadBurn
	case 4, ViridianCity_School_EventScript_ReadFreeze
	case 5, ViridianCity_School_EventScript_ExitBlackboard
	case 127, ViridianCity_School_EventScript_ExitBlackboard
	end

ViridianCity_School_EventScript_ReadSleep::
	msgbox ViridianCity_School_Text_ExplainSleep
	goto ViridianCity_School_EventScript_ChooseBlackboardTopic
	end

ViridianCity_School_EventScript_ReadBurn::
	msgbox ViridianCity_School_Text_ExplainBurn
	goto ViridianCity_School_EventScript_ChooseBlackboardTopic
	end

ViridianCity_School_EventScript_ReadPoison::
	msgbox ViridianCity_School_Text_ExplainPoison
	goto ViridianCity_School_EventScript_ChooseBlackboardTopic
	end

ViridianCity_School_EventScript_ReadFreeze::
	msgbox ViridianCity_School_Text_ExplainFreeze
	goto ViridianCity_School_EventScript_ChooseBlackboardTopic
	end

ViridianCity_School_EventScript_ReadParalysis::
	msgbox ViridianCity_School_Text_ExplainParalysis
	goto ViridianCity_School_EventScript_ChooseBlackboardTopic
	end

ViridianCity_School_EventScript_ExitBlackboard::
	releaseall
	end

ViridianCity_School_Text_TryingToMemorizeNotes::
    .string "呜！我正尽力记住我所有的笔记。$"

ViridianCity_School_Text_ReadBlackboardCarefully::
    .string "好的！\p"
    .string "一定要仔细读黑板上\n"
    .string "写的东西！$"

ViridianCity_School_Text_NotebookFirstPage::
    .string "我们看一下笔记本。\p"
    .string "第一页……\p"
    .string "精灵球是用来抓宝可梦的。\p"
    .string "你最多能带6只宝可梦。\p"
    .string "培养和使用宝可梦战斗的人\n"
    .string "被称为训练家。$"

ViridianCity_School_Text_NotebookSecondPage::
    .string "第二页……\p"
    .string "一只健康的宝可梦很难被收服，\n"
    .string "所以首先要把它变弱。\p"
    .string "用毒，烧伤，或者用其他能造成\n"
    .string "异常状态的技能来削弱它。$"

ViridianCity_School_Text_NotebookThirdPage::
    .string "第三页……\p"
    .string "宝可梦训练家喜欢和\n"
    .string "别人进行宝可梦战斗。\p"
    .string "对于训练家很美好的。\p"
    .string "战斗在宝可梦道馆，\n"
    .string "是每天都会发生的事情。$"

ViridianCity_School_Text_NotebookFourthPage::
    .string "第四页……\p"
    .string "所有的宝可梦训练家\n"
    .string "最终的目标很简单。\p"
    .string "就是战胜8位宝可梦道馆馆主。\p"
    .string "然后就有资格去面对……\p"
    .string "宝可梦联盟的四天王！$"

ViridianCity_School_Text_TurnThePage::
    .string "翻页吗？$"

ViridianCity_School_Text_HeyDontLookAtMyNotes::
    .string "女生：喂！\n"
    .string "不要看我的笔记！$"

ViridianCity_School_Text_BlackboardListsStatusProblems::
    .string "黑板上列出了在战斗中\n"
    .string "宝可梦状态的问题。$"

ViridianCity_School_Text_ReadWhichTopic::
    .string "你想读哪个？$"

ViridianCity_School_Text_ExplainSleep::
    .string "如果宝可梦睡着了，\n"
    .string "那么它就无法攻击了。\p"
    .string "甚至战斗结束以后\n"
    .string "也不会醒。\p"
    .string "用解眠药可以叫醒它。$"

ViridianCity_School_Text_ExplainBurn::
    .string "烧伤会减少攻击力。\n"
    .string "而且会引起HP的损失。\p"
    .string "在战斗结束后烧伤会一直持续。\n"
    .string "用灼伤药可以治烧伤。$"

ViridianCity_School_Text_ExplainPoison::
    .string "宝可梦中毒以后，\n"
    .string "每回合都会损失HP。\p"
    .string "而且战斗结束也不会消失。\n"
    .string "可以用解毒药治疗中毒！$"

ViridianCity_School_Text_ExplainFreeze::
    .string "被冰冻的宝可梦无法\n"
    .string "正常行动。\p"
    .string "而且战斗结束\n"
    .string "冰冻也会一直持续。\p"
    .string "用解冻药来治疗被冰冻的宝可梦。$"

ViridianCity_School_Text_ExplainParalysis::
    .string "麻痹会减少宝可梦的速度，\n"
    .string "而且可能使宝可梦无法行动。\p"
    .string "麻痹状态在战斗结束后会一直保持。\n"
    .string "要用解麻药来治疗。$"

