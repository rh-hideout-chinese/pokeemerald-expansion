TrainerTower_Lobby_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TrainerTower_Lobby_OnResume
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, TrainerTower_Lobby_OnReturnToField
	map_script MAP_SCRIPT_ON_TRANSITION, TrainerTower_Lobby_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, TrainerTower_Lobby_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrainerTower_Lobby_OnFrame
	.byte 0

TrainerTower_Lobby_OnResume::
	setvar VAR_TEMP_2, 0
	ttower_resumetimer
	ttower_shouldexit
	goto_if_eq VAR_RESULT, FALSE, TrainerTower_Lobby_OnResumeEnd
	@ Never reached, above always FALSE
	setvar VAR_TEMP_0, 0
	setobjectxy LOCALID_PLAYER, 9, 7
	applymovement LOCALID_PLAYER, TrainerTower_Lobby_Movement_FaceReceptionist
TrainerTower_Lobby_OnResumeEnd::
	end

TrainerTower_Lobby_OnReturnToField::
	addobject LOCALID_TOWER_NURSE
	addobject LOCALID_TOWER_MART_CLERK
	addobject LOCALID_TOWER_RECEPTIONIST
	addobject LOCALID_TOWER_COOLTRAINER_F
	addobject LOCALID_TOWER_BALDING_MAN
	end

TrainerTower_Lobby_OnLoad::
	call_if_eq VAR_TEMP_D, 17, TrainerTower_Lobby_OpenCounterBarrier
	end

TrainerTower_Lobby_OpenCounterBarrier::
	setmetatile 17, 10, METATILE_TrainerTower_Floor_ShadeBottomLeft, 0
	return

TrainerTower_Lobby_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_TRAINER_TOWER_LOBBY
	getplayerxy VAR_TEMP_D, VAR_RESULT
	end

TrainerTower_Lobby_OnFrame::
	map_script_2 VAR_TEMP_0, 0, TrainerTower_Lobby_EventScript_Enter
	map_script_2 VAR_TEMP_D, 17, TrainerTower_Lobby_EventScript_ExitElevator
	.2byte 0

TrainerTower_Lobby_EventScript_ExitElevator::
	lockall
	applymovement LOCALID_PLAYER, TrainerTower_Lobby_Movement_ExitElevator
	waitmovement 0
	setmetatile 17, 10, METATILE_TrainerTower_CounterBarrier, 1
	special DrawWholeMapView
	playse SE_CLICK
	waitse
	setvar VAR_TEMP_D, 0
	releaseall
	end

TrainerTower_Lobby_Movement_ExitElevator::
	walk_down
	walk_down
	step_end

TrainerTower_Lobby_EventScript_Enter::
	setvar VAR_TEMP_0, 1
	ttower_getchallengestatus
	switch VAR_RESULT
	case TT_CHALLENGE_STATUS_LOST, TrainerTower_Lobby_EventScript_LostChallenge
	case TT_CHALLENGE_STATUS_UNK, TrainerTower_Lobby_EventScript_ExitChallengeSpeakToReceptionist
	case TT_CHALLENGE_STATUS_NORMAL, TrainerTower_Lobby_EventScript_EnterEnd

TrainerTower_Lobby_EventScript_LostChallenge::
	lock
	faceplayer
	applymovement LOCALID_PLAYER, TrainerTower_Lobby_Movement_FaceReceptionist
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox TrainerTower_Lobby_Text_TooBadComeBackTryAgain
	goto TrainerTower_Lobby_EventScript_ExitChallenge

@ Presumably E-Reader related
TrainerTower_Lobby_EventScript_ExitChallengeSpeakToReceptionist::
	lock
	faceplayer
	applymovement LOCALID_PLAYER, TrainerTower_Lobby_Movement_FaceReceptionist
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox TrainerTower_Lobby_Text_MoveCounterHereWhenTrainersSwitch
TrainerTower_Lobby_EventScript_ExitChallenge::
	closemessage
	applymovement LOCALID_PLAYER, TrainerTower_Lobby_Movement_WalkDown
	waitmovement 0
	setvar VAR_MAP_SCENE_TRAINER_TOWER, 0
	release
TrainerTower_Lobby_EventScript_EnterEnd::
	end

TrainerTower_Lobby_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

TrainerTower_Lobby_EventScript_Receptionist::
	lock
	faceplayer
	ttower_getbeatchallenge
	goto_if_eq VAR_RESULT, TRUE, TrainerTower_Lobby_EventScript_ThanksForCompeting
	msgbox TrainerTower_Lobby_Text_GiveItYourBest
	goto TrainerTower_Lobby_EventScript_ReceptionistEnd

TrainerTower_Lobby_EventScript_ThanksForCompeting::
	msgbox TrainerTower_Lobby_Text_ThanksForCompeting
TrainerTower_Lobby_EventScript_ReceptionistEnd::
	release
	end

TrainerTower_Lobby_EventScript_MartClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart TrainerTower_Lobby_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
TrainerTower_Lobby_Mart_Items::
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_MAX_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

TrainerTower_Lobby_EventScript_EntryTrigger::
	lockall
	applymovement LOCALID_PLAYER, TrainerTower_Lobby_Movement_FaceReceptionist
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox TrainerTower_Lobby_Text_WelcomeToTrainerTower
	ttower_getnumfloors
	goto_if_eq VAR_RESULT, FALSE, TrainerTower_Lobby_EventScript_AllFloorsUsed
	msgbox TrainerTower_Lobby_Text_TrainersUpToFloorNum
	goto TrainerTower_Lobby_EventScript_AskEnterChallenge

TrainerTower_Lobby_EventScript_AllFloorsUsed::
	msgbox TrainerTower_Lobby_Text_TrainersUpEighthFloor
TrainerTower_Lobby_EventScript_AskEnterChallenge::
	message TrainerTower_Lobby_Text_LikeToChallengeTrainers
	waitmessage
	multichoice 18, 6, MULTI_YESNOINFO, FALSE
	switch VAR_RESULT
	case 0, TrainerTower_Lobby_EventScript_ChooseChallenge
	case 1, TrainerTower_Lobby_EventScript_DeclineChallenge
	case 2, TrainerTower_Lobby_EventScript_ChallengeInfo
	case MULTI_B_PRESSED, TrainerTower_Lobby_EventScript_DeclineChallenge
	end

TrainerTower_Lobby_EventScript_ChallengeInfo::
	msgbox TrainerTower_Lobby_Text_ExplainTrainerTower
	goto TrainerTower_Lobby_EventScript_AskEnterChallenge
	end

TrainerTower_Lobby_EventScript_ChooseChallenge::
	multichoice 13, 3, MULTI_TRAINER_TOWER_MODE, FALSE
	switch VAR_RESULT
	case 0, TrainerTower_Lobby_EventScript_BeginChallenge
	case 1, TrainerTower_Lobby_EventScript_BeginChallenge
	case 2, TrainerTower_Lobby_EventScript_BeginChallenge
	case 3, TrainerTower_Lobby_EventScript_BeginChallenge
	case 4, TrainerTower_Lobby_EventScript_DeclineChallenge
	case MULTI_B_PRESSED, TrainerTower_Lobby_EventScript_DeclineChallenge
	end

TrainerTower_Lobby_EventScript_BeginChallenge::
	copyvar VAR_0x8005, VAR_RESULT
	setvar VAR_MAP_SCENE_TRAINER_TOWER, 1
	special HealPlayerParty
	msgbox TrainerTower_Lobby_Text_StartClockGetSetGo
	ttower_startchallenge
	releaseall
	end

TrainerTower_Lobby_EventScript_DeclineChallenge::
	msgbox TrainerTower_Lobby_Text_PleaseVisitUsAgain
	closemessage
	applymovement LOCALID_PLAYER, TrainerTower_Lobby_Movement_WalkDown
	waitmovement 0
	releaseall
	end

TrainerTower_Lobby_Movement_FaceReceptionist::
	face_right
	step_end

TrainerTower_Lobby_Movement_WalkDown::
	walk_down
	step_end

TrainerTower_Lobby_EventScript_ShowRecords::
	lockall
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, 1
	special ShowTrainerHillRecords
	waitstate
	releaseall
	end

TrainerTower_Lobby_EventScript_CooltrainerF::
	msgbox TrainerTower_Lobby_Text_WonderWhatKindsOfTrainers, MSGBOX_NPC
	end

TrainerTower_Lobby_EventScript_BaldingMan::
	msgbox TrainerTower_Lobby_Text_StairsTougherThanAnyBattle, MSGBOX_NPC
	end

@ All Trainer Tower text (Lobby and Roof) is interleaved here

TrainerTower_Lobby_Text_WelcomeToTrainerTower::
    .string "您好！\p"
    .string "欢迎来到来自各地的训练家的聚集地\n"
    .string "训练家之塔！$"

TrainerTower_Lobby_Text_TrainersUpToFloorNum::
    .string "来自世界各地的训练家\n"
    .string "聚到这里来对斗。\p"
    .string "我看看……\p"
    .string "现在，只有{STR_VAR_1}层的训练家了！$"

TrainerTower_Lobby_Text_TrainersUpEighthFloor::
    .string "训练家正在第八层\n"
    .string "等着你的挑战。$"

TrainerTower_Lobby_Text_LikeToChallengeTrainers::
    .string "你想要挑战等待着你的训练家吗？$"

TrainerTower_Lobby_Text_StartClockGetSetGo::
    .string "好的，我要开始计时了，\n"
    .string "请尽你最大的努力去\p"
    .string "夺得分数……\p"
    .string "准备……\p"
    .string "开始！$"

TrainerTower_Lobby_Text_PleaseVisitUsAgain::
    .string "敬请再次光临！$"

TrainerTower_Lobby_Text_TooBadComeBackTryAgain::
    .string "太糟糕了。\p"
    .string "我想你已经很努力地在战斗了。\p"
    .string "请以后再来试试吧！$"

TrainerTower_Lobby_Text_GiveItYourBest::
    .string "我希望你发挥出了你所有的实力。$"

TrainerTower_Lobby_Text_MoveCounterHereWhenTrainersSwitch::
    .string "当训练家交换场地的时候，\n"
    .string "移动会很混乱。\p"
    .string "为了避免拥堵，\n"
    .string "我们将服务台移到了这儿，\p"
    .string "对您造成的不便深感歉意。$"

TrainerTower_Roof_Text_ImOwnerBattledPerfectly::
    .string "你好……\p"
    .string "我是这座塔的主人……\p"
    .string "天空屹立在塔顶之上……\p"
    .string "轻风温柔地抚摸着它……\p"
    .string "一切都是那么完美……\p"
    .string "你战斗的方式……\n"
    .string "也是一样的完美……$"

TrainerTower_Roof_Text_ThisIsForYou::
    .string "这是给你的……$"

TrainerTower_Roof_Text_DoneItInRecordTime::
    .string "真了不起！\p"
    .string "你能这么快地爬上来\n"
    .string "真是不可思议。\p"
    .string "事实上，\n"
    .string "你刚刚创造了最快的时间记录……\p"
    .string "我要将你的记录\n"
    .string "贴在在服务台那里。$"

TrainerTower_Roof_Text_TookSweetTimeGettingHere::
    .string "你好像花了\n"
    .string "不少时间才到达这里……$"

TrainerTower_Roof_Text_IdLikeToSeeBetterTime::
    .string "我希望能看到你更好的表现……\p"
    .string "我期待着你。\p"
    .string "在那个时候到来之前，再会了……$"

TrainerTower_Text_XMinYZSec::
    .string "{STR_VAR_1}分{STR_VAR_2}。{STR_VAR_3}秒。$"

TrainerTower_Lobby_Text_HereAreTheResults::
	.string "せいせきひょうです$"

TrainerTower_Lobby_Text_NeedTwoMonsForDouble::
    .string "这是一场二对二的战斗。\p"
    .string "你至少需要有两只宝可梦才能战斗。$"

TrainerTower_Lobby_Text_ExplainTrainerTower::
    .string "在这个训练家之塔里，\n"
    .string "有一个叫做进攻计时的项目。\p"
    .string "您会被记录下从服务台\n"
    .string "到塔顶主人那儿的时间\l"
    .string "看看您到底有多快。\p"
    .string "最快的时间将会被记录在\n"
    .string "时间看板上\p"
    .string "试一试与您的朋友们比赛\n"
    .string "看看谁能最快到达。\p"
    .string "在这里打败训练家\n"
    .string "您将不会得到任何经验值和金钱。$"

TrainerTower_Lobby_Text_ThanksForCompeting::
    .string "感谢您的挑战！$"

TrainerTower_Lobby_Text_WonderWhatKindsOfTrainers::
    .string "我来这儿试试我有多厉害。\p"
    .string "我想知道会有什么样的训练家\n"
    .string "在等着我呢？\p"
    .string "真是伤脑筋啊！$"

TrainerTower_Lobby_Text_StairsTougherThanAnyBattle::
    .string "呼，呼……\p"
    .string "不管战斗了！\n"
    .string "爬这些楼梯比任何战斗都困难……$"

