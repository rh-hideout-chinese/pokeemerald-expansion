SaffronCity_MrPsychicsHouse_Frlg_MapScripts::
	.byte 0

SaffronCity_MrPsychicsHouse_EventScript_MrPsychic::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM29_FROM_MR_PSYCHIC, SaffronCity_MrPsychicsHouse_EventScript_AlreadyGotTM29
	msgbox SaffronCity_MrPsychicsHouse_Text_YouWantedThis
	checkitemspace ITEM_TM29
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_MrPsychicsHouse_EventScript_NoRoomForTM29
	giveitem_msg SaffronCity_MrPsychicsHouse_Text_ReceivedTM29FromMrPsychic, ITEM_TM29
	msgbox SaffronCity_MrPsychicsHouse_Text_ExplainTM29
	setflag FLAG_GOT_TM29_FROM_MR_PSYCHIC
	release
	end

SaffronCity_MrPsychicsHouse_EventScript_NoRoomForTM29::
	msgbox SaffronCity_MrPsychicsHouse_Text_YouveNoRoom
	release
	end

SaffronCity_MrPsychicsHouse_EventScript_AlreadyGotTM29::
	msgbox SaffronCity_MrPsychicsHouse_Text_ExplainTM29
	release
	end

SaffronCity_MrPsychicsHouse_Text_YouWantedThis::
    .string "……慢着！什么都别说！\p"
    .string "我有预感你需要这个！$"

SaffronCity_MrPsychicsHouse_Text_ReceivedTM29FromMrPsychic::
    .string "{PLAYER}从超能先生那里\n"
    .string "得到TM29。$"

SaffronCity_MrPsychicsHouse_Text_ExplainTM29::
    .string "你已经知道了，不是吗？\n"
    .string "TM29是精神强念。\p"
    .string "这是一种可以降低目标\n"
    .string "特殊能力值的攻击。$"

SaffronCity_MrPsychicsHouse_Text_YouveNoRoom::
    .string "你想要把这个放哪儿？\n"
    .string "你已经没有空间了。$"

