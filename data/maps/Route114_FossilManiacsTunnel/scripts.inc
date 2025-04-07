.set LOCALID_FOSSIL_MANIAC, 1

Route114_FossilManiacsTunnel_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsTunnel_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route114_FossilManiacsTunnel_OnLoad
	.byte 0

Route114_FossilManiacsTunnel_OnTransition:
	call_if_set FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac
	end

Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac::
	setobjectxyperm LOCALID_FOSSIL_MANIAC, 6, 5
	setobjectmovementtype LOCALID_FOSSIL_MANIAC, MOVEMENT_TYPE_FACE_DOWN
	return

Route114_FossilManiacsTunnel_OnLoad:
	call_if_unset FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass
	end

Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass::
	setmetatile 6, 1, METATILE_Fallarbor_RedRockWall, TRUE
	setmetatile 6, 2, METATILE_Fallarbor_RedRockWall, TRUE
	return

Route114_FossilManiacsTunnel_EventScript_ManiacMentionCaveIn::
	lockall
	applymovement LOCALID_FOSSIL_MANIAC, Common_Movement_WalkInPlaceFasterUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox Route114_FossilManiacsTunnel_Text_NotSafeThatWay, MSGBOX_DEFAULT
	setvar VAR_FOSSIL_MANIAC_STATE, 2
	releaseall
	end

Route114_FossilManiacsTunnel_EventScript_FossilManiac::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_REVIVED_FOSSIL_MON, Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil
	msgbox Route114_FossilManiacsTunnel_Text_LookInDesertForFossils, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil::
	msgbox Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil::
	msgbox Route114_FossilManiacsTunnel_Text_FossilsAreWonderful, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_Text_LookInDesertForFossils:
    .string "我是化石迷…\n我是喜欢化石的好人…\p你想要化石？\p但是这里所有的化石\n全部属于我…不能给你…\p如果你也需要化石\n去沙漠里找找吧\l那里到处是沙砾\l也许会藏着化石…$"

Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils:
    .string "难道说你找到了化石？\n太好了…不会是做梦吧…\p你想对那个化石\n做什么？\p我听说，得文正在做研究\n把宝可梦从\l化石中复活…\p我喜欢我的化石，因此\n我不喜欢那样做…$"

Route114_FossilManiacsTunnel_Text_FossilsAreWonderful:
    .string "化石是那么的…迷人…\n它是那么完美…$"

Route114_FossilManiacsTunnel_Text_NotSafeThatWay:
    .string "哦…\n那条路不安全…\p你看到了，当所有墙壁倒塌时…\n我正要挖洞离开…\p我认为现在下面\n有一个巨大的洞…\p但是我要走了\n因为我认为那里没有化石…$"

