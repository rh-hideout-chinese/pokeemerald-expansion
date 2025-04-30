.set LOCALID_VIVI, 1
.set LOCALID_VICTOR, 2
.set LOCALID_VICTORIA, 3
.set LOCALID_VICKY, 4

Route111_WinstrateFamilysHouse_MapScripts::
	.byte 0

Route111_WinstrateFamilysHouse_EventScript_Victor::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VICTOR
	msgbox Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Victoria::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VICTORIA
	goto_if_set FLAG_RECEIVED_MACHO_BRACE, Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace
	msgbox Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace, MSGBOX_DEFAULT
	giveitem ITEM_MACHO_BRACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MACHO_BRACE
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace::
	msgbox Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vivi::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VIVI
	msgbox Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vicky::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VICKY
	goto_if_set FLAG_TEMP_4, Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrong, MSGBOX_DEFAULT
	setflag FLAG_TEMP_4
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo::
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_0x8008, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou:
    .string "你是我所见过的训练家中\n指挥宝可梦最纯熟的。\p但是，我要告诉你——我的儿子\n比你还要厉害。\p他甚至成为了宝可梦联盟\n挑战者，你知道吗。$"

Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace:
    .string "我们使用强制锻炼器\n有效提高宝可梦\l的力量。\p你战胜了我们所有人，\n我不知道你是否需要这个\l请收下我们给你的强制锻炼器。$"

Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles:
    .string "当进行宝可梦对战时，\n我们变得很激情。$"

Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers:
    .string "妈妈比爸爸厉害。\p我比妈妈厉害。\p奶奶比我厉害！\p但是我的哥哥\n比奶奶还要厉害哟。$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrong:
    .string "显然你很厉害。\p但是如果你和我的孙子战斗\n你一定会输到哭泣的。\p他比我们所知道的训练家\n都要厉害。\p他现在一定在挑战\n联盟冠军吧。\p你会认识我的孙子的，他应该\n已经是冠军了！$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort:
    .string "我的孙子现在一定\n在挑战联盟冠军。\p你会认识我的孙子的，他应该\n已经是冠军了！$"

