SootopolisCity_House6_MapScripts::
	.byte 0

SootopolisCity_House6_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_WAILMER_DOLL, SootopolisCity_House6_EventScript_ReceivedWailmerDoll
	msgbox SootopolisCity_House6_Text_FirstGuestInWhileTakeDoll, MSGBOX_YESNO
	call_if_eq VAR_RESULT, NO, SootopolisCity_House6_EventScript_DeclineWailmerDoll
	msgbox SootopolisCity_House6_Text_TakeGoodCareOfIt, MSGBOX_DEFAULT
	givedecoration DECOR_WAILMER_DOLL
	goto_if_eq VAR_RESULT, FALSE, SootopolisCity_House6_EventScript_NoRoomForWailmerDoll
	setflag FLAG_RECEIVED_WAILMER_DOLL
	release
	end

SootopolisCity_House6_EventScript_DeclineWailmerDoll::
	msgbox SootopolisCity_House6_Text_DontWantThisDoll, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House6_EventScript_ReceivedWailmerDoll::
	msgbox SootopolisCity_House6_Text_LovePlushDolls, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House6_EventScript_NoRoomForWailmerDoll::
	bufferdecorationname STR_VAR_2, DECOR_WAILMER_DOLL
	msgbox gText_NoRoomLeftForAnother, MSGBOX_DEFAULT
	msgbox SootopolisCity_House6_Text_IllHoldItForYou, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House6_Text_FirstGuestInWhileTakeDoll:
    .string "你好！你是我们\n第一个客人，\p你照亮了我的一天，\n这个大吼吼鲸玩偶送给你。$"

SootopolisCity_House6_Text_TakeGoodCareOfIt:
    .string "要保存好它！$"

SootopolisCity_House6_Text_IllHoldItForYou:
    .string "嗯？你想要，但现在还不能拿？\n那好，我先替你保管。$"

SootopolisCity_House6_Text_DontWantThisDoll:
    .string "你肯定吗？\n不想要这个玩偶？$"

SootopolisCity_House6_Text_LovePlushDolls:
    .string "我喜欢毛绒玩偶！$"

