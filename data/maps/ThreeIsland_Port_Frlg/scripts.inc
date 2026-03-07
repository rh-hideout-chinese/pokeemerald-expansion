ThreeIsland_Port_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ThreeIsland_Port_OnTransition
	.byte 0

ThreeIsland_Port_OnTransition::
	clearflag FLAG_SYS_PC_STORAGE_DISABLED
	setflag FLAG_SEVII_DETOUR_FINISHED
	end

ThreeIsland_Port_EventScript_Woman::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_TWO_ISLAND_JOYFUL_GAME_CORNER, 2, ThreeIsland_Port_EventScript_WomanLostelleFound
	goto_if_ge VAR_MAP_SCENE_THREE_ISLAND, 4, ThreeIsland_Port_EventScript_WomanBikersGone
	msgbox ThreeIsland_Port_Text_IllCallThePolice
	release
	end

ThreeIsland_Port_EventScript_WomanLostelleFound::
	msgbox ThreeIsland_Port_Text_EverythingTurnedOutForBest
	release
	end

ThreeIsland_Port_EventScript_WomanBikersGone::
	msgbox ThreeIsland_Port_Text_ThankGoodnessBikersGone
	release
	end

ThreeIsland_Port_EventScript_Biker1::
	msgbox ThreeIsland_Port_Text_WereKantoRiderFederation, MSGBOX_NPC
	end

ThreeIsland_Port_EventScript_Biker2::
	lock
	msgbox ThreeIsland_Port_Text_ForkOverMoney
	release
	end

ThreeIsland_Port_Text_WereKantoRiderFederation::
    .string "我们是关都飙车族！\n"
    .string "呜！呜！呜！\p"
    .string "我的车子太安静了，所以\n"
    .string "我不得不自己发出排气的声音！$"

ThreeIsland_Port_Text_ForkOverMoney::
    .string "嘿，站住，小姐！\n"
    .string "借点儿钱花花！$"

ThreeIsland_Port_Text_IllCallThePolice::
    .string "哎！\p"
    .string "你，你是谁？！\n"
    .string "我要叫警察了！$"

ThreeIsland_Port_Text_ThankGoodnessBikersGone::
    .string "那些飙车族……\n"
    .string "它们都不见了？\p"
    .string "真是谢天谢地！\n"
    .string "那些家伙都让我烦透了！$"

ThreeIsland_Port_Text_EverythingTurnedOutForBest::
    .string "那些飙车族不见了，\n"
    .string "但小迷很安全。\p"
    .string "一切事情都变好了！$"

