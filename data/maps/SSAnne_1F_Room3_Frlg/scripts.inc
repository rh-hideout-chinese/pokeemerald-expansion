SSAnne_1F_Room3_Frlg_MapScripts::
	.byte 0

SSAnne_1F_Room3_EventScript_LittleGirl::
	msgbox SSAnne_1F_Room3_Text_AlwaysTravelWithWigglytuff, MSGBOX_NPC
	end

SSAnne_1F_Room3_EventScript_BaldingMan::
	msgbox SSAnne_1F_Room3_Text_CruiseIsElegantAndCozy, MSGBOX_NPC
	end

SSAnne_1F_Room3_EventScript_Wigglytuff::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WIGGLYTUFF, CRY_MODE_NORMAL
	msgbox SSAnne_1F_Room3_Text_Wigglytuff
	waitmoncry
	release
	end

SSAnne_1F_Room3_Text_CruiseIsElegantAndCozy::
    .string "世界漫游真是优雅舒适！$"

SSAnne_1F_Room3_Text_AlwaysTravelWithWigglytuff::
    .string "我旅行时总是带着胖可丁。\n"
    .string "我出门时从来不会丢下它。$"

SSAnne_1F_Room3_Text_Wigglytuff::
    .string "胖可丁：噗噗噗噗！$"

