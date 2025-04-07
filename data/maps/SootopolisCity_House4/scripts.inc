SootopolisCity_House4_MapScripts::
	.byte 0

SootopolisCity_House4_EventScript_Man::
	msgbox SootopolisCity_House4_Text_AncientTreasuresWaitingInSea, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Woman::
	msgbox SootopolisCity_House4_Text_StrollUnderwaterWithPokemon, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Azumarill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, CRY_MODE_NORMAL
	msgbox SootopolisCity_House4_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SootopolisCity_House4_Text_AncientTreasuresWaitingInSea:
    .string "听着，我要告诉你\n一些好事。\p据说这附近的海里\n有一座古代遗迹，\p那里面一定有\n等待被发掘的宝藏。$"

SootopolisCity_House4_Text_StrollUnderwaterWithPokemon:
    .string "古代的宝藏…\p如果真的有当然好，\n但就算没有，\l和宝可梦一起进行一次\l海底旅行也不错。$"

SootopolisCity_House4_Text_Azumarill:
    .string "玛力露丽：马鹿马鹿。$"

