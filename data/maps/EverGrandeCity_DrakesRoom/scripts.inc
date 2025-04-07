EverGrandeCity_DrakesRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_DrakesRoom_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_DrakesRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_SidneysRoom_OnWarp
	.byte 0

@ Unused, Drake uses Sidneys identical OnWarp for some reason
EverGrandeCity_DrakesRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_DrakesRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_DrakesRoom_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_DrakesRoom_OnFrame:
	map_script_2 VAR_ELITE_4_STATE, 3, EverGrandeCity_DrakesRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_DrakesRoom_EventScript_WalkInCloseDoor::
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 4
	releaseall
	end

EverGrandeCity_DrakesRoom_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_DRAKE, EverGrandeCity_DrakesRoom_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_ELITE_4_STATE, 4, EverGrandeCity_DrakesRoom_EventScript_CloseDoor
	end

EverGrandeCity_DrakesRoom_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_DrakesRoom_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_DrakesRoom_EventScript_Drake::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_DRAKE, EverGrandeCity_DrakesRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_DrakesRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_DRAKE, EverGrandeCity_DrakesRoom_Text_Defeat
	goto EverGrandeCity_DrakesRoom_EventScript_Defeated
	end

EverGrandeCity_DrakesRoom_EventScript_PostBattleSpeech::
	msgbox EverGrandeCity_DrakesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_DrakesRoom_EventScript_Defeated::
	setvar VAR_0x8004, FANCOUNTER_DEFEATED_DRAKE
	special Script_TryGainNewFanFromCounter
	setflag FLAG_DEFEATED_ELITE_4_DRAKE
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_DrakesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_DrakesRoom_Text_IntroSpeech:
    .string "我是联盟四天王中最强的\n源治 龙之使者！\p在自然情况下，宝可梦是\n野外生存的。它们自由自在。\p有时候，它们会妨碍到人类。\n有时候，它们会帮助人类。\p当我们使用宝可梦作为伙伴\n进行战斗时，你知道如何才能成功吗？\p你知道需要什么条件吗？\p如果你不知道，那么你永远\n不可能战胜我！$"

EverGrandeCity_DrakesRoom_Text_Defeat:
    .string "漂亮，果然不是浪得虚名。$"

EverGrandeCity_DrakesRoom_Text_PostBattleSpeech:
    .string "你能走这么远已经证明了你\n自己作为宝可梦训练师的水平！\p看起来你知道战斗胜利的条件。\p是的，训练师所需要的\n就是高尚的心灵。\p宝可梦感受到\n训练师的心灵并从中学习。\p它们感受到训练师的心灵\n并且变得强大起来。\p走吧！继续前进！\n冠军正在等待你！$"

