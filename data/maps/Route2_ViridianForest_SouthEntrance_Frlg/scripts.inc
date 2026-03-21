Route2_ViridianForest_SouthEntrance_Frlg_MapScripts::
	.byte 0

Route2_ViridianForest_SouthEntrance_EventScript_Woman1::
	msgbox Route2_ViridianForest_SouthEntrance_Text_ForestIsMaze, MSGBOX_NPC
	end

Route2_ViridianForest_SouthEntrance_EventScript_Woman2::
	msgbox Route2_ViridianForest_SouthEntrance_Text_RattataHasWickedBite, MSGBOX_NPC
	end

Route2_ViridianForest_SouthEntrance_Text_ForestIsMaze::
    .string "你准备去常青森林吗？\n"
    .string "那里是个天然的迷宫。\l"
    .string "小心别迷路了。$"

Route2_ViridianForest_SouthEntrance_Text_RattataHasWickedBite::
    .string "小拉达虽小，\n"
    .string "但它能到处乱咬。\p"
    .string "你有抓到过一只吗？$"

