SaffronCity_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_OnTransition
	.byte 0

SaffronCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SAFFRON_CITY
	call_if_unset FLAG_RESCUED_MR_FUJI, SaffronCity_EventScript_MoveDoorGuardGrunt
	end

SaffronCity_EventScript_MoveDoorGuardGrunt::
	setobjectxyperm LOCALID_SAFFRON_DOOR_GUARD_GRUNT, 33, 31
	return

SaffronCity_EventScript_RocketGrunt1::
	msgbox SaffronCity_Text_WhatDoYouWantGetLost, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt2::
	msgbox SaffronCity_Text_BossTakeTownForTeamRocket, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt3::
	msgbox SaffronCity_Text_DontGetDefiantOrIllHurtYou, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt4::
	msgbox SaffronCity_Text_SaffronBelongsToTeamRocket, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt5::
	msgbox SaffronCity_Text_CriminalLifeMakesMeFeelAlive, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt6::
	msgbox SaffronCity_Text_WatchWhereYoureWalking, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt7::
	msgbox SaffronCity_Text_WeCanExploitMonsAroundWorld, MSGBOX_NPC
	end

SaffronCity_EventScript_DoorGuardGrunt::
	lock
	goto_if_set FLAG_RESCUED_MR_FUJI, SaffronCity_EventScript_DoorGuardAsleep
	applymovement LOCALID_SAFFRON_DOOR_GUARD_GRUNT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SaffronCity_Text_ImASecurityGuard
	release
	end

SaffronCity_EventScript_DoorGuardAsleep::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox SaffronCity_Text_HesTakingASnooze
	release
	end

SaffronCity_EventScript_WorkerM::
	msgbox SaffronCity_Text_YouBeatTeamRocket, MSGBOX_NPC
	end

SaffronCity_EventScript_Youngster::
	msgbox SaffronCity_Text_SafeToGoOutAgain, MSGBOX_NPC
	end

SaffronCity_EventScript_Lass::
	msgbox SaffronCity_Text_PeopleComingBackToSaffron, MSGBOX_NPC
	end

SaffronCity_EventScript_Boy::
	msgbox SaffronCity_Text_FlewHereOnPidgeot, MSGBOX_NPC
	end

SaffronCity_EventScript_Pidgeot::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIDGEOT, CRY_MODE_NORMAL
	msgbox SaffronCity_Text_Pidgeot
	waitmoncry
	release
	end

SaffronCity_EventScript_Man::
	msgbox SaffronCity_Text_SawRocketBossEscaping, MSGBOX_NPC
	end

SaffronCity_EventScript_CitySign::
	msgbox SaffronCity_Text_CitySign, MSGBOX_SIGN
	end

SaffronCity_EventScript_DojoSign::
	msgbox SaffronCity_Text_FightingDojo, MSGBOX_SIGN
	end

SaffronCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_SABRINA, 0
	msgbox SaffronCity_Text_GymSign
	releaseall
	end

SaffronCity_EventScript_TrainerTips1::
	msgbox SaffronCity_Text_FullHealCuresStatus, MSGBOX_SIGN
	end

SaffronCity_EventScript_TrainerTips2::
	msgbox SaffronCity_Text_GreatBallImprovedCatchRate, MSGBOX_SIGN
	end

SaffronCity_EventScript_SilphCoSign::
	msgbox SaffronCity_Text_SilphCoSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_MrPsychicsHouseSign::
	msgbox SaffronCity_Text_MrPsychicsHouse, MSGBOX_SIGN
	end

SaffronCity_EventScript_SilphProductSign::
	msgbox SaffronCity_Text_SilphsLatestProduct, MSGBOX_SIGN
	end

SaffronCity_EventScript_TrainerFanClubSign::
	msgbox SaffronCity_Text_TrainerFanClubSign, MSGBOX_SIGN
	end

SaffronCity_Text_WhatDoYouWantGetLost::
    .string "你想干什么？\n"
    .string "滚开！$"

SaffronCity_Text_BossTakeTownForTeamRocket::
    .string "老大说他会把这座城镇\n"
    .string "命名为火箭队！$"

SaffronCity_Text_DontGetDefiantOrIllHurtYou::
    .string "不要惹我生气！\n"
    .string "否则我会狠狠地报复你的！$"

SaffronCity_Text_SaffronBelongsToTeamRocket::
    .string "金黄永远属于火箭队！$"

SaffronCity_Text_CriminalLifeMakesMeFeelAlive::
    .string "只有犯罪才会让我觉得\n"
    .string "是如此的有意义！$"

SaffronCity_Text_WatchWhereYoureWalking::
    .string "噢！\n"
    .string "给我好好走路！$"

SaffronCity_Text_WeCanExploitMonsAroundWorld::
    .string "在我们控制了西尔佛之后，\n"
    .string "我们将会拥有全世界的宝可梦！\p"
    .string "富甲天下，哇哈哈哈！$"

SaffronCity_Text_YouBeatTeamRocket::
    .string "你一人就打败了火箭队？\n"
    .string "真难以想象！$"

SaffronCity_Text_SafeToGoOutAgain::
    .string "耶！火箭队被赶跑了！\n"
    .string "外面都安全喽！$"

SaffronCity_Text_PeopleComingBackToSaffron::
    .string "当火箭队来的时候，\n"
    .string "人们成群结队地逃离这里。\p"
    .string "他们现在要涌回\n"
    .string "金黄了。$"

SaffronCity_Text_FlewHereOnPidgeot::
    .string "当我得知西尔佛的事件后，\n"
    .string "就马上乘着大比鸟飞过来了。\p"
    .string "现在一切都结束了吗？\n"
    .string "我错过了写报导的最好时机……$"

SaffronCity_Text_Pidgeot::
    .string "大比鸟 比比比！$"

SaffronCity_Text_SawRocketBossEscaping::
    .string "我看见火箭队的老大\n"
    .string "从西尔佛大楼逃了出来。$"

SaffronCity_Text_ImASecurityGuard::
    .string "我是一名保安。\p"
    .string "我决不允许可疑的孩子进入！$"

SaffronCity_Text_HesTakingASnooze::
    .string "……\n"
    .string "鼾声传了出来……\p"
    .string "哈！他正在打盹儿！$"

SaffronCity_Text_CitySign::
    .string "金黄市\n"
    .string "遍布商机的闪耀之地$"

SaffronCity_Text_FightingDojo::
    .string "格斗道场$"

SaffronCity_Text_GymSign::
    .string "金黄市宝可梦道馆\n"
    .string "馆主：娜姿\l"
    .string "超能力属性宝可梦的大师！$"

SaffronCity_Text_FullHealCuresStatus::
    .string "训练家贴士\p"
    .string "万灵药能治愈\n"
    .string "像烧伤，麻痹，中毒，\l"
    .string "冰冻和睡眠等异常状态。\p"
    .string "虽然有点贵，但是\n"
    .string "比一个一个买其他商品更方便。$"

SaffronCity_Text_GreatBallImprovedCatchRate::
    .string "训练家贴士\p"
    .string "新的超级球提高了\n"
    .string "收服率。\p"
    .string "试试用它去抓那些\n"
    .string "很难收服的宝可梦。$"

SaffronCity_Text_SilphCoSign::
    .string "西尔佛公司办公大楼$"

SaffronCity_Text_MrPsychicsHouse::
    .string "超能先生的家$"

SaffronCity_Text_SilphsLatestProduct::
    .string "西尔佛的最新产品！\n"
    .string "即将开始销售……$"

SaffronCity_Text_TrainerFanClubSign::
    .string "宝可梦训练家迷俱乐部\p"
    .string "许多训练家在这里\n"
    .string "留下了他们的名字。$"

SaffronCity_Text_HowCanClubNotRecognizeLance::
    .string "这个俱乐部里面……\n"
    .string "没人有异议！\p"
    .string "谁不知道\n"
    .string "渡的实力？\p"
    .string "他就是正义的化身！\n"
    .string "而且冷静又富有激情！\l"
    .string "渡先生是最棒的！$"

