CeladonCity_Restaurant_Frlg_MapScripts::
	.byte 0

CeladonCity_Restaurant_EventScript_Chef::
	msgbox CeladonCity_Restaurant_Text_TakingBreakRightNow, MSGBOX_NPC
	end

CeladonCity_Restaurant_EventScript_Woman::
	msgbox CeladonCity_Restaurant_Text_OftenGoToDrugstore, MSGBOX_NPC
	end

CeladonCity_Restaurant_EventScript_CoinCaseMan::
	lock
	faceplayer
	goto_if_set FLAG_GOT_COIN_CASE, CeladonCity_Restaurant_EventScript_AlreadyGotCoinCase
	msgbox CeladonCity_Restaurant_Text_TakeThisImBusted
	checkitemspace ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, CeladonCity_Restaurant_EventScript_NoRoomForCoinCase
	giveitem_msg CeladonCity_Restaurant_Text_ReceivedCoinCaseFromMan, ITEM_COIN_CASE
	setflag FLAG_GOT_COIN_CASE
	release
	end

CeladonCity_Restaurant_EventScript_NoRoomForCoinCase::
	msgbox CeladonCity_Restaurant_Text_MakeRoomForThis
	release
	end

CeladonCity_Restaurant_EventScript_AlreadyGotCoinCase::
	msgbox CeladonCity_Restaurant_Text_ThoughtIdWinItBack
	release
	end

CeladonCity_Restaurant_EventScript_WorkerM::
	msgbox CeladonCity_Restaurant_Text_PsstBasementUnderGameCorner, MSGBOX_NPC
	end

CeladonCity_Restaurant_EventScript_FatMan::
	msgbox CeladonCity_Restaurant_Text_ManLostItAllAtSlots, MSGBOX_NPC
	end

CeladonCity_Restaurant_Text_TakingBreakRightNow::
    .string "嗨！\p"
    .string "抱歉，我们正在休息呢。$"

CeladonCity_Restaurant_Text_OftenGoToDrugstore::
    .string "我的宝可梦比较弱，\n"
    .string "所以我常去药店。$"

CeladonCity_Restaurant_Text_PsstBasementUnderGameCorner::
    .string "嘿！我听说这个\n"
    .string "游戏厅下面有个地下室。$"

CeladonCity_Restaurant_Text_ManLostItAllAtSlots::
    .string "吧唧吧唧……\p"
    .string "那边桌子上那个人，\n"
    .string "把家当全输在老虎机上了。$"

CeladonCity_Restaurant_Text_TakeThisImBusted::
    .string "去吧！哈哈！\n"
    .string "我破产了！\p"
    .string "没法再玩老虎机了！\n"
    .string "我要走了！\p"
    .string "给你！\n"
    .string "我再也用不着它了！$"

CeladonCity_Restaurant_Text_ReceivedCoinCaseFromMan::
    .string "{PLAYER}获得了一个代币盒。$"

CeladonCity_Restaurant_Text_MakeRoomForThis::
    .string "把包包腾出点地方来！$"

CeladonCity_Restaurant_Text_ThoughtIdWinItBack::
    .string "我总想着\n"
    .string "要把输的都赢回来……$"

