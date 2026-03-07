.equ BILL_IN_TELEPORTER,     FLAG_TEMP_2
.equ RETURN_AFTER_SS_TICKET, FLAG_TEMP_3

Route25_SeaCottage_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route25_SeaCottage_OnTransition
	.byte 0

Route25_SeaCottage_OnTransition::
	call_if_unset FLAG_HELPED_BILL_IN_SEA_COTTAGE, Route25_SeaCottage_EventScript_HideClefairyBill
	call_if_set FLAG_GOT_SS_TICKET, Route25_SeaCottage_EventScript_SetReturnedAfterSSTicket
	end

Route25_SeaCottage_EventScript_HideClefairyBill::
	clearflag FLAG_HIDE_BILL_CLEFAIRY
	setobjectxyperm LOCALID_BILL_HUMAN, 3, 3
	return

Route25_SeaCottage_EventScript_SetReturnedAfterSSTicket::
	setflag RETURN_AFTER_SS_TICKET
	return

Route25_SeaCottage_EventScript_Bill::
	lock
	faceplayer
	goto_if_set RETURN_AFTER_SS_TICKET, Route25_SeaCottage_EventScript_BillGoLookAtPC
	goto_if_set FLAG_GOT_SS_TICKET, Route25_SeaCottage_EventScript_BillGoToSSAnne
	goto_if_set FLAG_HELPED_BILL_IN_SEA_COTTAGE, Route25_SeaCottage_EventScript_BillGiveSSTicket
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route25_SeaCottage_EventScript_BillAskForHelpMale
	goto_if_eq VAR_RESULT, FEMALE, Route25_SeaCottage_EventScript_BillAskForHelpFemale
	end

Route25_SeaCottage_EventScript_BillAskForHelpMale::
	msgbox Route25_SeaCottage_Text_ImBillHelpMeOutPal, MSGBOX_YESNO
	goto Route25_SeaCottage_EventScript_BillAskForHelp
	end

Route25_SeaCottage_EventScript_BillAskForHelpFemale::
	msgbox Route25_SeaCottage_Text_ImBillHelpMeOutLady, MSGBOX_YESNO
	goto Route25_SeaCottage_EventScript_BillAskForHelp
	end

Route25_SeaCottage_EventScript_BillAskForHelp::
	call_if_eq VAR_RESULT, NO, Route25_SeaCottage_EventScript_DeclineHelpBill
	msgbox Route25_SeaCottage_Text_RunCellSeparationOnPC
	closemessage
	delay 10
	call_if_eq VAR_FACING, DIR_SOUTH, Route25_SeaCottage_EventScript_BillWalkToTeleporterSouth
	call_if_eq VAR_FACING, DIR_NORTH, Route25_SeaCottage_EventScript_BillWalkToTeleporter
	call_if_eq VAR_FACING, DIR_WEST, Route25_SeaCottage_EventScript_BillWalkToTeleporter
	call_if_eq VAR_FACING, DIR_EAST, Route25_SeaCottage_EventScript_BillWalkToTeleporter
	opendoor 10, 3
	waitdooranim
	applymovement LOCALID_BILL_CLEFAIRY, Route25_SeaCottage_Movement_BillEnterTeleporter
	waitmovement 0
	removeobject LOCALID_BILL_CLEFAIRY
	playse SE_CONTEST_CURTAIN_FALL
	closedoor 10, 3
	waitdooranim
	setflag BILL_IN_TELEPORTER
	release
	end

@ Just returns after message, execution continues as if player had said yes
Route25_SeaCottage_EventScript_DeclineHelpBill::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Route25_SeaCottage_EventScript_DeclineHelpBillMale
	call_if_eq VAR_RESULT, FEMALE, Route25_SeaCottage_EventScript_DeclineHelpBillFemale
	return

Route25_SeaCottage_EventScript_DeclineHelpBillMale::
	msgbox Route25_SeaCottage_Text_NoPleaseChief
	return

Route25_SeaCottage_EventScript_DeclineHelpBillFemale::
	msgbox Route25_SeaCottage_Text_NoPleaseBeautiful
	return

Route25_SeaCottage_EventScript_BillWalkToTeleporterSouth::
	applymovement LOCALID_BILL_CLEFAIRY, Route25_SeaCottage_Movement_BillWalkToTeleporterSouth
	waitmovement 0
	return

Route25_SeaCottage_EventScript_BillWalkToTeleporter::
	applymovement LOCALID_BILL_CLEFAIRY, Route25_SeaCottage_Movement_BillWalkToTeleporter
	waitmovement 0
	return

Route25_SeaCottage_EventScript_BillGoToSSAnne::
	msgbox Route25_SeaCottage_Text_SSAnnePartyYouGoInstead
	release
	end

Route25_SeaCottage_EventScript_BillGiveSSTicket::
	famechecker FAMECHECKER_BILL, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Route25_SeaCottage_EventScript_BillThanksMale
	call_if_eq VAR_RESULT, FEMALE, Route25_SeaCottage_EventScript_BillThanksFemale
	checkitemspace ITEM_SS_TICKET
	goto_if_eq VAR_RESULT, FALSE, Route25_SeaCottage_EventScript_NoRoomForSSTicket
	giveitem_msg Route25_SeaCottage_Text_ReceivedSSTicketFromBill, ITEM_SS_TICKET, 1, MUS_RG_OBTAIN_KEY_ITEM
	setflag FLAG_GOT_SS_TICKET_DUP
	setflag FLAG_HIDE_NUGGET_BRIDGE_ROCKET
	setflag FLAG_GOT_SS_TICKET
	setflag FLAG_SYS_PC_LANETTE
	goto Route25_SeaCottage_EventScript_BillGoToSSAnne
	end

Route25_SeaCottage_EventScript_BillThanksMale::
	msgbox Route25_SeaCottage_Text_ThanksBudTakeThis
	return

Route25_SeaCottage_EventScript_BillThanksFemale::
	msgbox Route25_SeaCottage_Text_ThanksLadyTakeThis
	return

Route25_SeaCottage_EventScript_NoRoomForSSTicket::
	msgbox Route25_SeaCottage_Text_YouveGotTooMuchStuff
	release
	end

Route25_SeaCottage_EventScript_BillGoLookAtPC::
	msgbox Route25_SeaCottage_Text_CheckOutRareMonsOnPC
	release
	end

Route25_SeaCottage_Movement_BillWalkToTeleporter::
	walk_up
	walk_up
	step_end

Route25_SeaCottage_Movement_BillWalkToTeleporterSouth::
	walk_right
	walk_up
	walk_up
	walk_left
	walk_in_place_faster_up
	step_end

Route25_SeaCottage_Movement_BillEnterTeleporter::
	walk_up
	step_end

Route25_SeaCottage_EventScript_Computer::
	lockall
	goto_if_set RETURN_AFTER_SS_TICKET, Route25_SeaCottage_EventScript_OpenBillsMonList
	goto_if_set BILL_IN_TELEPORTER, Route25_SeaCottage_EventScript_RunCellSeparator
	msgbox Route25_SeaCottage_Text_TeleporterIsDisplayed
	releaseall
	end

Route25_SeaCottage_EventScript_RunCellSeparator::
	fadeoutbgm 0
	msgbox Route25_SeaCottage_Text_InitiatedTeleportersCellSeparator
	closemessage
	clearflag BILL_IN_TELEPORTER
	setflag FLAG_HELPED_BILL_IN_SEA_COTTAGE
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, Route25_SeaCottage_Movement_CameraPanToTeleporters
	waitmovement 0
	delay 35
	playse SE_PIN
	waitse
	setvar VAR_0x8004, 0
	special AnimateTeleporterHousing
	delay 10
	call Route25_SeaCottage_EventScript_PlayTeleporterBeepSE
	call Route25_SeaCottage_EventScript_PlayTeleporterBeepSE
	call Route25_SeaCottage_EventScript_PlayTeleporterBeepSE
	call Route25_SeaCottage_EventScript_PlayTeleporterBeepSE
	call Route25_SeaCottage_EventScript_PlayTeleporterBeepSE
	call Route25_SeaCottage_EventScript_PlayTeleporterBeepSE
	call Route25_SeaCottage_EventScript_PlayTeleporterBeepSE
	setvar VAR_0x8004, 1
	special AnimateTeleporterHousing
	playse SE_WARP_IN
	special AnimateTeleporterCable
	waitse
	call Route25_SeaCottage_EventScript_PlayTeleporterBeepSE
	call Route25_SeaCottage_EventScript_PlayTeleporterBeepSE
	call Route25_SeaCottage_EventScript_PlayTeleporterBeepSE
	call Route25_SeaCottage_EventScript_PlayTeleporterBeepSE
	call Route25_SeaCottage_EventScript_PlayTeleporterBeepSE
	opendoor 3, 3
	waitdooranim
	fadeinbgm 0
	addobject LOCALID_BILL_HUMAN
	clearflag FLAG_HIDE_BILL_HUMAN_SEA_COTTAGE
	delay 50
	playfanfare MUS_LEVEL_UP
	applymovement LOCALID_BILL_HUMAN, Route25_SeaCottage_Movement_BillExitTeleporter
	waitmovement 0
	waitfanfare
	applymovement LOCALID_CAMERA, Route25_SeaCottage_Movement_CameraPanBackFromTeleporters
	waitmovement 0
	playse SE_CONTEST_CURTAIN_FALL
	closedoor 3, 3
	waitdooranim
	applymovement LOCALID_BILL_HUMAN, Route25_SeaCottage_Movement_BillWalkToMiddleOfRoom
	waitmovement 0
	special RemoveCameraObject
	releaseall
	end

Route25_SeaCottage_EventScript_PlayTeleporterBeepSE::
	playse SE_BALL
	waitse
	delay 20
	return

Route25_SeaCottage_Movement_CameraPanToTeleporters::
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

Route25_SeaCottage_Movement_CameraPanBackFromTeleporters::
	delay_16
	delay_16
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

Route25_SeaCottage_EventScript_OpenBillsMonList::
	msgbox Route25_SeaCottage_Text_BillsFavoriteMonList
	goto Route25_SeaCottage_EventScript_BillsMonList
	end

Route25_SeaCottage_EventScript_BillsMonList::
	message Route25_SeaCottage_Text_SeeWhichMon
	waitmessage
	multichoice 0, 0, MULTI_EEVEELUTIONS, FALSE
	switch VAR_RESULT
	case 0, Route25_SeaCottage_EventScript_ViewEevee
	case 1, Route25_SeaCottage_EventScript_ViewFlareon
	case 2, Route25_SeaCottage_EventScript_ViewJolteon
	case 3, Route25_SeaCottage_EventScript_ViewVaporeon
	case 4, Route25_SeaCottage_EventScript_ExitBillsMonList
	case 127, Route25_SeaCottage_EventScript_ExitBillsMonList
	end

Route25_SeaCottage_EventScript_ViewEevee::
	showmonpic SPECIES_EEVEE, 10, 3
	waitbuttonpress
	hidemonpic
	setvar VAR_0x8004, SPECIES_EEVEE
	special SetSeenMon
	goto Route25_SeaCottage_EventScript_BillsMonList
	end

Route25_SeaCottage_EventScript_ViewFlareon::
	showmonpic SPECIES_FLAREON, 10, 3
	waitbuttonpress
	hidemonpic
	setvar VAR_0x8004, SPECIES_FLAREON
	special SetSeenMon
	goto Route25_SeaCottage_EventScript_BillsMonList
	end

Route25_SeaCottage_EventScript_ViewJolteon::
	showmonpic SPECIES_JOLTEON, 10, 3
	waitbuttonpress
	hidemonpic
	setvar VAR_0x8004, SPECIES_JOLTEON
	special SetSeenMon
	goto Route25_SeaCottage_EventScript_BillsMonList
	end

Route25_SeaCottage_EventScript_ViewVaporeon::
	showmonpic SPECIES_VAPOREON, 10, 3
	waitbuttonpress
	hidemonpic
	setvar VAR_0x8004, SPECIES_VAPOREON
	special SetSeenMon
	goto Route25_SeaCottage_EventScript_BillsMonList
	end

Route25_SeaCottage_EventScript_ExitBillsMonList::
	releaseall
	end

Route25_SeaCottage_Movement_BillWalkToMiddleOfRoom::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

Route25_SeaCottage_Movement_BillExitTeleporter::
	walk_down
	step_end

Route25_SeaCottage_Text_ImBillHelpMeOutPal::
    .string "哈！我是一只宝可梦……\n"
    .string "不对，我才不是！\p"
    .string "我是正辉！\n"
    .string "我是一个货真价实的怪兽狂！\p"
    .string "嘿！\n"
    .string "为什么要摆出一副怀疑的表情？\p"
    .string "朋友，我没和你开玩笑！\p"
    .string "我试验失败了然后和\n"
    .string "一只宝可梦合体了！\p"
    .string "那么，怎么样？\n"
    .string "帮我恢复原状吧！$"

Route25_SeaCottage_Text_ImBillHelpMeOutLady::
    .string "哈！我是一只宝可梦……\n"
    .string "不对，我才不是！\p"
    .string "我是正辉！\n"
    .string "我是一个货真价实的怪兽狂！\p"
    .string "嘿！\n"
    .string "为什么要摆出一副怀疑的表情？\p"
    .string "小姐，我没和你开玩笑！\p"
    .string "我试验失败了然后和\n"
    .string "一只宝可梦合体了！\p"
    .string "那么，你觉得怎么样？\n"
    .string "帮我恢复原状吧！$"

Route25_SeaCottage_Text_RunCellSeparationOnPC::
    .string "请先等我进入\n"
    .string "传送装置。\p"
    .string "等我进去了以后，去我的电脑运行\n"
    .string "细胞分离系统。$"

Route25_SeaCottage_Text_NoPleaseChief::
    .string "不！？\n"
    .string "你不能这么冷淡！\p"
    .string "拜托，你一定要帮我这个陷入了\n"
    .string "大-大-大麻烦的人！\p"
    .string "怎样，帅哥？\n"
    .string "好吧？\l"
    .string "行吧？\l"
    .string "太好了！$"

Route25_SeaCottage_Text_NoPleaseBeautiful::
    .string "不！？\n"
    .string "你不能这么冷淡！\p"
    .string "拜托，你一定要帮我这个陷入了\n"
    .string "大-大-大麻烦的人！\p"
    .string "怎样，美女？\n"
    .string "好吧？\l"
    .string "行吧？\l"
    .string "太好了！$"

Route25_SeaCottage_Text_ThanksBudTakeThis::
    .string "正辉：啊呀呀呀！\n"
    .string "谢了，兄弟！我欠你一次！\p"
    .string "嗯，你看过我的\n"
    .string "宝可梦收藏了吗？\p"
    .string "还没有？\n"
    .string "太可惜了。\p"
    .string "我该怎样表达我的谢意……\n"
    .string "啊，这个，这个应该不错的。$"

Route25_SeaCottage_Text_ThanksLadyTakeThis::
    .string "正辉：啊呀呀呀！\n"
    .string "谢了，小姐！我欠你一次！\p"
    .string "嗯，你看过我的\n"
    .string "宝可梦收藏了吗？\p"
    .string "还没有？\n"
    .string "太可惜了。\p"
    .string "我该怎样表达我的谢意……\n"
    .string "啊，这个，这应该不错的。$"

Route25_SeaCottage_Text_ReceivedSSTicketFromBill::
    .string "{PLAYER}从正辉手上\n"
    .string "接过船票。$"

Route25_SeaCottage_Text_YouveGotTooMuchStuff::
    .string "你身上的东西太多了！$"

Route25_SeaCottage_Text_SSAnnePartyYouGoInstead::
    .string "这艘圣特安努号巡航船\n"
    .string "现在停在枯叶市。\p"
    .string "我听说有很多训练家\n"
    .string "都会上船。\p"
    .string "他们邀请过我，\n"
    .string "不过我不习惯这种大场面。\p"
    .string "所以你能代替我去吗？\n"
    .string "去好好享受吧。$"

Route25_SeaCottage_Text_CheckOutRareMonsOnPC::
    .string "正辉：想要在我的电脑上\n"
    .string "看我珍贵的宝可梦？\p"
    .string "那就请看吧。$"

Route25_SeaCottage_Text_TeleporterIsDisplayed::
    .string "传送装置显示在\n"
    .string "电脑的屏幕上。$"

Route25_SeaCottage_Text_InitiatedTeleportersCellSeparator::
    .string "{PLAYER}启动了传送装置的\n"
    .string "细胞分离器。$"

Route25_SeaCottage_Text_BillsFavoriteMonList::
    .string "正辉的最爱的宝可梦列表！$"

Route25_SeaCottage_Text_SeeWhichMon::
    .string "你想看哪只宝可梦？$"

