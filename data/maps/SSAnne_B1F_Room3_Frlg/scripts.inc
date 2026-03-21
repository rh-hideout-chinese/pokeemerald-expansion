SSAnne_B1F_Room3_Frlg_MapScripts::
	.byte 0

SSAnne_B1F_Room3_EventScript_Dylan::
	trainerbattle_single TRAINER_SAILOR_DYLAN, SSAnne_B1F_Room3_Text_DylanIntro, SSAnne_B1F_Room3_Text_DylanDefeat
	msgbox SSAnne_B1F_Room3_Text_DylanPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_B1F_Room3_Text_DylanIntro::
    .string "我喜欢像你一样争强好胜的孩子！$"

SSAnne_B1F_Room3_Text_DylanDefeat::
    .string "啊！\n"
    .string "我输了！$"

SSAnne_B1F_Room3_Text_DylanPostBattle::
    .string "海洋宝可梦在深水中生活。\n"
    .string "你需要一个破钓竿来把它们钓上钩！$"

