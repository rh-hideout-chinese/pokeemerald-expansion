Route12_NorthEntrance_2F_Frlg_MapScripts::
	.byte 0

Route12_NorthEntrance_2F_EventScript_LeftBinoculars::
	msgbox Route12_NorthEntrance_2F_Text_TheresManFishing, MSGBOX_SIGN
	end

Route12_NorthEntrance_2F_EventScript_RightBinoculars::
	msgbox Route12_NorthEntrance_2F_Text_ItsPokemonTower, MSGBOX_SIGN
	end

Route12_NorthEntrance_2F_EventScript_Lass::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM27, Route12_NorthEntrance_2F_EventScript_ExplainTM27
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Route12_NorthEntrance_2F_EventScript_TakeTMMale
	call_if_eq VAR_RESULT, FEMALE, Route12_NorthEntrance_2F_EventScript_TakeTMFemale
	checkitemspace ITEM_TM27
	goto_if_eq VAR_RESULT, FALSE, Route12_NorthEntrance_2F_EventScript_NoRoomForTM27
	giveitem_msg Route12_NorthEntrance_2F_Text_ReceivedTM27FromLittleGirl, ITEM_TM27
	msgbox Route12_NorthEntrance_2F_Text_ExplainTM27
	setflag FLAG_GOT_TM27
	release
	end

Route12_NorthEntrance_2F_EventScript_TakeTMMale::
	msgbox Route12_NorthEntrance_2F_Text_TakeTMDontNeedAnymoreMale
	return

Route12_NorthEntrance_2F_EventScript_TakeTMFemale::
	msgbox Route12_NorthEntrance_2F_Text_TakeTMDontNeedAnymoreFemale
	return

Route12_NorthEntrance_2F_EventScript_NoRoomForTM27::
	msgbox Route12_NorthEntrance_2F_Text_DontHaveRoomForThis
	release
	end

Route12_NorthEntrance_2F_EventScript_ExplainTM27::
	msgbox Route12_NorthEntrance_2F_Text_ExplainTM27
	release
	end

@ Male and female text identical, differ (presumably) in JP
Route12_NorthEntrance_2F_Text_TakeTMDontNeedAnymoreMale::
    .string "我宝可梦的骨灰寄存在\n"
    .string "宝可梦塔。\p"
    .string "把这个技能拿走吧。\n"
    .string "我不再需要它了……$"

Route12_NorthEntrance_2F_Text_TakeTMDontNeedAnymoreFemale::
    .string "我宝可梦的骨灰寄存在\n"
    .string "宝可梦塔。\p"
    .string "把这个技能拿走吧。\n"
    .string "我不再需要它了……$"

Route12_NorthEntrance_2F_Text_ReceivedTM27FromLittleGirl::
    .string "{PLAYER}从小女孩那儿\n"
    .string "得到了TM27。$"

Route12_NorthEntrance_2F_Text_ExplainTM27::
    .string "TM27叫做报恩……\p"
    .string "如果你把宝可梦照顾得很好，\n"
    .string "它将会在战斗中\l"
    .string "以最大的力量回馈你的爱。$"

Route12_NorthEntrance_2F_Text_DontHaveRoomForThis::
    .string "你身上的空间不足以存放此道具。$"

Route12_NorthEntrance_2F_Text_TheresManFishing::
    .string "一架望远镜……\n"
    .string "我来看看……\p"
    .string "一个正在钓鱼的男人……！$"

Route12_NorthEntrance_2F_Text_ItsPokemonTower::
    .string "一架望远镜……\n"
    .string "我来看看……\p"
    .string "那是一座宝可梦塔$"

