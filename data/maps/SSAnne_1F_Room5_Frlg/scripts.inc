SSAnne_1F_Room5_Frlg_MapScripts::
	.byte 0

SSAnne_1F_Room5_EventScript_Arthur::
	trainerbattle_single TRAINER_GENTLEMAN_ARTHUR, SSAnne_1F_Room5_Text_ArthurIntro, SSAnne_1F_Room5_Text_ArthurDefeat
	msgbox SSAnne_1F_Room5_Text_ArthurPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_1F_Room5_Text_ArthurIntro::
    .string "你这个无礼的小伙子！\n"
    .string "你怎么敢闯进这里！$"

SSAnne_1F_Room5_Text_ArthurDefeat::
    .string "哼！你无礼的孩子！\n"
    .string "你真没礼貌！$"

SSAnne_1F_Room5_Text_ArthurPostBattle::
    .string "我希望能独自呆一会！\n"
    .string "给我出去！$"

