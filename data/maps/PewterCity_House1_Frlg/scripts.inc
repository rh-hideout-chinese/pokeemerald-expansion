PewterCity_House1_Frlg_MapScripts::
	.byte 0

PewterCity_House1_EventScript_BaldingMan::
	msgbox PewterCity_House1_Text_TradeMonsAreFinicky, MSGBOX_NPC
	end

PewterCity_House1_EventScript_LittleBoy::
	lock
	msgbox PewterCity_House1_Text_NidoranSit
	call PewterCity_House1_EventScript_DoNidoranCry
	release
	end

PewterCity_House1_EventScript_Nidoran::
	lock
	faceplayer
	call PewterCity_House1_EventScript_DoNidoranCry
	applymovement LOCALID_PEWTER_HOUSE_NIDORAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

PewterCity_House1_EventScript_DoNidoranCry::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	waitse
	playmoncry SPECIES_NIDORAN_M, CRY_MODE_NORMAL
	msgbox PewterCity_House1_Text_Nidoran
	waitmoncry
	call EventScript_RestorePrevTextColor
	return

PewterCity_House1_Text_Nidoran::
    .string "尼多朗：啵啵！$"

PewterCity_House1_Text_NidoranSit::
    .string "尼多朗，坐下！$"

PewterCity_House1_Text_TradeMonsAreFinicky::
    .string "我们的宝可梦是外来的，\n"
    .string "所以它很难控制。\p"
    .string "外来的宝可梦就是说\n"
    .string "你是通过交换得到它的。\p"
    .string "它成长得很快，但是战斗中\n"
    .string "可能不会听训练家的话。\p"
    .string "但是如果有徽章就不一样了……$"

