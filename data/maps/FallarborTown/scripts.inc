FallarborTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_OnTransition
	.byte 0

FallarborTown_OnTransition:
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	clearflag FLAG_CONTEST_SKETCH_CREATED
	end

FallarborTown_EventScript_ExpertM::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_EventScript_ExpertMNormal
	msgbox FallarborTown_Text_ShadyCharactersCozmosHome, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_ExpertMNormal::
	msgbox FallarborTown_Text_RegionKnownForMeteors, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_Girl::
	msgbox FallarborTown_Text_MyPreciousAzurill, MSGBOX_NPC
	end

FallarborTown_EventScript_Gentleman::
	msgbox FallarborTown_Text_HaveYouChallengedFlannery, MSGBOX_NPC
	end

FallarborTown_EventScript_Azurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox FallarborTown_Text_Azurill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_EventScript_BattleTentSign::
	msgbox FallarborTown_Text_BattleTentSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_TownSign::
	msgbox FallarborTown_Text_TownSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_MoveTutorSign::
	msgbox FallarborTown_Text_MoveTutorSign, MSGBOX_SIGN
	end

FallarborTown_Text_ShadyCharactersCozmosHome:
    .string "发生了些\n很讨厌的事！\p我总是看到鬼鬼祟祟的家伙\n在索蓝斯博士家进进出出……$"

FallarborTown_Text_RegionKnownForMeteors:
    .string "自古这片地区\n就以陨石而闻名，\p据说流星瀑布就是很久以前\n一颗陨石掉下来砸成的。$"

FallarborTown_Text_MyPreciousAzurill:
    .string "来啊！来看看！\n这是我珍贵的露力丽！\p滑滑软软的，多漂亮！$"

FallarborTown_Text_Azurill:
    .string "露力丽：蓝蓝路～～～～～。$"

FallarborTown_Text_HaveYouChallengedFlannery:
    .string "你挑战过釜炎镇道馆的馆主\n亚莎了吗？\p那女孩的爷爷非常出名，\n他曾是宝可梦联盟的\l四天王之一，\p如今亚莎也成长为一个\n出色的训练家\l并不让我感到奇怪。$"

FallarborTown_Text_BattleTentSign:
    .string "对战帐篷秋叶镇分址\n“愿优秀的队伍在这里聚集！”$"

FallarborTown_Text_TownSign:
    .string "秋叶镇\n“一个拥有小花园的农业小镇。”$"

FallarborTown_Text_MoveTutorSign:
    .string "招式指导员的家\n“教会宝可梦新的招式。”$"

