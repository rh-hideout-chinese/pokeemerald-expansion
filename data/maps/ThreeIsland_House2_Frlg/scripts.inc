ThreeIsland_House2_Frlg_MapScripts::
	.byte 0

ThreeIsland_House2_EventScript_Man::
	lock
	faceplayer
	famechecker FAMECHECKER_SABRINA, 1
	msgbox ThreeIsland_House2_Text_IAdmireSabrina
	release
	end

ThreeIsland_House2_EventScript_Rocker::
	msgbox ThreeIsland_House2_Text_CantMakeThisSpoonBend, MSGBOX_NPC
	end

ThreeIsland_House2_Text_CantMakeThisSpoonBend::
	.string "嗯……………\n"
	.string "呃……！\p"
	.string "……不行啊！我不可能用我的意念\n"
	.string "把这个勺子弄弯啊！\p"
	.string "也许我根本\n"
	.string "没有超能力。$"

ThreeIsland_House2_Text_IAdmireSabrina::
	.string "你认识金黄市的\n"
	.string "道馆馆主吗？\p"
	.string "她擅长使用超能力属性的宝可梦，\n"
	.string "没错吧？\p"
	.string "我喜欢她，真的很喜欢！\p"
	.string "我听说\n"
	.string "她也来过这里旅游！$"

