// multichoice lists
static const struct MenuAction MultichoiceList_BrineyOnDewford[] =
{
    {COMPOUND_STRING("橙华市")},
    {COMPOUND_STRING("凯那市")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_EnterInfo[] =
{
    {COMPOUND_STRING("报名")},
    {gText_Info2},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ContestInfo[] =
{
    {COMPOUND_STRING("华丽大赛是什么?")},
    {COMPOUND_STRING("华丽大赛的类型")},
    {COMPOUND_STRING("级别")},
    {gText_Cancel2},
};

static const struct MenuAction MultichoiceList_ContestType[] =
{
    {gText_CoolnessContest},
    {gText_BeautyContest},
    {gText_CutenessContest},
    {gText_SmartnessContest},
    {gText_ToughnessContest},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_BasePCWithRegistry[] =
{
    {gText_Decoration2},
    {gText_PackUp},
    {gText_Registry},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_BasePCNoRegistry[] =
{
    {gText_Decoration2},
    {gText_PackUp},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_RegisterMenu[] =
{
    {gMenuText_Register},
    {gText_Registry},
    {gText_Information},
    {gText_Cancel2},
};

static const struct MenuAction MultichoiceList_Bike[] =
{
    {COMPOUND_STRING("音速")},
    {COMPOUND_STRING("越野")},
};

static const struct MenuAction MultichoiceList_StatusInfo[] =
{
    {COMPOUND_STRING("中毒")},
    {COMPOUND_STRING("麻痹")},
    {COMPOUND_STRING("睡眠")},
    {COMPOUND_STRING("灼伤")},
    {COMPOUND_STRING("冰冻")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_BrineyOffDewford[] =
{
    {COMPOUND_STRING("武斗镇")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ViewedPaintings[] =
{
    {COMPOUND_STRING("看到了")},
    {COMPOUND_STRING("还没有")},
};

static const struct MenuAction MultichoiceList_YesNoInfo2[] =
{
    {gText_Yes},
    {gText_No},
    {gText_Info2},
};

static const struct MenuAction MultichoiceList_ChallengeInfo[] =
{
    {COMPOUND_STRING("挑战")},
    {COMPOUND_STRING("说明")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_LevelMode[] =
{
    {gText_Lv50},
    {gText_OpenLevel},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_Mechadoll1_Q1[] =
{
    {COMPOUND_STRING("走路草")},
    {COMPOUND_STRING("土狼犬")},
    {COMPOUND_STRING("傲骨燕")},
};

static const struct MenuAction MultichoiceList_Mechadoll1_Q2[] =
{
    {COMPOUND_STRING("露力丽")},
    {COMPOUND_STRING("莲叶童子")},
    {COMPOUND_STRING("长翅鸥")},
};

static const struct MenuAction MultichoiceList_Mechadoll1_Q3[] =
{
    {COMPOUND_STRING("毒粉蛾")},
    {COMPOUND_STRING("超音蝠")},
    {COMPOUND_STRING("土居忍士")},
};

static const struct MenuAction MultichoiceList_Mechadoll2_Q1[] =
{
    {COMPOUND_STRING("拉鲁拉丝")},
    {COMPOUND_STRING("蛇纹熊")},
    {COMPOUND_STRING("懒人獭")},
};

static const struct MenuAction MultichoiceList_Mechadoll2_Q2[] =
{
    {COMPOUND_STRING("土狼犬")},
    {COMPOUND_STRING("蘑蘑菇")},
    {COMPOUND_STRING("蛇纹熊")},
};

static const struct MenuAction MultichoiceList_Mechadoll2_Q3[] =
{
    {COMPOUND_STRING("土狼犬")},
    {COMPOUND_STRING("超音蝠")},
    {COMPOUND_STRING("利牙鱼")},
};

static const struct MenuAction MultichoiceList_Mechadoll3_Q1[] =
{
    {COMPOUND_STRING("灼伤药")},
    {COMPOUND_STRING("港口邮件")},
    {COMPOUND_STRING("价格相等")},
};

static const struct MenuAction MultichoiceList_Mechadoll3_Q2[] =
{
    {COMPOUND_STRING("¥60")},
    {COMPOUND_STRING("¥55")},
    {COMPOUND_STRING("不会剩下")},
};

static const struct MenuAction MultichoiceList_Mechadoll3_Q3[] =
{
    {COMPOUND_STRING("花得更多")},
    {COMPOUND_STRING("花得更少")},
    {COMPOUND_STRING("价格相同")},
};

static const struct MenuAction MultichoiceList_Mechadoll4_Q1[] =
{
    {COMPOUND_STRING("男人")},
    {COMPOUND_STRING("女人")},
    {COMPOUND_STRING("都不是")},
};

static const struct MenuAction MultichoiceList_Mechadoll4_Q2[] =
{
    {COMPOUND_STRING("老爷爷")},
    {COMPOUND_STRING("老奶奶")},
    {COMPOUND_STRING("相等")},
};

static const struct MenuAction MultichoiceList_Mechadoll4_Q3[] =
{
    {COMPOUND_STRING("没有")},
    {COMPOUND_STRING("1")},
    {COMPOUND_STRING("2")},
};

static const struct MenuAction MultichoiceList_Mechadoll5_Q1[] =
{
    {COMPOUND_STRING("2")},
    {COMPOUND_STRING("3")},
    {COMPOUND_STRING("4")},
};

static const struct MenuAction MultichoiceList_Mechadoll5_Q2[] =
{
    {COMPOUND_STRING("6")},
    {COMPOUND_STRING("7")},
    {COMPOUND_STRING("8")},
};

static const struct MenuAction MultichoiceList_Mechadoll5_Q3[] =
{
    {COMPOUND_STRING("6")},
    {COMPOUND_STRING("7")},
    {COMPOUND_STRING("8")},
};

static const struct MenuAction MultichoiceList_VendingMachine[] =
{
    {COMPOUND_STRING("美味之水{CLEAR_TO 0x48}¥200")},
    {COMPOUND_STRING("劲爽汽水{CLEAR_TO 0x48}¥300")},
    {COMPOUND_STRING("果汁牛奶{CLEAR_TO 0x48}¥350")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_MachBikeInfo[] =
{
    {COMPOUND_STRING("如何骑行")},
    {COMPOUND_STRING("如何转弯")},
    {COMPOUND_STRING("流沙坡")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_AcroBikeInfo[] =
{
    {COMPOUND_STRING("单轮特技")},
    {COMPOUND_STRING("小跳")},
    {COMPOUND_STRING("跳")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_Satisfaction[] =
{
    {COMPOUND_STRING("满意")},
    {COMPOUND_STRING("不满意")},
};

static const struct MenuAction MultichoiceList_SternDeepSea[] =
{
    {COMPOUND_STRING("深海之牙")},
    {COMPOUND_STRING("深海鳞片")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_UnusedAshVendor[] =
{
    {COMPOUND_STRING("蓝色玻璃哨")},
    {COMPOUND_STRING("黄色玻璃哨")},
    {COMPOUND_STRING("红色玻璃哨")},
    {COMPOUND_STRING("白色玻璃哨")},
    {COMPOUND_STRING("黑色玻璃哨")},
    {COMPOUND_STRING("玻璃凳子")},
    {COMPOUND_STRING("玻璃桌子")},
    {gText_Cancel2},
};

static const struct MenuAction MultichoiceList_GameCornerDolls[] =
{
    {COMPOUND_STRING("木守宫玩偶 1000代币")},
    {COMPOUND_STRING("火稚鸡玩偶 1000代币")},
    {COMPOUND_STRING("水跃鱼玩偶 1000代币")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_GameCornerTMs[] =
{
    {COMPOUND_STRING("TM32{CLEAR_TO 0x48}1500代币")},
    {COMPOUND_STRING("TM29{CLEAR_TO 0x48}3500代币")},
    {COMPOUND_STRING("TM35{CLEAR_TO 0x48}4000代币")},
    {COMPOUND_STRING("TM24{CLEAR_TO 0x48}4000代币")},
    {COMPOUND_STRING("TM13{CLEAR_TO 0x48}4000代币")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_GameCornerCoins[] =
{
    {COMPOUND_STRING(" 50代币   ¥1000")},
    {COMPOUND_STRING("500代币  ¥10000")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_HowsFishing[] =
{
    {COMPOUND_STRING("好得很")},
    {COMPOUND_STRING("不太好")},
};

static const struct MenuAction MultichoiceList_SSTidalSlateportWithBF[] =
{
    {gText_LilycoveCity},
    {gText_BattleFrontier},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_SSTidalBattleFrontier[] =
{
    {gText_SlateportCity},
    {gText_LilycoveCity},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_RightLeft[] =
{
    {COMPOUND_STRING("右")},
    {COMPOUND_STRING("左")},
};

static const struct MenuAction MultichoiceList_SSTidalSlateportNoBF[] =
{
    {gText_LilycoveCity},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_Floors[] =
{
    {gText_5F},
    {gText_4F},
    {gText_3F},
    {gText_2F},
    {gText_1F},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ShardsR[] =
{
    {gText_RedShard},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ShardsY[] =
{
    {gText_YellowShard},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ShardsRY[] =
{
    {gText_RedShard},
    {gText_YellowShard},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ShardsB[] =
{
    {gText_BlueShard},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ShardsRB[] =
{
    {gText_RedShard},
    {gText_BlueShard},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ShardsYB[] =
{
    {gText_YellowShard},
    {gText_BlueShard},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ShardsRYB[] =
{
    {gText_RedShard},
    {gText_YellowShard},
    {gText_BlueShard},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ShardsG[] =
{
    {gText_GreenShard},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ShardsRG[] =
{
    {gText_RedShard},
    {gText_GreenShard},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ShardsYG[] =
{
    {gText_YellowShard},
    {gText_GreenShard},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ShardsRYG[] =
{
    {gText_RedShard},
    {gText_YellowShard},
    {gText_GreenShard},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ShardsBG[] =
{
    {gText_BlueShard},
    {gText_GreenShard},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ShardsRBG[] =
{
    {gText_RedShard},
    {gText_BlueShard},
    {gText_GreenShard},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ShardsYBG[] =
{
    {gText_YellowShard},
    {gText_BlueShard},
    {gText_GreenShard},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ShardsRYBG[] =
{
    {gText_RedShard},
    {gText_YellowShard},
    {gText_BlueShard},
    {gText_GreenShard},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_TourneyWithRecord[] =
{
    {gText_Opponent},
    {gText_Tourney_Tree},
    {gText_ReadyToStart},
    {gText_Record2},
    {gText_Rest},
    {gText_Retire},
};

static const struct MenuAction MultichoiceList_TourneyNoRecord[] =
{
    {gText_Opponent},
    {gText_Tourney_Tree},
    {gText_ReadyToStart},
    {gText_Rest},
    {gText_Retire},
};

static const struct MenuAction MultichoiceList_Tent[] =
{
    {COMPOUND_STRING("红帐篷")},
    {COMPOUND_STRING("蓝帐篷")},
};

static const struct MenuAction MultichoiceList_LinkServicesNoBerry[] =
{
    {gText_TradeCenter},
    {gText_Colosseum},
    {gText_RecordCorner},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_YesNoInfo[] =
{
    {gText_Yes},
    {gText_No},
    {gText_Info2},
};

static const struct MenuAction MultichoiceList_BattleMode[] =
{
    {COMPOUND_STRING("单打对战")},
    {COMPOUND_STRING("双打对战")},
    {COMPOUND_STRING("多人对战")},
    {gText_Info2},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_LinkServicesNoRecord[] =
{
    {gText_TradeCenter},
    {gText_Colosseum},
    {gText_BerryCrush3},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_LinkServicesAll[] =
{
    {gText_TradeCenter},
    {gText_Colosseum},
    {gText_RecordCorner},
    {gText_BerryCrush3},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_LinkServicesNoRecordBerry[] =
{
    {gText_TradeCenter},
    {gText_Colosseum},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_WirelessMinigame[] =
{
    {COMPOUND_STRING("宝可梦跳绳")},
    {COMPOUND_STRING("嘟嘟利摘树果")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_LinkLeader[] =
{
    {COMPOUND_STRING("加入队伍")},
    {COMPOUND_STRING("成为队长")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ContestRank[] =
{
    {COMPOUND_STRING("普通级")},
    {COMPOUND_STRING("高手级")},
    {COMPOUND_STRING("究极级")},
    {COMPOUND_STRING("大师级")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_FrontierItemChoose[] =
{
    {COMPOUND_STRING("对战包包")},
    {COMPOUND_STRING("持有物")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_LinkContestInfo[] =
{
    {COMPOUND_STRING("联机华丽大赛")},
    {COMPOUND_STRING("关于E-模式")},
    {COMPOUND_STRING("关于G-模式")},
    {gText_Cancel2},
};

static const struct MenuAction MultichoiceList_LinkContestMode[] =
{
    {COMPOUND_STRING("E-模式")},
    {COMPOUND_STRING("G-模式")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_ForcedStartMenu[] =
{
    {gText_MenuOptionPokedex},
    {gText_MenuOptionPokemon},
    {gText_MenuOptionBag},
    {gText_MenuOptionPokenav},
    {gText_Blank}, // blank because it's filled by the player's name
    {gText_MenuOptionSave},
    {gText_MenuOptionOption},
    {gText_MenuOptionExit},
};

static const struct MenuAction MultichoiceList_FrontierGamblerBet[] =
{
    {COMPOUND_STRING("  5BP")},
    {COMPOUND_STRING("10BP")},
    {COMPOUND_STRING("15BP")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_UnusedSSTidal1[] =
{
    {gText_SouthernIsland},
    {gText_BirthIsland},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_UnusedSSTidal2[] =
{
    {gText_SouthernIsland},
    {gText_FarawayIsland},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_UnusedSSTidal3[] =
{
    {gText_BirthIsland},
    {gText_FarawayIsland},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_UnusedSSTidal4[] =
{
    {gText_SouthernIsland},
    {gText_BirthIsland},
    {gText_FarawayIsland},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_Fossil[] =
{
    {COMPOUND_STRING("爪子化石")},
    {COMPOUND_STRING("根状化石")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_YesNo[] =
{
    {gText_Yes},
    {COMPOUND_STRING("否")},
};

static const struct MenuAction MultichoiceList_FrontierRules[] =
{
    {COMPOUND_STRING("两种模式")},
    {COMPOUND_STRING("50级")},
    {COMPOUND_STRING("自由级")},
    {COMPOUND_STRING("宝可梦属性&编号")},
    {COMPOUND_STRING("持有物")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_FrontierPassInfo[] =
{
    {COMPOUND_STRING("象征")},
    {COMPOUND_STRING("记录")},
    {COMPOUND_STRING("战斗点数")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_BattleArenaRules[] =
{
    {gText_BattleRules},
    {gText_JudgeMind},
    {gText_JudgeSkill},
    {gText_JudgeBody},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_BattleTowerRules[] =
{
    {COMPOUND_STRING("对战塔信息")},
    {COMPOUND_STRING("对战宝可梦")},
    {COMPOUND_STRING("对战沙龙")},
    {COMPOUND_STRING("多人联机")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_BattleDomeRules[] =
{
    {COMPOUND_STRING("对手")},
    {COMPOUND_STRING("对阵树")},
    {COMPOUND_STRING("双双击倒")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_BattleFactoryRules[] =
{
    {gText_BasicRules},
    {gText_SwapPartners},
    {gText_SwapNumber},
    {gText_SwapNotes},
    {COMPOUND_STRING("自由级")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_BattlePalaceRules[] =
{
    {gText_BattleBasics},
    {gText_PokemonNature},
    {gText_PokemonMoves},
    {gText_Underpowered},
    {gText_WhenInDanger},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_BattlePyramidRules[] =
{
    {COMPOUND_STRING("金字塔：宝可梦")},
    {COMPOUND_STRING("金字塔：训练家")},
    {COMPOUND_STRING("金字塔：迷宫")},
    {COMPOUND_STRING("对战包包")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_BattlePikeRules[] =
{
    {COMPOUND_STRING("导航器和包包")},
    {COMPOUND_STRING("持有物")},
    {COMPOUND_STRING("宝可梦顺序")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_GoOnRecordRestRetire[] =
{
    {gText_GoOn},
    {gText_Record2},
    {gText_Rest},
    {gText_Retire},
};

static const struct MenuAction MultichoiceList_GoOnRestRetire[] =
{
    {gText_GoOn},
    {gText_Rest},
    {gText_Retire},
};

static const struct MenuAction MultichoiceList_GoOnRecordRetire[] =
{
    {gText_GoOn},
    {gText_Record2},
    {gText_Retire},
};

static const struct MenuAction MultichoiceList_GoOnRetire[] =
{
    {gText_GoOn},
    {gText_Retire},
};

static const struct MenuAction MultichoiceList_TVLati[] =
{
    {COMPOUND_STRING("红色")},
    {COMPOUND_STRING("蓝色")},
};

static const struct MenuAction MultichoiceList_BattleTowerFeelings[] =
{
    {COMPOUND_STRING("我现在要对战了!")},
    {COMPOUND_STRING("赢了!")},
    {COMPOUND_STRING("输了!")},
    {COMPOUND_STRING("我不想说。")},
};

static const struct MenuAction MultichoiceList_WheresRayquaza[] =
{
    {COMPOUND_STRING("觉醒神殿")},
    {COMPOUND_STRING("送神山")},
    {COMPOUND_STRING("天空之柱")},
    {COMPOUND_STRING("不记得了")},
};

static const struct MenuAction MultichoiceList_SlateportTentRules[] =
{
    {gText_BasicRules},
    {gText_SwapPartners},
    {gText_SwapNumber},
    {gText_SwapNotes},
    {gText_BattlePokemon},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_FallarborTentRules[] =
{
    {gText_BattleTrainers},
    {gText_BattleRules},
    {gText_JudgeMind},
    {gText_JudgeSkill},
    {gText_JudgeBody},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_TagMatchType[] =
{
    {gText_NormalTagMatch},
    {gText_VarietyTagMatch},
    {gText_UniqueTagMatch},
    {gText_ExpertTagMatch},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_BerryPlot[] =
{
    {COMPOUND_STRING("加肥料")},
    {COMPOUND_STRING("种树果")},
    {gText_Exit},
};

static const struct MenuAction MultichoiceList_Exit[] =
{
    {gText_Exit},
};

struct MultichoiceListStruct
{
    const struct MenuAction *list;
    u8 count;
};

static const struct MultichoiceListStruct sMultichoiceLists[] =
{
    [MULTI_BRINEY_ON_DEWFORD]          = MULTICHOICE(MultichoiceList_BrineyOnDewford),
    [MULTI_PC]                         = MULTICHOICE(MultichoiceList_Exit),
    [MULTI_ENTERINFO]                  = MULTICHOICE(MultichoiceList_EnterInfo),
    [MULTI_CONTEST_INFO]               = MULTICHOICE(MultichoiceList_ContestInfo),
    [MULTI_CONTEST_TYPE]               = MULTICHOICE(MultichoiceList_ContestType),
    [MULTI_BASE_PC_NO_REGISTRY]        = MULTICHOICE(MultichoiceList_BasePCNoRegistry),
    [MULTI_BASE_PC_WITH_REGISTRY]      = MULTICHOICE(MultichoiceList_BasePCWithRegistry),
    [MULTI_REGISTER_MENU]              = MULTICHOICE(MultichoiceList_RegisterMenu),
    [MULTI_SSTIDAL_LILYCOVE]           = MULTICHOICE(MultichoiceList_Exit),
    [MULTI_UNUSED_9]                   = MULTICHOICE(MultichoiceList_Exit),
    [MULTI_UNUSED_10]                  = MULTICHOICE(MultichoiceList_Exit),
    [MULTI_FRONTIER_PASS_INFO]         = MULTICHOICE(MultichoiceList_FrontierPassInfo),
    [MULTI_BIKE]                       = MULTICHOICE(MultichoiceList_Bike),
    [MULTI_STATUS_INFO]                = MULTICHOICE(MultichoiceList_StatusInfo),
    [MULTI_BRINEY_OFF_DEWFORD]         = MULTICHOICE(MultichoiceList_BrineyOffDewford),
    [MULTI_UNUSED_15]                  = MULTICHOICE(MultichoiceList_Exit),
    [MULTI_VIEWED_PAINTINGS]           = MULTICHOICE(MultichoiceList_ViewedPaintings),
    [MULTI_YESNOINFO]                  = MULTICHOICE(MultichoiceList_YesNoInfo),
    [MULTI_BATTLE_MODE]                = MULTICHOICE(MultichoiceList_BattleMode),
    [MULTI_UNUSED_19]                  = MULTICHOICE(MultichoiceList_Exit),
    [MULTI_YESNOINFO_2]                = MULTICHOICE(MultichoiceList_YesNoInfo2),
    [MULTI_UNUSED_21]                  = MULTICHOICE(MultichoiceList_Exit),
    [MULTI_UNUSED_22]                  = MULTICHOICE(MultichoiceList_Exit),
    [MULTI_CHALLENGEINFO]              = MULTICHOICE(MultichoiceList_ChallengeInfo),
    [MULTI_LEVEL_MODE]                 = MULTICHOICE(MultichoiceList_LevelMode),
    [MULTI_MECHADOLL1_Q1]              = MULTICHOICE(MultichoiceList_Mechadoll1_Q1),
    [MULTI_MECHADOLL1_Q2]              = MULTICHOICE(MultichoiceList_Mechadoll1_Q2),
    [MULTI_MECHADOLL1_Q3]              = MULTICHOICE(MultichoiceList_Mechadoll1_Q3),
    [MULTI_MECHADOLL2_Q1]              = MULTICHOICE(MultichoiceList_Mechadoll2_Q1),
    [MULTI_MECHADOLL2_Q2]              = MULTICHOICE(MultichoiceList_Mechadoll2_Q2),
    [MULTI_MECHADOLL2_Q3]              = MULTICHOICE(MultichoiceList_Mechadoll2_Q3),
    [MULTI_MECHADOLL3_Q1]              = MULTICHOICE(MultichoiceList_Mechadoll3_Q1),
    [MULTI_MECHADOLL3_Q2]              = MULTICHOICE(MultichoiceList_Mechadoll3_Q2),
    [MULTI_MECHADOLL3_Q3]              = MULTICHOICE(MultichoiceList_Mechadoll3_Q3),
    [MULTI_MECHADOLL4_Q1]              = MULTICHOICE(MultichoiceList_Mechadoll4_Q1),
    [MULTI_MECHADOLL4_Q2]              = MULTICHOICE(MultichoiceList_Mechadoll4_Q2),
    [MULTI_MECHADOLL4_Q3]              = MULTICHOICE(MultichoiceList_Mechadoll4_Q3),
    [MULTI_MECHADOLL5_Q1]              = MULTICHOICE(MultichoiceList_Mechadoll5_Q1),
    [MULTI_MECHADOLL5_Q2]              = MULTICHOICE(MultichoiceList_Mechadoll5_Q2),
    [MULTI_MECHADOLL5_Q3]              = MULTICHOICE(MultichoiceList_Mechadoll5_Q3),
    [MULTI_UNUSED_40]                  = MULTICHOICE(MultichoiceList_Exit),
    [MULTI_UNUSED_41]                  = MULTICHOICE(MultichoiceList_Exit),
    [MULTI_VENDING_MACHINE]            = MULTICHOICE(MultichoiceList_VendingMachine),
    [MULTI_MACH_BIKE_INFO]             = MULTICHOICE(MultichoiceList_MachBikeInfo),
    [MULTI_ACRO_BIKE_INFO]             = MULTICHOICE(MultichoiceList_AcroBikeInfo),
    [MULTI_SATISFACTION]               = MULTICHOICE(MultichoiceList_Satisfaction),
    [MULTI_STERN_DEEPSEA]              = MULTICHOICE(MultichoiceList_SternDeepSea),
    [MULTI_UNUSED_ASH_VENDOR]          = MULTICHOICE(MultichoiceList_UnusedAshVendor),
    [MULTI_GAME_CORNER_DOLLS]          = MULTICHOICE(MultichoiceList_GameCornerDolls),
    [MULTI_GAME_CORNER_COINS]          = MULTICHOICE(MultichoiceList_GameCornerCoins),
    [MULTI_HOWS_FISHING]               = MULTICHOICE(MultichoiceList_HowsFishing),
    [MULTI_UNUSED_51]                  = MULTICHOICE(MultichoiceList_Exit),
    [MULTI_SSTIDAL_SLATEPORT_WITH_BF]  = MULTICHOICE(MultichoiceList_SSTidalSlateportWithBF),
    [MULTI_SSTIDAL_BATTLE_FRONTIER]    = MULTICHOICE(MultichoiceList_SSTidalBattleFrontier),
    [MULTI_RIGHTLEFT]                  = MULTICHOICE(MultichoiceList_RightLeft),
    [MULTI_GAME_CORNER_TMS]            = MULTICHOICE(MultichoiceList_GameCornerTMs),
    [MULTI_SSTIDAL_SLATEPORT_NO_BF]    = MULTICHOICE(MultichoiceList_SSTidalSlateportNoBF),
    [MULTI_FLOORS]                     = MULTICHOICE(MultichoiceList_Floors),
    [MULTI_SHARDS_R]                   = MULTICHOICE(MultichoiceList_ShardsR),
    [MULTI_SHARDS_Y]                   = MULTICHOICE(MultichoiceList_ShardsY),
    [MULTI_SHARDS_RY]                  = MULTICHOICE(MultichoiceList_ShardsRY),
    [MULTI_SHARDS_B]                   = MULTICHOICE(MultichoiceList_ShardsB),
    [MULTI_SHARDS_RB]                  = MULTICHOICE(MultichoiceList_ShardsRB),
    [MULTI_SHARDS_YB]                  = MULTICHOICE(MultichoiceList_ShardsYB),
    [MULTI_SHARDS_RYB]                 = MULTICHOICE(MultichoiceList_ShardsRYB),
    [MULTI_SHARDS_G]                   = MULTICHOICE(MultichoiceList_ShardsG),
    [MULTI_SHARDS_RG]                  = MULTICHOICE(MultichoiceList_ShardsRG),
    [MULTI_SHARDS_YG]                  = MULTICHOICE(MultichoiceList_ShardsYG),
    [MULTI_SHARDS_RYG]                 = MULTICHOICE(MultichoiceList_ShardsRYG),
    [MULTI_SHARDS_BG]                  = MULTICHOICE(MultichoiceList_ShardsBG),
    [MULTI_SHARDS_RBG]                 = MULTICHOICE(MultichoiceList_ShardsRBG),
    [MULTI_SHARDS_YBG]                 = MULTICHOICE(MultichoiceList_ShardsYBG),
    [MULTI_SHARDS_RYBG]                = MULTICHOICE(MultichoiceList_ShardsRYBG),
    [MULTI_TOURNEY_WITH_RECORD]        = MULTICHOICE(MultichoiceList_TourneyWithRecord),
    [MULTI_CABLE_CLUB_NO_RECORD_MIX]   = MULTICHOICE(MultichoiceList_LinkServicesNoRecordBerry),
    [MULTI_WIRELESS_NO_RECORD_BERRY]   = MULTICHOICE(MultichoiceList_LinkServicesNoRecordBerry),
    [MULTI_CABLE_CLUB_WITH_RECORD_MIX] = MULTICHOICE(MultichoiceList_LinkServicesNoBerry),
    [MULTI_WIRELESS_NO_BERRY]          = MULTICHOICE(MultichoiceList_LinkServicesNoBerry),
    [MULTI_WIRELESS_NO_RECORD]         = MULTICHOICE(MultichoiceList_LinkServicesNoRecord),
    [MULTI_WIRELESS_ALL_SERVICES]      = MULTICHOICE(MultichoiceList_LinkServicesAll),
    [MULTI_WIRELESS_MINIGAME]          = MULTICHOICE(MultichoiceList_WirelessMinigame),
    [MULTI_LINK_LEADER]                = MULTICHOICE(MultichoiceList_LinkLeader),
    [MULTI_CONTEST_RANK]               = MULTICHOICE(MultichoiceList_ContestRank),
    [MULTI_FRONTIER_ITEM_CHOOSE]       = MULTICHOICE(MultichoiceList_FrontierItemChoose),
    [MULTI_LINK_CONTEST_INFO]          = MULTICHOICE(MultichoiceList_LinkContestInfo),
    [MULTI_LINK_CONTEST_MODE]          = MULTICHOICE(MultichoiceList_LinkContestMode),
    [MULTI_FORCED_START_MENU]          = MULTICHOICE(MultichoiceList_ForcedStartMenu),
    [MULTI_FRONTIER_GAMBLER_BET]       = MULTICHOICE(MultichoiceList_FrontierGamblerBet),
    [MULTI_TENT]                       = MULTICHOICE(MultichoiceList_Tent),
    [MULTI_UNUSED_SSTIDAL_1]           = MULTICHOICE(MultichoiceList_UnusedSSTidal1),
    [MULTI_UNUSED_SSTIDAL_2]           = MULTICHOICE(MultichoiceList_UnusedSSTidal2),
    [MULTI_UNUSED_SSTIDAL_3]           = MULTICHOICE(MultichoiceList_UnusedSSTidal3),
    [MULTI_UNUSED_SSTIDAL_4]           = MULTICHOICE(MultichoiceList_UnusedSSTidal4),
    [MULTI_FOSSIL]                     = MULTICHOICE(MultichoiceList_Fossil),
    [MULTI_YESNO]                      = MULTICHOICE(MultichoiceList_YesNo),
    [MULTI_FRONTIER_RULES]             = MULTICHOICE(MultichoiceList_FrontierRules),
    [MULTI_BATTLE_ARENA_RULES]         = MULTICHOICE(MultichoiceList_BattleArenaRules),
    [MULTI_BATTLE_TOWER_RULES]         = MULTICHOICE(MultichoiceList_BattleTowerRules),
    [MULTI_BATTLE_DOME_RULES]          = MULTICHOICE(MultichoiceList_BattleDomeRules),
    [MULTI_BATTLE_FACTORY_RULES]       = MULTICHOICE(MultichoiceList_BattleFactoryRules),
    [MULTI_BATTLE_PALACE_RULES]        = MULTICHOICE(MultichoiceList_BattlePalaceRules),
    [MULTI_BATTLE_PYRAMID_RULES]       = MULTICHOICE(MultichoiceList_BattlePyramidRules),
    [MULTI_BATTLE_PIKE_RULES]          = MULTICHOICE(MultichoiceList_BattlePikeRules),
    [MULTI_GO_ON_RECORD_REST_RETIRE]   = MULTICHOICE(MultichoiceList_GoOnRecordRestRetire),
    [MULTI_GO_ON_REST_RETIRE]          = MULTICHOICE(MultichoiceList_GoOnRestRetire),
    [MULTI_GO_ON_RECORD_RETIRE]        = MULTICHOICE(MultichoiceList_GoOnRecordRetire),
    [MULTI_GO_ON_RETIRE]               = MULTICHOICE(MultichoiceList_GoOnRetire),
    [MULTI_TOURNEY_NO_RECORD]          = MULTICHOICE(MultichoiceList_TourneyNoRecord),
    [MULTI_TV_LATI]                    = MULTICHOICE(MultichoiceList_TVLati),
    [MULTI_BATTLE_TOWER_FEELINGS]      = MULTICHOICE(MultichoiceList_BattleTowerFeelings),
    [MULTI_WHERES_RAYQUAZA]            = MULTICHOICE(MultichoiceList_WheresRayquaza),
    [MULTI_SLATEPORT_TENT_RULES]       = MULTICHOICE(MultichoiceList_SlateportTentRules),
    [MULTI_FALLARBOR_TENT_RULES]       = MULTICHOICE(MultichoiceList_FallarborTentRules),
    [MULTI_TAG_MATCH_TYPE]             = MULTICHOICE(MultichoiceList_TagMatchType),
    [MULTI_BERRY_PLOT]                 = MULTICHOICE(MultichoiceList_BerryPlot),
};

const u8 *const gStdStrings[] =
{
    [STDSTRING_COOL] = gText_Cool,
    [STDSTRING_BEAUTY] = gText_Beauty,
    [STDSTRING_CUTE] = gText_Cute,
    [STDSTRING_SMART] = gText_Smart,
    [STDSTRING_TOUGH] = gText_Tough,
    [STDSTRING_NORMAL] = gText_Normal,
    [STDSTRING_SUPER] = gText_Super,
    [STDSTRING_HYPER] = gText_Hyper,
    [STDSTRING_MASTER] = gText_Master,
    [STDSTRING_COOL2] = gText_Cool2,
    [STDSTRING_BEAUTY2] = gText_Beauty2,
    [STDSTRING_CUTE2] = gText_Cute2,
    [STDSTRING_SMART2] = gText_Smart2,
    [STDSTRING_TOUGH2] = gText_Tough2,
    [STDSTRING_ITEMS] = gText_Items,
    [STDSTRING_KEYITEMS] = gText_Key_Items,
    [STDSTRING_POKEBALLS] = gText_Poke_Balls,
    [STDSTRING_TMHMS] = gText_TMs_Hms,
    [STDSTRING_BERRIES] = gText_Berries2,
    [STDSTRING_SINGLE] = gText_Single2,
    [STDSTRING_DOUBLE] = gText_Double2,
    [STDSTRING_MULTI] = gText_Multi,
    [STDSTRING_MULTI_LINK] = gText_MultiLink,
    [STDSTRING_BATTLE_TOWER] = gText_BattleTower2,
    [STDSTRING_BATTLE_DOME] = gText_BattleDome,
    [STDSTRING_BATTLE_FACTORY] = gText_BattleFactory,
    [STDSTRING_BATTLE_PALACE] = gText_BattlePalace,
    [STDSTRING_BATTLE_ARENA] = gText_BattleArena,
    [STDSTRING_BATTLE_PIKE] = gText_BattlePike,
    [STDSTRING_BATTLE_PYRAMID] = gText_BattlePyramid,
};

static const u8 sLinkServicesMultichoiceIds[] =
{
    MULTI_CABLE_CLUB_NO_RECORD_MIX,
    MULTI_WIRELESS_NO_RECORD_BERRY,
    MULTI_CABLE_CLUB_WITH_RECORD_MIX,
    MULTI_WIRELESS_NO_BERRY,
    MULTI_WIRELESS_NO_RECORD,
    MULTI_WIRELESS_ALL_SERVICES
};

static const u8 *const sPCNameStrings[] =
{
    gText_SomeonesPC,
    gText_LanettesPC,
    gText_PlayersPC,
    gText_LogOff,
};

static const u8 *const sLilycoveSSTidalDestinations[SSTIDAL_SELECTION_COUNT] =
{
    [SSTIDAL_SELECTION_SLATEPORT]       = gText_SlateportCity,
    [SSTIDAL_SELECTION_BATTLE_FRONTIER] = gText_BattleFrontier,
    [SSTIDAL_SELECTION_SOUTHERN_ISLAND] = gText_SouthernIsland,
    [SSTIDAL_SELECTION_NAVEL_ROCK]      = gText_NavelRock,
    [SSTIDAL_SELECTION_BIRTH_ISLAND]    = gText_BirthIsland,
    [SSTIDAL_SELECTION_FARAWAY_ISLAND]  = gText_FarawayIsland,
    [SSTIDAL_SELECTION_EXIT]            = gText_Exit,
};

static const u8 *const sCableClubOptions_WithRecordMix[] =
{
    CableClub_Text_TradeUsingLinkCable,
    CableClub_Text_BattleUsingLinkCable,
    CableClub_Text_RecordCornerUsingLinkCable,
    CableClub_Text_CancelSelectedItem,
};
static const u8 *const sWirelessOptionsNoBerryCrush[] =
{
    CableClub_Text_YouMayTradeHere,
    CableClub_Text_YouMayBattleHere,
    CableClub_Text_CanMixRecords,
    CableClub_Text_CancelSelectedItem,
};
static const u8 *const sWirelessOptions_NoRecordMix[] =
{
    CableClub_Text_YouMayTradeHere,
    CableClub_Text_YouMayBattleHere,
    CableClub_Text_CanMakeBerryPowder,
    CableClub_Text_CancelSelectedItem,
};
static const u8 *const sWirelessOptions_AllServices[] =
{
    CableClub_Text_YouMayTradeHere,
    CableClub_Text_YouMayBattleHere,
    CableClub_Text_CanMixRecords,
    CableClub_Text_CanMakeBerryPowder,
    CableClub_Text_CancelSelectedItem,
};
static const u8 *const sCableClubOptions_NoRecordMix[] =
{
    CableClub_Text_TradeUsingLinkCable,
    CableClub_Text_BattleUsingLinkCable,
    CableClub_Text_CancelSelectedItem,
};
static const u8 *const sWirelessOptions_NoRecordMixBerryCrush[] =
{
    CableClub_Text_YouMayTradeHere,
    CableClub_Text_YouMayBattleHere,
    CableClub_Text_CancelSelectedItem,
};
