.set LOCALID_ROOT_FOSSIL, 1
.set LOCALID_CLAW_FOSSIL, 2

MirageTower_4F_MapScripts::
	.byte 0

MirageTower_4F_EventScript_RootFossil::
	lock
	faceplayer
	msgbox MirageTower_4F_Text_TakeRootFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MirageTower_4F_EventScript_LeaveRootFossil
	giveitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	setflag FLAG_HIDE_MIRAGE_TOWER_ROOT_FOSSIL
	setflag FLAG_HIDE_MIRAGE_TOWER_CLAW_FOSSIL
	removeobject LOCALID_ROOT_FOSSIL
	delay 30
	setflag FLAG_CHOSE_ROOT_FOSSIL
	goto MirageTower_4F_EventScript_CollapseMirageTower
	end

MirageTower_4F_EventScript_LeaveRootFossil::
	msgbox MirageTower_4F_Text_LeftRootFossilAlone, MSGBOX_DEFAULT
	release
	end

MirageTower_4F_EventScript_ClawFossil::
	lock
	faceplayer
	msgbox MirageTower_4F_Text_TakeClawFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MirageTower_4F_EventScript_LeaveClawFossil
	giveitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	setflag FLAG_HIDE_MIRAGE_TOWER_CLAW_FOSSIL
	setflag FLAG_HIDE_MIRAGE_TOWER_ROOT_FOSSIL
	removeobject LOCALID_CLAW_FOSSIL
	delay 30
	setflag FLAG_CHOSE_CLAW_FOSSIL
	goto MirageTower_4F_EventScript_CollapseMirageTower
	end

MirageTower_4F_EventScript_LeaveClawFossil::
	msgbox MirageTower_4F_Text_LeaveClawFossilAlone, MSGBOX_DEFAULT
	release
	end

MirageTower_4F_EventScript_CollapseMirageTower::
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 1   @ horizontal pan
	setvar VAR_0x8006, 32  @ num shakes
	setvar VAR_0x8007, 2   @ shake delay
	special ShakeCamera
	waitstate
	special DoMirageTowerCeilingCrumble
	waitstate
	setvar VAR_MIRAGE_TOWER_STATE, 1
	clearflag FLAG_LANDMARK_MIRAGE_TOWER
	warp MAP_ROUTE111, 19, 59
	waitstate
	release
	end

MirageTower_4F_Text_TakeRootFossil:
    .string "你发现了根状化石。\p如果拿走化石，周围的\n地面很可能会塌陷…\p真的要拿走根状化石吗？$"

MirageTower_4F_Text_LeftRootFossilAlone:
    .string "{PLAYER}留下了根状化石。$"

MirageTower_4F_Text_TakeClawFossil:
    .string "你发现了爪子化石。\p如果拿走化石，周围的\n地面很可能会塌陷…\p真的要拿走爪子化石吗？$"

MirageTower_4F_Text_LeaveClawFossilAlone:
    .string "{PLAYER}留下了爪子化石。$"

