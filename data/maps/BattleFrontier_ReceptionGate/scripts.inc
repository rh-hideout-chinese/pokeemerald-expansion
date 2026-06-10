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
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_Delay48
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter
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
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_ExclamationMark
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, BattleFrontier_ReceptionGate_Movement_GreeterFaceScott
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott
	applymovement LOCALID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerFaceScott
	applymovement LOCALID_FRONTIER_RECEPTION_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottEnter
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_FRONTIER_RECEPTION_SCOTT
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
    .string "您是第一次来吗？\n这边请！$"

BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier:
    .string "这里是宝可梦对战的最前线！\n欢迎来到对战开拓区！$"

BattleFrontier_ReceptionGate_Text_IssueFrontierPass:
    .string "每位初次来访的客人都可以\n得到一张开拓通行证。\p它可以在对战开拓区的\n所有设施中使用。\p给，这是您的！$"

BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass:
    .string "{PLAYER}获得了\n开拓通行证。$"

BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass:
    .string "{PLAYER}把训练家卡\n收入了开拓通行证中。$"

BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier:
    .string "希望您能尽情享受\n对战开拓区的一切！$"

BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame:
    .string "？？？：嗨，这不是{PLAYER}{KUN}吗！\n你终于来啦！$"

BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay:
    .string "向导：啊，亚希达先生！\n您好！$"

BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere:
    .string "亚希达：能在这里见到你真是太好了，\n真的！\p希望你慢慢探索\n这里的每个角落。\p当然，也希望你能在这里\n体验到最纯粹的对战精髓。\p我在这儿也有房间，\n有空记得随时来坐坐。$"

BattleFrontier_ReceptionGate_Text_YourGuideToFacilities:
    .string "我是您的对战开拓区的\n各个设施的向导。$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich2:
    .string "您想了解哪个设施呢？$"

BattleFrontier_ReceptionGate_Text_BattleTowerInfo:
    .string "这座巨大的高塔被视为\n对战开拓区的标志。\p塔内有4种类型的对战间，\n分别用于单打、双打、多人和\l多人连线对战。$"

BattleFrontier_ReceptionGate_Text_BattleDomeInfo:
    .string "对战巨蛋是外形像是巨大的\n蛋一样的建筑。\p这里会举办名为\n对战锦标赛的活动。\p对战锦标赛有2种模式——\n单打和双打对战。$"

BattleFrontier_ReceptionGate_Text_BattlePalaceInfo:
    .string "对战宫殿是位于对战开拓区\n右侧的红色建筑。\p里面有2种对战厅，\n分别用于单打和双打对战。$"

BattleFrontier_ReceptionGate_Text_BattleArenaInfo:
    .string "对战竞技场是位于对战开拓区\n中央偏右的道场式建筑。\p这里会举办名为三回合\n定胜负锦标赛的活动。$"

BattleFrontier_ReceptionGate_Text_BattleFactoryInfo:
    .string "对战工厂是离我们最近的那个\n大型建筑。\p这里会举办名为\n交换式对战的活动。\p交换式对战分2种，\n分别是单打和双打对战。$"

BattleFrontier_ReceptionGate_Text_BattlePikeInfo:
    .string "对战管道是位于对战开拓区\n中央偏左的宝可梦造型的建筑。\p这里会举办名为\n选择式对战的活动。$"

BattleFrontier_ReceptionGate_Text_BattlePyramidInfo:
    .string "对战金字塔是巨大的金字塔建筑。\p这里会举办名为\n探索式对战的活动。$"

BattleFrontier_ReceptionGate_Text_RankingHallInfo:
    .string "排名大厅位于对战塔附近。\p那里可以看到挑战过对战开拓区各个\n设施的训练家们所留下的非凡纪录。$"

BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo:
    .string "兑换服务区位于对战塔附近。\p可以用在对战开拓区得到的对战点数\n兑换精美的奖品。$"

BattleFrontier_ReceptionGate_Text_YourGuideToRules:
    .string "我是您的对战开拓区各个设施中\n各项通用基本规则的向导。$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhat:
    .string "您想了解什么内容呢？$"

BattleFrontier_ReceptionGate_Text_LevelModeInfo:
    .string "对战开拓区的所有挑战设施\n都提供2种模式可供选择——\lLv. 50级和自由等级。$"

BattleFrontier_ReceptionGate_Text_Level50Info:
    .string "Lv. 50级允许等级50级以内的\n宝可梦参加。\p但是，您遇到的训练家不会\n使用等级50以内的宝可梦。\p这是对战开拓区的\n入门级对战，\p我们建议您从这个模式\n开始挑战。$"

BattleFrontier_ReceptionGate_Text_OpenLevelInfo:
    .string "自由等级对于参加的宝可梦\n没有等级限制。\p对手的宝可梦等级会根据\n您的宝可梦等级进行调整。\p但是，您遇到的训练家不会\n使用等级60以内的宝可梦。$"

BattleFrontier_ReceptionGate_Text_MonEntryInfo:
    .string "绝大多数种类的宝可梦都可以\n参加所有设施里面的挑战，\p但蛋和某些特定种类的宝可梦\n无法参加。\p挑战所需的宝可梦数量\n取决于具体设施。\p但在所有设施中，都无法使用2只\n或以上的相同种类的宝可梦。$"

BattleFrontier_ReceptionGate_Text_HoldItemsInfo:
    .string "在对战开拓区参加挑战时，\n宝可梦不能携带相同的道具。\p请确保所有参加挑战的宝可梦\n都携带了不同的道具。$"

BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass:
    .string "我是您的开拓通行证向导。$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich1:
    .string "您想了解什么内容呢？$"

BattleFrontier_ReceptionGate_Text_SymbolsInfo:
    .string "对战开拓区共设有\n7个挑战设施。\p训练家若展现出卓越实力，\n就能获得各设施颁发的象征。\p要获得象征，训练家可能需要\n连续击败多位对手，\l或多次赢得赛事。\p赢得象征绝非易事，\n祝您好运！$"

BattleFrontier_ReceptionGate_Text_RecordedBattleInfo:
    .string "可以在您的开拓通行证上\n记录下您的一场对战。\p您可以记录您与朋友\n之间进行的对战，\p或记录下在对战开拓区进行过的对战，\n但不包括对战管道以及对战金字塔中\l的对战。\p对战结束时您可以选择\n是否要记录对战。$"

BattleFrontier_ReceptionGate_Text_BattlePointsInfo:
    .string "对战点数是向对战开拓区中表现出色\n的训练家给予的奖励。\p您可以在兑换服务区用\n对战点数兑换奖品。$"

