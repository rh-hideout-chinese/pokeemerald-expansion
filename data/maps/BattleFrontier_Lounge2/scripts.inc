BattleFrontier_Lounge2_MapScripts::
	.byte 0

@ This NPC gives hints about a random facility or battle mode.
@ For battle modes he gives generic advice
@ For facilities, depending on how far the player has progressed he will say either
@    The name of the Frontier Brain there
@    The type and description of the 3 pokemon they use in their silver battle
@    The type and description of the 3 pokemon they use in their gold battle
BattleFrontier_Lounge2_EventScript_FrontierManiac::
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_MANIAC, BattleFrontier_Lounge2_EventScript_AlreadyMetManiac
	setflag FLAG_MET_BATTLE_FRONTIER_MANIAC
	msgbox BattleFrontier_Lounge2_Text_FrontierManiacIntro, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_AlreadyMetManiac::
	msgbox BattleFrontier_Lounge2_Text_SwingByForTheLatestWord, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_GiveAdvice::
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_SINGLES, BattleFrontier_Lounge2_EventScript_BufferSingle
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_DOUBLES, BattleFrontier_Lounge2_EventScript_BufferDouble
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_MULTIS, BattleFrontier_Lounge2_EventScript_BufferMulti
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BufferMultiLink
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_BufferBattleDome
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_FACTORY, BattleFrontier_Lounge2_EventScript_BufferBattleFactory
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PALACE, BattleFrontier_Lounge2_EventScript_BufferBattlePalace
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_ARENA, BattleFrontier_Lounge2_EventScript_BufferBattleArena
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PIKE, BattleFrontier_Lounge2_EventScript_BufferBattlePike
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PYRAMID, BattleFrontier_Lounge2_EventScript_BufferBattlePyramid
@ <= FRONTIER_MANIAC_TOWER_LINK is any Battle Tower mode
	call_if_le VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BattleTowerNews
@ >= FRONTIER_MANIAC_DOME is any facility other than Battle Tower
	call_if_ge VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_FacilityNews
	special ShowFrontierManiacMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge2_EventScript_BattleTowerNews::
	msgbox BattleFrontier_Lounge2_Text_BattleTowerIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_FacilityNews::
	msgbox BattleFrontier_Lounge2_Text_FacilityIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_BufferSingle::
	bufferstdstring STR_VAR_1, STDSTRING_SINGLE
	return

BattleFrontier_Lounge2_EventScript_BufferDouble::
	bufferstdstring STR_VAR_1, STDSTRING_DOUBLE
	return

BattleFrontier_Lounge2_EventScript_BufferMulti::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI
	return

BattleFrontier_Lounge2_EventScript_BufferMultiLink::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI_LINK
	return

BattleFrontier_Lounge2_EventScript_BufferBattleDome::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_DOME
	return

BattleFrontier_Lounge2_EventScript_BufferBattleFactory::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_FACTORY
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePalace::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PALACE
	return

BattleFrontier_Lounge2_EventScript_BufferBattleArena::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_ARENA
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePike::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PIKE
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePyramid::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PYRAMID
	return

BattleFrontier_Lounge2_EventScript_Maniac1::
	lock
	msgbox BattleFrontier_Lounge2_Text_NewsGatheringPower, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowersOfObservation, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac3::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_TriathleteF::
	msgbox BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe, MSGBOX_NPC
	end

BattleFrontier_Lounge2_Text_FrontierManiacIntro::
    .string "嗨！我是对战开拓区\n消息最灵通的人，\p你可以叫我开拓区迷。\p只要看一眼我就知道你是个训练家，\n对不？\p我很高兴可以和你分享在\n对战开拓区收集的最新最热的新闻。$"

BattleFrontier_Lounge2_Text_SwingByForTheLatestWord::
    .string "嗨！你来是想知道最新的\n消息吗？好吧！$"

@ Unused
BattleFrontier_Lounge2_Text_MyInformationsBeenUsefulRight::
    .string "哇喔？哇喔？哇喔？\p我的情报对你来说\n非常有用，是吧？$"

BattleFrontier_Lounge2_Text_FacilityIsHottest::
    .string "让我想想……\p现在好像{STR_VAR_1}是\n最热门的地方。$"

BattleFrontier_Lounge2_Text_BattleTowerIsHottest::
    .string "让我想想……\p现在好像对战塔\n{STR_VAR_1}是最热门的。$"

BattleFrontier_Lounge2_Text_SalonMaidenIsThere::
    .string "告诉你个秘密！\p被亚希达称作开拓区大脑\n的顶级训练家之一现在就在那里。\p那个地方就是这个名叫对战塔大君的\n神秘的训练家管理的。$"

BattleFrontier_Lounge2_Text_SalonMaidenSilverMons::
    .string "你跟对战塔大君交过手了吗？\p一开始她试对手的实力的时候，\n通常都会用这些宝可梦：\p超能力属性的超能宝可梦，\n火属性的火山宝可梦，\l和一般属性的睡眠宝可梦。$"

BattleFrontier_Lounge2_Text_SalonMaidenGoldMons::
    .string "你跟认真起来的对战塔大君\n交过手了吗？\p她全力出手的时候，\n通常都会用这些宝可梦：\p龙和超能力属性的长寿宝可梦，\n电属性的闪电宝可梦，\l还有一般属性的睡眠宝可梦。$"

BattleFrontier_Lounge2_Text_DomeAceIsThere::
    .string "告诉你个秘密！\p被亚希达称作开拓之脑\n的顶级训练家之一现在就在那里。\p那里就是这个名叫巨蛋超级巨星的\n如火般的训练家管理的。$"

BattleFrontier_Lounge2_Text_DomeAceSilverMons::
    .string "你跟巨蛋超级巨星交过手了吗？\p他没认真起来的时候，\n通常都会用这些宝可梦：\p龙和飞行的龙宝可梦，\n水和地面的泥鱼宝可梦，\l还有火和飞行的火焰宝可梦。$"

BattleFrontier_Lounge2_Text_DomeAceGoldMons::
    .string "你跟认真起来的巨蛋超级巨星\n交过手了吗？\p当他把自己的策略完全展示的时候，\n通常都会用这些宝可梦：\p龙和飞行的古代宝可梦，\n水和地面的泥鱼宝可梦，\l还有钢铁和超能力属性的铁腿\l宝可梦。$"

BattleFrontier_Lounge2_Text_FactoryHeadIsThere::
    .string "告诉你个秘密！\p被亚希达称作开拓之脑\n的顶级训练家之一现在就在那里。\p那个地方就是这个名叫工厂头目的\n令人无法捉摸的训练家管理的。$"

BattleFrontier_Lounge2_Text_FactoryHeadSilverMons::
    .string "你跟工厂头目\n交过手了吗？\p我想想……他开始战斗的时候，\n通常只是借三只宝可梦用。\p他和你在非常相似的\n条件下战斗。$"

BattleFrontier_Lounge2_Text_FactoryHeadGoldMons::
    .string "你跟认真起来的工厂头目\n交过手了吗？\p就算他认真起来了，\n他还是用借来的宝可梦战斗。\p他是和你在完全\n相同的条件下战斗。$"

BattleFrontier_Lounge2_Text_PikeQueenIsThere::
    .string "告诉你个秘密！\p被亚希达称作开拓之脑\n的顶级训练家之一现在就在那里。\p那个地方就是这个名叫水管皇后的\n可怕的训练家管理的。$"

BattleFrontier_Lounge2_Text_PikeQueenSilverMons::
    .string "你跟水管皇后\n交过手了吗？\p据说她心情好的时候，\n通常都会用这些宝可梦：\p毒的牙蛇宝可梦，\n虫和岩石的模型宝可梦，\l还有水属性的温和的宝可梦。$"

BattleFrontier_Lounge2_Text_PikeQueenGoldMons::
    .string "你跟认真起来的水管皇后\n交过手了吗？\p据说她非常生气的时候，\n通常都会用这些宝可梦：\p毒属性的牙蛇宝可梦，\n钢铁和地面的钢蛇宝可梦，\l还有水和飞行属性的残暴\l宝可梦。$"

BattleFrontier_Lounge2_Text_ArenaTycoonIsThere::
    .string "告诉你个秘密！\p被亚希达称作开拓之脑\n的顶级训练家之一现在就在那里。\p那个地方就是这个名叫竞技场主将的\n可爱的训练家管理的。$"

BattleFrontier_Lounge2_Text_ArenaTycoonSilverMons::
    .string "你跟竞技场主将\n交过手了吗？\p一开始她估计敌方实力的时候，\n大概会用这些宝可梦：\p虫和格斗的独角宝可梦，\n恶属性的月光宝可梦，\l还有虫和鬼怪的躯壳宝可梦。$"

BattleFrontier_Lounge2_Text_ArenaTycoonGoldMons::
    .string "你跟认真起来的竞技场主将\n交过手了吗？\p她在卫冕战里\n大概会用这些宝可梦：\p恶属性的月光宝可梦，\n鬼怪和毒的影子宝可梦，\l还有草和格斗属性的\l蘑菇宝可梦。$"

BattleFrontier_Lounge2_Text_PalaceMavenIsThere::
    .string "告诉你个秘密！\p被亚希达称作开拓之脑\n的顶级训练家之一现在就在那里。\p那个地方就是这个名叫宫殿守护者的\n对人很凶的训练家管理的。$"

BattleFrontier_Lounge2_Text_PalaceMavenSilverMons::
    .string "你跟宫殿守护者\n交过手了吗？\p据说他测试对手的心的时候，\n通常会用这些宝可梦：\p毒和飞行属性的蝙蝠宝可梦，\n一般属性的懒惰宝可梦，还有\l水和冰属性的传送宝可梦。$"

BattleFrontier_Lounge2_Text_PalaceMavenGoldMons::
    .string "你跟认真起来的宫殿守护者\n交过手了吗？\p据说他把精力全部集中到战斗的时候，\n通常会使用这些宝可梦：\p火属性的传说宝可梦，\n一般属性的懒惰宝可梦，\l还有水属性的极光宝可梦。$"

BattleFrontier_Lounge2_Text_PyramidKingIsThere::
    .string "告诉你个秘密！\p被亚希达称作开拓之脑\n的顶级训练家之一现在就在那里。\p那个地方就是这个名叫金字塔法老的\n热情如火的训练家管理的。$"

BattleFrontier_Lounge2_Text_PyramidKingSilverMons::
    .string "你跟金字塔法老\n交过手了吗？\p他试验敌方实力的时候，\n通常都会用这些宝可梦：\p岩石属性的石顶宝可梦，\n冰属性的冰山宝可梦，\l还有钢属性的铁宝可梦。$"

BattleFrontier_Lounge2_Text_PyramidKingGoldMons::
    .string "你跟认真起来的金字塔法老\n交过手了吗？\p他的热情燃烧起来的时候，\n通常都会用这些宝可梦：\p冰和飞行的冰冻宝可梦，\n电和飞行的电宝可梦，\l还有火和飞行属性的火焰\l宝可梦。$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice1::
    .string "确实，有些地方也可以\n进行双打对战，\p不过在对战塔的双人\n对战房间里，这可是最基本的！\p你可以在那里学习\n如何在对战开拓区\l进行双打对战。$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice2::
    .string "在这里战斗不要大意。\p听说有些训练家\n可是专门为了双打对战\l而培育宝可梦的。$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice3::
    .string "当你熟悉了这里的\n双打对战之后，\l就去试着挑战其他地方的\l双打对战吧。$"

BattleFrontier_Lounge2_Text_MultiBattleAdvice::
    .string "对战沙龙里聚集了\n各种各样的训练家。\p想想吧——你可能会碰上\n你的朋友或粉丝！\l要好好注意周围啊！$"

BattleFrontier_Lounge2_Text_LinkMultiBattleAdvice::
    .string "如果碰到了朋友，就去\n联线多人对战房间吧。\p有一个很厉害的朋友在旁边的话，\n就有可能碰上很强的对手！$"

BattleFrontier_Lounge2_Text_NewsGatheringPower::
    .string "收集消息好厉害！\n老师果然非同一般！$"

BattleFrontier_Lounge2_Text_AmazingPowersOfObservation::
    .string "调查资料好厉害！\n老师果然非同一般！$"

BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion::
    .string "说服别人好厉害！\n老师果然非同一般！$"

BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe::
    .string "……这里是哪儿？\n好可怕……$"

