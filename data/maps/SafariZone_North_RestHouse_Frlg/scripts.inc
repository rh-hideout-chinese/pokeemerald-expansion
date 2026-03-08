SafariZone_North_RestHouse_Frlg_MapScripts::
	.byte 0

SafariZone_North_RestHouse_EventScript_Fisher::
	msgbox SafariZone_East_Text_PrizeInDeepestPartOfSafariZone, MSGBOX_NPC
	end

SafariZone_North_RestHouse_EventScript_Scientist::
	msgbox SafariZone_East_Text_KeepAnyItemFoundOnSafari, MSGBOX_NPC
	end

SafariZone_North_RestHouse_EventScript_Gentleman::
	msgbox SafariZone_East_Text_MyEeveeEvolvedIntoFlareon, MSGBOX_NPC
	end

SafariZone_East_Text_KeepAnyItemFoundOnSafari::
    .string "你能拿走任何你在野生原野区\n"
    .string "找到的东西。\p"
    .string "但是如果你想要一次把\n"
    .string "所有东西都拿走的话，\p"
    .string "你的时间会耗尽的。$"

SafariZone_East_Text_PrizeInDeepestPartOfSafariZone::
    .string "走到野生原野区的最深处。\n"
    .string "你就会赢得奖品！$"

SafariZone_East_Text_MyEeveeEvolvedIntoFlareon::
    .string "我的伊布进化成了火精灵。\p"
    .string "但是，我一个朋友的伊布进化成了\n"
    .string "水精灵。我不知道这是为什么？$"

