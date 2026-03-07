FiveIsland_LostCave_Room1_Frlg_MapScripts::
	.byte 0

FiveIsland_LostCave_Room1_EventScript_Lawson::
	trainerbattle_single TRAINER_RUIN_MANIAC_LAWSON, FiveIsland_LostCave_Room1_Text_LawsonIntro, FiveIsland_LostCave_Room1_Text_LawsonDefeat
	msgbox FiveIsland_LostCave_Room1_Text_LawsonPostBattle, MSGBOX_AUTOCLOSE
	end

FiveIsland_LostCave_Room1_Text_LawsonIntro::
    .string "啊\p"
    .string "我以为这是一个古老的遗迹。\n"
    .string "但是这里到处都是幽灵！$"

FiveIsland_LostCave_Room1_Text_LawsonDefeat::
    .string "啊啊啊啊啊啊啊！\n"
    .string "饶命啊！$"

FiveIsland_LostCave_Room1_Text_LawsonPostBattle::
    .string "我试着从这里走出去，\n"
    .string "但是总是在原地打转。\p"
    .string "也许\n"
    .string "这些卵石的数量是一个提示……$"

