FiveIsland_Meadow_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, FiveIsland_Meadow_OnLoad
	.byte 0

FiveIsland_Meadow_OnLoad::
	call_if_set FLAG_UNLOCKED_ROCKET_WAREHOUSE, FiveIsland_Meadow_EventScript_SetWarehouseDoorUnlocked
	end

FiveIsland_Meadow_EventScript_WarehouseDoor::
	lockall
	goto_if_set FLAG_UNLOCKED_ROCKET_WAREHOUSE, FiveIsland_Meadow_EventScript_WarehouseDoorAlreadyOpen
	goto_if_set FLAG_LEARNED_YES_NAH_CHANSEY, FiveIsland_Meadow_EventScript_OpenWarehouseDoor
	msgbox FiveIsland_Meadow_Text_EnteredPasswordAnotherNeeded
	releaseall
	end

FiveIsland_Meadow_EventScript_OpenWarehouseDoor::
	setflag FLAG_UNLOCKED_ROCKET_WAREHOUSE
	message FiveIsland_Meadow_Text_EnteredPasswordDoorOpened
	waitmessage
	delay 60
	call FiveIsland_Meadow_EventScript_SetWarehouseDoorUnlocked
	special DrawWholeMapView
	playse SE_PIN
	waitse
	releaseall
	end

FiveIsland_Meadow_EventScript_WarehouseDoorAlreadyOpen::
	msgbox FiveIsland_Meadow_Text_WarehouseDoorAlreadyOpen
	releaseall
	end

FiveIsland_Meadow_EventScript_SetWarehouseDoorUnlocked::
	setmetatile 12, 21, METATILE_SeviiIslands45_RocketWarehouseDoor_Unlocked, 1
	return

FiveIsland_Meadow_EventScript_Rocket1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_49, FiveIsland_Meadow_Text_Rocket1Intro, FiveIsland_Meadow_Text_Rocket1Defeat
	msgbox FiveIsland_Meadow_Text_Rocket1PostBattle, MSGBOX_AUTOCLOSE
	end

FiveIsland_Meadow_EventScript_Rocket2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_50, FiveIsland_Meadow_Text_Rocket2Intro, FiveIsland_Meadow_Text_Rocket2Defeat
	msgbox FiveIsland_Meadow_Text_Rocket2PostBattle, MSGBOX_AUTOCLOSE
	end

FiveIsland_Meadow_EventScript_Rocket3::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_51, FiveIsland_Meadow_Text_Rocket3Intro, FiveIsland_Meadow_Text_Rocket3Defeat
	msgbox FiveIsland_Meadow_Text_Rocket3PostBattle, MSGBOX_AUTOCLOSE
	end

@ Unused
FiveIsland_Meadow_Text_DoorNeedsTwoPasswords::
	.string "とびらを　あけるには\n"
	.string "パスワードが　2つ　いるようだ$"

FiveIsland_Meadow_Text_EnteredPasswordAnotherNeeded::
    .string "{PLAYER}输入了一段密码。\p"
    .string "“多多少少 少少多多”\p"
    .string "…………………………\p"
    .string "开门还需要\n"
    .string "另一段密码……$"

FiveIsland_Meadow_Text_EnteredPasswordDoorOpened::
    .string "{PLAYER}输入了两段密码。\p"
    .string "“多多少少 少少多多”\n"
    .string "“大大小小 小小大大”\p"
    .string "…… …… ……\p"
    .string "仓库的门打开了！$"

FiveIsland_Meadow_Text_WarehouseDoorAlreadyOpen::
    .string "仓库的门已经打开了。$"

FiveIsland_Meadow_Text_Rocket1Intro::
    .string "这个地方禁止入内！\n"
    .string "出去，出去！$"

FiveIsland_Meadow_Text_Rocket1Defeat::
    .string "这是真的吗？$"

FiveIsland_Meadow_Text_Rocket1PostBattle::
    .string "这儿什么都没有！\n"
    .string "回家吧！$"

FiveIsland_Meadow_Text_Rocket2Intro::
    .string "除了我们仓库的人\n"
    .string "再没有任何人来过这儿。\p"
    .string "谁把你带来的？$"

FiveIsland_Meadow_Text_Rocket2Defeat::
    .string "不希望发生的事出现了……$"

FiveIsland_Meadow_Text_Rocket2PostBattle::
    .string "你很想知道这仓库\n"
    .string "里面是什么？\p"
    .string "你最好别知道。\n"
    .string "这是为了你自己好。$"

FiveIsland_Meadow_Text_Rocket3Intro::
    .string "就算你能通过我这一关，\n"
    .string "你还是在浪费你的时间。$"

FiveIsland_Meadow_Text_Rocket3Defeat::
    .string "噢，我愤怒了！$"

FiveIsland_Meadow_Text_Rocket3PostBattle::
    .string "不管怎样，\n"
    .string "没有密码你就不能进去。$"

