SaffronCity_PokemonTrainerFanClub_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SaffronCity_PokemonTrainerFanClub_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_PokemonTrainerFanClub_OnTransition
	.byte 0

SaffronCity_PokemonTrainerFanClub_OnFrame::
	map_script_2 VAR_MAP_SCENE_SAFFRON_CITY_POKEMON_TRAINER_FAN_CLUB, 1, SaffronCity_PokemonTrainerFanClub_EventScript_MeetFirstFans
	.2byte 0

SaffronCity_PokemonTrainerFanClub_EventScript_MeetFirstFans::
	lockall
	textcolor NPC_TEXT_COLOR_FEMALE
	applymovement LOCALID_TRAINER_FAN_CLUB_BATTLE_GIRL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_TRAINER_FAN_CLUB_BATTLE_GIRL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_TRAINER_FAN_CLUB_BATTLE_GIRL, Common_Movement_Delay48
	waitmovement 0
	msgbox SaffronCity_PokemonTrainerFanClub_Text_HuhYou
	closemessage
	applymovement LOCALID_TRAINER_FAN_CLUB_BATTLE_GIRL, SaffronCity_PokemonTrainerFanClub_Movement_FanApproachPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SaffronCity_PokemonTrainerFanClub_Text_YourePlayerWereYourFansNow
	setvar VAR_MAP_SCENE_SAFFRON_CITY_POKEMON_TRAINER_FAN_CLUB, 2
	releaseall
	end

SaffronCity_PokemonTrainerFanClub_Movement_FanApproachPlayer::
	delay_16
	delay_8
	walk_down
	delay_16
	walk_down
	delay_8
	walk_left
	step_end

SaffronCity_PokemonTrainerFanClub_OnTransition::
	goto_if_eq VAR_MAP_SCENE_SAFFRON_CITY_POKEMON_TRAINER_FAN_CLUB, 1, SaffronCity_PokemonTrainerFanClub_EventScript_SetMemberPosForFirstMeeting
	goto_if_eq VAR_MAP_SCENE_SAFFRON_CITY_POKEMON_TRAINER_FAN_CLUB, 2, SaffronCity_PokemonTrainerFanClub_EventScript_UpdateFanMemberPositions
	end

SaffronCity_PokemonTrainerFanClub_EventScript_UpdateFanMemberPositions::
	special Script_TryLoseFansFromPlayTime
	setvar VAR_0x8004, FANCLUB_MEMBER1
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	call_if_eq VAR_RESULT, FALSE, SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember1ToFarTable
	setvar VAR_0x8004, FANCLUB_MEMBER2
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	call_if_eq VAR_RESULT, FALSE, SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember2ToFarTable
	setvar VAR_0x8004, FANCLUB_MEMBER3
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	call_if_eq VAR_RESULT, FALSE, SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember3ToFarTable
	setvar VAR_0x8004, FANCLUB_MEMBER4
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	call_if_eq VAR_RESULT, FALSE, SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember4ToFarTable
	setvar VAR_0x8004, FANCLUB_MEMBER5
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	call_if_eq VAR_RESULT, FALSE, SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember5ToFarTable
	setvar VAR_0x8004, FANCLUB_MEMBER6
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	call_if_eq VAR_RESULT, FALSE, SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember6ToFarTable
	setvar VAR_0x8004, FANCLUB_MEMBER7
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	call_if_eq VAR_RESULT, FALSE, SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember7ToFarTable
	setvar VAR_0x8004, FANCLUB_MEMBER8
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	call_if_eq VAR_RESULT, FALSE, SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember8ToFarTable
	end

SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember1ToFarTable::
	setobjectxyperm LOCALID_TRAINER_FAN_CLUB_BATTLE_GIRL, 5, 2
	setobjectmovementtype LOCALID_TRAINER_FAN_CLUB_BATTLE_GIRL, MOVEMENT_TYPE_FACE_UP
	return

SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember2ToFarTable::
	setobjectxyperm LOCALID_TRAINER_FAN_CLUB_YOUNGSTER, 7, 4
	setobjectmovementtype LOCALID_TRAINER_FAN_CLUB_YOUNGSTER, MOVEMENT_TYPE_FACE_LEFT
	return

SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember3ToFarTable::
	setobjectxyperm LOCALID_TRAINER_FAN_CLUB_GENTLEMAN, 2, 2
	setobjectmovementtype LOCALID_TRAINER_FAN_CLUB_GENTLEMAN, MOVEMENT_TYPE_FACE_UP
	return

SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember4ToFarTable::
	setobjectxyperm LOCALID_TRAINER_FAN_CLUB_LITTLE_GIRL, 3, 4
	setobjectmovementtype LOCALID_TRAINER_FAN_CLUB_LITTLE_GIRL, MOVEMENT_TYPE_FACE_RIGHT
	return

SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember5ToFarTable::
	setobjectxyperm LOCALID_TRAINER_FAN_CLUB_ROCKER, 4, 6
	setobjectmovementtype LOCALID_TRAINER_FAN_CLUB_ROCKER, MOVEMENT_TYPE_FACE_UP
	return

SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember6ToFarTable::
	setobjectxyperm LOCALID_TRAINER_FAN_CLUB_WOMAN, 10, 3
	setobjectmovementtype LOCALID_TRAINER_FAN_CLUB_WOMAN, MOVEMENT_TYPE_FACE_UP
	return

SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember7ToFarTable::
	setobjectxyperm LOCALID_TRAINER_FAN_CLUB_BEAUTY, 7, 5
	setobjectmovementtype LOCALID_TRAINER_FAN_CLUB_BEAUTY, MOVEMENT_TYPE_FACE_LEFT
	return

SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember8ToFarTable::
	setobjectxyperm LOCALID_TRAINER_FAN_CLUB_BLACK_BELT, 9, 6
	setobjectmovementtype LOCALID_TRAINER_FAN_CLUB_BLACK_BELT, MOVEMENT_TYPE_FACE_LEFT
	return

SaffronCity_PokemonTrainerFanClub_EventScript_SetMemberPosForFirstMeeting::
	call SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember4ToFarTable
	call SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember5ToFarTable
	call SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember6ToFarTable
	call SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember7ToFarTable
	call SaffronCity_PokemonTrainerFanClub_EventScript_MoveMember8ToFarTable
	end

SaffronCity_PokemonTrainerFanClub_EventScript_BattleGirl::
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER1
	special Script_BufferFanClubTrainerName
	goto_if_eq VAR_MAP_SCENE_SAFFRON_CITY_POKEMON_TRAINER_FAN_CLUB, 0, SaffronCity_PokemonTrainerFanClub_EventScript_BattleGirlPlayerNotChampion
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	goto_if_eq VAR_RESULT, TRUE, SaffronCity_PokemonTrainerFanClub_EventScript_BattleGirlPlayersFan
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1), SaffronCity_PokemonTrainerFanClub_EventScript_BattleGirlOnlyNonFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_WasYourFanNotAnymore
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_BattleGirlPlayersFan::
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, 1, SaffronCity_PokemonTrainerFanClub_EventScript_BattleGirlOnlyFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_AlwaysCheerForYou
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_BattleGirlOnlyFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_IllAlwaysBelieveInYou
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_BattleGirlOnlyNonFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_EveryonesYourFanButICantBe
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_BattleGirlPlayerNotChampion::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_TrainersCoolWhenBattling
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_LittleGirl::
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER4
	special Script_BufferFanClubTrainerName
	goto_if_eq VAR_MAP_SCENE_SAFFRON_CITY_POKEMON_TRAINER_FAN_CLUB, 0, SaffronCity_PokemonTrainerFanClub_EventScript_LittleGirlPlayerNotChampion
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	goto_if_eq VAR_RESULT, TRUE, SaffronCity_PokemonTrainerFanClub_EventScript_LittleGirlPlayersFan
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1), SaffronCity_PokemonTrainerFanClub_EventScript_LittleGirlOnlyNonFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_WantToBeLikeSabrina
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_LittleGirlPlayersFan::
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, 1, SaffronCity_PokemonTrainerFanClub_EventScript_LittleGirlOnlyFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_WantToBeLikeYouOneDay
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_LittleGirlOnlyFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_EveryoneButMeStoppedBeingYourFan
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_LittleGirlOnlyNonFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_WontStopBeingSabrinasFan
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_LittleGirlPlayerNotChampion::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_CanIBecomeCoolTrainerOneDay
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_Youngster::
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER2
	special Script_BufferFanClubTrainerName
	goto_if_eq VAR_MAP_SCENE_SAFFRON_CITY_POKEMON_TRAINER_FAN_CLUB, 0, SaffronCity_PokemonTrainerFanClub_EventScript_YoungsterPlayerNotChampion
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	goto_if_eq VAR_RESULT, TRUE, SaffronCity_PokemonTrainerFanClub_EventScript_YoungsterPlayersFan
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1), SaffronCity_PokemonTrainerFanClub_EventScript_YoungsterOnlyNonFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_BrocksMyHero
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_YoungsterPlayersFan::
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, 1, SaffronCity_PokemonTrainerFanClub_EventScript_YoungsterOnlyFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_CanYouAutographShorts
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_YoungsterOnlyFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_CountingOnYou
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_YoungsterOnlyNonFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_BrocksFanToBitterEnd
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_YoungsterPlayerNotChampion::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_BrocksLastWordOnCool
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_Gentleman::
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER3
	special Script_BufferFanClubTrainerName
	goto_if_eq VAR_MAP_SCENE_SAFFRON_CITY_POKEMON_TRAINER_FAN_CLUB, 0, SaffronCity_PokemonTrainerFanClub_EventScript_GentlemanPlayerNotChampion
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	goto_if_eq VAR_RESULT, TRUE, SaffronCity_PokemonTrainerFanClub_EventScript_GentlemanPlayersFan
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1), SaffronCity_PokemonTrainerFanClub_EventScript_GentlemanOnlyNonFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_HmmAndYouAre
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_GentlemanPlayersFan::
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, 1, SaffronCity_PokemonTrainerFanClub_EventScript_GentlemanOnlyFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_HadPleasureOfWatchingYouBattle
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_GentlemanOnlyFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_NeverSeenTrainerOfYourMagnificence
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_GentlemanOnlyNonFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_YouveStillAWaysToGo
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_GentlemanPlayerNotChampion::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_YoullBeTalkedAboutIfYouKeepWinning
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_Woman::
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER6
	special Script_BufferFanClubTrainerName
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	goto_if_eq VAR_RESULT, TRUE, SaffronCity_PokemonTrainerFanClub_EventScript_WomanPlayersFan
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1), SaffronCity_PokemonTrainerFanClub_EventScript_WomanOnlyNonFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_TrainerHasBeenOnFire
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_WomanPlayersFan::
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, 1, SaffronCity_PokemonTrainerFanClub_EventScript_WomanOnlyFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_AdoreWayYouBattle
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_WomanOnlyFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_ImYourNumberOneFan
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_WomanOnlyNonFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_EveryoneTalksAboutYou
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_Rocker::
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER5
	special Script_BufferFanClubTrainerName
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	goto_if_eq VAR_RESULT, TRUE, SaffronCity_PokemonTrainerFanClub_EventScript_RockerPlayersFan
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1), SaffronCity_PokemonTrainerFanClub_EventScript_RockerOnlyNonFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_LoveWayTrainerTalks
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_RockerPlayersFan::
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, 1, SaffronCity_PokemonTrainerFanClub_EventScript_RockerOnlyFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_TheWayYouBattleIsCool
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_RockerOnlyFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_ImOnlyOneLeftOfYourFans
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_RockerOnlyNonFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_ImLoneTrainerFan
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_Beauty::
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER7
	special Script_BufferFanClubTrainerName
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	goto_if_eq VAR_RESULT, TRUE, SaffronCity_PokemonTrainerFanClub_EventScript_BeautyPlayersFan
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1), SaffronCity_PokemonTrainerFanClub_EventScript_BeautyOnlyNonFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_WhyCantOthersSeeMastersDignity
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_BeautyPlayersFan::
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, 1, SaffronCity_PokemonTrainerFanClub_EventScript_BeautyOnlyFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_YouReallyAreAmazing
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_BeautyOnlyFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_ImYourOnlyFan
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_BeautyOnlyNonFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_BelieveInMasterWithAllMyHeart
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_BlackBelt::
	lock
	faceplayer
	setvar VAR_0x8004, FANCLUB_MEMBER8
	special Script_BufferFanClubTrainerName
	specialvar VAR_RESULT, Script_IsFanClubMemberFanOfPlayer
	goto_if_eq VAR_RESULT, TRUE, SaffronCity_PokemonTrainerFanClub_EventScript_BlackBeltPlayersFan
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, (NUM_TRAINER_FAN_CLUB_MEMBERS - 1), SaffronCity_PokemonTrainerFanClub_EventScript_BlackBeltOnlyNonFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_OnlyMasterHasMyRespect
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_BlackBeltPlayersFan::
	specialvar VAR_RESULT, Script_GetNumFansOfPlayerInTrainerFanClub
	goto_if_eq VAR_RESULT, 1, SaffronCity_PokemonTrainerFanClub_EventScript_BlackBeltOnlyFan
	msgbox SaffronCity_PokemonTrainerFanClub_Text_YourBattleStyleIsEducational
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_BlackBeltOnlyFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_WontStopBeingYourFan
	release
	end

SaffronCity_PokemonTrainerFanClub_EventScript_BlackBeltOnlyNonFan::
	msgbox SaffronCity_PokemonTrainerFanClub_Text_NeverBeFanOfAnyoneButMaster
	release
	end

SaffronCity_PokemonTrainerFanClub_Text_HuhYou::
    .string "哈？\n"
    .string "你……$"

SaffronCity_PokemonTrainerFanClub_Text_YourePlayerWereYourFansNow::
    .string "莫非你就是……\n"
    .string "……\p"
    .string "没错！就是你！\n"
    .string "你是{PLAYER}！\p"
    .string "我们正在谈论你！\p"
    .string "我们谈到一个非常优秀的\n"
    .string "训练家是如何产生的。\p"
    .string "那个人就是你！\n"
    .string "你太棒了！\p"
    .string "所以我们决定成为你的\n"
    .string "俱乐部！\p"
    .string "我们都希望你能继续战斗\n"
    .string "以显示你是多么棒。\p"
    .string "这样，可能别人也会像我\n"
    .string "一样成为你的粉丝。$"

SaffronCity_PokemonTrainerFanClub_Text_AlwaysCheerForYou::
    .string "我会永远为你鼓掌喝彩！\p"
    .string "加油，{PLAYER}！$"

SaffronCity_PokemonTrainerFanClub_Text_IllAlwaysBelieveInYou::
    .string "我会一直相信你，\n"
    .string "{PLAYER}。\p"
    .string "当你认真战斗时，向别人\n"
    .string "展现自己。$"

SaffronCity_PokemonTrainerFanClub_Text_WasYourFanNotAnymore::
    .string "很抱歉。\n"
    .string "我曾经是你粉丝。\p"
    .string "但是现在，你已\n"
    .string "雄风不再。\p"
    .string "我最近觉得{STR_VAR_1}\n"
    .string "更加棒。$"

SaffronCity_PokemonTrainerFanClub_Text_EveryonesYourFanButICantBe::
    .string "噢！\n"
    .string "{PLAYER}！\p"
    .string "最近人人都对你\n"
    .string "感兴趣。\p"
    .string "我知道原因。\n"
    .string "你知道你很强。\p"
    .string "但是，你知道吗？\p"
    .string "一旦我成为{STR_VAR_1}的粉丝，\n"
    .string "我就不能满足于我仅仅是一个粉丝。$"

SaffronCity_PokemonTrainerFanClub_Text_TrainersCoolWhenBattling::
    .string "我觉得训练家\n"
    .string "在他们战斗时非常棒。\p"
    .string "你觉得呢？$"

SaffronCity_PokemonTrainerFanClub_Text_CanYouAutographShorts::
    .string "哦！是{PLAYER}！\n"
    .string "太棒了！\p"
    .string "哦！\n"
    .string "哦，是啊！\p"
    .string "你能签个名吗？\n"
    .string "签在短裤上怎么样？$"

SaffronCity_PokemonTrainerFanClub_Text_CountingOnYou::
    .string "无论天气变得多么热……\p"
    .string "无论天气变得多么冷……\p"
    .string "我一直坚信这个理念，穿，\n"
    .string "短裤才是王道！\p"
    .string "我希望你能保持\n"
    .string "胜利！\p"
    .string "我相信你就像相信\n"
    .string "我的短裤一样！$"

SaffronCity_PokemonTrainerFanClub_Text_BrocksMyHero::
    .string "小刚是我心中的英雄！\n"
    .string "他是男人中的男人！\p"
    .string "呵呵，我让妈妈给我\n"
    .string "做了点事。\p"
    .string "我让她在我的短裤上\n"
    .string "绣上了“小刚”！$"

SaffronCity_PokemonTrainerFanClub_Text_BrocksFanToBitterEnd::
    .string "……\p"
    .string "……\p"
    .string "我是小刚的粉丝！\p"
    .string "即使我是他唯一的粉丝，\n"
    .string "我还是以我坚定的信念向\l"
    .string "我的短裤发誓！\p"
    .string "我会将做他的粉丝进行到底。$"

SaffronCity_PokemonTrainerFanClub_Text_BrocksLastWordOnCool::
    .string "小刚在战斗结束后说的话太帅了！\n"
    .string "表明故事结束了！\p"
    .string "他是我的榜样，我想\n"
    .string "向他学习！$"

SaffronCity_PokemonTrainerFanClub_Text_HadPleasureOfWatchingYouBattle::
    .string "{PLAYER}，我有幸能观看你\n"
    .string "的战斗。\p"
    .string "它让我找回了逝去青春\n"
    .string "的美好回忆。\p"
    .string "你可以继续为成功而奋斗。\n"
    .string "我是你的粉丝！$"

SaffronCity_PokemonTrainerFanClub_Text_NeverSeenTrainerOfYourMagnificence::
    .string "我到过很多地方\n"
    .string "旅行。\p"
    .string "但我从没见过像你这么伟大\n"
    .string "的训练家。\p"
    .string "相信自己的能力\n"
    .string "继续战斗吧！\p"
    .string "以此作为对我的承诺吧，\n"
    .string "我的小偶像！$"

SaffronCity_PokemonTrainerFanClub_Text_HmmAndYouAre::
    .string "嗯……\n"
    .string "你是谁？\p"
    .string "你是想成为我们俱乐部\n"
    .string "的成员吗？$"

SaffronCity_PokemonTrainerFanClub_Text_YouveStillAWaysToGo::
    .string "啊，你可是个热点\n"
    .string "话题啊，{PLAYER}。\p"
    .string "你看起来就有\n"
    .string "冠军相。\p"
    .string "但是要让我认为你能成为\n"
    .string "一个宝可梦史上的伟人……\p"
    .string "……\p"
    .string "你还有很长的路要走！$"

SaffronCity_PokemonTrainerFanClub_Text_YoullBeTalkedAboutIfYouKeepWinning::
    .string "聚集在这里的人都是\n"
    .string "宝可梦训练家的粉丝。\p"
    .string "他们看战斗的方式……\n"
    .string "是出色的画面。\p"
    .string "如果你继续胜利下去的话，\n"
    .string "也许在这里你会成为这里的话题。$"

SaffronCity_PokemonTrainerFanClub_Text_WantToBeLikeYouOneDay::
    .string "是{PLAYER}！\n"
    .string "是{PLAYER}！\p"
    .string "总有一天我会像{PLAYER}一样！$"

SaffronCity_PokemonTrainerFanClub_Text_EveryoneButMeStoppedBeingYourFan::
    .string "大家不再是{PLAYER}的\n"
    .string "粉丝了……\p"
    .string "但是这意味着我可以\n"
    .string "独占{PLAYER}！\p"
    .string "太好了！加油吧！\n"
    .string "我唯一的{PLAYER}！$"

SaffronCity_PokemonTrainerFanClub_Text_WantToBeLikeSabrina::
    .string "你知道我想说什么吗？\n"
    .string "我想像娜姿一样！\p"
    .string "我想成为一个像她一样有\n"
    .string "超能力的女孩！$"

SaffronCity_PokemonTrainerFanClub_Text_WontStopBeingSabrinasFan::
    .string "即使只有我一个，我也要坚持\n"
    .string "做娜姿的粉丝。\p"
    .string "我的梦想是成为娜姿，\n"
    .string "可爱又强大。\p"
    .string "我想成为一个像她一样有\n"
    .string "超能力的女孩！$"

SaffronCity_PokemonTrainerFanClub_Text_CanIBecomeCoolTrainerOneDay::
    .string "我不知道我能否有成为\n"
    .string "强大的训练家的一天？$"

SaffronCity_PokemonTrainerFanClub_Text_TheWayYouBattleIsCool::
    .string "哦，伙计！\n"
    .string "棒！很棒！\p"
    .string "……呃？\n"
    .string "不是，不是说你。\p"
    .string "是你的战斗方式。\n"
    .string "棒极了！$"

SaffronCity_PokemonTrainerFanClub_Text_ImOnlyOneLeftOfYourFans::
    .string "哟，{PLAYER}！\p"
    .string "看起来我是你唯一仅剩\n"
    .string "的粉丝了。\p"
    .string "但是你知道，我喜欢作为唯一\n"
    .string "的粉丝，这样压力小啊。\p"
    .string "继续保持！$"

SaffronCity_PokemonTrainerFanClub_Text_LoveWayTrainerTalks::
    .string "{STR_VAR_1}很棒，对吗？\n"
    .string "我喜欢他说话的方式。\p"
    .string "我很想有机会亲自\n"
    .string "见他一面。$"

SaffronCity_PokemonTrainerFanClub_Text_ImLoneTrainerFan::
    .string "嗯，你能相信吗？\n"
    .string "每个人都变成了你的粉丝。\p"
    .string "所以我们都通过后，\n"
    .string "就我一个是{STR_VAR_1}的粉丝？\p"
    .string "不管怎样，作为{STR_VAR_1}唯一的\n"
    .string "粉丝是我的风格。$"

SaffronCity_PokemonTrainerFanClub_Text_AdoreWayYouBattle::
    .string "哦，天哪！\n"
    .string "真的是你，{PLAYER}？\p"
    .string "我要告诉你，我喜欢你的\n"
    .string "战斗方式。\p"
    .string "我希望你能继续保持。\n"
    .string "我将是你的头号粉丝！$"

SaffronCity_PokemonTrainerFanClub_Text_ImYourNumberOneFan::
    .string "哦，天哪！\n"
    .string "这不是{PLAYER}吗！\p"
    .string "太令人失望了……\n"
    .string "我是你唯一的头号粉丝！\p"
    .string "没办法！\n"
    .string "至少让我为你喝彩！\p"
    .string "加油，加油，{PLAYER}！$"

SaffronCity_PokemonTrainerFanClub_Text_TrainerHasBeenOnFire::
    .string "最近，{STR_VAR_1}\n"
    .string "的人气一路飞涨。\p"
    .string "他的战斗方式\n"
    .string "是我喜欢的。$"

SaffronCity_PokemonTrainerFanClub_Text_EveryoneTalksAboutYou::
    .string "哦，你好！\n"
    .string "这不是{PLAYER}吗！\p"
    .string "最近，每个人都在\n"
    .string "谈论你。\p"
    .string "我感到寂寞，因为我\n"
    .string "喜欢{STR_VAR_1}。$"

SaffronCity_PokemonTrainerFanClub_Text_YouReallyAreAmazing::
    .string "太神了！\n"
    .string "{PLAYER}，你真的很棒！\p"
    .string "也许我不能只是观看，而是应该\n"
    .string "成为一名训练家。$"

SaffronCity_PokemonTrainerFanClub_Text_ImYourOnlyFan::
    .string "我是你仅有的粉丝……\n"
    .string "唉……真是寂寞得很……\p"
    .string "你不能努力一点，让别人\n"
    .string "关注关注你吗？$"

SaffronCity_PokemonTrainerFanClub_Text_WhyCantOthersSeeMastersDignity::
    .string "{STR_VAR_1}老师是如此孤傲……\n"
    .string "他是我喜欢的类型。\p"
    .string "为什么其他人看不到\n"
    .string "他流露出来的忧郁呢？$"

SaffronCity_PokemonTrainerFanClub_Text_BelieveInMasterWithAllMyHeart::
    .string "我全心全意地信任\n"
    .string "{STR_VAR_1}老师。\p"
    .string "即使只有我一个人\n"
    .string "相信他。\p"
    .string "我永远也不会感到孤独。\p"
    .string "只要我一直想念着\n"
    .string "{STR_VAR_1}老师。$"

SaffronCity_PokemonTrainerFanClub_Text_YourBattleStyleIsEducational::
    .string "嗨呀！\p"
    .string "你的作战风格最\n"
    .string "值得学习了。\p"
    .string "我希望你能继续向着\n"
    .string "成功努力，嘿！$"

SaffronCity_PokemonTrainerFanClub_Text_WontStopBeingYourFan::
    .string "不要只是看着别人战斗，\n"
    .string "自己战斗吧！\p"
    .string "……我道场的掌门曾今\n"
    .string "这样训斥我……\p"
    .string "但是这不会妨碍我成为\n"
    .string "你的粉丝！\p"
    .string "我无法不当你的粉丝！$"

SaffronCity_PokemonTrainerFanClub_Text_OnlyMasterHasMyRespect::
    .string "嗨呀！只有一个训练家\n"
    .string "能得到我的尊敬。\p"
    .string "在格斗道场，没有人\n"
    .string "比得过我的掌门。\p"
    .string "你应该像我一样成为\n"
    .string "我的掌门的粉丝！嗨呀！$"

SaffronCity_PokemonTrainerFanClub_Text_NeverBeFanOfAnyoneButMaster::
    .string "嗨呀！我很尊敬在格斗道场\n"
    .string "的我的掌门。\p"
    .string "除了我的掌门，我不会成为\n"
    .string "任何人的粉丝！\p"
    .string "我甚至会溜出道场\n"
    .string "来宣扬他的伟大！\p"
    .string "嗨呀！$"

