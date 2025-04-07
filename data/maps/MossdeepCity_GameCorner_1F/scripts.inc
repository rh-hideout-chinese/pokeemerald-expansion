MossdeepCity_GameCorner_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MossdeepCity_GameCorner_1F_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MossdeepCity_GameCorner_1F_OnWarp
	map_script MAP_SCRIPT_ON_LOAD, CableClub_OnLoad
	.byte 0

MossdeepCity_GameCorner_1F_OnWarp:
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_CheckTurnAttendant
	.2byte 0

MossdeepCity_GameCorner_1F_OnFrame:
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_ExitMinigameRoom
	.2byte 0

@ Script is redundant, the label in the goto also does lock and faceplayer
MossdeepCity_GameCorner_1F_EventScript_InfoMan::
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_InfoMan2
	release
	end

@ Script is redundant, the label in the goto also does lock and faceplayer
MossdeepCity_GameCorner_1F_EventScript_OldMan::
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_OldMan2
	release
	end


@ Everything below is leftover from RS
@ The house that was here in RS was moved to Sootopolis and replaced by the Game Corner
@ The text below is unused and duplicated in its replacement in Sootopolis City
@ And the BG Door event was moved inaccessibly into a wall

RS_MysteryEventsHouse_EventScript_Door::
	msgbox RS_MysteryEventsHouse_Text_DoorIsLocked, MSGBOX_SIGN
	end

RS_MysteryEventsHouse_Text_OldManGreeting:
    .string "我年轻的时候，作为训练师\n在全世界旅游。\p现在我已经变成一个老头了，\n我现在唯一的乐趣就是观看\l年轻训练师的战斗。$"

RS_MysteryEventsHouse_Text_DoorIsLocked:
    .string "门锁上了。$"

RS_MysteryEventsHouse_Text_ChallengeVisitingTrainer:
    .string "名叫{STR_VAR_1}的训练师\n来我家拜访了。\p你想挑战\n{STR_VAR_1}吗？$"

RS_MysteryEventsHouse_Text_YouWontBattle:
    .string "你不想战斗？看不到你的战斗\n我好失望啊…$"

RS_MysteryEventsHouse_Text_KeepItToA3On3:
    .string "很好，很好！\p但是我的房子没那么结实。\p我们可不可以来场\n3对3的比赛？$"

RS_MysteryEventsHouse_Text_SaveYourProgress:
    .string "在你们两个战斗前\n可以先保存下进度。$"

RS_MysteryEventsHouse_Text_HopeToSeeAGoodMatch:
    .string "我希望看到一场好的比赛。$"

RS_MysteryEventsHouse_Text_BattleTie:
    .string "所以，这会是陷入僵局\p一场双方都没人让步\n的战斗！$"

RS_MysteryEventsHouse_Text_BattleWon:
    .string "太优秀了！\p我彷佛又看到了\n我年轻的时候！$"

RS_MysteryEventsHouse_Text_BattleLost:
    .string "啊，太糟糕了！\p但是确实是场不错的战斗。\n希望下次你可以赢。$"
