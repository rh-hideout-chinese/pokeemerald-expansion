FuchsiaCity_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FuchsiaCity_OnTransition
	.byte 0

FuchsiaCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_FUCHSIA_CITY
	call_if_set FLAG_GOT_DOME_FOSSIL, FuchsiaCity_EventScript_SetOmanyteGfx
	call_if_unset FLAG_GOT_DOME_FOSSIL, FuchsiaCity_EventScript_SetKabutoGfx
	end

FuchsiaCity_EventScript_SetOmanyteGfx::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_OMANYTE
	return

FuchsiaCity_EventScript_SetKabutoGfx::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_KABUTO
	return

FuchsiaCity_EventScript_LittleBoy::
	msgbox FuchsiaCity_Text_DidYouTrySafariGame, MSGBOX_NPC
	end

FuchsiaCity_EventScript_OldMan::
	msgbox FuchsiaCity_Text_SafariZoneZooInFront, MSGBOX_NPC
	end

FuchsiaCity_EventScript_Erik::
	msgbox FuchsiaCity_Text_WheresSara, MSGBOX_NPC
	end

FuchsiaCity_EventScript_Youngster::
	msgbox FuchsiaCity_Text_ItemBallInThere, MSGBOX_NPC
	end

FuchsiaCity_EventScript_Lass::
	lock
	faceplayer
	famechecker FAMECHECKER_KOGA, 3
	msgbox FuchsiaCity_Text_MyFatherIsGymLeader
	release
	end

FuchsiaCity_EventScript_CitySign::
	msgbox FuchsiaCity_Text_CitySign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_SafariZoneSign::
	msgbox FuchsiaCity_Text_SafariZoneSign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_SafariGameSign::
	msgbox FuchsiaCity_Text_SafariGameSign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_WardensHomeSign::
	msgbox FuchsiaCity_Text_WardensHomeSign, MSGBOX_SIGN
	end

@ Unused
FuchsiaCity_EventScript_SafariZoneOfficeSign::
	msgbox FuchsiaCity_Text_SafariZoneOfficeSign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_KOGA, 0
	msgbox FuchsiaCity_Text_GymSign
	releaseall
	end

FuchsiaCity_EventScript_ChanseySign::
	lockall
	setvar VAR_0x8004, SPECIES_CHANSEY
	special SetSeenMon
	showmonpic SPECIES_CHANSEY, 10, 3
	msgbox FuchsiaCity_Text_ChanseySign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_VoltorbSign::
	lockall
	setvar VAR_0x8004, SPECIES_VOLTORB
	special SetSeenMon
	showmonpic SPECIES_VOLTORB, 10, 3
	msgbox FuchsiaCity_Text_VoltorbSign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_KangaskhanSign::
	lockall
	setvar VAR_0x8004, SPECIES_KANGASKHAN
	special SetSeenMon
	showmonpic SPECIES_KANGASKHAN, 10, 3
	msgbox FuchsiaCity_Text_KangaskhanSign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_SlowpokeSign::
	lockall
	setvar VAR_0x8004, SPECIES_SLOWPOKE
	special SetSeenMon
	showmonpic SPECIES_SLOWPOKE, 10, 3
	msgbox FuchsiaCity_Text_SlowpokeSign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_LaprasSign::
	lockall
	setvar VAR_0x8004, SPECIES_LAPRAS
	special SetSeenMon
	showmonpic SPECIES_LAPRAS, 10, 3
	msgbox FuchsiaCity_Text_LaprasSign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_FossilMonSign::
	lockall
	goto_if_set FLAG_GOT_DOME_FOSSIL, FuchsiaCity_EventScript_OmanyteSign
	setvar VAR_0x8004, SPECIES_KABUTO
	special SetSeenMon
	showmonpic SPECIES_KABUTO, 10, 3
	msgbox FuchsiaCity_Text_KabutoSign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_OmanyteSign::
	setvar VAR_0x8004, SPECIES_OMANYTE
	special SetSeenMon
	showmonpic SPECIES_OMANYTE, 10, 3
	msgbox FuchsiaCity_Text_OmanyteSign
	hidemonpic
	releaseall
	end

FuchsiaCity_Text_DidYouTrySafariGame::
    .string "你试过原野区游戏吗？\p"
    .string "有一些稀有的宝可梦\n"
    .string "只能在那里抓到。$"

FuchsiaCity_Text_SafariZoneZooInFront::
    .string "野生原野区在入口前面\n"
    .string "有一个园子。\p"
    .string "后面就是收服宝可梦\n"
    .string "的原野区游戏。$"

FuchsiaCity_Text_WheresSara::
    .string "阿初：敦子在哪里？\n"
    .string "说了在这里等她的。$"

FuchsiaCity_Text_ItemBallInThere::
    .string "那里放着个精灵球……\n"
    .string "你想要吗？\p"
    .string "我也是！\n"
    .string "……嗯？那是一只宝可梦？$"

FuchsiaCity_Text_CitySign::
    .string "浅红市\n"
    .string "浅红，是浅红亮丽的石竹花！$"

FuchsiaCity_Text_SafariZoneSign::
    .string "宝可梦的乐园\n"
    .string "野生原野区$"

FuchsiaCity_Text_SafariGameSign::
    .string "原野区游戏\n"
    .string "收服宝可梦吧！$"

FuchsiaCity_Text_WardensHomeSign::
    .string "野生原野区\n"
    .string "园长的家$"

FuchsiaCity_Text_SafariZoneOfficeSign::
    .string "宝可梦的乐园！\n"
    .string "欢迎来到野生原野区！\l"
    .string "原野区办公室$"

FuchsiaCity_Text_GymSign::
    .string "浅红市宝可梦道馆\n"
    .string "馆主：阿桔\l"
    .string "剧毒的忍者之王$"

FuchsiaCity_Text_ChanseySign::
    .string "名字 吉利蛋\n"
    .string "抓到的话说明你运气很好。$"

FuchsiaCity_Text_VoltorbSign::
    .string "名字 霹雳电球\n"
    .string "外观很像一个精灵球。$"

FuchsiaCity_Text_KangaskhanSign::
    .string "名字 袋兽\p"
    .string "母亲般的宝可梦，用肚子上的\n"
    .string "口袋来养育自己的小孩。$"

FuchsiaCity_Text_SlowpokeSign::
    .string "名字 呆呆兽\n"
    .string "很友好，但是行动缓慢。$"

FuchsiaCity_Text_LaprasSign::
    .string "名字 拉普拉斯\n"
    .string "又被称为海上的王者。$"

FuchsiaCity_Text_OmanyteSign::
    .string "名字 菊石兽\n"
    .string "从化石中再生的\l"
    .string "极其稀有的宝可梦。$"

FuchsiaCity_Text_KabutoSign::
    .string "名字 化石盔\n"
    .string "从化石中再生的\l"
    .string "极其稀有的宝可梦。$"

@ Unused. May have been meant to be the placeholder text for the zoo mons, similar to RB's "!" text
FuchsiaCity_Text_Ellipsis::
    .string "……$"

Text_SubstituteTeach::
    .string "啊 我多么希望自己是\n"
    .string "袋兽的孩子。\p"
    .string "我甚至愿意替代这个孩子……\p"
    .string "依偎在母亲\n"
    .string "袋兽的袋子里。\p"
    .string "但是只有宝可梦能使用\n"
    .string "技能替身……\p"
    .string "让我教给你的宝可梦\n"
    .string "替身吧？$"

Text_SubstituteDeclined::
    .string "哦，真的吗？\n"
    .string "替身其实很有趣呢……$"

Text_SubstituteWhichMon::
    .string "哪只宝可梦想要\n"
    .string "学会替身？$"

Text_SubstituteTaught::
    .string "孩子，我需要什么才能爬进\n"
    .string "袋兽的袋子里呢……$"

FuchsiaCity_Text_MyFatherIsGymLeader::
    .string "我父亲是这座城市道馆的馆主。\p"
    .string "我日复一日的特训，就是为了成为\n"
    .string "父亲那样的毒属性宝可梦高手。$"

