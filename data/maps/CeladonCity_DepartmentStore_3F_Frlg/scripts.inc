CeladonCity_DepartmentStore_3F_Frlg_MapScripts::
	.byte 0

CeladonCity_DepartmentStore_3F_EventScript_CounterTutor::
	goto EventScript_CounterTutor
	end

CeladonCity_DepartmentStore_3F_EventScript_GBAKid1::
	msgbox CeladonCity_DepartmentStore_3F_Text_OTStandsForOriginalTrainer, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_3F_EventScript_GBAKid2::
	msgbox CeladonCity_DepartmentStore_3F_Text_BuddyTradingKangaskhanForHaunter, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_3F_EventScript_GBAKid3::
	msgbox CeladonCity_DepartmentStore_3F_Text_HaunterEvolvedOnTrade, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_3F_EventScript_LittleGirl::
	msgbox CeladonCity_DepartmentStore_3F_Text_CanIdentifyTradeMonsByID, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_3F_EventScript_SuperNES::
	msgbox CeladonCity_DepartmentStore_3F_Text_ItsSuperNES, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_3F_EventScript_TV1::
	msgbox CeladonCity_DepartmentStore_3F_Text_AnRPG, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_3F_EventScript_TV2::
	msgbox CeladonCity_DepartmentStore_3F_Text_SportsGame, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_3F_EventScript_TV3::
	msgbox CeladonCity_DepartmentStore_3F_Text_PuzzleGame, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_3F_EventScript_TV4::
	msgbox CeladonCity_DepartmentStore_3F_Text_FightingGame, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_3F_EventScript_FloorSign::
	msgbox CeladonCity_DepartmentStore_3F_Text_TVGameShop, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_3F_EventScript_Poster::
	msgbox CeladonCity_DepartmentStore_3F_Text_RedGreenBothArePokemon, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_3F_Text_OTStandsForOriginalTrainer::
    .string "收服后的宝可梦会生成\n"
    .string "“ID号码”和“主人”(OT)。\p"
    .string "OT是“初始训练家”的简称--\n"
    .string "指的是最初收服它的训练家。$"

CeladonCity_DepartmentStore_3F_Text_BuddyTradingKangaskhanForHaunter::
	.string "好极了！\p"
	.string "我的朋友打算用他的\n"
	.string "袋兽和我的鬼斯通交换！$"

CeladonCity_DepartmentStore_3F_Text_HaunterEvolvedOnTrade::
    .string "来吧，鬼斯通！\p"
    .string "我喜欢鬼斯通！\n"
    .string "我一直在收集它！\p"
    .string "啊？\p"
    .string "鬼斯通在通讯后变成了\n"
    .string "另一种宝可梦！$"

CeladonCity_DepartmentStore_3F_Text_CanIdentifyTradeMonsByID::
    .string "你可以通过ID号码\n"
    .string "来辨识通讯交换来的宝可梦。$"

CeladonCity_DepartmentStore_3F_Text_ItsSuperNES::
    .string "这是一个超级红白机。$"

CeladonCity_DepartmentStore_3F_Text_AnRPG::
	.string "一款角色扮演游戏！\n"
	.string "现在可不是玩游戏的时候！$"

CeladonCity_DepartmentStore_3F_Text_SportsGame::
    .string "一款体育游戏！\n"
    .string "是爸爸喜欢的游戏！$"

CeladonCity_DepartmentStore_3F_Text_PuzzleGame::
    .string "一款拼图游戏！\n"
    .string "看起来很有趣！$"

CeladonCity_DepartmentStore_3F_Text_FightingGame::
    .string "一款格斗游戏！\n"
    .string "看上去很过瘾！$"

CeladonCity_DepartmentStore_3F_Text_TVGameShop::
    .string "三楼：电玩商店$"

CeladonCity_DepartmentStore_3F_Text_RedGreenBothArePokemon::
    .string "火红和叶绿！\n"
    .string "都是精灵宝可梦游戏！$"

Text_CounterTeach::
    .string "嗨，你好！\n"
    .string "我终于把精灵宝可梦通关了。\p"
    .string "你还没通关吗？\n"
    .string "我教你个不错的技能怎么样？\p"
    .string "这个技能叫作双倍奉还。\p"
    .string "提醒你，\n"
    .string "这不是我唯一依靠的技能！$"

Text_CounterDeclined::
    .string "你没兴趣学啊？\n"
    .string "要是改变主意了就来找我吧。$"

Text_CounterWhichMon::
    .string "我该让哪只宝可梦学双倍奉还呢？$"

Text_CounterTaught::
    .string "你在用我教给你宝可梦的双倍奉还技能吗？$"
