.set LOCALID_ATTENDANT, 1

BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleTowerMultiPartnerRoom_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame
	.byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_OnResume:
	pyramid_resetparty
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition:
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_1
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_2
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_3
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_4
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_5
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_6
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_1
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_2
	tower_loadpartners
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_3, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_4, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_5, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_6, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_7, OBJ_EVENT_GFX_BOY_1
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_3, 1
	setobjectxyperm LOCALID_ATTENDANT, 10, 2
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp:
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom::
	lockall
	setvar VAR_TEMP_3, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom
	waitmovement 0
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit
	waitmovement 0
	copyobjectxytoperm LOCALID_ATTENDANT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner, MSGBOX_DEFAULT
	special HealPlayerParty
	setvar VAR_TEMP_1, 1
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom:
	walk_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit:
	walk_left
	walk_in_place_faster_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Attendant::
	lock
	faceplayer
	message BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge::
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator::
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 10, 1
	waitdooranim
	call BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator
	closedoor 10, 1
	waitdooranim
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_ELEVATOR, 1, 6
	waitstate
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator::
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorEast:
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorWest:
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator:
	walk_up
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast:
	walk_right
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest:
	walk_left
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner1::
	lock
	faceplayer
	setvar VAR_TEMP_2, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner::
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_INTRO
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON1
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON2_ASK
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_ACCEPT
	waitmessage
	waitbuttonpress
	closemessage
	call_if_ne VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth
	removeobject VAR_LAST_TALKED
	setflag FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_TOWER_MULTI_PARTNER_ROOM, 10, 3
	waitstate
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner::
	tower_dopartnermsg PARTNER_MSGID_REJECT
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner2::
	lock
	faceplayer
	setvar VAR_TEMP_2, 1
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner3::
	lock
	faceplayer
	setvar VAR_TEMP_2, 2
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner4::
	lock
	faceplayer
	setvar VAR_TEMP_2, 3
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner5::
	lock
	faceplayer
	setvar VAR_TEMP_2, 4
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner6::
	lock
	faceplayer
	setvar VAR_TEMP_2, 5
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner7::
	lock
	faceplayer
	setvar VAR_TEMP_2, 6
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner8::
	lock
	faceplayer
	setvar VAR_TEMP_2, 7
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner::
    .string "请在这里的训练师中\n选择一个搭档。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner::
    .string "{PLAYER}，你还没找到\n组队的搭档，\p现在你想回\n入口接待处吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2::
    .string "那么，请在这里的训练师中\n选择一个搭档。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner::
    .string "选择好搭档以后就跟我来吧，\p我带你们去\n多人对战房间。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Intro::
    .string "我是{STR_VAR_1}的第{STR_VAR_2}个徒弟。\n你可以叫我{STR_VAR_3}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon1::
    .string "按照{STR_VAR_1}的指点，我带了\n一只携带了{STR_VAR_2}的{STR_VAR_3}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon2Ask::
    .string "一只携带了{STR_VAR_1}的{STR_VAR_2}。\p请和我一起组队吧。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Accept::
    .string "谢谢你！\n我马上就去登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Reject::
    .string "我十分想\n和你组队，{PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Intro::
    .string "我是{STR_VAR_1}的第{STR_VAR_2}个徒弟。\n我叫{STR_VAR_3}。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon1::
    .string "我从{STR_VAR_1}那里得到了建议并且选择了\n一只携带了{STR_VAR_2}的{STR_VAR_3}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon2Ask::
    .string "一只携带了{STR_VAR_1}的{STR_VAR_2}。\p请和我一起组队吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Accept::
    .string "非常感谢！\n我马上就去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Reject::
    .string "{PLAYER}，我希望我能成为\n你的搭档…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Intro::
    .string "呃，我叫{STR_VAR_3}，是\n{STR_VAR_1}的第{STR_VAR_2}个徒弟。\p呜呜…\p对不起！\n我太紧张了，不小心哭了…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon1::
    .string "我听了{STR_VAR_3}的建议，\n带了有{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon2Ask::
    .string "有{STR_VAR_1}的{STR_VAR_2}。\p呜呜…\n和、和我组队吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Accept::
    .string "真、真的吗？\n太棒了！好高兴！呜～呜…\p啊…抱歉…\n我太兴奋，都哭出来了…\p我这就去登记，\n别走啊！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Reject::
    .string "啊，怎么会…\n呜…呜…呜哇啊！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Intro::
    .string "嗨！我是{STR_VAR_3}！\n也就是{STR_VAR_1}的第{STR_VAR_2}个徒弟！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon1::
    .string "{STR_VAR_3}为我推荐了一支队伍。\n我所拥有的是有{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon2Ask::
    .string "和有{STR_VAR_1}的{STR_VAR_2}。\n很棒是不是？\p那就来吧！\n我们组队吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Accept::
    .string "哈！棒极了！\n好了，我去登记，好吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Reject::
    .string "呃，为什么？\n我想跟你组队啊，{PLAYER}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Intro::
    .string "我是{STR_VAR_3}，伟大的{STR_VAR_1}\n的第{STR_VAR_2}个徒弟！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon1::
    .string "我向{STR_VAR_3}征询了一些意见。\n会{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon2Ask::
    .string "和有{STR_VAR_1}的{STR_VAR_2}\n就是我带的伙伴。\p拜托了，\n跟我组队吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Accept::
    .string "谢谢！\n我这就去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Reject::
    .string "{PLAYER}，我一直希望\n能和你组队…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Intro::
    .string "唔…你能花时间来找我\n我真的很高兴。\p我是{STR_VAR_3}，\n也就是{STR_VAR_1}的第{STR_VAR_2}个徒弟…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon1::
    .string "{STR_VAR_3}给过我一些建议，\n为此我非常感激。\p我的队伍里有一只\n会{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon2Ask::
    .string "和会{STR_VAR_1}的{STR_VAR_2}。\n我知道我的要求有点过分…\p我想你可能不愿意，\n但我真的想成为你的搭档。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Accept::
    .string "真的吗？真不敢相信！\n我真的不敢相信你会接纳我！\l我…我一定不会让你失望的！\p唔…真的可以的话，\n我这就去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Reject::
    .string "啊…\n我知道我水平还不够…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Intro::
    .string "嗨，我是{STR_VAR_3}，\n{STR_VAR_1}的第{STR_VAR_2}个徒弟！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon1::
    .string "{STR_VAR_3}告诉\n这样的队伍不错：\l用{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon2Ask::
    .string "和会{STR_VAR_1}\n的{STR_VAR_2}。\p不错的队伍，是不？\n想和我组队吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Accept::
    .string "太好了，很荣幸和你组队！\n我希望你不要拖我的后腿！\l我现在去登记一下。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Reject::
    .string "啊？为什么你要拒绝我？\n不要光看外表啊！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Intro::
    .string "我是{STR_VAR_3}，一个三项全能运动员。\n我每天都忙着\l跑步、锻炼，\p偶然之下成了{STR_VAR_1}的\n第{STR_VAR_2}个徒弟。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon1::
    .string "我用的是{STR_VAR_3}推荐的\n用{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon2Ask::
    .string "和用{STR_VAR_1}\n的{STR_VAR_2}。\p无论我有多忙，我都会\n尽最大的努力去培养他们。\p让我们组队\n横扫一切对手吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Accept::
    .string "好极了，要的就是这种精神！\n我去登记，你就在这儿等一下吧。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Reject::
    .string "我是从排得满满的日程表里挤出时间\n来这里的！别让我失望！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Intro::
    .string "嗨！\n怎么样？\p我是{STR_VAR_3}，{STR_VAR_1}的\n第{STR_VAR_2}个徒弟。很高兴见到你！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon1::
    .string "听着，听着！你有必要听听\n{STR_VAR_3}推荐的宝可梦。\l有{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon2Ask::
    .string "和{STR_VAR_1}的{STR_VAR_2}。\n当然，我的培养方式也非常完美！\p好了，组个队如何？\n我相信我们的联手一定超强！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Accept::
    .string "哈，我想这次一定会很有趣的！\n我去登记了！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Reject::
    .string "哼，真小气！\n要知道我可是经常被夸奖的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Intro::
    .string "请允许我先介绍一下自己。\n我是{STR_VAR_3}，\p也就是{STR_VAR_1}的\n第{STR_VAR_2}个徒弟。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon1::
    .string "我遵从了睿智的{STR_VAR_3}\n的建议，培养了\l有{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon2Ask::
    .string "和有{STR_VAR_1}的{STR_VAR_2}。\p请与我组队吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Accept::
    .string "哇…太高兴了！\n我保证我一定会做到最好！\p我现在就去登记！\n请稍等！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Reject::
    .string "我一直都想和你组队的，\n{PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Intro::
    .string "哇！你和我说话了！\n我…我太高兴了！\p我是{STR_VAR_3}！{STR_VAR_1}的\n第{STR_VAR_2}个徒弟！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon1::
    .string "按照{STR_VAR_3}的建议，我训练了\n会{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon2Ask::
    .string "和会{STR_VAR_1}的\n{STR_VAR_2}。\p拜托，答应我吧，\n我想成为你的搭档！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Accept::
    .string "喔！我…我兴奋地要晕倒了！\n非常感谢！\l我马上就去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Reject::
    .string "天哪！你没有一点同情心吗？\n不过你看上去更酷了…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Intro::
    .string "呀哈！我就是{STR_VAR_1}的\n第{STR_VAR_2}个弟子！\p我叫{STR_VAR_3}，你好，你好！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon1::
    .string "我的老师{STR_VAR_3}建议我用\n擅长{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon2Ask::
    .string "和擅长{STR_VAR_1}的\n{STR_VAR_2}。\p这组合不错吧？\n你会和我搭档的吧？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Accept::
    .string "好，太棒了！\n我很快就能登记好！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Reject::
    .string "切！\n你真是个斤斤计较的家伙，{PLAYER}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Intro::
    .string "嘿！我们有大麻烦了！\n明天对战塔就要关门了！\p… … … … … …\n只是开个玩笑！\p人们都叫我{STR_VAR_3}！\n{STR_VAR_1}的第一千个徒弟！\l但实际上，我是第{STR_VAR_2}个！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon1::
    .string "{STR_VAR_3}给过我一些建议，让我用\n会{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon2Ask::
    .string "和会{STR_VAR_1}的{STR_VAR_2}。\n每种我都有十只！\l呃，实际上，只是每种一只！\p如何？\n想和我组队吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Accept::
    .string "哈哈哈！\n作为感谢，我送你一只宝可梦！\p当然，是开玩笑的！那么我\n这就去登记，可以吧？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Reject::
    .string "啊，你真绝情！那就让我\n破坏掉对战塔吧！\p当然，我不是说真的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Intro::
    .string "嘿，就是你，我是个玩摇滚的说！\n宝可梦，我也能控制的说！\p我是{STR_VAR_3}一个说唱水手的说，\n别把我当成普通艺人了的说！\p我是{STR_VAR_1}的第{STR_VAR_2}个徒弟，\n哼哼，可别那么快拒绝我！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon1::
    .string "{STR_VAR_3}给的建议我照做了，\n我为我的队伍感到骄傲！\l使用{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon2Ask::
    .string "和使用{STR_VAR_1}的\n{STR_VAR_2}！\p让组队的胜利\n纪念我们的相遇！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Accept::
    .string "嘿嘿，我喜欢这样的你！\n让我现在就去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Reject::
    .string "哦呀，{PLAYER}，你真绝情！\n或许是我太唐突了！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Intro::
    .string "耶耶，呀--呼--！\n喂，别跑呀！我没病，只是自娱自乐！\p喔哈哈！我是{STR_VAR_3}！\n{STR_VAR_1}的第{STR_VAR_2}个徒弟！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon1::
    .string "{STR_VAR_3}教我怎么做，\n使用{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon2Ask::
    .string "使用{STR_VAR_1}的{STR_VAR_2}\n它们是我的选择。\p好了你觉得怎么样？\n来吧我们组个队！\p拜托就算我求你！\n我们一起向前进！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Accept::
    .string "呀哈！幸运站在我身边！\n现在的我好高兴！\p我们开始比赛前，\n还要赶快去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Reject::
    .string "这么干脆地拒绝我？\n{PLAYER}你让我很不爽！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Intro::
    .string "咳咳！\p啊，抱歉，我感冒了。\n但我的宝可梦没事。\p我的名字是{STR_VAR_3}，{STR_VAR_1}的\n第{STR_VAR_2}个徒弟。咳咳！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon1::
    .string "我把{STR_VAR_3}的建议牢牢\n记在心里了，我的队伍是\l有{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon2Ask::
    .string "有{STR_VAR_1}的{STR_VAR_2}。\p我天天都在训练他们，\n风雨无阻。\p我想就因此\n才会感冒吧。\p这就是我。\n要我做你的搭档吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Accept::
    .string "谢谢，非常感激你！\n咳咳，咳咳！\l稍等，我这就去登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Reject::
    .string "啊，你不想吗？\n{PLAYER}，我们肯定能搭档得很好的。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Intro::
    .string "你好！\n这里真是个强者云集的地方。\p我是{STR_VAR_3}，\n{STR_VAR_1}的第{STR_VAR_2}个徒弟。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon1::
    .string "{STR_VAR_3}说这样的队伍不错--\n有{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon2Ask::
    .string "有{STR_VAR_1}的{STR_VAR_2}。\p虽然有点害羞，不过，\n能让我跟你组队吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Accept::
    .string "啊呀，谢谢！\n就算有点局促，我也会尽力的！\p我这就去登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Reject::
    .string "呜，不要拒绝呀！\n我感觉已经够糟了…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Intro::
    .string "我是{STR_VAR_3}，没骗你。\n我是{STR_VAR_1}的第{STR_VAR_2}个徒弟。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon1::
    .string "{STR_VAR_3}给我推荐了一支队伍。\p他是很认真地建议我的，\n所以我听了他的话，\l带了使用{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon2Ask::
    .string "和使用{STR_VAR_1}的{STR_VAR_2}。\p如果可能的话，希望你能\n允许我成为你的搭档。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Accept::
    .string "你真的接受我这个搭档？\n还好，否则我都不知道该怎么办了。\p你同意就好。\n我去登记一下我们的信息。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Reject::
    .string "哎？你为什么拒绝我？\n是在开我玩笑吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassIntro::
    .string "我是{STR_VAR_1}，一个少女！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon1::
    .string "我有使用{STR_VAR_1}的\n{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon2Ask::
    .string "使用{STR_VAR_1}的{STR_VAR_2}，\n现在带的就是它们。\p愿意成为我的搭档吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassAccept::
    .string "谢谢！\n我这就去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassReject::
    .string "你不想做我的搭档？\n你一定会后悔的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterIntro::
    .string "嗨！\p我是少年{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon1::
    .string "想不想知道我有什么？\n有{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon2Ask::
    .string "有{STR_VAR_1}的{STR_VAR_2}！\p你肯定想成为我的搭档，\n对吧？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterAccept::
    .string "耶！\n我这就去登记，行吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterReject::
    .string "啊！如果是你和我的宝可梦\n搭档的话，我们会战无不胜的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerIntro::
    .string "呀嗬！\n我是登山者{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon1::
    .string "知道我有什么吗？\n使用{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon2Ask::
    .string "使用{STR_VAR_1}的{STR_VAR_2}！\p还不错吧？\n组个队吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerAccept::
    .string "呀嗬！\n那我这就去登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerReject::
    .string "我真的很想\n跟你并肩战斗。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyIntro::
    .string "你好！\n我是{STR_VAR_1}，一个美女！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon1::
    .string "你知道我都训练了些什么吗？\n有{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon2Ask::
    .string "有{STR_VAR_1}的{STR_VAR_2}！\p觉得怎么样？\n一起组个队如何？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyAccept::
    .string "棒极了！\n我现在就去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyReject::
    .string "太让我失望了！\p我们两个组队的话，\n一定会是最棒的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanIntro::
    .string "哟！\p知道我是谁吗？\n我就是{STR_VAR_1}，渔人！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon1::
    .string "我的队伍是\n使用{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon2Ask::
    .string "使用{STR_VAR_1}的{STR_VAR_2}。\p觉得怎样？\n要和我一起战斗吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanAccept::
    .string "好的，好的！\n交给我吧！\p我这就去登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanReject::
    .string "我们的组合会是最完美的…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyIntro::
    .string "非常高兴认识你。\n我是{STR_VAR_1}，一个女士。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon1::
    .string "陪同我的队伍是\n会{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon2Ask::
    .string "会{STR_VAR_1}的{STR_VAR_2}。\p希望我能符合你的要求。\n让我成为你的搭档吧。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyAccept::
    .string "我发自内心地感激你。\n登记的事情就交给我吧。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyReject::
    .string "我肯定你会后悔\n没有和我搭档的。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFIntro::
    .string "我是三项运动员{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon1::
    .string "我带着的是…\n会{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon2Ask::
    .string "会{STR_VAR_1}的{STR_VAR_2}！\n这就是我的队伍！\p如何？\n和我组队吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFAccept::
    .string "哈哈，谢了！\n我马上去前台登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFReject::
    .string "我们两个一起的话，\n肯定会是极强的组合！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherIntro::
    .string "嗨呀！\n我是捉虫少年{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon1::
    .string "让你看看我有什么！\n会{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon2Ask::
    .string "会{STR_VAR_1}的{STR_VAR_2}！\p所以说，\n跟我组队吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherAccept::
    .string "太棒了！\p我马上去前台\n进行登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherReject::
    .string "呃，我的宝可梦很优秀的。\n希望你不要为此后悔！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMIntro::
    .string "你好！\n我是学生{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon1::
    .string "我培养的是\n使用{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon2Ask::
    .string "和使用{STR_VAR_1}的\n{STR_VAR_2}。\p不觉得这组合不错吗？\n有没有兴趣一起组队呢？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMAccept::
    .string "非常感谢！\n让我去登记吧。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMReject::
    .string "真遗憾啊…\p我还期待做你的搭档\n跟你学习呢…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyIntro::
    .string "哟！让我告诉你我是谁！\n我就是大少爷{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon1::
    .string "猜猜看我有什么！\n会{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon2Ask::
    .string "会{STR_VAR_1}的{STR_VAR_2}！\p我就大发慈悲的给你个机会\n让你和我组个队吧。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyAccept::
    .string "很高明的决定！\p我很快就会解决\n登记的程序的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyReject::
    .string "你居然拒绝杰出的我？\n你一定会为这个决定后悔的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltIntro::
    .string "嗨！\n我是空手道达人{STR_VAR_1}。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon1::
    .string "我的伙伴是\n使用{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon2Ask::
    .string "和使用{STR_VAR_1}的\n{STR_VAR_2}。\p请满足我的愿望吧！\n让我做你的搭档吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltAccept::
    .string "哈哈！\n我立刻就去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltReject::
    .string "我明白了…希望下次见面的时候\n你还能给我个机会…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFIntro::
    .string "嗨，这里！\n我是{STR_VAR_1}，一个植树者！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon1::
    .string "告诉你我有什么吧。\n会{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon2Ask::
    .string "会{STR_VAR_1}的{STR_VAR_2}！\n我能成为你的队友吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFAccept::
    .string "谢谢！\n我马上去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFReject::
    .string "我们两个搭档的话，\n可是会变得很强的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacIntro::
    .string "你好…\n我是电脑迷{STR_VAR_1}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon1::
    .string "我拥有使用{STR_VAR_1}的\n{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon2Ask::
    .string "使用{STR_VAR_1}的{STR_VAR_2}…\p我看好你…\n我们组队…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacAccept::
    .string "谢…\n我去登记…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacReject::
    .string "我好想加入…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMIntro::
    .string "你好吗？我是{STR_VAR_1}，\n一个宝可梦饲养员！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon1::
    .string "我很细心地培养了两个伙伴！\n会{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon2Ask::
    .string "会{STR_VAR_1}的{STR_VAR_2}！\p怎么样？\n和我组队如何？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMAccept::
    .string "太感谢了！\p我马上就去登记，\n请在这里稍等！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMReject::
    .string "我本来还很期待\n能成为你的搭档的…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFIntro::
    .string "你好呀！\n我是三项全能运动员{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon1::
    .string "想知道我跟谁一起跑步吗？\n有{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon2Ask::
    .string "有{STR_VAR_1}的{STR_VAR_2}！\p怎样？\n想和我组队了吧？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFAccept::
    .string "漂亮的决定！\p我马上就去\n搞定登记的事情！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFReject::
    .string "你和我，肯定会成为冠军的。\n真可惜…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMIntro::
    .string "嗨！我是{STR_VAR_1}！\n一个三项全能运动员！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon1::
    .string "跑步的时候我会都带着同样的伙伴--\n会{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon2Ask::
    .string "会{STR_VAR_1}的{STR_VAR_2}！\p这队伍还不坏，对吧？\n我们组队肯定不错！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMAccept::
    .string "太好了！\n我一瞬间就能完成登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMReject::
    .string "我真的很想和你\n一起组队战斗…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlIntro::
    .string "我是战斗少女{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon1::
    .string "我一直在训练\n使用{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon2Ask::
    .string "使用{STR_VAR_1}的{STR_VAR_2}！\p喜欢这样的组合吗？\n那么你我就一起组队吧？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlAccept::
    .string "哇，谢谢！\p我这就去\n登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlReject::
    .string "我想，和你一起的话，\n我们会成为顶尖队伍的…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMIntro::
    .string "我是三项运动员{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon1::
    .string "我一直带着\n会使用{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon2Ask::
    .string "和会{STR_VAR_1}的{STR_VAR_2}跑步！\p我们两个组队的话，\n不是很棒么？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMAccept::
    .string "谢谢！\p我去登记，\n现在立刻就去！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMReject::
    .string "呃，真可惜。我们应该\n能成为最强的队伍的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMIntro::
    .string "我？\n我是植树者{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon1::
    .string "我有什么？\n会{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon2Ask::
    .string "会{STR_VAR_1}的{STR_VAR_2}！\p嗯？\n你会和我组队的，是吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMAccept::
    .string "好！\p我去登记！\n一起发挥我们的实力吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMReject::
    .string "我的宝可梦确实很强的…\n不和我组队真可惜啊。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristIntro::
    .string "呀-嘿！\n叫我吉他手{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon1::
    .string "我来介绍一下我的随从！\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}！\p呀-嘿！非常棒，是不是？\n让我们在队伍里继续交流吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristAccept::
    .string "呀-嘿！痛快！\n我这就去注册！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristReject::
    .string "我的宝可梦很失望！\n我告诉你，你必须要道歉！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanIntro::
    .string "很高兴见到你。\n我是{STR_VAR_1}，一个绅士。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon1::
    .string "我一直带着我信任的\n用来{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon2Ask::
    .string "一只用来{STR_VAR_1}的{STR_VAR_2}。\p我邀请你和我组一支\n二人战斗队，如何？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanAccept::
    .string "啊，谢谢你对我的信任。\n我会去注册的。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanReject::
    .string "这太不幸了…\p我只好去找下一个\n机会了…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMIntro::
    .string "你好，我是{STR_VAR_1}，\n我是一个口袋迷。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon1::
    .string "我现在有一只\n懂得{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}。\p喜欢他们吗？\n那为什么不成为我的搭档呢？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMAccept::
    .string "谢谢！\n我这就去找注册点！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMReject::
    .string "我的宝可梦是顶尖级别的…\n你竟然不懂得欣赏他们。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMIntro::
    .string "那个！\n我是{STR_VAR_1}，一个专家！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon1::
    .string "我带着的宝可梦是\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}！\p和我组个队如何？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMAccept::
    .string "那个！\n我会马上去注册的！\l让我们做到最好吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMReject::
    .string "我希望你的决定\n不会让你后悔…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFIntro::
    .string "你好，你好。\n我是{STR_VAR_1}，一个专家。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon1::
    .string "我十分的热爱宝可梦。\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}--\n这就是我拥有的。\p你难道不想和我组一个队吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFAccept::
    .string "好，太好了。\n我马上就到组册点去。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFReject::
    .string "希望在我们下一次见面的时候\n你会回心转意。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerIntro::
    .string "我是驯龙员{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon1::
    .string "我一直训练的队伍是\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}！\p如何？\n和我搭档怎么样？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerAccept::
    .string "好极，我一定会做到最好的！\n这就去注册，没问题吧？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerReject::
    .string "你不会找到比我再好的\n搭档了！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperIntro::
    .string "我是操鸟者{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon1::
    .string "我有什么宝可梦？\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}。\p你不觉得我们能构成一支\n像样的队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperAccept::
    .string "太好了，谢谢！\n我马上去找注册点！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperReject::
    .string "我的宝可梦和我都很强。\n太让人失望了。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyIntro::
    .string "我是忍者儿童{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon1::
    .string "我的宝可梦队伍由\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}构成！\p让我们组一支队伍吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyAccept::
    .string "耶！\n我去注册！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyReject::
    .string "你会后悔没有接受\n我强大的宝可梦！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyIntro::
    .string "你好！\n我是阳伞大姐{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon1::
    .string "现在守护着我的是我的\n用来{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon2Ask::
    .string "用来{STR_VAR_1}\n的{STR_VAR_2}。\p他们漂亮吧？\n想和我们合作吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyAccept::
    .string "真是太谢谢你了！\p我去注册点注册一下。\n我们都不要让彼此失望喔！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyReject::
    .string "我的宝可梦是很强的。\n太失望了呀…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacIntro::
    .string "你好。\n我是{STR_VAR_1}，一个昆虫迷！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon1::
    .string "我也有宝可梦，没错。\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}--\n这就是我拥有的。\p那么有没有兴趣\n组一个队呢？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacAccept::
    .string "好极了！\n了解！\p我不会用太多时间去注册的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacReject::
    .string "和我找到的宝可梦一起，我们\n不可能输的…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorIntro::
    .string "喂，这里呀！\n我是水手{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon1::
    .string "这是让我快乐和骄傲的宝贝们！\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}！\p当然你不会让我失望的\n我们会组成一个队的，对吧？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorAccept::
    .string "这简直太出乎我的意料了！\n我现在就去注册。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorReject::
    .string "我本来不想暴风雨般的\n击败敌人的！太糟了！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorIntro::
    .string "嗨，我是{STR_VAR_1}。\n我是收藏家。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon1::
    .string "我收集的宝贝是\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}！\p很有气势，是不是？\n我们应该组一个队的。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorAccept::
    .string "太棒啦！\p好的，那就不要浪费时间了。\n我这就去帮我们注册。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorReject::
    .string "呃，这真让人心烦。\n你竟然不赏识我的宝可梦。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMIntro::
    .string "你好，我是{STR_VAR_1}。\n一个宝可梦护林员。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon1::
    .string "守护我的伙伴是一只\n用来{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}！\p你不认为我们我们能构成\n一支令人印象深刻的队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMAccept::
    .string "太好了！\n我马上就去解决注册问题。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMReject::
    .string "下一次，你会选择我的宝可梦的，\n是吧？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFIntro::
    .string "我的名字是{STR_VAR_1}。\n一个宝可梦护林员！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon1::
    .string "让你了解一下我的队伍。我有\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}！\p那么，你想不想\n加入我的小组？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFAccept::
    .string "我们都要做到最好！\n我会很快去注的册！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFReject::
    .string "我多希望下一次\n你会选择我的宝可梦。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyIntro::
    .string "很高兴见到你。我是{STR_VAR_1}。\n我自认为我是一个芬香女士。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon1::
    .string "我带着一只用来{STR_VAR_1}\n的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon2Ask::
    .string "一只用来{STR_VAR_1}的{STR_VAR_2}\n到处旅行。\p希望你会喜欢他们。\n你想成为我的搭档吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyAccept::
    .string "我尊敬你的决断。\n刻不容缓，我这就去注册。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyReject::
    .string "没关系，我们下次再组队\n那也是非常美好的。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacIntro::
    .string "想知道我是谁吗？\n我是{STR_VAR_1}，一个遗迹迷！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon1::
    .string "我拥有的宝可梦是\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}！\p很迷人，是吧？\n你和我，组个队如何？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacAccept::
    .string "合理的决断！\n我这就去填注册申请表。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacReject::
    .string "嗯…\n我认为我的宝可梦很强的…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMIntro::
    .string "我是帅气的训练师{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon1::
    .string "我现在有的宝可梦是\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}。\n酷，是不是？\p你不觉得如果我们组队\n他们会变得更酷吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMAccept::
    .string "酷！\n看我瞬间就搞定注册项目！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMReject::
    .string "我觉得我们能组成一支\n最强的队伍的。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFIntro::
    .string "我是帅气的训练师{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon1::
    .string "我的队伍里有\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}。\p听起来很棒吧？\n我们组成一支队伍如何？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFAccept::
    .string "听起来好极了！\n我最好现在就去注册。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFReject::
    .string "我一直在想\n怎样才能建一支坚韧的队伍…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacIntro::
    .string "嘿！\n我是{STR_VAR_1}，口袋迷！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon1::
    .string "像我这样的人应该有什么呢？\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}，\n就是他们！\p无所不能！\n我们组了队一定会威震八方的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacAccept::
    .string "说得好！\n这就去注册我们两个！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacReject::
    .string "我的宝可梦是无敌的！\n你可不要后悔！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerIntro::
    .string "你好！\n我是操火者{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon1::
    .string "你知道我训练了一支什么队伍吗？\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}！\p你想说什么？\n想和我组队吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerAccept::
    .string "好极了！\n我马上去注册点。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerReject::
    .string "好吧，我允许你再考虑\n直到我们下次见面。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperIntro::
    .string "我是{STR_VAR_1}，一个野营者！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon1::
    .string "我有一只用来{STR_VAR_1}的\n{STR_VAR_2}和一只$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon2Ask::
    .string "用来{STR_VAR_1}的{STR_VAR_2}。\p你不觉得和我组队会很有趣吗？\n我打赌一定会！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperAccept::
    .string "耶！\n我会抽空去注册的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperReject::
    .string "下一次吧，好吗？\n我真的很想成为你的队友。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerIntro::
    .string "你好！\n我是{STR_VAR_1}，一个野餐者！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon1::
    .string "我带着的宝可梦是\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}。\p你有没有兴趣\n和我组一支队伍呢？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerAccept::
    .string "哇，谢谢！\n我现在就去注册。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerReject::
    .string "今后还有机会，我会努力\n加入你的。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMIntro::
    .string "我是超能力者{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon1::
    .string "我训练的两个伙伴是\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}。\p你想和我\n组个队吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMAccept::
    .string "理所当然！\n我会马上去注册的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMReject::
    .string "如果我们下次还能见面，我依然\n希望加入你。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFIntro::
    .string "我是{STR_VAR_1}。\n一个超能力者。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon1::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}--\n这就是我的伙伴。\p建一支二人战斗组，\n你觉得如何？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFAccept::
    .string "谢谢。\n接下来的申请就交给我了。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFReject::
    .string "我希望下一次\n我们还有机会。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFIntro::
    .string "我是小学生{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon1::
    .string "一只用来{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon2Ask::
    .string "和一只用来{STR_VAR_1}的\n{STR_VAR_2}就是我的宝可梦搭档。\p我能成为你的\n战斗伙伴吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFAccept::
    .string "哇，谢谢！\n我现在就去注册台！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFReject::
    .string "哎？那么，\n下一次我能加入你吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFIntro::
    .string "你好！{STR_VAR_1}是我的名字！\n我是一个宝可梦饲养员！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon1::
    .string "我有的宝可梦是一只\n用来{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon2Ask::
    .string "一只用来{STR_VAR_1}的{STR_VAR_2}。\p听起来不错吧？\n接下来，我们组个队如何？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFAccept::
    .string "太好了！\n请允许我这就去注册！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFReject::
    .string "下一次你会答应我的，\n对吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFIntro::
    .string "我是{STR_VAR_1}，我可以很自豪的\n说我是一个口袋迷。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon1::
    .string "我心爱的宝可梦是\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}。\p他们很聪明伶俐吧？\n我们应该组一支队伍！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFAccept::
    .string "谢谢，亲爱的！\n我这就注册去！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFReject::
    .string "我心爱的宝可梦是最棒的，\n我会让你知道。真恼火！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFIntro::
    .string "嗨，我是游泳者{STR_VAR_1}。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon1::
    .string "一只用来{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon2Ask::
    .string "和一只用来{STR_VAR_1}的\n{STR_VAR_2}是我的旅行伙伴。\p你和我，让我们组一支队伍吧。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFAccept::
    .string "那太酷了！\n我这就去注册。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFReject::
    .string "下次见面时，你一定要\n让我加入你！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMIntro::
    .string "怎么了？\n我是{STR_VAR_1}，一个三项全能运动员。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon1::
    .string "我有一对高贵的宝可梦。\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}！\p如果我们组队，那是多高雅的\n一件事呀，你觉得呢？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMAccept::
    .string "太好了！\n你等我去注册一下，好不好？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMReject::
    .string "那么下一次见面的时候\n请让我加入你，好不好？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFIntro::
    .string "我是三项全能运动员{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon1::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon2Ask::
    .string "另一只懂得如何使用{STR_VAR_1}\n的{STR_VAR_2}。这就是我的搭档。\p你觉得如何？\n我们一定能组成一直很好的队伍，我这么觉得。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFAccept::
    .string "我喜欢这个答案！\n我会很快去注册的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFReject::
    .string "下一次你还会给我一个机会的，\n是不是？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMIntro::
    .string "嘿！你好！\n我是{STR_VAR_1}，一个游泳者！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon1::
    .string "给你看看我的队伍吧！\n一只带着{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon2Ask::
    .string "一只带着{STR_VAR_1}的{STR_VAR_2}！\p不错，是不是？\n我很想和你组个队的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMAccept::
    .string "太棒了！\n我马上就去注册！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMReject::
    .string "如果我们再见面，你会和我组队的\n你会的，对吧？$"

