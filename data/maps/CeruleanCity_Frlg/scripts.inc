CeruleanCity_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeruleanCity_OnTransition
	.byte 0

CeruleanCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_CERULEAN_CITY
	call_if_unset FLAG_GOT_SS_TICKET, CeruleanCity_EventScript_BlockExits
	end

CeruleanCity_EventScript_BlockExits::
	setobjectxyperm LOCALID_CERULEAN_POLICEMAN, 30, 12
	setobjectxyperm LOCALID_CERULEAN_SLOWBRO, 26, 31
	setobjectxyperm LOCALID_CERULEAN_LASS, 27, 31
	return

CeruleanCity_EventScript_RivalTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto CeruleanCity_EventScript_Rival
	end

CeruleanCity_EventScript_RivalTriggerMid::
	lockall
	setvar VAR_TEMP_1, 1
	setobjectxyperm LOCALID_CERULEAN_RIVAL, 23, 0
	goto CeruleanCity_EventScript_Rival
	end

CeruleanCity_EventScript_RivalTriggerRight::
	lockall
	setvar VAR_TEMP_1, 2
	setobjectxyperm LOCALID_CERULEAN_RIVAL, 24, 0
	goto CeruleanCity_EventScript_Rival
	end

CeruleanCity_EventScript_Rival::
	textcolor NPC_TEXT_COLOR_MALE
	setvar VAR_MAP_SCENE_ROUTE22, 2
	playbgm MUS_RG_ENCOUNTER_RIVAL, 0
	addobject LOCALID_CERULEAN_RIVAL
	applymovement LOCALID_CERULEAN_RIVAL, CeruleanCity_Movement_RivalEnter
	waitmovement 0
	msgbox CeruleanCity_Text_RivalIntro
	setvar VAR_LAST_TALKED, LOCALID_CERULEAN_RIVAL
	call_if_eq VAR_STARTER_MON, 2, CeruleanCity_EventScript_RivalSquirtle
	call_if_eq VAR_STARTER_MON, 1, CeruleanCity_EventScript_RivalBulbasaur
	call_if_eq VAR_STARTER_MON, 0, CeruleanCity_EventScript_RivalCharmander
	famechecker FAMECHECKER_BILL, 0
	msgbox CeruleanCity_Text_RivalPostBattle
	closemessage
	playbgm MUS_RG_RIVAL_EXIT, 0
	call_if_eq VAR_TEMP_1, 0, CeruleanCity_EventScript_RivalStartExit
	call_if_eq VAR_TEMP_1, 1, CeruleanCity_EventScript_RivalStartExit
	call_if_eq VAR_TEMP_1, 2, CeruleanCity_EventScript_RivalStartExitRight
	msgbox CeruleanCity_Text_OhRightLittlePresentAsFavor
	setvar VAR_MAP_SCENE_CERULEAN_CITY_RIVAL, 1
	setflag FLAG_GOT_FAME_CHECKER
	giveitem ITEM_FAME_CHECKER
	msgbox CeruleanCity_Text_ExplainFameCheckerSmellYa
	closemessage
	applymovement LOCALID_CERULEAN_RIVAL, CeruleanCity_Movement_RivalExit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_CERULEAN_RIVAL
	releaseall
	end

CeruleanCity_EventScript_RivalSquirtle::
	trainerbattle_no_intro TRAINER_RIVAL_CERULEAN_SQUIRTLE, CeruleanCity_Text_RivalDefeat
	return

CeruleanCity_EventScript_RivalBulbasaur::
	trainerbattle_no_intro TRAINER_RIVAL_CERULEAN_BULBASAUR, CeruleanCity_Text_RivalDefeat
	return

CeruleanCity_EventScript_RivalCharmander::
	trainerbattle_no_intro TRAINER_RIVAL_CERULEAN_CHARMANDER, CeruleanCity_Text_RivalDefeat
	return

CeruleanCity_EventScript_RivalStartExit::
	applymovement LOCALID_PLAYER, CeruleanCity_Movement_PlayerWatchRivalExit
	applymovement LOCALID_CERULEAN_RIVAL, CeruleanCity_Movement_RivalStartExit
	waitmovement 0
	return

CeruleanCity_EventScript_RivalStartExitRight::
	applymovement LOCALID_PLAYER, CeruleanCity_Movement_PlayerWatchRivalExitRight
	applymovement LOCALID_CERULEAN_RIVAL, CeruleanCity_Movement_RivalStartExitRight
	waitmovement 0
	return

CeruleanCity_Movement_PlayerWatchRivalExit::
	delay_16
	delay_8
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_down
	step_end

CeruleanCity_Movement_PlayerWatchRivalExitRight::
	delay_16
	delay_8
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

CeruleanCity_Movement_RivalEnter::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

CeruleanCity_Movement_RivalStartExit::
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	delay_16
	delay_16
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

CeruleanCity_Movement_RivalStartExitRight::
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	delay_16
	delay_16
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

CeruleanCity_Movement_RivalExit::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

CeruleanCity_EventScript_Grunt::
	lock
	faceplayer
	goto_if_defeated TRAINER_TEAM_ROCKET_GRUNT_5, CeruleanCity_EventScript_GruntDefeated
	message CeruleanCity_Text_GruntIntro
	waitmessage
	playbgm MUS_RG_ENCOUNTER_ROCKET, 0
	waitbuttonpress
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_5, CeruleanCity_Text_GruntDefeat
	setvar VAR_MAP_SCENE_CERULEAN_CITY_ROCKET, 1
	goto CeruleanCity_EventScript_GruntDefeated
	end

CeruleanCity_EventScript_GruntDefeated::
	msgbox CeruleanCity_Text_OkayIllReturnStolenTM
	checkitemspace ITEM_TM28
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_EventScript_NoRoomForTM28
	giveitem_msg CeruleanCity_Text_RecoveredTM28FromGrunt, ITEM_TM28
	msgbox CeruleanCity_Text_BetterGetMovingBye
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_CERULEAN_GRUNT
	fadescreenswapbuffers FADE_FROM_BLACK
	setflag FLAG_GOT_TM28_FROM_ROCKET
	release
	end

CeruleanCity_EventScript_NoRoomForTM28::
	textcolor NPC_TEXT_COLOR_MALE
	msgbox CeruleanCity_Text_MakeRoomForThisCantRun
	release
	end

CeruleanCity_EventScript_GruntTriggerTop::
	lockall
	setvar VAR_TEMP_1, 0
	applymovement LOCALID_CERULEAN_GRUNT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	goto CeruleanCity_EventScript_GruntTrigger
	end

CeruleanCity_EventScript_GruntTriggerBottom::
	lockall
	setvar VAR_TEMP_1, 1
	applymovement LOCALID_CERULEAN_GRUNT, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto CeruleanCity_EventScript_GruntTrigger
	end

CeruleanCity_EventScript_GruntTrigger::
	textcolor NPC_TEXT_COLOR_MALE
	msgbox CeruleanCity_Text_GruntIntro
	setvar VAR_LAST_TALKED, LOCALID_CERULEAN_GRUNT
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_5, CeruleanCity_Text_GruntDefeat
	setvar VAR_MAP_SCENE_CERULEAN_CITY_ROCKET, 1
	goto CeruleanCity_EventScript_GruntDefeated
	end

CeruleanCity_EventScript_Policeman::
	lock
	faceplayer
	msgbox CeruleanCity_Text_PeopleHereWereRobbed
	closemessage
	applymovement LOCALID_CERULEAN_POLICEMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CeruleanCity_EventScript_LittleBoy::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SS_TICKET, CeruleanCity_EventScript_LittleBoySlowbroMoved
	msgbox CeruleanCity_Text_IfSlowbroWasntThereCouldCutTree
	release
	end

CeruleanCity_EventScript_LittleBoySlowbroMoved::
	msgbox CeruleanCity_Text_YouCanCutDownSmallTrees
	release
	end

CeruleanCity_EventScript_BaldingMan::
	msgbox CeruleanCity_Text_PokemonEncyclopediaAmusing, MSGBOX_NPC
	end

CeruleanCity_EventScript_Youngster::
	msgbox CeruleanCity_Text_TrainerLifeIsToughIsntIt, MSGBOX_NPC
	end

CeruleanCity_EventScript_CeruleanCaveGuard::
	msgbox CeruleanCity_Text_ThisIsCeruleanCave, MSGBOX_NPC
	end

CeruleanCity_EventScript_Woman::
	lock
	faceplayer
	msgbox CeruleanCity_Text_WantBrightRedBicycle
	closemessage
	applymovement LOCALID_CERULEAN_WOMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CeruleanCity_EventScript_Lass::
	lock
	random 3
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, 0, CeruleanCity_EventScript_SlowbroCommand1
	call_if_eq VAR_0x8008, 1, CeruleanCity_EventScript_SlowbroCommand2
	call_if_eq VAR_0x8008, 2, CeruleanCity_EventScript_SlowbroCommand3
	waitmessage
	delay 40
	playse SE_PIN
	applymovement LOCALID_CERULEAN_SLOWBRO, Common_Movement_QuestionMark
	waitmovement 0
	delay 30
	call_if_eq VAR_0x8008, 0, CeruleanCity_EventScript_SlowbroFailed1
	call_if_eq VAR_0x8008, 1, CeruleanCity_EventScript_SlowbroFailed2
	call_if_eq VAR_0x8008, 2, CeruleanCity_EventScript_SlowbroFailed3
	release
	end

CeruleanCity_EventScript_SlowbroCommand1::
	message CeruleanCity_Text_SlowbroUseSonicboom
	return

CeruleanCity_EventScript_SlowbroCommand2::
	message CeruleanCity_Text_SlowbroPunch
	return

CeruleanCity_EventScript_SlowbroCommand3::
	message CeruleanCity_Text_SlowbroWithdraw
	return

CeruleanCity_EventScript_SlowbroFailed1::
	msgbox CeruleanCity_Text_SlowbroPayAttention
	return

CeruleanCity_EventScript_SlowbroFailed2::
	msgbox CeruleanCity_Text_NoYouBlewItAgain
	return

CeruleanCity_EventScript_SlowbroFailed3::
	msgbox CeruleanCity_Text_HardToControlMonsObedience
	return

CeruleanCity_EventScript_Slowbro::
	lock
	random 4
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, 0, CeruleanCity_EventScript_SlowbroText1
	call_if_eq VAR_0x8008, 1, CeruleanCity_EventScript_SlowbroText2
	call_if_eq VAR_0x8008, 2, CeruleanCity_EventScript_SlowbroText3
	call_if_eq VAR_0x8008, 3, CeruleanCity_EventScript_SlowbroText4
	release
	end

CeruleanCity_EventScript_SlowbroText1::
	msgbox CeruleanCity_Text_SlowbroTookSnooze
	return

CeruleanCity_EventScript_SlowbroText2::
	msgbox CeruleanCity_Text_SlowbroLoafingAround
	return

CeruleanCity_EventScript_SlowbroText3::
	msgbox CeruleanCity_Text_SlowbroTurnedAway
	return

CeruleanCity_EventScript_SlowbroText4::
	msgbox CeruleanCity_Text_SlowbroIgnoredOrders
	return

CeruleanCity_EventScript_CitySign::
	msgbox CeruleanCity_Text_CitySign, MSGBOX_SIGN
	end

CeruleanCity_EventScript_TrainerTips::
	msgbox CeruleanCity_Text_TrainerTipsHeldItems, MSGBOX_SIGN
	end

CeruleanCity_EventScript_BikeShopSign::
	msgbox CeruleanCity_Text_BikeShopSign, MSGBOX_SIGN
	end

CeruleanCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_MISTY, 0
	msgbox CeruleanCity_Text_GymSign
	releaseall
	end

CeruleanCity_Text_RivalIntro::
    .string "{RIVAL} 哟！是{PLAYER}啊！\p"
    .string "你还在这里\n"
    .string "独自徘徊么？\p"
    .string "我可是做得很好！我收服了一群\n"
    .string "既强壮又聪明的宝可梦！\p"
    .string "来吧，让我看看你收服了什么！\n"
    .string "{PLAYER}$"

CeruleanCity_Text_RivalDefeat::
    .string "嘿！\n"
    .string "放松点！\l"
    .string "你已经赢了！$"

CeruleanCity_Text_RivalPostBattle::
    .string "{RIVAL}：嘿，你猜怎么着？\p"
    .string "我去了趟正辉的家，叫他让我\n"
    .string "看了他稀有的宝可梦。\p"
    .string "这样就使我的宝可梦图鉴\n"
    .string "增加了好多数据！\p"
    .string "毕竟啊正辉作为一个怪兽狂\n"
    .string "在全世界都很有名。\p"
    .string "就是他开发了\n"
    .string "宝可梦存储系统。\p"
    .string "既然你正在使用他的系统\n"
    .string "就应该去好好谢谢他。\p"
    .string "好了我得走了。\n"
    .string "下次再见咯！$"

CeruleanCity_Text_OhRightLittlePresentAsFavor::
    .string "噢对了。\p"
    .string "看到你总是不声不响的跟在我身后。\n"
    .string "我有些不好意思。不，我是真心的。\p"
    .string "所以呐，我要送你一个\n"
    .string "小小的礼物。$"

CeruleanCity_Text_ExplainFameCheckerSmellYa::
    .string "虽然这个东西废话很多……\n"
    .string "但是东西本身倒不坏。\p"
    .string "我不需要它是因为\n"
    .string "我才不喜欢和别人唠唠叨叨的。\p"
    .string "现在我可是真的要走了，\n"
    .string "有缘再会了！$"

CeruleanCity_Text_GruntIntro::
    .string "嘿！给我站住！\n"
    .string "这里可不是你的院子！\p"
    .string "……什么？\n"
    .string "我是干什么的\p"
    .string "我是路过打酱油的！\n"
    .string "……你不相信我？{PLAY_BGM}{MUS_RG_ENCOUNTER_ROCKET}$"

CeruleanCity_Text_GruntDefeat::
    .string "成员：别打了！我投降！\n"
    .string "我会马上离开的！$"

CeruleanCity_Text_OkayIllReturnStolenTM::
    .string "……我懂了。\n"
    .string "我会把我偷的技能交出来的。$"

CeruleanCity_Text_RecoveredTM28FromGrunt::
    .string "{PLAYER}从火箭队队员那里\n"
    .string "获得了TM28$"

CeruleanCity_Text_BetterGetMovingBye::
    .string "我想我最好得撤了！\n"
    .string "再见！$"

CeruleanCity_Text_MakeRoomForThisCantRun::
    .string "赶快把你的包腾出地方！\n"
    .string "给了你这个我才能走！$"

CeruleanCity_Text_TrainerLifeIsToughIsntIt::
    .string "你也是一个训练家对不对？\p"
    .string "收集，战斗……\n"
    .string "这是一条艰辛的路啊，可不是吗？$"

CeruleanCity_Text_YouCanCutDownSmallTrees::
    .string "你知道用居合斩能\n"
    .string "砍倒细小的树吗？\p"
    .string "就算是那个商店面前的小树\n"
    .string "也可以用居合斩砍倒。\p"
    .string "我认为有条路在那附近。$"

CeruleanCity_Text_IfSlowbroWasntThereCouldCutTree::
    .string "如果那只呆壳兽不在这里的话\n"
    .string "你就能用居合斩砍倒那边的小树了。\p"
    .string "这样一来，\n"
    .string "你就可以到另一边去了。\p"
    .string "虽然也有办法绕路过去。$"

CeruleanCity_Text_PokemonEncyclopediaAmusing::
    .string "你在做关于宝可梦的百科全书吧？\n"
    .string "听起来真厉害啊。$"

CeruleanCity_Text_PeopleHereWereRobbed::
    .string "这家人被抢了。\p"
    .string "很明显这种十恶不赦的事\n"
    .string "背后又有火箭队在作怪！\p"
    .string "甚至我们的警力集结\n"
    .string "起来都敌不过火箭队！$"

CeruleanCity_Text_SlowbroUseSonicboom::
    .string "好！呆壳兽！\n"
    .string "使用音爆！$"

CeruleanCity_Text_SlowbroPayAttention::
    .string "来吧，呆壳兽，注意了！$"

CeruleanCity_Text_SlowbroPunch::
    .string "呆壳兽，给我狠狠地攻击！$"

CeruleanCity_Text_NoYouBlewItAgain::
    .string "不！\n"
    .string "你又搞砸了！$"

CeruleanCity_Text_SlowbroWithdraw::
    .string "呆壳兽 撤退$"

CeruleanCity_Text_HardToControlMonsObedience::
    .string "不对！那样不对！\n"
    .string "想要控制好宝可梦是很困难的！\p"
    .string "你的宝可梦对你信赖与否\n"
    .string "取决于你作为一名训练家的能力。$"

CeruleanCity_Text_SlowbroTookSnooze::
    .string "呆壳兽打起了盹……$"

CeruleanCity_Text_SlowbroLoafingAround::
    .string "呆壳兽在四处闲逛……$"

CeruleanCity_Text_SlowbroTurnedAway::
    .string "呆壳兽躲得远远的……$"

CeruleanCity_Text_SlowbroIgnoredOrders::
    .string "被呆壳兽无视了……$"

CeruleanCity_Text_WantBrightRedBicycle::
    .string "我想要一辆红色的自行车。\p"
    .string "有了它我就会把它放在家里，\n"
    .string "这样它就不会被弄脏了。$"

CeruleanCity_Text_ThisIsCeruleanCave::
    .string "从这里进去就是华蓝洞窟了。\p"
    .string "那只强大得恐怖的宝可梦\n"
    .string "就栖息在这里面。\p"
    .string "只有那些特别的训练家\n"
    .string "才能够被允许入内。\p"
    .string "如果你成为了\n"
    .string "宝可梦联盟\l"
    .string "的联盟冠军。\p"
    .string "才有足够的\n"
    .string "实力进去挑战。$"

CeruleanCity_Text_CitySign::
    .string "华蓝市\n"
    .string "被蓝色所环绕着的\l"
    .string "神秘城市$"

CeruleanCity_Text_TrainerTipsHeldItems::
    .string "训练家贴士\p"
    .string "一只宝可梦只可以装备\n"
    .string "一个道具。\p"
    .string "其中一些道具\n"
    .string "甚至能在战斗使用。$"

CeruleanCity_Text_BikeShopSign::
    .string "轻松愉快的在草地和洞窟间驰骋！\n"
    .string "自行车行$"

CeruleanCity_Text_GymSign::
    .string "华蓝市宝可梦道馆\n"
    .string "馆主：小霞\l"
    .string "男孩子气的美人鱼！$"

