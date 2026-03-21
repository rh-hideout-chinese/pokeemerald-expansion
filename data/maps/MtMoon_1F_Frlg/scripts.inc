MtMoon_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtMoon_1F_OnTransition
	.byte 0

MtMoon_1F_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_MT_MOON_1F
	end

MtMoon_1F_EventScript_ZubatSign::
	msgbox MtMoon_1F_Text_ZubatIsABloodsucker, MSGBOX_SIGN
	end

MtMoon_1F_EventScript_Marcos::
	trainerbattle_single TRAINER_HIKER_MARCOS, MtMoon_1F_Text_MarcosIntro, MtMoon_1F_Text_MarcosDefeat
	msgbox MtMoon_1F_Text_MarcosPostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_1F_EventScript_Josh::
	trainerbattle_single TRAINER_YOUNGSTER_JOSH, MtMoon_1F_Text_JoshIntro, MtMoon_1F_Text_JoshDefeat
	msgbox MtMoon_1F_Text_JoshPostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_1F_EventScript_Miriam::
	trainerbattle_single TRAINER_LASS_MIRIAM, MtMoon_1F_Text_MiriamIntro, MtMoon_1F_Text_MiriamDefeat
	msgbox MtMoon_1F_Text_MiriamPostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_1F_EventScript_Iris::
	trainerbattle_single TRAINER_LASS_IRIS, MtMoon_1F_Text_IrisIntro, MtMoon_1F_Text_IrisDefeat
	msgbox MtMoon_1F_Text_IrisPostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_1F_EventScript_Jovan::
	trainerbattle_single TRAINER_SUPER_NERD_JOVAN, MtMoon_1F_Text_JovanIntro, MtMoon_1F_Text_JovanDefeat
	msgbox MtMoon_1F_Text_JovanPostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_1F_EventScript_Kent::
	trainerbattle_single TRAINER_BUG_CATCHER_KENT, MtMoon_1F_Text_KentIntro, MtMoon_1F_Text_KentDefeat
	msgbox MtMoon_1F_Text_KentPostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_1F_EventScript_Robby::
	trainerbattle_single TRAINER_BUG_CATCHER_ROBBY, MtMoon_1F_Text_RobbyIntro, MtMoon_1F_Text_RobbyDefeat
	msgbox MtMoon_1F_Text_RobbyPostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_1F_Text_MarcosIntro::
    .string "哇！\n"
    .string "吓我一大跳！\l"
    .string "……不过就是个小孩嘛！$"

MtMoon_1F_Text_MarcosDefeat::
    .string "哇！\n"
    .string "吓我两大跳！$"

MtMoon_1F_Text_MarcosPostBattle::
    .string "像你这样的小朋友\n"
    .string "不应该在这么暗的地方晃悠。$"

MtMoon_1F_Text_JoshIntro::
    .string "你也是来这个山洞探险的吗？$"

MtMoon_1F_Text_JoshDefeat::
    .string "惨败！\n"
    .string "太丢人了。$"

MtMoon_1F_Text_JoshPostBattle::
    .string "我来这里的目的就是向\n"
    .string "女生们显摆我本人的形象。$"

MtMoon_1F_Text_MiriamIntro::
    .string "哇！\n"
    .string "这里宽敞得出乎我预料！$"

MtMoon_1F_Text_MiriamDefeat::
    .string "喔！\n"
    .string "我输了！$"

MtMoon_1F_Text_MiriamPostBattle::
    .string "你打算怎么从这儿出去？\n"
    .string "这里太大了，我都要迷路了。$"

MtMoon_1F_Text_JovanIntro::
    .string "干嘛！\n"
    .string "别鬼鬼祟祟地靠近我！$"

MtMoon_1F_Text_JovanDefeat::
    .string "我的宝可梦是不会输的！$"

MtMoon_1F_Text_JovanPostBattle::
    .string "我必须抓一些更强的宝可梦了。\n"
    .string "但是它们在哪儿呢？$"

MtMoon_1F_Text_IrisIntro::
    .string "什么？\n"
    .string "我在这儿等朋友来找我。$"

MtMoon_1F_Text_IrisDefeat::
    .string "我输了？$"

MtMoon_1F_Text_IrisPostBattle::
    .string "听说这里有罕见的\n"
    .string "化石，我就赶来了。$"

MtMoon_1F_Text_KentIntro::
    .string "有一些可疑的人在这个山洞里。\n"
    .string "你呢，你在这里干什么？$"

MtMoon_1F_Text_KentDefeat::
    .string "被你打败了！$"

MtMoon_1F_Text_KentPostBattle::
    .string "我看见他们了！\n"
    .string "我可以肯定他们是火箭队的！$"

MtMoon_1F_Text_RobbyIntro::
    .string "你要穿过这个山洞\n"
    .string "才能到达华蓝市。$"

MtMoon_1F_Text_RobbyDefeat::
    .string "我输了。$"

MtMoon_1F_Text_RobbyPostBattle::
    .string "超音蝠是很难对付的！\n"
    .string "不过你收服了一只的话，\l"
    .string "你完全可以信任它。$"

MtMoon_1F_Text_ZubatIsABloodsucker::
    .string "注意！\n"
    .string "超音蝠就像一只吸血鬼！$"

MtMoon_1F_Text_BrockHelpsExcavateFossils::
    .string "嗨，我在月见山\n"
    .string "脚下挖掘化石。\p"
    .string "有时候，深灰道馆的小刚\n"
    .string "会来帮我的忙。$"
