.set LOCALID_GREETER, 1
.set LOCALID_GUIDE, 2
.set LOCALID_SCOTT, 4

BattleFrontier_ReceptionGate_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_ReceptionGate_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_ReceptionGate_OnTransition
	.byte 0

BattleFrontier_ReceptionGate_OnTransition:
	setflag FLAG_LANDMARK_BATTLE_FRONTIER
	end

BattleFrontier_ReceptionGate_OnFrame:
	map_script_2 VAR_HAS_ENTERED_BATTLE_FRONTIER, 0, BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering
	.2byte 0

BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering::
	lockall
	setvar VAR_HAS_ENTERED_BATTLE_FRONTIER, 1
	playse SE_PIN
	applymovement LOCALID_GREETER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_GREETER, Common_Movement_Delay48
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter
	waitmovement 0
	goto BattleFrontier_ReceptionGate_EventScript_ScottScene
	end

BattleFrontier_ReceptionGate_EventScript_ScottScene::
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IssueFrontierPass, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass
	waitfanfare
	waitmessage
	msgbox BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass, MSGBOX_DEFAULT
	setflag FLAG_SYS_FRONTIER_PASS
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GREETER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_GUIDE, Common_Movement_WalkInPlaceFasterUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_GREETER, Common_Movement_ExclamationMark
	applymovement LOCALID_GUIDE, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GREETER, BattleFrontier_ReceptionGate_Movement_GreeterFaceScott
	applymovement LOCALID_GUIDE, BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerFaceScott
	applymovement LOCALID_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottEnter
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_SCOTT
	releaseall
	end

BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter:
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_PlayerFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

@ Unused
BattleFrontier_ReceptionGate_Movement_WalkDown:
	walk_down
	walk_down
	step_end

BattleFrontier_ReceptionGate_Movement_ScottEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_ScottExit:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_ReceptionGate_Movement_GreeterFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

BattleFrontier_ReceptionGate_EventScript_Greeter::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FacilityGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFacilities, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich2
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BF_RECEPTIONIST
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_BattleTower
	case 1, BattleFrontier_ReceptionGate_EventScript_BattleDome
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePalace
	case 3, BattleFrontier_ReceptionGate_EventScript_BattleArena
	case 4, BattleFrontier_ReceptionGate_EventScript_BattleFactory
	case 5, BattleFrontier_ReceptionGate_EventScript_BattlePike
	case 6, BattleFrontier_ReceptionGate_EventScript_BattlePyramid
	case 7, BattleFrontier_ReceptionGate_EventScript_RankingHall
	case 8, BattleFrontier_ReceptionGate_EventScript_ExchangeCorner
	case 9, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	end

BattleFrontier_ReceptionGate_EventScript_BattleTower::
	msgbox BattleFrontier_ReceptionGate_Text_BattleTowerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleDome::
	msgbox BattleFrontier_ReceptionGate_Text_BattleDomeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePalace::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePalaceInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleArena::
	msgbox BattleFrontier_ReceptionGate_Text_BattleArenaInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleFactory::
	msgbox BattleFrontier_ReceptionGate_Text_BattleFactoryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePike::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePikeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePyramid::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePyramidInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RankingHall::
	msgbox BattleFrontier_ReceptionGate_Text_RankingHallInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExchangeCorner::
	msgbox BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_RulesGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToRules, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhat
	waitmessage
	multichoice 15, 0, MULTI_FRONTIER_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_LevelMode
	case 1, BattleFrontier_ReceptionGate_EventScript_Level50
	case 2, BattleFrontier_ReceptionGate_EventScript_OpenLevel
	case 3, BattleFrontier_ReceptionGate_EventScript_MonEntry
	case 4, BattleFrontier_ReceptionGate_EventScript_HoldItems
	case 5, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	end

BattleFrontier_ReceptionGate_EventScript_LevelMode::
	msgbox BattleFrontier_ReceptionGate_Text_LevelModeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_Level50::
	msgbox BattleFrontier_ReceptionGate_Text_Level50Info, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_OpenLevel::
	msgbox BattleFrontier_ReceptionGate_Text_OpenLevelInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_MonEntry::
	msgbox BattleFrontier_ReceptionGate_Text_MonEntryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_HoldItems::
	msgbox BattleFrontier_ReceptionGate_Text_HoldItemsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FrontierPassGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich1
	waitmessage
	multichoice 16, 4, MULTI_FRONTIER_PASS_INFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_Symbols
	case 1, BattleFrontier_ReceptionGate_EventScript_RecordBattle
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePoints
	case 3, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	end

BattleFrontier_ReceptionGate_EventScript_Symbols::
	msgbox BattleFrontier_ReceptionGate_Text_SymbolsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RecordBattle::
	msgbox BattleFrontier_ReceptionGate_Text_RecordedBattleInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePoints::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePointsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay:
    .string "你是第一次来吗？\n请走这边！$"

BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier:
    .string "这里是宝可梦对战的最前线！\n欢迎来到对战开拓区！$"

BattleFrontier_ReceptionGate_Text_IssueFrontierPass:
    .string "每一位新的来访者都会\n得到一张开拓区通行证。\p有了它就可以参加\n对战开拓区各种设施。\p给，这是你的！$"

BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass:
    .string "{PLAYER}得到了\n开拓区通行证。$"

BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass:
    .string "{PLAYER}把训练师卡片\n放进了开拓区通行证里。$"

BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier:
    .string "希望你喜欢\n对战开拓区的一切！$"

BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame:
    .string "？？？：嗨，这不是{PLAYER}{KUN}吗！\n你来了！$"

BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay:
    .string "导游：啊，亚希达先生！\n您好！$"

BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere:
    .string "亚希达：很高兴能在这儿看见你，\n真的很高兴！\p希望你能在这儿好好转转，\n每个地方都去看看吧。\p当然，也希望你能在这里\n体会到战斗的精华。\p我在这儿也有住处，\n有空的话就过来歇歇脚吧。$"

BattleFrontier_ReceptionGate_Text_YourGuideToFacilities:
    .string "我负责向你介绍\n对战开拓区的各种设施。$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich2:
    .string "你想知道什么？$"

BattleFrontier_ReceptionGate_Text_BattleTowerInfo:
    .string "它是一座巨大的塔，被视作\n对战开拓区的标志。\p塔里面有四种对战房间，\n单人、双人、多人和\l联线多人对战房间。$"

BattleFrontier_ReceptionGate_Text_BattleDomeInfo:
    .string "对战巨蛋是那个好像一只\n巨大的蛋的建筑。\p里面会举行\n被称为对战锦标赛的活动。\p对战锦标赛有两种路线\n——单人和双人\l对战。$"

BattleFrontier_ReceptionGate_Text_BattlePalaceInfo:
    .string "对战宫殿是对战开拓区\n右侧的红色建筑。\p里面有两种对战大厅，分别\n进行单人和双打对战。$"

BattleFrontier_ReceptionGate_Text_BattleArenaInfo:
    .string "对战竞技场是位于\n对战开拓区中央偏右的\l道场一样的建筑。\p对战竞技场里面会举行\n名叫三回合定胜负锦标赛的活动。$"

BattleFrontier_ReceptionGate_Text_BattleFactoryInfo:
    .string "对战工厂就是离我们\n最近的那个大型建筑。\p里面举行\n交换式对战。\p交换式对战分两种，\n分别是单人和双人\l对战。$"

BattleFrontier_ReceptionGate_Text_BattlePikeInfo:
    .string "对战水管是位于\n对战开拓区中央偏左的\l像宝可梦一样的建筑。\p里面会举行\n选择式对战。$"

BattleFrontier_ReceptionGate_Text_BattlePyramidInfo:
    .string "对战金字塔就是那个\n巨大的金字塔。\p里面会举行\n追寻式战斗。$"

BattleFrontier_ReceptionGate_Text_RankingHallInfo:
    .string "排行榜位于\n对战塔附近。\p你可以在那里看到\n活跃在对战开拓区的\l训练师们所留下的\l非凡的成绩。$"

BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo:
    .string "交换服务中心位于\n对战塔附近。\p你可以用在对战开拓区\n得到的对战点数交换一些\l非同寻常的奖品。$"

BattleFrontier_ReceptionGate_Text_YourGuideToRules:
    .string "我负责向你介绍\n对战开拓区各设施里\l通用的一些\l基本规则。$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhat:
    .string "你想知道什么？$"

BattleFrontier_ReceptionGate_Text_LevelModeInfo:
    .string "对战开拓区里的\n每种挑战都分成两种——\l50级和自由级。$"

BattleFrontier_ReceptionGate_Text_Level50Info:
    .string "50级允许50级或以下的\n宝可梦参加。\p但是请记住，你并不会碰上\n使用50级以下宝可梦的\l训练师。\p这是对战开拓区的\n入门级战斗，\p如果你是新手，\n可以先来挑战它。$"

BattleFrontier_ReceptionGate_Text_OpenLevelInfo:
    .string "自由级对于\n参加宝可梦\l没有等级限制。\p你的对手的宝可梦等级\n会根据你自己的宝可梦等级\l而改变。\p但是，你不会碰上\n使用60级以下宝可梦的训练师。$"

BattleFrontier_ReceptionGate_Text_MonEntryInfo:
    .string "大部分宝可梦都可以参加\n所有设施里面的挑战，\p但蛋和某些特定的宝可梦\n不能参加。\p参加挑战的宝可梦数量\n根据挑战的不同而不同，\p但所有设施都不可以\n选择同样的两只\l或以上宝可梦参加。$"

BattleFrontier_ReceptionGate_Text_HoldItemsInfo:
    .string "参加对战开拓区的\n挑战时，每只宝可梦\l携带的物品都不能相同。\p参加之前请先确认\n每只参加的宝可梦\l都携带了不同的物品。$"

BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass:
    .string "我负责向你介绍开拓区通行证。$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich1:
    .string "你想知道什么？$"

BattleFrontier_ReceptionGate_Text_SymbolsInfo:
    .string "对战开拓区中有\n七种设施。\p在每一设施中，训练师的能力\n如果能够被认可，\l就能够得到一枚象征作为奖励。\p要想得到印记，训练师也许\n得连续打败许多其他训练师，\l也许得在同一活动中不断胜出。\p确实，想要得到印记并不容易，\n祝你好运！$"

BattleFrontier_ReceptionGate_Text_RecordedBattleInfo:
    .string "可以在你的开拓区通行证上面\n记录下你的某一场战斗。\p你可以记录你与你的\n朋友们的战斗，\p或者记录下在对战开拓区\n进行过的一场战斗，包括\l在对战水管或对战金字塔里\l进行的比赛。\p战斗结束时你可以选择\n是否要记录战斗。$"

BattleFrontier_ReceptionGate_Text_BattlePointsInfo:
    .string "对战点数是送给\n对战开拓区中战斗非常出色的\l训练师的奖励。\p你可以在交换服务中心\n用你的对战点数\l兑换其他奖品。$"

