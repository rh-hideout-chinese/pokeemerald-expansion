.set LOCALID_DOCK, 1

SlateportCity_SternsShipyard_1F_MapScripts::
	.byte 0

SlateportCity_SternsShipyard_1F_EventScript_Dock::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_SternsShipyard_1F_EventScript_FerryReady
	goto_if_set FLAG_BADGE07_GET, SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined
	goto_if_set FLAG_DELIVERED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_GoFindStern
	msgbox SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails, MSGBOX_DEFAULT
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_DOCK_REJECTED_DEVON_GOODS
	setflag FLAG_HIDE_SLATEPORT_CITY_TEAM_AQUA
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_FerryReady::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_FerryIsReady, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_GoFindStern::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist1::
	msgbox SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist2::
	msgbox SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Briney::
	msgbox SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails:
    .string "唔…如果这个向这边，\n那个去那边…\p那么这个怎么办？\n那个装置怎么办？\p啊啊啊！\n我都想糊涂了！$"

SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern:
    .string "嗯？\n你好，我是多克。\p库斯诺吉馆长雇我来\n设计游船。\p啊！那个…\n那是得文的包裹吗？\p但是，唔…\n这不太…\p库斯诺吉馆长出去了，\n他说有些事要做。\p可以请你去找找库斯诺吉馆长，\n把东西交给他吗？$"

SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern:
    .string "多克：库斯诺吉馆长\n去哪儿了？\p可以请你去找找库斯诺吉馆长，\n把包裹交给他吗？$"

SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran:
    .string "多克：造船是一门艺术，\p很多东西并不是\n只靠计算就能够知道的。\p我该去向了解大海的\n老水手们请教一下…$"

SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs:
    .string "多克：嗨！哈奇\n也来帮我们的忙了。\p多亏了这位老水手，\n游船的组装正在顺利进行中。$"

SlateportCity_SternsShipyard_1F_Text_FerryIsReady:
    .string "多克：游船终于造好了！\p这崭新的破浪号是\n工业技术的奇迹！\p但我觉得我们\n能做得更好。\p要知道，技术的进步\n永远不会停止。$"

SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock:
    .string "哈奇：啊，{PLAYER}{KUN}！\n好久不见！\p哈，自从我见到你，你一直\n让我这老海员特别快乐！\p所以我决定来\n帮多克造游船。\p毕竟，游船上\n能载很多人。\p那个多克\n也不简单。\p有他的技术和我的经验，\n我敢肯定我们能造出\l世界最棒的船来！哈哈！$"

SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing:
    .string "季节，天气，\n月亮在天空中的位置…\p这些，还有其他很多东西\n都会对大海产生影响。\p是的！\n大海就好像生物一样！$"

SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily:
    .string "我很容易晕船，\n所以我只能到这儿来帮忙。$"

