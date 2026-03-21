SixIsland_RuinValley_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SixIsland_RuinValley_OnLoad
	.byte 0

SixIsland_RuinValley_OnLoad::
	call_if_set FLAG_USED_CUT_ON_RUIN_VALLEY_BRAILLE, SixIsland_RuinValley_EventScript_OpenDottedHoleDoor
	end

SixIsland_RuinValley_EventScript_OpenDottedHoleDoor::
	setmetatile 24, 24, METATILE_SeviiIslands67_DottedHoleDoor_Open, 0
	return

SixIsland_RuinValley_EventScript_Scientist::
	lock
	msgbox SixIsland_RuinValley_Text_CantFigureOutHowToGetInside
	applymovement LOCALID_RUIN_VALLEY_SCIENTIST, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SixIsland_RuinValley_Text_IFoundThisPlace
	applymovement LOCALID_RUIN_VALLEY_SCIENTIST, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SixIsland_RuinValley_EventScript_DottedHoleDoor::
	lockall
	goto_if_set FLAG_USED_CUT_ON_RUIN_VALLEY_BRAILLE, SixIsland_RuinValley_EventScript_DottedHoleDoorOpen
	msgbox SixIsland_RuinValley_Text_CheckDoorMoreThoroughly, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SixIsland_RuinValley_EventScript_IgnoreDottedHoleDoor
	msgbox SixIsland_RuinValley_Text_SeveralDotsOnTheDoor
	braillemsgbox Braille_Text_Cut
	releaseall
	end

SixIsland_RuinValley_EventScript_DottedHoleDoorOpen::
	msgbox SixIsland_RuinValley_Text_DoorIsOpen
	releaseall
	end

SixIsland_RuinValley_EventScript_IgnoreDottedHoleDoor::
	msgbox SixIsland_RuinValley_Text_LeftDoorAlone
	releaseall
	end

SixIsland_RuinValley_Text_CantFigureOutHowToGetInside::
    .string "我弄不明白我是怎样\n"
    .string "进来的。$"

SixIsland_RuinValley_Text_IFoundThisPlace::
    .string "告诉你吧，是我找到了这个地方。\p"
    .string "别一脸嫉妒地看着我，好吗？$"

SixIsland_RuinValley_Text_CheckDoorMoreThoroughly::
    .string "这扇门动都没动一下。\n"
    .string "再认真检查一遍吧？$"

SixIsland_RuinValley_Text_LeftDoorAlone::
    .string "{PLAYER}不管这扇门了。$"

SixIsland_RuinValley_Text_SeveralDotsOnTheDoor::
    .string "仔细观察，发现门上\n"
    .string "有几个代码。$"

SixIsland_RuinValley_Text_DoorIsOpen::
    .string "门打开了。$"

SixIsland_RuinValley_Text_StanlyIntro::
    .string "在这个世界上显然还有\n"
    .string "很多秘密是没有解开的。$"

SixIsland_RuinValley_Text_StanlyDefeat::
    .string "嗯……$"

SixIsland_RuinValley_Text_StanlyPostBattle::
    .string "我建议你在某一天\n"
    .string "也来思考一下\l"
    .string "这个世界的未解之谜。$"

SixIsland_RuinValley_Text_FosterIntro::
    .string "我很好奇，是什么\n"
    .string "驱使你来这儿的？$"

SixIsland_RuinValley_Text_FosterDefeat::
    .string "离上次战斗已经过去很久了，\n"
    .string "我的直觉早没了。$"

SixIsland_RuinValley_Text_FosterPostBattle::
    .string "在七岛有几个遗址\p"
    .string "大部分都可以追溯至\n"
    .string "很久很久以前了。$"

SixIsland_RuinValley_Text_LarryIntro::
    .string "据说在这座岛上\n"
    .string "有一些神秘的石头。\p"
    .string "我怀疑它们与\n"
    .string "这些遗址有关$"

SixIsland_RuinValley_Text_LarryDefeat::
    .string "噢，太有趣了。$"

SixIsland_RuinValley_Text_LarryPostBattle::
    .string "那些遗址……\p"
    .string "我想我没有这个运气\n"
    .string "找到方法进去。$"

SixIsland_RuinValley_Text_DarylIntro::
    .string "和你战斗一场，太兴奋了！$"

SixIsland_RuinValley_Text_DarylDefeat::
    .string "噢，失败太容易换来\n"
    .string "心碎的感觉了！$"

SixIsland_RuinValley_Text_DarylPostBattle::
    .string "体验攀岩的乐趣！$"

SixIsland_RuinValley_Text_HectorIntro::
    .string "在这个地区\n"
    .string "我对这块陆地实在太熟悉了。$"

SixIsland_RuinValley_Text_HectorDefeat::
    .string "你不需要这么上进。\n"
    .string "我很高兴地告诉你。$"

SixIsland_RuinValley_Text_HectorPostBattle::
    .string "通往遗址的门……\n"
    .string "在外面有一些奇怪的\l"
    .string "花纹刻在上面。\p"
    .string "不过，\n"
    .string "我不知道它们代表什么。$"
