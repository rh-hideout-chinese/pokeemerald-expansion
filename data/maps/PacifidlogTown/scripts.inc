PacifidlogTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, PacifidlogTown_OnResume
	.byte 0

PacifidlogTown_OnTransition:
	setflag FLAG_VISITED_PACIFIDLOG_TOWN
	end

PacifidlogTown_OnResume:
	setstepcallback STEP_CB_PACIFIDLOG_BRIDGE
	end

PacifidlogTown_EventScript_NinjaBoy::
	msgbox PacifidlogTown_Text_NeatHousesOnWater, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Girl::
	msgbox PacifidlogTown_Text_FastRunningCurrent, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Fisherman::
	msgbox PacifidlogTown_Text_SkyPillarTooScary, MSGBOX_NPC
	end

PacifidlogTown_EventScript_TownSign::
	msgbox PacifidlogTown_Text_TownSign, MSGBOX_SIGN
	end

PacifidlogTown_Text_FastRunningCurrent:
    .string "暮水镇与凯那市\n之间的海流很急，\p如果你打算冲浪，最后恐怕\n会被冲到谁也不知道的地方。$"

PacifidlogTown_Text_NeatHousesOnWater:
    .string "看，很简单的镇子吧？\n房子都建在水上！\p我就是在这儿出生的！$"

PacifidlogTown_Text_SkyPillarTooScary:
    .string "天空之柱？\p…哦，你是说不远处\n那座高高的塔吧。\p别问我，我不会去爬的，\n登那么高太可怕了。\p对我来说，还是住在海平面上的\n暮水镇中更安心。$"

PacifidlogTown_Text_TownSign:
    .string "暮水镇\p“早晨的太阳\n在海平面上微笑。”$"

