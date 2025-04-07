MossdeepCity_House4_MapScripts::
	.byte 0

MossdeepCity_House4_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, MossdeepCity_House4_EventScript_CanBattleAtSecretBases
	msgbox MossdeepCity_House4_Text_BrotherLikesToFindBases, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_CanBattleAtSecretBases::
	msgbox MossdeepCity_House4_Text_BrotherLikesToVisitBasesAndBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_NinjaBoy::
	lock
	faceplayer
	special CheckPlayerHasSecretBase
	goto_if_eq VAR_RESULT, FALSE, MossdeepCity_House4_EventScript_NoSecretBase
	special GetSecretBaseNearbyMapName
	msgbox MossdeepCity_House4_Text_YouMadeSecretBaseNearX, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_NoSecretBase::
	msgbox MossdeepCity_House4_Text_MakeSecretBase, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox MossdeepCity_House4_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

MossdeepCity_House4_Text_BrotherLikesToFindBases:
    .string "我弟弟喜欢寻找\n别人的秘密基地。$"

MossdeepCity_House4_Text_BrotherLikesToVisitBasesAndBattle:
    .string "我弟弟喜欢寻找\n别人的秘密基地，\l和他们战斗。$"

MossdeepCity_House4_Text_YouMadeSecretBaseNearX:
    .string "是你在{STR_VAR_1}附近\n建的秘密基地吗？$"

MossdeepCity_House4_Text_MakeSecretBase:
    .string "你造一个秘密基地吧，\n然后我就去找出来！$"

MossdeepCity_House4_Text_Skitty:
    .string "向尾喵：喵呀？$"

