CinnabarIsland_Gym_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, CinnabarIsland_Gym_OnLoad
	.byte 0

CinnabarIsland_Gym_OnLoad::
	goto_if_set FLAG_DEFEATED_BLAINE, CinnabarIsland_Gym_OnLoadOpenAllDoors
	call_if_set FLAG_CINNABAR_GYM_QUIZ_1, CinnabarIsland_Gym_OnLoadOpenDoor1
	call_if_set FLAG_CINNABAR_GYM_QUIZ_2, CinnabarIsland_Gym_OnLoadOpenDoor2
	call_if_set FLAG_CINNABAR_GYM_QUIZ_3, CinnabarIsland_Gym_OnLoadOpenDoor3
	call_if_set FLAG_CINNABAR_GYM_QUIZ_4, CinnabarIsland_Gym_OnLoadOpenDoor4
	call_if_set FLAG_CINNABAR_GYM_QUIZ_5, CinnabarIsland_Gym_OnLoadOpenDoor5
	call_if_set FLAG_CINNABAR_GYM_QUIZ_6, CinnabarIsland_Gym_OnLoadOpenDoor6
	end

CinnabarIsland_Gym_OnLoadOpenAllDoors::
	call CinnabarIsland_Gym_EventScript_OpenDoor1
	call CinnabarIsland_Gym_EventScript_OpenDoor2
	call CinnabarIsland_Gym_EventScript_OpenDoor3
	call CinnabarIsland_Gym_EventScript_OpenDoor4
	call CinnabarIsland_Gym_EventScript_OpenDoor5
	call CinnabarIsland_Gym_EventScript_OpenDoor6
	end

CinnabarIsland_Gym_OnLoadOpenDoor1::
	call CinnabarIsland_Gym_EventScript_OpenDoor1
	return

CinnabarIsland_Gym_OnLoadOpenDoor2::
	call CinnabarIsland_Gym_EventScript_OpenDoor2
	return

CinnabarIsland_Gym_OnLoadOpenDoor3::
	call CinnabarIsland_Gym_EventScript_OpenDoor3
	return

CinnabarIsland_Gym_OnLoadOpenDoor4::
	call CinnabarIsland_Gym_EventScript_OpenDoor4
	return

CinnabarIsland_Gym_OnLoadOpenDoor5::
	call CinnabarIsland_Gym_EventScript_OpenDoor5
	return

CinnabarIsland_Gym_OnLoadOpenDoor6::
	call CinnabarIsland_Gym_EventScript_OpenDoor6
	return

CinnabarIsland_Gym_EventScript_Blaine::
	famechecker FAMECHECKER_BLAINE, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_BLAINE, CinnabarIsland_Gym_Text_BlaineIntro, CinnabarIsland_Gym_Text_BlaineDefeat, CinnabarIsland_Gym_EventScript_DefeatedBlaine, NO_MUSIC
	goto_if_unset FLAG_GOT_TM38_FROM_BLAINE, CinnabarIsland_Gym_EventScript_GiveTM38
	msgbox CinnabarIsland_Gym_Text_BlainePostBattle
	release
	end

CinnabarIsland_Gym_EventScript_DefeatedBlaine::
	famechecker FAMECHECKER_BLAINE, 1
	setflag FLAG_DEFEATED_BLAINE
	setflag FLAG_BADGE07_GET
	setrespawn HEAL_LOCATION_CINNABAR_ISLAND
	setvar VAR_MAP_SCENE_CINNABAR_ISLAND, 1
	clearflag FLAG_HIDE_CINNABAR_BILL
	set_gym_trainers_frlg 7
	goto CinnabarIsland_Gym_EventScript_GiveTM38
	end

CinnabarIsland_Gym_EventScript_GiveTM38::
	msgbox CinnabarIsland_Gym_Text_ExplainVolcanoBadge
	checkitemspace ITEM_TM38
	goto_if_eq VAR_RESULT, FALSE, CinnabarIsland_Gym_EventScript_NoRoomForTM38
	giveitem_msg CinnabarIsland_Gym_Text_ReceivedTM38FromBlaine, ITEM_TM38
	setflag FLAG_GOT_TM38_FROM_BLAINE
	msgbox CinnabarIsland_Gym_Text_FireBlastIsUltimateFireMove
	release
	end

CinnabarIsland_Gym_EventScript_NoRoomForTM38::
	msgbox CinnabarIsland_Gym_Text_MakeSpaceForThis
	release
	end

CinnabarIsland_Gym_EventScript_Erik::
	trainerbattle_single TRAINER_SUPER_NERD_ERIK, CinnabarIsland_Gym_Text_ErikIntro, CinnabarIsland_Gym_Text_ErikDefeat
	msgbox CinnabarIsland_Gym_Text_ErikPostBattle, MSGBOX_AUTOCLOSE
	end

CinnabarIsland_Gym_EventScript_Avery::
	trainerbattle_single TRAINER_SUPER_NERD_AVERY, CinnabarIsland_Gym_Text_AveryIntro, CinnabarIsland_Gym_Text_AveryDefeat, CinnabarIsland_Gym_EventScript_DefeatedAvery
	msgbox CinnabarIsland_Gym_Text_AveryPostBattle, MSGBOX_AUTOCLOSE
	end

CinnabarIsland_Gym_EventScript_DefeatedAvery::
	call_if_unset FLAG_CINNABAR_GYM_QUIZ_2, CinnabarIsland_Gym_EventScript_Quiz2CompleteTrainer
	release
	end

CinnabarIsland_Gym_EventScript_Quiz2CompleteTrainer::
	call CinnabarIsland_Gym_EventScript_Quiz2Complete
	return

CinnabarIsland_Gym_EventScript_Derek::
	trainerbattle_single TRAINER_SUPER_NERD_DEREK, CinnabarIsland_Gym_Text_DerekIntro, CinnabarIsland_Gym_Text_DerekDefeat, CinnabarIsland_Gym_EventScript_DefeatedDerek
	famechecker FAMECHECKER_BLAINE, 2
	msgbox CinnabarIsland_Gym_Text_DerekPostBattle, MSGBOX_AUTOCLOSE
	end

CinnabarIsland_Gym_EventScript_DefeatedDerek::
	call_if_unset FLAG_CINNABAR_GYM_QUIZ_4, CinnabarIsland_Gym_EventScript_Quiz4CompleteTrainer
	release
	end

CinnabarIsland_Gym_EventScript_Quiz4CompleteTrainer::
	call CinnabarIsland_Gym_EventScript_Quiz4Complete
	return

CinnabarIsland_Gym_EventScript_Zac::
	trainerbattle_single TRAINER_SUPER_NERD_ZAC, CinnabarIsland_Gym_Text_ZacIntro, CinnabarIsland_Gym_Text_ZacDefeat, CinnabarIsland_Gym_EventScript_DefeatedZac
	msgbox CinnabarIsland_Gym_Text_ZacPostBattle, MSGBOX_AUTOCLOSE
	end

CinnabarIsland_Gym_EventScript_DefeatedZac::
	call_if_unset FLAG_CINNABAR_GYM_QUIZ_6, CinnabarIsland_Gym_EventScript_Quiz6CompleteTrainer
	release
	end

CinnabarIsland_Gym_EventScript_Quiz6CompleteTrainer::
	call CinnabarIsland_Gym_EventScript_Quiz6Complete
	return

CinnabarIsland_Gym_EventScript_Quinn::
	trainerbattle_single TRAINER_BURGLAR_QUINN, CinnabarIsland_Gym_Text_QuinnIntro, CinnabarIsland_Gym_Text_QuinnDefeat, CinnabarIsland_Gym_EventScript_DefeatedQuinn
	msgbox CinnabarIsland_Gym_Text_QuinnPostBattle, MSGBOX_AUTOCLOSE
	end

CinnabarIsland_Gym_EventScript_DefeatedQuinn::
	call_if_unset FLAG_CINNABAR_GYM_QUIZ_1, CinnabarIsland_Gym_EventScript_Quiz1CompleteTrainer
	release
	end

CinnabarIsland_Gym_EventScript_Quiz1CompleteTrainer::
	call CinnabarIsland_Gym_EventScript_Quiz1Complete
	return

CinnabarIsland_Gym_EventScript_Ramon::
	trainerbattle_single TRAINER_BURGLAR_RAMON, CinnabarIsland_Gym_Text_RamonIntro, CinnabarIsland_Gym_Text_RamonDefeat, CinnabarIsland_Gym_EventScript_DefeatedRamon
	msgbox CinnabarIsland_Gym_Text_RamonPostBattle, MSGBOX_AUTOCLOSE
	end

CinnabarIsland_Gym_EventScript_DefeatedRamon::
	call_if_unset FLAG_CINNABAR_GYM_QUIZ_3, CinnabarIsland_Gym_EventScript_Quiz3CompleteTrainer
	release
	end

CinnabarIsland_Gym_EventScript_Quiz3CompleteTrainer::
	call CinnabarIsland_Gym_EventScript_Quiz3Complete
	return

CinnabarIsland_Gym_EventScript_Dusty::
	trainerbattle_single TRAINER_BURGLAR_DUSTY, CinnabarIsland_Gym_Text_DustyIntro, CinnabarIsland_Gym_Text_DustyDefeat, CinnabarIsland_Gym_EventScript_DefeatedDusty
	msgbox CinnabarIsland_Gym_Text_DustyPostBattle, MSGBOX_AUTOCLOSE
	end

CinnabarIsland_Gym_EventScript_DefeatedDusty::
	call_if_unset FLAG_CINNABAR_GYM_QUIZ_5, CinnabarIsland_Gym_EventScript_Quiz5CompleteTrainer
	release
	end

CinnabarIsland_Gym_EventScript_Quiz5CompleteTrainer::
	call CinnabarIsland_Gym_EventScript_Quiz5Complete
	return

CinnabarIsland_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_BLAINE, CinnabarIsland_Gym_EventScript_GymGuyPostVictory
	msgbox CinnabarIsland_Gym_Text_GymGuyAdvice
	release
	end

CinnabarIsland_Gym_EventScript_GymGuyPostVictory::
	msgbox CinnabarIsland_Gym_Text_GymGuyPostVictory
	release
	end

CinnabarIsland_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, CinnabarIsland_Gym_EventScript_GymStatuePostVictory
	msgbox CinnabarIsland_Gym_Text_GymStatue
	releaseall
	end

CinnabarIsland_Gym_EventScript_GymStatuePostVictory::
	msgbox CinnabarIsland_Gym_Text_GymStatuePlayerWon
	releaseall
	end

CinnabarIsland_Gym_EventScript_Quz1Left::
	lockall
	setvar VAR_TEMP_1, 0
	goto CinnabarIsland_Gym_EventScript_Quiz1
	end

CinnabarIsland_Gym_EventScript_Quz1Right::
	lockall
	setvar VAR_TEMP_1, 1
	goto CinnabarIsland_Gym_EventScript_Quiz1
	end

CinnabarIsland_Gym_EventScript_Quiz1::
	msgbox CinnabarIsland_Gym_Text_PokemonQuizRules
	msgbox CinnabarIsland_Gym_Text_QuizQuestion1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CinnabarIsland_Gym_EventScript_Quiz1Correct
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_Gym_EventScript_Quiz1Incorrect
	end

CinnabarIsland_Gym_EventScript_CorrectAnswer::
	playfanfare MUS_LEVEL_UP
	waitfanfare
	msgbox CinnabarIsland_Gym_Text_CorrectGoOnThrough
	return

CinnabarIsland_Gym_EventScript_IncorrectAnswer::
	waitse
	playse SE_BOO
	waitse
	msgbox CinnabarIsland_Gym_Text_SorryBadCall
	closemessage
	return

CinnabarIsland_Gym_EventScript_Quiz1Correct::
	call CinnabarIsland_Gym_EventScript_CorrectAnswer
	goto_if_set FLAG_CINNABAR_GYM_QUIZ_1, CinnabarIsland_Gym_EventScript_DoorAlreadyOpen
	call CinnabarIsland_Gym_EventScript_Quiz1Complete
	releaseall
	end

CinnabarIsland_Gym_EventScript_Quiz1Complete::
	playse SE_UNLOCK
	waitse
	call CinnabarIsland_Gym_EventScript_OpenDoor1
	special DrawWholeMapView
	setflag FLAG_CINNABAR_GYM_QUIZ_1
	return

CinnabarIsland_Gym_EventScript_DoorAlreadyOpen::
	releaseall
	end

CinnabarIsland_Gym_EventScript_Quiz1Incorrect::
	call CinnabarIsland_Gym_EventScript_IncorrectAnswer
	goto_if_not_defeated TRAINER_BURGLAR_QUINN, CinnabarIsland_Gym_EventScript_BattleQuinn
	releaseall
	end

CinnabarIsland_Gym_EventScript_BattleQuinn::
	call_if_eq VAR_TEMP_1, 0, CinnabarIsland_Gym_EventScript_QuinnApproachLeft
	call_if_eq VAR_TEMP_1, 1, CinnabarIsland_Gym_EventScript_QuinnApproachRight
	textcolor NPC_TEXT_COLOR_MALE
	msgbox CinnabarIsland_Gym_Text_QuinnIntro
	trainerbattle_no_intro TRAINER_BURGLAR_QUINN, CinnabarIsland_Gym_Text_QuinnDefeat
	goto_if_set FLAG_CINNABAR_GYM_QUIZ_1, CinnabarIsland_Gym_EventScript_DoorAlreadyOpen
	call CinnabarIsland_Gym_EventScript_Quiz1Complete
	releaseall
	end

CinnabarIsland_Gym_EventScript_QuinnApproachLeft::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_QUINN, CinnabarIsland_Gym_Movement_QuinnApproachLeft
	waitmovement 0
	return

CinnabarIsland_Gym_EventScript_QuinnApproachRight::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_QUINN, CinnabarIsland_Gym_Movement_QuinnApproachRight
	waitmovement 0
	return

CinnabarIsland_Gym_Movement_QuinnApproachLeft::
	walk_left
	walk_left
	step_end

CinnabarIsland_Gym_Movement_QuinnApproachRight::
	walk_left
	step_end

CinnabarIsland_Gym_EventScript_Quiz2Left::
	lockall
	setvar VAR_TEMP_1, 0
	goto CinnabarIsland_Gym_EventScript_Quiz2
	end

CinnabarIsland_Gym_EventScript_Quiz2Right::
	lockall
	setvar VAR_TEMP_1, 1
	goto CinnabarIsland_Gym_EventScript_Quiz2
	end

CinnabarIsland_Gym_EventScript_Quiz2::
	msgbox CinnabarIsland_Gym_Text_PokemonQuizRules
	msgbox CinnabarIsland_Gym_Text_QuizQuestion2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CinnabarIsland_Gym_EventScript_Quiz2Incorrect
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_Gym_EventScript_Quiz2Correct
	end

CinnabarIsland_Gym_EventScript_Quiz2Correct::
	call CinnabarIsland_Gym_EventScript_CorrectAnswer
	goto_if_set FLAG_CINNABAR_GYM_QUIZ_2, CinnabarIsland_Gym_EventScript_DoorAlreadyOpen
	call CinnabarIsland_Gym_EventScript_Quiz2Complete
	releaseall
	end

CinnabarIsland_Gym_EventScript_Quiz2Complete::
	playse SE_UNLOCK
	waitse
	call CinnabarIsland_Gym_EventScript_OpenDoor2
	special DrawWholeMapView
	setflag FLAG_CINNABAR_GYM_QUIZ_2
	return

CinnabarIsland_Gym_EventScript_Quiz2Incorrect::
	call CinnabarIsland_Gym_EventScript_IncorrectAnswer
	goto_if_not_defeated TRAINER_SUPER_NERD_AVERY, CinnabarIsland_Gym_EventScript_BattleAvery
	releaseall
	end

CinnabarIsland_Gym_EventScript_BattleAvery::
	call_if_eq VAR_TEMP_1, 0, CinnabarIsland_Gym_EventScript_AveryApproachLeft
	call_if_eq VAR_TEMP_1, 1, CinnabarIsland_Gym_EventScript_AveryApproachRight
	textcolor NPC_TEXT_COLOR_MALE
	msgbox CinnabarIsland_Gym_Text_AveryIntro
	trainerbattle_no_intro TRAINER_SUPER_NERD_AVERY, CinnabarIsland_Gym_Text_AveryDefeat
	goto_if_set FLAG_CINNABAR_GYM_QUIZ_2, CinnabarIsland_Gym_EventScript_DoorAlreadyOpen
	call CinnabarIsland_Gym_EventScript_Quiz2Complete
	releaseall
	end

CinnabarIsland_Gym_EventScript_AveryApproachLeft::
	applymovement LOCALID_PLAYER, CinnabarIsland_Gym_Movement_PlayerFaceAvery
	applymovement LOCALID_AVERY, CinnabarIsland_Gym_Movement_AveryApproachLeft
	waitmovement 0
	return

CinnabarIsland_Gym_EventScript_AveryApproachRight::
	applymovement LOCALID_PLAYER, CinnabarIsland_Gym_Movement_PlayerFaceAvery
	applymovement LOCALID_AVERY, CinnabarIsland_Gym_Movement_AveryApproachRight
	waitmovement 0
	return

CinnabarIsland_Gym_Movement_AveryApproachLeft::
	walk_up
	walk_up
	walk_left
	step_end

CinnabarIsland_Gym_Movement_AveryApproachRight::
	walk_up
	walk_up
	walk_in_place_faster_left
	step_end

CinnabarIsland_Gym_Movement_PlayerFaceAvery::
	delay_16
	delay_16
	walk_in_place_faster_right
	step_end

CinnabarIsland_Gym_EventScript_Quiz3Left::
	lockall
	setvar VAR_TEMP_1, 0
	goto CinnabarIsland_Gym_EventScript_Quiz3
	end

CinnabarIsland_Gym_EventScript_Quiz3Right::
	lockall
	setvar VAR_TEMP_1, 1
	goto CinnabarIsland_Gym_EventScript_Quiz3
	end

CinnabarIsland_Gym_EventScript_Quiz3::
	msgbox CinnabarIsland_Gym_Text_PokemonQuizRules
	msgbox CinnabarIsland_Gym_Text_QuizQuestion3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CinnabarIsland_Gym_EventScript_Quiz3Incorrect
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_Gym_EventScript_Quiz3Correct
	end

CinnabarIsland_Gym_EventScript_Quiz3Correct::
	call CinnabarIsland_Gym_EventScript_CorrectAnswer
	goto_if_set FLAG_CINNABAR_GYM_QUIZ_3, CinnabarIsland_Gym_EventScript_DoorAlreadyOpen
	call CinnabarIsland_Gym_EventScript_Quiz3Complete
	releaseall
	end

CinnabarIsland_Gym_EventScript_Quiz3Complete::
	playse SE_UNLOCK
	waitse
	call CinnabarIsland_Gym_EventScript_OpenDoor3
	special DrawWholeMapView
	setflag FLAG_CINNABAR_GYM_QUIZ_3
	return

CinnabarIsland_Gym_EventScript_Quiz3Incorrect::
	call CinnabarIsland_Gym_EventScript_IncorrectAnswer
	goto_if_not_defeated TRAINER_BURGLAR_RAMON, CinnabarIsland_Gym_EventScript_BattleRamon
	releaseall
	end

CinnabarIsland_Gym_EventScript_BattleRamon::
	call_if_eq VAR_TEMP_1, 0, CinnabarIsland_Gym_EventScript_RamonApproachLeft
	call_if_eq VAR_TEMP_1, 1, CinnabarIsland_Gym_EventScript_RamonApproachRight
	textcolor NPC_TEXT_COLOR_MALE
	msgbox CinnabarIsland_Gym_Text_RamonIntro
	trainerbattle_no_intro TRAINER_BURGLAR_RAMON, CinnabarIsland_Gym_Text_RamonDefeat
	goto_if_set FLAG_CINNABAR_GYM_QUIZ_3, CinnabarIsland_Gym_EventScript_DoorAlreadyOpen
	call CinnabarIsland_Gym_EventScript_Quiz3Complete
	releaseall
	end

CinnabarIsland_Gym_EventScript_RamonApproachLeft::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_RAMON, CinnabarIsland_Gym_Movement_RamonApproachLeft
	waitmovement 0
	return

CinnabarIsland_Gym_EventScript_RamonApproachRight::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_RAMON, CinnabarIsland_Gym_Movement_RamonApproachRight
	waitmovement 0
	return

CinnabarIsland_Gym_Movement_RamonApproachLeft::
	walk_left
	walk_left
	step_end

CinnabarIsland_Gym_Movement_RamonApproachRight::
	walk_left
	step_end

CinnabarIsland_Gym_EventScript_Quiz4Left::
	lockall
	setvar VAR_TEMP_1, 0
	goto CinnabarIsland_Gym_EventScript_Quiz4
	end

CinnabarIsland_Gym_EventScript_Quiz4Right::
	lockall
	setvar VAR_TEMP_1, 1
	goto CinnabarIsland_Gym_EventScript_Quiz4
	end

CinnabarIsland_Gym_EventScript_Quiz4::
	msgbox CinnabarIsland_Gym_Text_PokemonQuizRules
	msgbox CinnabarIsland_Gym_Text_QuizQuestion4, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CinnabarIsland_Gym_EventScript_Quiz4Incorrect
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_Gym_EventScript_Quiz4Correct
	end

CinnabarIsland_Gym_EventScript_Quiz4Correct::
	call CinnabarIsland_Gym_EventScript_CorrectAnswer
	goto_if_set FLAG_CINNABAR_GYM_QUIZ_4, CinnabarIsland_Gym_EventScript_DoorAlreadyOpen
	call CinnabarIsland_Gym_EventScript_Quiz4Complete
	releaseall
	end

CinnabarIsland_Gym_EventScript_Quiz4Complete::
	playse SE_UNLOCK
	waitse
	call CinnabarIsland_Gym_EventScript_OpenDoor4
	special DrawWholeMapView
	setflag FLAG_CINNABAR_GYM_QUIZ_4
	return

CinnabarIsland_Gym_EventScript_Quiz4Incorrect::
	call CinnabarIsland_Gym_EventScript_IncorrectAnswer
	goto_if_not_defeated TRAINER_SUPER_NERD_DEREK, CinnabarIsland_Gym_EventScript_BattleDerek
	releaseall
	end

CinnabarIsland_Gym_EventScript_BattleDerek::
	call_if_eq VAR_TEMP_1, 0, CinnabarIsland_Gym_EventScript_DerekApproachLeft
	call_if_eq VAR_TEMP_1, 1, CinnabarIsland_Gym_EventScript_DerekApproachRight
	textcolor NPC_TEXT_COLOR_MALE
	msgbox CinnabarIsland_Gym_Text_DerekIntro
	trainerbattle_no_intro TRAINER_SUPER_NERD_DEREK, CinnabarIsland_Gym_Text_DerekDefeat
	goto_if_set FLAG_CINNABAR_GYM_QUIZ_4, CinnabarIsland_Gym_EventScript_DoorAlreadyOpen
	call CinnabarIsland_Gym_EventScript_Quiz4Complete
	releaseall
	end

CinnabarIsland_Gym_EventScript_DerekApproachLeft::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_DEREK, CinnabarIsland_Gym_Movement_DerekApproachLeft
	waitmovement 0
	return

CinnabarIsland_Gym_EventScript_DerekApproachRight::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_DEREK, CinnabarIsland_Gym_Movement_DerekApproachRight
	waitmovement 0
	return

CinnabarIsland_Gym_Movement_DerekApproachLeft::
	walk_left
	walk_left
	step_end

CinnabarIsland_Gym_Movement_DerekApproachRight::
	walk_left
	step_end

CinnabarIsland_Gym_EventScript_Quiz5Left::
	lockall
	setvar VAR_TEMP_1, 0
	goto CinnabarIsland_Gym_EventScript_Quiz5
	end

CinnabarIsland_Gym_EventScript_Quiz5Right::
	lockall
	setvar VAR_TEMP_1, 1
	goto CinnabarIsland_Gym_EventScript_Quiz5
	end

CinnabarIsland_Gym_EventScript_Quiz5::
	msgbox CinnabarIsland_Gym_Text_PokemonQuizRules
	msgbox CinnabarIsland_Gym_Text_QuizQuestion5, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CinnabarIsland_Gym_EventScript_Quiz5Correct
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_Gym_EventScript_Quiz5Incorrect
	end

CinnabarIsland_Gym_EventScript_Quiz5Correct::
	call CinnabarIsland_Gym_EventScript_CorrectAnswer
	goto_if_set FLAG_CINNABAR_GYM_QUIZ_5, CinnabarIsland_Gym_EventScript_DoorAlreadyOpen
	call CinnabarIsland_Gym_EventScript_Quiz5Complete
	releaseall
	end

CinnabarIsland_Gym_EventScript_Quiz5Complete::
	playse SE_UNLOCK
	waitse
	call CinnabarIsland_Gym_EventScript_OpenDoor5
	special DrawWholeMapView
	setflag FLAG_CINNABAR_GYM_QUIZ_5
	return

CinnabarIsland_Gym_EventScript_Quiz5Incorrect::
	call CinnabarIsland_Gym_EventScript_IncorrectAnswer
	goto_if_not_defeated TRAINER_BURGLAR_DUSTY, CinnabarIsland_Gym_EventScript_BattleDusty
	releaseall
	end

CinnabarIsland_Gym_EventScript_BattleDusty::
	call_if_eq VAR_TEMP_1, 0, CinnabarIsland_Gym_EventScript_DustyApproachLeft
	call_if_eq VAR_TEMP_1, 1, CinnabarIsland_Gym_EventScript_DustyApproachRight
	textcolor NPC_TEXT_COLOR_MALE
	msgbox CinnabarIsland_Gym_Text_DustyIntro
	trainerbattle_no_intro TRAINER_BURGLAR_DUSTY, CinnabarIsland_Gym_Text_DustyDefeat
	goto_if_set FLAG_CINNABAR_GYM_QUIZ_5, CinnabarIsland_Gym_EventScript_DoorAlreadyOpen
	call CinnabarIsland_Gym_EventScript_Quiz5Complete
	releaseall
	end

CinnabarIsland_Gym_EventScript_DustyApproachLeft::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_DUSTY, CinnabarIsland_Gym_Movement_DustyApproachLeft
	waitmovement 0
	return

CinnabarIsland_Gym_EventScript_DustyApproachRight::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_DUSTY, CinnabarIsland_Gym_Movement_DustyApproachRight
	waitmovement 0
	return

CinnabarIsland_Gym_Movement_DustyApproachLeft::
	walk_left
	walk_left
	step_end

CinnabarIsland_Gym_Movement_DustyApproachRight::
	walk_left
	step_end

CinnabarIsland_Gym_EventScript_Quiz6Left::
	lockall
	setvar VAR_TEMP_1, 0
	goto CinnabarIsland_Gym_EventScript_Quiz6
	end

CinnabarIsland_Gym_EventScript_Quiz6Right::
	lockall
	setvar VAR_TEMP_1, 1
	goto CinnabarIsland_Gym_EventScript_Quiz6
	end

CinnabarIsland_Gym_EventScript_Quiz6::
	msgbox CinnabarIsland_Gym_Text_PokemonQuizRules
	msgbox CinnabarIsland_Gym_Text_QuizQuestion6, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CinnabarIsland_Gym_EventScript_Quiz6Incorrect
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_Gym_EventScript_Quiz6Correct
	end

CinnabarIsland_Gym_EventScript_Quiz6Correct::
	call CinnabarIsland_Gym_EventScript_CorrectAnswer
	goto_if_set FLAG_CINNABAR_GYM_QUIZ_6, CinnabarIsland_Gym_EventScript_DoorAlreadyOpen
	call CinnabarIsland_Gym_EventScript_Quiz6Complete
	releaseall
	end

CinnabarIsland_Gym_EventScript_Quiz6Complete::
	playse SE_UNLOCK
	waitse
	call CinnabarIsland_Gym_EventScript_OpenDoor6
	special DrawWholeMapView
	setflag FLAG_CINNABAR_GYM_QUIZ_6
	return

CinnabarIsland_Gym_EventScript_Quiz6Incorrect::
	call CinnabarIsland_Gym_EventScript_IncorrectAnswer
	goto_if_not_defeated TRAINER_SUPER_NERD_ZAC, CinnabarIsland_Gym_EventScript_BattleZac
	releaseall
	end

CinnabarIsland_Gym_EventScript_BattleZac::
	call_if_eq VAR_TEMP_1, 0, CinnabarIsland_Gym_EventScript_ZacApproachLeft
	call_if_eq VAR_TEMP_1, 1, CinnabarIsland_Gym_EventScript_ZacApproachRight
	textcolor NPC_TEXT_COLOR_MALE
	msgbox CinnabarIsland_Gym_Text_ZacIntro
	trainerbattle_no_intro TRAINER_SUPER_NERD_ZAC, CinnabarIsland_Gym_Text_ZacDefeat
	goto_if_set FLAG_CINNABAR_GYM_QUIZ_6, CinnabarIsland_Gym_EventScript_DoorAlreadyOpen
	call CinnabarIsland_Gym_EventScript_Quiz6Complete
	releaseall
	end

CinnabarIsland_Gym_EventScript_ZacApproachLeft::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_ZAC, CinnabarIsland_Gym_Movement_ZacApproachLeft
	waitmovement 0
	return

CinnabarIsland_Gym_EventScript_ZacApproachRight::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_ZAC, CinnabarIsland_Gym_Movement_ZacApproachRight
	waitmovement 0
	return

CinnabarIsland_Gym_Movement_ZacApproachLeft::
	walk_left
	walk_left
	step_end

CinnabarIsland_Gym_Movement_ZacApproachRight::
	walk_left
	step_end

CinnabarIsland_Gym_EventScript_OpenDoor1::
	setmetatile 26,  8, METATILE_CinnabarGym_Floor_WallLeftCorner, 0
	setmetatile 27,  8, METATILE_CinnabarGym_Floor_WallRightCorner, 0
	setmetatile 26,  9, METATILE_CinnabarGym_Floor_WallLeftEdge, 0
	setmetatile 27,  9, METATILE_CinnabarGym_Floor_WallRightEdge, 0
	setmetatile 26, 10, METATILE_CinnabarGym_Floor_ShadeFull, 0
	setmetatile 27, 10, METATILE_CinnabarGym_Floor, 0
	setmetatile 28, 10, METATILE_CinnabarGym_Floor_ShadeDiagonal, 0
	return

CinnabarIsland_Gym_EventScript_OpenDoor2::
	setmetatile 17,  8, METATILE_CinnabarGym_Floor_WallLeftCorner, 0
	setmetatile 18,  8, METATILE_CinnabarGym_Floor_WallRightCorner, 0
	setmetatile 17,  9, METATILE_CinnabarGym_Floor_WallLeftEdge, 0
	setmetatile 18,  9, METATILE_CinnabarGym_Floor_WallRightEdge, 0
	setmetatile 17, 10, METATILE_CinnabarGym_Floor_ShadeFull, 0
	setmetatile 18, 10, METATILE_CinnabarGym_Floor, 0
	setmetatile 19, 10, METATILE_CinnabarGym_Floor_ShadeDiagonal, 0
	return

CinnabarIsland_Gym_EventScript_OpenDoor3::
	setmetatile 17, 15, METATILE_CinnabarGym_Floor_WallLeftCorner, 0
	setmetatile 18, 15, METATILE_CinnabarGym_Floor_WallRightCorner, 0
	setmetatile 17, 16, METATILE_CinnabarGym_Floor_WallLeftEdge, 0
	setmetatile 18, 16, METATILE_CinnabarGym_Floor_WallRightEdge, 0
	setmetatile 17, 17, METATILE_CinnabarGym_Floor_ShadeFull, 0
	setmetatile 18, 17, METATILE_CinnabarGym_Floor, 0
	setmetatile 19, 17, METATILE_CinnabarGym_Floor_ShadeDiagonal, 0
	return

CinnabarIsland_Gym_EventScript_OpenDoor4::
	setmetatile 11, 21, METATILE_CinnabarGym_Wall_RetractedBarrier, 1
	setmetatile 11, 22, METATILE_CinnabarGym_Floor_ShadeFull, 0
	setmetatile 11, 23, METATILE_CinnabarGym_Floor, 0
	return

CinnabarIsland_Gym_EventScript_OpenDoor5::
	setmetatile  5, 16, METATILE_CinnabarGym_Floor_WallLeftCorner, 0
	setmetatile  6, 16, METATILE_CinnabarGym_Floor_WallRightCorner, 0
	setmetatile  5, 17, METATILE_CinnabarGym_Floor_WallLeftEdge, 0
	setmetatile  6, 17, METATILE_CinnabarGym_Floor_WallRightEdge, 0
	setmetatile  5, 18, METATILE_CinnabarGym_Floor_ShadeFull, 0
	setmetatile  6, 18, METATILE_CinnabarGym_Floor, 0
	setmetatile  7, 18, METATILE_CinnabarGym_Floor_ShadeDiagonal, 0
	return

CinnabarIsland_Gym_EventScript_OpenDoor6::
	setmetatile  5,  8, METATILE_CinnabarGym_Floor_WallLeftCorner, 0
	setmetatile  6,  8, METATILE_CinnabarGym_Floor_WallRightCorner, 0
	setmetatile  5,  9, METATILE_CinnabarGym_Floor_WallLeftEdge, 0
	setmetatile  6,  9, METATILE_CinnabarGym_Floor_WallRightEdge, 0
	setmetatile  5, 10, METATILE_CinnabarGym_Floor_ShadeFull, 0
	setmetatile  6, 10, METATILE_CinnabarGym_Floor, 0
	setmetatile  7, 10, METATILE_CinnabarGym_Floor_ShadeDiagonal, 0
	return

CinnabarIsland_Gym_Text_BlaineIntro::
    .string "啊哈！\p"
    .string "夏伯就是我，\n"
    .string "红莲道馆火热的馆主！\p"
    .string "我炽烈的宝可梦都\n"
    .string "狂野而富有热情！\p"
    .string "它们会把所有的挑战者燃烧殆尽！\p"
    .string "好了！\n"
    .string "开战前你最好准备些灼伤药！{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

CinnabarIsland_Gym_Text_BlaineDefeat::
    .string "被燃烧殆尽的是我！\n"
    .string "烧得连灰烬也不剩！\p"
    .string "深红徽章是你的了！$"

CinnabarIsland_Gym_Text_FireBlastIsUltimateFireMove::
    .string "大字爆炎是一个\n"
    .string "高级的火属性技能\p"
    .string "别把它浪费在水属性宝可梦身上。$"

CinnabarIsland_Gym_Text_ExplainVolcanoBadge::
    .string "哈！\p"
    .string "深红徽章能够将你\n"
    .string "宝可梦的特攻提高一点点\p"
    .string "还有，你还能得到它！$"

CinnabarIsland_Gym_Text_ReceivedTM38FromBlaine::
    .string "{PLAYER}从夏伯那里\n"
    .string "得到了TM38。$"

CinnabarIsland_Gym_Text_BlainePostBattle::
    .string "TM38是大字爆炎。\n"
    .string "把它教给火属性宝可梦。\p"
    .string "六尾或者火恐龙\n"
    .string "是一个不错的选择。$"

CinnabarIsland_Gym_Text_MakeSpaceForThis::
    .string "把背包腾点空间再来，小子！$"

CinnabarIsland_Gym_Text_ErikIntro::
    .string "你知道宝可梦\n"
    .string "灼热的吐息温度有多高吗？$"

CinnabarIsland_Gym_Text_ErikDefeat::
    .string "哟噢！\n"
    .string "烫，烫，烫！$"

CinnabarIsland_Gym_Text_ErikPostBattle::
    .string "燃素，专业点说的话，\n"
    .string "可燃物……\p"
    .string "……空气中的氧……\n"
    .string "叽哩呱啦呱啦叽哩…$"

CinnabarIsland_Gym_Text_QuinnIntro::
    .string "过去我是一名小偷\n"
    .string "但我现在是一名正直的训练家。$"

CinnabarIsland_Gym_Text_QuinnDefeat::
    .string "我要去自首！$"

CinnabarIsland_Gym_Text_QuinnPostBattle::
    .string "对于其他人的宝可梦我总是\n"
    .string "难以抑制的想着去偷。$"

CinnabarIsland_Gym_Text_AveryIntro::
    .string "我很努力的学过了宝可梦的知识。\n"
    .string "你赢不了我的！$"

CinnabarIsland_Gym_Text_AveryDefeat::
    .string "哇啊！\n"
    .string "我学的还不够！$"

CinnabarIsland_Gym_Text_AveryPostBattle::
    .string "我的理论很高深，\n"
    .string "和你讲你很难明白。$"

CinnabarIsland_Gym_Text_RamonIntro::
    .string "走自己的路让别人说去吧。\n"
    .string "我就只喜欢火属性的宝可梦。$"

CinnabarIsland_Gym_Text_RamonDefeat::
    .string "温度高得不能控制了！$"

CinnabarIsland_Gym_Text_RamonPostBattle::
    .string "我希望有一种小偷宝可梦。\n"
    .string "那我就指望着用它了！$"

CinnabarIsland_Gym_Text_DerekIntro::
    .string "我知道夏伯为什么会\n"
    .string "成为一名训练家。$"

CinnabarIsland_Gym_Text_DerekDefeat::
    .string "喔$"

CinnabarIsland_Gym_Text_DerekPostBattle::
    .string "我们的馆主，夏伯在山里迷路了，\n"
    .string "但幸运的是，\p"
    .string "当夜幕降临的时候，\n"
    .string "一只灼热的鸟宝可梦降临在他面前。\p"
    .string "它发出的光使\n"
    .string "夏伯找到了下山的路。$"

CinnabarIsland_Gym_Text_DustyIntro::
    .string "我去过许多道馆，\n"
    .string "但这个最合我的口味。$"

CinnabarIsland_Gym_Text_DustyDefeat::
    .string "哇哇！\n"
    .string "好烫！$"

CinnabarIsland_Gym_Text_DustyPostBattle::
    .string "小火马，九尾…\n"
    .string "都是受欢迎的火属性宝可梦。$"

CinnabarIsland_Gym_Text_ZacIntro::
    .string "火对H2O不利。$"

CinnabarIsland_Gym_Text_ZacDefeat::
    .string "呃！\n"
    .string "火熄灭了！$"

CinnabarIsland_Gym_Text_ZacPostBattle::
    .string "毋庸置疑，水克火。\p"
    .string "但是火能融化冰，\n"
    .string "所以火属性能够打败冰属性宝可梦。$"

CinnabarIsland_Gym_Text_GymGuyAdvice::
    .string "哟！\n"
    .string "未来的冠军！\p"
    .string "热血的夏伯是一位\n"
    .string "炎宝可梦教授。\p"
    .string "用水来浇灭他的斗志吧！\p"
    .string "你最好带上些\n"
    .string "灼伤药。$"

CinnabarIsland_Gym_Text_GymGuyPostVictory::
    .string "{PLAYER}\n"
    .string "你击败了那个火焰狂人$"

CinnabarIsland_Gym_Text_GymStatue::
    .string "红莲宝可梦道馆\n"
    .string "馆主：夏伯\p"
    .string "优胜训练家：\n"
    .string "{RIVAL}$"

CinnabarIsland_Gym_Text_GymStatuePlayerWon::
    .string "红莲宝可梦道馆\n"
    .string "馆主：夏伯\p"
    .string "优胜训练家：\n"
    .string "{RIVAL} {PLAYER}$"

CinnabarIsland_Gym_Text_PokemonQuizRules::
    .string "宝可梦竞答！\p"
    .string "答对了，\n"
    .string "通向下一个房间的门就会打开。\p"
    .string "答错了，就得面对训练家的挑战！\p"
    .string "你如果想要把你的实力\n"
    .string "保留到最后一刻……\p"
    .string "那就要尽可能的答对！\n"
    .string "三，二，一，开始了！$"

CinnabarIsland_Gym_Text_QuizQuestion1::
    .string "绿毛虫进化成铁甲蛹吗？$"

CinnabarIsland_Gym_Text_QuizQuestion2::
    .string "宝可梦联盟徽章\n"
    .string "一共有九枚？$"

CinnabarIsland_Gym_Text_QuizQuestion3::
    .string "蚊香蝌蚪能进化三次？$"

CinnabarIsland_Gym_Text_QuizQuestion4::
    .string "电属性技能对地面属性\n"
    .string "宝可梦有效果吗？$"

CinnabarIsland_Gym_Text_QuizQuestion5::
    .string "同一种宝可梦有着同样的等级\n"
    .string "它们的能力却不一定一样？$"

CinnabarIsland_Gym_Text_QuizQuestion6::
    .string "TM28是岩石封锁吗$"

CinnabarIsland_Gym_Text_CorrectGoOnThrough::
    .string "你答得太对了！\p"
    .string "请通过！$"

CinnabarIsland_Gym_Text_SorryBadCall::
    .string "不好意思！\n"
    .string "答错了！$"

