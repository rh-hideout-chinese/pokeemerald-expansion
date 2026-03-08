SilphCo_6F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_6F_OnLoad
	.byte 0

SilphCo_6F_OnLoad::
	call_if_unset FLAG_SILPH_6F_DOOR, EventScript_Close6FDoor
	end

SilphCo_6F_EventScript_WorkerM2::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_6F_EventScript_WorkerM2RocketsGone
	msgbox SilphCo_6F_Text_TargetedSilphForOurMonProducts
	release
	end

SilphCo_6F_EventScript_WorkerM2RocketsGone::
	msgbox SilphCo_6F_Text_ComeWorkForSilphWhenYoureOlder
	release
	end

SilphCo_6F_EventScript_WorkerM3::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_6F_EventScript_WorkerM3RocketsGone
	msgbox SilphCo_6F_Text_RocketsTookOverBuilding
	release
	end

SilphCo_6F_EventScript_WorkerM3RocketsGone::
	msgbox SilphCo_6F_Text_BetterGetBackToWork
	release
	end

SilphCo_6F_EventScript_WorkerM1::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_6F_EventScript_WorkerM1RocketsGone
	msgbox SilphCo_6F_Text_HelpMePlease
	release
	end

SilphCo_6F_EventScript_WorkerM1RocketsGone::
	msgbox SilphCo_6F_Text_WeGotEngaged
	release
	end

SilphCo_6F_EventScript_WorkerF1::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_6F_EventScript_WorkerF1RocketsGone
	msgbox SilphCo_6F_Text_ThatManIsSuchACoward
	release
	end

SilphCo_6F_EventScript_WorkerF1RocketsGone::
	msgbox SilphCo_6F_Text_NeedsMeToLookAfterHim
	release
	end

SilphCo_6F_EventScript_WorkerF2::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_6F_EventScript_WorkerF2RocketsGone
	msgbox SilphCo_6F_Text_RocketsTryingToConquerWorld
	release
	end

SilphCo_6F_EventScript_WorkerF2RocketsGone::
	msgbox SilphCo_6F_Text_RocketsRanAwayBecauseOfYou
	release
	end

SilphCo_6F_EventScript_FloorSign::
	msgbox SilphCo_6F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_6F_EventScript_Taylor::
	trainerbattle_single TRAINER_SCIENTIST_TAYLOR, SilphCo_6F_Text_TaylorIntro, SilphCo_6F_Text_TaylorDefeat
	msgbox SilphCo_6F_Text_TaylorPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_6F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_30, SilphCo_6F_Text_Grunt1Intro, SilphCo_6F_Text_Grunt1Defeat
	msgbox SilphCo_6F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_6F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_31, SilphCo_6F_Text_Grunt2Intro, SilphCo_6F_Text_Grunt2Defeat
	msgbox SilphCo_6F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_6F_Text_RocketsTookOverBuilding::
    .string "火箭队闯进来\n"
    .string "占领了这幢大厦！$"

SilphCo_6F_Text_BetterGetBackToWork::
    .string "嘛，最好回去继续工作。$"

SilphCo_6F_Text_HelpMePlease::
    .string "哦，天哪，我的天哪。\n"
    .string "救命， 请救救我们！$"

SilphCo_6F_Text_WeGotEngaged::
    .string "我们订婚了。\n"
    .string "呵呵！$"

SilphCo_6F_Text_ThatManIsSuchACoward::
    .string "我旁边的那个男人……\n"
    .string "他居然是这样的一个懦夫！$"

SilphCo_6F_Text_NeedsMeToLookAfterHim::
    .string "他很绝望，他需要\n"
    .string "像我这样的人来照顾他。$"

SilphCo_6F_Text_RocketsTryingToConquerWorld::
    .string "火箭队正试图用宝可梦\n"
    .string "征服世界。$"

SilphCo_6F_Text_RocketsRanAwayBecauseOfYou::
    .string "火箭队逃跑了，\n"
    .string "这都对亏有你！$"

SilphCo_6F_Text_TargetedSilphForOurMonProducts::
    .string "他们一定是因为宝可梦产品\n"
    .string "而盯上了我们西尔佛。$"

SilphCo_6F_Text_ComeWorkForSilphWhenYoureOlder::
    .string "等你长大了就来\n"
    .string "西尔佛来上班吧。$"

SilphCo_6F_Text_Grunt1Intro::
    .string "我是火箭队\n"
    .string "四兄弟之一！$"

SilphCo_6F_Text_Grunt1Defeat::
    .string "真让人火大！$"

SilphCo_6F_Text_Grunt1PostBattle::
    .string "没关系！\n"
    .string "我的兄弟们会为我报仇的！$"

SilphCo_6F_Text_TaylorIntro::
    .string "那个可恶的总裁！\p"
    .string "该死的家伙用船把我送\n"
    .string "到了缇斯基分部！\p"
    .string "我敢肯定这就是为什么火箭队\n"
    .string "追着我们不放！$"

SilphCo_6F_Text_TaylorDefeat::
    .string "该死！$"

SilphCo_6F_Text_TaylorPostBattle::
    .string "缇斯基分部？\n"
    .string "在俄罗斯语里这是无人岛的意思！$"

SilphCo_6F_Text_Grunt2Intro::
    .string "你竟敢出卖火箭队？$"

SilphCo_6F_Text_Grunt2Defeat::
    .string "你这个叛徒！$"

SilphCo_6F_Text_Grunt2PostBattle::
    .string "如果你代表正义，那你\n"
    .string "就出卖了我们这些坏家伙！$"

SilphCo_6F_Text_FloorSign::
    .string "西尔佛公司总部\n"
    .string "6层$"

