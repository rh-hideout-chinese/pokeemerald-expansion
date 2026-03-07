SSAnne_B1F_Room2_Frlg_MapScripts::
	.byte 0

SSAnne_B1F_Room2_EventScript_Huey::
	trainerbattle_single TRAINER_SAILOR_HUEY, SSAnne_B1F_Room2_Text_HueyIntro, SSAnne_B1F_Room2_Text_HueyDefeat
	msgbox SSAnne_B1F_Room2_Text_HueyPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_B1F_Room2_Text_HueyIntro::
    .string "即使我们水手也是有宝可梦！$"

SSAnne_B1F_Room2_Text_HueyDefeat::
    .string "不错，你还不赖。$"

SSAnne_B1F_Room2_Text_HueyPostBattle::
    .string "我们的宝可梦都是在\n"
    .string "出海时收服的。$"

