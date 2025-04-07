BattleFrontier_Lounge4_MapScripts::
	.byte 0

BattleFrontier_Lounge4_EventScript_Woman::
	msgbox BattleFrontier_Lounge4_Text_WonderIfInterviewsAiring, MSGBOX_NPC
	end

BattleFrontier_Lounge4_EventScript_Cook::
	msgbox BattleFrontier_Lounge4_Text_IfIOpenedRestaurantHere, MSGBOX_NPC
	end

BattleFrontier_Lounge4_EventScript_Man::
	msgbox BattleFrontier_Lounge4_Text_NeedBreatherAfterBattles, MSGBOX_NPC
	end

BattleFrontier_Lounge4_Text_WonderIfInterviewsAiring:
    .string "不知道今天会不会有关于强大训练师的\n电视采访？$"

BattleFrontier_Lounge4_Text_IfIOpenedRestaurantHere:
    .string "在这儿开个饭馆的话\n肯定能挣大钱吧。$"

BattleFrontier_Lounge4_Text_NeedBreatherAfterBattles:
    .string "呼…\p那么紧张的战斗之后，\n我得稍微休息一下了…\p但即使是现在，我脑子里也会\n一直设计着战斗策略。$"

