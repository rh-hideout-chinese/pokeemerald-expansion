VictoryRoad_3F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, VictoryRoad_3F_OnLoad
	.byte 0

VictoryRoad_3F_OnLoad::
	call_if_ne VAR_MAP_SCENE_VICTORY_ROAD_3F, 100, VictoryRoad_3F_EventScript_SetRockBarrier
	end

VictoryRoad_3F_EventScript_SetRockBarrier::
	setmetatile 12, 12, METATILE_Cave_RockBarrier_Top, 1
	setmetatile 12, 13, METATILE_Cave_RockBarrier_Bottom, 1
	return

VictoryRoad_3F_EventScript_FloorSwitch::
	lockall
	goto_if_eq VAR_MAP_SCENE_VICTORY_ROAD_3F, 100, VictoryRoad_3F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 12, 12, METATILE_Cave_Floor_Ledge_Top, 0
	setmetatile 12, 13, METATILE_Cave_Floor_Ledge_Bottom, 0
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	copyobjectxytoperm LOCALID_VICTORY_ROAD_3F_BOULDER1
	copyobjectxytoperm LOCALID_VICTORY_ROAD_3F_BOULDER2
	setvar VAR_MAP_SCENE_VICTORY_ROAD_3F, 100
	releaseall
	end

VictoryRoad_3F_EventScript_FloorSwitchAlreadyPressed::
	releaseall
	end

VictoryRoad_3F_EventScript_George::
	trainerbattle_single TRAINER_COOLTRAINER_GEORGE, VictoryRoad_3F_Text_GeorgeIntro, VictoryRoad_3F_Text_GeorgeDefeat
	msgbox VictoryRoad_3F_Text_GeorgePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_3F_EventScript_Colby::
	trainerbattle_single TRAINER_COOLTRAINER_COLBY, VictoryRoad_3F_Text_ColbyIntro, VictoryRoad_3F_Text_ColbyDefeat
	msgbox VictoryRoad_3F_Text_ColbyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_3F_EventScript_Caroline::
	trainerbattle_single TRAINER_COOLTRAINER_CAROLINE, VictoryRoad_3F_Text_CarolineIntro, VictoryRoad_3F_Text_CarolineDefeat
	msgbox VictoryRoad_3F_Text_CarolinePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_3F_EventScript_Alexa::
	trainerbattle_single TRAINER_COOLTRAINER_ALEXA, VictoryRoad_3F_Text_AlexaIntro, VictoryRoad_3F_Text_AlexaDefeat
	msgbox VictoryRoad_3F_Text_AlexaPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_3F_EventScript_Ray::
	trainerbattle_double TRAINER_COOL_COUPLE_RAY_TYRA, VictoryRoad_3F_Text_RayIntro, VictoryRoad_3F_Text_RayDefeat, VictoryRoad_3F_Text_RayNotEnoughMons
	msgbox VictoryRoad_3F_Text_RayPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_3F_EventScript_Tyra::
	trainerbattle_double TRAINER_COOL_COUPLE_RAY_TYRA, VictoryRoad_3F_Text_TyraIntro, VictoryRoad_3F_Text_TyraDefeat, VictoryRoad_3F_Text_TyraNotEnoughMons
	msgbox VictoryRoad_3F_Text_TyraPostBattle, MSGBOX_AUTOCLOSE
	end

Text_DoubleEdgeTeach::
    .string "你应该为自己感到骄傲，\n"
    .string "你已经在这条冠军之路上\l"
    .string "勇敢的杀出了属于自己的路。\p"
    .string "作为对你成绩的认可\n"
    .string "我会教你舍身冲撞。\p"
    .string "你想要我教你学这个技能吗？$"

Text_DoubleEdgeDeclined::
    .string "我随时都能教你这个技能的。$"

Text_DoubleEdgeWhichMon::
    .string "我要教哪个宝可梦\n"
    .string "舍身冲撞$"

Text_DoubleEdgeTaught::
    .string "保持那股动力，\n"
    .string "去参加宝可梦联盟吧！\p"
    .string "去会会他们\n"
    .string "并将他们通通击败吧！$"

VictoryRoad_3F_Text_GeorgeIntro::
    .string "我听说关于一个神童的传闻。$"

VictoryRoad_3F_Text_GeorgeDefeat::
    .string "传闻是真的！$"

VictoryRoad_3F_Text_GeorgePostBattle::
    .string "莫非，就是你击败了\n"
    .string "火箭队的坂木吗？$"

VictoryRoad_3F_Text_AlexaIntro::
    .string "训练家的人生就是\n"
    .string "去寻找更强的对手。$"

VictoryRoad_3F_Text_AlexaDefeat::
    .string "啊！\n"
    .string "这么强！$"

VictoryRoad_3F_Text_AlexaPostBattle::
    .string "在艰难的战斗中，\n"
    .string "你会变得更强。$"

VictoryRoad_3F_Text_CarolineIntro::
    .string "我会让你看看你到底\n"
    .string "有多强……还是多弱！$"

VictoryRoad_3F_Text_CarolineDefeat::
    .string "我很气愤！$"

VictoryRoad_3F_Text_CarolinePostBattle::
    .string "你只不过证明了我有多强……$"

VictoryRoad_3F_Text_ColbyIntro::
    .string "只有被选中的人可以通过这里！$"

VictoryRoad_3F_Text_ColbyDefeat::
    .string "我不相信！$"

VictoryRoad_3F_Text_ColbyPostBattle::
    .string "这里所有的训练家都以\n"
    .string "宝可梦联盟为目标。\p"
    .string "不要放松警惕。$"

VictoryRoad_3F_Text_RayIntro::
    .string "阿新：我们俩在一起会更强大！$"

VictoryRoad_3F_Text_RayDefeat::
    .string "阿新：真可笑！\n"
    .string "这是不可能的！$"

VictoryRoad_3F_Text_RayPostBattle::
    .string "阿新：你打败了我们。\n"
    .string "强大的人总是难以捉摸……$"

VictoryRoad_3F_Text_RayNotEnoughMons::
    .string "阿新：我们俩一起着向冠军努力。\p"
    .string "请你带上两只宝可梦\n"
    .string "来跟我们战斗。$"

VictoryRoad_3F_Text_TyraIntro::
    .string "佳代：我们正试着一起\n"
    .string "变成冠军。$"

VictoryRoad_3F_Text_TyraDefeat::
    .string "佳代：哦，但是……$"

VictoryRoad_3F_Text_TyraPostBattle::
    .string "佳代：你教会了我，\n"
    .string "实力有无数种形式和形态。$"

VictoryRoad_3F_Text_TyraNotEnoughMons::
    .string "佳代：如果你只有一只宝可梦，\n"
    .string "就不能和我们战斗。$"

