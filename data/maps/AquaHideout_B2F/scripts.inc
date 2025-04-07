.set LOCALID_MATT, 1
.set LOCALID_SUBMARINE, 4

AquaHideout_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AquaHideout_B2F_OnTransition
	.byte 0

AquaHideout_B2F_OnTransition:
	call_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, AquaHideout_B2F_EventScript_PreventMattNoticing
	end

AquaHideout_B2F_EventScript_PreventMattNoticing::
	setvar VAR_TEMP_1, 1
	return

AquaHideout_B2F_EventScript_MattNoticePlayer::
	lockall
	setvar VAR_0x8008, LOCALID_MATT
	playse SE_PIN
	applymovement VAR_0x8008, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_TEMP_1, 1
	releaseall
	end

AquaHideout_B2F_EventScript_Matt::
	trainerbattle_single TRAINER_MATT, AquaHideout_B2F_Text_MattIntro, AquaHideout_B2F_Text_MattDefeat, AquaHideout_B2F_EventScript_SubmarineEscape
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_SubmarineEscape::
	setvar VAR_0x8008, LOCALID_MATT
	setvar VAR_0x8009, LOCALID_SUBMARINE
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_OurBossGotThroughHisPreparations, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFasterLeft
	applymovement VAR_0x8009, AquaHideout_B2F_Movement_SumbarineDepartLeft
	waitmovement 0
	removeobject VAR_0x8009
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	setflag FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE
	setflag FLAG_HIDE_LILYCOVE_CITY_AQUA_GRUNTS
	release
	end

AquaHideout_B2F_Movement_SumbarineDepartLeft:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

@ Unused
AquaHideout_B2F_Movement_SumbarineDepartRight:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

AquaHideout_B2F_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_4, AquaHideout_B2F_Text_Grunt4Intro, AquaHideout_B2F_Text_Grunt4Defeat, AquaHideout_B2F_EventScript_Grunt4Defeated
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt4Defeated::
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_6, AquaHideout_B2F_Text_Grunt6Intro, AquaHideout_B2F_Text_Grunt6Defeat
	msgbox AquaHideout_B2F_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_8, AquaHideout_B2F_Text_Grunt8Intro, AquaHideout_B2F_Text_Grunt8Defeat
	msgbox AquaHideout_B2F_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_Text_MattIntro:
    .string "嘿嘿嘿…\p居然能走到这儿来啊，\n看来我们低估了你！\p但是到此为止了！\p我可比前面那些家伙\n都要强得多。\p我可不是仅仅拖延时间的，\n我会将你捏成粉末的！$"

AquaHideout_B2F_Text_MattDefeat:
    .string "嘿嘿嘿…\n看来我也输了…$"

AquaHideout_B2F_Text_OurBossGotThroughHisPreparations:
    .string "嘿嘿嘿！\p我陪你玩的时候，我们的老大\n就可以做好准备了！$"

AquaHideout_B2F_Text_MattPostBattle:
    .string "嘿嘿嘿！\p我们的老大已经在去\n海底洞窟的路上了！\p想追的话，就去\n水静市那边\l宽广的海域慢慢找吧。\p但是你能找到吗？\n嘿嘿嘿！$"

AquaHideout_B2F_Text_Grunt4Intro:
    .string "哇哈哈，我已经等烦了！\n你也欠我一场战斗！$"

AquaHideout_B2F_Text_Grunt4Defeat:
    .string "等烦了…\n也败得一塌糊涂…$"

AquaHideout_B2F_Text_Grunt4PostBattle:
    .string "老大…\n这样可以了么？$"

AquaHideout_B2F_Text_Grunt6Intro:
    .string "这里的传送地板可是\n基地的骄傲！\p你完全不知道你身在何处了吧，\n不是吗？\p等敌人变得慌乱又疲劳，突然给他\n致命一击！这就是我们的作战计划！$"

AquaHideout_B2F_Text_Grunt6Defeat:
    .string "你怎么会这样？\n你一点也不显得累！$"

AquaHideout_B2F_Text_Grunt6PostBattle:
    .string "说起来…我忘了\n把掌门球放在哪里了。\p如果我没有保护好它，\n会被老大骂死的…$"

AquaHideout_B2F_Text_Grunt8Intro:
    .string "我加入水舰队的时候，第一件事\n就是记住这些传送地板\l都通向什么地方。$"

AquaHideout_B2F_Text_Grunt8Defeat:
    .string "脑子里全都是\n传送地板的事情了…$"

AquaHideout_B2F_Text_Grunt8PostBattle:
    .string "我想我必须学学\n战斗的要诀了…$"
