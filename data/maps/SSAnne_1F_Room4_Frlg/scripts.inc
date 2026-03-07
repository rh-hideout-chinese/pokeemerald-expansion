SSAnne_1F_Room4_Frlg_MapScripts::
	.byte 0

SSAnne_1F_Room4_EventScript_Woman::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, SSAnne_1F_Room4_EventScript_WomanPlayerMale
	msgbox SSAnne_1F_Room4_Text_WaitressCherryPiePlease
	release
	end

SSAnne_1F_Room4_EventScript_WomanPlayerMale::
	msgbox SSAnne_1F_Room4_Text_WaiterCherryPiePlease
	release
	end

SSAnne_1F_Room4_Text_WaiterCherryPiePlease::
    .string "服务员，我想要一个樱桃派，\n"
    .string "麻烦你了！$"

SSAnne_1F_Room4_Text_WaitressCherryPiePlease::
    .string "女服务员，我想要个樱桃派，\n"
    .string "麻烦你了！$"

