.set LOCALID_ARCHIE, 1
.set LOCALID_MAXIE, 2
.set LOCALID_TABITHA, 3
.set LOCALID_MAGMA_GRUNT_2, 22
.set LOCALID_MAGMA_GRUNT_1, 29


MtChimney_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MtChimney_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MtChimney_OnTransition
	.byte 0

MtChimney_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 1
	end

MtChimney_OnResume:
	setstepcallback STEP_CB_ASH
	end

MtChimney_EventScript_Archie::
	lock
	faceplayer
	call_if_unset FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieGoStopTeamMagma
	call_if_set FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieBusyFighting
	closemessage
	applymovement LOCALID_ARCHIE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_EVIL_LEADER_PLEASE_STOP
	release
	end

MtChimney_EventScript_ArchieGoStopTeamMagma::
	msgbox MtChimney_Text_ArchieGoStopTeamMagma, MSGBOX_DEFAULT
	return

MtChimney_EventScript_ArchieBusyFighting::
	msgbox MtChimney_Text_ArchieIHaveMyHandsFull, MSGBOX_DEFAULT
	return

MtChimney_EventScript_Maxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MtChimney_Text_MeteoriteWillActivateVolcano, MSGBOX_DEFAULT
	applymovement LOCALID_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAXIE, Common_Movement_Delay48
	waitmovement 0
	msgbox MtChimney_Text_MaxieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat
	msgbox MtChimney_Text_MaxieYouHaventSeenLastOfMagma, MSGBOX_DEFAULT
	closemessage
	delay 30
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAXIE
	removeobject LOCALID_MAGMA_GRUNT_1
	removeobject LOCALID_TABITHA
	removeobject LOCALID_MAGMA_GRUNT_2
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_MAGMA
	fadescreen FADE_FROM_BLACK
	setobjectxyperm LOCALID_ARCHIE, 10, 12
	addobject LOCALID_ARCHIE
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieApproachPlayerEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieApproachPlayerNorth
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MtChimney_Text_ArchieThankYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieExitEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieExitNorth
	removeobject LOCALID_ARCHIE
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA
	setflag FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY
	clearflag FLAG_HIDE_FALLARBOR_HOUSE_PROF_COZMO
	setflag FLAG_HIDE_METEOR_FALLS_1F_1R_COZMO
	clearflag FLAG_HIDE_MT_CHIMNEY_LAVA_COOKIE_LADY
	releaseall
	end

MtChimney_EventScript_ArchieApproachPlayerEast::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieApproachPlayerEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieApproachPlayerNorth::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieApproachPlayerNorth
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitEast::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieExitEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitNorth::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieExitNorth
	waitmovement 0
	return

MtChimney_EventScript_LavaCookieLady::
	lock
	faceplayer
	showmoneybox 0, 0
	msgbox MtChimney_Text_LavaCookiesJust200, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_DeclineLavaCookie
	checkmoney 200
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_NotEnoughMoney
	msgbox MtChimney_Text_ThankYouDear, MSGBOX_DEFAULT
	checkitemspace ITEM_LAVA_COOKIE
	call_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RemoveMoney
.if OW_SHOW_ITEM_DESCRIPTIONS == OW_ITEM_DESCRIPTIONS_OFF
	giveitem ITEM_LAVA_COOKIE
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_BagIsFull
	hidemoneybox
	release
	end

MtChimney_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end
.else
	hidemoneybox
	giveitem ITEM_LAVA_COOKIE
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_BagIsFull
	release
	end

MtChimney_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end
.endif @ OW_SHOW_ITEM_DESCRIPTIONS


MtChimney_EventScript_RemoveMoney::
	removemoney 200
	updatemoneybox
	return

MtChimney_EventScript_DeclineLavaCookie::
	msgbox MtChimney_Text_OhFineThen, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_NotEnoughMoney::
	msgbox MtChimney_Text_YouveNotGotTheMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_Movement_ArchieApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

MtChimney_Movement_ArchieExitEast:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_ArchieApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

MtChimney_Movement_ArchieExitNorth:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused2:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused3:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused4:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused5:
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused6:
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused7:
	delay_16
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused8:
	delay_16
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

MtChimney_Movement_Unused9:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused10:
	walk_down
	step_end

MtChimney_Movement_Unused11:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused12:
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused13:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused14:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_right
	step_end

MtChimney_Movement_Unused15:
	walk_left
	walk_in_place_faster_right
	delay_16
	step_end

MtChimney_EventScript_BusyAquaGrunt1::
	msgbox MtChimney_Text_MagmaOutnumbersUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt2::
	msgbox MtChimney_Text_LessHabitatForWaterPokemon, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt3::
	msgbox MtChimney_Text_MagmasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MT_CHIMNEY, MtChimney_Text_TabithaIntro, MtChimney_Text_TabithaDefeat
	msgbox MtChimney_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_2, MtChimney_Text_Grunt2Intro, MtChimney_Text_Grunt2Defeat
	msgbox MtChimney_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_BusyMagmaGrunt1::
	msgbox MtChimney_Text_TeamAquaAlwaysMessingWithPlans, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt2::
	msgbox MtChimney_Text_MeteoritesPackAmazingPower, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt3::
	msgbox MtChimney_Text_YouBetterNotMessWithUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt4::
	msgbox MtChimney_Text_AquasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt5::
	msgbox MtChimney_Text_DouseThemInFire, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt6::
	msgbox MtChimney_Text_KeepMakingMoreLand, MSGBOX_SIGN
	end

MtChimney_EventScript_MagmaPoochyena::
	msgbox MtChimney_Text_Bufoh, MSGBOX_SIGN
	end

MtChimney_EventScript_AquaPoochyena::
	msgbox MtChimney_Text_Bushaa, MSGBOX_SIGN
	end

MtChimney_EventScript_MeteoriteMachine::
	lockall
	goto_if_unset FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, MtChimney_EventScript_MachineOn
	goto_if_set FLAG_RECEIVED_METEORITE, MtChimney_EventScript_MachineOff
	msgbox MtChimney_Text_RemoveTheMeteorite, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_LeaveMeteoriteAlone
	msgbox MtChimney_Text_PlayerRemovedMeteorite, MSGBOX_DEFAULT
	giveitem ITEM_METEORITE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_METEORITE
	releaseall
	end

MtChimney_EventScript_LeaveMeteoriteAlone::
	msgbox MtChimney_Text_PlayerLeftMeteorite, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOff::
	msgbox MtChimney_Text_MachineMakesNoResponse, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOn::
	msgbox MtChimney_Text_MetoriteFittedOnMachine, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_RouteSign::
	msgbox MtChimney_Text_RouteSign, MSGBOX_SIGN
	end

MtChimney_EventScript_Shelby::
	trainerbattle_single TRAINER_SHELBY_1, MtChimney_Text_ShelbyIntro, MtChimney_Text_ShelbyDefeat, MtChimney_EventScript_DefeatedShelby
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RematchShelby
	msgbox MtChimney_Text_ShelbyPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_DefeatedShelby::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_ShelbyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SHELBY_1
	release
	end

MtChimney_EventScript_RematchShelby::
	trainerbattle_rematch TRAINER_SHELBY_1, MtChimney_Text_ShelbyRematchIntro, MtChimney_Text_ShelbyRematchDefeat
	msgbox MtChimney_Text_ShelbyPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Melissa::
	trainerbattle_single TRAINER_MELISSA, MtChimney_Text_MelissaIntro, MtChimney_Text_MelissaDefeat
	msgbox MtChimney_Text_MelissaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sheila::
	trainerbattle_single TRAINER_SHEILA, MtChimney_Text_SheilaIntro, MtChimney_Text_SheilaDefeat
	msgbox MtChimney_Text_SheilaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Shirley::
	trainerbattle_single TRAINER_SHIRLEY, MtChimney_Text_ShirleyIntro, MtChimney_Text_ShirleyDefeat
	msgbox MtChimney_Text_ShirleyPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_Grunt1Intro, MtChimney_Text_Grunt1Defeat
	msgbox MtChimney_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sawyer::
	trainerbattle_single TRAINER_SAWYER_1, MtChimney_Text_SawyerIntro, MtChimney_Text_SawyerDefeat, MtChimney_EventScript_SawyerDefeated
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_SawyerRematch
	msgbox MtChimney_Text_SawyerPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_SawyerDefeated::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_SawyerRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SAWYER_1
	release
	end

MtChimney_EventScript_SawyerRematch::
	trainerbattle_rematch TRAINER_SAWYER_1, MtChimney_Text_SawyerRematchIntro, MtChimney_Text_SawyerRematchDefeat
	msgbox MtChimney_Text_SawyerPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_Text_MeteoriteWillActivateVolcano:
    .string "蕴含在陨石的能量……\p用这机器放大这能量的话，\n烟囱山的火山活动\l马上会加剧的……\p这能量会直达火山口深处，\n然后……\l呵呵呵……$"

MtChimney_Text_MaxieIntro:
    .string "赤焰松：嗯？\n你是谁？\p…… …… ……\n…… …… ……\p我听水梧桐那家伙在抱怨说\n有个小孩把海洋队的计划\l全盘搅乱了，\p他说的就是你吧。\p哼！莫非你还想\n碍我们熔岩队的事？\p听着，\n很久以前，世界上的生命\l都是依靠大地生存与成长的，\p因此大地才会如此重要！\n它是一切生命的摇篮！\p也正因此我们熔岩队才会\n奉献出自己的一切来扩展大地。\p这是为了人类和宝可梦\n长远发展！\p为此，我们需要在这座山里\n沉睡的能量……\p哦！没必要告诉你\n这么多。\p不过，没关系！\n我会告诉你干涉我们的崇高的目标\l会有什么后果！$"

MtChimney_Text_MaxieDefeat:
    .string "什么？！\p我，赤焰松，居然会被打败？！$"

MtChimney_Text_MaxieYouHaventSeenLastOfMagma:
    .string "赤焰松：哼，\n这次就先算了。\p但别以为我们熔岩队\n不会再出现了。\p哼哼哼……\p就算没有陨石，只要\n那个宝玉还在我们手上……哼哼哼……$"

MtChimney_Text_TabithaIntro:
    .string "呵呵呵！\p你还是追来了！\p可惜太迟了！\n我已经把流星瀑布的\l陨石交给老大了！$"

MtChimney_Text_TabithaDefeat:
    .string "呵呵呵……\p我输了不要紧，只要我们的头儿\n能唤醒那家伙……$"

MtChimney_Text_TabithaPostBattle:
    .string "老大，快！\n把陨石的力量交给它！\p呵呵呵……$"

MtChimney_Text_Grunt2Intro:
    .string "我们熔岩队\n是为了大家而努力着。\p比如说，如果那家伙的力量能制造更多\n土地，人们生活的空间会越来越多。\p大家都会很高兴的！$"

MtChimney_Text_Grunt2Defeat:
    .string "哎？\n我输了？$"

MtChimney_Text_Grunt2PostBattle:
    .string "我们的老大说过，\n“这会让所有人都幸福。”\p可是为什么每个人都在\n阻碍我们？$"

MtChimney_Text_Grunt1Intro:
    .string "如果有更多的土地，我就能\n有一所自己的大房子了！\p我要把它建在凝固的岩浆上！$"

MtChimney_Text_Grunt1Defeat:
    .string "我大房子的梦想啊……$"

MtChimney_Text_Grunt1PostBattle:
    .string "像你这样的孩子，应该\n去海里玩水才对！$"

MtChimney_Text_TeamAquaAlwaysMessingWithPlans:
    .string "可恶的海洋队……\n总是妨碍我们的计划！$"

MtChimney_Text_MeteoritesPackAmazingPower:
    .string "陨石蕴含着巨大的力量！$"

MtChimney_Text_YouBetterNotMessWithUs:
    .string "你最好别妨碍我们！\p我们要唤醒那家伙，\n这是为了所有人的利益！$"

MtChimney_Text_AquasNameSimilar:
    .string "我们是熔岩队！\p他们叫海洋队！\p居然用跟我们相似的名字，\n真让人生气！$"

MtChimney_Text_DouseThemInFire:
    .string "好！\n烧了它们！$"

MtChimney_Text_KeepMakingMoreLand:
    .string "我们要继续制造更多的土地！$"

MtChimney_Text_Bufoh:
    .string "呼喔！$"

MtChimney_Text_ArchieGoStopTeamMagma:
    .string "水梧桐：唔唔，{PLAYER}！\n我该猜到你会出现的！\p自己看看熔岩队\n的所作所为吧！\p他们居然想把偷来的陨石\n的力量引入火山里面！\p这种举动会\n引起火山爆发的！$"

MtChimney_Text_ArchieIHaveMyHandsFull:
    .string "水梧桐：唔唔……\p我想要阻止赤焰松，\n但做不到！\p同时对付三个对手\n已经让我忙不过来了！$"

MtChimney_Text_ArchieThankYou:
    .string "水梧桐：{PLAYER}！\n谢谢！\p多亏你帮忙，我们才能挫败\n熔岩队的破坏计划！\p可是……你……\n到底站在哪边？\p啊，这不重要。\p我们会保持警惕\n继续追击熔岩队的。\p{PLAYER}，后会有期！$"

MtChimney_Text_MagmaOutnumbersUs:
    .string "可恶……熔岩队比我们人多！\n我们阻止不了他们！$"

MtChimney_Text_LessHabitatForWaterPokemon:
    .string "如果任他们扩展陆地，水属性\n宝可梦们的生存空间就会减少了！$"

MtChimney_Text_MagmasNameSimilar:
    .string "我们是海洋队！\p他们是熔岩队！\p这种容易混淆的名字\n真气死我了！$"

MtChimney_Text_Bushaa:
    .string "扑沙！$"

MtChimney_Text_LavaCookiesJust200:
    .string "釜炎仙贝是\n烟囱山的特产。\p吃吃看吧，一个只卖¥200。$"

MtChimney_Text_ThankYouDear:
    .string "谢谢惠顾，孩子！$"

MtChimney_Text_YouveNotGotTheMoney:
    .string "天啊，没钱的话\n可是买不了东西的。$"

MtChimney_Text_OhFineThen:
    .string "啊，那就算了。$"

MtChimney_Text_MetoriteFittedOnMachine:
    .string "一个奇异的机器上面\n安装了一块陨石……\p这台机器似乎能储存\n陨石的能量。$"

MtChimney_Text_RemoveTheMeteorite:
    .string "一个奇异的机器上面\n安装了一块陨石……\p你想拿走陨石吗？$"

MtChimney_Text_PlayerRemovedMeteorite:
    .string "{PLAYER}把陨石从\n奇异的机器上拿了下来。$"

MtChimney_Text_PlayerLeftMeteorite:
    .string "{PLAYER}把陨石\n留在原地。$"

MtChimney_Text_MachineMakesNoResponse:
    .string "是一台奇异的机器……\n什么反应也没有。$"

MtChimney_Text_RouteSign:
    .string "{DOWN_ARROW}凹凸山道\n前方为釜炎镇$"

MtChimney_Text_ShelbyIntro:
    .string "泡过温泉后，\n筋骨都舒展开了。\l现在我精神焕发！$"

MtChimney_Text_ShelbyDefeat:
    .string "哦，我的天啊，\n你可不是一般人！$"

MtChimney_Text_ShelbyPostBattle:
    .string "好吧，好吧，我输了，\n现在不能自称高手了。$"

MtChimney_Text_ShelbyRegister:
    .string "谢谢你，孩子，我很高兴，这就像\n我在和自己的孙子战斗一样。\p以后一定要再回来\n和我战斗啊。$"

MtChimney_Text_ShelbyRematchIntro:
    .string "如果你能够把自己的心\n与你的宝可梦融合在一起，\l一定会有非凡的成就。$"

MtChimney_Text_ShelbyRematchDefeat:
    .string "哦，我的天啊，\n你可不是一般人！$"

MtChimney_Text_ShelbyPostRematch:
    .string "也许你的心已经与宝可梦\n合为一体了。$"

MtChimney_Text_MelissaIntro:
    .string "我的热血在沸腾！\n不能忍受了！我要战斗！$"

MtChimney_Text_MelissaDefeat:
    .string "喔喔，真是场激烈的比赛！$"

MtChimney_Text_MelissaPostBattle:
    .string "烟囱山的炽热\n点燃了我的心！$"

MtChimney_Text_SheilaIntro:
    .string "我终于到了烟囱山了。\n我想让自己的宝可梦战斗！$"

MtChimney_Text_SheilaDefeat:
    .string "你战斗的方式……\n好像烟囱山的喷发一般！$"

MtChimney_Text_SheilaPostBattle:
    .string "正如我说的，我终于到达了\n烟囱山，如果只是看看风景\l就真是太可惜了……\p我想来几场战斗，再买些\n煎饼当作纪念品。$"

MtChimney_Text_ShirleyIntro:
    .string "在温泉泡过后，\n感觉好极了！\l我一定能赢！$"

MtChimney_Text_ShirleyDefeat:
    .string "阿嚏！\n出浴后有点发冷呢。$"

MtChimney_Text_ShirleyPostBattle:
    .string "我要去温泉里再泡一下。\n一起来吗？\p开玩笑啦！$"

MtChimney_Text_SawyerIntro:
    .string "真是座好山啊！有许多\n热情的人呢！$"

MtChimney_Text_SawyerDefeat:
    .string "哦，你的激情也很火热啊！$"

MtChimney_Text_SawyerPostBattle:
    .string "我想我应该和这里的人一起\n到釜炎镇温泉深处去！$"

MtChimney_Text_SawyerRegister:
    .string "我喜欢你这样热情的训练家，\n让我把你登记进宝可导航吧。$"

MtChimney_Text_SawyerRematchIntro:
    .string "我喜欢跟这里热情的人们\n呆在一起。我不会输的！$"

MtChimney_Text_SawyerRematchDefeat:
    .string "喔喔，你还是与以前\n一样的火热！$"

MtChimney_Text_SawyerPostRematch:
    .string "这里真是热，\n我确实穿的太多了。$"

