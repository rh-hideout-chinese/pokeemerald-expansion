Route5_SouthEntrance_Frlg_MapScripts::
	.byte 0

Route5_SouthEntrance_EventScript_Guard::
	msgbox Route5_SouthEntrance_Text_HiHowsItGoing, MSGBOX_NPC
	end

Route5_SouthEntrance_EventScript_GuardTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto Route5_SouthEntrance_EventScript_GuardTrigger
	end

Route5_SouthEntrance_EventScript_GuardTriggerMid::
	lockall
	setvar VAR_TEMP_1, 1
	goto Route5_SouthEntrance_EventScript_GuardTrigger
	end

Route5_SouthEntrance_EventScript_GuardTriggerRight::
	lockall
	setvar VAR_TEMP_1, 2
	goto Route5_SouthEntrance_EventScript_GuardTrigger
	end

Route5_SouthEntrance_EventScript_GuardTrigger::
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto_if_set FLAG_GOT_TEA, Route5_SouthEntrance_EventScript_GiveTea
	msgbox Route5_SouthEntrance_Text_ThirstyOnGuardDuty
	closemessage
	applymovement LOCALID_PLAYER, Route5_SouthEntrance_Movement_BlockPlayerEntry
	waitmovement 0
	releaseall
	end

Route5_SouthEntrance_EventScript_GiveTea::
	removeitem ITEM_TEA
	goto Route5_SouthEntrance_EventScript_GuardDrinkTea
	end

Route5_SouthEntrance_EventScript_GuardDrinkTea::
	msgbox Route5_SouthEntrance_Text_ThatTeaLooksTasty
	closemessage
	call_if_eq VAR_TEMP_1, 0, Route5_SouthEntrance_EventScript_WalkToGuardLeft
	call_if_eq VAR_TEMP_1, 1, Route5_SouthEntrance_EventScript_WalkToGuardMid
	call_if_eq VAR_TEMP_1, 2, Route5_SouthEntrance_EventScript_WalkToGuardRight
	msgbox Route5_SouthEntrance_Text_ThanksIllShareTeaWithGuards
	setvar VAR_MAP_SCENE_ROUTE5_ROUTE6_ROUTE7_ROUTE8_GATES, 1
	releaseall
	end

Route5_SouthEntrance_EventScript_WalkToGuardLeft::
	applymovement LOCALID_PLAYER, Route5_SouthEntrance_Movement_WalkToGuardLeft
	waitmovement 0
	return

Route5_SouthEntrance_EventScript_WalkToGuardMid::
	applymovement LOCALID_PLAYER, Route5_SouthEntrance_Movement_WalkToGuardMid
	waitmovement 0
	return

Route5_SouthEntrance_EventScript_WalkToGuardRight::
	applymovement LOCALID_PLAYER, Route5_SouthEntrance_Movement_WalkToGuardRight
	waitmovement 0
	return

Route5_SouthEntrance_Movement_WalkToGuardMid::
	walk_left
	step_end

Route5_SouthEntrance_Movement_WalkToGuardRight::
	walk_left
	walk_left
	step_end

Route5_SouthEntrance_Movement_WalkToGuardLeft::
	walk_in_place_left
	step_end

Route5_SouthEntrance_Movement_BlockPlayerEntry::
	walk_up
	step_end

Route5_SouthEntrance_Text_ThirstyOnGuardDuty::
    .string "呃，我虽然很口渴得要命。\n"
    .string "但我仍然在第一线执勤！\p"
    .string "喂，站住！那条路禁止通行！$"

Route5_SouthEntrance_Text_ThatTeaLooksTasty::
    .string "诶，那个茶……\n"
    .string "看起来很好喝的样子……$"

Route5_SouthEntrance_Text_ThanksIllShareTeaWithGuards::
    .string "嗯？我能喝这个吗？\n"
    .string "呃，谢谢！\l"
    .string "……\l"
    .string "咕噜……咕噜……\l"
    .string "……\l"
    .string "嗯……\l"
    .string "如果你想去\l"
    .string "金黄市的话……\l"
    .string "……\l"
    .string "就去吧。\p"
    .string "我去和其他的警卫\n"
    .string "一起分了这杯茶。$"

Route5_SouthEntrance_Text_HiHowsItGoing::
    .string "嗨，最近过得怎么样啊？$"

