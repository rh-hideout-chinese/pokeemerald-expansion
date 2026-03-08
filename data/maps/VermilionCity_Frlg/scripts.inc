VermilionCity_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VermilionCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VermilionCity_OnFrame
	.byte 0

VermilionCity_OnFrame::
	map_script_2 VAR_MAP_SCENE_VERMILION_CITY, 2, VermilionCity_EventScript_ExitSSAnne
	.2byte 0

VermilionCity_EventScript_ExitSSAnne::
	lockall
	applymovement LOCALID_PLAYER, VermilionCity_Movement_ExitSSAnne
	waitmovement 0
	setvar VAR_MAP_SCENE_VERMILION_CITY, 3
	releaseall
	end

VermilionCity_Movement_ExitSSAnne::
	walk_up
	walk_up
	step_end

VermilionCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_VERMILION_CITY
	call_if_set FLAG_TALKED_TO_OAKS_AIDE_IN_VERMILION, VermilionCity_EventScript_HideOaksAide
	end

VermilionCity_EventScript_HideOaksAide::
	setflag FLAG_HIDE_VERMILION_CITY_OAKS_AIDE
	return

VermilionCity_EventScript_Woman::
	msgbox VermilionCity_Text_GrimerMultipliesInSludge, MSGBOX_NPC
	end

VermilionCity_EventScript_OldMan1::
	lock
	faceplayer
	goto_if_eq VAR_MAP_SCENE_VERMILION_CITY, 3, VermilionCity_EventScript_OldMan1SSAnneLeft
	msgbox VermilionCity_Text_DidYouSeeSSAnneInHarbor
	release
	end

VermilionCity_EventScript_OldMan1SSAnneLeft::
	msgbox VermilionCity_Text_SSAnneHasDepartedForYear
	release
	end

VermilionCity_EventScript_FerrySailor::
	lock
	faceplayer
	goto_if_eq VAR_MAP_SCENE_VERMILION_CITY, 3, VermilionCity_EventScript_CheckSeagallopPresent
	msgbox VermilionCity_Text_WelcomeToTheSSAnne
	release
	end

VermilionCity_EventScript_CheckHasMysticTicket::
	goto_if_unset FLAG_ENABLE_SHIP_NAVEL_ROCK, EventScript_SetResultFalse
	checkitem ITEM_MYSTIC_TICKET
	goto_if_eq VAR_RESULT, FALSE, EventScript_SetResultFalse
	goto EventScript_SetResultTrue
	end

VermilionCity_EventScript_CheckHasAuroraTicket::
	goto_if_unset FLAG_ENABLE_SHIP_BIRTH_ISLAND, EventScript_SetResultFalse
	checkitem ITEM_AURORA_TICKET
	goto_if_eq VAR_RESULT, FALSE, EventScript_SetResultFalse
	goto EventScript_SetResultTrue
	end

VermilionCity_EventScript_CheckSeagallopPresent::
	setvar VAR_0x8004, SEAGALLOP_VERMILION_CITY
	goto_if_ge VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 5, VermilionCity_EventScript_ChooseSeagallopDestRainbowPass
	goto_if_ge VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 1, VermilionCity_EventScript_ChooseSeagallopDestTriPass
	msgbox VermilionCity_Text_TheShipSetSail
	release
	end

VermilionCity_EventScript_ChooseSeagallopDestRainbowPass::
	call VermilionCity_EventScript_CheckHasMysticTicket
	goto_if_eq VAR_RESULT, TRUE, VermilionCity_EventScript_HasMysticTicket
	call VermilionCity_EventScript_CheckHasAuroraTicket
	goto_if_eq VAR_RESULT, TRUE, VermilionCity_EventScript_HasAuroraTicket
	setvar VAR_0x8004, SEAGALLOP_VERMILION_CITY
	message VermilionCity_Text_BoardSeagallopRainbowPass
	waitmessage
	goto EventScript_SeviiDestinationsPage1
	end

VermilionCity_EventScript_HasMysticTicket::
	call VermilionCity_EventScript_CheckHasAuroraTicket
	goto_if_eq VAR_RESULT, TRUE, VermilionCity_EventScript_HasMysticAndAuroraTickets
	call_if_unset FLAG_SHOWN_MYSTIC_TICKET, VermilionCity_EventScript_ShowMysticTicket
	message VermilionCity_Text_BoardSeagallopFerry
	waitmessage
	multichoice 17, 6, MULTI_SEVII_NAVEL, FALSE
	switch VAR_RESULT
	case 0, EventScript_SeviiDestinationsPage1
	case 1, EventScript_SailToNavelRock
	case 2, EventScript_CancelSail
	case 127, EventScript_CancelSail
	end

VermilionCity_EventScript_ShowMysticTicket::
	setflag FLAG_SHOWN_MYSTIC_TICKET
	msgbox VermilionCity_Text_OhMysticTicketTakeYouToNavelRock
	return

VermilionCity_EventScript_HasAuroraTicket::
	call_if_unset FLAG_SHOWN_AURORA_TICKET, VermilionCity_EventScript_ShowAuroraTicket
	message VermilionCity_Text_BoardSeagallopFerry
	waitmessage
	multichoice 13, 6, MULTI_SEVII_BIRTH, FALSE
	switch VAR_RESULT
	case 0, EventScript_SeviiDestinationsPage1
	case 1, EventScript_SailToBirthIsland
	case 2, EventScript_CancelSail
	case 127, EventScript_CancelSail
	end

VermilionCity_EventScript_ShowAuroraTicket::
	setflag FLAG_SHOWN_AURORA_TICKET
	msgbox VermilionCity_Text_OhAuroraTicketTakeYouToBirthIsland
	return

VermilionCity_EventScript_HasMysticAndAuroraTickets::
	call_if_unset FLAG_SHOWN_MYSTIC_TICKET, VermilionCity_EventScript_ShowMysticTicket
	call_if_unset FLAG_SHOWN_AURORA_TICKET, VermilionCity_EventScript_ShowAuroraTicket
	message VermilionCity_Text_BoardSeagallopFerry
	waitmessage
	multichoice 13, 5, MULTI_SEVII_NAVEL_BIRTH, FALSE
	switch VAR_RESULT
	case 0, EventScript_SeviiDestinationsPage1
	case 1, EventScript_SailToNavelRock
	case 2, EventScript_SailToBirthIsland
	case 3, EventScript_CancelSail
	case 127, EventScript_CancelSail
	end

EventScript_SailToNavelRock::
	msgbox VermilionCity_Text_Seagallop10Departing
	setvar VAR_0x8004, SEAGALLOP_VERMILION_CITY
	setvar VAR_0x8006, SEAGALLOP_NAVEL_ROCK
	goto EventScript_SetSail
	end

EventScript_SailToBirthIsland::
	msgbox VermilionCity_Text_Seagallop12Departing
	setvar VAR_0x8004, SEAGALLOP_VERMILION_CITY
	setvar VAR_0x8006, SEAGALLOP_BIRTH_ISLAND
	goto EventScript_SetSail
	end

VermilionCity_EventScript_ChooseSeagallopDestTriPass::
	message VermilionCity_Text_BoardSeagallopTriPass
	waitmessage
	setvar VAR_0x8004, SEAGALLOP_VERMILION_CITY
	multichoice 19, 5, MULTI_SEAGALLOP_123, FALSE
	switch VAR_RESULT
	case 0, EventScript_SailToOneIsland2
	case 1, EventScript_SailToTwoIsland2
	case 2, EventScript_SailToThreeIsland2
	case 3, EventScript_CancelSail
	case 127, EventScript_CancelSail
	end

@ Unreachable
Vermilion_EventScript_Unused::
	release
	end

VermilionCity_EventScript_CheckTicketLeft::
	lockall
	goto VermilionCity_EventScript_CheckTicket
	end

VermilionCity_EventScript_CheckTicketRight::
	lockall
	goto VermilionCity_EventScript_CheckTicket
	end

VermilionCity_EventScript_ExitedTicketCheck::
	lockall
	setvar VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 0
	releaseall
	end

VermilionCity_EventScript_CheckTicket::
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_VERMILION_FERRY_SAILOR, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	goto_if_eq VAR_MAP_SCENE_VERMILION_CITY, 3, VermilionCity_EventScript_CheckSeagallopPresentTrigger
	msgbox VermilionCity_Text_DoYouHaveATicket
	goto_if_unset FLAG_GOT_SS_TICKET, VermilionCity_EventScript_DontHaveSSTicket
	msgbox VermilionCity_Text_FlashedSSTicket
	setvar VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 1
	releaseall
	end

VermilionCity_EventScript_DontHaveSSTicket::
	msgbox VermilionCity_Text_DontHaveNeededSSTicket
	closemessage
	goto VermilionCity_EventScript_WalkUpPier
	end

VermilionCity_EventScript_CheckSeagallopPresentTrigger::
	setvar VAR_0x8004, SEAGALLOP_VERMILION_CITY
	goto_if_ge VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 5, VermilionCity_EventScript_ChooseSeagallopDestRainbowPass
	goto_if_ge VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 1, VermilionCity_EventScript_ChooseSeagallopDestTriPass
	msgbox VermilionCity_Text_TheShipSetSail
	closemessage
	goto VermilionCity_EventScript_WalkUpPier
	end

VermilionCity_EventScript_Sailor::
	msgbox VermilionCity_Text_SSAnneVisitsOnceAYear, MSGBOX_NPC
	end

VermilionCity_EventScript_OaksAide::
	lock
	faceplayer
	setflag FLAG_TALKED_TO_OAKS_AIDE_IN_VERMILION
	msgbox VermilionCity_Text_Route2AideHasPackageForYou
	release
	end

VermilionCity_EventScript_OldMan2::
	msgbox VermilionCity_Text_BuildingOnThisLand, MSGBOX_NPC
	end

VermilionCity_EventScript_Machop::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHOP, CRY_MODE_NORMAL
	msgbox VermilionCity_Text_Machop
	waitmoncry
	msgbox VermilionCity_Text_MachopStompingLandFlat
	release
	end

VermilionCity_EventScript_CitySign::
	msgbox VermilionCity_Text_CitySign, MSGBOX_SIGN
	end

VermilionCity_EventScript_SnorlaxNotice::
	msgbox VermilionCity_Text_SnorlaxBlockingRoute12, MSGBOX_SIGN
	end

VermilionCity_EventScript_PokemonFanClubSign::
	msgbox VermilionCity_Text_PokemonFanClubSign, MSGBOX_SIGN
	end

VermilionCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_LTSURGE, 0
	msgbox VermilionCity_Text_GymSign
	releaseall
	end

VermilionCity_EventScript_HarborSign::
	msgbox VermilionCity_Text_VermilionHarbor, MSGBOX_SIGN
	end

VermilionCity_Text_GrimerMultipliesInSludge::
    .string "我们十分注重对环境的保护。\p"
    .string "我们曾经听说臭泥\n"
    .string "会在有毒的污泥里繁殖。$"

VermilionCity_Text_DidYouSeeSSAnneInHarbor::
    .string "你看到圣特安努号\n"
    .string "停泊在港口了吗？$"

VermilionCity_Text_SSAnneHasDepartedForYear::
    .string "这样啊，圣特安努号离港了？\p"
    .string "她明年会回到\n"
    .string "枯叶来的。$"

VermilionCity_Text_BuildingOnThisLand::
    .string "我在这片土地上修房子。\n"
    .string "你所见的这一切都是我的。\p"
    .string "我的宝可梦\n"
    .string "在夯实这里的地块作为地基。$"

VermilionCity_Text_Machop::
    .string "腕力 呃啊！喝啊啊啊！$"

VermilionCity_Text_MachopStompingLandFlat::
    .string "腕力用脚把地面使劲地跺平。$"

VermilionCity_Text_SSAnneVisitsOnceAYear::
    .string "圣特安努号是一艘\n"
    .string "著名的游轮。\p"
    .string "每年都来枯叶一次。$"

VermilionCity_Text_CitySign::
    .string "枯叶市\n"
    .string "落日下美丽的港口$"

VermilionCity_Text_SnorlaxBlockingRoute12::
    .string "通知\p"
    .string "12号道路被一只\n"
    .string "熟睡着的宝可梦堵死了。\p"
    .string "请从岩山隧道绕道至\n"
    .string "紫苑镇。\p"
    .string "枯叶警察局$"

VermilionCity_Text_PokemonFanClubSign::
    .string "宝可梦同好会\n"
    .string "欢迎所有的宝可梦爱好者！$"

VermilionCity_Text_GymSign::
    .string "枯叶市宝可梦道馆\n"
    .string "馆主：马志士\l"
    .string "闪电般的美国人！$"

VermilionCity_Text_VermilionHarbor::
    .string "枯叶海港$"

VermilionCity_Text_WelcomeToTheSSAnne::
    .string "欢迎来到圣特安努号！$"

VermilionCity_Text_DoYouHaveATicket::
    .string "欢迎来到圣特安努号！\p"
    .string "抱歉，您是否带了票？$"

VermilionCity_Text_FlashedSSTicket::
    .string "{FONT_NORMAL}{PLAYER}出示了船票！\p"
    .string "{FONT_MALE}很好！\n"
    .string "欢迎来到圣特安努号！$"

VermilionCity_Text_DontHaveNeededSSTicket::
    .string "{FONT_NORMAL}{PLAYER}没有带着要的\n"
    .string "船票。\p"
    .string "{FONT_MALE}对不起！\p"
    .string "想登船必须得有票。$"

VermilionCity_Text_TheShipSetSail::
    .string "船顺利地航行着。$"

VermilionCity_Text_BoardSeagallopTriPass::
    .string "啊，你带着三岛通行证。\p"
    .string "想坐海烈焰马号\n"
    .string "来此海上旅行吗？$"

VermilionCity_Text_Seagallop7Departing::
    .string "好，万事俱备了。\p"
    .string "海烈焰马号将以7被的高速\n"
    .string "马上起航。$"

VermilionCity_Text_BoardSeagallopRainbowPass::
    .string "啊，你带着彩虹通行证。\p"
    .string "想坐海烈焰马号\n"
    .string "来次海上旅行吗？$"

VermilionCity_Text_OhMysticTicketTakeYouToNavelRock::
    .string "哦！是神秘的船票啊！\n"
    .string "这可是难得的珍稀之物。\p"
    .string "您要是想前往脐之岩，\n"
    .string "我们随时恭候大驾。$"

VermilionCity_Text_OhAuroraTicketTakeYouToBirthIsland::
    .string "哦！是诞生之岛船票啊！\n"
    .string "这可是难得的珍稀之物。\p"
    .string "您要是想前往诞生之岛，\n"
    .string "我们随时恭候大驾。$"

VermilionCity_Text_BoardSeagallopFerry::
    .string "你想乘坐海烈焰马号游艇吗？$"

VermilionCity_Text_Seagallop10Departing::
    .string "好了，您登艇的相关手续已经\n"
    .string "办理完毕。\p"
    .string "海烈焰马号将以10倍的高速\n"
    .string "马上起航。$"

VermilionCity_Text_Seagallop12Departing::
    .string "好了，您登艇的相关手续已经\n"
    .string "办理完毕。\p"
    .string "海烈焰马号将以12倍的高速\n"
    .string "开始起航。$"

VermilionCity_Text_Route2AideHasPackageForYou::
    .string "嘿，你好啊，{PLAYER}！\n"
    .string "最近还好么？\p"
    .string "我是大木博士的一名助手。\p"
    .string "你碰到过其他助手吗？\p"
    .string "{PLAYER}，有人从博士那里带了一件包裹。\p"
    .string "他说会他在2号道路附近等你。\p"
    .string "如果你要去2号道路那边的话，\n"
    .string "请与他联系一下。$"

