.set LOCALID_WALLYS_DAD, 1

PetalburgCity_WallysHouse_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_WallysHouse_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgCity_WallysHouse_OnWarp
	.byte 0

PetalburgCity_WallysHouse_OnWarp:
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther
	.2byte 0

PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	turnobject LOCALID_WALLYS_DAD, DIR_WEST
	end

PetalburgCity_WallysHouse_OnFrame:
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_GiveHMSurf
	.2byte 0

PetalburgCity_WallysHouse_EventScript_GiveHMSurf::
	lockall
	msgbox PetalburgCity_WallysHouse_Text_PleaseExcuseUs, MSGBOX_DEFAULT
	giveitem ITEM_HM_SURF
	setflag FLAG_RECEIVED_HM_SURF
	msgbox PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces, MSGBOX_DEFAULT
	setvar VAR_PETALBURG_CITY_STATE, 5
	releaseall
	end

PetalburgCity_WallysHouse_EventScript_WallysDad::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_ReceievedHMSurf
	goto_if_set FLAG_THANKED_FOR_PLAYING_WITH_WALLY, PetalburgCity_WallysHouse_EventScript_PlayedWithWally
	msgbox PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally, MSGBOX_DEFAULT
	setflag FLAG_THANKED_FOR_PLAYING_WITH_WALLY
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceievedHMSurf::
	msgbox PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad::
	msgbox PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_PlayedWithWally::
	msgbox PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_WallysMom::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_ReceivedHMSurf
	msgbox PetalburgCity_WallysHouse_Text_WallyWasReallyHappy, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceivedHMSurf::
	msgbox PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally:
    .string "你是……\n啊，你一定是{PLAYER}{KUN}，对吗？\p谢谢你刚才能\n和满充一起玩。\p他从小\n体弱多病，\p我们打算送他到\n绿茵镇的亲戚家去，\p那里的空气\n比这儿洁净。\p什么？满充在哪儿？\n我们家满充已经出发了。\p不知道现在\n该到哪儿了呢？$"

PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing:
    .string "不知道我家满充在做什么？$"

PetalburgCity_WallysHouse_Text_PleaseExcuseUs:
    .string "{PLAYER}{KUN}！原谅我们\n这样拉你过来，\p但是，自从我家满充去了\n绿茵镇之后，他的身体好多了。\p我们都欠你的情！\p满充离开镇子前，\n是你陪他捕捉了一只宝可梦对吗？\p我想那让满充\n非常开心。\p实际上，不只是满充，\n作为父亲的我也很开心，\p很开心他能交上\n你这样的好朋友。\p这点礼物虽然不算什么\n但还是请你收下。$"

PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces:
    .string "如果你的宝可梦会冲浪，\n你就可以去很多地方了。$"

PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon:
    .string "满充很快就会回家了，\n真想快点见到他。$"

PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity:
    .string "哦？你在彩悠市\n遇到了满充？\p哎，{PLAYER}{KUN}，别闹了。\p他可能健康多了，\n但它不可能一个人\l到那么远的地方去。$"

PetalburgCity_WallysHouse_Text_WallyWasReallyHappy:
    .string "满充非常兴奋地告诉我们\n他捕捉到了一只宝可梦。\p已经有很多年没看到过\n他那快乐的笑容了。$"

PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling:
    .string "有件事你一定要\n对我丈夫保密……\p我们的满充没跟任何人说\n就离开了绿茵镇。\p你知道，尽管满充身体很弱，\n但他的意志很坚强。\p我知道他总有一天\n会平安无事地回家的！$"

