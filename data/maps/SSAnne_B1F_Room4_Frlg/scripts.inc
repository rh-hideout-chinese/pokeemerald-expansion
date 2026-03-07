SSAnne_B1F_Room4_Frlg_MapScripts::
	.byte 0

SSAnne_B1F_Room4_EventScript_Leonard::
	trainerbattle_single TRAINER_SAILOR_LEONARD, SSAnne_B1F_Room4_Text_LeonardIntro, SSAnne_B1F_Room4_Text_LeonardDefeat
	msgbox SSAnne_B1F_Room4_Text_LeonardPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_B1F_Room4_EventScript_Duncan::
	trainerbattle_single TRAINER_SAILOR_DUNCAN, SSAnne_B1F_Room4_Text_DuncanIntro, SSAnne_B1F_Room4_Text_DuncanDefeat
	msgbox SSAnne_B1F_Room4_Text_DuncanPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_B1F_Room4_Text_LeonardIntro::
    .string "你知道他们是怎样\n"
    .string "评价水手的战斗的！$"

SSAnne_B1F_Room4_Text_LeonardDefeat::
    .string "很好！\n"
    .string "精彩的战斗，伙计！$"

SSAnne_B1F_Room4_Text_LeonardPostBattle::
    .string "哈哈哈！\n"
    .string "你想成为一名水手吗，伙计？$"

SSAnne_B1F_Room4_Text_DuncanIntro::
    .string "那就来吧！\n"
    .string "赌上我身为水手的尊严！$"

SSAnne_B1F_Room4_Text_DuncanDefeat::
    .string "你的精神让我沉没了！$"

SSAnne_B1F_Room4_Text_DuncanPostBattle::
    .string "你见过枯叶市的\n"
    .string "钓鱼大师了吗？$"

