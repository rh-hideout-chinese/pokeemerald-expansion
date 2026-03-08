ThreeIsland_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ThreeIsland_OnTransition
	.byte 0

ThreeIsland_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_THREE_ISLAND
	call_if_set FLAG_RESCUED_LOSTELLE, ThreeIsland_EventScript_HideAntiBikers
	call_if_eq VAR_MAP_SCENE_THREE_ISLAND, 4, ThreeIsland_EventScript_SetAntiBikersMovementAfterBikers
	end

ThreeIsland_EventScript_HideAntiBikers::
	setflag FLAG_HIDE_THREE_ISLAND_ANTIBIKERS
	return

ThreeIsland_EventScript_SetAntiBikersMovementAfterBikers::
	setobjectmovementtype LOCALID_THREE_ISLAND_ANTIBIKER1, MOVEMENT_TYPE_LOOK_AROUND
	setobjectmovementtype LOCALID_THREE_ISLAND_ANTIBIKER2, MOVEMENT_TYPE_LOOK_AROUND
	return

ThreeIsland_EventScript_Biker::
	lock
	setvar VAR_TEMP_1, 2
	call ThreeIsland_EventScript_BikerArgumentScene
	release
	end

ThreeIsland_EventScript_AntiBiker1::
	lock
	goto_if_set FLAG_GOT_FULL_RESTORE_FROM_THREE_ISLAND_DEFENDER, ThreeIsland_EventScript_AntiBiker1GotFullRestore
	goto_if_eq VAR_MAP_SCENE_THREE_ISLAND, 4, ThreeIsland_EventScript_GiveFullRestore
	setvar VAR_TEMP_1, 0
	call ThreeIsland_EventScript_BikerArgumentScene
	release
	end

ThreeIsland_EventScript_AntiBiker1GotFullRestore::
	applymovement LOCALID_THREE_ISLAND_ANTIBIKER1, Common_Movement_FacePlayer
	waitmovement 0
	msgbox ThreeIsland_Text_YouveGotImpressiveMons
	release
	end

ThreeIsland_EventScript_GiveFullRestore::
	applymovement LOCALID_THREE_ISLAND_ANTIBIKER1, Common_Movement_FacePlayer
	waitmovement 0
	msgbox ThreeIsland_Text_ThankYouOhYourMonGotHurt
	checkitemspace ITEM_FULL_RESTORE
	goto_if_eq VAR_RESULT, FALSE, ThreeIsland_EventScript_NoRoomForFullRestore
	msgreceiveditem ThreeIsland_Text_GivenFullRestore, ITEM_FULL_RESTORE
	additem ITEM_FULL_RESTORE
	setflag FLAG_GOT_FULL_RESTORE_FROM_THREE_ISLAND_DEFENDER
	msgbox ThreeIsland_Text_YouveGotImpressiveMons
	release
	end

ThreeIsland_EventScript_NoRoomForFullRestore::
	msgbox ThreeIsland_Text_OhYourBagIsFull
	release
	end

ThreeIsland_EventScript_BikerArgumentScene::
	call_if_eq VAR_TEMP_1, 1, ThreeIsland_EventScript_PlayerFaceLeft
	call_if_eq VAR_TEMP_1, 2, ThreeIsland_EventScript_PlayerFaceLeft
	applymovement LOCALID_THREE_ISLAND_ANTIBIKER1, ThreeIsland_Movement_SpeakRight
	waitmovement 0
	msgbox ThreeIsland_Text_GoBackToKanto
	call_if_eq VAR_TEMP_1, 0, ThreeIsland_EventScript_PlayerFaceRight
	call_if_eq VAR_TEMP_1, 1, ThreeIsland_EventScript_PlayerFaceRight
	call_if_eq VAR_TEMP_1, 2, ThreeIsland_EventScript_PlayerFaceBiker
	applymovement LOCALID_THREE_ISLAND_BIKER1, ThreeIsland_Movement_SpeakLeft
	waitmovement 0
	msgbox ThreeIsland_Text_BossIsOnHisWay
	call_if_eq VAR_TEMP_1, 0, ThreeIsland_EventScript_PlayerFaceUp
	call_if_eq VAR_TEMP_1, 1, ThreeIsland_EventScript_PlayerFaceUp
	call_if_eq VAR_TEMP_1, 2, ThreeIsland_EventScript_PlayerFaceAntiBiker
	applymovement LOCALID_THREE_ISLAND_ANTIBIKER2, ThreeIsland_Movement_SpeakRight
	waitmovement 0
	msgbox ThreeIsland_Text_GetOffIslandNow
	call_if_eq VAR_TEMP_1, 0, ThreeIsland_EventScript_PlayerFaceRight
	call_if_eq VAR_TEMP_1, 1, ThreeIsland_EventScript_PlayerFaceRight
	call_if_eq VAR_TEMP_1, 2, ThreeIsland_EventScript_PlayerFaceBiker
	applymovement LOCALID_THREE_ISLAND_BIKER3, ThreeIsland_Movement_SpeakLeft
	waitmovement 0
	msgbox ThreeIsland_Text_WhosGonnaMakeMe
	return

ThreeIsland_EventScript_PlayerFaceUp::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

@ Unused
ThreeIsland_EventScript_PlayerFaceDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

ThreeIsland_EventScript_PlayerFaceLeft::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

ThreeIsland_EventScript_PlayerFaceRight::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

ThreeIsland_EventScript_PlayerFaceBiker::
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ge VAR_0x8004, 9, ThreeIsland_EventScript_PlayerFaceUp
	goto ThreeIsland_EventScript_PlayerFaceRight
	end

ThreeIsland_EventScript_PlayerFaceAntiBiker::
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ge VAR_0x8004, 9, ThreeIsland_EventScript_PlayerFaceLeft
	goto ThreeIsland_EventScript_PlayerFaceUp
	end

ThreeIsland_EventScript_AntiBiker2::
	lock
	goto_if_eq VAR_MAP_SCENE_THREE_ISLAND, 4, ThreeIsland_EventScript_AntiBiker2BikersGone
	setvar VAR_TEMP_1, 1
	call ThreeIsland_EventScript_BikerArgumentScene
	release
	end

ThreeIsland_EventScript_AntiBiker2BikersGone::
	applymovement LOCALID_THREE_ISLAND_ANTIBIKER2, Common_Movement_FacePlayer
	waitmovement 0
	msgbox ThreeIsland_Text_LostelleWentOffTowardsBondBridge
	release
	end

ThreeIsland_EventScript_BikerBossIntroTrigger::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_THREE_ISLAND_ANTIBIKER1, ThreeIsland_Movement_SpeakRight
	waitmovement 0
	msgbox ThreeIsland_Text_AreYouBossGoBackToKanto
	applymovement LOCALID_PAXTON, ThreeIsland_Movement_SpeakLeft
	waitmovement 0
	msgbox ThreeIsland_Text_JustGotHerePal
	applymovement LOCALID_THREE_ISLAND_ANTIBIKER1, ThreeIsland_Movement_SpeakRight
	waitmovement 0
	msgbox ThreeIsland_Text_FollowersRaisingHavoc
	applymovement LOCALID_PAXTON, ThreeIsland_Movement_SpeakLeft
	waitmovement 0
	msgbox ThreeIsland_Text_OughtToBeThankingUs
	applymovement LOCALID_THREE_ISLAND_ANTIBIKER1, ThreeIsland_Movement_SpeakRight
	waitmovement 0
	msgbox ThreeIsland_Text_YouCowardsToughInPack
	setvar VAR_MAP_SCENE_THREE_ISLAND, 3
	releaseall
	end

ThreeIsland_Movement_SpeakLeft::
	walk_in_place_left
	step_end

ThreeIsland_Movement_SpeakRight::
	walk_in_place_right
	step_end

ThreeIsland_EventScript_BattleBikersTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto ThreeIsland_EventScript_BattleBikersScene
	end

ThreeIsland_EventScript_BattleBikersTriggerMidLeft::
	lockall
	setvar VAR_TEMP_1, 1
	goto ThreeIsland_EventScript_BattleBikersScene
	end

ThreeIsland_EventScript_BattleBikersTriggerMid::
	lockall
	setvar VAR_TEMP_1, 2
	goto ThreeIsland_EventScript_BattleBikersScene
	end

ThreeIsland_EventScript_BattleBikersTriggerMidRight::
	lockall
	setvar VAR_TEMP_1, 3
	goto ThreeIsland_EventScript_BattleBikersScene
	end

ThreeIsland_EventScript_BattleBikersTriggerRight::
	lockall
	setvar VAR_TEMP_1, 4
	goto ThreeIsland_EventScript_BattleBikersScene
	end

ThreeIsland_EventScript_BattleBikersScene::
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_THREE_ISLAND_BIKER1, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_THREE_ISLAND_BIKER1, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_THREE_ISLAND_BIKER1, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_THREE_ISLAND_BIKER1, ThreeIsland_Movement_BikerApproach
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_BOY, 0
	msgbox ThreeIsland_Text_WannaMakeSomethingOfYourStaring, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ThreeIsland_EventScript_LeaveBikersAlone
	msgbox ThreeIsland_Text_Biker1Intro
	setvar VAR_LAST_TALKED, LOCALID_THREE_ISLAND_BIKER1
	trainerbattle_no_intro TRAINER_BIKER_GOON, ThreeIsland_Text_Biker1Defeat
	applymovement LOCALID_THREE_ISLAND_BIKER1, ThreeIsland_Movement_BikerSpeak
	waitmovement 0
	msgbox ThreeIsland_Text_Biker1PostBattle
	closemessage
	applymovement LOCALID_THREE_ISLAND_BIKER2, ThreeIsland_Movement_BikerApproach
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_BOY, 0
	msgbox ThreeIsland_Text_Biker2Intro
	setvar VAR_LAST_TALKED, LOCALID_THREE_ISLAND_BIKER2
	trainerbattle_no_intro TRAINER_BIKER_GOON_2, ThreeIsland_Text_Biker2Defeat
	applymovement LOCALID_THREE_ISLAND_BIKER2, ThreeIsland_Movement_BikerSpeak
	waitmovement 0
	msgbox ThreeIsland_Text_Biker2PostBattle
	closemessage
	applymovement LOCALID_THREE_ISLAND_BIKER3, ThreeIsland_Movement_BikerApproach
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_BOY, 0
	msgbox ThreeIsland_Text_Biker3Intro
	setvar VAR_LAST_TALKED, LOCALID_THREE_ISLAND_BIKER3
	trainerbattle_no_intro TRAINER_BIKER_GOON_3, ThreeIsland_Text_Biker3Defeat
	applymovement LOCALID_THREE_ISLAND_BIKER3, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_THREE_ISLAND_BIKER4, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_THREE_ISLAND_BIKER5, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox ThreeIsland_Text_Biker3PostBattle
	closemessage
	delay 45
	call_if_eq VAR_TEMP_1, 0, ThreeIsland_EventScript_PaxtonApproachLeft
	call_if_eq VAR_TEMP_1, 1, ThreeIsland_EventScript_PaxtonApproachMidLeft
	call_if_eq VAR_TEMP_1, 2, ThreeIsland_EventScript_PaxtonApproachMid
	call_if_eq VAR_TEMP_1, 3, ThreeIsland_EventScript_PaxtonApproachMidRight
	call_if_eq VAR_TEMP_1, 4, ThreeIsland_EventScript_PaxtonApproachRight
	playbgm MUS_RG_ENCOUNTER_BOY, 0
	msgbox ThreeIsland_Text_PaxtonIntro
	setvar VAR_LAST_TALKED, LOCALID_PAXTON
	trainerbattle_no_intro TRAINER_CUE_BALL_PAXTON, ThreeIsland_Text_PaxtonDefeat
	msgbox ThreeIsland_Text_PaxtonPostBattle
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_PAXTON
	removeobject LOCALID_THREE_ISLAND_BIKER1
	removeobject LOCALID_THREE_ISLAND_BIKER2
	removeobject LOCALID_THREE_ISLAND_BIKER3
	removeobject LOCALID_THREE_ISLAND_BIKER4
	removeobject LOCALID_THREE_ISLAND_BIKER5
	removeobject LOCALID_THREE_ISLAND_BIKER6
	fadescreenswapbuffers FADE_FROM_BLACK
	setvar VAR_MAP_SCENE_THREE_ISLAND, 4
	releaseall
	end

ThreeIsland_EventScript_PaxtonApproachLeft::
	applymovement LOCALID_THREE_ISLAND_BIKER3, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PAXTON, ThreeIsland_Movement_PaxtonApproachLeft
	waitmovement 0
	return

ThreeIsland_EventScript_PaxtonApproachMidLeft::
	applymovement LOCALID_THREE_ISLAND_BIKER3, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PAXTON, ThreeIsland_Movement_PaxtonApproachMidLeft
	waitmovement 0
	return

ThreeIsland_EventScript_PaxtonApproachMid::
	applymovement LOCALID_THREE_ISLAND_BIKER3, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PAXTON, ThreeIsland_Movement_PaxtonApproachMid
	applymovement LOCALID_PLAYER, ThreeIsland_Movement_PlayerFacePaxton
	waitmovement 0
	return

ThreeIsland_EventScript_PaxtonApproachMidRight::
	applymovement LOCALID_THREE_ISLAND_BIKER3, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PLAYER, ThreeIsland_Movement_PlayerFacePaxton
	applymovement LOCALID_PAXTON, ThreeIsland_Movement_PaxtonApproachMidRight
	waitmovement 0
	return

ThreeIsland_EventScript_PaxtonApproachRight::
	applymovement LOCALID_THREE_ISLAND_BIKER3, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PLAYER, ThreeIsland_Movement_PlayerFacePaxton
	applymovement LOCALID_PAXTON, ThreeIsland_Movement_PaxtonApproachRight
	waitmovement 0
	return

ThreeIsland_EventScript_LeaveBikersAlone::
	msgbox ThreeIsland_Text_ThatsSmart
	closemessage
	applymovement LOCALID_PLAYER, ThreeIsland_Movement_PlayerLeaveBikers
	waitmovement 0
	applymovement LOCALID_THREE_ISLAND_BIKER1, ThreeIsland_Movement_Biker1ReturnToPack
	waitmovement 0
	fadedefaultbgm
	releaseall
	end

ThreeIsland_Movement_PlayerLeaveBikers::
	walk_down
	step_end

ThreeIsland_Movement_BikerApproach::
	walk_down
	step_end

ThreeIsland_Movement_Biker1ReturnToPack::
	walk_up
	walk_in_place_faster_left
	step_end

ThreeIsland_Movement_BikerSpeak::
	walk_in_place_down
	step_end

ThreeIsland_Movement_PaxtonApproachLeft::
	walk_down
	walk_left
	walk_in_place_faster_down
	step_end

ThreeIsland_Movement_PaxtonApproachMidLeft::
	walk_down
	step_end

ThreeIsland_Movement_PaxtonApproachMid::
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

ThreeIsland_Movement_PlayerFacePaxton::
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

ThreeIsland_Movement_PaxtonApproachMidRight::
	walk_down
	walk_down
	walk_right
	walk_in_place_faster_right
	step_end

ThreeIsland_Movement_PaxtonApproachRight::
	walk_down
	walk_down
	walk_right
	walk_right
	walk_in_place_faster_right
	step_end

ThreeIsland_EventScript_Woman::
	msgbox ThreeIsland_Text_WouldntWantToSeeBikersHereAgain, MSGBOX_NPC
	end

ThreeIsland_EventScript_LittleBoy::
	msgbox ThreeIsland_Text_WhenDodouEvolvesGoingToPlayGame, MSGBOX_NPC
	end

ThreeIsland_EventScript_Doduo::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DODUO, CRY_MODE_NORMAL
	msgbox ThreeIsland_Text_Doduo
	waitmoncry
	release
	end

ThreeIsland_EventScript_IslandSign::
	msgbox ThreeIsland_Text_IslandSign, MSGBOX_SIGN
	end

ThreeIsland_EventScript_Biker6::
	msgbox ThreeIsland_Text_IslandBelongsToUs, MSGBOX_NPC
	end

ThreeIsland_Text_IslandSign::
    .string "三之岛\n"
    .string "大小一同的家庭之岛$"

ThreeIsland_Text_IslandBelongsToUs::
    .string "呀呼！\p"
    .string "从今天起，\n"
    .string "这个岛就是我们的了！$"

ThreeIsland_Text_GoBackToKanto::
    .string "我们不欢迎\n"
    .string "你们这些制造噪音和麻烦的家伙！\p"
    .string "滚回你们的关都去！$"

ThreeIsland_Text_BossIsOnHisWay::
    .string "喂，喂，吵死了。\n"
    .string "我们的老大正在路上。\p"
    .string "等他到了这里，\n"
    .string "我们会表演一场让你终身难忘的\l"
    .string "机车秀！$"

ThreeIsland_Text_GetOffIslandNow::
    .string "什，什么！？想都别想！\n"
    .string "给我马上滚！$"

ThreeIsland_Text_WhosGonnaMakeMe::
    .string "谁想让我滚？$"

ThreeIsland_Text_AreYouBossGoBackToKanto::
    .string "你就是老大？\n"
    .string "滚回你的关都去！$"

ThreeIsland_Text_JustGotHerePal::
    .string "啊？\p"
    .string "我刚刚才到这里，朋友。\p"
    .string "你们的态度怎么这么恶劣？\n"
    .string "实在太冷淡了！$"

ThreeIsland_Text_FollowersRaisingHavoc::
    .string "你的这群手下\n"
    .string "骑着车四处胡闹。\p"
    .string "你能想象他们给岛上的居民\n"
    .string "带来了多少麻烦吗？$"

ThreeIsland_Text_OughtToBeThankingUs::
    .string "我可一点不同意你的说法。\p"
    .string "你自己看看你这地方。\n"
    .string "你们有什么娱乐活动啊？\p"
    .string "你该感谢我们给这个\n"
    .string "沉闷的村庄带来了活力才对啊。\p"
    .string "不过，如果你硬要坚持的话，\n"
    .string "你可以试试赶我们走。$"

ThreeIsland_Text_YouCowardsToughInPack::
    .string "呃……你们这些废物……\n"
    .string "他们组队还真厉害……$"

ThreeIsland_Text_WannaMakeSomethingOfYourStaring::
    .string "你，干嘛盯着我看？\n"
    .string "你不知道这不礼貌吗？\p"
    .string "你想找我们茬儿吗？$"

ThreeIsland_Text_ThatsSmart::
    .string "聪明。\n"
    .string "别多管闲事。$"

ThreeIsland_Text_Biker1Intro::
    .string "嘿，我欣赏你的胆量。\n"
    .string "明知会败给我，还……$"

ThreeIsland_Text_Biker1Defeat::
    .string "哇……\n"
    .string "这孩子是什么来头？！$"

ThreeIsland_Text_Biker1PostBattle::
    .string "嗷，你……\n"
    .string "你敢再笑！$"

ThreeIsland_Text_Biker2Intro::
    .string "你不是关都人吗？\n"
    .string "你应该站我们这边才对！$"

ThreeIsland_Text_Biker2Defeat::
    .string "别胡闹了！$"

ThreeIsland_Text_Biker2PostBattle::
    .string "你干嘛那么拼命啊？\n"
    .string "一点都不酷！$"

ThreeIsland_Text_Biker3Intro::
    .string "我们把老大请来这里，\n"
    .string "可竟然全被你搞砸了！\p"
    .string "你让我们很不爽啊，小子！$"

ThreeIsland_Text_Biker3Defeat::
    .string "……  ……$"

ThreeIsland_Text_Biker3PostBattle::
    .string "老大，\n"
    .string "你一定要好好教训下这小子！$"

ThreeIsland_Text_PaxtonIntro::
    .string "我观察你很久了，\n"
    .string "你有些过分了哦。\p"
    .string "你和他们是什么关系？\n"
    .string "朋友还是别的什么？\p"
    .string "我猜你是准备好\n"
    .string "为了他们跟我宣战了。$"

ThreeIsland_Text_PaxtonDefeat::
    .string "好吧！\n"
    .string "如你们所愿，我们会走的！\p"
    .string "我们很高兴\n"
    .string "和这个无趣的岛说再见！$"

ThreeIsland_Text_PaxtonPostBattle::
    .string "哼！好吧，你就继续\n"
    .string "和这些乡巴佬混一起吧！$"

ThreeIsland_Text_ThankYouOhYourMonGotHurt::
    .string "谢谢！\n"
    .string "那些暴徒真是麻烦。\p"
    .string "噢，看啊，你的宝可梦因为我受伤了。$"

ThreeIsland_Text_GivenFullRestore::
    .string "{PLAYER}获得了\n"
    .string "一个全复药。$"

ThreeIsland_Text_OhYourBagIsFull::
    .string "喔？\n"
    .string "你的背包满了。$"

ThreeIsland_Text_YouveGotImpressiveMons::
    .string "你的宝可梦令人印象非常深刻。$"

ThreeIsland_Text_LostelleWentOffTowardsBondBridge::
    .string "如果有个像你这么厉害的人\n"
    .string "常住在这里可就好了。\p"
    .string "我希望你至少能多待上一会儿。\p"
    .string "……你说什么？\n"
    .string "你在找小迷？\p"
    .string "小迷不久前朝着\n"
    .string "索桥的方向去了。$"

ThreeIsland_Text_WouldntWantToSeeBikersHereAgain::
    .string "三之岛实际上\n"
    .string "是这里的岛屿中人口最多的一个。\p"
    .string "当然，可能是有点沉闷。\p"
    .string "但我不想再看到像那些飙车族一样的\n"
    .string "笨蛋到这里来了。$"

ThreeIsland_Text_WhenDodouEvolvesGoingToPlayGame::
    .string "我打算在树果森林训练我的嘟嘟。\p"
    .string "等它进化后，我打算\n"
    .string "带它去二之岛参加越野比赛。$"

ThreeIsland_Text_Doduo::
    .string "嘟嘟：唧唧！$"

