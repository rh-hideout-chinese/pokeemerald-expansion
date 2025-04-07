AbandonedShip_Corridors_1F_MapScripts::
	.byte 0

AbandonedShip_Corridors_1F_EventScript_Youngster::
	msgbox AbandonedShip_Corridors_1F_Text_IsntItFunHere, MSGBOX_NPC
	end

AbandonedShip_Corridors_1F_EventScript_Charlie::
	trainerbattle_single TRAINER_CHARLIE, AbandonedShip_Corridors_1F_Text_CharlieIntro, AbandonedShip_Corridors_1F_Text_CharlieDefeat
	msgbox AbandonedShip_Corridors_1F_Text_CharliePostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Corridors_1F_Text_CharlieIntro:
    .string "带着游泳圈上船\n有什么好笑的？$"

AbandonedShip_Corridors_1F_Text_CharlieDefeat:
    .string "啊，你赢了！$"

AbandonedShip_Corridors_1F_Text_CharliePostBattle:
    .string "抓着游泳圈的时候\n是很难扔精灵球的！$"

AbandonedShip_Corridors_1F_Text_IsntItFunHere:
    .string "这里挺好玩的吧？\n我一来这里就兴奋！$"
