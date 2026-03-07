ApricornTreeScript::
	lock
	faceplayer
	message ApricornTree_Text_Intro
	waitmessage
	special ObjectEventInteractionGetApricornTreeData
	goto_if_gt VAR_0x8005, 0, ApricornTree_EventScript_WantToPick
	message ApricornTree_Text_Empty
	waitmessage
	waitbuttonpress
	release
	end

ApricornTree_EventScript_WantToPick::
	buffernumberstring STR_VAR_2, VAR_0x8005
	msgbox ApricornTree_Text_WantToPick, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, ApricornTree_EventScript_PickApricorn
	goto_if_eq VAR_RESULT, NO, ApricornTree_EventScript_CancelPickingApricorn

.set APRICORN_NORMAL_BAG_FULL, 0
.set APRICORN_NORMAL_SPACE_IN_BAG, 1

ApricornTree_EventScript_PickApricorn::
	special ObjectEventInteractionPickApricornTree
	call EventScript_BufferPocketNameAndTryFanfare
	goto_if_eq VAR_0x8006, APRICORN_NORMAL_BAG_FULL, ApricornTree_EventScript_PocketFull
	message ApricornTree_Text_PickedTheApricorn
.if OW_SHOW_ITEM_DESCRIPTIONS != OW_ITEM_DESCRIPTIONS_OFF
	copyvar VAR_0x8006 VAR_0x8004
.endif
	delay 10
.if OW_SHOW_ITEM_DESCRIPTIONS != OW_ITEM_DESCRIPTIONS_OFF
	showberrydescription
.endif
	playfanfare MUS_OBTAIN_BERRY
	waitmessage
	waitfanfare
	waitbuttonpress
	message ApricornTree_Text_PutAwayApricorn
	waitmessage
	waitbuttonpress
.if OW_SHOW_ITEM_DESCRIPTIONS != OW_ITEM_DESCRIPTIONS_OFF
	hideitemdescription
.endif
	release
	end

ApricornTree_EventScript_PocketFull::
	message ApricornTree_Text_PocketFull
	waitmessage
	waitbuttonpress
	release
	end

ApricornTree_EventScript_CancelPickingApricorn::
	message ApricornTree_Text_ApricornLeftUnpicked
	waitmessage
	waitbuttonpress
	release
	end

ApricornTree_Text_Intro:
	.string "是一棵球果树！$"

ApricornTree_Text_Empty:
	.string "树上没有球果……$"

ApricornTree_Text_WantToPick:
	.string "……是{STR_VAR_2}{STR_VAR_1}！\p"
	.string "要摘下这颗\n"
	.string "{STR_VAR_1}吗？$"

ApricornTree_Text_PickedTheApricorn:
	.string "{PLAYER}获得了\n"
	.string "{STR_VAR_2}{STR_VAR_1}。$"

ApricornTree_Text_PutAwayApricorn:
	.string "{PLAYER}将{STR_VAR_1}\n"
	.string "放入了背包的\l"
	.string "{STR_VAR_3}口袋。$"

ApricornTree_Text_PocketFull:
	.string "背包的{STR_VAR_3}口袋已经满了。\p"
	.string "{PLAYER}只好放弃了\p"
	.string "{STR_VAR_1}……$"

ApricornTree_Text_ApricornLeftUnpicked:
	.string "{PLAYER}放弃了\p"
	.string "{STR_VAR_1}……$"
