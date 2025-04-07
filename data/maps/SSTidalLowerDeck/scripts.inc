SSTidalLowerDeck_MapScripts::
	.byte 0

SSTidalLowerDeck_EventScript_Phillip::
	trainerbattle_single TRAINER_PHILLIP, SSTidalLowerDeck_Text_PhillipIntro, SSTidalLowerDeck_Text_PhillipDefeat
	msgbox SSTidalLowerDeck_Text_PhillipPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalLowerDeck_EventScript_Leonard::
	trainerbattle_single TRAINER_LEONARD, SSTidalLowerDeck_Text_LeonardIntro, SSTidalLowerDeck_Text_LeonardDefeat
	msgbox SSTidalLowerDeck_Text_LeonardPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalLowerDeck_Text_PhillipIntro:
    .string "啊！一天到晚打扫这么大的地方\n我已经受够了！\p我们速战速决！$"

SSTidalLowerDeck_Text_PhillipDefeat:
    .string "弟弟，我输了！$"

SSTidalLowerDeck_Text_PhillipPostBattle:
    .string "我们是清扫兄弟！\p哥哥负责倒洗涤剂，\n弟弟负责擦地板！$"

SSTidalLowerDeck_Text_LeonardIntro:
    .string "这里是船体的底部，\n空间很大，\l正好适合来一场宝可梦对战。$"

SSTidalLowerDeck_Text_LeonardDefeat:
    .string "哥哥，我输了！$"

SSTidalLowerDeck_Text_LeonardPostBattle:
    .string "我们是清扫兄弟！\p哥哥负责倒洗涤剂，\n弟弟负责擦地板！$"

