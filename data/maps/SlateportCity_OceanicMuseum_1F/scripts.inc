.set LOCALID_FAMILIAR_GRUNT, 13

SlateportCity_OceanicMuseum_1F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_1F_EventScript_EntranceAttendant::
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeLeft::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeRight::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee::
	showmoneybox 0, 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee
	closemessage
	hidemoneybox
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee::
	checkmoney 50
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 50
	updatemoneybox
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney::
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway
	msgbox SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway::
	msgbox SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt4::
	msgbox SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt5::
	msgbox SlateportCity_OceanicMuseum_1F_Text_RustboroBungled, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt6::
	msgbox SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_WhirlpoolExperiment::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_WaterfallExperiment::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanSoilDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_BeachSandDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_FossilDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_FossilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_DepthMeasuringMachine::
	msgbox SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron4::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGrunt::
	lock
	faceplayer
	delay 8
	playse SE_PIN
	applymovement LOCALID_FAMILIAR_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FAMILIAR_GRUNT, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_THIEF
	goto_if_eq VAR_RESULT, 0, SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief
	setflag FLAG_RECEIVED_TM_THIEF
	msgbox SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_NORTH, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth
	goto_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth
	goto_if_eq VAR_FACING, DIR_WEST, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	goto_if_eq VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth::
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth
	applymovement LOCALID_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth::
	applymovement LOCALID_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast::
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast
	applymovement LOCALID_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited::
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_FAMILIAR_AQUA_GRUNT
	playse SE_EXIT
	removeobject LOCALID_FAMILIAR_GRUNT
	release
	end

SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief::
	msgbox SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis, MSGBOX_DEFAULT
	release
	end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast:
	delay_16
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit:
	face_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter:
    .string "欢迎来到海之博物馆，\p参观费50$。\n您想参观吗？$"

SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself:
    .string "祝您愉快。$"

SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney:
    .string "嗯？很抱歉，\n您似乎没有带够钱。$"

SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup:
    .string "哦？您和刚刚离开的那些人\n是一起的吗？\p只剩下您一个了，\n您最好快些赶上他们！$"

SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll:
    .string "我们水舰队永远\n站在正义的一方！$"

SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere:
    .string "上面要我们在这儿集合，\n所以我们都来了，但是…\p老大还没来。$"

SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich:
    .string "如果偷走这儿的东西，\n能让我一夜暴富吗？$"

SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds:
    .string "我觉得在这里\n我会做出些坏事来…$"

SlateportCity_OceanicMuseum_1F_Text_RustboroBungled:
    .string "如果不是那些蠢货在\n卡那兹市搞砸了，我们怎么会到这儿来！$"

SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney:
    .string "我没带够50$，从接待员那儿\n混进来花了不少时间。$"

SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling:
    .string "我想了解大海，\n把那些知识融入我的战斗中。$"

SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel:
    .string "一看到大海\n我就会感到头晕！\p对我来说，库斯诺吉馆长\n是最大的榜样！$"

SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow:
    .string "大海一望无际，\n无限深沉…\p里面一定还有很多\n我们所不知道的宝可梦。$"

SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon:
    .string "我想要只海中的宝可梦，\p抱着它们的感觉\n一定很奇妙。$"

SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis:
    .string "哎呀！\n你在这儿干什么？\p我？我是之前被你狠狠教训过的\n水舰队队员，记得吗？\l就在卡绿隧道那里？\p这个给你！\n原谅我吧！$"

SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain:
    .string "比起我来，\n这个招式学习器更适合你。\p希望下次不要再见面了！\n啊哈哈哈！$"

SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis:
    .string "啊噢，拜托了！\n拿着这个，放我走吧！$"

SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment:
    .string "蓝色的液体在\n玻璃容器中盘旋着。\p“利用风力人工制造\n漩涡的实验”。$"

SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment:
    .string "一个红色的球\n在玻璃容器里上下跳动。\p“利用球的浮力\n模拟攀瀑的实验”。$"

SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay:
    .string "海底土壤的\n样品。\p“生物遗骸沉到\n海洋底部，经过多年\l形成沉积层。\p研究这些地层，\n能够揭示出远古的历史”。$"

SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay:
    .string "海滩沙子的样品。\p“河流冲下\n高山上的石块，在颠簸中\l粉碎成小石子，\p最后成为海滩上\n松散的沙粒”。$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1:
    .string "“海洋小常识 1\n为什么海水是蓝的？\p光分成多种颜色，\p穿过海水时，\n大部分光失去了颜色。\p但蓝色光能留住颜色，\n所以海水看上去就成了蓝色。”$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2:
    .string "“海洋小常识 2\n为什么海水是咸的？\p“海水中溶解的盐\n以钠离子和氯离子的形式存在。\p这些离子由礁石分离，\n被雨水冲进大海。\p溶解的盐慢慢聚集，\n使海水变咸。”$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3:
    .string "“海洋小常识 3\n大陆和海洋哪个更大？\p海洋占据星球上70%的\n地表，剩下的是大陆。\p因此海洋的面积\n是大陆的两倍以上。”$"

SlateportCity_OceanicMuseum_1F_Text_FossilDisplay:
    .string "有波浪形突起的化石。\p“洋底的泥土经过\n潮汐的冲刷，\p表面留下了\n凹凸不平的痕迹。\p泥土变成化石后，\n就形成了波纹石。”$"

SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine:
    .string "半球型的玻璃罩下面\n有奇怪的机器在运转。\p也许是用来测量\n什么东西的深度的…$"

