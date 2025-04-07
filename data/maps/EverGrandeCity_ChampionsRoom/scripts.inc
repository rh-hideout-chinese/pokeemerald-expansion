.set LOCALID_WALLACE, 1
.set LOCALID_RIVAL, 2
.set LOCALID_BIRCH, 3

EverGrandeCity_ChampionsRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_ChampionsRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_ChampionsRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_ChampionsRoom_OnFrame
	.byte 0

EverGrandeCity_ChampionsRoom_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	end

EverGrandeCity_ChampionsRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_ChampionsRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_EnterRoom
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_EnterRoom::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp4
	waitmovement 0
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace
	waitmovement 0
	setvar VAR_TEMP_1, 1
	goto EverGrandeCity_ChampionsRoom_EventScript_Wallace
	releaseall
	end

EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_EventScript_Wallace::
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox EverGrandeCity_ChampionsRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLACE, EverGrandeCity_ChampionsRoom_Text_Defeat
	goto EverGrandeCity_ChampionsRoom_EventScript_Defeated
	end

EverGrandeCity_ChampionsRoom_EventScript_Defeated::
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, FALSE
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic
	addobject LOCALID_RIVAL
	call EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayAdvice
	goto_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice
	end

EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_MayAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF::
	closemessage
	addobject LOCALID_BIRCH
	applymovement LOCALID_BIRCH, EverGrandeCity_ChampionsRoom_Movement_BirchArrives
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex, MSGBOX_DEFAULT
	call ProfBirch_EventScript_RatePokedex
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchCongratulations, MSGBOX_DEFAULT
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalFollows
	waitmovement 0
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside, MSGBOX_DEFAULT
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations
	closemessage
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExit
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_GYM_GREETER
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer::
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth::
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_PlayerExit:
	walk_up
	delay_16
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_in_place_faster_right
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth:
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_up
	delay_8
	walk_in_place_faster_right
	delay_16
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalFollows:
	walk_right
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart:
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExit:
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_BirchArrives:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_in_place_faster_left
	step_end

EverGrandeCity_ChampionsRoom_Text_IntroSpeech:
    .string "米可利：欢迎你，{PLAYER}{KUN}。\p在琉璃市发生的事…\n你做得很好，通过自己的努力\l战胜了罪恶。\p呵呵！\p让你独自去阻止罪恶\n可能有点不太公平。\p通过你和你的宝可梦之间的努力，\n你克服了重重困难。\p我们训练师通过给予宝可梦道具\n来培养它们。\l和教给它们战斗所需招式。\p其实我们自己本身\n也从宝可梦那里得到学习。\p这里就是与其他像你一样的对手战斗\n来检验自己努力成果的最好的地方。\p现在！\p谁能与自己的宝可梦\n在丰缘笑到最后？\p现在，就在这里展示给我看吧！$"

EverGrandeCity_ChampionsRoom_Text_Defeat:
    .string "我，冠军，被打败了…\p真是精彩的比赛。\n你是那么的优秀，我也感到愤怒了。\l但是我输得心服口服！\p光荣属于你，{PLAYER}{KUN}！\p你是一名真正伟大的\n宝可梦训练师！$"

EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech:
    .string "米可利：你所选择参加战斗的\n宝可梦…\p有时它们轻柔如风\n有时它们又\l迅猛如闪电。\p你指挥你的宝可梦\n是那么轻松，稳健，优雅。\p甚至我都被你\n出色的表演所迷惑！\p你现在已经到达了\n宝可梦联盟的顶峰。\p我现在宣布\n你是丰缘地区新的…$"

EverGrandeCity_ChampionsRoom_Text_MayAdvice:
    .string "小遥：{PLAYER}{KUN}！\p给你几条挑战冠军前\n的建议…$"

EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver:
    .string "小遥：呃？\n什么，那个，难道？\p{PLAYER}{KUN}…\n不会吧…\l已经结束了？$"

EverGrandeCity_ChampionsRoom_Text_BrendanAdvice:
    .string "佑树：{PLAYER}！\p需要挑战冠军前\n的建议吗？…$"

EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon:
    .string "佑树：{PLAYER}…\p你不会是想告诉我…\n你已经打败了冠军？$"

EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex:
    .string "小田卷博士：是吧？\n就像我之前说过的，{RIVAL}？\p我说过你不必担忧\n{PLAYER}{KUN}？\p… … … … … … … …\n{PLAYER}{KUN}，你最终成功了。\p当我听说你\n在橙华道馆打败了你的父亲，\l我当时认为你可能有机会…\p但是我没想到你现在确实\n成了冠军！\p啊，是的！\p你的图鉴完成得如何了？\n这里，来让我看下。$"

EverGrandeCity_ChampionsRoom_Text_BirchCongratulations:
    .string "小田卷博士：不管怎么说，\n恭喜你！\p现在，昂首挺进最终的房间吧！$"

EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe:
    .string "米可利：{PLAYER}{KUN}…\p不，我要改口了。\p新的冠军！\p跟我来。$"

EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside:
    .string "米可利：对不起，但是…\p从这里开始，只有那些成为冠军的训练师\n才可以进去。\p你只能在外面等候了\n小田卷博士。$"

EverGrandeCity_ChampionsRoom_Text_MayCongratulations:
    .string "小遥：呃…\p… … … … … … … …\n… … … … … … … …\p开玩笑的吧？！没关系！\n这是规定嘛！\p{PLAYER}{KUN}！\n真诚的恭喜你！$"

EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations:
    .string "佑树：什什什么？！… … … … …\n… … … … … … … …\p如果规定了这样也没有办法。\p{PLAYER}，去吧！\n恭喜你！$"

