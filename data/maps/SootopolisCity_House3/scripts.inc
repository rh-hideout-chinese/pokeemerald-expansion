SootopolisCity_House3_MapScripts::
	.byte 0

SootopolisCity_House3_EventScript_Woman::
	lock
	faceplayer
	msgbox SootopolisCity_House3_Text_JuanHasManyFansDoYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SootopolisCity_House3_EventScript_HaveFans
	msgbox SootopolisCity_House3_Text_LonesomeTryWorkingHarder, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_HaveFans::
	msgbox SootopolisCity_House3_Text_YouMustBePrettyStrong, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_Girl::
	msgbox SootopolisCity_House3_Text_TrainerFanClubWasWild, MSGBOX_NPC
	end

SootopolisCity_House3_Text_JuanHasManyFansDoYou:
    .string "你是宝可梦训练师吗？\p有很多人喜欢琉璃市的亚当，\n甚至比喜欢米可利的还多！\p也有人喜欢你吗？$"

SootopolisCity_House3_Text_YouMustBePrettyStrong:
    .string "呀，那么你肯定很强。$"

SootopolisCity_House3_Text_LonesomeTryWorkingHarder:
    .string "哎呀…\n这样可有点寂寞。\p你得更努力些，\n那样才会有粉丝跟着你的。$"

SootopolisCity_House3_Text_TrainerFanClubWasWild:
    .string "追星的人们甚至都会\n从丰缘地区以外的地方赶来，\p我上次去水静市的训练师俱乐部时\n真正见识到了他们的狂热。$"

