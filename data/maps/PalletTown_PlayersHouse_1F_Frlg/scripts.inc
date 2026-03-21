PalletTown_PlayersHouse_1F_Frlg_MapScripts::
	.byte 0

PalletTown_PlayersHouse_1F_EventScript_Mom::
	lock
	faceplayer
	goto_if_set FLAG_BEAT_RIVAL_IN_OAKS_LAB, PalletTown_PlayersHouse_1F_EventScript_MomHeal
	checkplayergender
	call_if_eq VAR_RESULT, MALE, PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouMale
	call_if_eq VAR_RESULT, FEMALE, PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouFemale
	closemessage
	applymovement LOCALID_PLAYERS_HOUSE_1F_MOM, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouMale::
	msgbox PalletTown_PlayersHouse_1F_Text_AllBoysLeaveOakLookingForYou
	return

PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouFemale::
	msgbox PalletTown_PlayersHouse_1F_Text_AllGirlsLeaveOakLookingForYou
	return

PalletTown_PlayersHouse_1F_EventScript_MomHeal::
	msgbox PalletTown_PlayersHouse_1F_Text_YouShouldTakeQuickRest
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox PalletTown_PlayersHouse_1F_Text_LookingGreatTakeCare
	release
	end

@ Displays special text if interacted with from side or back (which are normally inaccessible)
PalletTown_PlayersHouse_1F_EventScript_TV::
	lockall
	goto_if_eq VAR_FACING, DIR_NORTH, PalletTown_PlayersHouse_1F_EventScript_TVScreen
	msgbox PalletTown_PlayersHouse_1F_Text_OopsWrongSide
	releaseall
	end

PalletTown_PlayersHouse_1F_EventScript_TVScreen::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, PalletTown_PlayersHouse_1F_EventScript_TVScreenMale
	call_if_eq VAR_RESULT, FEMALE, PalletTown_PlayersHouse_1F_EventScript_TVScreenFemale
	releaseall
	end

PalletTown_PlayersHouse_1F_EventScript_TVScreenMale::
	msgbox PalletTown_PlayersHouse_1F_Text_MovieOnTVFourBoysOnRailroad
	return

PalletTown_PlayersHouse_1F_EventScript_TVScreenFemale::
	msgbox PalletTown_PlayersHouse_1F_Text_MovieOnTVGirlOnBrickRoad
	return

PalletTown_PlayersHouse_1F_Text_AllBoysLeaveOakLookingForYou::
    .string "妈妈：……好吧。\n"
    .string "电视上说过。\l"
    .string "每一个男孩子都有离开家的那一天。\p"
    .string "对了，隔壁的大木博士\n"
    .string "正在找你呢。$"

PalletTown_PlayersHouse_1F_Text_AllGirlsLeaveOakLookingForYou::
    .string "妈妈 ……好吧。\n"
    .string "电视上说过，\l"
    .string "每一个女孩子都梦想着去旅行。\p"
    .string "对了，隔壁的大木博士\n"
    .string "正在找你呢。$"

PalletTown_PlayersHouse_1F_Text_YouShouldTakeQuickRest::
    .string "妈妈 {PLAYER}！\n"
    .string "你应该稍微休息一下。$"

PalletTown_PlayersHouse_1F_Text_LookingGreatTakeCare::
    .string "妈妈：嗯，很好！你和你的\n"
    .string "宝可梦看起来精力十足。\l"
    .string "路上小心！$"

PalletTown_PlayersHouse_1F_Text_MovieOnTVFourBoysOnRailroad::
    .string "电视上播放着一部电影。\n"
    .string "四个男孩沿着铁轨\l"
    .string "步行着开始了旅行。\p"
    .string "……我也该走了。$"

PalletTown_PlayersHouse_1F_Text_MovieOnTVGirlOnBrickRoad::
    .string "电视上播放着一部电影。\n"
    .string "一个扎着马尾的女孩\l"
    .string "沿着砖块砌成的路开始了旅行。\p"
    .string "……我也该走了。$"

PalletTown_PlayersHouse_1F_Text_OopsWrongSide::
    .string "哎哟，方向错了……$"
