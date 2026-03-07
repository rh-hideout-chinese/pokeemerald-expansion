ViridianForest_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianForest_OnTransition
	.byte 0

ViridianForest_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_VIRIDIAN_FOREST
	end

ViridianForest_EventScript_Youngster::
	msgbox ViridianForest_Text_FriendsItchingToBattle, MSGBOX_NPC
	end

ViridianForest_EventScript_Boy::
	msgbox ViridianForest_Text_RanOutOfPokeBalls, MSGBOX_NPC
	end

ViridianForest_EventScript_TrainerTips1::
	msgbox ViridianForest_Text_AvoidGrassyAreasWhenWeak, MSGBOX_SIGN
	end

ViridianForest_EventScript_TrainerTips2::
	msgbox ViridianForest_Text_UseAntidoteForPoison, MSGBOX_SIGN
	end

ViridianForest_EventScript_TrainerTips3::
	msgbox ViridianForest_Text_ContactOakViaPCToRatePokedex, MSGBOX_SIGN
	end

ViridianForest_EventScript_TrainerTips4::
	msgbox ViridianForest_Text_CantCatchOwnedMons, MSGBOX_SIGN
	end

ViridianForest_EventScript_TrainerTips5::
	msgbox ViridianForest_Text_WeakenMonsBeforeCapture, MSGBOX_SIGN
	end

ViridianForest_EventScript_ExitSign::
	msgbox ViridianForest_Text_LeavingViridianForest, MSGBOX_SIGN
	end

ViridianForest_EventScript_Rick::
	trainerbattle_single TRAINER_BUG_CATCHER_RICK, ViridianForest_Text_RickIntro, ViridianForest_Text_RickDefeat
	msgbox ViridianForest_Text_RickPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_EventScript_Doug::
	trainerbattle_single TRAINER_BUG_CATCHER_DOUG, ViridianForest_Text_DougIntro, ViridianForest_Text_DougDefeat
	msgbox ViridianForest_Text_DougPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_EventScript_Sammy::
	trainerbattle_single TRAINER_BUG_CATCHER_SAMMY, ViridianForest_Text_SammyIntro, ViridianForest_Text_SammyDefeat
	msgbox ViridianForest_Text_SammyPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_EventScript_Anthony::
	trainerbattle_single TRAINER_BUG_CATCHER_ANTHONY, ViridianForest_Text_AnthonyIntro, ViridianForest_Text_AnthonyDefeat
	msgbox ViridianForest_Text_AnthonyPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_EventScript_Charlie::
	trainerbattle_single TRAINER_BUG_CATCHER_CHARLIE, ViridianForest_Text_CharlieIntro, ViridianForest_Text_CharlieDefeat
	msgbox ViridianForest_Text_CharliePostBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_Text_FriendsItchingToBattle::
    .string "我和朋友们来这里\n"
    .string "收服虫属性的宝可梦。\p"
    .string "他们都渴望用\n"
    .string "自己的宝可梦去战斗！$"

ViridianForest_Text_RickIntro::
    .string "嘿！你有宝可梦啊！\l"
    .string "来吧！\l"
    .string "我们对战！$"

ViridianForest_Text_RickDefeat::
    .string "不！\n"
    .string "绿毛虫根本打不过它！$"

ViridianForest_Text_RickPostBattle::
    .string "嘘！你这样会把虫子吓跑的。\n"
    .string "下次再来打一场，怎么样？$"

ViridianForest_Text_DougIntro::
    .string "嗨！\n"
    .string "如果你是一个宝可梦训练家，\l"
    .string "就不能大意！$"

ViridianForest_Text_DougDefeat::
    .string "啥？\n"
    .string "我的宝可梦全倒下了！$"

ViridianForest_Text_DougPostBattle::
    .string "太糟了！\n"
    .string "我要去抓些更强大的！$"

ViridianForest_Text_SammyIntro::
    .string "嘿！等一下！\n"
    .string "怎么了？你跑这么快干嘛？$"

ViridianForest_Text_SammyDefeat::
    .string "我服了！\n"
    .string "你的确很强！$"

ViridianForest_Text_SammyPostBattle::
    .string "有的时候，\n"
    .string "你能找到一些掉在地上的东西。\p"
    .string "我正在找我掉了的东西。\n"
    .string "你能帮我找找吗？$"

ViridianForest_Text_AnthonyIntro::
    .string "我身材可能很矮小，\n"
    .string "但我可不希望你因此对我手下留情！$"

ViridianForest_Text_AnthonyDefeat::
    .string "唉，真不好。\n"
    .string "完全没照我的计划来。$"

ViridianForest_Text_AnthonyPostBattle::
    .string "我弄丢了一些零用钱……$"

ViridianForest_Text_CharlieIntro::
    .string "宝可梦的进化你知道多少？$"

ViridianForest_Text_CharlieDefeat::
    .string "噢！\n"
    .string "我输了！$"

ViridianForest_Text_CharliePostBattle::
    .string "虫属性宝可梦进化得很快。\n"
    .string "和它们在一起乐趣多多！$"

ViridianForest_Text_RanOutOfPokeBalls::
    .string "为了收服宝可梦\n"
    .string "我把精灵球都用光了。\p"
    .string "所以你需要常备\n"
    .string "一些精灵球在身边。$"

ViridianForest_Text_AvoidGrassyAreasWhenWeak::
    .string "训练家贴士\p"
    .string "如果你的宝可梦很虚弱，\n"
    .string "而且你不想进行无谓的战斗的话，\l"
    .string "那么就避开草地吧！$"

ViridianForest_Text_UseAntidoteForPoison::
    .string "如果中毒了，就用解毒药！\n"
    .string "你可以在宝可梦商店里买到！$"

ViridianForest_Text_ContactOakViaPCToRatePokedex::
    .string "训练家贴士\p"
    .string "通过电脑联系大木博士，\n"
    .string "让他给你的宝可梦图鉴做个评价！$"

ViridianForest_Text_CantCatchOwnedMons::
    .string "训练家贴士\p"
    .string "你不可以收服\n"
    .string "别人的宝可梦。\p"
    .string "只有对野生的宝可梦\n"
    .string "才能用精灵球收服！$"

ViridianForest_Text_WeakenMonsBeforeCapture::
    .string "训练家贴士\p"
    .string "在收服宝可梦之前\n"
    .string "先削弱它们的体力！\p"
    .string "它们精力充沛时可能会逃跑！$"

ViridianForest_Text_LeavingViridianForest::
    .string "走出常青森林后\n"
    .string "深灰市就在前面$"

