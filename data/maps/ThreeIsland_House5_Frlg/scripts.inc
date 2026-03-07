ThreeIsland_House5_Frlg_MapScripts::
	.byte 0

ThreeIsland_House5_EventScript_LittleGirl::
	lock
	faceplayer
	goto_if_set FLAG_RESCUED_LOSTELLE, ThreeIsland_House5_EventScript_LittleGirlLostelleFound
	msgbox ThreeIsland_House5_Text_ImNotLostelle
	release
	end

ThreeIsland_House5_EventScript_LittleGirlLostelleFound::
	msgbox ThreeIsland_House5_Text_IllGoPlayWithLostelle
	release
	end

ThreeIsland_House5_Text_ImNotLostelle::
	.string "我吗？\n"
	.string "我不是小迷。\p"
	.string "我想她极有可能\n"
	.string "去了树果森林。\p"
	.string "为了烹饪午饭\n"
	.string "她经常去那采树果。$"

ThreeIsland_House5_Text_IllGoPlayWithLostelle::
	.string "我今天会和小迷\n"
	.string "一起出去玩。$"

