SilphCo_5F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_5F_OnLoad
	.byte 0

SilphCo_5F_OnLoad::
	call_if_unset FLAG_SILPH_5F_DOOR_1, EventScript_Close5FDoor1
	call_if_unset FLAG_SILPH_5F_DOOR_2, EventScript_Close5FDoor2
	call_if_unset FLAG_SILPH_5F_DOOR_3, EventScript_Close5FDoor3
	end

SilphCo_5F_EventScript_WorkerM::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_5F_EventScript_WorkerMRocketsGone
	msgbox SilphCo_5F_Text_RocketsInUproarAboutIntruder
	release
	end

SilphCo_5F_EventScript_WorkerMRocketsGone::
	msgbox SilphCo_5F_Text_YoureOurHeroThankYou
	release
	end

SilphCo_5F_EventScript_PokemonReport1::
	msgbox SilphCo_5F_Text_PorygonFirstVRMon, MSGBOX_SIGN
	end

SilphCo_5F_EventScript_PokemonReport2::
	msgbox SilphCo_5F_Text_Over350TechniquesConfirmed, MSGBOX_SIGN
	end

SilphCo_5F_EventScript_PokemonReport3::
	msgbox SilphCo_5F_Text_SomeMonsEvolveWhenTraded, MSGBOX_SIGN
	end

SilphCo_5F_EventScript_FloorSign::
	msgbox SilphCo_5F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_5F_EventScript_Beau::
	trainerbattle_single TRAINER_SCIENTIST_BEAU, SilphCo_5F_Text_BeauIntro, SilphCo_5F_Text_BeauDefeat
	msgbox SilphCo_5F_Text_BeauPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_5F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_28, SilphCo_5F_Text_Grunt1Intro, SilphCo_5F_Text_Grunt1Defeat
	msgbox SilphCo_5F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_5F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_29, SilphCo_5F_Text_Grunt2Intro, SilphCo_5F_Text_Grunt2Defeat
	msgbox SilphCo_5F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_5F_EventScript_Dalton::
	trainerbattle_single TRAINER_JUGGLER_DALTON, SilphCo_5F_Text_DaltonIntro, SilphCo_5F_Text_DaltonDefeat
	msgbox SilphCo_5F_Text_DaltonPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_5F_Text_RocketsInUproarAboutIntruder::
    .string "火箭队有一些慌乱是因为\n"
    .string "有一些闯入者进来了。\p"
    .string "你就是那个闯入者，对吧？$"

SilphCo_5F_Text_YoureOurHeroThankYou::
    .string "火箭队逃跑了！\n"
    .string "你是我们的英雄！谢谢！$"

SilphCo_5F_Text_Grunt1Intro::
    .string "我听说有一个孩子\n"
    .string "在周围徘徊。$"

SilphCo_5F_Text_Grunt1Defeat::
    .string "隆隆！$"

SilphCo_5F_Text_Grunt1PostBattle::
    .string "和火箭队战斗可不是\n"
    .string "一个明智的选择！$"

SilphCo_5F_Text_BeauIntro::
    .string "我们在这一层研究\n"
    .string "关于精灵球的技术。$"

SilphCo_5F_Text_BeauDefeat::
    .string "啊！\n"
    .string "哎哟！$"

SilphCo_5F_Text_BeauPostBattle::
    .string "我们正在研究可以抓住任何\n"
    .string "宝可梦的超级精灵球。$"

SilphCo_5F_Text_DaltonIntro::
    .string "怎么回事？\p"
    .string "孩子不应该来这里的！$"

SilphCo_5F_Text_DaltonDefeat::
    .string "哦，天哪！$"

SilphCo_5F_Text_DaltonPostBattle::
    .string "你只不过刚到5F而已。\n"
    .string "要见我们的老大，还要走很长的一段路！$"

SilphCo_5F_Text_Grunt2Intro::
    .string "在火箭队面前放尊重些！$"

SilphCo_5F_Text_Grunt2Defeat::
    .string "咳……\n"
    .string "咳……$"

SilphCo_5F_Text_Grunt2PostBattle::
    .string "那倒提醒了我。\p"
    .string "瓦斯弹进化成了双弹瓦斯！$"

SilphCo_5F_Text_PorygonFirstVRMon::
    .string "这是一份宝可梦研究报告！\p"
    .string "宝可梦实验室创造了多边兽，\n"
    .string "第一个虚拟现实的宝可梦。$"

SilphCo_5F_Text_Over350TechniquesConfirmed::
    .string "这是一份宝可梦研究报告！\p"
    .string "已证实存在350个宝可梦\n"
    .string "的技能。$"

SilphCo_5F_Text_SomeMonsEvolveWhenTraded::
    .string "这是一份宝可梦研究报告！\p"
    .string "有些宝可梦已经被确认\n"
    .string "在他们被交换时会进化。$"

SilphCo_5F_Text_FloorSign::
    .string "西尔佛公司总部\n"
    .string "5层$"

SilphCo_5F_Text_RocketBossLookingForStrongMons::
    .string "那些混蛋占领了\n"
    .string "我们的大厦……\p"
    .string "他们的头目说他一直\n"
    .string "在寻找强大的宝可梦。\p"
    .string "我希望我们的总裁能\n"
    .string "不遇上这些麻烦……$"
