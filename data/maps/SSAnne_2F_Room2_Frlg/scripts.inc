SSAnne_2F_Room2_Frlg_MapScripts::
	.byte 0

SSAnne_2F_Room2_EventScript_Dale::
	trainerbattle_single TRAINER_FISHERMAN_DALE, SSAnne_2F_Room2_Text_DaleIntro, SSAnne_2F_Room2_Text_DaleDefeat
	msgbox SSAnne_2F_Room2_Text_DalePostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_2F_Room2_EventScript_Brooks::
	trainerbattle_single TRAINER_GENTLEMAN_BROOKS, SSAnne_2F_Room2_Text_BrooksIntro, SSAnne_2F_Room2_Text_BrooksDefeat
	msgbox SSAnne_2F_Room2_Text_BrooksPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_2F_Room2_Text_BrooksIntro::
    .string "和年轻人战斗能使我保持年轻。$"

SSAnne_2F_Room2_Text_BrooksDefeat::
    .string "战斗棒极了！\n"
    .string "啊，我感觉我又变年轻了！$"

SSAnne_2F_Room2_Text_BrooksPostBattle::
    .string "如果放在15年前，我肯定我能赢！$"

SSAnne_2F_Room2_Text_DaleIntro::
    .string "看看我钓到了什么！$"

SSAnne_2F_Room2_Text_DaleDefeat::
    .string "全都倒下了！$"

SSAnne_2F_Room2_Text_DalePostBattle::
    .string "聚会？\p"
    .string "船上的聚会现在应该结束了。$"

