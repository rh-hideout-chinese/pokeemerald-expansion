Route20_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route20_OnTransition
	.byte 0

Route20_OnTransition::
	call_if_unset FLAG_STOPPED_SEAFOAM_B3F_CURRENT, Route20_EventScript_ResetSeafoamBouldersForB3F
	call_if_unset FLAG_STOPPED_SEAFOAM_B4F_CURRENT, Route20_EventScript_ResetSeafoamBouldersForB4F
	end

Route20_EventScript_ResetSeafoamBouldersForB3F::
	clearflag FLAG_HIDE_SEAFOAM_1F_BOULDER_1
	clearflag FLAG_HIDE_SEAFOAM_1F_BOULDER_2
	setflag FLAG_HIDE_SEAFOAM_B1F_BOULDER_1
	setflag FLAG_HIDE_SEAFOAM_B1F_BOULDER_2
	setflag FLAG_HIDE_SEAFOAM_B2F_BOULDER_1
	setflag FLAG_HIDE_SEAFOAM_B2F_BOULDER_2
	setflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_1
	setflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_2
	return

Route20_EventScript_ResetSeafoamBouldersForB4F::
	clearflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_3
	clearflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_4
	clearflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_5
	clearflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_6
	setflag FLAG_HIDE_SEAFOAM_B4F_BOULDER_1
	setflag FLAG_HIDE_SEAFOAM_B4F_BOULDER_2
	return

Route20_EventScript_SeafoamIslandsSign::
	msgbox Route20_Text_SeafoamIslands, MSGBOX_SIGN
	end

Route20_Text_BarryIntro::
    .string "这儿的水很浅。\n"
    .string "有很多人在这儿游泳。$"

Route20_Text_BarryDefeat::
    .string "扑通！$"

Route20_Text_BarryPostBattle::
    .string "我希望能骑着我的宝可梦。\n"
    .string "你应该还不算太累。$"

Route20_Text_ShirleyIntro::
    .string "双子岛是一个安静的度假场所。\n"
    .string "我就是正在这儿休假。$"

Route20_Text_ShirleyDefeat::
    .string "停下来！$"

Route20_Text_ShirleyPostBattle::
    .string "这座岛下有个巨大的洞穴。$"

Route20_Text_TiffanyIntro::
    .string "我喜欢和鱼儿们一起\n"
    .string "飘游在波浪之中。$"

Route20_Text_TiffanyDefeat::
    .string "哟！$"

Route20_Text_TiffanyPostBattle::
    .string "想和我一起飘游吗？$"

Route20_Text_IreneIntro::
    .string "你也在度假吗？$"

Route20_Text_IreneDefeat::
    .string "不会放过你！$"

Route20_Text_IrenePostBattle::
    .string "在很久以前，\n"
    .string "双子岛是一座独立的小岛。$"

Route20_Text_DeanIntro::
    .string "检查一下我充满肌肉的体格！$"

Route20_Text_DeanDefeat::
    .string "太没用了！$"

Route20_Text_DeanPostBattle::
    .string "我应该让宝可梦的体格变强壮，\n"
    .string "而不是我的！$"

Route20_Text_DarrinIntro::
    .string "你为什么骑着宝可梦？\n"
    .string "你不会游泳吗？$"

Route20_Text_DarrinDefeat::
    .string "哎哟！\n"
    .string "完了！$"

Route20_Text_DarrinPostBattle::
    .string "骑着宝可梦看起来确实很有趣！$"

Route20_Text_RogerIntro::
    .string "我乘着我的鸟系宝可梦来这。$"

Route20_Text_RogerDefeat::
    .string "噢，不！\n"
    .string "现在我该怎么办？$"

Route20_Text_RogerPostBattle::
    .string "我的宝可梦筋疲力尽了。\n"
    .string "它们不能带我飞翔回去了！$"

Route20_Text_NoraIntro::
    .string "我的男朋友给了我大颗的珍珠。$"

Route20_Text_NoraDefeat::
    .string "噢，不！\n"
    .string "我的珍珠还在里面！$"

Route20_Text_NoraPostBattle::
    .string "我的珍珠放在刺甲贝\n"
    .string "里面会变大吗？$"

Route20_Text_MissyIntro::
    .string "我从红莲镇游过来的。\n"
    .string "跟你讲，这可不轻松。$"

Route20_Text_MissyDefeat::
    .string "我太失望了！$"

Route20_Text_MissyPostBattle::
    .string "在红莲，宝可梦占据了\n"
    .string "那所被遗弃的大厦。\p"
    .string "那儿现在叫做宝可梦屋。$"

Route20_Text_MelissaIntro::
    .string "在红莲西方，\n"
    .string "有一个宝可梦的研究所。\p"
    .string "我的爸爸在那儿工作。$"

Route20_Text_MelissaDefeat::
    .string "等等！\n"
    .string "你给我站住！$"

Route20_Text_MelissaPostBattle::
    .string "红莲是一个火山岛。\p"
    .string "我听说在某一次火山喷发时，\n"
    .string "它从海上生成了。$"

Route20_Text_SeafoamIslands::
    .string "双子岛$"

Route20_Text_MistyTrainsHere::
    .string "在这儿经常能看到\n"
    .string "强大的训练家和强大的水属性宝可梦。\p"
    .string "据说华蓝道馆的小霞\n"
    .string "也在这儿训练。$"
