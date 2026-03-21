ThreeIsland_House1_Frlg_MapScripts::
	.byte 0

ThreeIsland_House1_EventScript_Lostelle::
	lock
	faceplayer
	special GetPlayerBigGuyGirlString
	msgbox ThreeIsland_House1_Text_YoureAlwaysSoCool
	release
	end

ThreeIsland_House1_EventScript_DisplayCase::
	msgbox ThreeIsland_House1_Text_RareRocksGemsDisplayed, MSGBOX_SIGN
	end

ThreeIsland_House1_Text_YoureAlwaysSoCool::
	.string "小迷：嗨，{PLAYER}！\n"
	.string "你一直都是这么帅啊！\p"
	.string "将来有机会……\n"
	.string "我也要亲手为你做便当 {PLAYER}。$"

ThreeIsland_House1_Text_RareRocksGemsDisplayed::
    .string "展览着稀有的岩石和宝石。$"

