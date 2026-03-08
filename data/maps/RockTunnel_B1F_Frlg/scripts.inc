RockTunnel_B1F_Frlg_MapScripts::
	.byte 0

RockTunnel_B1F_EventScript_Sofia::
	trainerbattle_single TRAINER_PICNICKER_SOFIA, RockTunnel_B1F_Text_SofiaIntro, RockTunnel_B1F_Text_SofiaDefeat
	msgbox RockTunnel_B1F_Text_SofiaPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Martha::
	trainerbattle_single TRAINER_PICNICKER_MARTHA, RockTunnel_B1F_Text_MarthaIntro, RockTunnel_B1F_Text_MarthaDefeat
	msgbox RockTunnel_B1F_Text_MarthaPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Dudley::
	trainerbattle_single TRAINER_HIKER_DUDLEY, RockTunnel_B1F_Text_DudleyIntro, RockTunnel_B1F_Text_DudleyDefeat
	msgbox RockTunnel_B1F_Text_DudleyPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Allen::
	trainerbattle_single TRAINER_HIKER_ALLEN, RockTunnel_B1F_Text_AllenIntro, RockTunnel_B1F_Text_AllenDefeat
	msgbox RockTunnel_B1F_Text_AllenPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Eric::
	trainerbattle_single TRAINER_HIKER_ERIC, RockTunnel_B1F_Text_EricIntro, RockTunnel_B1F_Text_EricDefeat
	msgbox RockTunnel_B1F_Text_EricPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Cooper::
	trainerbattle_single TRAINER_POKEMANIAC_COOPER, RockTunnel_B1F_Text_CooperIntro, RockTunnel_B1F_Text_CooperDefeat
	msgbox RockTunnel_B1F_Text_CooperPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Steve::
	trainerbattle_single TRAINER_POKEMANIAC_STEVE, RockTunnel_B1F_Text_SteveIntro, RockTunnel_B1F_Text_SteveDefeat
	msgbox RockTunnel_B1F_Text_StevePostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Winston::
	trainerbattle_single TRAINER_POKEMANIAC_WINSTON, RockTunnel_B1F_Text_WinstonIntro, RockTunnel_B1F_Text_WinstonDefeat
	msgbox RockTunnel_B1F_Text_WinstonPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_Text_SofiaIntro::
    .string "你知道怎样避免\n"
    .string "在深山里迷路么？\p"
    .string "你可以折断树枝\n"
    .string "作为路标。$"

RockTunnel_B1F_Text_SofiaDefeat::
    .string "哦哦哦！\n"
    .string "我尽力了！$"

RockTunnel_B1F_Text_SofiaPostBattle::
    .string "我想回家！$"

RockTunnel_B1F_Text_DudleyIntro::
    .string "哈哈哈！\n"
    .string "你能战胜我么？$"

RockTunnel_B1F_Text_DudleyDefeat::
    .string "诶呀！\n"
    .string "你竟然比我强！$"

RockTunnel_B1F_Text_DudleyPostBattle::
    .string "我只追求力量，\n"
    .string "因为我懒得思考！$"

RockTunnel_B1F_Text_CooperIntro::
    .string "你有宝可梦图鉴？\n"
    .string "我也想要一个。$"

RockTunnel_B1F_Text_CooperDefeat::
    .string "可恶啊！\n"
    .string "真嫉妒你啊！$"

RockTunnel_B1F_Text_CooperPostBattle::
    .string "当你完成了你的宝可梦图鉴，\n"
    .string "可以把它送给我吗？$"

RockTunnel_B1F_Text_SteveIntro::
    .string "嗯…你了解\n"
    .string "宝可梦cosplay吗？$"

RockTunnel_B1F_Text_SteveDefeat::
    .string "好吧，就这样吧。$"

RockTunnel_B1F_Text_StevePostBattle::
    .string "所谓cosplay宝可梦，\n"
    .string "就是为了好玩打扮成宝可梦的样子！\p"
    .string "我最喜欢扮成皮皮了。$"

RockTunnel_B1F_Text_AllenIntro::
    .string "我的宝可梦技能，\n"
    .string "会把你打到哭！$"

RockTunnel_B1F_Text_AllenDefeat::
    .string "我投降！\n"
    .string "你是一个更好的技术员！$"

RockTunnel_B1F_Text_AllenPostBattle::
    .string "在山里，你经常会遇到\n"
    .string "岩石属性的宝可梦。$"

RockTunnel_B1F_Text_MarthaIntro::
    .string "虽然我不经常来这儿，\n"
    .string "但我还是要和你打一场。$"

RockTunnel_B1F_Text_MarthaDefeat::
    .string "啊！\n"
    .string "我输了！$"

RockTunnel_B1F_Text_MarthaPostBattle::
    .string "我喜欢小小的宝可梦。\n"
    .string "大的实在是太吓人了！$"

RockTunnel_B1F_Text_EricIntro::
    .string "尽你所能打中我！$"

RockTunnel_B1F_Text_EricDefeat::
    .string "开火！$"

RockTunnel_B1F_Text_EricPostBattle::
    .string "小子，我会培育我自己的宝可梦\n"
    .string "来打败你的！$"

RockTunnel_B1F_Text_WinstonIntro::
    .string "我在家里的时候，\n"
    .string "给宝可梦画插画。$"

RockTunnel_B1F_Text_WinstonDefeat::
    .string "呼呼…\n"
    .string "累死了…$"

RockTunnel_B1F_Text_WinstonPostBattle::
    .string "我是一名画师，不是战士。\n"
    .string "我要回家画画去了。$"

