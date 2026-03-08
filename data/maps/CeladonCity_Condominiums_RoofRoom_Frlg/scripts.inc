CeladonCity_Condominiums_RoofRoom_Frlg_MapScripts::
	.byte 0

CeladonCity_Condominiums_RoofRoom_EventScript_BlackBelt::
	msgbox CeladonCity_Condominiums_RoofRoom_Text_TheresNothingIDontKnow, MSGBOX_NPC
	end

CeladonCity_Condominiums_RoofRoom_EventScript_EeveeBall::
	lock
	faceplayer
	setvar VAR_TEMP_1, SPECIES_EEVEE
	givemon SPECIES_EEVEE, 25
	goto_if_eq VAR_RESULT, 0, CeladonCity_Condominiums_RoofRoom_EventScript_GetEeveeParty
	goto_if_eq VAR_RESULT, 1, CeladonCity_Condominiums_RoofRoom_EventScript_GetEeveePC
	goto_if_eq VAR_RESULT, 2, Common_EventScript_NoMoreRoomForPokemon
	release
	end

CeladonCity_Condominiums_RoofRoom_EventScript_GetEeveeParty::
	removeobject LOCALID_EEVEE_POKEBALL
	playfanfare MUS_LEVEL_UP
	message CeladonCity_Condominiums_RoofRoom_Text_ObtainedAnEevee
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_EEVEE
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CeladonCity_Condominiums_RoofRoom_EventScript_SetGotEevee
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto CeladonCity_Condominiums_RoofRoom_EventScript_SetGotEevee
	end

CeladonCity_Condominiums_RoofRoom_EventScript_GetEeveePC::
	removeobject LOCALID_EEVEE_POKEBALL
	playfanfare MUS_LEVEL_UP
	message CeladonCity_Condominiums_RoofRoom_Text_ObtainedAnEevee
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_EEVEE
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CeladonCity_Condominiums_RoofRoom_EventScript_TransferEeveeToPC
	call Common_EventScript_NameReceivedBoxMon
	goto CeladonCity_Condominiums_RoofRoom_EventScript_TransferEeveeToPC
	end

CeladonCity_Condominiums_RoofRoom_EventScript_TransferEeveeToPC::
	call Common_EventScript_TransferredToPC
	goto CeladonCity_Condominiums_RoofRoom_EventScript_SetGotEevee
	end

CeladonCity_Condominiums_RoofRoom_EventScript_SetGotEevee::
	setflag FLAG_GOT_EEVEE
	release
	end

CeladonCity_Condominiums_RoofRoom_EventScript_TMsPamphlet::
	msgbox CeladonCity_Condominiums_RoofRoom_Text_PamphletOnTMs, MSGBOX_SIGN
	end

CeladonCity_Condominiums_RoofRoom_EventScript_Blackboard::
	lockall
	msgbox CeladonCity_Condominiums_RoofRoom_Text_WirelessAdapterLecture
	message CeladonCity_Condominiums_RoofRoom_Text_ReadWhichHeading
	waitmessage
	setvar VAR_0x8004, 4
	multichoice 0, 0, MULTI_LINKED_DIRECT_UNION, FALSE
	switch VAR_RESULT
	case 0, CeladonCity_Condominiums_RoofRoom_EventScript_WirelessClub
	case 1, CeladonCity_Condominiums_RoofRoom_EventScript_DirectCorner
	case 2, CeladonCity_Condominiums_RoofRoom_EventScript_UnionRoom
	case 3, CeladonCity_Condominiums_RoofRoom_EventScript_ExitBlackboard
	case 127, CeladonCity_Condominiums_RoofRoom_EventScript_ExitBlackboard
	end

CeladonCity_Condominiums_RoofRoom_EventScript_ReadAnotherHeading::
	message CeladonCity_Condominiums_RoofRoom_Text_ReadWhichHeading
	waitmessage
	multichoice 0, 0, MULTI_LINKED_DIRECT_UNION, FALSE
	switch VAR_RESULT
	case 0, CeladonCity_Condominiums_RoofRoom_EventScript_WirelessClub
	case 1, CeladonCity_Condominiums_RoofRoom_EventScript_DirectCorner
	case 2, CeladonCity_Condominiums_RoofRoom_EventScript_UnionRoom
	case 3, CeladonCity_Condominiums_RoofRoom_EventScript_ExitBlackboard
	case 127, CeladonCity_Condominiums_RoofRoom_EventScript_ExitBlackboard
	end

CeladonCity_Condominiums_RoofRoom_EventScript_WirelessClub::
	msgbox CeladonCity_Condominiums_RoofRoom_Text_ExplainWirelessClub
	goto CeladonCity_Condominiums_RoofRoom_EventScript_ReadAnotherHeading
	end

CeladonCity_Condominiums_RoofRoom_EventScript_DirectCorner::
	msgbox CeladonCity_Condominiums_RoofRoom_Text_ExplainDirectCorner
	goto CeladonCity_Condominiums_RoofRoom_EventScript_ReadAnotherHeading
	end

CeladonCity_Condominiums_RoofRoom_EventScript_UnionRoom::
	msgbox CeladonCity_Condominiums_RoofRoom_Text_ExplainUnionRoom
	goto CeladonCity_Condominiums_RoofRoom_EventScript_ReadAnotherHeading
	end

CeladonCity_Condominiums_RoofRoom_EventScript_ExitBlackboard::
	releaseall
	end

CeladonCity_Condominiums_RoofRoom_Text_TheresNothingIDontKnow::
    .string "就像我在黑板上写的那样，\n"
    .string "我无所不知。\p"
    .string "我了解在GAME BOY ADVANCE中的\n"
    .string "宝可梦世界！\p"
    .string "和你的朋友们一起玩吧，\n"
    .string "祝你们交换宝可梦愉快！$"

CeladonCity_Condominiums_RoofRoom_Text_ObtainedAnEevee::
    .string "{PLAYER}获得了伊布！$"

CeladonCity_Condominiums_RoofRoom_Text_BoxIsFull::
	.string "ポケモンが　いっぱいだ\n"
	.string "ボックスを　かえて　きなさい$"

CeladonCity_Condominiums_RoofRoom_Text_WirelessAdapterLecture::
    .string "宝可梦讲座\p"
    .string "用无线适配器游戏$"

CeladonCity_Condominiums_RoofRoom_Text_ReadWhichHeading::
    .string "你想了解哪部分？$"

CeladonCity_Condominiums_RoofRoom_Text_ExplainWirelessClub::
    .string "宝可梦无线俱乐部\n"
    .string "在宝可梦中心的上层。\p"
    .string "去那里通过无线适配器\n"
    .string "和你的朋友通讯。$"

CeladonCity_Condominiums_RoofRoom_Text_ExplainDirectCorner::
    .string "和单个朋友通讯，\n"
    .string "就去直连房间。\p"
    .string "宝可梦无线俱乐部右边的柜台就是。\p"
    .string "和你的朋友一起进入\n"
    .string "通信房间或者大竞技场。$"

CeladonCity_Condominiums_RoofRoom_Text_ExplainUnionRoom::
    .string "如果要和任意其他人通讯，\n"
    .string "就去联合房间。\p"
    .string "宝可梦无线俱乐部左边的柜台就是。\p"
    .string "去联合房间尽情享受和其他训练家\n"
    .string "通讯的乐趣吧！$"

CeladonCity_Condominiums_RoofRoom_Text_PamphletOnTMs::
    .string "是本关于技能学习机的小册子。\p"
    .string "…… ……\p"
    .string "一共有50种技能机器。\p"
    .string "还有7种能反复使用的秘传机器。\p"
    .string "西尔佛公司。$"

