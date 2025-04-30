#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_message.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "scanline_effect.h"
#include "palette.h"
#include "party_menu.h"
#include "pokemon_icon.h"
#include "sprite.h"
#include "item.h"
#include "task.h"
#include "bg.h"
#include "gpu_regs.h"
#include "window.h"
#include "text.h"
#include "text_window.h"
#include "international_string_util.h"
#include "strings.h"
#include "battle_ai_main.h"
#include "battle_ai_util.h"
#include "list_menu.h"
#include "decompress.h"
#include "trainer_pokemon_sprites.h"
#include "malloc.h"
#include "string_util.h"
#include "util.h"
#include "data.h"
#include "reset_rtc_screen.h"
#include "reshow_battle_screen.h"
#include "constants/abilities.h"
#include "constants/party_menu.h"
#include "constants/moves.h"
#include "constants/items.h"
#include "constants/rgb.h"
#include "constants/hold_effects.h"

#define MAX_MODIFY_DIGITS 4

struct BattleDebugModifyArrows
{
    u8 arrowSpriteId[2];
    u16 minValue;
    u16 maxValue;
    int currValue;
    u8 currentDigit:4;
    u8 maxDigits:4;
    u8 charDigits[MAX_MODIFY_DIGITS];
    void *modifiedValPtr;
    u8 typeOfVal;
};

struct BattleDebugMenu
{
    u8 battlerId:2;
    u8 aiBattlerId:2;

    u8 battlerWindowId;

    u8 mainListWindowId;
    u8 mainListTaskId;
    u8 currentMainListItemId;

    u8 secondaryListWindowId;
    u8 secondaryListTaskId;
    u8 currentSecondaryListItemId;
    u8 secondaryListItemCount;

    u8 modifyWindowId;

    u8 activeWindow;

    struct BattleDebugModifyArrows modifyArrows;
    const struct BitfieldInfo *bitfield;
    bool8 battlerWasChanged[MAX_BATTLERS_COUNT];

    u8 aiViewState;

    u8 aiMonSpriteId;
    u8 aiMovesWindowId;

    union
    {
        u8 aiIconSpriteIds[MAX_BATTLERS_COUNT];
        u8 aiPartyIcons[PARTY_SIZE];
    } spriteIds;
};

struct __attribute__((__packed__)) BitfieldInfo
{
    u8 bitsCount;
    u8 currBit;
};

enum
{
    LIST_ITEM_MOVES,
    LIST_ITEM_ABILITY,
    LIST_ITEM_HELD_ITEM,
    LIST_ITEM_PP,
    LIST_ITEM_TYPES,
    LIST_ITEM_STATS,
    LIST_ITEM_STAT_STAGES,
    LIST_ITEM_STATUS1,
    LIST_ITEM_STATUS2,
    LIST_ITEM_STATUS3,
    LIST_ITEM_STATUS4,
    LIST_ITEM_SIDE_STATUS,
    LIST_ITEM_AI,
    LIST_ITEM_AI_MOVES_PTS,
    LIST_ITEM_AI_INFO,
    LIST_ITEM_AI_PARTY,
    LIST_ITEM_VARIOUS,
    LIST_ITEM_COUNT
};

enum
{
    LIST_STAT_HP_CURRENT,
    LIST_STAT_HP_MAX,
    LIST_STAT_ATTACK,
    LIST_STAT_DEFENSE,
    LIST_STAT_SPEED,
    LIST_STAT_SP_ATK,
    LIST_STAT_SP_DEF,
};

enum
{
    LIST_STATUS1_SLEEP,
    LIST_STATUS1_POISON,
    LIST_STATUS1_BURN,
    LIST_STATUS1_FREEZE,
    LIST_STATUS1_PARALYSIS,
    LIST_STATUS1_TOXIC_POISON,
    LIST_STATUS1_TOXIC_COUNTER,
    LIST_STATUS1_FROSTBITE,
};

enum
{
    LIST_STATUS2_CONFUSION,
    LIST_STATUS2_FLINCHED,
    LIST_STATUS2_TORMENT,
    LIST_STATUS2_POWDER,
    LIST_STATUS2_DEFENSE_CURL,
    LIST_STATUS2_RECHARGE,
    LIST_STATUS2_RAGE,
    LIST_STATUS2_DESTINY_BOND,
    LIST_STATUS2_ESCAPE_PREVENTION,
    LIST_STATUS2_CURSED,
    LIST_STATUS2_FORESIGHT,
    LIST_STATUS2_DRAGON_CHEER,
    LIST_STATUS2_FOCUS_ENERGY
};

enum
{
    LIST_STATUS3_LEECH_SEED_HEALER,
    LIST_STATUS3_LEECH_SEEDED,
    LIST_STATUS3_ALWAYS_HITS,
    LIST_STATUS3_PERISH_SONG,
    LIST_STATUS3_ON_AIR,
    LIST_STATUS3_UNDERGROUND,
    LIST_STATUS3_MINIMIZED,
    LIST_STATUS3_CHARGED_UP,
    LIST_STATUS3_ROOTED,
    LIST_STATUS3_YAWN,
    LIST_STATUS3_IMPRISONED_OTHERS,
    LIST_STATUS3_GRUDGE,
    LIST_STATUS3_GASTRO_ACID,
    LIST_STATUS3_EMBARGO,
    LIST_STATUS3_UNDERWATER,
    LIST_STATUS3_SMACKED_DOWN,
    LIST_STATUS3_TELEKINESIS,
    LIST_STATUS3_MIRACLE_EYED,
    LIST_STATUS3_MAGNET_RISE,
    LIST_STATUS3_HEAL_BLOCK,
    LIST_STATUS3_AQUA_RING,
    LIST_STATUS3_LASER_FOCUS,
    LIST_STATUS3_POWER_TRICK,
};

enum
{
    LIST_STATUS4_ELECTRIFIED,
    LIST_STATUS4_MUD_SPORT,
    LIST_STATUS4_WATER_SPORT,
    LIST_STATUS4_SALT_CURE,
    LIST_STATUS4_SYRUP_BOMB,
    LIST_STATUS4_GLAIVE_RUSH,
};

enum
{
    LIST_SIDE_REFLECT,
    LIST_SIDE_LIGHTSCREEN,
    LIST_SIDE_STICKY_WEB,
    LIST_SIDE_SPIKES,
    LIST_SIDE_SAFEGUARD,
    LIST_SIDE_MIST,
    LIST_SIDE_TAILWIND,
    LIST_SIDE_AURORA_VEIL,
    LIST_SIDE_LUCKY_CHANT,
    LIST_SIDE_TOXIC_SPIKES,
    LIST_SIDE_STEALTH_ROCK,
    LIST_SIDE_STEELSURGE,
    LIST_SIDE_DAMAGE_NON_TYPES,
    LIST_SIDE_RAINBOW,
    LIST_SIDE_SEA_OF_FIRE,
    LIST_SIDE_SWAMP,
};

enum
{
    LIST_AI_CHECK_BAD_MOVE,
    LIST_AI_TRY_TO_FAINT,
    LIST_AI_CHECK_VIABILITY,
    LIST_AI_FORCE_SETUP_FIRST_TURN,
    LIST_AI_RISKY,
    LIST_AI_TRY_TO_2HKO,
    LIST_AI_PREFER_BATON_PASS,
    LIST_AI_DOUBLE_BATTLE,
    LIST_AI_HP_AWARE,
    LIST_AI_POWERFUL_STATUS,
    LIST_AI_NEGATE_UNAWARE,
    LIST_AI_WILL_SUICIDE,
    LIST_AI_PREFER_STATUS_MOVES,
    LIST_AI_STALL,
    LIST_AI_SMART_SWITCHING,
    LIST_AI_ACE_POKEMON,
    LIST_AI_OMNISCIENT,
    LIST_AI_SMART_MON_CHOICES,
    LIST_AI_CONSERVATIVE,
    LIST_AI_SEQUENCE_SWITCHING,
    LIST_AI_DOUBLE_ACE_POKEMON,
    LIST_AI_WEIGH_ABILITY_PREDICTION,
    LIST_AI_PREFER_HIGHEST_DAMAGE_MOVE,
    LIST_AI_PREDICT_SWITCH,
    LIST_AI_PREDICT_INCOMING_MON,
    LIST_AI_DYNAMIC_FUNC,
    LIST_AI_ROAMING,
    LIST_AI_SAFARI,
    LIST_AI_FIRST_BATTLE,
};

enum
{
    VARIOUS_SHOW_HP,
    VARIOUS_SUBSTITUTE_HP,
    VARIOUS_IN_LOVE,
};

enum
{
    ACTIVE_WIN_MAIN,
    ACTIVE_WIN_SECONDARY,
    ACTIVE_WIN_MODIFY
};

enum
{
    VAL_U8,
    VAL_U16,
    VAL_U32,
    VAL_BITFIELD_8,
    VAL_BITFIELD_16,
    VAL_BITFIELD_32,
    VAR_SIDE_STATUS,
    VAR_SHOW_HP,
    VAR_SUBSTITUTE,
    VAR_IN_LOVE,
    VAR_U16_4_ENTRIES,
    VAL_S8,
    VAL_ALL_STAT_STAGES,
};

// Static Declarations
static const u8 *GetHoldEffectName(u16 holdEffect);

// const rom data
static const u8 sText_Moves[] = _("招式");
static const u8 sText_Ability[] = _("特性");
static const u8 sText_HeldItem[] = _("持有物");
static const u8 sText_HoldEffect[] = _("携带效果");
static const u8 sText_PP[] = _("PP");
static const u8 sText_Types[] = _("属性");
static const u8 sText_Stats[] = _("能力");
static const u8 sText_StatStages[] = _("能力阶级");
static const u8 sText_Status1[] = _("状态1");
static const u8 sText_Status2[] = _("状态2");
static const u8 sText_Status3[] = _("状态3");
static const u8 sText_Status4[] = _("状态4");
static const u8 sText_SideStatus[] = _("场地状态");
static const u8 sText_AI[] = _("AI");
static const u8 sText_AIMovePts[] = _("AI点数/伤害");
static const u8 sText_AiKnowledge[] = _("AI信息");
static const u8 sText_AiParty[] = _("AI队伍");
static const u8 sText_Various[] = _("杂项");
static const u8 sText_CurrHp[] = _("当前HP");
static const u8 sText_MaxHp[] = _("最大HP");
static const u8 sText_Attack[] = _("攻击");
static const u8 sText_Defense[] = _("防御");
static const u8 sText_Speed[] = _("速度");
static const u8 sText_SpAtk[] = _("特攻");
static const u8 sText_SpDef[] = _("特防");
static const u8 sText_Sleep[] = _("睡眠");
static const u8 sText_Poison[] = _("中毒");
static const u8 sText_Burn[] = _("灼伤");
static const u8 sText_Freeze[] = _("冰冻");
static const u8 sText_Paralysis[] = _("麻痹");
static const u8 sText_ToxicPoison[] = _("剧毒");
static const u8 sText_ToxicCounter[] = _("剧毒经过回合");
static const u8 sText_Frostbite[] = _("冻伤");
static const u8 sText_Confusion[] = _("念力");
static const u8 sText_Flinched[] = _("畏缩");
static const u8 sText_Uproar[] = _("吵闹");
static const u8 sText_Torment[] = _("无理取闹");
static const u8 sText_Bide[] = _("忍耐");
static const u8 sText_LockConfuse[] = _("锁定混乱？");
static const u8 sText_MultipleTurns[] = _("多回合");
static const u8 sText_Wrapped[] = _("束缚");
static const u8 sText_Powder[] = _("粉尘");
static const u8 sText_Infatuation[] = _("着迷");
static const u8 sText_DefenseCurl[] = _("变圆");
static const u8 sText_Transformed[] = _("变身");
static const u8 sText_Recharge[] = _("无法动弹");
static const u8 sText_Rage[] = _("愤怒");
static const u8 sText_Substitute[] = _("替身");
static const u8 sText_DestinyBond[] = _("同命");
static const u8 sText_EscapePrevention[] = _("无法逃走");
static const u8 sText_Nightmare[] = _("恶梦");
static const u8 sText_Cursed[] = _("诅咒");
static const u8 sText_Foresight[] = _("识破");
static const u8 sText_DragonCheer[] = _("龙声鼓舞");
static const u8 sText_FocusEnergy[] = _("聚气");
static const u8 sText_LeechSeedHealer[] = _("因寄生种子回复");
static const u8 sText_LeechSeeded[] = _("被寄生种子寄生");
static const u8 sText_AlwaysHits[] = _("锁定");
static const u8 sText_PerishSong[] = _("终焉之歌");
static const u8 sText_OnAir[] = _("飞翔");
static const u8 sText_Underground[] = _("挖洞");
static const u8 sText_Minimized[] = _("变小");
static const u8 sText_ChargedUp[] = _("充电");
static const u8 sText_Rooted[] = _("扎根");
static const u8 sText_Yawn[] = _("哈欠");
static const u8 sText_ImprisonedOthers[] = _("封印其他宝可梦");
static const u8 sText_Grudge[] = _("怨念");
static const u8 sText_GastroAcid[] = _("胃液");
static const u8 sText_Embargo[] = _("查封");
static const u8 sText_Underwater[] = _("潜水");
static const u8 sText_Trace[] = _("复制");
static const u8 sText_SmackedDown[] = _("被击落");
static const u8 sText_MeFirst[] = _("抢先一步");
static const u8 sText_Telekinesis[] = _("意念移物");
static const u8 sText_PhantomForce[] = _("潜灵奇袭");
static const u8 sText_MiracleEyed[] = _("奇迹之眼");
static const u8 sText_MagnetRise[] = _("电磁飘浮");
static const u8 sText_HealBlock[] = _("回复封锁");
static const u8 sText_AquaRing[] = _("水流环");
static const u8 sText_LaserFocus[] = _("磨砺");
static const u8 sText_PowerTrick[] = _("力量戏法");
static const u8 sText_SkyDropped[] = _("自由落体中");
static const u8 sText_Electrified[] = _("输电");
static const u8 sText_MudSport[] = _("玩泥巴");
static const u8 sText_WaterSport[] = _("玩水");
static const u8 sText_InfiniteConfusion[] = _("无限混乱");
static const u8 sText_SaltCure[] = _("盐腌");
static const u8 sText_SyrupBomb[] = _("满身糖");
static const u8 sText_GlaiveRush[] = _("巨剑突击");
static const u8 sText_Reflect[] = _("反射壁");
static const u8 sText_LightScreen[] = _("光墙");
static const u8 sText_StickyWeb[] = _("黏黏网");
static const u8 sText_Spikes[] = _("撒菱");
static const u8 sText_Safeguard[] = _("神秘守护");
static const u8 sText_FutureAttack[] = _("未来攻击");
static const u8 sText_Mist[] = _("白雾");
static const u8 sText_Tailwind[] = _("顺风");
static const u8 sText_AuroraVeil[] = _("极光幕");
static const u8 sText_LuckyChant[] = _("幸运咒语");
static const u8 sText_ToxicSpikes[] = _("毒菱");
static const u8 sText_StealthRock[] = _("隐形岩");
static const u8 sText_Steelsurge[] = _("超极巨钢铁阵法");
static const u8 sText_DamageNonTypes[] = _("无属性攻击？");
static const u8 sText_Rainbow[] = _("彩虹");
static const u8 sText_SeaOfFire[] = _("火海");
static const u8 sText_Swamp[] = _("湿地");
static const u8 sText_CheckBadMove[] = _("检查效果不好的招式");
static const u8 sText_TryToFaint[] = _("尝试击晕");
static const u8 sText_CheckViability[] = _("检查可行性");
static const u8 sText_ForceSetupFirstTurn[] = _("遵循第一回合设置");
static const u8 sText_Risky[] = _("危险大胆");
static const u8 sText_TryTo2HKO[] = _("尝试两招击倒");
static const u8 sText_PreferBatonPass[] = _("偏好接力棒");
static const u8 sText_DoubleBattle[] = _("双打对战");
static const u8 sText_HpAware[] = _("注意HP");
static const u8 sText_PowerfulStatus[] = _("异常状态干扰？");
static const u8 sText_NegateUnaware[] = _("纯朴无效？");
static const u8 sText_WillSuicide[] = _("愿意自杀");
static const u8 sText_PreferStatusMoves[] = _("偏好状态变化招式");
static const u8 sText_Stall[] = _("拖延消耗");
static const u8 sText_SmartSwitching[] = _("聪明替换");
static const u8 sText_AcePokemon[] = _("主力宝可梦");
static const u8 sText_Omniscient[] = _("全知");
static const u8 sText_SmartMonChoices[] = _("聪明的宝可梦选择");
static const u8 sText_Conservative[] = _("保守");
static const u8 sText_SequenceSwitching[] = _("按顺序替换");
static const u8 sText_DoubleAcePokemon[] = _("双主力宝可梦");
static const u8 sText_WeighAbilityPrediction[] = _("权衡特性预测");
static const u8 sText_PreferHighestDamageMove[] = _("偏好最高伤害招式");
static const u8 sText_PredictSwitch[] = _("预测替换");
static const u8 sText_PredictIncomingMon[] = _("预测上场宝可梦");
static const u8 sText_DynamicFunc[] = _("动态功能");
static const u8 sText_Roaming[] = _("四处游走");
static const u8 sText_Safari[] = _("狩猎地带");
static const u8 sText_FirstBattle[] = _("第一战");
static const u8 sText_ShowHP[] = _("显示HP");
static const u8 sText_SubstituteHp[] = _("替换HP");
static const u8 sText_InLove[] = _("着迷");
static const u8 sText_Unknown[] = _("未知");
static const u8 sText_EmptyString[] = _("");
static const u8 sText_IsSwitching[] = _("替换为");

static const struct BitfieldInfo sStatus1Bitfield[] =
{
    {/*Sleep*/ 3, 0},
    {/*Poison*/ 1, 3},
    {/*Burn*/ 1, 4},
    {/*Freeze*/ 1, 5},
    {/*Paralysis*/1, 6},
    {/*Toxic Poison*/ 1, 7},
    {/*Toxic Counter*/ 4, 8},
    {/*Frostbite*/ 1, 12},
};

static const struct BitfieldInfo sStatus2Bitfield[] =
{
    {/*Confusion*/ 3, 0},
    {/*Flinched*/ 1, 3},
    {/*Torment*/ 1, 7},
    {/*Powder*/ 1, 14},
    {/*Defense Curl*/ 1, 20},
    {/*Recharge*/ 1, 22},
    {/*Rage*/ 1, 23},
    {/*Destiny Bond*/ 1, 25},
    {/*Escape Prevention*/ 1, 26},
    {/*Cursed*/ 1, 28},
    {/*Foresight*/ 1, 29},
    {/*Dragon Cheer*/ 1, 30},
    {/*Focus Energy*/ 1, 31},
};

static const struct BitfieldInfo sStatus3Bitfield[] =
{
    {/*Leech Seed Battler*/ 2, 0},
    {/*Leech Seed*/ 1, 2},
    {/*Always Hits*/ 2, 3},
    {/*Perish Song*/ 1, 5},
    {/*On Air*/ 1, 6},
    {/*Underground*/ 1, 7},
    {/*Minimized*/ 1, 8},
    {/*Charged Up*/ 1, 9},
    {/*Rooted*/ 1, 10},
    {/*Yawn*/ 2, 11},
    {/*Imprisoned Others*/ 1, 13},
    {/*Grudge*/ 1, 14},
    {/*Gastro Acid*/ 1, 16},
    {/*Embargo*/ 1, 17},
    {/*Underwater*/ 1, 18},
    {/*Smacked Down*/ 1, 21},
    {/*Telekinesis*/ 1, 23},
    {/*Miracle Eyed*/ 1, 25},
    {/*Magnet Rise*/ 1, 26},
    {/*Heal Blocked*/ 1, 27},
    {/*Aqua Ring*/ 1, 28},
    {/*Laser Focus*/ 1, 29},
    {/*Power Trick*/ 1, 30},
};

static const struct BitfieldInfo sStatus4Bitfield[] =
{
    {/*Electrified*/ 1, 0},
    {/*Mud Sport*/ 1, 1},
    {/*Water Sport*/ 1, 2},
    {/*Salt Cure*/ 1, 4},
    {/*Syrup Bomb*/ 1, 5},
    {/*Glaive Rush*/ 1, 6},
};

static const struct BitfieldInfo sAIBitfield[] =
{
    {/*Check Bad Move*/ 1, 0},
    {/*Try to Faint*/ 1, 1},
    {/*Check Viability*/ 1, 2},
    {/*Force Setup First Turn*/ 1, 3},
    {/*Risky*/ 1, 4},
    {/*Prefer Strongest Move*/ 1, 5},
    {/*Prefer Baton Pass*/ 1, 6},
    {/*Double Battle*/ 1, 7},
    {/*HP Aware*/ 1, 8},
    {/*Powerful Status*/ 1, 9},
    {/*Negate Unaware*/ 1, 10},
    {/*Will Suicide*/ 1, 11},
    {/*Prefer Status Moves*/ 1, 12},
    {/*Stall*/ 1, 13},
    {/*Smart Switching*/ 1, 14},
    {/*Ace Pokemon*/ 1, 15},
    {/*Omniscient*/ 1, 16},
    {/*Smart Mon Choices*/ 1, 17},
    {/*Conservative*/ 1, 18},
    {/*Sequence Switching*/ 1, 19},
    {/*Double Ace Pokemon*/ 1, 20},
    {/*Weigh Ability Prediction*/ 1, 21},
    {/*Prefer Highest Damage Move*/ 1, 22},
    {/*Predict Switch*/ 1, 23},
    {/*Predict Incoming Mon*/ 1, 24},
    {/*Dynamic Func*/ 1, 28},
    {/*Roaming*/ 1, 29},
    {/*Safari*/ 1, 30},
    {/*First Battle*/ 1, 31},
};

static const struct ListMenuItem sMainListItems[] =
{
    {sText_Moves, LIST_ITEM_MOVES},
    {sText_Ability, LIST_ITEM_ABILITY},
    {sText_HeldItem, LIST_ITEM_HELD_ITEM},
    {sText_PP, LIST_ITEM_PP},
    {sText_Types, LIST_ITEM_TYPES},
    {sText_Stats, LIST_ITEM_STATS},
    {sText_StatStages, LIST_ITEM_STAT_STAGES},
    {sText_Status1, LIST_ITEM_STATUS1},
    {sText_Status2, LIST_ITEM_STATUS2},
    {sText_Status3, LIST_ITEM_STATUS3},
    {sText_Status4, LIST_ITEM_STATUS4},
    {sText_SideStatus, LIST_ITEM_SIDE_STATUS},
    {sText_AI, LIST_ITEM_AI},
    {sText_AIMovePts, LIST_ITEM_AI_MOVES_PTS},
    {sText_AiKnowledge, LIST_ITEM_AI_INFO},
    {sText_AiParty, LIST_ITEM_AI_PARTY},
    {sText_Various, LIST_ITEM_VARIOUS},
};

static const struct ListMenuItem sStatsListItems[] =
{
    {sText_CurrHp, LIST_STAT_HP_CURRENT},
    {sText_MaxHp, LIST_STAT_HP_MAX},
    {sText_Attack, LIST_STAT_ATTACK},
    {sText_Defense, LIST_STAT_DEFENSE},
    {sText_Speed, LIST_STAT_SPEED},
    {sText_SpAtk, LIST_STAT_SP_ATK},
    {sText_SpDef, LIST_STAT_SP_DEF},
};

static const struct ListMenuItem sStatus1ListItems[] =
{
    {sText_Sleep, LIST_STATUS1_SLEEP},
    {sText_Poison, LIST_STATUS1_POISON},
    {sText_Burn, LIST_STATUS1_BURN},
    {sText_Freeze, LIST_STATUS1_FREEZE},
    {sText_Paralysis, LIST_STATUS1_PARALYSIS},
    {sText_ToxicPoison, LIST_STATUS1_TOXIC_POISON},
    {sText_ToxicCounter, LIST_STATUS1_TOXIC_COUNTER},
    {sText_Frostbite, LIST_STATUS1_FROSTBITE},
};

static const struct ListMenuItem sStatus2ListItems[] =
{
    {sText_Confusion, LIST_STATUS2_CONFUSION},
    {sText_Flinched, LIST_STATUS2_FLINCHED},
    {sText_Torment, LIST_STATUS2_TORMENT},
    {sText_Powder, LIST_STATUS2_POWDER},
    {sText_DefenseCurl, LIST_STATUS2_DEFENSE_CURL},
    {sText_Recharge, LIST_STATUS2_RECHARGE},
    {sText_Rage, LIST_STATUS2_RAGE},
    {sText_DestinyBond, LIST_STATUS2_DESTINY_BOND},
    {sText_EscapePrevention, LIST_STATUS2_ESCAPE_PREVENTION},
    {sText_Cursed, LIST_STATUS2_CURSED},
    {sText_Foresight, LIST_STATUS2_FORESIGHT},
    {sText_DragonCheer, LIST_STATUS2_DRAGON_CHEER},
    {sText_FocusEnergy, LIST_STATUS2_FOCUS_ENERGY},
};

static const struct ListMenuItem sStatus3ListItems[] =
{
    {sText_LeechSeedHealer, LIST_STATUS3_LEECH_SEED_HEALER},
    {sText_LeechSeeded, LIST_STATUS3_LEECH_SEEDED},
    {sText_AlwaysHits, LIST_STATUS3_ALWAYS_HITS},
    {sText_PerishSong, LIST_STATUS3_PERISH_SONG},
    {sText_OnAir, LIST_STATUS3_ON_AIR},
    {sText_Underground, LIST_STATUS3_UNDERGROUND},
    {sText_Minimized, LIST_STATUS3_MINIMIZED},
    {sText_ChargedUp, LIST_STATUS3_CHARGED_UP},
    {sText_Rooted, LIST_STATUS3_ROOTED},
    {sText_Yawn, LIST_STATUS3_YAWN},
    {sText_ImprisonedOthers, LIST_STATUS3_IMPRISONED_OTHERS},
    {sText_Grudge, LIST_STATUS3_GRUDGE},
    {sText_GastroAcid, LIST_STATUS3_GASTRO_ACID},
    {sText_Embargo, LIST_STATUS3_EMBARGO},
    {sText_Underwater, LIST_STATUS3_UNDERWATER},
    {sText_SmackedDown, LIST_STATUS3_SMACKED_DOWN},
    {sText_Telekinesis, LIST_STATUS3_TELEKINESIS},
    {sText_MiracleEyed, LIST_STATUS3_MIRACLE_EYED},
    {sText_MagnetRise, LIST_STATUS3_MAGNET_RISE},
    {sText_HealBlock, LIST_STATUS3_HEAL_BLOCK},
    {sText_AquaRing, LIST_STATUS3_AQUA_RING},
    {sText_LaserFocus, LIST_STATUS3_LASER_FOCUS},
    {sText_PowerTrick, LIST_STATUS3_POWER_TRICK},
};

static const struct ListMenuItem sStatus4ListItems[] =
{
    {sText_Electrified, LIST_STATUS4_ELECTRIFIED},
    {sText_MudSport, LIST_STATUS4_MUD_SPORT},
    {sText_WaterSport, LIST_STATUS4_WATER_SPORT},
    {sText_SaltCure, LIST_STATUS4_SALT_CURE},
    {sText_SyrupBomb, LIST_STATUS4_SYRUP_BOMB},
    {sText_GlaiveRush, LIST_STATUS4_GLAIVE_RUSH},
};

static const struct ListMenuItem sSideStatusListItems[] =
{
    {sText_Reflect, LIST_SIDE_REFLECT},
    {sText_LightScreen, LIST_SIDE_LIGHTSCREEN},
    {sText_StickyWeb, LIST_SIDE_STICKY_WEB},
    {sText_Spikes, LIST_SIDE_SPIKES},
    {sText_Safeguard, LIST_SIDE_SAFEGUARD},
    {sText_Mist, LIST_SIDE_MIST},
    {sText_Tailwind, LIST_SIDE_TAILWIND},
    {sText_AuroraVeil, LIST_SIDE_AURORA_VEIL},
    {sText_LuckyChant, LIST_SIDE_LUCKY_CHANT},
    {sText_ToxicSpikes, LIST_SIDE_TOXIC_SPIKES},
    {sText_StealthRock, LIST_SIDE_STEALTH_ROCK},
    {sText_Steelsurge, LIST_SIDE_STEELSURGE},
    {sText_DamageNonTypes, LIST_SIDE_DAMAGE_NON_TYPES},
    {sText_Rainbow, LIST_SIDE_RAINBOW},
    {sText_SeaOfFire, LIST_SIDE_SEA_OF_FIRE},
    {sText_Swamp, LIST_SIDE_SWAMP},
};

static const struct ListMenuItem sAIListItems[] =
{
    {sText_CheckBadMove, LIST_AI_CHECK_BAD_MOVE},
    {sText_TryToFaint, LIST_AI_TRY_TO_FAINT},
    {sText_CheckViability, LIST_AI_CHECK_VIABILITY},
    {sText_ForceSetupFirstTurn, LIST_AI_FORCE_SETUP_FIRST_TURN},
    {sText_Risky, LIST_AI_RISKY},
    {sText_TryTo2HKO, LIST_AI_TRY_TO_2HKO},
    {sText_PreferBatonPass, LIST_AI_PREFER_BATON_PASS},
    {sText_DoubleBattle, LIST_AI_DOUBLE_BATTLE},
    {sText_HpAware, LIST_AI_HP_AWARE},
    {sText_PowerfulStatus, LIST_AI_POWERFUL_STATUS},
    {sText_NegateUnaware, LIST_AI_NEGATE_UNAWARE},
    {sText_WillSuicide, LIST_AI_WILL_SUICIDE},
    {sText_PreferStatusMoves, LIST_AI_PREFER_STATUS_MOVES},
    {sText_Stall, LIST_AI_STALL},
    {sText_SmartSwitching, LIST_AI_SMART_SWITCHING},
    {sText_AcePokemon, LIST_AI_ACE_POKEMON},
    {sText_Omniscient, LIST_AI_OMNISCIENT},
    {sText_SmartMonChoices, LIST_AI_SMART_MON_CHOICES},
    {sText_Conservative, LIST_AI_CONSERVATIVE},
    {sText_SequenceSwitching, LIST_AI_SEQUENCE_SWITCHING},
    {sText_DoubleAcePokemon, LIST_AI_DOUBLE_ACE_POKEMON},
    {sText_WeighAbilityPrediction, LIST_AI_WEIGH_ABILITY_PREDICTION},
    {sText_PreferHighestDamageMove, LIST_AI_PREFER_HIGHEST_DAMAGE_MOVE},
    {sText_PredictSwitch, LIST_AI_PREDICT_SWITCH},
    {sText_PredictIncomingMon, LIST_AI_PREDICT_INCOMING_MON},
    {sText_DynamicFunc, LIST_AI_DYNAMIC_FUNC},
    {sText_Roaming, LIST_AI_ROAMING},
    {sText_Safari, LIST_AI_SAFARI},
    {sText_FirstBattle, LIST_AI_FIRST_BATTLE},
};

static const struct ListMenuItem sVariousListItems[] =
{
    {sText_ShowHP, VARIOUS_SHOW_HP},
    {sText_SubstituteHp, VARIOUS_SUBSTITUTE_HP},
    {sText_InLove, VARIOUS_IN_LOVE},
};

static const struct ListMenuItem sSecondaryListItems[] =
{
    {sText_EmptyString, 0},
    {sText_EmptyString, 1},
    {sText_EmptyString, 2},
    {sText_EmptyString, 3},
    {sText_EmptyString, 4},
    {sText_EmptyString, 5},
    {sText_EmptyString, 6},
    {sText_EmptyString, 7},
    {sText_EmptyString, 8},
};


static const struct ListMenuTemplate sMainListTemplate =
{
    .items = sMainListItems,
    .moveCursorFunc = NULL,
    .itemPrintFunc = NULL,
    .totalItems = ARRAY_COUNT(sMainListItems),
    .maxShowed = 6,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 1,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = 1,
    .cursorKind = 0
};

static const struct ListMenuTemplate sSecondaryListTemplate =
{
    .items = sSecondaryListItems,
    .moveCursorFunc = NULL,
    .itemPrintFunc = NULL,
    .totalItems = 0,
    .maxShowed = 0,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 1,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = 1,
    .cursorKind = 0
};


static const struct WindowTemplate sMainListWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 3,
    .width = 9,
    .height = 12,
    .paletteNum = 0xF,
    .baseBlock = 0x1
};

static const struct WindowTemplate sSecondaryListWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 12,
    .tilemapTop = 3,
    .width = 20,
    .height = 16,
    .paletteNum = 0xF,
    .baseBlock = 0x6D
};

static const struct WindowTemplate sModifyWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 25,
    .tilemapTop = 2,
    .width = 4,
    .height = 2,
    .paletteNum = 0xF,
    .baseBlock = 0x1AD
};

static const struct WindowTemplate sBattlerWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 10,
    .tilemapTop = 0,
    .width = 14,
    .height = 2,
    .paletteNum = 0xF,
    .baseBlock = 0x1B5
};

static const struct BgTemplate sBgTemplates[] =
{
   {
       .bg = 0,
       .charBaseIndex = 0,
       .mapBaseIndex = 31,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 1,
       .baseTile = 0
   },
   {
       .bg = 1,
       .charBaseIndex = 2,
       .mapBaseIndex = 20,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 0,
       .baseTile = 0
   }
};

static const u8 sBitsToMaxDigit[] =
{
    [0] = 0,
    [1] = 1, // max 1
    [2] = 1, // max 3
    [3] = 1, // max 7
    [4] = 2, // max 15
    [5] = 2, // max 31
    [6] = 2, // max 63
    [7] = 3, // max 127
    [8] = 3, // max 255
};

static const bool8 sHasChangeableEntries[LIST_ITEM_COUNT] =
{
    [LIST_ITEM_MOVES] = TRUE,
    [LIST_ITEM_AI_MOVES_PTS] = TRUE,
    [LIST_ITEM_PP] = TRUE,
    [LIST_ITEM_ABILITY] = TRUE,
    [LIST_ITEM_TYPES] = TRUE,
    [LIST_ITEM_HELD_ITEM] = TRUE,
    [LIST_ITEM_STAT_STAGES] = TRUE,
};

static const u16 sBgColor[] = {RGB_WHITE};

// this file's functions
static void Task_DebugMenuFadeOut(u8 taskId);
static void Task_DebugMenuProcessInput(u8 taskId);
static void Task_DebugMenuFadeIn(u8 taskId);
static void PrintOnBattlerWindow(u8 windowId, u8 battlerId);
static void UpdateWindowsOnChangedBattler(struct BattleDebugMenu *data);
static void CreateSecondaryListMenu(struct BattleDebugMenu *data);
static void PrintSecondaryEntries(struct BattleDebugMenu *data);
static void DestroyModifyArrows(struct BattleDebugMenu *data);
static void PrintDigitChars(struct BattleDebugMenu *data);
static void SetUpModifyArrows(struct BattleDebugMenu *data);
static void UpdateBattlerValue(struct BattleDebugMenu *data);
static void UpdateMonData(struct BattleDebugMenu *data);
static u16 *GetSideStatusValue(struct BattleDebugMenu *data, bool32 changeStatus, bool32 statusTrue);
static bool32 TryMoveDigit(struct BattleDebugModifyArrows *modArrows, bool32 moveUp);
static void SwitchToDebugView(u8 taskId);
static void SwitchToDebugViewFromAiParty(u8 taskId);

// code
static struct BattleDebugMenu *GetStructPtr(u8 taskId)
{
    u8 *taskDataPtr = (u8 *)(&gTasks[taskId].data[0]);

    return (struct BattleDebugMenu*)(T1_READ_PTR(taskDataPtr));
}

static void SetStructPtr(u8 taskId, void *ptr)
{
    u32 structPtr = (u32)(ptr);
    u8 *taskDataPtr = (u8 *)(&gTasks[taskId].data[0]);

    taskDataPtr[0] = structPtr >> 0;
    taskDataPtr[1] = structPtr >> 8;
    taskDataPtr[2] = structPtr >> 16;
    taskDataPtr[3] = structPtr >> 24;
}

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_BattleDebugMenu(void)
{
    u8 taskId;
    struct BattleDebugMenu *data;

    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
        ResetVramOamAndBgCntRegs();
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
        ResetAllBgsCoordinates();
        FreeAllWindowBuffers();
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        LoadPalette(sBgColor, 0, 2);
        LoadPalette(GetOverworldTextboxPalettePtr(), 0xf0, 16);
        gMain.state++;
        break;
    case 4:
        taskId = CreateTask(Task_DebugMenuFadeIn, 0);
        data = AllocZeroed(sizeof(struct BattleDebugMenu));
        SetStructPtr(taskId, data);

        data->battlerId = gBattleStruct->debugBattler;
        data->battlerWindowId = AddWindow(&sBattlerWindowTemplate);
        PutWindowTilemap(data->battlerWindowId);
        PrintOnBattlerWindow(data->battlerWindowId, data->battlerId);

        data->mainListWindowId = AddWindow(&sMainListWindowTemplate);

        gMultiuseListMenuTemplate = sMainListTemplate;
        gMultiuseListMenuTemplate.windowId = data->mainListWindowId;
        data->mainListTaskId = ListMenuInit(&gMultiuseListMenuTemplate, 0, 0);

        data->currentMainListItemId = 0;
        data->activeWindow = ACTIVE_WIN_MAIN;
        data->secondaryListTaskId = 0xFF;
        CopyWindowToVram(data->mainListWindowId, COPYWIN_FULL);
        gMain.state++;
        break;
    case 5:
        BeginNormalPaletteFade(-1, 0, 0x10, 0, 0);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

static void PutMovesPointsText(struct BattleDebugMenu *data)
{
    u32 i, j, count, battlerDef;
    u8 *text = Alloc(0x50);

    FillWindowPixelBuffer(data->aiMovesWindowId, 0x11);
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        text[0] = CHAR_SPACE;
        StringCopy(text + 1, GetMoveName(gBattleMons[data->aiBattlerId].moves[i]));
        AddTextPrinterParameterized(data->aiMovesWindowId, FONT_NORMAL, text, 0, i * 15, 0, NULL);
        for (count = 0, j = 0; j < MAX_BATTLERS_COUNT; j++)
        {
            if (data->spriteIds.aiIconSpriteIds[j] == 0xFF)
                continue;
            battlerDef = gSprites[data->spriteIds.aiIconSpriteIds[j]].data[0];
            ConvertIntToDecimalStringN(text,
                                       gBattleStruct->aiFinalScore[data->aiBattlerId][battlerDef][i],
                                       STR_CONV_MODE_RIGHT_ALIGN, 3);
            AddTextPrinterParameterized(data->aiMovesWindowId, FONT_NORMAL, text, 83 + count * 54, i * 15, 0, NULL);

            ConvertIntToDecimalStringN(text,
                                       AI_DATA->simulatedDmg[data->aiBattlerId][battlerDef][i].expected,
                                       STR_CONV_MODE_RIGHT_ALIGN, 3);
            AddTextPrinterParameterized(data->aiMovesWindowId, FONT_NORMAL, text, 110 + count * 54, i * 15, 0, NULL);

            count++;
        }
    }

    if (AI_DATA->shouldSwitch & (1u << data->aiBattlerId))
    {
        u32 switchMon = GetMonData(&gEnemyParty[AI_DATA->mostSuitableMonId[data->aiBattlerId]], MON_DATA_SPECIES);

        AddTextPrinterParameterized(data->aiMovesWindowId, FONT_NORMAL, sText_IsSwitching, 74, 64, 0, NULL);
        AddTextPrinterParameterized(data->aiMovesWindowId, FONT_NORMAL, gSpeciesInfo[switchMon].speciesName, 74 + 68, 64, 0, NULL);
    }

    CopyWindowToVram(data->aiMovesWindowId, COPYWIN_FULL);
    Free(text);
}

static void CleanUpAiInfoWindow(u8 taskId)
{
    u32 i;
    struct BattleDebugMenu *data = GetStructPtr(taskId);

    FreeMonIconPalettes();
    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (data->spriteIds.aiIconSpriteIds[i] != 0xFF)
            FreeAndDestroyMonIconSprite(&gSprites[data->spriteIds.aiIconSpriteIds[i]]);
    }
    FreeAndDestroyMonPicSprite(data->aiMonSpriteId);
    ClearWindowTilemap(data->aiMovesWindowId);
    RemoveWindow(data->aiMovesWindowId);
}

static void Task_ShowAiPoints(u8 taskId)
{
    u32 i, count;
    struct WindowTemplate winTemplate;
    struct BattleDebugMenu *data = GetStructPtr(taskId);
    struct Pokemon *mon;

    switch (data->aiViewState)
    {
    case 0:
        HideBg(0);
        ShowBg(1);

        // Swap battler if it's player mon
        data->aiBattlerId = data->battlerId;
        while (!BattlerHasAi(data->aiBattlerId))
        {
            if (++data->aiBattlerId >= gBattlersCount)
                data->aiBattlerId = 0;
        }
        data->battlerId = data->aiBattlerId;

        LoadMonIconPalettes();
        for (count = 0, i = 0; i < MAX_BATTLERS_COUNT; i++)
        {
            if (i != data->aiBattlerId && IsBattlerAlive(i))
            {
                data->spriteIds.aiIconSpriteIds[i] = CreateMonIcon(gBattleMons[i].species,
                                                         SpriteCallbackDummy,
                                                         95 + (count * 60), 17, 0, 0);
                gSprites[data->spriteIds.aiIconSpriteIds[i]].data[0] = i; // battler id
                count++;
            }
            else
            {
                data->spriteIds.aiIconSpriteIds[i] = 0xFF;
            }
        }

        mon = &GetBattlerParty(data->aiBattlerId)[gBattlerPartyIndexes[data->aiBattlerId]];

        data->aiMonSpriteId = CreateMonPicSprite(gBattleMons[data->aiBattlerId].species,
                                                 GetMonData(mon, MON_DATA_IS_SHINY),
                                                 gBattleMons[data->aiBattlerId].personality,
                                                 TRUE,
                                                 39, 130, 15, TAG_NONE);
        data->aiViewState++;
        break;
    // Put text
    case 1:
        winTemplate = CreateWindowTemplate(1, 0, 4, 30, 14, 15, 0x200);
        data->aiMovesWindowId = AddWindow(&winTemplate);
        PutWindowTilemap(data->aiMovesWindowId);
        PutMovesPointsText(data);

        data->aiViewState++;
        break;
    // Input
    case 2:
        if (JOY_NEW(R_BUTTON) && IsDoubleBattle())
        {
            CleanUpAiInfoWindow(taskId);
            do {
                data->battlerId++;
                data->battlerId %= gBattlersCount;
            } while (!IsBattlerAlive(data->battlerId));
            data->aiViewState = 0;
        }
        else if (JOY_NEW(L_BUTTON) && IsDoubleBattle())
        {
            CleanUpAiInfoWindow(taskId);
            do {
                if (data->battlerId == 0)
                    data->battlerId = gBattlersCount - 1;
                else
                    data->battlerId--;
            } while (!IsBattlerAlive(data->battlerId) || !BattlerHasAi(data->battlerId));
            data->aiViewState = 0;
        }
        else if (JOY_NEW(SELECT_BUTTON | B_BUTTON))
        {
            SwitchToDebugView(taskId);
            HideBg(1);
            ShowBg(0);
            return;
        }
        break;
    }
}

static void SwitchToAiPointsView(u8 taskId)
{
    gTasks[taskId].func = Task_ShowAiPoints;
    GetStructPtr(taskId)->aiViewState = 0;
}

static const u8 *const sAiInfoItemNames[] =
{
    sText_Ability,
    sText_HeldItem,
    sText_HoldEffect,
};

static void PutAiInfoText(struct BattleDebugMenu *data)
{
    u32 i;
    u8 *text = Alloc(0x50);

    FillWindowPixelBuffer(data->aiMovesWindowId, 0x11);

    // item names
    for (i = 0; i < ARRAY_COUNT(sAiInfoItemNames); i++)
    {
        AddTextPrinterParameterized(data->aiMovesWindowId, FONT_NORMAL, sAiInfoItemNames[i], 3, i * 15, 0, NULL);
    }

    // items info
    for (i = 0; i < gBattlersCount; i++)
    {
        if (GetBattlerSide(i) == B_SIDE_PLAYER && IsBattlerAlive(i))
        {
            u16 ability = AI_DATA->abilities[i];
            u16 holdEffect = AI_DATA->holdEffects[i];
            u16 item = AI_DATA->items[i];
            u8 x = (i == B_POSITION_PLAYER_LEFT) ? 83 + (i) * 75 : 83 + (i-1) * 75;
            AddTextPrinterParameterized(data->aiMovesWindowId, FONT_SMALL, gAbilitiesInfo[ability].name, x, 0, 0, NULL);
            AddTextPrinterParameterized(data->aiMovesWindowId, FONT_SMALL, ItemId_GetName(item), x, 15, 0, NULL);
            AddTextPrinterParameterized(data->aiMovesWindowId, FONT_SMALL, GetHoldEffectName(holdEffect), x, 30, 0, NULL);
        }
    }

    CopyWindowToVram(data->aiMovesWindowId, COPYWIN_FULL);
    Free(text);
}

static void PutAiPartyText(struct BattleDebugMenu *data)
{
    u32 i, j, count;
    u8 *text = Alloc(0x50), *txtPtr;
    struct AiPartyMon *aiMons = AI_PARTY->mons[GetBattlerSide(data->aiBattlerId)];

    FillWindowPixelBuffer(data->aiMovesWindowId, 0x11);
    count = AI_PARTY->count[GetBattlerSide(data->aiBattlerId)];
    for (i = 0; i < count; i++)
    {
        if (aiMons[i].wasSentInBattle)
        {
            text[0] = CHAR_LV;
            txtPtr = ConvertIntToDecimalStringN(text + 1, aiMons[i].level, STR_CONV_MODE_LEFT_ALIGN, 3);
            *txtPtr++ = CHAR_SPACE;
            if (aiMons[i].gender == MON_MALE)
                *txtPtr++ = CHAR_MALE;
            else if (aiMons[i].gender == MON_FEMALE)
                *txtPtr++ = CHAR_FEMALE;
            *txtPtr = EOS;
            AddTextPrinterParameterized5(data->aiMovesWindowId, FONT_SMALL_NARROW, text, i * 41, 0, 0, NULL, 0, 0);
        }

        txtPtr = StringCopyN(text, gAbilitiesInfo[aiMons[i].ability].name, 7); // The screen is too small to fit the whole string, so we need to drop the last letters.
        *txtPtr = EOS;
        AddTextPrinterParameterized5(data->aiMovesWindowId, FONT_SMALL_NARROW, text, i * 41, 15, 0, NULL, 0, 0);

        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            txtPtr = StringCopyN(text, GetMoveName(aiMons[i].moves[j]), 8);
            *txtPtr = EOS;
            AddTextPrinterParameterized5(data->aiMovesWindowId, FONT_SMALL_NARROW, text, i * 41, 35 + j * 15, 0, NULL, 0, 0);
        }

        txtPtr = StringCopyN(text, GetHoldEffectName(aiMons[i].heldEffect), 7);
        *txtPtr = EOS;
        AddTextPrinterParameterized5(data->aiMovesWindowId, FONT_SMALL_NARROW, text, i * 41, 35 + j * 15, 0, NULL, 0, 0);

        txtPtr = ConvertIntToDecimalStringN(text, aiMons[i].switchInCount, STR_CONV_MODE_LEFT_ALIGN, 2);
        *txtPtr = EOS;
        AddTextPrinterParameterized5(data->aiMovesWindowId, FONT_SMALL_NARROW, text, i * 41, 35 + (j + 1) * 15, 0, NULL, 0, 0);
    }

    CopyWindowToVram(data->aiMovesWindowId, COPYWIN_FULL);
    Free(text);
}

static void Task_ShowAiKnowledge(u8 taskId)
{
    u32 i, count;
    struct WindowTemplate winTemplate;
    struct BattleDebugMenu *data = GetStructPtr(taskId);
    struct Pokemon *mon;

    switch (data->aiViewState)
    {
    case 0:
        HideBg(0);
        ShowBg(1);

        // Swap battler if it's player mon
        data->aiBattlerId = data->battlerId;
        while (!BattlerHasAi(data->aiBattlerId))
        {
            if (++data->aiBattlerId >= gBattlersCount)
                data->aiBattlerId = 0;
        }

        LoadMonIconPalettes();
        for (count = 0, i = 0; i < MAX_BATTLERS_COUNT; i++)
        {
            if (GetBattlerSide(i) == B_SIDE_PLAYER && IsBattlerAlive(i))
            {
                data->spriteIds.aiIconSpriteIds[i] = CreateMonIcon(gBattleMons[i].species,
                                                         SpriteCallbackDummy,
                                                         95 + (count * 80), 17, 0, 0);
                gSprites[data->spriteIds.aiIconSpriteIds[i]].data[0] = i; // battler id
                count++;
            }
            else
            {
                data->spriteIds.aiIconSpriteIds[i] = 0xFF;
            }
        }

        mon = &GetBattlerParty(data->aiBattlerId)[gBattlerPartyIndexes[data->aiBattlerId]];

        data->aiMonSpriteId = CreateMonPicSprite(gBattleMons[data->aiBattlerId].species,
                                                 GetMonData(mon, MON_DATA_IS_SHINY),
                                                 gBattleMons[data->aiBattlerId].personality,
                                                 TRUE,
                                                 39, 130, 15, TAG_NONE);
        data->aiViewState++;
        break;
    // Put text
    case 1:
        winTemplate = CreateWindowTemplate(1, 0, 4, 27, 14, 15, 0x200);
        data->aiMovesWindowId = AddWindow(&winTemplate);
        PutWindowTilemap(data->aiMovesWindowId);
        PutAiInfoText(data);
        data->aiViewState++;
        break;
    // Input
    case 2:
        if (JOY_NEW(SELECT_BUTTON | B_BUTTON))
        {
            SwitchToDebugView(taskId);
            HideBg(1);
            ShowBg(0);
            return;
        }
        break;
    }
}

#define sConditionSpriteId data[1]

static void Task_ShowAiParty(u8 taskId)
{
    u32 i, ailment;
    struct WindowTemplate winTemplate;
    struct AiPartyMon *aiMons;
    struct BattleDebugMenu *data = GetStructPtr(taskId);

    switch (data->aiViewState)
    {
    case 0:
        HideBg(0);
        ShowBg(1);

        LoadMonIconPalettes();
        LoadPartyMenuAilmentGfx();
        data->aiBattlerId = data->battlerId;
        aiMons = AI_PARTY->mons[GetBattlerSide(data->aiBattlerId)];
        for (i = 0; i < AI_PARTY->count[GetBattlerSide(data->aiBattlerId)]; i++)
        {
            u16 species = SPECIES_NONE; // Question mark
            if (aiMons[i].wasSentInBattle && aiMons[i].species)
                species = aiMons[i].species;
            data->spriteIds.aiPartyIcons[i] = CreateMonIcon(species, SpriteCallbackDummy, (i * 41) + 15, 7, 1, 0);
            gSprites[data->spriteIds.aiPartyIcons[i]].oam.priority = 0;

            gSprites[data->spriteIds.aiPartyIcons[i]].sConditionSpriteId = CreateSprite(&gSpriteTemplate_StatusIcons, (i * 41) + 15, 7, 0);
            gSprites[gSprites[data->spriteIds.aiPartyIcons[i]].sConditionSpriteId].oam.priority = 0;
            if (aiMons[i].isFainted)
                ailment = AILMENT_FNT;
            else
                ailment = GetAilmentFromStatus(aiMons[i].status);

            if (ailment != AILMENT_NONE)
                StartSpriteAnim(&gSprites[gSprites[data->spriteIds.aiPartyIcons[i]].sConditionSpriteId], ailment - 1);
            else
                gSprites[gSprites[data->spriteIds.aiPartyIcons[i]].sConditionSpriteId].invisible = TRUE;
        }
        for (; i < PARTY_SIZE; i++)
            data->spriteIds.aiPartyIcons[i] = 0xFF;
        data->aiViewState++;
        break;
    // Put text
    case 1:
        winTemplate = CreateWindowTemplate(1, 0, 3, 29, 16, 15, 0x150);
        data->aiMovesWindowId = AddWindow(&winTemplate);
        PutWindowTilemap(data->aiMovesWindowId);
        PutAiPartyText(data);
        data->aiViewState++;
        break;
    // Input
    case 2:
        if (JOY_NEW(SELECT_BUTTON | B_BUTTON))
        {
            SwitchToDebugViewFromAiParty(taskId);
            HideBg(1);
            ShowBg(0);
            return;
        }
        break;
    }
}

static void SwitchToAiInfoView(u8 taskId)
{
    gTasks[taskId].func = Task_ShowAiKnowledge;
    GetStructPtr(taskId)->aiViewState = 0;
}

static void SwitchToAiPartyView(u8 taskId)
{
    gTasks[taskId].func = Task_ShowAiParty;
    GetStructPtr(taskId)->aiViewState = 0;
}

static void SwitchToDebugViewFromAiParty(u8 taskId)
{
    u32 i;
    struct BattleDebugMenu *data = GetStructPtr(taskId);

    FreeMonIconPalettes();
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (data->spriteIds.aiPartyIcons[i] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[gSprites[data->spriteIds.aiPartyIcons[i]].sConditionSpriteId]);
            FreeAndDestroyMonIconSprite(&gSprites[data->spriteIds.aiPartyIcons[i]]);
        }
    }
    ClearWindowTilemap(data->aiMovesWindowId);
    RemoveWindow(data->aiMovesWindowId);

    gTasks[taskId].func = Task_DebugMenuProcessInput;
}

#undef sConditionSpriteId

static void SwitchToDebugView(u8 taskId)
{
    CleanUpAiInfoWindow(taskId);
    gTasks[taskId].func = Task_DebugMenuProcessInput;
}

static void Task_DebugMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_DebugMenuProcessInput;
}

static void Task_DebugMenuProcessInput(u8 taskId)
{
    s32 listItemId = 0;
    struct BattleDebugMenu *data = GetStructPtr(taskId);

    // Exit the menu.
    if (JOY_NEW(SELECT_BUTTON) || ((JOY_NEW(B_BUTTON)) && data->activeWindow == ACTIVE_WIN_MAIN))
    {
        BeginNormalPaletteFade(-1, 0, 0, 0x10, 0);
        gTasks[taskId].func = Task_DebugMenuFadeOut;
        return;
    }

    // Try changing active battler.
    if (JOY_NEW(R_BUTTON))
    {
        if (data->battlerId++ == gBattlersCount - 1)
            data->battlerId = 0;
        UpdateWindowsOnChangedBattler(data);
    }
    else if (JOY_NEW(L_BUTTON))
    {
        if (data->battlerId-- == 0)
            data->battlerId = gBattlersCount - 1;
        UpdateWindowsOnChangedBattler(data);
    }

    // A main list item is active, handle input.
    if (data->activeWindow == ACTIVE_WIN_MAIN)
    {
        listItemId = ListMenu_ProcessInput(data->mainListTaskId);
        if (listItemId != LIST_CANCEL && listItemId != LIST_NOTHING_CHOSEN && listItemId < LIST_ITEM_COUNT)
        {
            if (listItemId == LIST_ITEM_AI_MOVES_PTS && JOY_NEW(A_BUTTON))
            {
                SwitchToAiPointsView(taskId);
                return;
            }
            else if (listItemId == LIST_ITEM_AI_INFO && JOY_NEW(A_BUTTON))
            {
                SwitchToAiInfoView(taskId);
                return;
            }
            else if (listItemId == LIST_ITEM_AI_PARTY && JOY_NEW(A_BUTTON))
            {
                SwitchToAiPartyView(taskId);
                return;
            }
            data->currentMainListItemId = listItemId;

            // Create the secondary menu list.
            CreateSecondaryListMenu(data);
            PrintSecondaryEntries(data);
            data->activeWindow = ACTIVE_WIN_SECONDARY;
        }
    }
    // Secondary list is active, handle input.
    else if (data->activeWindow == ACTIVE_WIN_SECONDARY)
    {
        listItemId = ListMenu_ProcessInput(data->secondaryListTaskId);
        if (listItemId == LIST_CANCEL)
        {
            DestroyListMenuTask(data->secondaryListTaskId, NULL, NULL);
            ClearStdWindowAndFrameToTransparent(data->secondaryListWindowId, TRUE);
            RemoveWindow(data->secondaryListWindowId);
            data->activeWindow = ACTIVE_WIN_MAIN;
            data->secondaryListTaskId = 0xFF;
        }
        else if (listItemId != LIST_NOTHING_CHOSEN)
        {
            data->currentSecondaryListItemId = listItemId;
            data->modifyWindowId = AddWindow(&sModifyWindowTemplate);
            PutWindowTilemap(data->modifyWindowId);
            CopyWindowToVram(data->modifyWindowId, COPYWIN_FULL);
            SetUpModifyArrows(data);
            PrintDigitChars(data);
            data->activeWindow = ACTIVE_WIN_MODIFY;
        }
    }
    // Handle value modifying.
    else if (data->activeWindow == ACTIVE_WIN_MODIFY)
    {
        if (JOY_NEW(B_BUTTON | A_BUTTON))
        {
            ClearStdWindowAndFrameToTransparent(data->modifyWindowId, TRUE);
            RemoveWindow(data->modifyWindowId);
            DestroyModifyArrows(data);
            data->activeWindow = ACTIVE_WIN_SECONDARY;
        }
        else if (JOY_NEW(DPAD_RIGHT))
        {
            if (data->modifyArrows.currentDigit != (data->modifyArrows.maxDigits - 1))
            {
                data->modifyArrows.currentDigit++;
                gSprites[data->modifyArrows.arrowSpriteId[0]].x2 += 6;
                gSprites[data->modifyArrows.arrowSpriteId[1]].x2 += 6;
            }
        }
        else if (JOY_NEW(DPAD_LEFT))
        {
            if (data->modifyArrows.currentDigit != 0)
            {
                data->modifyArrows.currentDigit--;
                gSprites[data->modifyArrows.arrowSpriteId[0]].x2 -= 6;
                gSprites[data->modifyArrows.arrowSpriteId[1]].x2 -= 6;
            }
        }
        else if (JOY_NEW(DPAD_UP))
        {
            if (TryMoveDigit(&data->modifyArrows, TRUE))
            {
                PrintDigitChars(data);
                UpdateBattlerValue(data);
                PrintSecondaryEntries(data);
            }
        }
        else if (JOY_NEW(DPAD_DOWN))
        {
            if (TryMoveDigit(&data->modifyArrows, FALSE))
            {
                PrintDigitChars(data);
                UpdateBattlerValue(data);
                PrintSecondaryEntries(data);
            }
        }
    }
}

static void Task_DebugMenuFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        struct BattleDebugMenu *data = GetStructPtr(taskId);
        DestroyListMenuTask(data->mainListTaskId, 0, 0);
        if (data->secondaryListTaskId != 0xFF)
            DestroyListMenuTask(data->secondaryListTaskId, 0, 0);

        FreeAllWindowBuffers();
        UpdateMonData(data);
        gBattleStruct->debugBattler = data->battlerId;
        Free(data);
        DestroyTask(taskId);
        SetMainCallback2(ReshowBattleScreenAfterMenu);
    }
}

static void PrintOnBattlerWindow(u8 windowId, u8 battlerId)
{
    u8 text[POKEMON_NAME_LENGTH + 10];

    text[0] = CHAR_0 + battlerId;
    text[1] = CHAR_SPACE;
    text[2] = CHAR_HYPHEN;
    text[3] = CHAR_SPACE;
    StringCopy(&text[4], gBattleMons[battlerId].nickname);

    FillWindowPixelBuffer(windowId, 0x11);
    AddTextPrinterParameterized(windowId, FONT_NORMAL, text, 0, 0, 0, NULL);
    CopyWindowToVram(windowId, COPYWIN_FULL);
}

static void UpdateWindowsOnChangedBattler(struct BattleDebugMenu *data)
{
    PrintOnBattlerWindow(data->battlerWindowId, data->battlerId);
    if (data->secondaryListTaskId != 0xFF)
    {
        DestroyListMenuTask(data->secondaryListTaskId, 0, 0);
        RemoveWindow(data->secondaryListWindowId);
        CreateSecondaryListMenu(data);
        data->currentSecondaryListItemId = 0;
        PrintSecondaryEntries(data);
    }
    if (data->activeWindow == ACTIVE_WIN_MODIFY)
    {
        DestroyModifyArrows(data);
        SetUpModifyArrows(data);
        PrintDigitChars(data);
    }
}


static void CreateSecondaryListMenu(struct BattleDebugMenu *data)
{
    struct WindowTemplate winTemplate;
    struct ListMenuTemplate listTemplate;
    u8 itemsCount = 1;

    winTemplate = sSecondaryListWindowTemplate;
    listTemplate = sSecondaryListTemplate;

    switch (data->currentMainListItemId)
    {
    case LIST_ITEM_ABILITY:
        itemsCount = 1;
        break;
    case LIST_ITEM_HELD_ITEM:
        itemsCount = 1;
        break;
    case LIST_ITEM_TYPES:
        itemsCount = 3;
        break;
    case LIST_ITEM_MOVES:
        itemsCount = 5;
        break;
    case LIST_ITEM_PP:
        itemsCount = 4;
        break;
    case LIST_ITEM_STATS:
        listTemplate.items = sStatsListItems;
        itemsCount = ARRAY_COUNT(sStatsListItems);
        break;
    case LIST_ITEM_STAT_STAGES:
        itemsCount = 8;
        break;
    case LIST_ITEM_STATUS1:
        listTemplate.items = sStatus1ListItems;
        itemsCount = ARRAY_COUNT(sStatus1ListItems);
        data->bitfield = sStatus1Bitfield;
        break;
    case LIST_ITEM_STATUS2:
        listTemplate.items = sStatus2ListItems;
        itemsCount = ARRAY_COUNT(sStatus2ListItems);
        data->bitfield = sStatus2Bitfield;
        break;
    case LIST_ITEM_STATUS3:
        listTemplate.items = sStatus3ListItems;
        itemsCount = ARRAY_COUNT(sStatus3ListItems);
        data->bitfield = sStatus3Bitfield;
        break;
    case LIST_ITEM_STATUS4:
        listTemplate.items = sStatus4ListItems;
        itemsCount = ARRAY_COUNT(sStatus4ListItems);
        data->bitfield = sStatus4Bitfield;
        break;
    case LIST_ITEM_AI:
        listTemplate.items = sAIListItems;
        itemsCount = ARRAY_COUNT(sAIListItems);
        data->bitfield = sAIBitfield;
        break;
    case LIST_ITEM_VARIOUS:
        listTemplate.items = sVariousListItems;
        itemsCount = ARRAY_COUNT(sVariousListItems);
        break;
    case LIST_ITEM_SIDE_STATUS:
        listTemplate.items = sSideStatusListItems;
        itemsCount = ARRAY_COUNT(sSideStatusListItems);
        break;
    case LIST_ITEM_AI_MOVES_PTS:
    case LIST_ITEM_AI_INFO:
        return;
    }

    data->secondaryListItemCount = itemsCount;
    data->secondaryListWindowId = AddWindow(&winTemplate);

    listTemplate.totalItems = itemsCount;
    listTemplate.maxShowed = itemsCount;
    if (listTemplate.maxShowed > 7 && !sHasChangeableEntries[data->currentMainListItemId])
        listTemplate.maxShowed = 7;
    listTemplate.windowId = data->secondaryListWindowId;

    data->secondaryListTaskId = ListMenuInit(&listTemplate, 0, 0);
    CopyWindowToVram(data->secondaryListWindowId, COPYWIN_FULL);
}

static void PadString(const u8 *src, u8 *dst)
{
    u32 i;

    for (i = 0; i < 19 && src[i] != EOS; i++)
        dst[i] = src[i];

    for (; i < 19; i++)
        dst[i] = CHAR_SPACE;

    dst[i] = EOS;
}

static const u8 sTextAll[] = _("全部");

static void PrintSecondaryEntries(struct BattleDebugMenu *data)
{
    u8 text[20];
    s32 i;
    struct TextPrinterTemplate printer;
    u8 yMultiplier;

    // Do not print entries if they are not changing.
    if (!sHasChangeableEntries[data->currentMainListItemId])
        return;

    yMultiplier = (GetFontAttribute(sSecondaryListTemplate.fontId, 1) + sSecondaryListTemplate.itemVerticalPadding);

    printer.windowId = data->secondaryListWindowId;
    printer.fontId = 1;
    printer.unk = 0;
    printer.letterSpacing = 0;
    printer.lineSpacing = 1;
    printer.fgColor = 2;
    printer.bgColor = 1;
    printer.shadowColor = 3;
    printer.x = sSecondaryListTemplate.item_X;
    printer.currentX = sSecondaryListTemplate.item_X;
    printer.currentChar = text;

    switch (data->currentMainListItemId)
    {
    case LIST_ITEM_MOVES:
    case LIST_ITEM_PP:
        for (i = 0; i < 4; i++)
        {
            PadString(GetMoveName(gBattleMons[data->battlerId].moves[i]), text);
            printer.currentY = printer.y = (i * yMultiplier) + sSecondaryListTemplate.upText_Y;
            AddTextPrinter(&printer, 0, NULL);
        }
        // Allow changing all moves at once. Useful for testing in wild doubles.
        if (data->currentMainListItemId == LIST_ITEM_MOVES)
        {
            PadString(sTextAll, text);
            printer.currentY = printer.y = (i * yMultiplier) + sSecondaryListTemplate.upText_Y;
            AddTextPrinter(&printer, 0, NULL);
        }
        break;
    case LIST_ITEM_ABILITY:
        PadString(gAbilitiesInfo[gBattleMons[data->battlerId].ability].name, text);
        printer.currentY = printer.y = sSecondaryListTemplate.upText_Y;
        AddTextPrinter(&printer, 0, NULL);
        break;
    case LIST_ITEM_HELD_ITEM:
        PadString(ItemId_GetName(gBattleMons[data->battlerId].item), text);
        printer.currentY = printer.y = sSecondaryListTemplate.upText_Y;
        AddTextPrinter(&printer, 0, NULL);
        break;
    case LIST_ITEM_TYPES:
        for (i = 0; i < 3; i++)
        {
            u8 *types = &gBattleMons[data->battlerId].types[0];

            PadString(gTypesInfo[types[i]].name, text);
            printer.currentY = printer.y = (i * yMultiplier) + sSecondaryListTemplate.upText_Y;
            AddTextPrinter(&printer, 0, NULL);
        }
        break;
    case LIST_ITEM_STAT_STAGES:
        for (i = 0; i < NUM_BATTLE_STATS - 1; i++)
        {
            u8 *txtPtr = StringCopy(text, gStatNamesTable[STAT_ATK + i]);
            txtPtr[0] = CHAR_SPACE;
            if (gBattleMons[data->battlerId].statStages[STAT_ATK + i] >= DEFAULT_STAT_STAGE)
            {
                txtPtr[1] = CHAR_PLUS;
                txtPtr[2] = CHAR_0 + (gBattleMons[data->battlerId].statStages[STAT_ATK + i] - DEFAULT_STAT_STAGE);
            }
            else
            {
                txtPtr[1] = CHAR_HYPHEN;
                txtPtr[2] = CHAR_6 - (gBattleMons[data->battlerId].statStages[STAT_ATK + i]);
            }
            txtPtr[3] = EOS;

            PadString(text, text);
            printer.currentY = printer.y = (i * yMultiplier) + sSecondaryListTemplate.upText_Y;
            AddTextPrinter(&printer, 0, NULL);
        }
        // Allow changing all stat stages at once.
        PadString(sTextAll, text);
        printer.currentY = printer.y = (i * yMultiplier) + sSecondaryListTemplate.upText_Y;
        AddTextPrinter(&printer, 0, NULL);
        break;
    }
}

static void DestroyModifyArrows(struct BattleDebugMenu *data)
{
    if (data->modifyArrows.arrowSpriteId[0] != 0xFF)
        DestroySpriteAndFreeResources(&gSprites[data->modifyArrows.arrowSpriteId[0]]);
    if (data->modifyArrows.arrowSpriteId[1] != 0xFF)
        DestroySpriteAndFreeResources(&gSprites[data->modifyArrows.arrowSpriteId[1]]);
}

static void PrintDigitChars(struct BattleDebugMenu *data)
{
    s32 i;
    u8 text[MAX_MODIFY_DIGITS + 1];

    for (i = 0; i < data->modifyArrows.maxDigits; i++)
        text[i] = data->modifyArrows.charDigits[i];

    text[i] = EOS;

    FillWindowPixelBuffer(data->modifyWindowId, 0x11);
    AddTextPrinterParameterized(data->modifyWindowId, FONT_NORMAL, text, 3, 0, 0, NULL);
}

static const u32 GetBitfieldToAndValue(u32 currBit, u32 bitsCount)
{
    u32 i;
    u32 toAnd = 0;

    for (i = 0; i < bitsCount; i++)
        toAnd |= (1 << (currBit + i));

    return toAnd;
}

static const u32 GetBitfieldValue(u32 value, u32 currBit, u32 bitsCount)
{
    return (value & (GetBitfieldToAndValue(currBit, bitsCount))) >> currBit;
}

static void UpdateBattlerValue(struct BattleDebugMenu *data)
{
    u32 i;
    switch (data->modifyArrows.typeOfVal)
    {
    case VAL_U8:
        *(u8 *)(data->modifyArrows.modifiedValPtr) = data->modifyArrows.currValue;
        break;
    case VAL_S8:
        *(s8 *)(data->modifyArrows.modifiedValPtr) = data->modifyArrows.currValue;
        break;
    case VAL_U16:
        *(u16 *)(data->modifyArrows.modifiedValPtr) = data->modifyArrows.currValue;
        break;
    case VAR_U16_4_ENTRIES:
        ((u16 *)(data->modifyArrows.modifiedValPtr))[0] = data->modifyArrows.currValue;
        ((u16 *)(data->modifyArrows.modifiedValPtr))[1] = data->modifyArrows.currValue;
        ((u16 *)(data->modifyArrows.modifiedValPtr))[2] = data->modifyArrows.currValue;
        ((u16 *)(data->modifyArrows.modifiedValPtr))[3] = data->modifyArrows.currValue;
        break;
    case VAL_ALL_STAT_STAGES:
        for (i = 0; i < NUM_BATTLE_STATS; i++)
            gBattleMons[data->battlerId].statStages[i] = data->modifyArrows.currValue;
        break;
    case VAL_U32:
        *(u32 *)(data->modifyArrows.modifiedValPtr) = data->modifyArrows.currValue;
        break;
    case VAL_BITFIELD_32:
        *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~(GetBitfieldToAndValue(data->bitfield[data->currentSecondaryListItemId].currBit, data->bitfield[data->currentSecondaryListItemId].bitsCount));
        *(u32 *)(data->modifyArrows.modifiedValPtr) |= (data->modifyArrows.currValue << data->bitfield[data->currentSecondaryListItemId].currBit);
        break;
    case VAR_SIDE_STATUS:
        *GetSideStatusValue(data, TRUE, data->modifyArrows.currValue != 0) = data->modifyArrows.currValue;
        break;
    case VAR_SHOW_HP:
        (*(struct BattleSpriteInfo*)(data->modifyArrows.modifiedValPtr)).hpNumbersNoBars = data->modifyArrows.currValue;
        break;
    case VAR_SUBSTITUTE:
        *(u8 *)(data->modifyArrows.modifiedValPtr) = data->modifyArrows.currValue;
        if (*(u8 *)(data->modifyArrows.modifiedValPtr) == 0)
        {
            gBattleMons[data->battlerId].status2 &= ~STATUS2_SUBSTITUTE;
            gBattleSpritesDataPtr->battlerData[data->battlerId].behindSubstitute = 0;
        }
        else
        {
            gBattleMons[data->battlerId].status2 |= STATUS2_SUBSTITUTE;
            gBattleSpritesDataPtr->battlerData[data->battlerId].behindSubstitute = 1;
        }
        break;
    case VAR_IN_LOVE:
        if (data->modifyArrows.currValue)
        {
            if (IsBattlerAlive(BATTLE_OPPOSITE(data->battlerId)))
                gBattleMons[data->battlerId].status2 |= STATUS2_INFATUATED_WITH(BATTLE_OPPOSITE(data->battlerId));
            else
                gBattleMons[data->battlerId].status2 |= STATUS2_INFATUATED_WITH(BATTLE_PARTNER(BATTLE_OPPOSITE(data->battlerId)));
        }
        else
        {
            gBattleMons[data->battlerId].status2 &= ~STATUS2_INFATUATION;
        }
        break;
    }
    data->battlerWasChanged[data->battlerId] = TRUE;
}

static u32 CharDigitsToValue(u8 *charDigits, u8 maxDigits)
{
    s32 i;
    u8 id = 0;
    u32 newValue = 0;
    u8 valueDigits[MAX_MODIFY_DIGITS];

    for (i = 0; i < MAX_MODIFY_DIGITS; i++)
        valueDigits[i] = charDigits[i] - CHAR_0;

    if (maxDigits >= MAX_MODIFY_DIGITS)
        newValue += valueDigits[id++] * 1000;
    if (maxDigits >= MAX_MODIFY_DIGITS - 1)
        newValue += valueDigits[id++] * 100;
    if (maxDigits >= MAX_MODIFY_DIGITS - 2)
        newValue += valueDigits[id++] * 10;
    if (maxDigits >= MAX_MODIFY_DIGITS - 3)
        newValue += valueDigits[id++];

    return newValue;
}

static void ValueToCharDigits(u8 *charDigits, u32 newValue, u8 maxDigits)
{
    s32 i;
    u8 valueDigits[MAX_MODIFY_DIGITS];
    u8 id = 0;

    if (maxDigits >= MAX_MODIFY_DIGITS)
        valueDigits[id++] = newValue / 1000;
    if (maxDigits >= MAX_MODIFY_DIGITS - 1)
        valueDigits[id++] = (newValue % 1000) / 100;
    if (maxDigits >= MAX_MODIFY_DIGITS - 2)
        valueDigits[id++] = (newValue % 100) / 10;
    if (maxDigits >= MAX_MODIFY_DIGITS - 3)
        valueDigits[id++] = newValue % 10;

    for (i = 0; i < MAX_MODIFY_DIGITS; i++)
        charDigits[i] = valueDigits[i] + CHAR_0;
}

static u16 *GetSideStatusValue(struct BattleDebugMenu *data, bool32 changeStatus, bool32 statusTrue)
{
    struct SideTimer *sideTimer = &gSideTimers[GetBattlerSide(data->battlerId)];

    switch (data->currentSecondaryListItemId)
    {
    case LIST_SIDE_REFLECT:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_REFLECT;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_REFLECT;
            sideTimer->reflectBattlerId = data->battlerId;
        }
        return &sideTimer->reflectTimer;
    case LIST_SIDE_LIGHTSCREEN:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_LIGHTSCREEN;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_LIGHTSCREEN;
            sideTimer->lightscreenBattlerId = data->battlerId;
        }
        return &sideTimer->lightscreenTimer;
    case LIST_SIDE_STICKY_WEB:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_STICKY_WEB;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_STICKY_WEB;
            sideTimer->stickyWebBattlerId = data->battlerId;
            sideTimer->stickyWebBattlerSide = GetBattlerSide(data->battlerId);
        }
        return &sideTimer->stickyWebAmount;
    case LIST_SIDE_SPIKES:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_SPIKES;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_SPIKES;
        }
        return &sideTimer->spikesAmount;
    case LIST_SIDE_SAFEGUARD:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_SAFEGUARD;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_SAFEGUARD;
            sideTimer->safeguardBattlerId = data->battlerId;
        }
        return &sideTimer->safeguardTimer;
    case LIST_SIDE_MIST:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_MIST;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_MIST;
            sideTimer->mistBattlerId = data->battlerId;
        }
        return &sideTimer->mistTimer;
    case LIST_SIDE_TAILWIND:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_TAILWIND;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_TAILWIND;
            sideTimer->tailwindBattlerId = data->battlerId;
        }
        return &sideTimer->tailwindTimer;
    case LIST_SIDE_AURORA_VEIL:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_AURORA_VEIL;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_AURORA_VEIL;
            sideTimer->auroraVeilBattlerId = data->battlerId;
        }
        return &sideTimer->auroraVeilTimer;
    case LIST_SIDE_LUCKY_CHANT:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_LUCKY_CHANT;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_LUCKY_CHANT;
            sideTimer->luckyChantBattlerId = data->battlerId;
        }
        return &sideTimer->luckyChantTimer;
    case LIST_SIDE_TOXIC_SPIKES:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_TOXIC_SPIKES;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_TOXIC_SPIKES;
        }
        return &sideTimer->toxicSpikesAmount;
    case LIST_SIDE_STEALTH_ROCK:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_STEALTH_ROCK;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_STEALTH_ROCK;
        }
        return &sideTimer->stealthRockAmount;
    case LIST_SIDE_STEELSURGE:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_STEELSURGE;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_STEELSURGE;
        }
        return &sideTimer->steelsurgeAmount;
    case LIST_SIDE_DAMAGE_NON_TYPES:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_DAMAGE_NON_TYPES;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_DAMAGE_NON_TYPES;
            sideTimer->damageNonTypesType = GetMoveType(gCurrentMove);
        }
        return &sideTimer->damageNonTypesTimer;
    case LIST_SIDE_RAINBOW:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_RAINBOW;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_RAINBOW;
        }
        return &sideTimer->rainbowTimer;
    case LIST_SIDE_SEA_OF_FIRE:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_SEA_OF_FIRE;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_SEA_OF_FIRE;
        }
        return &sideTimer->seaOfFireTimer;
    case LIST_SIDE_SWAMP:
        if (changeStatus)
        {
            if (statusTrue)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_SWAMP;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_SWAMP;
        }
        return &sideTimer->swampTimer;
    default:
        return NULL;
    }
}

static void SetUpModifyArrows(struct BattleDebugMenu *data)
{
    LoadSpritePalette(&gSpritePalette_Arrow);
    data->modifyArrows.arrowSpriteId[0] = CreateSprite(&gSpriteTemplate_Arrow, 207, 12, 0);
    data->modifyArrows.arrowSpriteId[1] = CreateSprite(&gSpriteTemplate_Arrow, 207, 36, 0);
    gSprites[data->modifyArrows.arrowSpriteId[1]].animNum = 1;
    switch (data->currentMainListItemId)
    {
    case LIST_ITEM_ABILITY:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = ABILITIES_COUNT - 1;
        data->modifyArrows.maxDigits = 3;
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].ability;
        data->modifyArrows.typeOfVal = VAL_U16;
        data->modifyArrows.currValue = gBattleMons[data->battlerId].ability;
        break;
    case LIST_ITEM_MOVES:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = MOVES_COUNT - 1;
        data->modifyArrows.maxDigits = 3;
        if (data->currentSecondaryListItemId == 4)
        {
            data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].moves[0];
            data->modifyArrows.currValue = gBattleMons[data->battlerId].moves[0];
            data->modifyArrows.typeOfVal = VAR_U16_4_ENTRIES;
        }
        else
        {
            data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].moves[data->currentSecondaryListItemId];
            data->modifyArrows.currValue = gBattleMons[data->battlerId].moves[data->currentSecondaryListItemId];
            data->modifyArrows.typeOfVal = VAL_U16;
        }
        break;
    case LIST_ITEM_PP:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = CalculatePPWithBonus(gBattleMons[data->battlerId].moves[data->currentSecondaryListItemId], gBattleMons[data->battlerId].ppBonuses, data->currentSecondaryListItemId);
        data->modifyArrows.maxDigits = 2;
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].pp[data->currentSecondaryListItemId];
        data->modifyArrows.typeOfVal = VAL_U8;
        data->modifyArrows.currValue = gBattleMons[data->battlerId].pp[data->currentSecondaryListItemId];
        break;
    case LIST_ITEM_HELD_ITEM:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = ITEMS_COUNT - 1;
        data->modifyArrows.maxDigits = 3;
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].item;
        data->modifyArrows.typeOfVal = VAL_U16;
        data->modifyArrows.currValue = gBattleMons[data->battlerId].item;
        break;
    case LIST_ITEM_TYPES:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = NUMBER_OF_MON_TYPES - 1;
        data->modifyArrows.maxDigits = 2;
        data->modifyArrows.modifiedValPtr = (u8 *)((&gBattleMons[data->battlerId].types[0]) + data->currentSecondaryListItemId);
        data->modifyArrows.typeOfVal = VAL_U8;
        data->modifyArrows.currValue = *(u8 *)((&gBattleMons[data->battlerId].types[0]) + data->currentSecondaryListItemId);
        break;
    case LIST_ITEM_STATS:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = 9999;
        data->modifyArrows.maxDigits = 4;
        data->modifyArrows.typeOfVal = VAL_U16;
        if (data->currentSecondaryListItemId == LIST_STAT_HP_CURRENT)
        {
            data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].hp;
            data->modifyArrows.currValue = gBattleMons[data->battlerId].hp;
            data->modifyArrows.minValue = 1;
            data->modifyArrows.maxValue = gBattleMons[data->battlerId].maxHP;
        }
        else if (data->currentSecondaryListItemId == LIST_STAT_HP_MAX)
        {
            data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].maxHP;
            data->modifyArrows.minValue = gBattleMons[data->battlerId].hp;
            data->modifyArrows.currValue = gBattleMons[data->battlerId].maxHP;
        }
        else
        {
            data->modifyArrows.modifiedValPtr = (u16 *)((&gBattleMons[data->battlerId].attack) + (data->currentSecondaryListItemId - 2));
            data->modifyArrows.currValue = *(u16 *)((&gBattleMons[data->battlerId].attack) + (data->currentSecondaryListItemId - 2));
        }
        break;
    case LIST_ITEM_STAT_STAGES:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = 12;
        data->modifyArrows.maxDigits = 2;
        if (data->currentSecondaryListItemId == NUM_BATTLE_STATS - 1) // Change all stats
        {
            data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].statStages[STAT_ATK];
            data->modifyArrows.currValue = gBattleMons[data->battlerId].statStages[STAT_ATK];
            data->modifyArrows.typeOfVal = VAL_ALL_STAT_STAGES;
        }
        else
        {
            data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].statStages[data->currentSecondaryListItemId + STAT_ATK];
            data->modifyArrows.typeOfVal = VAL_U8;
            data->modifyArrows.currValue = gBattleMons[data->battlerId].statStages[data->currentSecondaryListItemId + STAT_ATK];
        }
        break;
    case LIST_ITEM_VARIOUS:
        if (data->currentSecondaryListItemId == VARIOUS_SHOW_HP)
        {
            data->modifyArrows.minValue = 0;
            data->modifyArrows.maxValue = 1;
            data->modifyArrows.maxDigits = 1;
            data->modifyArrows.modifiedValPtr = &gBattleSpritesDataPtr->battlerData[data->battlerId];
            data->modifyArrows.typeOfVal = VAR_SHOW_HP;
            data->modifyArrows.currValue = gBattleSpritesDataPtr->battlerData[data->battlerId].hpNumbersNoBars;
        }
        else if (data->currentSecondaryListItemId == VARIOUS_SUBSTITUTE_HP)
        {
            data->modifyArrows.minValue = 0;
            data->modifyArrows.maxValue = 255;
            data->modifyArrows.maxDigits = 3;
            data->modifyArrows.modifiedValPtr = &gDisableStructs[data->battlerId].substituteHP;
            data->modifyArrows.typeOfVal = VAR_SUBSTITUTE;
            data->modifyArrows.currValue = gDisableStructs[data->battlerId].substituteHP;
        }
        else if (data->currentSecondaryListItemId == VARIOUS_IN_LOVE)
        {
            data->modifyArrows.minValue = 0;
            data->modifyArrows.maxValue = 1;
            data->modifyArrows.maxDigits = 1;
            data->modifyArrows.modifiedValPtr = NULL;
            data->modifyArrows.typeOfVal = VAR_IN_LOVE;
            data->modifyArrows.currValue = (gBattleMons[data->battlerId].status2 & STATUS2_INFATUATION) != 0;
        }
        break;
    case LIST_ITEM_STATUS1:
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].status1;
        data->modifyArrows.currValue = GetBitfieldValue(gBattleMons[data->battlerId].status1, data->bitfield[data->currentSecondaryListItemId].currBit, data->bitfield[data->currentSecondaryListItemId].bitsCount);
        data->modifyArrows.typeOfVal = VAL_BITFIELD_32;
        goto CASE_ITEM_STATUS;
    case LIST_ITEM_STATUS2:
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].status2;
        data->modifyArrows.currValue = GetBitfieldValue(gBattleMons[data->battlerId].status2, data->bitfield[data->currentSecondaryListItemId].currBit, data->bitfield[data->currentSecondaryListItemId].bitsCount);
        data->modifyArrows.typeOfVal = VAL_BITFIELD_32;
        goto CASE_ITEM_STATUS;
    case LIST_ITEM_STATUS3:
        data->modifyArrows.modifiedValPtr = &gStatuses3[data->battlerId];
        data->modifyArrows.currValue = GetBitfieldValue(gStatuses3[data->battlerId], data->bitfield[data->currentSecondaryListItemId].currBit, data->bitfield[data->currentSecondaryListItemId].bitsCount);
        data->modifyArrows.typeOfVal = VAL_BITFIELD_32;
        goto CASE_ITEM_STATUS;
    case LIST_ITEM_STATUS4:
        data->modifyArrows.modifiedValPtr = &gStatuses4[data->battlerId];
        data->modifyArrows.currValue = GetBitfieldValue(gStatuses4[data->battlerId], data->bitfield[data->currentSecondaryListItemId].currBit, data->bitfield[data->currentSecondaryListItemId].bitsCount);
        data->modifyArrows.typeOfVal = VAL_BITFIELD_32;
        goto CASE_ITEM_STATUS;
    case LIST_ITEM_AI:
        data->modifyArrows.modifiedValPtr = &gBattleResources->ai->aiFlags[data->battlerId];
        data->modifyArrows.currValue = GetBitfieldValue(gBattleResources->ai->aiFlags[data->battlerId], data->bitfield[data->currentSecondaryListItemId].currBit, data->bitfield[data->currentSecondaryListItemId].bitsCount);
        data->modifyArrows.typeOfVal = VAL_BITFIELD_32;
        goto CASE_ITEM_STATUS;
    CASE_ITEM_STATUS:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = (1 << data->bitfield[data->currentSecondaryListItemId].bitsCount) - 1;
        data->modifyArrows.maxDigits = sBitsToMaxDigit[data->bitfield[data->currentSecondaryListItemId].bitsCount];
        break;
    case LIST_ITEM_SIDE_STATUS:
        data->modifyArrows.minValue = 0;

        if (data->currentSecondaryListItemId == LIST_SIDE_SPIKES)
            data->modifyArrows.maxValue = 3;
        else if (data->currentSecondaryListItemId == LIST_SIDE_STEALTH_ROCK || data->currentSecondaryListItemId == LIST_SIDE_STICKY_WEB)
            data->modifyArrows.maxValue = 1;
        else
            data->modifyArrows.maxValue = 9;

        data->modifyArrows.maxDigits = 2;
        data->modifyArrows.modifiedValPtr = &gSideStatuses[GetBattlerSide(data->battlerId)];
        data->modifyArrows.typeOfVal = VAR_SIDE_STATUS;
        data->modifyArrows.currValue = *GetSideStatusValue(data, FALSE, FALSE);
        break;
    }

    data->modifyArrows.currentDigit = 0;
    ValueToCharDigits(data->modifyArrows.charDigits, data->modifyArrows.currValue, data->modifyArrows.maxDigits);
}

static bool32 TryMoveDigit(struct BattleDebugModifyArrows *modArrows, bool32 moveUp)
{
    s32 i;
    u8 charDigits[MAX_MODIFY_DIGITS];
    u32 newValue;

    for (i = 0; i < MAX_MODIFY_DIGITS; i++)
        charDigits[i] = modArrows->charDigits[i];

    if (moveUp)
    {
        if (charDigits[modArrows->currentDigit] == CHAR_9)
        {
            charDigits[modArrows->currentDigit] = CHAR_0;
            for (i = modArrows->currentDigit - 1; i >= 0; i--)
            {
                if (charDigits[i] == CHAR_9)
                {
                    charDigits[i] = CHAR_0;
                }
                else
                {
                    charDigits[i]++;
                    break;
                }
            }
        }
        else
            charDigits[modArrows->currentDigit]++;
    }
    else
    {
        if (charDigits[modArrows->currentDigit] == CHAR_0)
        {
            charDigits[modArrows->currentDigit] = CHAR_9;
            for (i = modArrows->currentDigit - 1; i >= 0; i--)
            {
                if (charDigits[i] == CHAR_0)
                {
                    charDigits[i] = CHAR_9;
                }
                else
                {
                    charDigits[i]--;
                    break;
                }
            }
        }
        else
            charDigits[modArrows->currentDigit]--;
    }

    newValue = CharDigitsToValue(charDigits, modArrows->maxDigits);
    if (newValue > modArrows->maxValue || newValue < modArrows->minValue)
    {
        return FALSE;
    }
    else
    {
        modArrows->currValue = newValue;
        for (i = 0; i < MAX_MODIFY_DIGITS; i++)
             modArrows->charDigits[i] = charDigits[i];
        return TRUE;
    }
}

static void UpdateMonData(struct BattleDebugMenu *data)
{
    s32 i, j;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (data->battlerWasChanged[i])
        {
            struct Pokemon *mon = GetPartyBattlerData(i);
            struct BattlePokemon *battleMon = &gBattleMons[i];

            SetMonData(mon, MON_DATA_HELD_ITEM, &battleMon->item);
            SetMonData(mon, MON_DATA_STATUS, &battleMon->status1);
            SetMonData(mon, MON_DATA_HP, &battleMon->hp);
            SetMonData(mon, MON_DATA_MAX_HP, &battleMon->maxHP);
            for (j = 0; j < 4; j++)
                SetMonData(mon, MON_DATA_MOVE1 + j, &battleMon->moves[j]);
        }
    }
}

static const u8 sText_HoldEffectNone[] = _("不眠");
static const u8 sText_HoldEffectRestoreHp[] = _("回复HP");
static const u8 sText_HoldEffectCurePar[] = _("麻痹解除");
static const u8 sText_HoldEffectCureSlp[] = _("睡眠解除");
static const u8 sText_HoldEffectCurePsn[] = _("中毒解除");
static const u8 sText_HoldEffectCureBrn[] = _("灼伤解除");
static const u8 sText_HoldEffectCureFrz[] = _("冰冻解除");
static const u8 sText_HoldEffectRestorePp[] = _("回复PP");
static const u8 sText_HoldEffectCureConfusion[] = _("混乱解除");
static const u8 sText_HoldEffectCureStatus[] = _("异常状态解除");
static const u8 sText_HoldEffectConfuseSpicy[] = _("因树果太辣混乱");
static const u8 sText_HoldEffectConfuseDry[] = _("因树果太涩混乱");
static const u8 sText_HoldEffectConfuseSweet[] = _("因树果太甜混乱");
static const u8 sText_HoldEffectConfuseBitter[] = _("因树果太苦混乱");
static const u8 sText_HoldEffectConfuseSour[] = _("因树果太酸混乱");
static const u8 sText_HoldEffectAttackUp[] = _("攻击提升");
static const u8 sText_HoldEffectDefenseUp[] = _("防御提升");
static const u8 sText_HoldEffectSpeedUp[] = _("速度提升");
static const u8 sText_HoldEffectSpAttackUp[] = _("特攻提升");
static const u8 sText_HoldEffectSpDefenseUp[] = _("特防提升");
static const u8 sText_HoldEffectCriticalUp[] = _("击中要害率提升");
static const u8 sText_HoldEffectRandomStatUp[] = _("随机能力提升");
static const u8 sText_HoldEffectEvasionUp[] = _("闪避率提升");
static const u8 sText_HoldEffectRestoreStats[] = _("能力恢复");
static const u8 sText_HoldEffectMachoBrace[] = _("强制锻炼器");
static const u8 sText_HoldEffectExpShare[] = _("学习装置");
static const u8 sText_HoldEffectQuickClaw[] = _("先制之爪");
static const u8 sText_HoldEffectFriendshipUp[] = _("亲密度上升");
static const u8 sText_HoldEffectMentalHerb[] = _("心灵香草");
static const u8 sText_HoldEffectChoiceBand[] = _("讲究头带");
static const u8 sText_HoldEffectFlinch[] = _("畏缩");
static const u8 sText_HoldEffectBugPower[] = _("虫属性强化");
static const u8 sText_HoldEffectDoublePrize[] = _("零花钱翻倍");
static const u8 sText_HoldEffectRepel[] = _("除虫喷雾");
static const u8 sText_HoldEffectSoulDew[] = _("心之水滴");
static const u8 sText_HoldEffectDeepSeaTooth[] = _("深海之牙");
static const u8 sText_HoldEffectDeepSeaScale[] = _("深海鳞片");
static const u8 sText_HoldEffectCanAlwaysRun[] = _("必定能逃走");
static const u8 sText_HoldEffectPreventEvolve[] = _("不会进化");
static const u8 sText_HoldEffectFocusBand[] = _("气势头带");
static const u8 sText_HoldEffectLuckyEgg[] = _("幸运蛋");
static const u8 sText_HoldEffectScopeLens[] = _("焦点镜");
static const u8 sText_HoldEffectSteelPower[] = _("钢属性强化");
static const u8 sText_HoldEffectLeftovers[] = _("吃剩的东西");
static const u8 sText_HoldEffectDragonScale[] = _("龙之鳞片");
static const u8 sText_HoldEffectLightBall[] = _("电气球");
static const u8 sText_HoldEffectGroundPower[] = _("地面属性强化");
static const u8 sText_HoldEffectRockPower[] = _("岩石属性强化");
static const u8 sText_HoldEffectGrassPower[] = _("草属性强化");
static const u8 sText_HoldEffectDarkPower[] = _("恶属性强化");
static const u8 sText_HoldEffectFightingPower[] = _("格斗属性强化");
static const u8 sText_HoldEffectElectricPower[] = _("电属性强化");
static const u8 sText_HoldEffectWaterPower[] = _("水属性强化");
static const u8 sText_HoldEffectFlyingPower[] = _("飞行属性强化");
static const u8 sText_HoldEffectPoisonPower[] = _("毒属性强化");
static const u8 sText_HoldEffectIcePower[] = _("冰属性强化");
static const u8 sText_HoldEffectGhostPower[] = _("幽灵属性强化");
static const u8 sText_HoldEffectPsychicPower[] = _("超能力属性强化");
static const u8 sText_HoldEffectFirePower[] = _("火属性强化");
static const u8 sText_HoldEffectDragonPower[] = _("龙属性强化");
static const u8 sText_HoldEffectNormalPower[] = _("一般属性强化");
static const u8 sText_HoldEffectUpgrade[] = _("升级数据");
static const u8 sText_HoldEffectShellBell[] = _("贝壳之铃");
static const u8 sText_HoldEffectLuckyPunch[] = _("吉利拳");
static const u8 sText_HoldEffectMetalPowder[] = _("金属粉");
static const u8 sText_HoldEffectThickClub[] = _("粗骨头");
static const u8 sText_HoldEffectLeek[] = _("大葱");
static const u8 sText_HoldEffectChoiceScarf[] = _("讲究围巾");
static const u8 sText_HoldEffectChoiceSpecs[] = _("讲究眼镜");
static const u8 sText_HoldEffectDampRock[] = _("潮湿岩石");
static const u8 sText_HoldEffectGripClaw[] = _("紧缠钩爪");
static const u8 sText_HoldEffectHeatRock[] = _("炽热岩石");
static const u8 sText_HoldEffectIcyRock[] = _("冰冷岩石");
static const u8 sText_HoldEffectLightClay[] = _("光之黏土");
static const u8 sText_HoldEffectSmoothRock[] = _("沙沙岩石");
static const u8 sText_HoldEffectPowerHerb[] = _("强力香草");
static const u8 sText_HoldEffectBigRoot[] = _("大根茎");
static const u8 sText_HoldEffectExpertBelt[] = _("达人带");
static const u8 sText_HoldEffectLifeOrb[] = _("生命宝珠");
static const u8 sText_HoldEffectMetronome[] = _("挥指");
static const u8 sText_HoldEffectMuscleBand[] = _("力量头带");
static const u8 sText_HoldEffectWideLens[] = _("广角镜");
static const u8 sText_HoldEffectWiseGlasses[] = _("博识眼镜");
static const u8 sText_HoldEffectZoomLens[] = _("对焦镜");
static const u8 sText_HoldEffectLaggingTail[] = _("后攻之尾");
static const u8 sText_HoldEffectFocusSash[] = _("气势披带");
static const u8 sText_HoldEffectFlameOrb[] = _("火焰宝珠");
static const u8 sText_HoldEffectToxicOrb[] = _("剧毒宝珠");
static const u8 sText_HoldEffectStickyBarb[] = _("附着针");
static const u8 sText_HoldEffectIronBall[] = _("黑色铁球");
static const u8 sText_HoldEffectBlackSludge[] = _("黑色污泥");
static const u8 sText_HoldEffectDestinyKnot[] = _("红线");
static const u8 sText_HoldEffectShedShell[] = _("美丽空壳");
static const u8 sText_HoldEffectQuickPowder[] = _("速度粉");
static const u8 sText_HoldEffectAdamantOrb[] = _("金刚宝珠");
static const u8 sText_HoldEffectLustrousOrb[] = _("白玉宝珠");
static const u8 sText_HoldEffectGriseousOrb[] = _("白金宝珠");
static const u8 sText_HoldEffectEnigmaBerry[] = _("谜芝果");
static const u8 sText_HoldEffectResistBerry[] = _("属性抵抗类树果");
static const u8 sText_HoldEffectPowerItem[] = _("属性增强类道具");
static const u8 sText_HoldEffectRestorePctHp[] = _("一定比例HP回复");
static const u8 sText_HoldEffectMicleBerry[] = _("奇秘果");
static const u8 sText_HoldEffectCustapBerry[] = _("释陀果");
static const u8 sText_HoldEffectJabocaBerry[] = _("嘉珍果");
static const u8 sText_HoldEffectRowapBerry[] = _("雾莲果");
static const u8 sText_HoldEffectKeeBerry[] = _("亚开果");
static const u8 sText_HoldEffectMarangaBerry[] = _("香罗果");
static const u8 sText_HoldEffectFloatStone[] = _("轻石");
static const u8 sText_HoldEffectEviolite[] = _("进化奇石");
static const u8 sText_HoldEffectAssaultVest[] = _("突击背心");
static const u8 sText_HoldEffectDrive[] = _("属性卡带");
static const u8 sText_HoldEffectGems[] = _("属性宝石");
static const u8 sText_HoldEffectRockyHelmet[] = _("凸凸头盔");
static const u8 sText_HoldEffectAirBalloon[] = _("气球");
static const u8 sText_HoldEffectRedCard[] = _("红牌");
static const u8 sText_HoldEffectRingTarget[] = _("标靶");
static const u8 sText_HoldEffectBindingBand[] = _("紧绑束带");
static const u8 sText_HoldEffectEjectButton[] = _("逃脱按键");
static const u8 sText_HoldEffectAbsorbBulb[] = _("球根");
static const u8 sText_HoldEffectCellBattery[] = _("充电电池");
static const u8 sText_HoldEffectFairyPower[] = _("妖精属性强化");
static const u8 sText_HoldEffectMegaStone[] = _("超级进化石");
static const u8 sText_HoldEffectSafetyGoggles[] = _("防尘护目镜");
static const u8 sText_HoldEffectLuminousMoss[] = _("光苔");
static const u8 sText_HoldEffectSnowball[] = _("雪丸");
static const u8 sText_HoldEffectWeaknessPolicy[] = _("弱点保险");
static const u8 sText_HoldEffectPrimalOrb[] = _("原始回归宝珠");
static const u8 sText_HoldEffectProtectivePads[] = _("部位护具");
static const u8 sText_HoldEffectTerrainExtender[] = _("大地膜");
static const u8 sText_HoldEffectSeeds[] = _("场地种子");
static const u8 sText_HoldEffectAdrenalineOrb[] = _("胆怯球");
static const u8 sText_HoldEffectMemory[] = _("属性存储碟");
static const u8 sText_HoldEffectZCrystal[] = _("Z纯晶");
static const u8 sText_HoldEffectPlate[] = _("属性石板");
static const u8 sText_HoldEffectUtilityUmbrella[] = _("万能伞");
static const u8 sText_HoldEffectEjectPack[] = _("避难背包");
static const u8 sText_HoldEffectRoomService[] = _("客房服务");
static const u8 sText_HoldEffectBlunderPolicy[] = _("打空保险");
static const u8 sText_HoldEffectHeavyDutyBoots[] = _("厚底靴");
static const u8 sText_HoldEffectThroatSpray[] = _("爽喉喷雾");
static const u8 sText_HoldEffectAbilityShield[] = _("特性护具");
static const u8 sText_HoldEffectClearAmulet[] = _("清净坠饰");
static const u8 sText_HoldEffectMirrorHerb[] = _("模仿香草");
static const u8 sText_HoldEffectPunchingGlove[] = _("拳击手套");
static const u8 sText_HoldEffectCovertCloak[] = _("密探斗篷");
static const u8 sText_HoldEffectLoadedDice[] = _("机变骰子");
static const u8 sText_HoldEffectBoosterEnergy[] = _("驱劲能量");
static const u8 sText_HoldEffectBerserkGene[] = _("破坏基因");
static const u8 sText_HoldEffectOgerponMask[] = _("厄诡椪面具");
static const u8 *const sHoldEffectNames[] =
{
    [HOLD_EFFECT_NONE] = sText_HoldEffectNone,
    [HOLD_EFFECT_RESTORE_HP] = sText_HoldEffectRestoreHp,
    [HOLD_EFFECT_CURE_PAR] = sText_HoldEffectCurePar,
    [HOLD_EFFECT_CURE_SLP] = sText_HoldEffectCureSlp,
    [HOLD_EFFECT_CURE_PSN] = sText_HoldEffectCurePsn,
    [HOLD_EFFECT_CURE_BRN] = sText_HoldEffectCureBrn,
    [HOLD_EFFECT_CURE_FRZ] = sText_HoldEffectCureFrz,
    [HOLD_EFFECT_RESTORE_PP] = sText_HoldEffectRestorePp,
    [HOLD_EFFECT_CURE_CONFUSION] = sText_HoldEffectCureConfusion,
    [HOLD_EFFECT_CURE_STATUS] = sText_HoldEffectCureStatus,
    [HOLD_EFFECT_CONFUSE_SPICY] = sText_HoldEffectConfuseSpicy,
    [HOLD_EFFECT_CONFUSE_DRY] = sText_HoldEffectConfuseDry,
    [HOLD_EFFECT_CONFUSE_SWEET] = sText_HoldEffectConfuseSweet,
    [HOLD_EFFECT_CONFUSE_BITTER] = sText_HoldEffectConfuseBitter,
    [HOLD_EFFECT_CONFUSE_SOUR] = sText_HoldEffectConfuseSour,
    [HOLD_EFFECT_ATTACK_UP] = sText_HoldEffectAttackUp,
    [HOLD_EFFECT_DEFENSE_UP] = sText_HoldEffectDefenseUp,
    [HOLD_EFFECT_SPEED_UP] = sText_HoldEffectSpeedUp,
    [HOLD_EFFECT_SP_ATTACK_UP] = sText_HoldEffectSpAttackUp,
    [HOLD_EFFECT_SP_DEFENSE_UP] = sText_HoldEffectSpDefenseUp,
    [HOLD_EFFECT_CRITICAL_UP] = sText_HoldEffectCriticalUp,
    [HOLD_EFFECT_RANDOM_STAT_UP] = sText_HoldEffectRandomStatUp,
    [HOLD_EFFECT_EVASION_UP] = sText_HoldEffectEvasionUp,
    [HOLD_EFFECT_RESTORE_STATS] = sText_HoldEffectRestoreStats,
    [HOLD_EFFECT_MACHO_BRACE] = sText_HoldEffectMachoBrace,
    [HOLD_EFFECT_EXP_SHARE] = sText_HoldEffectExpShare,
    [HOLD_EFFECT_QUICK_CLAW] = sText_HoldEffectQuickClaw,
    [HOLD_EFFECT_FRIENDSHIP_UP] = sText_HoldEffectFriendshipUp,
    [HOLD_EFFECT_MENTAL_HERB] = sText_HoldEffectMentalHerb,
    [HOLD_EFFECT_CHOICE_BAND] = sText_HoldEffectChoiceBand,
    [HOLD_EFFECT_FLINCH] = sText_HoldEffectFlinch,
    [HOLD_EFFECT_BUG_POWER] = sText_HoldEffectBugPower,
    [HOLD_EFFECT_DOUBLE_PRIZE] = sText_HoldEffectDoublePrize,
    [HOLD_EFFECT_REPEL] = sText_HoldEffectRepel,
    [HOLD_EFFECT_SOUL_DEW] = sText_HoldEffectSoulDew,
    [HOLD_EFFECT_DEEP_SEA_TOOTH] = sText_HoldEffectDeepSeaTooth,
    [HOLD_EFFECT_DEEP_SEA_SCALE] = sText_HoldEffectDeepSeaScale,
    [HOLD_EFFECT_CAN_ALWAYS_RUN] = sText_HoldEffectCanAlwaysRun,
    [HOLD_EFFECT_PREVENT_EVOLVE] = sText_HoldEffectPreventEvolve,
    [HOLD_EFFECT_FOCUS_BAND] = sText_HoldEffectFocusBand,
    [HOLD_EFFECT_LUCKY_EGG] = sText_HoldEffectLuckyEgg,
    [HOLD_EFFECT_SCOPE_LENS] = sText_HoldEffectScopeLens,
    [HOLD_EFFECT_STEEL_POWER] = sText_HoldEffectSteelPower,
    [HOLD_EFFECT_LEFTOVERS] = sText_HoldEffectLeftovers,
    [HOLD_EFFECT_DRAGON_SCALE] = sText_HoldEffectDragonScale,
    [HOLD_EFFECT_LIGHT_BALL] = sText_HoldEffectLightBall,
    [HOLD_EFFECT_GROUND_POWER] = sText_HoldEffectGroundPower,
    [HOLD_EFFECT_ROCK_POWER] = sText_HoldEffectRockPower,
    [HOLD_EFFECT_GRASS_POWER] = sText_HoldEffectGrassPower,
    [HOLD_EFFECT_DARK_POWER] = sText_HoldEffectDarkPower,
    [HOLD_EFFECT_FIGHTING_POWER] = sText_HoldEffectFightingPower,
    [HOLD_EFFECT_ELECTRIC_POWER] = sText_HoldEffectElectricPower,
    [HOLD_EFFECT_WATER_POWER] = sText_HoldEffectWaterPower,
    [HOLD_EFFECT_FLYING_POWER] = sText_HoldEffectFlyingPower,
    [HOLD_EFFECT_POISON_POWER] = sText_HoldEffectPoisonPower,
    [HOLD_EFFECT_ICE_POWER] = sText_HoldEffectIcePower,
    [HOLD_EFFECT_GHOST_POWER] = sText_HoldEffectGhostPower,
    [HOLD_EFFECT_PSYCHIC_POWER] = sText_HoldEffectPsychicPower,
    [HOLD_EFFECT_FIRE_POWER] = sText_HoldEffectFirePower,
    [HOLD_EFFECT_DRAGON_POWER] = sText_HoldEffectDragonPower,
    [HOLD_EFFECT_NORMAL_POWER] = sText_HoldEffectNormalPower,
    [HOLD_EFFECT_UPGRADE] = sText_HoldEffectUpgrade,
    [HOLD_EFFECT_SHELL_BELL] = sText_HoldEffectShellBell,
    [HOLD_EFFECT_LUCKY_PUNCH] = sText_HoldEffectLuckyPunch,
    [HOLD_EFFECT_METAL_POWDER] = sText_HoldEffectMetalPowder,
    [HOLD_EFFECT_THICK_CLUB] = sText_HoldEffectThickClub,
    [HOLD_EFFECT_LEEK] = sText_HoldEffectLeek,
    [HOLD_EFFECT_CHOICE_SCARF] = sText_HoldEffectChoiceScarf,
    [HOLD_EFFECT_CHOICE_SPECS] = sText_HoldEffectChoiceSpecs,
    [HOLD_EFFECT_DAMP_ROCK] = sText_HoldEffectDampRock,
    [HOLD_EFFECT_GRIP_CLAW] = sText_HoldEffectGripClaw,
    [HOLD_EFFECT_HEAT_ROCK] = sText_HoldEffectHeatRock,
    [HOLD_EFFECT_ICY_ROCK] = sText_HoldEffectIcyRock,
    [HOLD_EFFECT_LIGHT_CLAY] = sText_HoldEffectLightClay,
    [HOLD_EFFECT_SMOOTH_ROCK] = sText_HoldEffectSmoothRock,
    [HOLD_EFFECT_POWER_HERB] = sText_HoldEffectPowerHerb,
    [HOLD_EFFECT_BIG_ROOT] = sText_HoldEffectBigRoot,
    [HOLD_EFFECT_EXPERT_BELT] = sText_HoldEffectExpertBelt,
    [HOLD_EFFECT_LIFE_ORB] = sText_HoldEffectLifeOrb,
    [HOLD_EFFECT_METRONOME] = sText_HoldEffectMetronome,
    [HOLD_EFFECT_MUSCLE_BAND] = sText_HoldEffectMuscleBand,
    [HOLD_EFFECT_WIDE_LENS] = sText_HoldEffectWideLens,
    [HOLD_EFFECT_WISE_GLASSES] = sText_HoldEffectWiseGlasses,
    [HOLD_EFFECT_ZOOM_LENS] = sText_HoldEffectZoomLens,
    [HOLD_EFFECT_LAGGING_TAIL] = sText_HoldEffectLaggingTail,
    [HOLD_EFFECT_FOCUS_SASH] = sText_HoldEffectFocusSash,
    [HOLD_EFFECT_FLAME_ORB] = sText_HoldEffectFlameOrb,
    [HOLD_EFFECT_TOXIC_ORB] = sText_HoldEffectToxicOrb,
    [HOLD_EFFECT_STICKY_BARB] = sText_HoldEffectStickyBarb,
    [HOLD_EFFECT_IRON_BALL] = sText_HoldEffectIronBall,
    [HOLD_EFFECT_BLACK_SLUDGE] = sText_HoldEffectBlackSludge,
    [HOLD_EFFECT_DESTINY_KNOT] = sText_HoldEffectDestinyKnot,
    [HOLD_EFFECT_SHED_SHELL] = sText_HoldEffectShedShell,
    [HOLD_EFFECT_QUICK_POWDER] = sText_HoldEffectQuickPowder,
    [HOLD_EFFECT_ADAMANT_ORB] = sText_HoldEffectAdamantOrb,
    [HOLD_EFFECT_LUSTROUS_ORB] = sText_HoldEffectLustrousOrb,
    [HOLD_EFFECT_GRISEOUS_ORB] = sText_HoldEffectGriseousOrb,
    [HOLD_EFFECT_ENIGMA_BERRY] = sText_HoldEffectEnigmaBerry,
    [HOLD_EFFECT_RESIST_BERRY] = sText_HoldEffectResistBerry,
    [HOLD_EFFECT_POWER_ITEM] = sText_HoldEffectPowerItem,
    [HOLD_EFFECT_RESTORE_PCT_HP] = sText_HoldEffectRestorePctHp,
    [HOLD_EFFECT_MICLE_BERRY] = sText_HoldEffectMicleBerry,
    [HOLD_EFFECT_CUSTAP_BERRY] = sText_HoldEffectCustapBerry,
    [HOLD_EFFECT_JABOCA_BERRY] = sText_HoldEffectJabocaBerry,
    [HOLD_EFFECT_ROWAP_BERRY] = sText_HoldEffectRowapBerry,
    [HOLD_EFFECT_KEE_BERRY] = sText_HoldEffectKeeBerry,
    [HOLD_EFFECT_MARANGA_BERRY] = sText_HoldEffectMarangaBerry,
    [HOLD_EFFECT_PLATE] = sText_HoldEffectPlate,
    [HOLD_EFFECT_FLOAT_STONE] = sText_HoldEffectFloatStone,
    [HOLD_EFFECT_EVIOLITE] = sText_HoldEffectEviolite,
    [HOLD_EFFECT_ASSAULT_VEST] = sText_HoldEffectAssaultVest,
    [HOLD_EFFECT_DRIVE] = sText_HoldEffectDrive,
    [HOLD_EFFECT_GEMS] = sText_HoldEffectGems,
    [HOLD_EFFECT_ROCKY_HELMET] = sText_HoldEffectRockyHelmet,
    [HOLD_EFFECT_AIR_BALLOON] = sText_HoldEffectAirBalloon,
    [HOLD_EFFECT_RED_CARD] = sText_HoldEffectRedCard,
    [HOLD_EFFECT_RING_TARGET] = sText_HoldEffectRingTarget,
    [HOLD_EFFECT_BINDING_BAND] = sText_HoldEffectBindingBand,
    [HOLD_EFFECT_EJECT_BUTTON] = sText_HoldEffectEjectButton,
    [HOLD_EFFECT_ABSORB_BULB] = sText_HoldEffectAbsorbBulb,
    [HOLD_EFFECT_CELL_BATTERY] = sText_HoldEffectCellBattery,
    [HOLD_EFFECT_FAIRY_POWER] = sText_HoldEffectFairyPower,
    [HOLD_EFFECT_MEGA_STONE] = sText_HoldEffectMegaStone,
    [HOLD_EFFECT_SAFETY_GOGGLES] = sText_HoldEffectSafetyGoggles,
    [HOLD_EFFECT_LUMINOUS_MOSS] = sText_HoldEffectLuminousMoss,
    [HOLD_EFFECT_SNOWBALL] = sText_HoldEffectSnowball,
    [HOLD_EFFECT_WEAKNESS_POLICY] = sText_HoldEffectWeaknessPolicy,
    [HOLD_EFFECT_PRIMAL_ORB] = sText_HoldEffectPrimalOrb,
    [HOLD_EFFECT_PROTECTIVE_PADS] = sText_HoldEffectProtectivePads,
    [HOLD_EFFECT_TERRAIN_EXTENDER] = sText_HoldEffectTerrainExtender,
    [HOLD_EFFECT_SEEDS] = sText_HoldEffectSeeds,
    [HOLD_EFFECT_ADRENALINE_ORB] = sText_HoldEffectAdrenalineOrb,
    [HOLD_EFFECT_MEMORY] = sText_HoldEffectMemory,
    [HOLD_EFFECT_Z_CRYSTAL] = sText_HoldEffectZCrystal,
    [HOLD_EFFECT_UTILITY_UMBRELLA] = sText_HoldEffectUtilityUmbrella,
    [HOLD_EFFECT_EJECT_PACK] = sText_HoldEffectEjectPack,
    [HOLD_EFFECT_ROOM_SERVICE] = sText_HoldEffectRoomService,
    [HOLD_EFFECT_BLUNDER_POLICY] = sText_HoldEffectBlunderPolicy,
    [HOLD_EFFECT_HEAVY_DUTY_BOOTS] = sText_HoldEffectHeavyDutyBoots,
    [HOLD_EFFECT_THROAT_SPRAY] = sText_HoldEffectThroatSpray,
    [HOLD_EFFECT_ABILITY_SHIELD] = sText_HoldEffectAbilityShield,
    [HOLD_EFFECT_CLEAR_AMULET] = sText_HoldEffectClearAmulet,
    [HOLD_EFFECT_MIRROR_HERB] = sText_HoldEffectMirrorHerb,
    [HOLD_EFFECT_PUNCHING_GLOVE] = sText_HoldEffectPunchingGlove,
    [HOLD_EFFECT_COVERT_CLOAK] = sText_HoldEffectCovertCloak,
    [HOLD_EFFECT_LOADED_DICE] = sText_HoldEffectLoadedDice,
    [HOLD_EFFECT_BOOSTER_ENERGY] = sText_HoldEffectBoosterEnergy,
    [HOLD_EFFECT_OGERPON_MASK] = sText_HoldEffectOgerponMask,
    [HOLD_EFFECT_BERSERK_GENE] = sText_HoldEffectBerserkGene,
};
static const u8 *GetHoldEffectName(u16 holdEffect)
{
    if (holdEffect > ARRAY_COUNT(sHoldEffectNames))
        return sHoldEffectNames[0];
    return sHoldEffectNames[holdEffect];
}
