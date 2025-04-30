.set LOCALID_SS_TIDAL, 2
.set LOCALID_FERRY_ATTENDANT, 3
.set LOCALID_MANIAC_1, 9
.set LOCALID_MANIAC_2, 10
.set LOCALID_GIRL, 12
.set LOCALID_CAMPER, 14
.set LOCALID_FISHERMAN_2, 18
.set LOCALID_MAN_4, 23

BattleFrontier_OutsideWest_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideWest_OnTransition
	.byte 0

BattleFrontier_OutsideWest_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	end

BattleFrontier_OutsideWest_EventScript_FerryAttendant::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_MayISeeYourTicket, MSGBOX_DEFAULT
	checkitem ITEM_SS_TICKET
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_OutsideWest_EventScript_NoSSTicket
	message BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination::
	multichoicedefault 18, 6, MULTI_SSTIDAL_BATTLE_FRONTIER, 2, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_OutsideWest_EventScript_FerryToSlateport
	case 1, BattleFrontier_OutsideWest_EventScript_FerryToLilycove
	case 2, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	case MULTI_B_PRESSED, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	end

BattleFrontier_OutsideWest_EventScript_NoSSTicket::
	msgbox BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToSlateport::
	msgbox BattleFrontier_OutsideWest_Text_SlateportItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_SLATEPORT_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToLilycove::
	msgbox BattleFrontier_OutsideWest_Text_LilycoveItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_LILYCOVE_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination::
	message BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_BoardFerry::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_FERRY_ATTENDANT, MAP_BATTLE_FRONTIER_OUTSIDE_WEST
	setvar VAR_0x8004, LOCALID_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	return

BattleFrontier_OutsideWest_EventScript_CancelFerrySelect::
	msgbox BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_BattleDomeSign::
	msgbox BattleFrontier_OutsideWest_Text_BattleDomeSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattleFactorySign::
	msgbox BattleFrontier_OutsideWest_Text_BattleFactorySign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattlePikeSign::
	msgbox BattleFrontier_OutsideWest_Text_BattlePikeSign, MSGBOX_SIGN
	end

@ Unused. Of note, Battle Tower is in the East section in the final release
BattleFrontier_OutsideWest_EventScript_UnusedNPC1::
	msgbox BattleFrontier_OutsideWest_Text_ThisIsBattleTower, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC2::
	msgbox BattleFrontier_OutsideWest_Text_CantFindBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Boy1::
	msgbox BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Fisherman2::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere
	waitmessage
	applymovement LOCALID_FISHERMAN_2, Common_Movement_FaceAwayPlayer
	waitmovement 0
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_Man1::
	msgbox BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Maniac1::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_Maniac2::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk::
	applymovement LOCALID_MANIAC_1, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons, MSGBOX_DEFAULT
	applymovement LOCALID_MANIAC_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons, MSGBOX_DEFAULT
	closemessage
	delay 25
	applymovement LOCALID_MANIAC_1, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_MANIAC_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_Camper::
	lock
	faceplayer
	delay 20
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	msgbox BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_CamperFaceFactory::
	applymovement LOCALID_CAMPER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory::
	return

BattleFrontier_OutsideWest_EventScript_Girl::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper
	waitmessage
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_GirlShudderNorth
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_GirlShudderSouth
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_GirlShudderWest
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_GirlShudderEast
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_GirlShudderNorth::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderNorth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderSouth::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderSouth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderWest::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderWest
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderEast::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderEast
	waitmovement 0
	return

BattleFrontier_OutsideWest_Movement_GirlShudderNorth:
	walk_in_place_faster_down
	walk_in_place_faster_down
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderSouth:
	walk_in_place_faster_up
	walk_in_place_faster_up
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderWest:
	walk_in_place_faster_right
	walk_in_place_faster_right
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderEast:
	walk_in_place_faster_left
	walk_in_place_faster_left
	step_end

BattleFrontier_OutsideWest_EventScript_Woman2::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors, MSGBOX_DEFAULT
	random 2
	goto_if_eq VAR_RESULT, 1, BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors
	goto BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors
	end

BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Fisherman1::
	msgbox BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC3::
	msgbox BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Lass::
	msgbox BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_ExpertM::
	msgbox BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man2::
	msgbox BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman1::
	msgbox BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan1::
	msgbox BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan2::
	msgbox BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Boy2::
	lock
	msgbox BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_OldMan::
	msgbox BattleFrontier_OutsideWest_Text_DomeAceIsMine, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man4::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAN_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_PokefanF::
	msgbox BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Text_BattleDomeSign:
    .string "这里是对战巨蛋！\n通往超级明星的大路！$"

BattleFrontier_OutsideWest_Text_BattleFactorySign:
    .string "这里是对战工厂！\n寻找最强的宝可梦吧！$"

BattleFrontier_OutsideWest_Text_BattlePikeSign:
    .string "这里是对战管道！\n在三条路中选一条吧！$"

BattleFrontier_OutsideWest_Text_ThisIsBattleTower:
    .string "这里是对战塔，\p训练家将他们最优秀的\n宝可梦带来进行淘汰赛。$"

BattleFrontier_OutsideWest_Text_MayISeeYourTicket:
    .string "你好，你想登船？\n可以让我看一下你的船票吗？$"

BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard:
    .string "{PLAYER}没有船票……\p非常抱歉，\p想登船的话必须\n要有船票。$"

BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo:
    .string "{PLAYER}晃了晃船票。\p很好！这就够了！\p你想去哪里？$"

BattleFrontier_OutsideWest_Text_SlateportItIs:
    .string "那就去凯那市！$"

BattleFrontier_OutsideWest_Text_LilycoveItIs:
    .string "那就去水静市！$"

BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime:
    .string "欢迎下次再来！$"

BattleFrontier_OutsideWest_Text_PleaseBoardFerry:
    .string "请登船等待\n启航。$"

BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo:
    .string "那么你想去哪里？$"

BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends:
    .string "在朋友之中我是最强的，\n但在这儿……\l我根本不算什么！$"

BattleFrontier_OutsideWest_Text_CantFindBattleTower:
    .string "我想去对战塔，\n但就算有地图，我也\l找不到对战开拓区。\p这块地方实在太大了！$"

BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere:
    .string "我本来准备一到这儿\n就开始挑战的，\p不过，在路上，我晕船了……\n呜……$"

BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere:
    .string "知道吗，并不是\n所有人都能到这里的，\p只有被认定是强大的训练家\n才能来到这里。\p所以很多训练家甚至对\n对战开拓区一无所知。$"

BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons:
    .string "嗨，伙计……\p你敢肯定我们没有宝可梦\n也能进行挑战？$"

BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons:
    .string "呃……\n大概不要紧吧。\p我想是的……\p记得那个吓人的大家伙吗？\n他不是说：“我会借给你宝可梦！”$"

BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons:
    .string "那边的是对战工厂，\n在那儿你能借到强大的宝可梦，\p不过我一直在奇怪，\n那些宝可梦是谁培育出来的？$"

BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper:
    .string "我不敢进对战管道，\n我怕饭匙蛇……\p但——但我既然已经到这儿来了\n我要努力战胜一切！\l……咕咕……$"

BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors:
    .string "来，石头剪子布！\n一～二～三！\p…… …… ……$"

BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge:
    .string "耶！赢了！\n去挑战对战管道咯！$"

BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge:
    .string "啊，不要啊……\n我输了。\p好像我今天的运气不是很好，\n明天再去挑战\l对战管道吧。$"

BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling:
    .string "我想这儿除了我，再没有别人\n会因为某些原因不对战\l反而去钓鱼。\p嗯？这儿什么都钓不到？\n好失望……$"

BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol:
    .string "今天，不论发生什么，我都要\n坚持战斗下去，直到获得奖章为止。$"

BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome:
    .string "嗯？你要去挑战\n对战巨蛋？\p祝你好运，\n希望我们都会一路获胜下去，\l然后在挑战中相遇。$"

BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa:
    .string "爷爷，过来过来！\n对战巨蛋在这儿！\l一定要赢啊，爷爷！$"

BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe:
    .string "啊，这儿就是对战巨蛋了。\n我不会被绅士打败的！\p对了，入口在哪儿？$"

BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo:
    .string "就在不久之前，这里\n还是一片荒原。\p但现在看看这里吧！简直是奇迹！\n我要带妈妈来看看。$"

BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier:
    .string "终于到达\n对战开拓区了！\p靠我的美貌和才能，\n肯定很快会成为焦点的！$"

BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople:
    .string "嘎吱嘎吱……\p这广场上好像聚集了\n很多非常强的人啊。\p嘎吱嘎吱……$"

BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike:
    .string "嘎吱嘎吱……\p刚才在对战管道\n看到了一个目光很可怕的\l大姐姐。\p嘎吱嘎吱……\p她冲我吼：“别吃了！”\n然后揍了我一顿。\p真可怕的经历啊！\p嘎吱嘎吱……$"

BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet:
    .string "哈，你在叫给自己听吗？\n那种东西什么都不是！\p看看，我为他加油的时候，\n我们交汇的眼神里都射出了火花！$"

BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering:
    .string "什——么？！\n哼！\p这是因为我恰好\n坐在你旁边而已！\p是因为我的加油声很大，\n巨蛋超级巨星才会注意到这边的！$"

BattleFrontier_OutsideWest_Text_DomeAceIsMine:
    .string "啊，嘘～嘘～\n吵死了，安静一下啦！\p你该让你那些不坚定的追星族们\n给别的道馆馆主加油！\p巨蛋超级巨星是我的！\n是只属于我的偶像！$"

BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers:
    .string "那边吵架的那些人……\p真不敢相信那些人以前也都是\n训练家，而且还挺厉害的。\p他们以前非常强，\n同时也相当有名气。\p但在一场联赛中，他们都被\n某个训练家击倒了。\p他们完全地失败了，\n同时开始对那个训练家神魂颠倒。\p而现在，他们仅仅是那个训练家的\n狂热者而已，每天每天地在\l对战巨蛋为他们的偶像加油助威。$"

BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier:
    .string "有传言说有人在\n对战开拓区的某处看到\l一种尾巴异常长的宝可梦。\p我敢肯定，它一定很可爱……\p啊，挑战什么的都一边去吧，\n我要去找那个小东西了！$"

