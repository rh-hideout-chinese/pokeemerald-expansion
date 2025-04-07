RustboroCity_CuttersHouse_MapScripts::
	.byte 0

RustboroCity_CuttersHouse_EventScript_Cutter::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_CUT, RustboroCity_CuttersHouse_EventScript_ExplainCut
	msgbox RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse, MSGBOX_DEFAULT
	giveitem ITEM_HM_CUT
	setflag FLAG_RECEIVED_HM_CUT
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_ExplainCut::
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_Lass::
	msgbox RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees, MSGBOX_NPC
	end

RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse:
    .string "那坚定的表情…\n敏捷的行动…\l还有训练有素的宝可梦…\p你肯定是个经验丰富的训练师！\p不，别急，不用说，\n我知道你想要什么。\p我想你会善加利用\n这个秘传学习器的。\p不用谦虚，\n这是你的了！$"

RustboroCity_CuttersHouse_Text_ExplainCut:
    .string "那个秘传学习器\n里面是居合斩。\p秘传学习器技是可以让宝可梦\n在战斗外也能使用的招式。\p如果训练师得到了\n岩石徽章，那么学会居合斩的\l宝可梦就能砍倒小树。\p而且，和招式学习器不同的是，\n秘传学习器可以使用\n很多次。$"

RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees:
    .string "卡那兹市扩建的时候，\n爸爸也去帮忙了。\p他让宝可梦用居合斩\n砍倒了树林。$"

