CinnabarIsland_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CinnabarIsland_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

CinnabarIsland_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_CINNABAR_ISLAND
	end

CinnabarIsland_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

CinnabarIsland_PokemonCenter_1F_EventScript_Gentleman::
	msgbox CinnabarIsland_PokemonCenter_1F_Text_VisitUnionRoom, MSGBOX_NPC
	end

CinnabarIsland_PokemonCenter_1F_EventScript_CooltrainerF::
	msgbox CinnabarIsland_PokemonCenter_1F_Text_CinnabarGymLocked, MSGBOX_NPC
	end

CinnabarIsland_PokemonCenter_1F_EventScript_Youngster::
	msgbox CinnabarIsland_PokemonCenter_1F_Text_EvolutionCanWaitForNewMoves, MSGBOX_NPC
	end

CinnabarIsland_PokemonCenter_1F_EventScript_Bill::
	lock
	faceplayer
	msgbox CinnabarIsland_PokemonCenter_1F_Text_ReadyToSailToOneIsland, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CinnabarIsland_PokemonCenter_1F_EventScript_NotReadyToSail
	msgbox CinnabarIsland_PokemonCenter_1F_Text_LetsGo
	closemessage
	playbgm MUS_FOLLOW_ME, 1
	savebgm MUS_FOLLOW_ME
	setflag FLAG_DONT_TRANSITION_MUSIC
	setflag FLAG_HIDE_CINNABAR_POKECENTER_BILL
	delay 20
	call_if_eq VAR_FACING, DIR_SOUTH, CinnabarIsland_PokemonCenter_1F_EventScript_ExitWithBillSouth
	call_if_eq VAR_FACING, DIR_EAST, CinnabarIsland_PokemonCenter_1F_EventScript_ExitWithBillEast
	call_if_eq VAR_FACING, DIR_WEST, CinnabarIsland_PokemonCenter_1F_EventScript_ExitWithBillWest
	removeobject LOCALID_CINNABAR_POKEMON_CENTER_BILL
	setvar VAR_MAP_SCENE_CINNABAR_ISLAND_2, 1
	clearflag FLAG_HIDE_CINNABAR_BILL
	warp MAP_CINNABAR_ISLAND, 14, 11
	waitstate
	release
	end

CinnabarIsland_PokemonCenter_1F_EventScript_ExitWithBillSouth::
	applymovement LOCALID_CINNABAR_POKEMON_CENTER_BILL, CinnabarIsland_PokemonCenter_1F_Movement_BillExit
	applymovement LOCALID_PLAYER, CinnabarIsland_PokemonCenter_1F_Movement_PlayerExitSouth
	waitmovement 0
	return

CinnabarIsland_PokemonCenter_1F_EventScript_ExitWithBillEast::
	applymovement LOCALID_CINNABAR_POKEMON_CENTER_BILL, CinnabarIsland_PokemonCenter_1F_Movement_BillExitEast
	applymovement LOCALID_PLAYER, CinnabarIsland_PokemonCenter_1F_Movement_PlayerExitEast
	waitmovement 0
	return

CinnabarIsland_PokemonCenter_1F_EventScript_ExitWithBillWest::
	applymovement LOCALID_CINNABAR_POKEMON_CENTER_BILL, CinnabarIsland_PokemonCenter_1F_Movement_BillExit
	applymovement LOCALID_PLAYER, CinnabarIsland_PokemonCenter_1F_Movement_PlayerExitWest
	waitmovement 0
	return

CinnabarIsland_PokemonCenter_1F_EventScript_NotReadyToSail::
	msgbox CinnabarIsland_PokemonCenter_1F_Text_OhNotDoneYet
	release
	end

CinnabarIsland_PokemonCenter_1F_Movement_BillExit::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	delay_8
	set_invisible
	step_end

CinnabarIsland_PokemonCenter_1F_Movement_PlayerExitSouth::
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	delay_16
	walk_down
	step_end

CinnabarIsland_PokemonCenter_1F_Movement_BillExitEast::
	walk_up
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	delay_8
	set_invisible
	step_end

CinnabarIsland_PokemonCenter_1F_Movement_PlayerExitEast::
	delay_16
	delay_16
	delay_16
	face_left
	delay_16
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	delay_8
	walk_down
	delay_8
	set_invisible
	step_end

CinnabarIsland_PokemonCenter_1F_Movement_PlayerExitWest::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	delay_16
	walk_down
	step_end

CinnabarIsland_PokemonCenter_1F_Text_CinnabarGymLocked::
    .string "我是特地来拜访红莲道馆的，\n"
    .string "但是这里的门却锁得很紧。\p"
    .string "这附近某个地方\n"
    .string "一定有一把能开门的钥匙。\p"
    .string "它该不会在\n"
    .string "那幢被烧毁的房子里吧？\p"
    .string "我听说这岛上的道馆馆主的朋友\n"
    .string "曾经住在那里。$"

CinnabarIsland_PokemonCenter_1F_Text_VisitUnionRoom::
    .string "你有那么一些朋友吗？\p"
    .string "毫无疑问，\n"
    .string "和他们联机是很有趣的。\p"
    .string "既然如此何不去\n"
    .string "联合房间看看呢？\p"
    .string "谁知道呢，\n"
    .string "你会交到新的朋友也说不定呢。\p"
    .string "我想联合房间\n"
    .string "一定值得一去。$"

CinnabarIsland_PokemonCenter_1F_Text_EvolutionCanWaitForNewMoves::
    .string "宝可梦在取消进化之后\n"
    .string "仍然可以学会新技能。\p"
    .string "可以等新技能学会了\n"
    .string "之后再进化。$"

CinnabarIsland_PokemonCenter_1F_Text_ReadyToSailToOneIsland::
    .string "正辉：嘿，让我好等！\n"
    .string "准备好乘船去一之岛了吗？$"

CinnabarIsland_PokemonCenter_1F_Text_OhNotDoneYet::
    .string "噢，你还是没准备好？$"

CinnabarIsland_PokemonCenter_1F_Text_LetsGo::
    .string "好，就是这样。\n"
    .string "出发了！$"

