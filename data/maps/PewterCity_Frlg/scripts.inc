PewterCity_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PewterCity_OnTransition
	.byte 0

PewterCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_PEWTER_CITY
	setvar VAR_MAP_SCENE_PEWTER_CITY_MUSEUM_1F, 0
	end

@ Impossible to speak to this NPC from a facing dir != DIR_EAST normally, so they arent checked
@ Additionally, no movement script exists for facing DIR_SOUTH, which would necessitate walking out of bounds
PewterCity_EventScript_GymGuide::
	lock
	faceplayer
	msgbox PewterCity_Text_BrocksLookingForChallengersFollowMe
	closemessage
	playbgm MUS_FOLLOW_ME, 0
	call_if_eq VAR_FACING, DIR_EAST, PewterCity_EventScript_WalkToGymEast
	msgbox PewterCity_Text_GoTakeOnBrock
	closemessage
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GymGuideExit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_PEWTER_GYM_GUIDE
	clearflag FLAG_HIDE_PEWTER_CITY_GYM_GUIDE
	release
	end

PewterCity_EventScript_WalkToGymEast::
	applymovement LOCALID_PLAYER, PewterCity_Movement_PlayerWaitForGuideEast
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GuideMoveToLeadEast
	waitmovement 0
	applymovement LOCALID_PLAYER, PewterCity_Movement_PlayerWalkToGymEast
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GuideWalkToGymEast
	waitmovement 0
	return

@ Unused
PewterCity_EventScript_WalkToGymWest::
	applymovement LOCALID_PLAYER, PewterCity_Movement_PlayerWaitForGuideWest
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GuideMoveToLeadWest
	waitmovement 0
	applymovement LOCALID_PLAYER, PewterCity_Movement_PlayerWalkToGymWest
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GuideWalkToGymWest
	waitmovement 0
	return

@ Unused
PewterCity_EventScript_WalkToGymNorth::
	applymovement LOCALID_PLAYER, PewterCity_Movement_PlayerWaitForGuideNorth
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GuideMoveToLeadNorth
	waitmovement 0
	applymovement LOCALID_PLAYER, PewterCity_Movement_PlayerWalkToGymNorth
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GuideWalkToGymNorth
	waitmovement 0
	return

.macro walk_to_gym
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
.endm

.macro walk_to_gym_alt
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
.endm

PewterCity_Movement_PlayerWaitForGuideEast::
	delay_16
	delay_16
	delay_4
	walk_in_place_faster_down
	step_end

PewterCity_Movement_PlayerWalkToGymEast::
	walk_down
	walk_to_gym
	step_end

PewterCity_Movement_PlayerWaitForGuideWest::
	delay_16
	step_end

PewterCity_Movement_PlayerWalkToGymWest::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_to_gym_alt
	step_end

PewterCity_Movement_PlayerWaitForGuideNorth::
	delay_16
	step_end

PewterCity_Movement_PlayerWalkToGymNorth::
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_to_gym_alt
	step_end

PewterCity_Movement_GuideMoveToLeadEast::
	walk_down
	walk_left
	walk_in_place_faster_up
	walk_in_place_up
	step_end

PewterCity_Movement_GuideWalkToGymEast::
	walk_to_gym
	walk_right
	walk_in_place_faster_left
	step_end

PewterCity_Movement_GuideMoveToLeadWest::
	walk_in_place_right
	step_end

PewterCity_Movement_GuideWalkToGymWest::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_to_gym_alt
	walk_right
	walk_in_place_faster_left
	step_end

PewterCity_Movement_GuideMoveToLeadNorth::
	walk_in_place_down
	step_end

PewterCity_Movement_GuideWalkToGymNorth::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_to_gym_alt
	walk_right
	walk_in_place_faster_left
	step_end

PewterCity_Movement_GymGuideExit::
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

PewterCity_EventScript_GymGuideTriggerTop::
	lockall
	setvar VAR_TEMP_1, 0
	goto PewterCity_EventScript_GymGuideTrigger
	end

PewterCity_EventScript_GymGuideTriggerMid::
	lockall
	setvar VAR_TEMP_1, 1
	goto PewterCity_EventScript_GymGuideTrigger
	end

PewterCity_EventScript_GymGuideTriggerBottom::
	lockall
	setvar VAR_TEMP_1, 2
	goto PewterCity_EventScript_GymGuideTrigger
	end

@ This trigger is inaccessible and its corresponding movement script isnt linked
PewterCity_EventScript_GymGuideTriggerRight::
	lockall
	setvar VAR_TEMP_1, 3
	goto PewterCity_EventScript_GymGuideTrigger
	end

PewterCity_EventScript_GymGuideTrigger::
	textcolor NPC_TEXT_COLOR_MALE
	msgbox PewterCity_Text_BrocksLookingForChallengersFollowMe
	closemessage
	playbgm MUS_FOLLOW_ME, 0
	call_if_eq VAR_TEMP_1, 0, PewterCity_EventScript_WalkToGymTop
	call_if_eq VAR_TEMP_1, 1, PewterCity_EventScript_WalkToGymMid
	call_if_eq VAR_TEMP_1, 2, PewterCity_EventScript_WalkToGymBottom
	msgbox PewterCity_Text_GoTakeOnBrock
	closemessage
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GymGuideExit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_PEWTER_GYM_GUIDE
	clearflag FLAG_HIDE_PEWTER_CITY_GYM_GUIDE
	releaseall
	end

PewterCity_EventScript_WalkToGymTop::
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GuideMoveToLeadTop
	waitmovement 0
	applymovement LOCALID_PLAYER, PewterCity_Movement_PlayerWalkToGymTop
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GuideWalkToGymTop
	waitmovement 0
	return

PewterCity_EventScript_WalkToGymMid::
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GuideMoveToLeadMid
	waitmovement 0
	applymovement LOCALID_PLAYER, PewterCity_Movement_PlayerWalkToGymMid
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GuideWalkToGymMid
	waitmovement 0
	return

PewterCity_EventScript_WalkToGymBottom::
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GuideMoveToLeadBottom
	waitmovement 0
	applymovement LOCALID_PLAYER, PewterCity_Movement_PlayerWalkToGymBottom
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GuideWalkToGymBottom
	waitmovement 0
	return

@ Unused
PewterCity_EventScript_WalkToGymRight::
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GuideApproachPlayerRight
	waitmovement 0
	applymovement LOCALID_PLAYER, PewterCity_Movement_PlayerWalkToGymRight
	applymovement LOCALID_PEWTER_GYM_GUIDE, PewterCity_Movement_GuideWalkToGymRight
	waitmovement 0
	return

PewterCity_Movement_PlayerWalkToGymTop::
	walk_left
	walk_to_gym
	step_end

PewterCity_Movement_PlayerWalkToGymMid::
	walk_up
	walk_left
	walk_to_gym
	step_end

PewterCity_Movement_PlayerWalkToGymBottom::
	walk_up
	walk_up
	walk_left
	walk_to_gym
	step_end

PewterCity_Movement_PlayerWalkToGymRight::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_to_gym_alt
	step_end

PewterCity_Movement_GuideMoveToLeadTop::
	walk_left
	walk_down
	walk_in_place_faster_right
	walk_in_place_right
	step_end

PewterCity_Movement_GuideMoveToLeadMid::
	walk_down
	walk_in_place_down
	step_end

PewterCity_Movement_GuideMoveToLeadBottom::
	walk_down
	walk_down
	walk_in_place_down
	step_end

PewterCity_Movement_GuideApproachPlayerRight::
	walk_down
	walk_down
	walk_right
	walk_down
	walk_right
	walk_in_place_right
	step_end

PewterCity_Movement_GuideWalkToGymTop::
	walk_to_gym
	walk_right
	walk_in_place_faster_left
	step_end

PewterCity_Movement_GuideWalkToGymMid::
	walk_left
	walk_to_gym
	walk_right
	walk_in_place_faster_left
	step_end

PewterCity_Movement_GuideWalkToGymBottom::
	walk_up
	walk_left
	walk_to_gym
	walk_right
	walk_in_place_faster_left
	step_end

PewterCity_Movement_GuideWalkToGymRight::
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_to_gym_alt
	walk_right
	walk_in_place_faster_left
	step_end

PewterCity_EventScript_Lass::
	msgbox PewterCity_Text_ClefairyCameFromMoon, MSGBOX_NPC
	end

PewterCity_EventScript_MuseumGuide::
	lock
	faceplayer
	msgbox PewterCity_Text_DidYouCheckOutMuseum, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PewterCity_EventScript_CheckedOutMuseum
	msgbox PewterCity_Text_ReallyYouHaveToGo
	closemessage
	delay 10
	playbgm MUS_FOLLOW_ME, 0
	call_if_eq VAR_FACING, DIR_NORTH, PewterCity_EventScript_LeadToMuseumNorth
	call_if_eq VAR_FACING, DIR_SOUTH, PewterCity_EventScript_LeadToMuseumSouth
	call_if_eq VAR_FACING, DIR_WEST, PewterCity_EventScript_LeadToMuseumWest
	call_if_eq VAR_FACING, DIR_EAST, PewterCity_EventScript_LeadToMuseumEast
	msgbox PewterCity_Text_ThisIsTheMuseum
	closemessage
	delay 10
	applymovement LOCALID_PEWTER_MUSEUM_GUIDE, PewterCity_Movement_MuseumGuideExit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_PEWTER_MUSEUM_GUIDE
	clearflag FLAG_HIDE_PEWTER_MUSEUM_GUIDE
	release
	end

PewterCity_EventScript_LeadToMuseumNorth::
	applymovement LOCALID_PEWTER_MUSEUM_GUIDE, PewterCity_Movement_GuideWalkToMuseumNorth
	applymovement LOCALID_PLAYER, PewterCity_Movement_PlayerWalkToMuseumNorth
	waitmovement 0
	return

PewterCity_EventScript_LeadToMuseumSouth::
	applymovement LOCALID_PEWTER_MUSEUM_GUIDE, PewterCity_Movement_GuideWalkToMuseumSouth
	applymovement LOCALID_PLAYER, PewterCity_Movement_PlayerWalkToMuseumSouth
	waitmovement 0
	return

PewterCity_EventScript_LeadToMuseumWest::
	applymovement LOCALID_PEWTER_MUSEUM_GUIDE, PewterCity_Movement_GuideWalkToMuseumWest
	applymovement LOCALID_PLAYER, PewterCity_Movement_PlayerWalkToMuseumWest
	waitmovement 0
	return

PewterCity_EventScript_LeadToMuseumEast::
	applymovement LOCALID_PEWTER_MUSEUM_GUIDE, PewterCity_Movement_GuideWalkToMuseumEast
	applymovement LOCALID_PLAYER, PewterCity_Movement_PlayerWalkToMuseumEast
	waitmovement 0
	return

PewterCity_EventScript_CheckedOutMuseum::
	msgbox PewterCity_Text_WerentThoseFossilsAmazing
	release
	end

.macro walk_to_museum
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
.endm

.macro walk_to_museum_south
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
.endm

PewterCity_Movement_PlayerWalkToMuseumNorth::
	walk_up
	walk_to_museum
	delay_8
	walk_in_place_faster_up
	step_end

PewterCity_Movement_GuideWalkToMuseumNorth::
	walk_to_museum
	walk_left
	walk_in_place_faster_up
	step_end

PewterCity_Movement_PlayerWalkToMuseumSouth::
	delay_16
	delay_16
	walk_left
	walk_to_museum_south
	delay_8
	walk_in_place_faster_up
	step_end

PewterCity_Movement_GuideWalkToMuseumSouth::
	walk_left
	walk_up
	walk_to_museum_south
	walk_left
	walk_in_place_faster_up
	step_end

PewterCity_Movement_PlayerWalkToMuseumWest::
	walk_left
	walk_to_museum
	delay_8
	walk_in_place_faster_up
	step_end

PewterCity_Movement_GuideWalkToMuseumWest::
	walk_to_museum
	walk_left
	walk_in_place_faster_up
	step_end

PewterCity_Movement_PlayerWalkToMuseumEast::
	walk_right
	walk_to_museum
	delay_8
	walk_in_place_faster_up
	step_end

PewterCity_Movement_GuideWalkToMuseumEast::
	walk_to_museum
	walk_left
	walk_in_place_faster_up
	step_end

PewterCity_Movement_MuseumGuideExit::
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

PewterCity_EventScript_FatMan::
	lock
	faceplayer
	famechecker FAMECHECKER_BROCK, 2
	msgbox PewterCity_Text_BrockOnlySeriousTrainerHere
	release
	end

PewterCity_EventScript_BugCatcher::
	lock
	faceplayer
	msgbox PewterCity_Text_DoYouKnowWhatImDoing, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PewterCity_EventScript_KnowWhatTheyreDoing
	msgbox PewterCity_Text_SprayingRepelToKeepWildMonsOut
	release
	end

PewterCity_EventScript_KnowWhatTheyreDoing::
	msgbox PewterCity_Text_ThatsRightItsHardWork
	release
	end

PewterCity_EventScript_TrainerTips::
	msgbox PewterCity_Text_TrainerTipsEarningEXP, MSGBOX_SIGN
	end

PewterCity_EventScript_PoliceNotice::
	msgbox PewterCity_Text_CallPoliceIfInfoOnThieves, MSGBOX_SIGN
	end

PewterCity_EventScript_MuseumSign::
	msgbox PewterCity_Text_MuseumOfScience, MSGBOX_SIGN
	end

PewterCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_BROCK, 0
	msgbox PewterCity_Text_GymSign
	releaseall
	end

PewterCity_EventScript_CitySign::
	msgbox PewterCity_Text_CitySign, MSGBOX_SIGN
	end

PewterCity_EventScript_RunningShoesAide::
	lock
	faceplayer
	setvar VAR_TEMP_1, 0
	call PewterCity_EventScript_AideGiveRunningShoes
	release
	end

PewterCity_EventScript_RunningShoesAideTriggerTop::
	lockall
	setvar VAR_TEMP_1, 1
	call PewterCity_EventScript_AideGiveRunningShoes
	releaseall
	end

PewterCity_EventScript_RunningShoesAideTriggerMid::
	lockall
	setvar VAR_TEMP_1, 2
	call PewterCity_EventScript_AideGiveRunningShoes
	releaseall
	end

PewterCity_EventScript_RunningShoesAideTriggerBottom::
	lockall
	setvar VAR_TEMP_1, 3
	call PewterCity_EventScript_AideGiveRunningShoes
	releaseall
	end

PewterCity_EventScript_AideGiveRunningShoes::
	textcolor NPC_TEXT_COLOR_MALE
	call_if_eq VAR_TEMP_1, 1, PewterCity_EventScript_AideNoticePlayer
	call_if_eq VAR_TEMP_1, 2, PewterCity_EventScript_AideNoticePlayer
	call_if_eq VAR_TEMP_1, 3, PewterCity_EventScript_AideNoticePlayer
	waitse
	playse SE_PIN
	applymovement LOCALID_PEWTER_AIDE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PEWTER_AIDE, Common_Movement_Delay48
	waitmovement 0
	msgbox PewterCity_Text_OhPlayer
	call_if_eq VAR_TEMP_1, 0, PewterCity_EventScript_AideApproachPlayer0
	call_if_eq VAR_TEMP_1, 1, PewterCity_EventScript_AideApproachPlayer1
	call_if_eq VAR_TEMP_1, 2, PewterCity_EventScript_AideApproachPlayer2
	call_if_eq VAR_TEMP_1, 3, PewterCity_EventScript_AideApproachPlayer3
	msgbox PewterCity_Text_AskedToDeliverThis
	textcolor NPC_TEXT_COLOR_NEUTRAL
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message PewterCity_Text_ReceivedRunningShoesFromAide
	waitmessage
	waitfanfare
	msgbox PewterCity_Text_SwitchedShoesWithRunningShoes
	special DisableMsgBoxWalkaway
	signmsg
	msgbox PewterCity_Text_ExplainRunningShoes
	normalmsg
	call EventScript_RestorePrevTextColor
	msgbox PewterCity_Text_MustBeGoingBackToLab
	closemessage
	call_if_eq VAR_TEMP_1, 0, PewterCity_EventScript_AideExit0
	call_if_eq VAR_TEMP_1, 1, PewterCity_EventScript_AideExit1
	call_if_eq VAR_TEMP_1, 2, PewterCity_EventScript_AideExit2
	call_if_eq VAR_TEMP_1, 3, PewterCity_EventScript_AideExit3
	delay 30
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox PewterCity_Text_RunningShoesLetterFromMom
	closemessage
	removeobject LOCALID_PEWTER_AIDE
	setflag FLAG_SYS_B_DASH
	setvar VAR_MAP_SCENE_PEWTER_CITY, 2
	return

PewterCity_EventScript_AideNoticePlayer::
	applymovement LOCALID_PEWTER_AIDE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

@ Aide already at player
PewterCity_EventScript_AideApproachPlayer0::
	closemessage
	delay 20
	return

PewterCity_EventScript_AideApproachPlayer1::
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

PewterCity_EventScript_AideApproachPlayer2::
	closemessage
	applymovement LOCALID_PEWTER_AIDE, PewterCity_Movement_AideApproachPlayerMid
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

PewterCity_EventScript_AideApproachPlayer3::
	closemessage
	applymovement LOCALID_PEWTER_AIDE, PewterCity_Movement_AideApproachPlayerBottom
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

PewterCity_EventScript_AideExit0::
	applymovement LOCALID_PEWTER_AIDE, PewterCity_Movement_AideExit0
	waitmovement 0
	return

PewterCity_EventScript_AideExit1::
	applymovement LOCALID_PEWTER_AIDE, PewterCity_Movement_AideExit1
	waitmovement 0
	return

PewterCity_EventScript_AideExit2::
	applymovement LOCALID_PEWTER_AIDE, PewterCity_Movement_AideExit2
	waitmovement 0
	return

PewterCity_EventScript_AideExit3::
	applymovement LOCALID_PEWTER_AIDE, PewterCity_Movement_AideExit3
	waitmovement 0
	return

PewterCity_Movement_AideApproachPlayerMid::
	delay_4
	walk_down
	step_end

PewterCity_Movement_AideApproachPlayerBottom::
	delay_4
	walk_down
	walk_down
	step_end

PewterCity_Movement_AideExit0::
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

PewterCity_Movement_AideExit1::
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

PewterCity_Movement_AideExit2::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

PewterCity_Movement_AideExit3::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

@ Unused
PewterCity_Movement_WalkInPlaceLeft::
	walk_in_place_left
	step_end

Text_DreamEaterTeach::
    .string "哈欠！\n"
    .string "在这种阳光下我肯定会打起瞌睡。\p"
    .string "然后我做了一个一只\n"
    .string "催眠貘正在吞食我做的梦的怪梦。\p"
    .string "在那之后……\n"
    .string "我学会了如何食梦……\p"
    .string "噢，真是太恐怖了！\p"
    .string "让我把它教给一只宝可梦吧\n"
    .string "这样我才能赶快忘了它！$"

Text_DreamEaterDeclined::
    .string "……呼……$"

Text_DreamEaterWhichMon::
    .string "哪一只宝可梦想要学会\n"
    .string "食梦呢？$"

Text_DreamEaterTaught::
    .string "……ZZZ……\n"
    .string "我……实在是……吃不下了……$"

PewterCity_Text_ClefairyCameFromMoon::
    .string "有这样一个传说，\n"
    .string "说皮皮来自月亮。\p"
    .string "在那之后月之石\n"
    .string "才出现在了月见山。$"

PewterCity_Text_BrockOnlySeriousTrainerHere::
    .string "这里没有那种很严肃的\n"
    .string "宝可梦训练家。\p"
    .string "他们都打扮得像个捉虫少年，\n"
    .string "你懂的，就是一种癖好。\p"
    .string "可深灰道馆的小刚并不像这样打扮。\n"
    .string "不像，一点都不像。$"

PewterCity_Text_DidYouCheckOutMuseum::
    .string "你去博物馆看过了吗？$"

PewterCity_Text_WerentThoseFossilsAmazing::
    .string "不觉得这些来自月见山的化石\n"
    .string "很令人吃惊吗？$"

PewterCity_Text_ReallyYouHaveToGo::
    .string "真的？\n"
    .string "你必须得去一次看看！$"

PewterCity_Text_ThisIsTheMuseum::
    .string "博物馆就在这里了。\p"
    .string "虽然你必须花钱买了票才能进去，\n"
    .string "但是里面非常值得一看。回头见！$"

PewterCity_Text_DoYouKnowWhatImDoing::
    .string "嘘！\n"
    .string "你知道我正在做什么吗？$"

PewterCity_Text_ThatsRightItsHardWork::
    .string "没错！\n"
    .string "这事做起来可不轻松！$"

PewterCity_Text_SprayingRepelToKeepWildMonsOut::
    .string "我正在喷除虫喷雾使那些野生的\n"
    .string "宝可梦远离我的花园！$"

PewterCity_Text_BrocksLookingForChallengersFollowMe::
    .string "你是一个训练家，对吗？\p"
    .string "小刚正在寻找新的挑战者\n"
    .string "跟我来！$"

PewterCity_Text_GoTakeOnBrock::
    .string "如果你有了正确的信念，\n"
    .string "就应该去打倒小刚！$"

PewterCity_Text_TrainerTipsEarningEXP::
    .string "训练家贴士\p"
    .string "在战斗中出场过的宝可梦，\n"
    .string "哪怕是只打了瓶酱油都会获得经验值。$"

PewterCity_Text_CallPoliceIfInfoOnThieves::
    .string "通知\p"
    .string "有些小偷正在对月见山的\n"
    .string "宝可梦化石下手。\p"
    .string "如果你有任何线索\n"
    .string "请马上通知深灰警察局。$"

PewterCity_Text_MuseumOfScience::
    .string "深灰科学博物馆$"

PewterCity_Text_GymSign::
    .string "深灰市宝可梦道馆\n"
    .string "馆主：小刚\l"
    .string "有如磐石般坚硬的宝可梦训练家！$"

PewterCity_Text_CitySign::
    .string "深灰市\n"
    .string "灰色的岩石之城$"

PewterCity_Text_OhPlayer::
    .string "噢，{PLAYER}{KUN}！$"

PewterCity_Text_AskedToDeliverThis::
    .string "能够赶上你真高兴。\n"
    .string "我是大木博士的助手。\p"
    .string "给。\n"
    .string "我被叮嘱要把这件东西带给你。$"

PewterCity_Text_ReceivedRunningShoesFromAide::
    .string "{PLAYER}从助手那里\n"
    .string "获得了跑步鞋。$"

PewterCity_Text_SwitchedShoesWithRunningShoes::
    .string "{PLAYER}换上了\n"
    .string "跑步鞋。$"

PewterCity_Text_ExplainRunningShoes::
    .string "现在开始按B键就可以跑步了。\n"
    .string "但是只能在空旷的地方跑哦！$"

PewterCity_Text_MustBeGoingBackToLab::
    .string "那么，我必须回\n"
    .string "研究所去了。\p"
    .string "再见啦！$"

PewterCity_Text_RunningShoesLetterFromMom::
    .string "是一封信……\p"
    .string "亲爱的{PLAYER}，\p"
    .string "这双跑步鞋\n"
    .string "是给我心爱的挑战者的。\p"
    .string "我一直都会祝福你。\n"
    .string "记住，永远不要中途就放弃了！\p"
    .string "妈妈$"

