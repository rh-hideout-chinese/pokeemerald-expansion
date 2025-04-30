.set LOCALID_GROUDON, 1
.set LOCALID_GRUNT_1, 2
.set LOCALID_GRUNT_2, 3
.set LOCALID_GRUNT_3, 4
.set LOCALID_TABITHA, 5
.set LOCALID_MAXIE, 6
.set LOCALID_GROUDON_SLEEPING, 7

MagmaHideout_4F_MapScripts::
	.byte 0

MagmaHideout_4F_EventScript_Maxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MagmaHideout_4F_Text_MaxieAwakenGroudon, MSGBOX_DEFAULT
	closemessage
	delay 20
	setvar VAR_RESULT, 1
	playse SE_M_DETECT
	dofieldeffectsparkle 18, 42, 0
	waitfieldeffect FLDEFF_SPARKLE
	setvar VAR_RESULT, 1
	playfanfare MUS_AWAKEN_LEGEND
	playse SE_ORB
	special DoOrbEffect
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 150
	removeobject LOCALID_GROUDON_SLEEPING
	addobject LOCALID_GROUDON
	waitstate
	delay 60
	applymovement LOCALID_GROUDON, MagmaHideout_4F_Movement_GroudonApproach
	waitmovement 0
	special FadeOutOrbEffect
	waitstate
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_GROUDON, MagmaHideout_4F_Movement_GroudonExit
	waitmovement 0
	removeobject LOCALID_GROUDON
	delay 4
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	delay 30
	applymovement LOCALID_MAXIE, MagmaHideout_4F_Movement_MaxieLookAround
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieGroudonWhatsWrong, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieOhItWasYou, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_MAXIE_MAGMA_HIDEOUT, MagmaHideout_4F_Text_MaxieDefeat
	msgbox MagmaHideout_4F_Text_MaxieImGoingAfterGroudon, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_SLATEPORT_CITY_CAPTAIN_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_GABBY_AND_TY
	setvar VAR_SLATEPORT_CITY_STATE, 1
	setflag FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT
	setvar VAR_SLATEPORT_HARBOR_STATE, 1
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAXIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_TABITHA
	setflag FLAG_HIDE_MAGMA_HIDEOUT_GRUNTS
	fadescreen FADE_FROM_BLACK
	releaseall
	end

MagmaHideout_4F_Movement_GroudonApproach:
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	step_end

MagmaHideout_4F_Movement_GroudonExit:
	slide_up
	slide_up
	step_end

MagmaHideout_4F_Movement_MaxieLookAround:
	face_left
	delay_16
	face_right
	delay_16
	face_left
	delay_16
	face_right
	delay_16
	face_up
	delay_16
	delay_16
	step_end

MagmaHideout_4F_EventScript_Grunt11::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_11, MagmaHideout_4F_Text_Grunt11Intro, MagmaHideout_4F_Text_Grunt11Defeat
	msgbox MagmaHideout_4F_Text_Grunt11PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt12::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_12, MagmaHideout_4F_Text_Grunt12Intro, MagmaHideout_4F_Text_Grunt12Defeat
	msgbox MagmaHideout_4F_Text_Grunt12PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt13::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_13, MagmaHideout_4F_Text_Grunt13Intro, MagmaHideout_4F_Text_Grunt13Defeat
	msgbox MagmaHideout_4F_Text_Grunt13PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MAGMA_HIDEOUT, MagmaHideout_4F_Text_TabithaIntro, MagmaHideout_4F_Text_TabithaDefeat
	msgbox MagmaHideout_4F_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_Text_Grunt11Intro:
    .string "我也想见固拉多，但它们\n连尾巴都不让我看……\p真让我难受。\p哦，不好！\n我怎么说出固拉多的事了！$"

MagmaHideout_4F_Text_Grunt11Defeat:
    .string "我想头脑不够冷静的话\n是不可能赢的……$"

MagmaHideout_4F_Text_Grunt11PostBattle:
    .string "不知道固拉多有没有尾巴？$"

MagmaHideout_4F_Text_Grunt12Intro:
    .string "哇哈哈！\n快了！就快了！\l我们的伟大目标就要实现了！$"

MagmaHideout_4F_Text_Grunt12Defeat:
    .string "啊……\n我努力了半天得到的就是这种结局？$"

MagmaHideout_4F_Text_Grunt12PostBattle:
    .string "赤焰松老大！\n有一名入侵者去你那儿了！$"

MagmaHideout_4F_Text_Grunt13Intro:
    .string "还没完呢！\n你别以为能轻易地干掉我！$"

MagmaHideout_4F_Text_Grunt13Defeat:
    .string "我那么容易就被干掉了？$"

MagmaHideout_4F_Text_Grunt13PostBattle:
    .string "来——来吧，再战一回……$"

MagmaHideout_4F_Text_TabithaIntro:
    .string "嘿嘿！既然你都\n打到这里了，那我就告诉你吧！\p正如你所料！\n固拉多就在前面沉睡着！\p赤焰松刚刚已经\n进去找固拉多了！\p它不久就要苏醒了！\n嘿嘿！嘿嘿！$"

MagmaHideout_4F_Text_TabithaDefeat:
    .string "又输了……\n嘿嘿……$"

MagmaHideout_4F_Text_TabithaPostBattle:
    .string "……在你和我周旋的时候，\n赤焰松应该已经唤醒了固拉多……$"

MagmaHideout_4F_Text_MaxieAwakenGroudon:
    .string "赤焰松：固拉多……\p无论怎样也不会\n从岩浆中苏醒的你……\p一直在寻求的，\n是靛蓝色宝珠吧？\p我带来了靛蓝色宝珠。\n就让它的光芒唤醒你吧！\p展示给我……\n把你全部的力量展示给我！$"

MagmaHideout_4F_Text_MaxieGroudonWhatsWrong:
    .string "赤焰松：固拉多！\n怎么回事？\p难道靛蓝色宝珠也不行吗？\p固拉多！\n你去哪里了……$"

MagmaHideout_4F_Text_MaxieOhItWasYou:
    .string "赤焰松：哦，是你？\p我早就看见你一直\n在偷偷摸摸东张西望……\p我明白了！\n肯定是你耍了什么花招！$"

MagmaHideout_4F_Text_MaxieDefeat:
    .string "你使用宝可梦为什么如此\n纯熟？$"

MagmaHideout_4F_Text_MaxieImGoingAfterGroudon:
    .string "赤焰松：固拉多逃跑肯定\n是有什么原因的……\p你是这个意思，\n对不对？\p…… …… ……\n…… …… ……\p哼……\n你以为我不知道？\p固拉多逃走了，我也没必要\n待在这座破火山里了。\p我去追固拉多，\n告辞了！$"
