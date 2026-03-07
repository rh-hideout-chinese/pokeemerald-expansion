OneIsland_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OneIsland_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OneIsland_OnFrame
	.byte 0

OneIsland_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_ONE_ISLAND
	end

OneIsland_OnFrame::
	map_script_2 VAR_MAP_SCENE_ONE_ISLAND_HARBOR, 2, OneIsland_EventScript_EnterOneIslandFirstTime
	.2byte 0

OneIsland_EventScript_EnterOneIslandFirstTime::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_PLAYER, OneIsland_Movement_PlayerExitHarbor
	waitmovement 0
	msgbox OneIsland_Text_BillLetsGoSeeCelio
	closemessage
	applymovement LOCALID_ONE_ISLAND_BILL, OneIsland_Movement_BillWalkToPokeCenter
	applymovement LOCALID_PLAYER, OneIsland_Movement_PlayerWalkToPokeCenter
	waitmovement 0
	opendoor 14, 5
	waitdooranim
	applymovement LOCALID_ONE_ISLAND_BILL, OneIsland_Movement_BillEnterPokeCenter
	applymovement LOCALID_PLAYER, OneIsland_Movement_PlayerEnterPokeCenter
	waitmovement 0
	closedoor 14, 5
	waitdooranim
	removeobject LOCALID_ONE_ISLAND_BILL
	setvar VAR_MAP_SCENE_ONE_ISLAND_HARBOR, 3
	warp MAP_ONE_ISLAND_POKEMON_CENTER_1F, 9, 9
	waitstate
	releaseall
	end

	.macro walk_to_pokecenter
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	.endm

OneIsland_Movement_PlayerWalkToPokeCenter::
	walk_up
	walk_to_pokecenter
	step_end

OneIsland_Movement_PlayerEnterPokeCenter::
	walk_up
	walk_up
	set_invisible
	step_end

OneIsland_Movement_PlayerExitHarbor::
	walk_up
	step_end

OneIsland_Movement_BillWalkToPokeCenter::
	walk_to_pokecenter
	walk_up
	step_end

OneIsland_Movement_BillEnterPokeCenter::
	walk_up
	set_invisible
	step_end

OneIsland_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_IS_CHAMPION, OneIsland_EventScript_OldManLinkHoenn
	goto_if_set FLAG_SEVII_DETOUR_FINISHED, OneIsland_EventScript_OldManLinkKanto
	msgbox OneIsland_Text_LuckyToHaveCelioHere
	release
	end

OneIsland_EventScript_OldManLinkKanto::
	msgbox OneIsland_Text_HavePCLinkageWithKanto
	release
	end

OneIsland_EventScript_OldManLinkHoenn::
	msgbox OneIsland_Text_HavePCLinkageWithHoenn
	release
	end

OneIsland_EventScript_BaldingMan::
	msgbox OneIsland_Text_IsntWarmClimateHereGreat, MSGBOX_NPC
	end

OneIsland_EventScript_IslandSign::
	msgbox OneIsland_Text_IslandSign, MSGBOX_SIGN
	end

OneIsland_EventScript_PokemonNetCenterSign::
	msgbox OneIsland_Text_PokemonNetCenterSign, MSGBOX_SIGN
	end

OneIsland_Text_BillLetsGoSeeCelio::
    .string "正辉：我们到喽！\n"
    .string "这里是一之岛。\p"
    .string "这附近还有好几个小岛，\n"
    .string "这个岛只是其中之一。\p"
    .string "我的朋友锦辉派船来接我。\p"
    .string "他独自管理着\n"
    .string "岛上的电脑网络联结。\p"
    .string "……为什么我现在要告诉你这些？\n"
    .string "我们先去见锦辉吧！$"

Text_WhereDoYouWantToSail::
    .string "嘿，这里这里！\n"
    .string "你打算坐船去哪儿？$"

OneIsland_Text_LuckyToHaveCelioHere::
    .string "我们来到了小岛的正中心。\p"
    .string "有一个像锦辉这样出色的\n"
    .string "年轻人真是太幸运了。\p"
    .string "我孙女作为锦辉的朋友\n"
    .string "感到很幸福。\p"
    .string "一个有名的\n"
    .string "怪兽狂？\p"
    .string "我不清楚这到底是什么意思，\n"
    .string "但似乎锦辉就是那样的人。$"

OneIsland_Text_HavePCLinkageWithKanto::
    .string "我的孙女对于新的突破\n"
    .string "有些兴奋。\p"
    .string "她说我们终于等来了\n"
    .string "电脑与关都的联动。\p"
    .string "我不确定这到底是什么意思，\n"
    .string "但锦辉就是能做到这种事的人。$"

OneIsland_Text_HavePCLinkageWithHoenn::
    .string "我的孙女对于新的突破\n"
    .string "有些兴奋。\p"
    .string "她说我们终于等来了\n"
    .string "电脑与丰缘的联动。\p"
    .string "我不清楚这到底是什么意思，\n"
    .string "但锦辉真的做到了！\p"
    .string "对我孙女来说，\n"
    .string "他一定会成为一个好丈夫！$"

OneIsland_Text_IslandSign::
    .string "一之岛\n"
    .string "朋友们聚集的小岛$"

OneIsland_Text_PokemonNetCenterSign::
    .string "扩展宝可梦的世界！\n"
    .string "宝可梦网络中心$"

@ Unused
OneIsland_Text_ReturnToCinnabar::
	.string "グレンタウンに　もどりますか？$"

OneIsland_Text_IsntWarmClimateHereGreat::
    .string "嗨，你是这里来观光的吗？\n"
    .string "这里气候温和，真是个好地方啊。$"

