ThreeIsland_BerryForest_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ThreeIsland_BerryForest_OnTransition
	.byte 0

ThreeIsland_BerryForest_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_THREE_ISLAND_BERRY_FOREST
	setescapewarp MAP_THREE_ISLAND_BOND_BRIDGE, 12, 6
	end

ThreeIsland_BerryForest_EventScript_Lostelle::
	lock
	faceplayer
	msgbox ThreeIsland_BerryForest_Text_HelpScaryPokemon
	playse SE_PIN
	applymovement LOCALID_BERRY_FOREST_LOSTELLE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_BERRY_FOREST_LOSTELLE, ThreeIsland_BerryForest_Movement_LostelleLookAround
	waitmovement 0
	msgbox ThreeIsland_BerryForest_Text_HereItComesAgain
	waitse
	playmoncry SPECIES_HYPNO, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_HYPNO, 30
	dowildbattle
	applymovement LOCALID_BERRY_FOREST_LOSTELLE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox ThreeIsland_BerryForest_Text_ThankYouHaveThis
	giveitem ITEM_IAPAPA_BERRY
	call_if_eq VAR_RESULT, FALSE, ThreeIsland_BerryForest_EventScript_NoRoomForBerry
	special GetPlayerBigGuyGirlString
	msgbox ThreeIsland_BerryForest_Text_LetsGoHome
	closemessage
	setflag FLAG_RESCUED_LOSTELLE
	setflag FLAG_HIDE_LOSTELLE_IN_BERRY_FOREST
	setvar VAR_MAP_SCENE_TWO_ISLAND_JOYFUL_GAME_CORNER, 2
	clearflag FLAG_HIDE_TWO_ISLAND_GAME_CORNER_LOSTELLE
	warp MAP_TWO_ISLAND_JOYFUL_GAME_CORNER, 6, 6
	waitstate
	release
	end

ThreeIsland_BerryForest_EventScript_NoRoomForBerry::
	msgbox ThreeIsland_BerryForest_Text_BerryPouchIsFull
	return

ThreeIsland_BerryForest_Movement_LostelleLookAround::
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_right
	delay_8
	walk_in_place_faster_left
	step_end

ThreeIsland_BerryForest_EventScript_WelcomeSign::
	msgbox ThreeIsland_BerryForest_Text_WelcomeToBerryForest, MSGBOX_SIGN
	end

ThreeIsland_BerryForest_EventScript_BewareSign::
	msgbox ThreeIsland_BerryForest_Text_BewareWildBerryLovingMons, MSGBOX_SIGN
	end

ThreeIsland_BerryForest_Text_HelpScaryPokemon::
    .string "小迷：呜……呜呜……\n"
    .string "哦！请救救我！\p"
    .string "就在刚才，\n"
    .string "一只可怕的宝可梦出现了。\p"
    .string "它一直吓唬人。\n"
    .string "小迷被它吓坏了了。\p"
    .string "小迷害怕得动不了了！\n"
    .string "但是我想回家……$"

ThreeIsland_BerryForest_Text_HereItComesAgain::
    .string "哦！它又来了！\n"
    .string "不！走开！太吓人了！\p"
    .string "哇！\n"
    .string "我要爸爸！$"

ThreeIsland_BerryForest_Text_ThankYouHaveThis::
    .string "哦！刚才真是太吓人了！\n"
    .string "谢谢！\p"
    .string "小迷捡了一些\n"
    .string "树果。\p"
    .string "这些送给你！$"

ThreeIsland_BerryForest_Text_LetsGoHome::
    .string "你叫什么名字？\p"
    .string "小迷很害怕，所以能让你\n"
    .string "送我回我爸爸的屋里吗？\p"
    .string "好！\n"
    .string "我们一起回家吧！$"

ThreeIsland_BerryForest_Text_BerryPouchIsFull::
    .string "你的树果袋满了。\n"
    .string "看来你不想要这个了吧。$"

ThreeIsland_BerryForest_Text_WelcomeToBerryForest::
    .string "欢迎来到树果森林\p"
    .string "请友好地和其他人与\n"
    .string "宝可梦分享树果。$"

ThreeIsland_BerryForest_Text_BewareWildBerryLovingMons::
    .string "当心野生的，喜爱树果\n"
    .string "的宝可梦！$"

