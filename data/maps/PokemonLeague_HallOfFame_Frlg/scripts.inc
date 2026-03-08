PokemonLeague_HallOfFame_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PokemonLeague_HallOfFame_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PokemonLeague_HallOfFame_OnWarp
	.byte 0

PokemonLeague_HallOfFame_OnWarp::
	map_script_2 VAR_TEMP_1, 0, PokemonLeague_HallOfFame_EventScript_TurnPlayerNorth
	.2byte 0

PokemonLeague_HallOfFame_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

PokemonLeague_HallOfFame_OnFrame::
	map_script_2 VAR_TEMP_1, 0, PokemonLeague_HallOfFame_EventScript_EnterRoom
	.2byte 0

PokemonLeague_HallOfFame_EventScript_EnterRoom::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_PLAYER, PokemonLeague_HallOfFame_Movement_EnterRoom
	waitmovement 0
	applymovement LOCALID_HALL_OF_FAME_PROF_OAK, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 18
	msgbox PokemonLeague_HallOfFame_Text_OakCongratulations
	closemessage
	applymovement LOCALID_HALL_OF_FAME_PROF_OAK, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	dofieldeffect FLDEFF_HALL_OF_FAME_RECORD_FRLG
	waitfieldeffect FLDEFF_HALL_OF_FAME_RECORD_FRLG
	delay 40
	setvar VAR_TEMP_1, 1
	call EventScript_SetDefeatedEliteFourFlagsVars
	setrespawn HEAL_LOCATION_PALLET_TOWN
	fadescreenspeed FADE_TO_BLACK, 24
	special EnterHallOfFame
	waitstate
	releaseall
	end

PokemonLeague_HallOfFame_Movement_EnterRoom::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PokemonLeague_HallOfFame_Text_OakCongratulations::
    .string "大木：咳嗯！\n"
    .string "祝贺，{PLAYER}！\p"
    .string "这层楼是\n"
    .string "宝可梦荣誉殿堂。\p"
    .string "宝可梦联盟冠军\n"
    .string "将因为他们的战绩而而得到荣光。\p"
    .string "他们的宝可梦也会被记录在\n"
    .string "荣誉殿堂里。\p"
    .string "{PLAYER}！\p"
    .string "你努力战斗到此成为了\n"
    .string "新的联盟冠军。\p"
    .string "祝贺你，{PLAYER}，你和你的\n"
    .string "宝可梦是荣誉殿堂的成员了！$"

