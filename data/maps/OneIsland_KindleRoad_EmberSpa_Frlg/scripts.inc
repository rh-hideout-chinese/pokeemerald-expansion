OneIsland_KindleRoad_EmberSpa_Frlg_MapScripts::
	.byte 0

OneIsland_KindleRoad_EmberSpa_EventScript_OldMan::
	msgbox OneIsland_KindleRoad_EmberSpa_Text_WaterWarmsMeToCore, MSGBOX_NPC
	end

OneIsland_KindleRoad_EmberSpa_EventScript_BaldingMan1::
	msgbox OneIsland_KindleRoad_EmberSpa_Text_EnjoyBowlOfChowder, MSGBOX_NPC
	end

OneIsland_KindleRoad_EmberSpa_EventScript_BaldingMan2::
	msgbox OneIsland_KindleRoad_EmberSpa_Text_HotSpringIsTherapeutic, MSGBOX_NPC
	end

OneIsland_KindleRoad_EmberSpa_EventScript_OldWoman::
	msgbox OneIsland_KindleRoad_EmberSpa_Text_SeeHowSmoothMySkinIs, MSGBOX_NPC
	end

OneIsland_KindleRoad_EmberSpa_EventScript_BlackBelt::
	lock
	faceplayer
	famechecker FAMECHECKER_BRUNO, 3
	msgbox OneIsland_KindleRoad_EmberSpa_Text_BrunoVisitsSpaOnOccasion
	release
	end

OneIsland_KindleRoad_EmberSpa_EventScript_RockSmashMan::
	lock
	faceplayer
	goto_if_set FLAG_GOT_HM06, OneIsland_KindleRoad_EmberSpa_EventScript_AlreadyGotHM06
	msgbox OneIsland_KindleRoad_EmberSpa_Text_UsedThisToMakeEmberSpa
	giveitem ITEM_HM06
	setflag FLAG_GOT_HM06
	msgbox OneIsland_KindleRoad_EmberSpa_Text_ExplainHM06
	release
	end

OneIsland_KindleRoad_EmberSpa_EventScript_AlreadyGotHM06::
	msgbox OneIsland_KindleRoad_EmberSpa_Text_ExplainHM06
	release
	end

OneIsland_KindleRoad_EmberSpa_EventScript_SpaHeal::
	lockall
	fadescreen FADE_TO_WHITE
	special HealPlayerParty
	fadescreen FADE_FROM_WHITE
	msgbox OneIsland_KindleRoad_EmberSpa_Text_WaterExquisiteFullyRefreshed
	setvar VAR_TEMP_1, 1
	releaseall
	end

OneIsland_KindleRoad_EmberSpa_Text_WaterWarmsMeToCore::
    .string "嗯！\n"
    .string "哈哈！\p"
    .string "真是天堂般的感受！\n"
    .string "这些温暖的水涌入我的心！\p"
    .string "你也应该跳进来的。\p"
    .string "到中间去，放松，\n"
    .string "去体会温暖和美好！$"

OneIsland_KindleRoad_EmberSpa_Text_EnjoyBowlOfChowder::
    .string "马上要进行的是\n"
    .string "沐浴中我最喜欢的一个环节。\p"
    .string "我也喜欢吃下一碗大杂烩，\n"
    .string "享受从身体内部涌出温暖的感觉。$"

OneIsland_KindleRoad_EmberSpa_Text_WaterExquisiteFullyRefreshed::
    .string "水非常温暖。\n"
    .string "有一种绝妙的感觉……\p"
    .string "{PLAYER}的宝可梦完全恢复精神了！$"

OneIsland_KindleRoad_EmberSpa_Text_HotSpringIsTherapeutic::
    .string "据说，\n"
    .string "泡温泉有益于身体健康。$"

OneIsland_KindleRoad_EmberSpa_Text_SeeHowSmoothMySkinIs::
    .string "看看我的脸。\n"
    .string "我的皮肤是不是很光滑？\p"
    .string "泡温泉使我看起来更年轻。$"

OneIsland_KindleRoad_EmberSpa_Text_BrunoVisitsSpaOnOccasion::
    .string "在经过一天辛苦的训练之后，\n"
    .string "没有比泡温泉更让人惬意的事了。\p"
    .string "我的一个前辈叫做希巴。\n"
    .string "有时会他会和他的宝可梦\p"
    .string "一起来到这个温泉，\n"
    .string "在这里做水疗。$"

OneIsland_KindleRoad_EmberSpa_Text_UsedThisToMakeEmberSpa::
    .string "温泉是伴随着火山而产生的。\p"
    .string "几年前，\n"
    .string "我在这里建造了灯火温泉。\p"
    .string "我从一堆巨大的岩石中，\n"
    .string "亲手开辟出了这个池子。\p"
    .string "那时我使用了这招，\n"
    .string "我想我是时候该放开它了。$"

OneIsland_KindleRoad_EmberSpa_Text_ExplainHM06::
    .string "就像它们是用饼干做的一样，\n"
    .string "我用这招砸碎了巨石。$"

