#include "global.h"
#include "battle_info.h"
#include "battle.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_gimmick.h"
#include "battle_setup.h"
#include "battle_util.h"
#include "event_data.h"
#include "bg.h"
#include "data.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "line_break.h"
#include "palette.h"
#include "party_menu.h"
#include "item.h"
#include "frontier_util.h"
#include "link.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "pokemon_summary_screen.h"
#include "scanline_effect.h"
#include "decompress.h"
#include "sound.h"
#include "sprite.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "window.h"
#include "config/battle_info.h"
#include "constants/battle_info.h"
#include "constants/battle.h"
#include "constants/party_menu.h"
#include "constants/abilities.h"
#include "constants/characters.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/pokemon.h"

_Static_assert(B_BATTLE_INFO_BUTTON == R_BUTTON || B_BATTLE_INFO_BUTTON == L_BUTTON, "must be L_BUTTON or R_BUTTON");

struct PrintText
{
    u8 windowId;
    u8 font;
    u8 left;
    u8 top;
    u8 letterSpacing;
    u8 lineSpacing;
    const u8 *color;
    s8 speed;
    const u8 *string;
};

struct BattleInfo
{
    u8 label;
    u8 durationRemaining;
    u8 baseTotalDuration;
    u8 stackCount:4;
    u8 setterSide:2;
    u8 durationKnown:1;
    u8 padding:1;
};

struct BattleInfoCard
{
    enum BattlerId battler;
    s16 x;
    s16 y;
    u8 hpBarSpriteId;
    u8 monIconSpriteId;
    u8 gimmickSpriteId;
    u8 statusSpriteId;
    u8 updateSpriteId;
    u8 hpBarLeftEndcapSpriteId;
    u8 hpBarRightEndcapSpriteId;
};

struct BattleInfoMenuData
{
    u8 menuState;
    u8 page;
    u8 selectedCard;
    u8 cursorSpriteId;
    u8 iconSpriteId;
    u8 hpBarSpriteId;
    u8 hpBarLeftEndcapSpriteId;
    u8 hpBarRightEndcapSpriteId;
    u8 statusSpriteId;
    u8 teraTypeSpriteId;
    u8 gimmickSpriteId;
    u8 typeIconSpriteIds[2];
    u8 statPipSpriteIds[B_INFO_DETAIL_STAT_ROW_COUNT][B_INFO_DETAIL_STAT_PIPS_PER_ROW];
    struct BattleInfoCard cards[MAX_BATTLERS_COUNT];
    struct BattleInfo activeEffects[B_INFO_DETAIL_MAX_ACTIVE_EFFECTS];
    u8 activeEffectsCount;
    u8 effectsCursor;
    u8 effectsScrollbarSpriteId;
    u16 effectsScroll;
    u32 windowIds[WIN_DETAIL_COUNT];
    u16 bg0Tilemap[BG_SCREEN_SIZE];
    u16 bg1Tilemap[BG_SCREEN_SIZE];
};

static EWRAM_DATA struct BattleInfoMenuData *sData = NULL;

static void CB2_BattleInfoMenu(void);
static void Task_BattleInfoLoadPage(u8 taskId);
static void BattleInfoVBlankCB(void);
static void BattleInfoMainCB(void);
static void BattleInfoResetSpriteIds(void);
static void BattleInfoInitBgs(void);
static void BattleInfoInit(void);
static void Overview_Enter(void);
static void Overview_Exit(void);
static void Overview_ComputeRowLayout(u8 *outXs);
static void Overview_InitCardValues(void);
static void Overview_DrawCards(void);
static void Overview_DrawCard(struct BattleInfoCard *card);
static void Overview_PrintMonAndGender(struct BattleInfoCard *card, struct Pokemon *mon, enum Species species, u32 contentYOffset);
static void CreateGimmickIndicator(struct BattleInfoCard *card, u32 iconCenterY);
static void CreateMonAndStatusIcon(struct BattleInfoCard *card, enum Species species, u32 personality, u32 contentYOffset);
static void CreateHpBar(struct BattleInfoCard *card, u32 contentYOffset);
static void Overview_SetBgTile(s32 x, u32 y, u32 tileNum, u32 attrs);
static void BackdropLoadBaseTilemap(void);
static void LoadBackdropAssets(void);
static void Overview_ComputeTrainerNameBoxLayout(u32 labelWidth, u32 centerRow, u32 *outTextLenTiles, u32 *outHeaderX, u32 *outHeaderWidth);
static void Overview_DrawStatusCard(u32 x, u32 y, bool32 isActive, bool32 isBottomRow);
static void Overview_DrawHeaderBoxRow(u32 cornerTile, u32 fillTile, u32 baseAttrs, s32 x, u32 y, u32 width);
static void Overview_DrawBackground(void);
static void Overview_DrawTrainerNameBox(enum BattleSide side);
static void Overview_DrawTrainerNameBoxHelper(u32 labelWidth, u32 top, u32 centerRow);
static void Overview_FillBgRect(u32 x, u32 y, u32 width, u32 height, u32 tileNum, u32 attrs);
static void Overview_DrawCardBackground(const struct BattleInfoCard *card, bool32 isActive);
static void Overview_UpdateCardSelectionHighlight(u32 oldSelectedIndex);
static void Overview_UpdateOldSelectedCard(u32 oldSelectedIndex);
static void Overview_UpdateNewSelectedCard(void);
static void Overview_DrawNameBoxes(void);
static void Overview_DrawLabels(void);
static void Overview_DrawTrainerLabels(enum BattleSide side);
static void Overview_DrawMultiTrainerLabels(enum BattleSide side);
static void Overview_DrawTrainerLabelText(u32 windowId, const u8 *label, s32 labelX);
static void Overview_FlushLabelWindow(u32 windowId);
static void Overview_DrawMultiTrainerNameBoxes(enum BattleSide side);
static void Overview_ComputeHeaderBoxAtCard(const struct BattleInfoCard *card, const u8 *label, u32 *outHeaderX, u32 *outWidth);
static void Overview_DrawHeaderBoxAtCard(const struct BattleInfoCard *card, u32 top, const u8 *label);
static void Overview_DrawHeaderBoxWidth(s32 x, u32 y, u32 width);
static const u8 *GetTrainerNameForBattler(enum BattlerId battler);
static void Overview_CreateWindows(void);
static void Overview_ClearWindows(void);
static void Overview_InitCursor(void);
static void Overview_UpdateCursorPos(void);
static void Overview_GetCursorPos(const struct BattleInfoCard *card, s16 *outX, s16 *outY);
static void Task_BattleMenuStatus_HandleInput(u8 taskId);
static void Overview_HandleInput(u8 taskId);

static void Overview_TryMoveCursor(u32 direction);
static void Detail_Enter(void);
static void Detail_Exit(void);
static void Detail_HandleInput(u8 taskId);
static void Detail_CreateWindows(void);
static void Detail_DestroyWindows(void);
static void Detail_DrawStatLabels(void);
static void Detail_DrawItemAbilityWindow(void);
static const u8 *GetGimmickIndicatorData(enum BattlerId battler, u32 *palTag);
static void Detail_DestroyHpBar(void);
static void Detail_RefreshHpBar(void);
static void Detail_DestroyStatusIcon(void);
static void Detail_RefreshStatusIcon(void);
static void Detail_DrawLRButtonGlyphs(void);
static s32 Detail_DrawLRButtonGlyphsItemAbility(struct PrintText text, s32 rGlyphWidth);
static void Detail_DrawLRButtonGlyphsStats(struct PrintText text, s32 alignedAbsY);
static void Detail_DestroyGimmickIndicator(void);
static void Detail_RefreshGimmickIndicator(void);
static void Detail_DestroyTeraTypeIndicator(void);
static void Detail_RefreshTeraTypeIndicator(void);
static void Detail_RefreshItemAbilityWindow(void);
static void PrintHeldItemText(struct PrintText text, enum BattlerId battler);
static void PrintAbilityText(struct PrintText text, enum BattlerId battler);
static void Detail_RefreshHeader(void);
static void Detail_PrintMonName(struct PrintText text, struct Pokemon *mon, s32 levelX);
static void Detail_DisplayMonGender(struct PrintText text, struct Pokemon *mon, s32 genderX);
static void Detail_DisplayMonLevel(struct PrintText text, struct Pokemon *mon, s32 levelX);
static void Detail_DisplayGimmickIndicator(struct PrintText text);
static void Detail_RefreshIcon(void);
static void Detail_RefreshTypeIcons(void);
static void Detail_DestroyTypeIcons(void);
static void Detail_CreateStatPips(void);
static void Detail_DestroyStatPips(void);
static void Detail_RefreshStatPips(void);
static s32 Detail_GetStatRowTextY(u32 row);
static void Detail_SetStatPipSpriteGraphic(u32 spriteId, u32 tileTag);
static void Detail_CycleBattler(s32 direction);
static void Detail_PreviousBattler(void);
static void Detail_NextBattler(void);
static void Detail_InitEffectsList(void);
static void Detail_BuildActiveEffectsForBattler(void);
static void TryAddActiveWeather(enum BattleInfoLabels label, enum BattleSide side);
static void TryAddActiveTerrain(enum BattleInfoLabels label, enum BattleSide side);
static void TryAddActiveScreen(enum BattleInfoLabels label, u32 sideStatus, u32 remaining, u32 extendedTotal, enum BattleSide side);
static bool32 ShouldShowIncreasedDuration(enum BattleSide side);

struct DisplayTimer
{
    s8 baseTotal;
    s8 extendedTotal;
    s8 remaining;
};
static void SetRemainingDuration(struct DisplayTimer *timer);
static void TryAddActiveFieldStatus(enum BattleInfoLabels label, u32 fieldStatus, u32 timer, u32 totalTimer, enum BattleSide side);
static void TryAddActiveSideStatus(enum BattleInfoLabels label, u32 sideStatus, u32 timer, u32 totalTimer, enum BattleSide side);
static void TryAddActiveStatus(enum BattleInfoLabels label, u32 timerOrFlag, enum BattleSide side);
static void TryAddActiveStatusTimer(enum BattleInfoLabels label, u32 remaining, u32 baseTotal, enum BattleSide side);
static void TryAddActiveStatusInternal(enum BattleInfoLabels label, u32 timerOrFlag, u32 baseTotal, enum BattleSide side, bool32 isTimer);
static enum BattleInfoLabels GetStatusEffectFromWeather(void);
static enum BattleInfoLabels GetStatusEffectFromTerrain(void);
static enum BattleInfoLabels GetInfoFromSemiInvulnerableState(u32 semiInvulnerable);
static void TryAddActiveDamageNonTypes(enum BattleSide side);
static void TryAddActiveThirdType(enum BattlerId battler, enum BattleSide side);

struct Durations
{
    u16 total;
    u16 remaining;
};
static bool32 Detail_SetDisplayedDuration(const struct BattleInfo *entry, enum BattleSide viewerSide, struct Durations *duration);

static void Detail_BuildTurnFractionText(u8 *dst, u32 remaining, u32 total);
static bool32 Detail_TryMoveEffectCursor(s32 direction);
static void Detail_RefreshEffectsWindow(void);
static void Detail_RefreshDescriptionWindow(void);
static void Detail_RefreshEffectsSection(void);
static void Detail_RefreshEffectsScrollbar(void);
static void Detail_DestroyIconSprite(void);
static void Detail_UpdateScrollbarLane(bool32 hasScrollbar);
static void Detail_SetDescriptionPlaceholder(enum BattleInfoLabels  label);
static void Detail_ClampTextLines(u8 *text, u32 maxLines);
static void Detail_ResetWithTransparentTextColor(u32 windowId);
static const u8 *GetSideTrainerName(enum BattleSide side);
static u32 GetOpponentTrainerCount(void);
static void BattleInfoDestroy(void);
static void DestroyOverviewCardSprites(struct BattleInfoCard *card);
static u32 CreateHpBarSprite(u32 tileTag, u32 x, u32 y);
static void DestroyHpBarEndcaps(u8 *leftEndcapSpriteId, u8 *rightEndcapSpriteId);
static void CreateHpBarEndcaps(u8 *leftEndcapSpriteId, u8 *rightEndcapSpriteId);
static void CreateEndCapSprite(const struct SpriteTemplate *template, u8 *endcapSpriteId);
static void UpdateHpBarEndcaps(u32 leftEndCapSpriteId, u32 rightEndCapSpriteId, u32 barCenterX, u32 barY, u32 segmentCount);
static void UpdateEndcapsSprites(u32 endcapSpriteId, u32 x, u32 y);
static void UpdateHpBarTilesWithWidth(u32 spriteId, u32 hp, u32 maxHp, u32 totalPixels, u32 segmentCount);
static void UpdateHpBarTiles(u32 spriteId, u32 hp, u32 maxHp);
static void DrawHpBarSprite(struct BattleInfoCard *card);
static u32 GetBarGfxId(u32 hp, u32 maxHp);
static u32 GetAilmentFromBattler(enum BattlerId battler);
static bool32 CanViewCard(enum BattlerId battler);
static u32 GetCardCount(void);
static enum BattlerId GetSelectedBattler(void);
static enum BattlerId GetBattlerFromSlot(u32 slot);
static void PrintTextOnWindow(struct PrintText *text);
static u32 MakeEven(u32 value);
static u32 PixelsToTiles(u32 width);

static const u8 sTextColor_BattleInfo_Default[] =
{
    B_INFO_TEXT_COLOR_TRANSPARENT,
    B_INFO_TEXT_COLOR_WHITE,
    B_INFO_TEXT_COLOR_DARK_GRAY
};

static const u8 sTextColor_BattleInfo_OverviewDefault[] =
{
    B_INFO_TEXT_COLOR_TRANSPARENT,
    B_INFO_TEXT_COLOR_BLACK,
    B_INFO_TEXT_COLOR_WHITE
};

static const u8 sTextColor_BattleInfo_Male[] =
{
    B_INFO_TEXT_COLOR_TRANSPARENT,
    B_INFO_TEXT_COLOR_BLUE,
    B_INFO_TEXT_COLOR_LIGHT_BLUE
};

static const u8 sTextColor_BattleInfo_Female[] =
{
    B_INFO_TEXT_COLOR_TRANSPARENT,
    B_INFO_TEXT_COLOR_PINK,
    B_INFO_TEXT_COLOR_DARK_PINK
};

static const u8 sText_BattleInfo_DetailLButtonGlyph[] = _("{L_BUTTON}");
static const u8 sText_BattleInfo_DetailRButtonGlyph[] = _("{R_BUTTON}");

static const u8 *const sBattleInfoDetailStatLabels[B_INFO_DETAIL_STAT_ROW_COUNT] =
{
    COMPOUND_STRING("攻击"),
    COMPOUND_STRING("防御"),
    COMPOUND_STRING("特攻"),
    COMPOUND_STRING("特防"),
    COMPOUND_STRING("速度"),
    COMPOUND_STRING("命中率"),
    COMPOUND_STRING("回避率"),
};

static const enum Stat sBattleInfoDetailStatIds[B_INFO_DETAIL_STAT_ROW_COUNT] =
{
    STAT_ATK,
    STAT_DEF,
    STAT_SPATK,
    STAT_SPDEF,
    STAT_SPEED,
    STAT_ACC,
    STAT_EVASION,
};

struct BattleInfoEffectData
{
    const u8 *name;
    const u8 *description;
};

static const struct BattleInfoEffectData sBattleInfoEffects[INFO_COUNT] =
{
    [INFO_HARSH_SUNLIGHT] =
    {
        COMPOUND_STRING("大晴天"),
        COMPOUND_STRING("火属性的招式威力会提高。水属性的招式威力会降低。")
    },
    [INFO_RAIN] =
    {
        COMPOUND_STRING("降雨"),
        COMPOUND_STRING("水属性的招式威力会提高。火属性的招式威力会降低。")
    },
    [INFO_SANDSTORM] =
    {
        COMPOUND_STRING("沙暴"),
        COMPOUND_STRING("岩石、地面和钢属性以外的宝可梦，每回合会受到伤害。岩石属性的特防会变强。")
    },
    [INFO_SNOW] =
    {
        COMPOUND_STRING("下雪"),
        COMPOUND_STRING("冰属性的防御变强。")
    },
    [INFO_ELECTRIC_TERRAIN] =
    {
        COMPOUND_STRING("电气场地"),
        COMPOUND_STRING("地面上的宝可梦不会变为睡眠状态。电属性的招式威力会提高。")
    },
    [INFO_GRASSY_TERRAIN] =
    {
        COMPOUND_STRING("青草场地"),
        COMPOUND_STRING("地面上的宝可梦会缓缓回复HP。草属性的招式威力会提高。")
    },
    [INFO_MISTY_TERRAIN] =
    {
        COMPOUND_STRING("薄雾场地"),
        COMPOUND_STRING("地面上的宝可梦不会陷入异常状态。龙属性招式的伤害也会减半。")
    },
    [INFO_TRICK_ROOM] =
    {
        COMPOUND_STRING("戏法空间"),
        COMPOUND_STRING("速度慢的宝可梦可以先行动。")
    },
    [INFO_MAGIC_ROOM] =
    {
        COMPOUND_STRING("魔法空间"),
        COMPOUND_STRING("所有宝可梦携带道具的效果都会消失。")
    },
    [INFO_WONDER_ROOM] =
    {
        COMPOUND_STRING("奇妙空间"),
        COMPOUND_STRING("互换所有宝可梦的防御和特防。")
    },
    [INFO_CRITICAL_HIT_BOOST] =
    {
        COMPOUND_STRING("易中要害"),
        COMPOUND_STRING("击中对手要害的几率变高。")
    },
    [INFO_CONFUSION] =
    {
        COMPOUND_STRING("混乱"),
        COMPOUND_STRING("在1～4回合内，有时会攻击自己。")
    },
    [INFO_INFATUATION] =
    {
        COMPOUND_STRING("着迷"),
        COMPOUND_STRING("处于着迷状态的宝可梦会变得很难使出招式。")
    },
    [INFO_NIGHTMARE] =
    {
        COMPOUND_STRING("恶梦"),
        COMPOUND_STRING("在睡着的时候，每回合HP会减少。")
    },
    [INFO_DROWSY] =
    {
        COMPOUND_STRING("瞌睡"),
        COMPOUND_STRING("在受到招式攻击的下一回合，变为睡眠状态。")
    },
    [INFO_ENCORE] =
    {
        COMPOUND_STRING("再来一次"),
        COMPOUND_STRING("只能使出{STR_VAR_1}.")
    },
    [INFO_NO_ABILITY] =
    {
        COMPOUND_STRING("无特性"),
        COMPOUND_STRING("特性会消失，变得没有效果。")
    },
    [INFO_TORMENT] =
    {
        COMPOUND_STRING("无理取闹"),
        COMPOUND_STRING("不能连续使出同样的招式。")
    },
    [INFO_TAILWIND] =
    {
        COMPOUND_STRING("顺风"),
        COMPOUND_STRING("出战的我方宝可梦速度会变为2倍。")
    },
    [INFO_LUCKY_CHANT] =
    {
        COMPOUND_STRING("幸运咒语"),
        COMPOUND_STRING("变得不会被对手的招式击中要害。")
    },
    [INFO_GRUDGE] =
    {
        COMPOUND_STRING("怨念"),
        COMPOUND_STRING("因对手的招式而濒死时，该招式的PP会变为0。")
    },
    [INFO_HEALING_PREVENTED] =
    {
        COMPOUND_STRING("回复封锁"),
        COMPOUND_STRING("无法通过招式、特性或携带的道具回复HP。")
    },
    [INFO_IDENTIFIED] =
    {
        COMPOUND_STRING("被识破"),
        COMPOUND_STRING("会被那些原本不会有特定效果的招式击中。无视闪避率提升的效果，都会受到攻击。")
    },
    [INFO_MOVE_DISABLED] =
    {
        COMPOUND_STRING("定身法"),
        COMPOUND_STRING("{STR_VAR_1}会变得无法使用。")
    },
    [INFO_CANT_ESCAPE] =
    {
        COMPOUND_STRING("无法逃走"),
        COMPOUND_STRING("无法逃走或替换。")
    },
    [INFO_LOCK_ON] =
    {
        COMPOUND_STRING("锁定"),
        COMPOUND_STRING("招式必定会命中锁定了的对手。")
    },
    [INFO_EMBARGO] =
    {
        COMPOUND_STRING("查封"),
        COMPOUND_STRING("持有物和道具会变得无法使用。")
    },
    [INFO_CHARGE] =
    {
        COMPOUND_STRING("充电"),
        COMPOUND_STRING("下次使出的电属性的招式威力会变为2倍。")
    },
    [INFO_GRAVITY] =
    {
        COMPOUND_STRING("重力"),
        COMPOUND_STRING("招式会变得容易击中。飞行属性和飘浮特性的宝可梦会被地面招式击中。飞向空中的招式将无法使用。")
    },
    [INFO_MIST] =
    {
        COMPOUND_STRING("白雾"),
        COMPOUND_STRING("不会被降低能力。")
    },
    [INFO_SAFEGUARD] =
    {
        COMPOUND_STRING("神秘守护"),
        COMPOUND_STRING("不会陷入异常状态。")
    },
    [INFO_STEALTH_ROCK] =
    {
        COMPOUND_STRING("隐形岩"),
        COMPOUND_STRING("替换出场的宝可梦会受到岩石属性的伤害。")
    },
    [INFO_STOCKPILING] =
    {
        COMPOUND_STRING("蓄力"),
        COMPOUND_STRING("在蓄力的时候，防御和特防会提高。")
    },
    [INFO_TAUNT] =
    {
        COMPOUND_STRING("挑衅"),
        COMPOUND_STRING("变得只能使出给予伤害的招式。")
    },
    [INFO_TELEKINESIS] =
    {
        COMPOUND_STRING("意念移物"),
        COMPOUND_STRING("在3回合内，一击必杀以外的招式也必定会击中。地面属性的招式会变得无法击中。")
    },
    [INFO_MAGNET_RISE] =
    {
        COMPOUND_STRING("电磁飘浮"),
        COMPOUND_STRING("地面属性的招式会变得无法击中。")
    },
    [INFO_TOXIC_SPIKES] =
    {
        COMPOUND_STRING("毒菱"),
        COMPOUND_STRING("让替换出场的宝可梦陷入中毒状态。飞行属性和飘浮特性的宝可梦不会被击中。")
    },
    [INFO_MUD_SPORT] =
    {
        COMPOUND_STRING("玩泥巴"),
        COMPOUND_STRING("电属性的招式的威力会减半。")
    },
    [INFO_WISH] =
    {
        COMPOUND_STRING("祈愿"),
        COMPOUND_STRING("使用祈愿后的下一回合，在该位置的宝可梦的HP会回复。")
    },
    [INFO_STICKY_WEB] =
    {
        COMPOUND_STRING("黏黏网"),
        COMPOUND_STRING("降低替换出场的宝可梦的速度。")
    },
    [INFO_INGRAIN] =
    {
        COMPOUND_STRING("扎根"),
        COMPOUND_STRING("在每回合结束时回复HP。扎根的宝可梦无法替换。")
    },
    [INFO_CURSE] =
    {
        COMPOUND_STRING("咒术"),
        COMPOUND_STRING("在每回合结束时减少HP。")
    },
    [INFO_TRICK_OR_TREAT] =
    {
        COMPOUND_STRING("万圣夜"),
        COMPOUND_STRING("宝可梦会被追加幽灵属性。")
    },
    [INFO_LIGHT_SCREEN] =
    {
        COMPOUND_STRING("光墙"),
        COMPOUND_STRING("受到的特殊攻击威力会减半。")
    },
    [INFO_REFLECT] =
    {
        COMPOUND_STRING("反射壁"),
        COMPOUND_STRING("受到的物理攻击威力会减半。")
    },
    [INFO_IMPRISON] =
    {
        COMPOUND_STRING("封印"),
        COMPOUND_STRING("宝可梦使出封印后，其所学会的招式，对手的宝可梦将无法使出。")
    },
    [INFO_PERISHING] =
    {
        COMPOUND_STRING("终焉之歌"),
        COMPOUND_STRING("陷入了终焉状态的全部宝可梦3回合后会陷入昏厥。")
    },
    [INFO_SPIKES] =
    {
        COMPOUND_STRING("撒菱"),
        COMPOUND_STRING("给予替换出场的宝可梦伤害。飞行属性和飘浮特性的宝可梦不会被击中。")
    },
    [INFO_WATER_SPORT] =
    {
        COMPOUND_STRING("玩水"),
        COMPOUND_STRING("火属性招式的威力会减半。")
    },
    [INFO_DESTINY_BOND] =
    {
        COMPOUND_STRING("同命"),
        COMPOUND_STRING("让自己陷入濒死的对手，也会一同陷入濒死。")
    },
    [INFO_FORESTS_CURSE] =
    {
        COMPOUND_STRING("森林咒术"),
        COMPOUND_STRING("宝可梦会被追加草属性。")
    },
    [INFO_LEECH_SEED] =
    {
        COMPOUND_STRING("寄生种子"),
        COMPOUND_STRING("每回合结束时，会被寄生种子夺走HP，同时回复对手的HP。")
    },
    [INFO_BOUND] =
    {
        COMPOUND_STRING("束缚"),
        COMPOUND_STRING("被紧紧绑住，每一回合都会受到伤害。")
    },
    [INFO_BIDE] =
    {
        COMPOUND_STRING("忍耐"),
        COMPOUND_STRING("在2回合内忍受攻击，受到的伤害会2倍返还给对手。")
    },
    [INFO_RAMPAGING] =
    {
        COMPOUND_STRING("大闹一番"),
        COMPOUND_STRING("因处于大闹状态，在2～3回合内，乱打一气地进行攻击。大闹一番后自己会陷入混乱。")
    },
    [INFO_BADLY_POISONED] =
    {
        COMPOUND_STRING("剧毒"),
        COMPOUND_STRING("剧毒状态。随着回合的推进，中毒伤害会增加。")
    },
    [INFO_FUTURE_ATTACK] =
    {
        COMPOUND_STRING("未来攻击"),
        COMPOUND_STRING("被招式攻击的2回合后，会受到伤害。")
    },
    [INFO_UPROAR] =
    {
        COMPOUND_STRING("吵闹"),
        COMPOUND_STRING("在3回合内大吵大闹攻击对手。在此期间谁都不能入眠。")
    },
    [INFO_AQUA_RING] =
    {
        COMPOUND_STRING("水流环"),
        COMPOUND_STRING("在自己身体的周围覆盖用水制造的幕。每回合回复HP。")
    },
    [INFO_AUTOTOMIZE] =
    {
        COMPOUND_STRING("身体轻量化"),
        COMPOUND_STRING("速度会大幅度提高，体重也会变轻。")
    },
    [INFO_SMACK_DOWN] =
    {
        COMPOUND_STRING("击落"),
        COMPOUND_STRING("被击落，掉到地面的状态。")
    },
    [INFO_FAIRY_LOCK] =
    {
        COMPOUND_STRING("妖精之锁"),
        COMPOUND_STRING("在使用招式的下一回合，所有的宝可梦都无法逃走。")
    },
    [INFO_RAINBOW] =
    {
        COMPOUND_STRING("彩虹"),
        COMPOUND_STRING("招式的追加效果变得更易出现。")
    },
    [INFO_SWAMP] =
    {
        COMPOUND_STRING("湿地"),
        COMPOUND_STRING("速度变为原来的1/4。")
    },
    [INFO_SEA_OF_FIRE] =
    {
        COMPOUND_STRING("火海"),
        COMPOUND_STRING("火属性以外的宝可梦，每回合受到伤害。")
    },
    [INFO_EXTREMELY_HARSH_SUNLIGHT] =
    {
        COMPOUND_STRING("大日照"),
        COMPOUND_STRING("火属性的招式威力会提高。不会受到水属性招式的攻击。")
    },
    [INFO_HEAVY_RAIN] =
    {
        COMPOUND_STRING("大雨"),
        COMPOUND_STRING("水属性的招式威力会提高。不会受到火属性招式的攻击。")
    },
    [INFO_STRONG_WINDS] =
    {
        COMPOUND_STRING("乱流"),
        COMPOUND_STRING("与飞行属性相克且效果绝佳的属性，其招式威力会变弱。")
    },
    [INFO_PSYCHIC_TERRAIN] =
    {
        COMPOUND_STRING("精神场地"),
        COMPOUND_STRING("地面上的宝可梦不会受到先制招式的攻击。超能力属性的招式威力会提高。")
    },
    [INFO_THROAT_CHOP] =
    {
        COMPOUND_STRING("深渊突刺"),
        COMPOUND_STRING("在2回合内，无法使出发声音的招式。")
    },
    [INFO_AURORA_VEIL] =
    {
        COMPOUND_STRING("极光幕"),
        COMPOUND_STRING("物理与特殊攻击的威力会减半。")
    },
    [INFO_LASER_FOCUS] =
    {
        COMPOUND_STRING("磨砺"),
        COMPOUND_STRING("在使用磨砺的下一回合，招式必定会击中要害。")
    },
    [INFO_TAR_SHOT] =
    {
        COMPOUND_STRING("沥青射击"),
        COMPOUND_STRING("火属性会变成弱点。")
    },
    [INFO_OCTOLOCK] =
    {
        COMPOUND_STRING("蛸固"),
        COMPOUND_STRING("每回合降低防御和特防。")
    },
    [INFO_WIDE_OPEN] =
    {
        COMPOUND_STRING("无防备"),
        COMPOUND_STRING("对手的攻击必定会命中，且伤害会变成2倍。")
    },
    // G-Max effects
    [INFO_G_MAX_WILDFIRE] =
    {
        COMPOUND_STRING("超极巨深渊灭焰"),
        COMPOUND_STRING("4回合内对火属性以外的宝可梦造成伤害。")
    },
    [INFO_G_MAX_VOLCALITH] =
    {
        COMPOUND_STRING("超极巨炎石喷发"),
        COMPOUND_STRING("4回合内对岩石属性以外的宝可梦造成伤害。")
    },
    [INFO_G_MAX_STEELSURGE] =
    {
        COMPOUND_STRING("超极巨钢铁阵法"),
        COMPOUND_STRING("对替换出场的宝可梦造成伤害。")
    },
    [INFO_G_MAX_VINE_LASH] =
    {
        COMPOUND_STRING("超极巨灰飞鞭灭"),
        COMPOUND_STRING("4回合内对草属性以外的宝可梦造成伤害。")
    },
    [INFO_G_MAX_CANNONADE] =
    {
        COMPOUND_STRING("超极巨水炮轰灭"),
        COMPOUND_STRING("4回合内对水属性以外的宝可梦造成伤害。")
    },
    [INFO_FOG] =
    {
        COMPOUND_STRING("起雾"),
        COMPOUND_STRING("除必定命中的招式外，所有招式会变得不易命中。")
    },
    [INFO_SALT_CURE] =
    {
        COMPOUND_STRING("盐腌"),
        COMPOUND_STRING("会陷入盐腌状态，每回合受到伤害。钢属性和水属性宝可梦受到的伤害会变为2倍。")
    },
    [INFO_SYRUPY] =
    {
        COMPOUND_STRING("满身糖"),
        COMPOUND_STRING("在3回合内，持续降低速度。")
    },
    [INFO_GOING_ALL_OUT] =
    {
        COMPOUND_STRING("冲冲猛攻"),
        COMPOUND_STRING("在训练家们的声援下，攻击和特攻会提高。")
    },
    [INFO_HANGING_TOUGH] =
    {
        COMPOUND_STRING("坚坚固守"),
        COMPOUND_STRING("在训练家们的声援下，防御和特防会提高。")
    },
    [INFO_BATTLE_STATE_112] =
    {
        COMPOUND_STRING("-"),
        COMPOUND_STRING("无")
    },
    [INFO_RECHARGING] =
    {
        COMPOUND_STRING("反作用力"),
        COMPOUND_STRING("无法行动1回合。")
    },
    [INFO_CHARGING] =
    {
        COMPOUND_STRING("积蓄"),
        COMPOUND_STRING("为了使出招式，会积蓄1回合。")
    },
    [INFO_SKY_HIGH] =
    {
        COMPOUND_STRING("空中"), // Fly, Bounce, Sky Drop
        COMPOUND_STRING("不会被许多招式击中，但会被打雷、暴风、击落等击中。场地效果将无效。")
    },
    [INFO_SUBMERGED] =
    {
        COMPOUND_STRING("水中"), // Dive
        COMPOUND_STRING("不会被许多招式击中，但会被冲浪、潮旋击中，且伤害会变为2倍。场地的效果将无效。")
    },
    [INFO_UNDERGROUND] =
    {
        COMPOUND_STRING("地下"), // Dig
        COMPOUND_STRING("不会被许多招式击中，但会被地震击中，且伤害会变为2倍。场地的效果将无效。")
    },
    [INFO_CONCEALED] =
    {
        COMPOUND_STRING("潜伏"), // Shadow Force, Phantom Force
        COMPOUND_STRING("不会被招式击中，且场地的效果将无效。")
    },
    [INFO_MINIMIZED] =
    {
        COMPOUND_STRING("变小"),
        COMPOUND_STRING("闪电强袭、泰山压顶、龙之俯冲、飞身重压、高温重压、重磅冲撞等必定会击中，且伤害会变为2倍。")
    },
    [INFO_ATK_DEF_SWAPPED] =
    {
        COMPOUND_STRING("攻防转换"), // Power Trick
        COMPOUND_STRING("攻击、防御会互换。")
    },
    [INFO_FLASH_FIRE] =
    {
        COMPOUND_STRING("引火"),
        COMPOUND_STRING("火属性招式的威力会变为1.5倍。")
    },
    [INFO_MICLE_BERRY] =
    {
        COMPOUND_STRING("奇秘果"),
        COMPOUND_STRING("下次使出的招式的命中率会变为1.2倍。")
    },
};

static const u8 sBattleInfoHpBarTiles[8 * TILE_SIZE_4BPP] = {0};
static const u8 sBattleInfoHpBarLeftEndcapGfx[] = INCBIN_U8("graphics/battle_interface/hpbar_left_endcap.4bpp");
static const u8 sBattleInfoHpBarRightEndcapGfx[] = INCBIN_U8("graphics/battle_interface/hpbar_right_endcap.4bpp");
static const u16 sBattleInfoMenuBgPalette[] = INCBIN_U16("graphics/battle_interface/battle_status_menu.gbapal");
static const u32 sBattleInfoMenuBgTiles[] = INCBIN_U32("graphics/battle_interface/battle_status_menu.4bpp");
static const u16 sBattleInfoMenuOverviewBaseTilemap[] = INCBIN_U16("graphics/battle_interface/active_battlers_overview.bin");
static const u16 sBattleInfoMenuDetailsBaseTilemap[] = INCBIN_U16("graphics/battle_interface/active_battlers_details.bin");

static const struct OamData sOamData_BattleInfoHpBar =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x8),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct Subsprite sBattleInfoHpBarSubsprites[] =
{
    {
        .x = -16,
        .y = 0,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = 16,
        .y = 0,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 1
    }
};

static const struct SubspriteTable sBattleInfoHpBarSubspriteTable[] =
{
    {ARRAY_COUNT(sBattleInfoHpBarSubsprites), sBattleInfoHpBarSubsprites}
};

static const struct SpriteSheet sSpriteSheet_BattleInfoHpBar =
{
    sBattleInfoHpBarTiles, sizeof(sBattleInfoHpBarTiles), B_INFO_HP_BAR_TILE_TAG_BASE
};

static const struct SpritePalette sSpritePalette_BattleInfoHpBar =
{
    gBattleInterface_BallDisplayPal, B_INFO_HP_BAR_PAL_TAG
};

static const struct SpriteTemplate sSpriteTemplate_BattleInfoHpBar =
{
    .tileTag = B_INFO_HP_BAR_TILE_TAG_BASE,
    .paletteTag = B_INFO_HP_BAR_PAL_TAG,
    .oam = &sOamData_BattleInfoHpBar,
    .callback = SpriteCallbackDummy
};

static const struct OamData sOamData_BattleInfoHpBarEndcap =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteSheet sSpriteSheet_BattleInfoHpBarLeftEndcap =
{
    sBattleInfoHpBarLeftEndcapGfx, sizeof(sBattleInfoHpBarLeftEndcapGfx), B_INFO_HP_BAR_ENDCAP_LEFT_TILE_TAG
};

static const struct SpriteSheet sSpriteSheet_BattleInfoHpBarRightEndcap =
{
    sBattleInfoHpBarRightEndcapGfx, sizeof(sBattleInfoHpBarRightEndcapGfx), B_INFO_HP_BAR_ENDCAP_RIGHT_TILE_TAG
};

static const struct SpritePalette sSpritePalette_BattleInfoHpBarEndcap =
{
    gBattleInterface_BallDisplayPal, B_INFO_HP_BAR_ENDCAP_PAL_TAG
};

static const struct SpriteTemplate sSpriteTemplate_BattleInfoHpBarLeftEndcap =
{
    .tileTag = B_INFO_HP_BAR_ENDCAP_LEFT_TILE_TAG,
    .paletteTag = B_INFO_HP_BAR_ENDCAP_PAL_TAG,
    .oam = &sOamData_BattleInfoHpBarEndcap,
    .callback = SpriteCallbackDummy
};

static const struct SpriteTemplate sSpriteTemplate_BattleInfoHpBarRightEndcap =
{
    .tileTag = B_INFO_HP_BAR_ENDCAP_RIGHT_TILE_TAG,
    .paletteTag = B_INFO_HP_BAR_ENDCAP_PAL_TAG,
    .oam = &sOamData_BattleInfoHpBarEndcap,
    .callback = SpriteCallbackDummy
};

static const u8 sBattleInfoUpdateIconGfx[] = INCBIN_U8("graphics/battle_interface/update_indicator.4bpp");

static const struct OamData sOamData_BattleInfoUpdateIcon =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteSheet sSpriteSheet_BattleInfoUpdateIcon =
{
    sBattleInfoUpdateIconGfx, sizeof(sBattleInfoUpdateIconGfx), B_INFO_UPDATE_ICON_TILE_TAG
};

static const struct SpriteTemplate sSpriteTemplate_BattleInfoUpdateIcon =
{
    .tileTag = B_INFO_UPDATE_ICON_TILE_TAG,
    .paletteTag = TAG_MISC_INDICATOR_PAL,
    .oam = &sOamData_BattleInfoUpdateIcon,
    .callback = SpriteCallbackDummy
};

static const u8 sBattleInfoDetailStatPipDotGfx[] = INCBIN_U8("graphics/battle_interface/battle_status_stat_slot_indicator.4bpp");
static const u8 sBattleInfoDetailStatPipUpGfx[] = INCBIN_U8("graphics/battle_interface/battle_status_stat_raise_indicator.4bpp");
static const u8 sBattleInfoDetailStatPipDownGfx[] = INCBIN_U8("graphics/battle_interface/battle_status_stat_drop_indicator.4bpp");

static const struct OamData sOamData_BattleInfoDetailStatPip =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteSheet sSpriteSheet_BattleInfoDetailStatPipDot =
{
    sBattleInfoDetailStatPipDotGfx, sizeof(sBattleInfoDetailStatPipDotGfx), B_INFO_DETAIL_STAT_PIP_DOT_TILE_TAG
};

static const struct SpriteSheet sSpriteSheet_BattleInfoDetailStatPipUp =
{
    sBattleInfoDetailStatPipUpGfx, sizeof(sBattleInfoDetailStatPipUpGfx), B_INFO_DETAIL_STAT_PIP_UP_TILE_TAG
};

static const struct SpriteSheet sSpriteSheet_BattleInfoDetailStatPipDown =
{
    sBattleInfoDetailStatPipDownGfx, sizeof(sBattleInfoDetailStatPipDownGfx), B_INFO_DETAIL_STAT_PIP_DOWN_TILE_TAG
};

static const struct SpriteTemplate sSpriteTemplate_BattleInfoDetailStatPip =
{
    .tileTag = B_INFO_DETAIL_STAT_PIP_DOT_TILE_TAG,
    .paletteTag = B_INFO_DETAIL_STAT_PIP_PAL_TAG,
    .oam = &sOamData_BattleInfoDetailStatPip,
    .callback = SpriteCallbackDummy,
};

static const u8 sBattleInfoDetailEffectsScrollbarGfx[] = INCBIN_U8("graphics/battle_interface/scrollbar.4bpp");

static const struct OamData sOamData_BattleInfoDetailEffectsScrollbar =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteSheet sSpriteSheet_BattleInfoDetailEffectsScrollbar =
{
    sBattleInfoDetailEffectsScrollbarGfx, sizeof(sBattleInfoDetailEffectsScrollbarGfx), B_INFO_DETAIL_EFFECTS_SCROLLBAR_TILE_TAG
};

static const struct SpriteTemplate sSpriteTemplate_BattleInfoDetailEffectsScrollbar =
{
    .tileTag = B_INFO_DETAIL_EFFECTS_SCROLLBAR_TILE_TAG,
    .paletteTag = TAG_MISC_INDICATOR_PAL,
    .oam = &sOamData_BattleInfoDetailEffectsScrollbar,
    .callback = SpriteCallbackDummy,
};

static const u8 sBattleInfoCursorGfx[] = INCBIN_U8("graphics/battle_interface/arrow_indicator.4bpp");

static const struct OamData sOamData_BattleInfoCursor =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteTemplate sSpriteTemplate_BattleInfoCursor =
{
    .tileTag = B_INFO_CURSOR_TILE_TAG,
    .paletteTag = TAG_MISC_INDICATOR_PAL,
    .oam = &sOamData_BattleInfoCursor,
    .callback = SpriteCallbackDummy
};

static const struct SpriteSheet sSpriteSheet_BattleInfoCursor =
{
    sBattleInfoCursorGfx, sizeof(sBattleInfoCursorGfx), B_INFO_CURSOR_TILE_TAG
};

static const struct OamData sOamData_BattleInfoDetailGimmick =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x16),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x16),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteTemplate sSpriteTemplate_BattleInfoDetailGimmick =
{
    .tileTag = B_INFO_DETAIL_GIMMICK_TILE_TAG,
    .paletteTag = TAG_MISC_INDICATOR_PAL,
    .oam = &sOamData_BattleInfoDetailGimmick,
    .callback = SpriteCallbackDummy,
};

static const struct BgTemplate sBattleInfoMenuBgTemplates[] =
{
    [B_INFO_TEXT_BG] = {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
    [B_INFO_BACKDROP_BG] = {
        .bg = 1,
        .charBaseIndex = 3,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
};

static const struct WindowTemplate sBattleInfoMenuWindowTemplates[] =
{
    [WIN_LABEL_TOP] = {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 32,
        .height = B_INFO_LABEL_TILE_H,
        .paletteNum = B_INFO_TEXT_PAL,
        .baseBlock = B_INFO_WIN_LABEL_TOP_BASE,
    },
    [WIN_LABEL_BOTTOM] = {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = B_INFO_LABEL_BOTTOM_TILE_TOP,
        .width = 32,
        .height = B_INFO_LABEL_TILE_H,
        .paletteNum = B_INFO_TEXT_PAL,
        .baseBlock = B_INFO_WIN_LABEL_BOTTOM_BASE,
    },
    [WIN_ROW_ENEMY] = {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = B_INFO_ROW_Y_ENEMY / 8,
        .width = 32,
        .height = B_INFO_CARD_TILE_H,
        .paletteNum = B_INFO_TEXT_PAL,
        .baseBlock = B_INFO_WIN_ROW_ENEMY_BASE,
    },
    [WIN_ROW_PLAYER] = {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = B_INFO_ROW_Y_PLAYER / 8,
        .width = 32,
        .height = B_INFO_CARD_TILE_H,
        .paletteNum = B_INFO_TEXT_PAL,
        .baseBlock = B_INFO_WIN_ROW_PLAYER_BASE,
    },
    DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sBattleInfoDetailWindowTemplates[WIN_DETAIL_COUNT] =
{
    [WIN_DETAIL_HEADER] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 0,
        .width = B_INFO_DETAIL_HEADER_WIN_W,
        .height = B_INFO_DETAIL_HEADER_WIN_H,
        .paletteNum = B_INFO_TEXT_PAL,
        .baseBlock = B_INFO_WIN_DETAIL_HEADER_BASE,
    },
    [WIN_DETAIL_ITEM_ABILITY] = {
        .bg = 0,
        .tilemapLeft = 7,
        .tilemapTop = 4,
        .width = B_INFO_DETAIL_ITEM_WIN_W,
        .height = B_INFO_DETAIL_ITEM_WIN_H,
        .paletteNum = B_INFO_TEXT_PAL,
        .baseBlock = B_INFO_WIN_DETAIL_ITEM_BASE,
    },
    [WIN_DETAIL_STATS] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 9,
        .width = B_INFO_DETAIL_STATS_WIN_W,
        .height = B_INFO_DETAIL_STATS_WIN_H,
        .paletteNum = B_INFO_TEXT_PAL,
        .baseBlock = B_INFO_WIN_DETAIL_STATS_BASE,
    },
    [WIN_DETAIL_EFFECTS] = {
        .bg = 0,
        .tilemapLeft = 17,
        .tilemapTop = 0,
        .width = B_INFO_DETAIL_EFFECTS_WIN_W,
        .height = B_INFO_DETAIL_EFFECTS_WIN_H,
        .paletteNum = B_INFO_TEXT_PAL,
        .baseBlock = B_INFO_WIN_DETAIL_EFFECTS_BASE,
    },
    [WIN_DETAIL_DESCRIPTION] = {
        .bg = 0,
        .tilemapLeft = 17,
        .tilemapTop = 12,
        .width = B_INFO_DETAIL_DESC_WIN_W,
        .height = B_INFO_DETAIL_DESC_WIN_H,
        .paletteNum = B_INFO_TEXT_PAL,
        .baseBlock = B_INFO_WIN_DETAIL_DESC_BASE,
    },
};

void CB2_BattleInfoFromBattle(void)
{
    sData = AllocZeroed(sizeof(struct BattleInfoMenuData));

    if (sData == NULL)
    {
        SetMainCallback2(CB2_SetUpReshowBattleScreenAfterMenu);
        return;
    }

    SetMainCallback2(CB2_BattleInfoMenu);
}

static void CB2_BattleInfoMenu(void)
{
    switch (gMain.state)
    {
    case 0:
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        if (!MenuHelpers_IsLinkActive())
            ResetTasks();
        BattleInfoResetSpriteIds();
        gPaletteFade.bufferTransferDisabled = TRUE;
        gMain.state++;
        break;
    case 2:
        BattleInfoInitBgs();
        gMain.state++;
        break;
    case 3:
        InitWindows((const struct WindowTemplate[]){DUMMY_WIN_TEMPLATE});
        DeactivateAllTextPrinters();
        BattleInfoInit();
        BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gPaletteFade.bufferTransferDisabled = FALSE;
        gMain.state++;
        break;
    case 4:
        sData->menuState = B_INFO_STATE_HANDLE_INPUT;
        CreateTask(Task_BattleInfoLoadPage, 0);
        SetVBlankCallback(BattleInfoVBlankCB);
        SetMainCallback2(BattleInfoMainCB);
        gMain.state++;
        break;
    }
}

static void Task_BattleInfoLoadPage(u8 taskId)
{
    if (gPaletteFade.active)
        return;

    switch (sData->menuState)
    {
    case B_INFO_STATE_CLEAR_PAGE:
        if (sData->page == B_INFO_PAGE_DETAIL)
            Overview_Exit();
        else if (sData->page == B_INFO_PAGE_OVERVIEW)
            Detail_Exit();
        sData->menuState++;
        break;
    case B_INFO_STATE_ENTER_PAGE:
        if (sData->page == B_INFO_PAGE_DETAIL)
            Detail_Enter();
        else if (sData->page == B_INFO_PAGE_OVERVIEW)
            Overview_Enter();
        sData->menuState = B_INFO_STATE_HANDLE_INPUT;
        break;
    case B_INFO_STATE_EXIT:
        BattleInfoDestroy();
        FreeAllWindowBuffers();
        DestroyTask(taskId);
        SetMainCallback2(CB2_SetUpReshowBattleScreenAfterMenu);
        break;
    case B_INFO_STATE_HANDLE_INPUT:
        gTasks[taskId].func = Task_BattleMenuStatus_HandleInput;
        sData->menuState++;
        break;
    case B_INFO_STATE_DONE:
        break;
    }
}

static void BattleInfoVBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void BattleInfoMainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void DestroySpriteById(u8 *spriteId)
{
    if (*spriteId == SPRITE_NONE)
        return;
    DestroySprite(&gSprites[*spriteId]);
    *spriteId = SPRITE_NONE;
}

static void BattleInfoResetSpriteIds(void)
{
    sData->cursorSpriteId = SPRITE_NONE;
    sData->iconSpriteId = SPRITE_NONE;
    sData->hpBarSpriteId = SPRITE_NONE;
    sData->hpBarLeftEndcapSpriteId = SPRITE_NONE;
    sData->hpBarRightEndcapSpriteId = SPRITE_NONE;
    sData->statusSpriteId = SPRITE_NONE;
    sData->teraTypeSpriteId = SPRITE_NONE;
    sData->gimmickSpriteId = SPRITE_NONE;
    sData->effectsScrollbarSpriteId = SPRITE_NONE;
    sData->typeIconSpriteIds[0] = SPRITE_NONE;
    sData->typeIconSpriteIds[1] = SPRITE_NONE;

    for (u32 i = 0; i < B_INFO_DETAIL_STAT_ROW_COUNT; i++)
    {
        for (u32 j = 0; j < B_INFO_DETAIL_STAT_PIPS_PER_ROW; j++)
            sData->statPipSpriteIds[i][j] = SPRITE_NONE;
    }

    for (u32 i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        sData->cards[i].hpBarSpriteId = SPRITE_NONE;
        sData->cards[i].monIconSpriteId = SPRITE_NONE;
        sData->cards[i].gimmickSpriteId = SPRITE_NONE;
        sData->cards[i].statusSpriteId = SPRITE_NONE;
        sData->cards[i].updateSpriteId = SPRITE_NONE;
        sData->cards[i].hpBarLeftEndcapSpriteId = SPRITE_NONE;
        sData->cards[i].hpBarRightEndcapSpriteId = SPRITE_NONE;
    }
}

static void BattleInfoInitBgs(void)
{
    ResetVramOamAndBgCntRegs();
    ResetBgsAndClearDma3BusyFlags(0);
    CpuFill16(0, (void *)BG_CHAR_ADDR(0), BG_CHAR_SIZE);
    CpuFill16(0, (void *)BG_CHAR_ADDR(2), BG_CHAR_SIZE);
    CpuFill16(0, (void *)BG_CHAR_ADDR(3), BG_CHAR_SIZE);

    InitBgsFromTemplates(0, sBattleInfoMenuBgTemplates, ARRAY_COUNT(sBattleInfoMenuBgTemplates));
    SetBgTilemapBuffer(B_INFO_TEXT_BG, sData->bg0Tilemap);
    SetBgTilemapBuffer(B_INFO_BACKDROP_BG, sData->bg1Tilemap);
    FillBgTilemapBufferRect(B_INFO_TEXT_BG, 0, 0, 0, B_INFO_TILEMAP_WIDTH, B_INFO_TILEMAP_HEIGHT, 0);
    FillBgTilemapBufferRect(B_INFO_BACKDROP_BG, 0, 0, 0, B_INFO_TILEMAP_WIDTH, B_INFO_TILEMAP_HEIGHT, 0);
    CopyBgTilemapBufferToVram(B_INFO_TEXT_BG);
    CopyBgTilemapBufferToVram(B_INFO_BACKDROP_BG);

    ResetAllBgsCoordinates();
    LoadBgTiles(B_INFO_BACKDROP_BG, sBattleInfoMenuBgTiles, sizeof(sBattleInfoMenuBgTiles), 0);
    LoadPalette(sBattleInfoMenuBgPalette, BG_PLTT_ID(0), sizeof(sBattleInfoMenuBgPalette));
    LoadPalette(gBattleInfoTextPalette, BG_PLTT_ID(B_INFO_TEXT_PAL), PLTT_SIZE_4BPP);

    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    ShowBg(B_INFO_BACKDROP_BG);
    ShowBg(B_INFO_TEXT_BG);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
}

static void BattleInfoInit(void)
{
    LoadMonIconPalettes();
    LoadPartyMenuAilmentGfx();
    LoadSpriteSheet(&sSpriteSheet_BattleInfoHpBar);
    LoadSpriteSheet(&sSpriteSheet_BattleInfoHpBarLeftEndcap);
    LoadSpriteSheet(&sSpriteSheet_BattleInfoHpBarRightEndcap);
    LoadSpritePalette(&sSpritePalette_BattleInfoHpBar);
    LoadSpritePalette(&sSpritePalette_BattleInfoHpBarEndcap);
    LoadSpriteSheet(&sSpriteSheet_BattleInfoUpdateIcon);
    LoadCompressedSpriteSheet(&gSpriteSheet_MoveTypes);
    LoadSpritePaletteInSlot(&(struct SpritePalette){ .data = gMoveTypes_Pal,      .tag = gSpriteTemplate_MoveTypes.paletteTag }, 13);
    LoadSpritePaletteInSlot(&(struct SpritePalette){ .data = gMoveTypes_Pal + 16, .tag = B_INFO_MOVE_TYPES_PAL_TAG_1 }, 14);
    LoadSpritePaletteInSlot(&(struct SpritePalette){ .data = gMoveTypes_Pal + 32, .tag = B_INFO_MOVE_TYPES_PAL_TAG_2 }, 15);
    LoadSpriteSheet(&sSpriteSheet_BattleInfoDetailEffectsScrollbar);
    LoadSpriteSheet(&sSpriteSheet_BattleInfoCursor);
    LoadIndicatorSpritesGfx();
    Overview_CreateWindows();
    Overview_Enter();
}

static void Overview_Enter(void)
{
    sData->page = B_INFO_PAGE_OVERVIEW;
    LoadBackdropAssets();
    Overview_ClearWindows();
    Overview_InitCardValues();
    Overview_DrawBackground();
    Overview_DrawCards();
    Overview_DrawLabels();
    Overview_InitCursor();
    ShowBg(B_INFO_BACKDROP_BG);
    ShowBg(B_INFO_TEXT_BG);
}

static void Overview_Exit(void)
{
    DestroySpriteById(&sData->cursorSpriteId);

    for (u32 i = 0; i < GetCardCount(); i++)
        DestroyOverviewCardSprites(&sData->cards[i]);

    Overview_ClearWindows();
}

static void Overview_CreateWindows(void)
{
    InitWindows(sBattleInfoMenuWindowTemplates);
    Overview_ClearWindows();
}

static void Overview_ClearWindows(void)
{
    for (u32 i = 0; i < GetCardCount(); i++)
    {
        FillWindowPixelBuffer(i, PIXEL_FILL(B_INFO_TEXT_COLOR_TRANSPARENT));
        ClearWindowTilemap(i);
        CopyWindowToVram(i, COPYWIN_GFX);
    }

    CopyBgTilemapBufferToVram(B_INFO_TEXT_BG);
}

static void Detail_Enter(void)
{
    DestroySpriteById(&sData->cursorSpriteId);

    sData->page = B_INFO_PAGE_DETAIL;
    sData->iconSpriteId = SPRITE_NONE;
    sData->hpBarSpriteId = SPRITE_NONE;
    sData->statusSpriteId = SPRITE_NONE;
    sData->teraTypeSpriteId = SPRITE_NONE;
    sData->gimmickSpriteId = SPRITE_NONE;
    LoadBackdropAssets();
    BackdropLoadBaseTilemap();
    FillBgTilemapBufferRect(B_INFO_TEXT_BG, 0, 0, 0, B_INFO_TILEMAP_WIDTH, B_INFO_TILEMAP_HEIGHT, 0);
    CopyBgTilemapBufferToVram(B_INFO_TEXT_BG);
    Detail_CreateWindows();
    Detail_DrawStatLabels();
    Detail_DrawItemAbilityWindow();
    Detail_InitEffectsList();
    Detail_CreateStatPips();
    Detail_RefreshStatPips();
    Detail_RefreshHeader();
    Detail_RefreshItemAbilityWindow();
    Detail_RefreshIcon();
    Detail_RefreshHpBar();
    Detail_RefreshStatusIcon();
    Detail_RefreshTypeIcons();
    ShowBg(B_INFO_BACKDROP_BG);
    ShowBg(B_INFO_TEXT_BG);
}

static void Detail_Exit(void)
{
    Detail_DestroyWindows();
    Detail_DestroyHpBar();
    Detail_DestroyStatusIcon();
    Detail_DestroyTeraTypeIndicator();
    Detail_DestroyGimmickIndicator();
    Detail_DestroyTypeIcons();
    Detail_DestroyStatPips();
    DestroySpriteById(&sData->effectsScrollbarSpriteId);
    DestroySpriteById(&sData->cursorSpriteId);
    Detail_DestroyIconSprite();
    sData->activeEffectsCount = 0;
    sData->effectsCursor = 0;
    sData->effectsScroll = 0;

    FillBgTilemapBufferRect(B_INFO_TEXT_BG, 0, 0, 0, B_INFO_TILEMAP_WIDTH, B_INFO_TILEMAP_HEIGHT, 0);
    CopyBgTilemapBufferToVram(B_INFO_TEXT_BG);
}

static void Detail_CreateWindows(void)
{
    for (u32 i = 0; i < WIN_DETAIL_COUNT; i++)
        sData->windowIds[i] = WINDOW_NONE;

    for (u32 i = 0; i < WIN_DETAIL_COUNT; i++)
    {
        if (i == WIN_DETAIL_ITEM_ABILITY)
            continue;

        sData->windowIds[i] = AddWindow(&sBattleInfoDetailWindowTemplates[i]);
        if (sData->windowIds[i] != WINDOW_NONE)
            Detail_ResetWithTransparentTextColor(sData->windowIds[i]);
    }

    sData->windowIds[WIN_DETAIL_ITEM_ABILITY] = sData->windowIds[WIN_DETAIL_HEADER];
}

static void Detail_DestroyWindows(void)
{
    u32 mergedInfoWindowId = sData->windowIds[WIN_DETAIL_HEADER];

    for (u32 i = 0; i < WIN_DETAIL_COUNT; i++)
    {
        u32 windowId = sData->windowIds[i];

        if (windowId == WINDOW_NONE)
            continue;

        if (i == WIN_DETAIL_ITEM_ABILITY && windowId == mergedInfoWindowId)
        {
            sData->windowIds[i] = WINDOW_NONE;
            continue;
        }

        FillWindowPixelBuffer(windowId, PIXEL_FILL(B_INFO_TEXT_COLOR_TRANSPARENT));
        ClearWindowTilemap(windowId);
        CopyWindowToVram(windowId, COPYWIN_GFX);
        RemoveWindow(windowId);
        sData->windowIds[i] = WINDOW_NONE;
    }

    CopyBgTilemapBufferToVram(B_INFO_TEXT_BG);
}

static void Detail_DrawStatLabels(void)
{
    u32 windowId = sData->windowIds[WIN_DETAIL_STATS];
    Detail_ResetWithTransparentTextColor(windowId);
    for (u32 i = 0; i < B_INFO_DETAIL_STAT_ROW_COUNT; i++)
    {
        AddTextPrinterParameterized4(
            windowId, FONT_SMALL_NARROW, 2,
            Detail_GetStatRowTextY(i), 0, 0,
            sTextColor_BattleInfo_Default, TEXT_SKIP_DRAW,
            sBattleInfoDetailStatLabels[i]
        );
    }
    PutWindowTilemap(windowId);
    CopyWindowToVram(windowId, COPYWIN_FULL);
}

static void Detail_DrawItemAbilityWindow(void)
{
    u32 windowId = sData->windowIds[WIN_DETAIL_ITEM_ABILITY];
    Detail_ResetWithTransparentTextColor(windowId);
    Detail_DrawLRButtonGlyphs();
    PutWindowTilemap(windowId);
    CopyWindowToVram(windowId, COPYWIN_FULL);
}

static void Detail_DestroyHpBar(void)
{
    DestroySpriteById(&sData->hpBarSpriteId);

    DestroyHpBarEndcaps(&sData->hpBarLeftEndcapSpriteId, &sData->hpBarRightEndcapSpriteId);
    FreeSpriteTilesByTag(B_INFO_DETAIL_HP_BAR_TILE_TAG);
}

static void SetHpBarEndcapInvisible(u32 hpBarEndcap)
{
    if (hpBarEndcap == SPRITE_NONE)
        return;
    gSprites[hpBarEndcap].invisible = TRUE;
}

static void Detail_RefreshHpBar(void)
{
    enum BattlerId battler = GetSelectedBattler();
    u32 hp = gBattleMons[battler].hp;
    u32 maxHp = gBattleMons[battler].maxHP;
    struct Sprite *sprite;

    if (sData->hpBarSpriteId == SPRITE_NONE)
    {
        sData->hpBarSpriteId = CreateHpBarSprite(B_INFO_DETAIL_HP_BAR_TILE_TAG, 21, 70);
        CreateHpBarEndcaps(&sData->hpBarLeftEndcapSpriteId, &sData->hpBarRightEndcapSpriteId);
    }

    sprite = &gSprites[sData->hpBarSpriteId];
    sprite->x = 21;
    sprite->y = 70;

    if (maxHp <= 0)
    {
        sprite->invisible = TRUE;
        SetHpBarEndcapInvisible(sData->hpBarLeftEndcapSpriteId);
        SetHpBarEndcapInvisible(sData->hpBarRightEndcapSpriteId);
        return;
    }

    UpdateHpBarTilesWithWidth(
        sData->hpBarSpriteId, hp, maxHp,
        B_INFO_DETAIL_HEALTHBAR_PIXELS,
        B_INFO_DETAIL_HP_BAR_SEGMENTS
    );

    sprite->invisible = FALSE;
    UpdateHpBarEndcaps(
        sData->hpBarLeftEndcapSpriteId,
        sData->hpBarRightEndcapSpriteId,
        21, 70, B_INFO_DETAIL_HP_BAR_SEGMENTS
    );
}

static void Detail_DestroyStatusIcon(void)
{
    DestroySpriteById(&sData->statusSpriteId);
}

static void Detail_RefreshStatusIcon(void)
{
    u32 ailment = GetAilmentFromBattler(GetSelectedBattler());

    Detail_DestroyStatusIcon();

    if (ailment == AILMENT_NONE || ailment == AILMENT_PKRS)
        return;

    sData->statusSpriteId = CreateSprite(&gSpriteTemplate_StatusIcons, 46, 66, 0);
    StartSpriteAnim(&gSprites[sData->statusSpriteId], ailment - 1);
    gSprites[sData->statusSpriteId].oam.priority = 0;
}

static void Detail_DrawLRButtonGlyphs(void)
{
    s32 rGlyphWidth = GetKeypadIconWidth(CHAR_R_BUTTON);

    if (rGlyphWidth == 0)
        rGlyphWidth = GetStringWidth(FONT_SHORT_NARROW, sText_BattleInfo_DetailRButtonGlyph, 0);

    struct PrintText text = {
        .font = FONT_SHORT_NARROW,
        .color = sTextColor_BattleInfo_Default,
        .speed = TEXT_SKIP_DRAW,
        .string = sText_BattleInfo_DetailLButtonGlyph,
    };

    s32 alignedAbsY = Detail_DrawLRButtonGlyphsItemAbility(text, rGlyphWidth);
    Detail_DrawLRButtonGlyphsStats(text, alignedAbsY);
}

static s32 Detail_DrawLRButtonGlyphsItemAbility(struct PrintText text, s32 rGlyphWidth)
{
    u32 window = sData->windowIds[WIN_DETAIL_ITEM_ABILITY];
    u32 windowWidth = WindowWidthPx(window);
    u32 windowHeight = GetWindowAttribute(window, WINDOW_HEIGHT) * 8;
    s32 absTop = GetWindowAttribute(window, WINDOW_TILEMAP_TOP) * 8;

    s32 itemY = windowHeight - KEYPAD_ICON_HEIGHT - 1;
    itemY -= 5;
    itemY = max(itemY, 1);

    s32 alignedAbsY = absTop + itemY;
    s32 itemX = windowWidth - rGlyphWidth - 2;
    itemX = max(itemX, 1);
    itemY -= 1;
    itemY = max(itemY, 0);

    text.windowId = window;
    text.left = itemX;
    text.top = itemY;
    PrintTextOnWindow(&text);
    return alignedAbsY;
}

static void Detail_DrawLRButtonGlyphsStats(struct PrintText text, s32 alignedAbsY)
{
    u32 window = sData->windowIds[WIN_DETAIL_STATS];
    s32 absTop = GetWindowAttribute(window, WINDOW_TILEMAP_TOP) * 8;

    s32 statsY = alignedAbsY - absTop;
    statsY -= 1;
    statsY = max(statsY, 0);

    text.windowId = window;
    text.left = 1;
    text.top = statsY;
    PrintTextOnWindow(&text);
}

static void Detail_DestroyTeraTypeIndicator(void)
{
    DestroySpriteById(&sData->teraTypeSpriteId);
    FreeSpriteTilesByTag(B_INFO_DETAIL_TERA_TYPE_TILE_TAG);
}

static void Detail_RefreshTeraTypeIndicator(void)
{
    u32 windowId = sData->windowIds[WIN_DETAIL_HEADER];
    struct SpriteSheet sheet;
    struct SpriteTemplate template = sSpriteTemplate_BattleInfoDetailGimmick;

    Detail_DestroyTeraTypeIndicator();

    if (!FlagGet(B_FLAG_TERA_ORB_CHARGED))
        return;

    enum Type teraType = GetBattlerTeraType(GetSelectedBattler());
    const u32 *indicatorData = GetTeraIndicatorSpriteSrc(teraType);
    if (indicatorData == NULL)
        return;

    sheet.data = (const u8 *)indicatorData;
    sheet.size = B_INFO_DETAIL_GIMMICK_GFX_SIZE;
    sheet.tag = B_INFO_DETAIL_TERA_TYPE_TILE_TAG;
    LoadSpriteSheet(&sheet);

    template.tileTag = B_INFO_DETAIL_TERA_TYPE_TILE_TAG;
    template.paletteTag = TAG_TERA_INDICATOR_PAL;

    u32 windowLeftPx = GetWindowAttribute(windowId, WINDOW_TILEMAP_LEFT) * 8;
    u32 windowTopPx = GetWindowAttribute(windowId, WINDOW_TILEMAP_TOP) * 8;
    sData->teraTypeSpriteId = CreateSprite(&template, windowLeftPx + 24 + (B_INFO_DETAIL_GIMMICK_W / 2), windowTopPx + 23, 0);

    if (sData->teraTypeSpriteId != SPRITE_NONE)
        gSprites[sData->teraTypeSpriteId].oam.priority = 0;
}

static const u8 *GetGimmickIndicatorData(enum BattlerId battler, u32 *palTag)
{
    const u32 *indicatorData = GetIndicatorSpriteSrc(battler);

    *palTag = GetIndicatorPalTag(battler);
    if (indicatorData == NULL || *palTag == TAG_NONE)
        return NULL;

    return (const u8 *)indicatorData;
}

static void Detail_DestroyGimmickIndicator(void)
{
    DestroySpriteById(&sData->gimmickSpriteId);
    FreeSpriteTilesByTag(B_INFO_DETAIL_GIMMICK_TILE_TAG);
}

static void Detail_RefreshGimmickIndicator(void)
{
    u32 windowId = sData->windowIds[WIN_DETAIL_HEADER];
    struct SpriteTemplate template = sSpriteTemplate_BattleInfoDetailGimmick;

    Detail_DestroyGimmickIndicator();

    u32 palTag;
    const u8 *indicatorData = GetGimmickIndicatorData(GetSelectedBattler(), &palTag);
    if (indicatorData == NULL || palTag == 0)
        return;

    struct SpriteSheet sheet = {
        .data = indicatorData,
        .size = B_INFO_DETAIL_GIMMICK_GFX_SIZE,
        .tag = B_INFO_DETAIL_GIMMICK_TILE_TAG,
    };
    LoadSpriteSheet(&sheet);

    template.paletteTag = palTag;
    u32 windowLeftPx = GetWindowAttribute(windowId, WINDOW_TILEMAP_LEFT) * 8;
    u32 windowTopPx = GetWindowAttribute(windowId, WINDOW_TILEMAP_TOP) * 8;
    u32 indicatorLeftPx = windowLeftPx + 2;
    u32 indicatorTopPx = windowTopPx + 33;

    sData->gimmickSpriteId = CreateSprite(&template, indicatorLeftPx + (B_INFO_DETAIL_GIMMICK_W / 2), indicatorTopPx + (B_INFO_DETAIL_GIMMICK_H / 2), 0);

    if (sData->gimmickSpriteId != SPRITE_NONE)
        gSprites[sData->gimmickSpriteId].oam.priority = 0;
}

static void Detail_RefreshItemAbilityWindow(void)
{
    enum BattlerId battler = GetSelectedBattler();
    u32 windowId = sData->windowIds[WIN_DETAIL_HEADER];
    u32 statsWindowId = sData->windowIds[WIN_DETAIL_STATS];

    if (IsOnPlayerSide(battler) || B_INFO_OPPOSING_INFORMATION)
    {
        struct PrintText text = {
            .windowId = windowId,
            .font = FONT_SHORT_NARROW,
            .color = sTextColor_BattleInfo_Default,
            .speed = TEXT_SKIP_DRAW,
            .left = 50,
        };

        PrintHeldItemText(text, battler);
        PrintAbilityText(text, battler);
    }

    Detail_DrawLRButtonGlyphs();
    PutWindowTilemap(windowId);
    CopyWindowToVram(windowId, COPYWIN_FULL);
    PutWindowTilemap(statsWindowId);
    CopyWindowToVram(statsWindowId, COPYWIN_FULL);
}

#define MAX_VALUE_WIDTH ((B_INFO_DETAIL_ITEM_WIN_W * 8) - 6)
static void PrintHeldItemText(struct PrintText text, enum BattlerId battler)
{
    text.top = 33;
    text.string = COMPOUND_STRING("持有物");
    PrintTextOnWindow(&text);

    enum Item heldItem = gBattleMons[battler].item;
    const u8 *string = (heldItem != ITEM_NONE) ? GetItemName(heldItem) : COMPOUND_STRING("无");

    text.font = GetFontIdToFit(string, FONT_SMALL, 0, MAX_VALUE_WIDTH);
    text.top = 43;
    text.string = string;
    PrintTextOnWindow(&text);
}

static void PrintAbilityText(struct PrintText text, enum BattlerId battler)
{
    text.top = 56;
    text.string = COMPOUND_STRING("特性");
    PrintTextOnWindow(&text);

    enum Ability ability = gBattleMons[battler].ability;
    const u8 *string = (ability != ABILITY_NONE) ? gAbilitiesInfo[ability].name : COMPOUND_STRING("无");

    text.font = GetFontIdToFit(string, FONT_SMALL, 0, MAX_VALUE_WIDTH);
    text.top = 66;
    text.string = string;
    PrintTextOnWindow(&text);
}
#undef MAX_VALUE_WIDTH

static void Detail_RefreshHeader(void)
{
    u32 windowId = sData->windowIds[WIN_DETAIL_HEADER];
    struct Pokemon *mon = GetBattlerMon(GetSelectedBattler());

    Detail_ResetWithTransparentTextColor(windowId);
    s32 genderX = WindowWidthPx(windowId) - 2 - B_INFO_GENDER_W;
    u8 maxLevelText[2] = { CHAR_EXTRA_SYMBOL, CHAR_LV_2 };

    ConvertIntToDecimalStringN(maxLevelText + 2, 999, STR_CONV_MODE_LEFT_ALIGN, 3);

    s32 levelMaxWidth = GetStringWidth(FONT_SMALL, maxLevelText, 0);
    s32 levelX = genderX - 2 - levelMaxWidth;
    levelX = max(levelX, 2);

    struct PrintText text = {
        .windowId = windowId,
        .color = sTextColor_BattleInfo_Default,
        .speed = TEXT_SKIP_DRAW,
    };

    Detail_PrintMonName(text, mon, levelX);
    Detail_DisplayMonGender(text, mon, genderX);
    Detail_DisplayMonLevel(text, mon, levelX);
    Detail_DisplayGimmickIndicator(text);

    PutWindowTilemap(windowId);
    CopyWindowToVram(windowId, COPYWIN_FULL);
}

static void Detail_PrintMonName(struct PrintText text, struct Pokemon *mon, s32 levelX)
{
    u8 monName[POKEMON_NAME_LENGTH + 1];
    GetMonData(mon, MON_DATA_NICKNAME, monName);
    u32 maxNameWidth = max(levelX - 4, 16);
    text.font = GetFontIdToFit(monName, FONT_NORMAL, 0, maxNameWidth);
    text.left = 2;
    text.top = 2;
    text.string = monName;
    PrintTextOnWindow(&text);
}

static void Detail_DisplayMonGender(struct PrintText text, struct Pokemon *mon, s32 genderX)
{
    enum Gender gender = GetMonGender(mon);

    if (gender == MON_MALE || gender == MON_FEMALE)
    {
        text.color = (gender == MON_MALE) ? sTextColor_BattleInfo_Male : sTextColor_BattleInfo_Female;

        u8 genderSymbol[2];
        genderSymbol[0] = (gender == MON_MALE) ? CHAR_MALE : CHAR_FEMALE;
        genderSymbol[1] = EOS;
        text.font = FONT_SMALL;
        text.left = genderX;
        text.top = 2;
        text.string = genderSymbol;
        PrintTextOnWindow(&text);
    }
}

static void Detail_DisplayMonLevel(struct PrintText text, struct Pokemon *mon, s32 levelX)
{
    u32 level = GetMonData(mon, MON_DATA_LEVEL);
    u8 levelText[2] = { CHAR_EXTRA_SYMBOL, CHAR_LV_2 };
    ConvertIntToDecimalStringN(levelText + 2, level, STR_CONV_MODE_LEFT_ALIGN, 3);

    text.font = FONT_SMALL;
    text.left = levelX;
    text.top = 2;
    text.string = levelText;
    PrintTextOnWindow(&text);
}

static void Detail_DisplayGimmickIndicator(struct PrintText text)
{
    Detail_DestroyGimmickIndicator();

    if (FlagGet(B_FLAG_TERA_ORB_CHARGED) && IsOnPlayerSide(GetSelectedBattler()))
    {
        text.font = FONT_SMALL_NARROWER;
        text.left = 2;
        text.top = 14;
        text.string = COMPOUND_STRING("太晶\n属性:");
        PrintTextOnWindow(&text);
        Detail_RefreshTeraTypeIndicator();
    }
    else
    {
        Detail_DestroyTeraTypeIndicator();
    }

    Detail_RefreshGimmickIndicator();
}

static void Detail_RefreshIcon(void)
{
    struct Pokemon *mon;
    enum Species species;
    u32 personality;

    Detail_DestroyIconSprite();

    mon = GetBattlerMon(GetSelectedBattler());
    species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);
    personality = GetMonData(mon, MON_DATA_PERSONALITY);

    sData->iconSpriteId = CreateMonIcon(species, SpriteCallbackDummy, 33, 52, 0, personality);
    if (sData->iconSpriteId != SPRITE_NONE)
        gSprites[sData->iconSpriteId].oam.priority = 0;
}

static void Detail_DestroyTypeIcons(void)
{
    for (u32 i = 0; i < ARRAY_COUNT(sData->typeIconSpriteIds); i++)
        DestroySpriteById(&sData->typeIconSpriteIds[i]);
}

static void Detail_RefreshTypeIcons(void)
{
    enum BattlerId battler = GetSelectedBattler();
    enum Type type1 = gBattleMons[battler].types[0];
    enum Type type2 = gBattleMons[battler].types[1];
    u32 windowId = sData->windowIds[WIN_DETAIL_HEADER];

    Detail_DestroyTypeIcons();

    if (GetActiveGimmick(battler) == GIMMICK_TERA)
    {
        type1 = GetBattlerTeraType(battler);
        type2 = type1;
    }

    s32 windowLeftPx = GetWindowAttribute(windowId, WINDOW_TILEMAP_LEFT) * 8;
    s32 windowTopPx = GetWindowAttribute(windowId, WINDOW_TILEMAP_TOP) * 8;

    s32 rightAlignedTypeRightPx = windowLeftPx + WindowWidthPx(windowId) - 2;
    s32 type2LeftPx = rightAlignedTypeRightPx - 32;
    s32 type1LeftPx = type2LeftPx - 33;

    u32 spriteId = CreateSprite(&gSpriteTemplate_MoveTypes, type1LeftPx + 16, windowTopPx + 25, 0);

    StartSpriteAnim(&gSprites[spriteId], type1);
    gSprites[spriteId].oam.paletteNum = gTypesInfo[type1].palette;
    gSprites[spriteId].oam.priority = 0;
    sData->typeIconSpriteIds[0] = spriteId;

    if (type2 == type1)
        return;

    spriteId = CreateSprite(&gSpriteTemplate_MoveTypes, type2LeftPx + 16, windowTopPx + 25, 0);

    StartSpriteAnim(&gSprites[spriteId], type2);
    gSprites[spriteId].oam.paletteNum = gTypesInfo[type2].palette;
    gSprites[spriteId].oam.priority = 0;
    sData->typeIconSpriteIds[1] = spriteId;
}

static s32 Detail_GetStatRowTextY(u32 row)
{
    u32 y = 15 + row * 9;

    if (row >= 5)
        y += 3;

    return y;
}

static void Detail_SetStatPipSpriteGraphic(u32 spriteId, u32 tileTag)
{
    u32 tileStart;

    if (spriteId == SPRITE_NONE)
        return;

    tileStart = GetSpriteTileStartByTag(tileTag);

    if (tileStart == 0xFFFF)
        return;

    gSprites[spriteId].oam.tileNum = tileStart;
}

static void Detail_CreateStatPips(void)
{
    u32 windowId = sData->windowIds[WIN_DETAIL_STATS];

    Detail_DestroyStatPips();

    LoadSpritePaletteInSlot(&(struct SpritePalette){
        .data = gBattleInfoTextPalette,
        .tag = B_INFO_DETAIL_STAT_PIP_PAL_TAG,
    }, B_INFO_DETAIL_STAT_PIP_PAL_NUM);
    LoadSpriteSheet(&sSpriteSheet_BattleInfoDetailStatPipDot);
    LoadSpriteSheet(&sSpriteSheet_BattleInfoDetailStatPipUp);
    LoadSpriteSheet(&sSpriteSheet_BattleInfoDetailStatPipDown);

    s32 windowLeftPx = GetWindowAttribute(windowId, WINDOW_TILEMAP_LEFT) * 8;
    s32 windowTopPx = GetWindowAttribute(windowId, WINDOW_TILEMAP_TOP) * 8;

    for (u32 row = 0; row < B_INFO_DETAIL_STAT_ROW_COUNT; row++)
    {
        s32 rowY = windowTopPx + Detail_GetStatRowTextY(row) + 8;

        for (u32 col = 0; col < B_INFO_DETAIL_STAT_PIPS_PER_ROW; col++)
        {
            u32 spriteId = CreateSprite(&sSpriteTemplate_BattleInfoDetailStatPip,
                                       windowLeftPx + 56 + col * 8,
                                       rowY, 0);
            sData->statPipSpriteIds[row][col] = spriteId;

            if (spriteId == SPRITE_NONE)
                continue;

            gSprites[spriteId].invisible = FALSE;
            gSprites[spriteId].oam.priority = 0;
        }
    }
}

static void Detail_DestroyStatPips(void)
{
    for (u32 row = 0; row < B_INFO_DETAIL_STAT_ROW_COUNT; row++)
    {
        for (u32 col = 0; col < B_INFO_DETAIL_STAT_PIPS_PER_ROW; col++)
        {
            u32 spriteId = sData->statPipSpriteIds[row][col];

            if (spriteId == SPRITE_NONE)
                continue;
            DestroySprite(&gSprites[spriteId]);
            sData->statPipSpriteIds[row][col] = SPRITE_NONE;
        }
    }

    FreeSpriteTilesByTag(B_INFO_DETAIL_STAT_PIP_DOT_TILE_TAG);
    FreeSpriteTilesByTag(B_INFO_DETAIL_STAT_PIP_UP_TILE_TAG);
    FreeSpriteTilesByTag(B_INFO_DETAIL_STAT_PIP_DOWN_TILE_TAG);
    FreeSpritePaletteByTag(B_INFO_DETAIL_STAT_PIP_PAL_TAG);
}

static void Detail_RefreshStatPips(void)
{
    enum BattlerId battler = GetSelectedBattler();

    for (u32 row = 0; row < B_INFO_DETAIL_STAT_ROW_COUNT; row++)
    {
        s32 delta = gBattleMons[battler].statStages[sBattleInfoDetailStatIds[row]] - DEFAULT_STAT_STAGE;
        u32 absDelta = (delta >= 0) ? delta : -delta;
        u32 tileTag = B_INFO_DETAIL_STAT_PIP_DOT_TILE_TAG;

        if (absDelta > B_INFO_DETAIL_STAT_PIPS_PER_ROW)
            absDelta = B_INFO_DETAIL_STAT_PIPS_PER_ROW;

        if (delta > 0)
            tileTag = B_INFO_DETAIL_STAT_PIP_UP_TILE_TAG;
        else if (delta < 0)
            tileTag = B_INFO_DETAIL_STAT_PIP_DOWN_TILE_TAG;

        for (u32 col = 0; col < B_INFO_DETAIL_STAT_PIPS_PER_ROW; col++)
        {
            u32 spriteId = sData->statPipSpriteIds[row][col];
            u32 currentTag = (col < absDelta) ? tileTag : B_INFO_DETAIL_STAT_PIP_DOT_TILE_TAG;

            Detail_SetStatPipSpriteGraphic(spriteId, currentTag);
        }
    }
}

static void Detail_CycleBattler(s32 direction)
{
    Detail_DestroyGimmickIndicator();
    Detail_DestroyTeraTypeIndicator();

    if (direction < 0)
        Detail_PreviousBattler();
    else
        Detail_NextBattler();

    Detail_RefreshIcon();
    Detail_RefreshHpBar();
    Detail_RefreshStatusIcon();
    Detail_RefreshTypeIcons();
    Detail_RefreshHeader();
    Detail_RefreshItemAbilityWindow();
    Detail_RefreshStatPips();
    Detail_InitEffectsList();
}

static void Detail_PreviousBattler(void)
{
    do {
        if (sData->selectedCard == 0)
            sData->selectedCard = GetCardCount() - 1;
        else
            sData->selectedCard--;
    } while (!CanViewCard(GetSelectedBattler()));
}

static void Detail_NextBattler(void)
{
    do {
        sData->selectedCard++;
        if (sData->selectedCard >= GetCardCount())
            sData->selectedCard = 0;
    } while (!CanViewCard(GetSelectedBattler()));
}

static void Detail_InitEffectsList(void)
{
    DestroySpriteById(&sData->effectsScrollbarSpriteId);
    sData->activeEffectsCount = 0;
    sData->effectsCursor = 0;
    sData->effectsScroll = 0;
    Detail_BuildActiveEffectsForBattler();
    Detail_RefreshEffectsSection();
}

static void Detail_BuildActiveEffectsForBattler(void)
{
    enum BattlerId battler = GetSelectedBattler();
    enum BattleSide side = GetBattlerSide(battler);

    struct FieldTimer *fieldStatus = &gFieldTimers;
    struct SideTimer *sideStatus = &gSideTimers[side];
    struct Volatiles *vol = &gBattleMons[battler].volatiles;

    TryAddActiveWeather(GetStatusEffectFromWeather(), side);
    TryAddActiveTerrain(GetStatusEffectFromTerrain(), side);
    TryAddActiveFieldStatus(INFO_TRICK_ROOM, STATUS_FIELD_TRICK_ROOM, fieldStatus->trickRoomTimer, 5, side);
    TryAddActiveFieldStatus(INFO_MAGIC_ROOM, STATUS_FIELD_MAGIC_ROOM, fieldStatus->magicRoomTimer, 5, side);
    TryAddActiveFieldStatus(INFO_WONDER_ROOM, STATUS_FIELD_WONDER_ROOM, fieldStatus->wonderRoomTimer, 5, side);
    TryAddActiveFieldStatus(INFO_GRAVITY, STATUS_FIELD_GRAVITY, fieldStatus->gravityTimer, 5, side);
    TryAddActiveFieldStatus(INFO_MUD_SPORT, STATUS_FIELD_MUDSPORT, fieldStatus->mudSportTimer, 5, side);
    TryAddActiveFieldStatus(INFO_WATER_SPORT, STATUS_FIELD_WATERSPORT, fieldStatus->waterSportTimer, 5, side);
    TryAddActiveFieldStatus(INFO_FAIRY_LOCK, STATUS_FIELD_FAIRY_LOCK, fieldStatus->fairyLockTimer, 2, side);

    #define SIDE_STATUS(s) (gSideStatuses[side] & s) != 0
    TryAddActiveScreen(INFO_LIGHT_SCREEN, SIDE_STATUS(SIDE_STATUS_LIGHTSCREEN), sideStatus->lightscreenTimer, sideStatus->lightscreenTimerTotal, side);
    TryAddActiveScreen(INFO_REFLECT, SIDE_STATUS(SIDE_STATUS_REFLECT), sideStatus->reflectTimer, sideStatus->reflectTimerTotal, side);
    TryAddActiveScreen(INFO_AURORA_VEIL, SIDE_STATUS(SIDE_STATUS_AURORA_VEIL), sideStatus->auroraVeilTimer, sideStatus->auroraVeilTimerTotal, side);
    TryAddActiveSideStatus(INFO_MIST, SIDE_STATUS(SIDE_STATUS_MIST), sideStatus->mistTimer, 5, side);
    TryAddActiveSideStatus(INFO_SAFEGUARD, SIDE_STATUS(SIDE_STATUS_SAFEGUARD), sideStatus->safeguardTimer, 5, side);
    TryAddActiveSideStatus(INFO_LUCKY_CHANT, SIDE_STATUS(SIDE_STATUS_LUCKY_CHANT), sideStatus->luckyChantTimer, 5, side);
    TryAddActiveSideStatus(INFO_TAILWIND, SIDE_STATUS(SIDE_STATUS_TAILWIND), sideStatus->tailwindTimer, (GetConfig(B_TAILWIND_TURNS) >= GEN_5 ? 4 : 3), side);
    TryAddActiveSideStatus(INFO_RAINBOW, SIDE_STATUS(SIDE_STATUS_RAINBOW), sideStatus->rainbowTimer, 4, side);
    TryAddActiveSideStatus(INFO_SWAMP, SIDE_STATUS(SIDE_STATUS_SWAMP), sideStatus->swampTimer, 4, side);
    TryAddActiveSideStatus(INFO_SEA_OF_FIRE, SIDE_STATUS(SIDE_STATUS_SEA_OF_FIRE), sideStatus->seaOfFireTimer, 4, side);
    #undef SIDE_STATUS
    TryAddActiveSideStatus(INFO_STEALTH_ROCK, IsHazardOnSide(side, HAZARDS_STEALTH_ROCK), 0, 0, side);
    TryAddActiveSideStatus(INFO_SPIKES, IsHazardOnSide(side, HAZARDS_SPIKES), sideStatus->spikesAmount, 0, side);
    TryAddActiveSideStatus(INFO_TOXIC_SPIKES, IsHazardOnSide(side, HAZARDS_TOXIC_SPIKES), sideStatus->toxicSpikesAmount, 0, side);
    TryAddActiveSideStatus(INFO_STICKY_WEB, IsHazardOnSide(side, HAZARDS_STICKY_WEB), 0, 0, side);
    TryAddActiveSideStatus(INFO_G_MAX_STEELSURGE, IsHazardOnSide(side, HAZARDS_STEELSURGE), 0, 0, side);
    TryAddActiveDamageNonTypes(side);

    TryAddActiveStatus(GetInfoFromSemiInvulnerableState(vol->semiInvulnerable), vol->semiInvulnerable, side);
    TryAddActiveStatus(INFO_INFATUATION, vol->infatuation, side);
    TryAddActiveStatus(INFO_NIGHTMARE, vol->nightmare, side);
    TryAddActiveStatus(INFO_TORMENT, vol->torment, side);
    TryAddActiveStatus(INFO_GRUDGE, vol->grudge, side);
    TryAddActiveStatus(INFO_LOCK_ON, vol->lockOn, side);
    TryAddActiveStatus(INFO_INGRAIN, vol->root, side);
    TryAddActiveStatus(INFO_AQUA_RING, vol->aquaRing, side);
    TryAddActiveStatus(INFO_CURSE, vol->cursed, side);
    TryAddActiveStatus(INFO_DESTINY_BOND, vol->destinyBond, side);
    TryAddActiveStatus(INFO_AUTOTOMIZE, vol->autotomizeCount, side);
    TryAddActiveStatus(INFO_TAR_SHOT, vol->tarShot, side);
    TryAddActiveStatus(INFO_OCTOLOCK, vol->octolock, side);
    TryAddActiveStatus(INFO_WIDE_OPEN, vol->glaiveRush, side);
    TryAddActiveStatus(INFO_ATK_DEF_SWAPPED, vol->powerTrick, side);
    TryAddActiveStatus(INFO_SMACK_DOWN, vol->smackDown, side);
    TryAddActiveStatus(INFO_SALT_CURE, vol->saltCure, side);
    TryAddActiveStatus(INFO_TAUNT, vol->tauntTimer, side);
    TryAddActiveStatus(INFO_CHARGE, vol->chargeTimer, side);
    TryAddActiveStatus(INFO_BOUND, vol->wrapTurns, side);
    TryAddActiveStatus(INFO_RAMPAGING, vol->rampageTurns, side);
    TryAddActiveStatus(INFO_CONFUSION, vol->confusionTimer, side);
    TryAddActiveStatus(INFO_CANT_ESCAPE, vol->escapePrevention, side);
    TryAddActiveStatus(INFO_CRITICAL_HIT_BOOST, vol->criticalHitBoost, side);
    TryAddActiveStatus(INFO_IDENTIFIED, vol->foresight, side);
    TryAddActiveStatus(INFO_IDENTIFIED, vol->miracleEye, side);
    TryAddActiveStatus(INFO_NO_ABILITY, vol->gastroAcid, side);
    TryAddActiveStatus(INFO_IMPRISON, vol->imprison, side);
    TryAddActiveStatus(INFO_LEECH_SEED, vol->leechSeed, side);
    TryAddActiveStatus(INFO_MINIMIZED, vol->minimize, side);
    TryAddActiveStatus(INFO_RECHARGING, vol->rechargeTimer, side);
    TryAddActiveStatus(INFO_FLASH_FIRE, vol->flashFireBoosted, side);
    TryAddActiveStatus(INFO_CHARGING, gBattleMons[battler].volatiles.chargeTurn, side);
    TryAddActiveStatus(INFO_MICLE_BERRY, gBattleStruct->battlerState[battler].usedMicleBerry, side);
    TryAddActiveStatusTimer(INFO_DROWSY, vol->yawn, 2, side);
    TryAddActiveStatusTimer(INFO_HEALING_PREVENTED, vol->healBlockTimer, B_HEAL_BLOCK_TIMER, side);
    TryAddActiveStatusTimer(INFO_EMBARGO, vol->embargoTimer, B_EMBARGO_TIMER, side);
    TryAddActiveStatusTimer(INFO_TELEKINESIS, vol->telekinesisTimer, B_TELEKINESIS_TIMER, side);
    TryAddActiveStatusTimer(INFO_MAGNET_RISE, vol->magnetRiseTimer, B_MAGNET_RISE_TIMER, side);
    TryAddActiveStatusTimer(INFO_BIDE, vol->bideTurns, 2, side);
    TryAddActiveStatusTimer(INFO_FUTURE_ATTACK, gBattleStruct->futureSight[battler].counter, 3, side);
    TryAddActiveStatusTimer(INFO_THROAT_CHOP, vol->throatChopTimer, B_THROAT_CHOP_TIMER, side);
    TryAddActiveStatusTimer(INFO_LASER_FOCUS, vol->laserFocusTimer, B_LASER_FOCUS_TIMER, side);
    TryAddActiveStatusTimer(INFO_SLOW_START, vol->slowStartTimer, B_SLOW_START_TIMER, side);
    TryAddActiveStatusTimer(INFO_SYRUPY, vol->syrupBombTimer, B_SYRUP_BOMB_TIMER, side);
    TryAddActiveStatusTimer(INFO_WISH, gBattleStruct->wish[battler].counter, 2, side);
    TryAddActiveStatusTimer(INFO_PERISHING, vol->perishSongTimer, 3, side);
    TryAddActiveStatusTimer(INFO_STOCKPILING, vol->stockpileCounter, 3, side);

    TryAddActiveThirdType(battler, side);

    if (B_DISABLE_TURNS >= GEN_5)
        TryAddActiveStatusTimer(INFO_MOVE_DISABLED, vol->disableTimer, B_DISABLE_TIMER, side);
    else
        TryAddActiveStatus(INFO_MOVE_DISABLED, vol->disableTimer, side);

    if (B_UPROAR_TURNS >= GEN_5)
        TryAddActiveStatusTimer(INFO_UPROAR, vol->uproarTurns, B_UPROAR_TURN_COUNT - 2, side);
    else
        TryAddActiveStatus(INFO_UPROAR, vol->uproarTurns, side);

    if (B_ENCORE_TURNS >= GEN_5)
        TryAddActiveStatusTimer(INFO_ENCORE, vol->encoreTimer, B_ENCORE_TIMER, side);
    else
        TryAddActiveStatus(INFO_ENCORE, vol->encoreTimer, side);
}

static void TryAddActiveWeather(enum BattleInfoLabels label, enum BattleSide side)
{
    if (gBattleStruct->weatherDuration > 0)
    {
        struct DisplayTimer timer = {
            .baseTotal = 5,
            .extendedTotal = gBattleStruct->weatherDurationTotal,
            .remaining = gBattleStruct->weatherDuration,
        };

        if (ShouldShowIncreasedDuration(gBattleStruct->weatherSide))
        {
            TryAddActiveStatusTimer(label, timer.remaining, timer.extendedTotal, side);
        }
        else
        {
            SetRemainingDuration(&timer);
            TryAddActiveStatusTimer(label, timer.remaining, timer.baseTotal, side);
        }
    }
    else
    {
        TryAddActiveStatus(label, PERMANENT_STATUS, side);
    }
}

static void TryAddActiveTerrain(enum BattleInfoLabels status, enum BattleSide side)
{
    if (gFieldTimers.terrainTimer > 0)
    {
        struct DisplayTimer timer = {
            .baseTotal = 5,
            .extendedTotal = gFieldTimers.terrainTimerTotal,
            .remaining = gFieldTimers.terrainTimer,
        };

        if (ShouldShowIncreasedDuration(gFieldTimers.terrainSide))
        {
            TryAddActiveStatusTimer(status, timer.remaining, timer.extendedTotal, side);
        }
        else
        {
            SetRemainingDuration(&timer);
            TryAddActiveStatusTimer(status, timer.remaining, timer.baseTotal, side);
        }
    }
    else
    {
        TryAddActiveStatus(status, PERMANENT_STATUS, side);
    }
}

static void TryAddActiveScreen(enum BattleInfoLabels label, u32 sideStatus, u32 remaining, u32 extendedTotal, enum BattleSide side)
{
    if (remaining > 0)
    {
        struct DisplayTimer timer = {
            .baseTotal = 5,
            .extendedTotal = extendedTotal,
            .remaining = remaining,
        };

        if (ShouldShowIncreasedDuration(side))
        {
            TryAddActiveStatusTimer(label, timer.remaining, timer.extendedTotal, side);
        }
        else
        {
            SetRemainingDuration(&timer);
            TryAddActiveSideStatus(label, sideStatus, timer.remaining, timer.baseTotal, side);
        }
    }
    else
    {
        TryAddActiveSideStatus(label, sideStatus, PERMANENT_STATUS, 0, side);
    }
}

static bool32 ShouldShowIncreasedDuration(enum BattleSide side)
{
    if (side == B_SIDE_PLAYER)
        return TRUE;

    if (B_INFO_ALWAYS_SHOW_ACCURATE_DURATION)
        return TRUE;

    return FALSE;
}

static void SetRemainingDuration(struct DisplayTimer *timer)
{
    if (timer->extendedTotal == timer->baseTotal)
        return;

    s32 durationDifference = timer->extendedTotal - timer->baseTotal;

    if (timer->remaining == durationDifference)
        timer->baseTotal = timer->extendedTotal;
    else
        timer->remaining = timer->remaining - durationDifference;
}

static void TryAddActiveFieldStatus(enum BattleInfoLabels label, u32 fieldStatus, u32 timer, u32 totalTimer, enum BattleSide side)
{
    if ((gFieldStatuses & fieldStatus) == 0)
        return;

    if (timer > 0)
        TryAddActiveStatusTimer(label, timer, totalTimer, side);
    else
        TryAddActiveStatus(label, PERMANENT_STATUS, side);
}

static void TryAddActiveSideStatus(enum BattleInfoLabels label, u32 sideStatus, u32 timer, u32 totalTimer, enum BattleSide side)
{
    if (!sideStatus)
        return;

    if (timer > 0)
        TryAddActiveStatusTimer(label, timer, totalTimer, side);
    else
        TryAddActiveStatus(label, PERMANENT_STATUS, side);
}

static void TryAddActiveStatus(enum BattleInfoLabels label, u32 timerOrFlag, enum BattleSide side)
{
    bool32 isNotTimer = FALSE;
    TryAddActiveStatusInternal(label, timerOrFlag, 0, side, isNotTimer);
}

static void TryAddActiveStatusTimer(enum BattleInfoLabels label, u32 remaining, u32 baseTotal, enum BattleSide side)
{
    bool32 isTimer = TRUE;
    TryAddActiveStatusInternal(label, remaining, baseTotal, side, isTimer);
}

static void TryAddActiveStatusInternal(enum BattleInfoLabels label, u32 timerOrFlag, u32 baseTotal, enum BattleSide side, bool32 isTimer)
{
    if (label == INFO_NONE)
        return;

    if (timerOrFlag == 0)
        return;

    if (baseTotal == 0)
        baseTotal = timerOrFlag;

    struct BattleInfo entry = {0};

    if (isTimer)
    {
        entry.durationRemaining = timerOrFlag;
        entry.baseTotalDuration = baseTotal;
        entry.durationKnown = TRUE;
    }

    entry.label = label;
    entry.setterSide = side;

    sData->activeEffects[sData->activeEffectsCount++] = entry;
}

static bool32 Detail_SetDisplayedDuration(const struct BattleInfo *entry, enum BattleSide viewerSide, struct Durations *duration)
{
    if (!entry->durationKnown)
        return FALSE;

    u32 actualTotal = entry->baseTotalDuration;
    if (actualTotal == 0)
        return FALSE;

    u32 remaining = entry->durationRemaining;
    u32 displayedTotal = actualTotal;

    duration->remaining = remaining;
    duration->total = displayedTotal;
    return TRUE;
}

static enum BattleInfoLabels GetStatusEffectFromWeather(void)
{
    switch (GetBattleWeather(gBattleWeather))
    {
    case BATTLE_WEATHER_NONE:          return INFO_NONE;
    case BATTLE_WEATHER_RAIN:          return INFO_RAIN;
    case BATTLE_WEATHER_RAIN_DOWNPOUR: return INFO_RAIN;
    case BATTLE_WEATHER_RAIN_PRIMAL:   return INFO_HEAVY_RAIN;
    case BATTLE_WEATHER_SUN:           return INFO_HARSH_SUNLIGHT;
    case BATTLE_WEATHER_SUN_PRIMAL:    return INFO_EXTREMELY_HARSH_SUNLIGHT;
    case BATTLE_WEATHER_SANDSTORM:     return INFO_SANDSTORM;
    case BATTLE_WEATHER_HAIL:          return INFO_SNOW;
    case BATTLE_WEATHER_SNOW:          return INFO_SNOW;
    case BATTLE_WEATHER_FOG:           return INFO_FOG;
    case BATTLE_WEATHER_STRONG_WINDS:  return INFO_STRONG_WINDS;
    case BATTLE_WEATHER_COUNT:         return INFO_NONE;
    }

    return INFO_NONE;
}

static enum BattleInfoLabels GetStatusEffectFromTerrain(void)
{
    switch (gFieldTimers.terrain)
    {
    case B_TERRAIN_ELECTRIC: return INFO_ELECTRIC_TERRAIN;
    case B_TERRAIN_GRASSY:   return INFO_GRASSY_TERRAIN;
    case B_TERRAIN_MISTY:    return INFO_MISTY_TERRAIN;
    case B_TERRAIN_PSYCHIC:  return INFO_PSYCHIC_TERRAIN;
    case B_TERRAIN_NONE:     return INFO_NONE;
    case B_TERRAIN_COUNT:    return INFO_NONE;
    }

    return INFO_NONE;
}

static enum BattleInfoLabels GetInfoFromSemiInvulnerableState(u32 semiInvulnerable)
{
    switch (semiInvulnerable)
    {
    case STATE_UNDERGROUND:       return INFO_UNDERGROUND;
    case STATE_UNDERWATER:        return INFO_SUBMERGED;
    case STATE_ON_AIR:            return INFO_SKY_HIGH;
    case STATE_PHANTOM_FORCE:     return INFO_CONCEALED;
    case STATE_SKY_DROP_ATTACKER: return INFO_SKY_HIGH;
    case STATE_SKY_DROP_TARGET:   return INFO_SKY_HIGH;
    }

    return INFO_NONE;
}

static void TryAddActiveDamageNonTypes(enum BattleSide side)
{
    if (!(gSideStatuses[side] & SIDE_STATUS_DAMAGE_NON_TYPES))
        return;

    switch (gSideTimers[side].damageNonTypesType)
    {
    case TYPE_FIRE:
        TryAddActiveStatus(INFO_G_MAX_WILDFIRE, PERMANENT_STATUS, side);
        break;
    case TYPE_ROCK:
        TryAddActiveStatus(INFO_G_MAX_VOLCALITH, PERMANENT_STATUS, side);
        break;
    case TYPE_GRASS:
        TryAddActiveStatus(INFO_G_MAX_VINE_LASH, PERMANENT_STATUS, side);
        break;
    case TYPE_WATER:
        TryAddActiveStatus(INFO_G_MAX_CANNONADE, PERMANENT_STATUS, side);
        break;
    default:
        break;
    }
}

static void TryAddActiveThirdType(enum BattlerId battler, enum BattleSide side)
{
    enum Type types[3];
    GetBattlerTypes(battler, FALSE, types);
    switch (types[2])
    {
    case TYPE_GHOST:
        TryAddActiveStatus(INFO_TRICK_OR_TREAT, TRUE, side);
        break;
    case TYPE_GRASS:
        TryAddActiveStatus(INFO_FORESTS_CURSE, TRUE, side);
        break;
    default:
        break;
    }
}

static void Detail_BuildTurnFractionText(u8 *dst, u32 remaining, u32 total)
{
    u8 *str = dst;

    str = ConvertIntToDecimalStringN(str, remaining, STR_CONV_MODE_LEFT_ALIGN, 2);
    *(str++) = CHAR_SLASH;
    str = ConvertIntToDecimalStringN(str, total, STR_CONV_MODE_LEFT_ALIGN, 2);
    *str = EOS;
}

static bool32 Detail_TryMoveEffectCursor(s32 direction)
{
    if (sData->activeEffectsCount == 0)
        return FALSE;

    if (direction < 0)
    {
        if (sData->effectsCursor == 0)
            return FALSE;
        sData->effectsCursor--;
    }
    else if (direction > 0)
    {
        if (sData->effectsCursor + 1 >= sData->activeEffectsCount)
            return FALSE;
        sData->effectsCursor++;
    }
    else
    {
        return FALSE;
    }

    if (sData->effectsCursor < sData->effectsScroll)
        sData->effectsScroll = sData->effectsCursor;
    else if (sData->effectsCursor >= sData->effectsScroll + B_INFO_DETAIL_EFFECTS_VISIBLE_ROWS)
        sData->effectsScroll = sData->effectsCursor - B_INFO_DETAIL_EFFECTS_VISIBLE_ROWS + 1;

    return TRUE;
}

static void Detail_CopyTextToFit(u8 *dst, const u8 *src, u32 fontId, u32 maxWidth)
{
    const u8 *in = src;
    u8 *out = dst;

    if (maxWidth == 0)
    {
        dst[0] = EOS;
        return;
    }

    while (*in != EOS)
    {
        *out = *in;
        out[1] = EOS;
        if (GetStringWidth(fontId, dst, 0) > maxWidth)
        {
            *out = EOS;
            break;
        }
        out++;
        in++;
    }
    *out = EOS;
}

static void Detail_DisplayRow(u32 windowId, u32 row, u32 index, u32 fractionYOffset)
{
    u32 top = 16 + row * 12;
    const struct BattleInfo *entry = &sData->activeEffects[index];
    const struct BattleInfoEffectData *effectData = &sBattleInfoEffects[entry->label];

    assertf(effectData->name != NULL, "missing info label name/description for %d", entry->label)
    {
        return;
    }

    struct PrintText text = {
        .windowId = windowId,
        .color = sTextColor_BattleInfo_Default,
        .speed = TEXT_SKIP_DRAW,
    };

    if (index == sData->effectsCursor)
    {
        text.font = FONT_SMALL_NARROWER;
        text.left = 2;
        text.top = top;
        text.string = gText_SelectorArrow2;
        PrintTextOnWindow(&text);
    }

    struct Durations duration = {0};
    bool32 isDuration = Detail_SetDisplayedDuration(entry, B_SIDE_PLAYER, &duration);

    if (isDuration || entry->stackCount > 0)
    {
        u8 durationString[24];
        u8 nameBuffer[64];

        u8 *str = durationString;

        switch (entry->label)
        {
        case INFO_PERISHING:
            str = ConvertIntToDecimalStringN(str, duration.remaining, STR_CONV_MODE_LEFT_ALIGN, 1);
            StringCopy(str, COMPOUND_STRING("回合"));
            break;
        case INFO_STOCKPILING:
        case INFO_TOXIC_SPIKES:
        case INFO_SPIKES:
            *(str++) = CHAR_PLUS;
            str = ConvertIntToDecimalStringN(str, duration.remaining, STR_CONV_MODE_LEFT_ALIGN, 1);
            *str = EOS;
            break;
        default:
            if (isDuration)
            {
                Detail_BuildTurnFractionText(durationString, duration.remaining, duration.total);
            }
            else if (entry->stackCount > 0)
            {
                *(str++) = CHAR_PLUS;
                str = ConvertIntToDecimalStringN(str, entry->stackCount, STR_CONV_MODE_LEFT_ALIGN, 1);
                *str = EOS;
            }
            break;
        }

        s32 windowWidth = WindowWidthPx(windowId);
        s32 durationWidth = GetStringWidth(FONT_SMALL_NARROWER, durationString, 0);

        s32 durationX = windowWidth - 6 - 2 - durationWidth;
        durationX = max(durationX, 10);

        s32 maxNameWidth = durationX - 10 - 2;
        maxNameWidth = max(maxNameWidth, 0);

        Detail_CopyTextToFit(nameBuffer, effectData->name, FONT_SHORT_NARROWER, maxNameWidth);

        text.font = FONT_SHORT_NARROWER;
        text.left = 10;
        text.top = top;
        text.string = nameBuffer;
        PrintTextOnWindow(&text);

        text.font = FONT_SMALL_NARROWER;
        text.left = durationX;
        text.top = top + fractionYOffset;
        text.string = durationString;
        PrintTextOnWindow(&text);
    }
    else
    {
        text.font = FONT_SHORT_NARROWER;
        text.left = 10;
        text.top = top;
        text.string = effectData->name;
        PrintTextOnWindow(&text);
    }
}

static void Detail_RefreshEffectsWindow(void)
{
    u32 windowId = sData->windowIds[WIN_DETAIL_EFFECTS];
    u32 fractionYOffset = 0;

    if (GetFontAttribute(FONT_SMALL_NARROWER, FONTATTR_MAX_LETTER_HEIGHT) < 12)
        fractionYOffset = (12 - GetFontAttribute(FONT_SMALL_NARROWER, FONTATTR_MAX_LETTER_HEIGHT)) / 2;

    Detail_ResetWithTransparentTextColor(windowId);
    AddTextPrinterParameterized4(
            windowId,
            FONT_NARROWER,
            2, 2, 0, 0,
            sTextColor_BattleInfo_Default,
            TEXT_SKIP_DRAW,
            COMPOUND_STRING("状态变化与效果")
        );

    if (sData->activeEffectsCount != 0)
    {
        for (u32 row = 0; row < B_INFO_DETAIL_EFFECTS_VISIBLE_ROWS; row++)
        {
            u32 rowIndex = sData->effectsScroll + row;

            if (rowIndex >= sData->activeEffectsCount)
                break;

            Detail_DisplayRow(windowId, row, rowIndex, fractionYOffset);
        }
    }

    PutWindowTilemap(windowId);
    CopyWindowToVram(windowId, COPYWIN_FULL);
    Detail_RefreshEffectsScrollbar();
    DestroySpriteById(&sData->cursorSpriteId);
}

static void Detail_RefreshEffectsScrollbar(void)
{
    if (sData->activeEffectsCount <= B_INFO_DETAIL_EFFECTS_VISIBLE_ROWS)
    {
        Detail_UpdateScrollbarLane(FALSE);
        DestroySpriteById(&sData->effectsScrollbarSpriteId);
        return;
    }

    Detail_UpdateScrollbarLane(TRUE);

    u32 windowId = sData->windowIds[WIN_DETAIL_EFFECTS];
    u32 windowLeftPx = GetWindowAttribute(windowId, WINDOW_TILEMAP_LEFT) * 8;
    u32 windowTopPx = GetWindowAttribute(windowId, WINDOW_TILEMAP_TOP) * 8;
    u32 scrollbarX = windowLeftPx + WindowWidthPx(windowId) - 6;
    u32 scrollbarMinY = windowTopPx + 16 + 7;
    u32 scrollbarMaxY = scrollbarMinY + 3 + (B_INFO_DETAIL_EFFECTS_VISIBLE_ROWS - 1) * 12;
    u32 maxScroll = sData->activeEffectsCount - B_INFO_DETAIL_EFFECTS_VISIBLE_ROWS;

    if (sData->effectsScroll > maxScroll)
        sData->effectsScroll = maxScroll;

    u32 spriteId;
    if (sData->effectsScrollbarSpriteId == SPRITE_NONE)
    {
        spriteId = CreateSprite(&sSpriteTemplate_BattleInfoDetailEffectsScrollbar, scrollbarX, scrollbarMinY, 0);
        if (spriteId == SPRITE_NONE)
            return;
        sData->effectsScrollbarSpriteId = spriteId;
        gSprites[spriteId].oam.priority = 0;
    }

    spriteId = sData->effectsScrollbarSpriteId;
    gSprites[spriteId].x = scrollbarX;
    gSprites[spriteId].y = scrollbarMinY + (sData->effectsScroll * (scrollbarMaxY - scrollbarMinY) + (maxScroll / 2)) / maxScroll;
    gSprites[spriteId].invisible = FALSE;
}

static void SetBg1Tilemap(u32 bottomTileY, u32 laneX, u32 scrollbarTile, bool32 hasScrollbar)
{
    u32 index = bottomTileY * B_INFO_TILEMAP_WIDTH + laneX;

    if (hasScrollbar)
        sData->bg1Tilemap[index] = (sData->bg1Tilemap[index] & 0xFC00) | scrollbarTile;
    else
        sData->bg1Tilemap[index] = sBattleInfoMenuDetailsBaseTilemap[index];
}

static void Detail_UpdateScrollbarLane(bool32 hasScrollbar)
{
    u32 windowId = sData->windowIds[WIN_DETAIL_EFFECTS];
    s32 laneX = GetWindowAttribute(windowId, WINDOW_TILEMAP_LEFT) + (WindowWidthPx(windowId) - 6) / 8;

    if (laneX < 0 || laneX >= B_INFO_TILEMAP_WIDTH)
        return;

    s32 laneYStart = (GetWindowAttribute(windowId, WINDOW_TILEMAP_TOP) + (16 / 8)) + 1;
    s32 laneTileCount = (((B_INFO_DETAIL_EFFECTS_VISIBLE_ROWS * 12) + 7) / 8) + 1;

    if (laneTileCount <= 0)
        return;

    for (u32 i = 0; i < laneTileCount; i++)
    {
        s32 tileY = laneYStart + i;

        if (tileY < 0 || tileY >= B_INFO_TILEMAP_HEIGHT)
            continue;

        SetBg1Tilemap(tileY, laneX, B_INFO_BG_TILE_SCROLLBAR_BOTTOM, hasScrollbar);
    }

    if (laneTileCount > 0)
    {
        s32 topTileY = laneYStart - 1;
        s32 bottomTileY = laneYStart + laneTileCount;

        if (topTileY >= 0 && topTileY < B_INFO_TILEMAP_HEIGHT)
            SetBg1Tilemap(topTileY, laneX, B_INFO_BG_TILE_SCROLLBAR_BOTTOM, hasScrollbar);

        if (bottomTileY >= 0 && bottomTileY < B_INFO_TILEMAP_HEIGHT)
            SetBg1Tilemap(bottomTileY, laneX, B_INFO_BG_TILE_SCROLLBAR_BOTTOM, hasScrollbar);
    }

    CopyBgTilemapBufferToVram(B_INFO_BACKDROP_BG);
}

static void Detail_SetDescriptionPlaceholder(enum BattleInfoLabels label)
{
    gStringVar1[0] = EOS;
    switch (label)
    {
    case INFO_ENCORE:
        StringCopy(gStringVar1, COMPOUND_STRING("上次使用的招式"));
        break;
    case INFO_MOVE_DISABLED:
        StringCopy(gStringVar1, COMPOUND_STRING("一个招式"));
        break;
    case INFO_G_MAX_WILDFIRE:
        StringCopy(gStringVar1, COMPOUND_STRING("火"));
        break;
    case INFO_G_MAX_VOLCALITH:
        StringCopy(gStringVar1, COMPOUND_STRING("岩石"));
        break;
    case INFO_G_MAX_VINE_LASH:
        StringCopy(gStringVar1, COMPOUND_STRING("草"));
        break;
    case INFO_G_MAX_CANNONADE:
        StringCopy(gStringVar1, COMPOUND_STRING("水"));
        break;
    default:
        StringCopy(gStringVar1, COMPOUND_STRING(""));
        break;
    }
}

static void Detail_ClampTextLines(u8 *text, u32 maxLines)
{
    u32 line = 1;

    while (*text != EOS)
    {
        if (*text == CHAR_NEWLINE)
        {
            line++;
            if (line > maxLines)
            {
                *text = EOS;
                return;
            }
        }
        text++;
    }
}

static void Detail_RefreshDescriptionWindow(void)
{
    u32 windowId = sData->windowIds[WIN_DETAIL_DESCRIPTION];
    u32 descFont = FONT_SMALL_NARROWER;

    u8 descriptionBuffer[512] = {0};
    enum BattleInfoLabels label = sData->activeEffects[sData->effectsCursor].label;
    const u8 *desc = sBattleInfoEffects[label].description;

    Detail_ResetWithTransparentTextColor(windowId);

    if (sData->activeEffectsCount == 0 || desc == NULL)
    {
        descriptionBuffer[0] = EOS;
    }
    else
    {
        Detail_SetDescriptionPlaceholder(label);
        StringExpandPlaceholders(descriptionBuffer, desc);
    }

    u32 wrapWidth = WindowWidthPx(windowId) - (2 * 2) - 2;
    wrapWidth = max(wrapWidth, 8);

    u32 windowHeightPx = GetWindowAttribute(windowId, WINDOW_HEIGHT) * 8;
    u32 availableHeight = (windowHeightPx > 2 + 1) ? windowHeightPx - 2 - 1 : 1;

    u32 lineHeight = GetFontAttribute(descFont, FONTATTR_MAX_LETTER_HEIGHT) + GetFontAttribute(descFont, FONTATTR_LINE_SPACING);
    lineHeight = max(lineHeight, 1);

    u32 maxLines = availableHeight / lineHeight;
    maxLines = max(maxLines, 1);

    BreakStringAutomatic(descriptionBuffer, wrapWidth, maxLines, descFont, HIDE_SCROLL_PROMPT);

    u8 *end = descriptionBuffer + StringLength(descriptionBuffer);
    WrapFontIdToFit(descriptionBuffer, end, descFont, wrapWidth);
    Detail_ClampTextLines(descriptionBuffer, maxLines);

    if (descriptionBuffer[0] != EOS)
    {
        AddTextPrinterParameterized4(windowId, descFont, 2, 2, 0, 0,
                                     sTextColor_BattleInfo_Default, TEXT_SKIP_DRAW, descriptionBuffer);
    }

    PutWindowTilemap(windowId);
    CopyWindowToVram(windowId, COPYWIN_FULL);
}

static void Detail_RefreshEffectsSection(void)
{
    Detail_RefreshEffectsWindow();
    Detail_RefreshDescriptionWindow();
}

static void Detail_DestroyIconSprite(void)
{
    if (sData->iconSpriteId == SPRITE_NONE)
        return;
    FreeAndDestroyMonIconSprite(&gSprites[sData->iconSpriteId]);
    sData->iconSpriteId = SPRITE_NONE;
}

static void Detail_ResetWithTransparentTextColor(u32 windowId)
{
    FillWindowPixelBuffer(windowId, PIXEL_FILL(B_INFO_TEXT_COLOR_TRANSPARENT));
}

static void Overview_ComputeRowLayout(u8 *outXs)
{
    u32 screenWidthTiles = DISPLAY_WIDTH / 8;
    u32 count = GetCardCount() / 2;
    u32 totalWidthTiles = count * B_INFO_CARD_TILE_W + (count - 1);

    s32 startXTile = (screenWidthTiles - totalWidthTiles) / 2;
    startXTile = max(startXTile, B_INFO_SAFE_LEFT_TILE);
    if (startXTile + totalWidthTiles - 1 > B_INFO_SAFE_RIGHT_TILE)
        startXTile = B_INFO_SAFE_RIGHT_TILE - totalWidthTiles + 1;
    startXTile = max(startXTile, B_INFO_SAFE_LEFT_TILE);

    for (u32 i = 0; i < count; i++)
        outXs[i] = (startXTile + i * B_INFO_CARD_TILE_W) * 8;
}

static void Overview_InitCardValues(void)
{
    u32 sideSlots = GetCardCount() / 2;
    u8 rowXs[MAX_BATTLERS_COUNT];
    Overview_ComputeRowLayout(rowXs);

    for (u32 i = 0; i < GetCardCount(); i++)
    {
        u32 battler = GetBattlerFromSlot(i);
        struct BattleInfoCard *card = &sData->cards[i];
        card->x = rowXs[i < sideSlots ? i : i - sideSlots];
        card->battler = battler;
        card->y = IsOnPlayerSide(battler) ? B_INFO_ROW_Y_PLAYER : B_INFO_ROW_Y_ENEMY;
    }
}

static void Overview_DrawCards(void)
{
    for (u32 i = 0; i < GetCardCount(); i++)
    {
        if (!CanViewCard(GetBattlerFromSlot(i)))
            continue;

        Overview_DrawCard(&sData->cards[i]);
    }
}

static void Overview_DrawCard(struct BattleInfoCard *card)
{
    s32 contentYOffset = (card->y == B_INFO_ROW_Y_ENEMY) ? -2 : 0;
    struct Pokemon *mon = GetBattlerMon(card->battler);
    enum Species species = GetMonData(mon, MON_DATA_SPECIES);

    Overview_PrintMonAndGender(card, mon, species, contentYOffset);
    CreateGimmickIndicator(card, card->y + 28 + contentYOffset);
    CreateMonAndStatusIcon(card, species, GetMonData(mon, MON_DATA_PERSONALITY), contentYOffset);
    CreateHpBar(card, contentYOffset);
}

static void Overview_PrintMonAndGender(struct BattleInfoCard *card, struct Pokemon *mon, enum Species species, u32 contentYOffset)
{
    u32 windowId = (card->y == B_INFO_ROW_Y_ENEMY) ? WIN_ROW_ENEMY : WIN_ROW_PLAYER;
    u32 gender = GetMonGender(mon);
    bool32 hasGender = gender == MON_MALE || gender == MON_FEMALE;
    u32 localX = card->x;
    u32 localY = card->y;

    u32 row = (windowId == WIN_ROW_ENEMY) ? B_INFO_ROW_Y_ENEMY : B_INFO_ROW_Y_PLAYER;
    localY -= (row / 8) * 8;

    u32 maxNameWidth = B_INFO_CARD_W - 6;
    maxNameWidth -= hasGender ? B_INFO_GENDER_W + 4 : 0;

    u8 name[POKEMON_NAME_LENGTH + 1];
    GetMonData(mon, MON_DATA_NICKNAME, name);

    FillWindowPixelRect(windowId, PIXEL_FILL(B_INFO_TEXT_COLOR_TRANSPARENT), localX, localY, B_INFO_CARD_W, B_INFO_CARD_H);

    struct PrintText text = {
        .windowId = windowId,
        .speed = TEXT_SKIP_DRAW,
    };

    text.font = GetFontIdToFit(name, FONT_NORMAL, 0, maxNameWidth);
    text.top = localY + 2 + contentYOffset;
    text.left = localX + 6;
    text.color = sTextColor_BattleInfo_OverviewDefault;
    text.string = name;
    PrintTextOnWindow(&text);

    if (hasGender)
    {
        u8 genderSymbol[2];
        genderSymbol[0] = (gender == MON_MALE) ? CHAR_MALE : CHAR_FEMALE;
        genderSymbol[1] = EOS;

        text.font = FONT_SMALL;
        text.top = localY + 2 + contentYOffset;
        text.left = localX + B_INFO_CARD_W - B_INFO_GENDER_W - 2;
        text.color = (gender == MON_MALE) ? sTextColor_BattleInfo_Male : sTextColor_BattleInfo_Female;
        text.string = genderSymbol;
        PrintTextOnWindow(&text);
    }

    PutWindowTilemap(windowId);
    CopyWindowToVram(windowId, COPYWIN_FULL);
}

static void CreateGimmickIndicator(struct BattleInfoCard *card, u32 iconCenterY)
{
    u32 gimmickIndicatorPalTag;
    const u8 *gimmickIndicatorData = GetGimmickIndicatorData(card->battler, &gimmickIndicatorPalTag);

    if (gimmickIndicatorData == NULL || gimmickIndicatorPalTag == TAG_NONE)
        return;

    card->gimmickSpriteId = SPRITE_NONE;
    u32 gimmickTileTag = B_INFO_OVERVIEW_GIMMICK_TILE_TAG_BASE + card->battler;

    struct SpriteTemplate gimmickTemplate;
    gimmickTemplate = sSpriteTemplate_BattleInfoDetailGimmick;
    gimmickTemplate.tileTag = gimmickTileTag;
    gimmickTemplate.paletteTag = gimmickIndicatorPalTag;

    struct SpriteSheet gimmickSheet;
    gimmickSheet.data = gimmickIndicatorData;
    gimmickSheet.size = B_INFO_DETAIL_GIMMICK_GFX_SIZE;
    gimmickSheet.tag = gimmickTileTag;
    LoadSpriteSheet(&gimmickSheet);

    u32 x = card->x + (B_INFO_DETAIL_GIMMICK_W / 2) + 5;
    u32 y = iconCenterY - (B_INFO_DETAIL_GIMMICK_H / 2) - 3;
    card->gimmickSpriteId = CreateSprite(&gimmickTemplate, x, y, 0);

    if (card->gimmickSpriteId != SPRITE_NONE)
        gSprites[card->gimmickSpriteId].oam.priority = 0;
}

static void CreateMonAndStatusIcon(struct BattleInfoCard *card, enum Species species, u32 personality, u32 contentYOffset)
{
    u32 iconCenterX = card->x + (B_INFO_CARD_W / 2);
    u32 iconCenterY = card->y + 28 + contentYOffset;

    card->monIconSpriteId = CreateMonIcon(species, SpriteCallbackDummy, iconCenterX, iconCenterY, 0, personality);
    gSprites[card->monIconSpriteId].oam.priority = 0;

    u32 ailment = GetAilmentFromBattler(card->battler);
    if (ailment != AILMENT_NONE && ailment != AILMENT_PKRS)
    {
        u32 statusX = iconCenterX + 13;
        u32 statusY = iconCenterY + 14;

        card->statusSpriteId = CreateSprite(&gSpriteTemplate_StatusIcons, statusX, statusY, 0);
        StartSpriteAnim(&gSprites[card->statusSpriteId], ailment - 1);
        gSprites[card->statusSpriteId].oam.priority = 0;
    }
}

static void CreateHpBar(struct BattleInfoCard *card, u32 contentYOffset)
{
    card->hpBarSpriteId = CreateHpBarSprite(B_INFO_HP_BAR_TILE_TAG_BASE + card->battler, card->x - 16, card->y + 46 + contentYOffset);
    CreateHpBarEndcaps(&card->hpBarLeftEndcapSpriteId, &card->hpBarRightEndcapSpriteId);
    DrawHpBarSprite(card);
}

static void Overview_SetBgTile(s32 x, u32 y, u32 tileNum, u32 attrs)
{
    sData->bg1Tilemap[y * B_INFO_TILEMAP_WIDTH + x] = tileNum | attrs;
}

static void LoadBackdropAssets(void)
{
    LoadBgTiles(B_INFO_BACKDROP_BG, sBattleInfoMenuBgTiles, sizeof(sBattleInfoMenuBgTiles), 0);
    LoadPalette(sBattleInfoMenuBgPalette, BG_PLTT_ID(0), sizeof(sBattleInfoMenuBgPalette));
}

static void BackdropLoadBaseTilemap(void)
{
    u32 mode = B_INFO_TILEMAP_WIDTH * B_INFO_TILEMAP_HEIGHT * sizeof(u16);
    CpuCopy16(sBattleInfoMenuDetailsBaseTilemap, sData->bg1Tilemap, mode);
    CopyBgTilemapBufferToVram(B_INFO_BACKDROP_BG);
}

static u32 GetCenterRow(void)
{
    u32 screenWidthTiles = DISPLAY_WIDTH / 8;
    u32 totalWidthTiles = B_INFO_NUM_SINGLE_BATTLE_MONS * B_INFO_CARD_TILE_W;

    s32 startXTile = (screenWidthTiles - totalWidthTiles) / 2;
    startXTile = max(startXTile, B_INFO_SAFE_LEFT_TILE);

    if (startXTile + totalWidthTiles - 1 > B_INFO_SAFE_RIGHT_TILE)
        startXTile = B_INFO_SAFE_RIGHT_TILE - totalWidthTiles + 1;
    startXTile = max(startXTile, B_INFO_SAFE_LEFT_TILE);

    u8 outXs[B_INFO_NUM_SINGLE_BATTLE_MONS];
    for (u32 i = 0; i < B_INFO_NUM_SINGLE_BATTLE_MONS; i++)
        outXs[i] = (startXTile + i * B_INFO_CARD_TILE_W) * 8;

    u32 outRowLeft = outXs[0];
    u32 outRowRight = outXs[B_INFO_NUM_SINGLE_BATTLE_MONS - 1] + B_INFO_CARD_W;

    return (outRowLeft + outRowRight) / 2;
}

static u32 GetSideCenterRow(enum BattleSide side)
{
    s32 minX = -1;
    s32 maxX = -1;

    for (u32 i = 0; i < GetCardCount(); i++)
    {
        struct BattleInfoCard *card = &sData->cards[i];
        if (GetBattlerSide(card->battler) != side)
            continue;

        if (minX < 0 || card->x < minX)
            minX = card->x;
        if ((card->x + B_INFO_CARD_W) > maxX)
            maxX = card->x + B_INFO_CARD_W;
    }

    if (minX < 0)
        return GetCenterRow();

    return (minX + maxX) / 2;
}

static void Overview_ComputeTrainerNameBoxLayout(u32 labelWidth, u32 centerRow, u32 *outTextLenTiles, u32 *outHeaderX, u32 *outHeaderWidth)
{
    u32 textLenTiles = MakeEven(max(PixelsToTiles(labelWidth), 1));

    s32 headerWidth = textLenTiles + 2;
    s32 headerX = (centerRow - ((headerWidth * 8) / 2)) / 8;
    headerX = max(headerX, B_INFO_SAFE_LEFT_TILE);
    if (headerX + headerWidth - 1 > B_INFO_SAFE_RIGHT_TILE)
        headerX = B_INFO_SAFE_RIGHT_TILE - headerWidth + 1;

    if (outTextLenTiles != NULL)
        *outTextLenTiles = textLenTiles;
    *outHeaderX = headerX;
    *outHeaderWidth = headerWidth;
}

static u32 GetCardTile(bool32 isActive, u32 role)
{
    if (isActive)
        return B_INFO_BG_TILE_CARD_BASE_ACTIVE + role;
    return B_INFO_BG_TILE_CARD_BASE_INACTIVE + role;
}

static void Overview_DrawStatusCard(u32 x, u32 y, bool32 isActive, bool32 isBottomRow)
{
    u32 topLeftTile    = GetCardTile(isActive, B_INFO_CARD_ROLE_TOP_LEFT);
    u32 topEdgeTile    = GetCardTile(isActive, B_INFO_CARD_ROLE_TOP_EDGE);
    u32 sideEdgeTile   = GetCardTile(isActive, B_INFO_CARD_ROLE_SIDE_EDGE);
    u32 fillTile       = GetCardTile(isActive, B_INFO_CARD_ROLE_INTERIOR);
    u32 bottomLeftTile = GetCardTile(isActive, B_INFO_CARD_ROLE_BOTTOM_LEFT);
    u32 bottomEdgeTile = GetCardTile(isActive, B_INFO_CARD_ROLE_BOTTOM_EDGE);

    u32 width = B_INFO_CARD_TILE_W;
    u32 height = B_INFO_CARD_TILE_H;
    u32 topAttrs = 0;
    u32 bottomAttrs = 0;

    if (isBottomRow)
    {
        u32 tmp;
        SWAP(topLeftTile, bottomLeftTile, tmp);
        SWAP(topEdgeTile, bottomEdgeTile, tmp);
        topAttrs = B_INFO_BG_ATTR_VFLIP;
        bottomAttrs = B_INFO_BG_ATTR_VFLIP;
    }

    Overview_DrawHeaderBoxRow(topLeftTile, topEdgeTile, topAttrs, x, y, width);
    for (u32 yi = y + 1; yi < y + height - 1; yi++)
        Overview_DrawHeaderBoxRow(sideEdgeTile, fillTile, 0, x, yi, width);
    Overview_DrawHeaderBoxRow(bottomLeftTile, bottomEdgeTile, bottomAttrs, x, y + height - 1, width);
}

static void Overview_DrawHeaderBoxWidth(s32 x, u32 y, u32 width)
{
    if (max(0, x) + width > B_INFO_TILEMAP_WIDTH)
        x = B_INFO_TILEMAP_WIDTH - width;

    Overview_DrawHeaderBoxRow(B_INFO_BG_TILE_HEADER_CORNER, B_INFO_BG_TILE_HEADER_TOP, 0, x, y, width);
    Overview_DrawHeaderBoxRow(B_INFO_BG_TILE_HEADER_SIDE, B_INFO_BG_TILE_HEADER_FILL, 0, x, y + 1, width);
    Overview_DrawHeaderBoxRow(B_INFO_BG_TILE_HEADER_CORNER, B_INFO_BG_TILE_HEADER_TOP, B_INFO_BG_ATTR_VFLIP, x, y + 2, width);
}

static void Overview_DrawHeaderBoxRow(u32 cornerTile, u32 fillTile, u32 baseAttrs, s32 x, u32 y, u32 width)
{
    Overview_SetBgTile(x, y, cornerTile, baseAttrs);
    Overview_SetBgTile(x + width - 1, y, cornerTile, baseAttrs | B_INFO_BG_ATTR_HFLIP);
    for (u32 xi = x + 1; xi < x + width - 1; xi++)
        Overview_SetBgTile(xi, y, fillTile, baseAttrs);
}

static void Overview_DrawCardBackground(const struct BattleInfoCard *card, bool32 isActive)
{
    u32 cardTileX = card->x / 8;
    u32 cardTileY = card->y / 8;
    Overview_FillBgRect(
        cardTileX,
        cardTileY,
        B_INFO_CARD_TILE_W,
        B_INFO_CARD_TILE_H,
        B_INFO_BG_TILE_FILL,
        0
    );
    Overview_DrawStatusCard(cardTileX, cardTileY, isActive, card->y == B_INFO_ROW_Y_PLAYER);
}

static void Overview_DrawBackground(void)
{
    CpuCopy16(sBattleInfoMenuOverviewBaseTilemap, sData->bg1Tilemap,
              B_INFO_TILEMAP_WIDTH * B_INFO_TILEMAP_HEIGHT * sizeof(u16));

    struct TileCoords {
        u32 top;
        u32 height;
    } tileCoords[] = {
        { B_INFO_ROW_Y_ENEMY / 8, B_INFO_CARD_TILE_H },
        { B_INFO_ROW_Y_PLAYER / 8, B_INFO_CARD_TILE_H },
        { 0, B_INFO_LABEL_TILE_H },
        { B_INFO_LABEL_BOTTOM_TILE_TOP, B_INFO_LABEL_TILE_H },
    };

    for (u32 i = 0; i < ARRAY_COUNT(tileCoords); i++)
    {
        Overview_FillBgRect(
            B_INFO_SAFE_LEFT_TILE,
            tileCoords[i].top,
            B_INFO_SAFE_RIGHT_TILE - B_INFO_SAFE_LEFT_TILE + 1,
            tileCoords[i].height,
            B_INFO_BG_TILE_FILL, 0
        );
    }

    for (u32 i = 0; i < GetCardCount(); i++)
        Overview_DrawCardBackground(&sData->cards[i], i == sData->selectedCard);

    Overview_DrawNameBoxes();
    CopyBgTilemapBufferToVram(B_INFO_BACKDROP_BG);
}

static void Overview_DrawTrainerNameBox(enum BattleSide side)
{
    u32 labelWidth = GetStringWidth(FONT_SMALL, GetSideTrainerName(side), 0);
    u32 top = (side == B_SIDE_PLAYER) ? B_INFO_LABEL_BOTTOM_TILE_TOP : 0;
    Overview_DrawTrainerNameBoxHelper(labelWidth, top, GetSideCenterRow(side));
}

static const u8 *GetTrainerNameForBattler(enum BattlerId battler)
{
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        return gLinkPlayers[GetBattlerMultiplayerId(battler)].name;
    }

    if (IsOnPlayerSide(battler))
    {
        if (GetBattlerPosition(battler) == B_POSITION_PLAYER_RIGHT && (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER))
        {
            static u8 trainerName[TRAINER_NAME_LENGTH + 1];
            GetFrontierTrainerName(trainerName, gPartnerTrainerId);
            return trainerName;
        }

        return gSaveBlock2Ptr->playerName;
    }

    u32 trainerId = (GetBattlerPosition(battler) == B_POSITION_OPPONENT_RIGHT && GetOpponentTrainerCount() >= 2)
                   ? TRAINER_BATTLE_PARAM.opponentB
                   : TRAINER_BATTLE_PARAM.opponentA;

    return GetTrainerNameFromId(trainerId);
}

static void Overview_DrawMultiTrainerNameBoxes(enum BattleSide side)
{
    for (u32 i = 0; i < GetCardCount(); i++)
    {
        struct BattleInfoCard *card = &sData->cards[i];
        if (GetBattlerSide(card->battler) != side)
            continue;
        const u8 *label = GetTrainerNameForBattler(card->battler);
        u32 top = (side == B_SIDE_PLAYER) ? B_INFO_LABEL_BOTTOM_TILE_TOP : 0;
        Overview_DrawHeaderBoxAtCard(card, top, label);
    }
}

static void Overview_ComputeHeaderBoxAtCard(const struct BattleInfoCard *card, const u8 *label, u32 *outHeaderX, u32 *outWidth)
{
    u32 labelWidth = GetStringWidth(FONT_SMALL, label, 0);
    u32 textLenTiles = MakeEven(max(PixelsToTiles(labelWidth), 1));

    s32 minTile = card->x / 8;
    s32 maxTile = minTile + B_INFO_CARD_TILE_W - 1;
    u32 boxWidth = min(B_INFO_TILEMAP_WIDTH, textLenTiles + 2);
    if (boxWidth > (u32)(maxTile - minTile + 1))
        boxWidth = maxTile - minTile + 1;

    s32 boxCenterPx = card->x + B_INFO_CARD_W / 2;
    s32 boxLeftPx = boxCenterPx - ((s32)boxWidth * 8) / 2;
    s32 headerX = boxLeftPx / 8;
    headerX = max(headerX, minTile);
    if (headerX + (s32)boxWidth - 1 > maxTile)
        headerX = maxTile - boxWidth + 1;
    headerX = max(headerX, minTile);

    *outHeaderX = headerX;
    *outWidth = boxWidth;
}

static void Overview_DrawHeaderBoxAtCard(const struct BattleInfoCard *card, u32 top, const u8 *label)
{
    u32 headerX = 0;
    u32 boxWidth = 0;
    Overview_ComputeHeaderBoxAtCard(card, label, &headerX, &boxWidth);
    Overview_DrawHeaderBoxWidth(headerX, top, boxWidth);
}

static void Overview_DrawTrainerNameBoxHelper(u32 labelWidth, u32 top, u32 centerRow)
{
    u32 textLenTiles = 0;
    u32 headerX = 0;
    u32 headerWidth = 0;

    Overview_ComputeTrainerNameBoxLayout(labelWidth, centerRow, &textLenTiles, &headerX, &headerWidth);
    Overview_DrawHeaderBoxWidth(headerX, top, min(B_INFO_TILEMAP_WIDTH, MakeEven(textLenTiles) + 2));
}

static void Overview_FillBgRect(u32 x, u32 y, u32 width, u32 height, u32 tileNum, u32 attrs)
{
    for (u32 yi = y; yi < y + height; yi++)
    {
        for (u32 xi = x; xi < x + width; xi++)
            Overview_SetBgTile(xi, yi, tileNum, attrs);
    }
}

static bool32 ShouldShowTrainerNames(void)
{
    switch (B_INFO_SHOW_TRAINER_NAMES)
    {
    case B_INFO_SHOW_TRAINER_NAMES_BLANK:  return FALSE;
    case B_INFO_SHOW_TRAINER_NAMES_LINK:   return gBattleTypeFlags & BATTLE_TYPE_LINK;
    case B_INFO_SHOW_TRAINER_NAMES_ALWAYS: return TRUE;
    }

    return FALSE;
}

static void Overview_DrawNameBoxes(void)
{
    if (!ShouldShowTrainerNames())
        return;

    if (GetOpponentTrainerCount() != 0) // not trainer battle
    {
        if (GetOpponentTrainerCount() >= 2)
            Overview_DrawMultiTrainerNameBoxes(B_SIDE_OPPONENT);
        else
            Overview_DrawTrainerNameBox(B_SIDE_OPPONENT);
    }

    if (HasPartnerTrainer(B_BATTLER_0))
        Overview_DrawMultiTrainerNameBoxes(B_SIDE_PLAYER);
    else
        Overview_DrawTrainerNameBox(B_SIDE_PLAYER);
}

static void Overview_DrawLabels(void)
{
    if (!ShouldShowTrainerNames())
        return;

    if (GetOpponentTrainerCount() != 0) // not trainer battle
    {
        if (GetOpponentTrainerCount() >= 2)
            Overview_DrawMultiTrainerLabels(B_SIDE_OPPONENT);
        else
            Overview_DrawTrainerLabels(B_SIDE_OPPONENT);
    }

    if (HasPartnerTrainer(B_BATTLER_0))
        Overview_DrawMultiTrainerLabels(B_SIDE_PLAYER);
    else
        Overview_DrawTrainerLabels(B_SIDE_PLAYER);
}

static u32 GetWindowForNameFromSide(enum BattleSide side)
{
    return (side == B_SIDE_PLAYER) ? WIN_LABEL_BOTTOM : WIN_LABEL_TOP;
}

static void Overview_DrawTrainerLabels(enum BattleSide side)
{
    u32 windowId = GetWindowForNameFromSide(side);

    u32 labelWidth = GetStringWidth(FONT_SMALL, GetSideTrainerName(side), 0);
    u32 headerX = 0;
    u32 headerWidth = 0;
    Overview_ComputeTrainerNameBoxLayout(labelWidth, GetSideCenterRow(side), NULL, &headerX, &headerWidth);

    s32 labelX = headerX * 8 + ((headerWidth * 8) - labelWidth) / 2;

    FillWindowPixelBuffer(windowId, PIXEL_FILL(B_INFO_TEXT_COLOR_TRANSPARENT));
    Overview_DrawTrainerLabelText(windowId, GetSideTrainerName(side), labelX);
    Overview_FlushLabelWindow(windowId);
}

static void Overview_DrawMultiTrainerLabels(enum BattleSide side)
{
    u32 windowId = GetWindowForNameFromSide(side);

    FillWindowPixelBuffer(windowId, PIXEL_FILL(B_INFO_TEXT_COLOR_TRANSPARENT));

    for (u32 i = 0; i < GetCardCount(); i++)
    {
        struct BattleInfoCard *card = &sData->cards[i];
        if (GetBattlerSide(card->battler) != side)
            continue;
        const u8 *label = GetTrainerNameForBattler(card->battler);
        u32 labelWidth = GetStringWidth(FONT_SMALL, label, 0);
        u32 headerX = 0;
        u32 boxWidth = 0;
        Overview_ComputeHeaderBoxAtCard(card, label, &headerX, &boxWidth);
        s32 labelX = headerX * 8 + ((boxWidth * 8) - labelWidth) / 2;
        Overview_DrawTrainerLabelText(windowId, label, labelX);
    }

    Overview_FlushLabelWindow(windowId);
}

static void Overview_DrawTrainerLabelText(u32 windowId, const u8 *label, s32 labelX)
{
    u32 labelHeight = GetFontAttribute(FONT_SMALL, FONTATTR_MAX_LETTER_HEIGHT);
    if (labelHeight == 0 || labelHeight > B_INFO_LABEL_H)
        labelHeight = 8;

    s32 labelY = (B_INFO_LABEL_H - labelHeight) / 2;
    labelY -= 2;
    labelY = max(labelY, 0);

    struct PrintText text = {
        .windowId = windowId,
        .font = FONT_SMALL,
        .color = sTextColor_BattleInfo_Default,
        .speed = TEXT_SKIP_DRAW,
        .top = labelY,
    };

    text.left = labelX;
    text.string = label;
    PrintTextOnWindow(&text);
}

static void Overview_FlushLabelWindow(u32 windowId)
{
    PutWindowTilemap(windowId);
    CopyWindowToVram(windowId, COPYWIN_FULL);
}

static const u8 *GetSideTrainerName(enum BattleSide side)
{
    if (side == B_SIDE_PLAYER)
        return gSaveBlock2Ptr->playerName;
    return GetTrainerNameFromId(TRAINER_BATTLE_PARAM.opponentA);
}

static u32 GetOpponentTrainerCount(void)
{
    if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER))
        return 0;

    if ((gBattleTypeFlags & (BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_MULTI)) && !BATTLE_TWO_VS_ONE_OPPONENT)
        return 2;

    return 1;
}

static void DestroyOverviewCardSprites(struct BattleInfoCard *card)
{
    DestroyHpBarEndcaps(&card->hpBarLeftEndcapSpriteId, &card->hpBarRightEndcapSpriteId);
    DestroySpriteById(&card->statusSpriteId);
    DestroySpriteById(&card->updateSpriteId);

    if (card->monIconSpriteId != SPRITE_NONE)
    {
        FreeAndDestroyMonIconSprite(&gSprites[card->monIconSpriteId]);
        card->monIconSpriteId = SPRITE_NONE;
    }

    if (card->gimmickSpriteId != SPRITE_NONE)
    {
        DestroySpriteAndFreeResources(&gSprites[card->gimmickSpriteId]);
        card->gimmickSpriteId = SPRITE_NONE;
    }

    if (card->hpBarSpriteId != SPRITE_NONE)
    {
        DestroySpriteAndFreeResources(&gSprites[card->hpBarSpriteId]);
        card->hpBarSpriteId = SPRITE_NONE;
    }
}

static void BattleInfoDestroy(void)
{
    DestroySpriteById(&sData->cursorSpriteId);
    Detail_DestroyWindows();
    Detail_DestroyHpBar();
    Detail_DestroyStatusIcon();
    Detail_DestroyTeraTypeIndicator();
    Detail_DestroyGimmickIndicator();
    Detail_DestroyTypeIcons();
    Detail_DestroyStatPips();
    DestroySpriteById(&sData->effectsScrollbarSpriteId);
    Detail_DestroyIconSprite();

    for (u32 i = 0; i < GetCardCount(); i++)
        DestroyOverviewCardSprites(&sData->cards[i]);

    RemoveWindow(WIN_LABEL_TOP);
    RemoveWindow(WIN_LABEL_BOTTOM);
    RemoveWindow(WIN_ROW_ENEMY);
    RemoveWindow(WIN_ROW_PLAYER);

    FreeSpritePaletteByTag(B_INFO_HP_BAR_PAL_TAG);
    FreeSpritePaletteByTag(B_INFO_HP_BAR_ENDCAP_PAL_TAG);
    FreeSpriteTilesByTag(B_INFO_HP_BAR_ENDCAP_LEFT_TILE_TAG);
    FreeSpriteTilesByTag(B_INFO_HP_BAR_ENDCAP_RIGHT_TILE_TAG);
    FreeSpriteTilesByTag(B_INFO_UPDATE_ICON_TILE_TAG);
    FreeSpriteTilesByTag(B_INFO_CURSOR_TILE_TAG);
    FreeSpriteTilesByTag(B_INFO_DETAIL_EFFECTS_SCROLLBAR_TILE_TAG);
    FreeSpritePaletteByTag(gSpriteTemplate_MoveTypes.paletteTag);
    FreeSpritePaletteByTag(B_INFO_MOVE_TYPES_PAL_TAG_1);
    FreeSpritePaletteByTag(B_INFO_MOVE_TYPES_PAL_TAG_2);
    FreeSpriteTilesByTag(TAG_STATUS_ICONS);
    FreeSpritePaletteByTag(TAG_STATUS_ICONS);
    FreeMonIconPalettes();

    FREE_AND_SET_NULL(sData);
}

static u32 CreateHpBarSprite(u32 tileTag, u32 x, u32 y)
{
    struct SpriteSheet sheet = {
        sBattleInfoHpBarTiles, sizeof(sBattleInfoHpBarTiles), tileTag
    };

    struct SpriteTemplate template = sSpriteTemplate_BattleInfoHpBar;
    u32 spriteId;

    LoadSpriteSheet(&sheet);
    template.tileTag = tileTag;
    spriteId = CreateSprite(&template, x, y, 0);

    if (spriteId != SPRITE_NONE)
    {
        SetSubspriteTables(&gSprites[spriteId], sBattleInfoHpBarSubspriteTable);
        gSprites[spriteId].subspriteMode = SUBSPRITES_IGNORE_PRIORITY;
        gSprites[spriteId].invisible = TRUE;
        gSprites[spriteId].oam.priority = 0;
    }

    return spriteId;
}

static void DestroyHpBarEndcaps(u8 *leftEndcapSpriteId, u8 *rightEndcapSpriteId)
{
    DestroySpriteById(leftEndcapSpriteId);
    DestroySpriteById(rightEndcapSpriteId);
}

static void CreateHpBarEndcaps(u8 *leftEndcapSpriteId, u8 *rightEndcapSpriteId)
{
    DestroyHpBarEndcaps(leftEndcapSpriteId, rightEndcapSpriteId);
    CreateEndCapSprite(&sSpriteTemplate_BattleInfoHpBarLeftEndcap, leftEndcapSpriteId);
    CreateEndCapSprite(&sSpriteTemplate_BattleInfoHpBarRightEndcap, rightEndcapSpriteId);
}

static void CreateEndCapSprite(const struct SpriteTemplate *template, u8 *endcapSpriteId)
{
    *endcapSpriteId = CreateSprite(template, 0, 0, 0);
    if (*endcapSpriteId == SPRITE_NONE)
        return;
    gSprites[*endcapSpriteId].oam.priority = 0;
    gSprites[*endcapSpriteId].invisible = TRUE;
}

static void UpdateHpBarEndcaps(u32 leftEndCapSpriteId, u32 rightEndCapSpriteId, u32 barCenterX, u32 barY, u32 segmentCount)
{
    u32 leftEdge = barCenterX - 32;
    UpdateEndcapsSprites(leftEndCapSpriteId, leftEdge, barY);

    u32 rightEndcapStart = leftEdge + 8 + (segmentCount * 8);
    UpdateEndcapsSprites(rightEndCapSpriteId, rightEndcapStart, barY);
}

static void UpdateEndcapsSprites(u32 endcapSpriteId, u32 x, u32 y)
{
    if (endcapSpriteId == SPRITE_NONE)
        return;
    gSprites[endcapSpriteId].x = x + 20;
    gSprites[endcapSpriteId].y = y + 4;
    gSprites[endcapSpriteId].invisible = FALSE;
}

static void UpdateHpBarTilesWithWidth(u32 spriteId, u32 hp, u32 maxHp, u32 totalPixels, u32 segmentCount)
{
    u32 array[B_INFO_HP_BAR_SEGMENTS];
    u32 filledPixels = GetScaledHPFraction(hp, maxHp, totalPixels);
    u32 barElementId = GetBarGfxId(hp, maxHp);

    for (u32 i = 0; i < B_INFO_HP_BAR_SEGMENTS; i++)
        array[i] = 0;

    if (filledPixels == 0 && hp > 0)
        filledPixels = 1;

    for (u32 i = 0; i < segmentCount; i++)
    {
        if (filledPixels >= 8)
        {
            array[i] = 8;
            filledPixels -= 8;
        }
        else
        {
            array[i] = filledPixels;
            filledPixels = 0;
        }
    }

    u32 tileNum = gSprites[spriteId].oam.tileNum;
    for (u32 segment = 0; segment < B_INFO_HP_BAR_SEGMENTS; segment++)
    {
        void *dst = (void *)(OBJ_VRAM0 + (tileNum + 1 + segment) * TILE_SIZE_4BPP);

        if (segment >= segmentCount)
            CpuFill16(0, dst, TILE_SIZE_4BPP);
        else
            CpuCopy32(&gHealthboxElementsGfxTable[barElementId][array[segment] * TILE_SIZE_4BPP], dst, TILE_SIZE_4BPP);
    }
}

static void UpdateHpBarTiles(u32 spriteId, u32 hp, u32 maxHp)
{
    UpdateHpBarTilesWithWidth(spriteId, hp, maxHp, B_INFO_HEALTHBAR_PIXELS, B_INFO_HP_BAR_SEGMENTS);
}

static void DrawHpBarSprite(struct BattleInfoCard *card)
{
    struct Sprite *sprite;
    u32 hp = gBattleMons[card->battler].hp;
    u32 maxHp = gBattleMons[card->battler].maxHP;
    s32 contentYOffset = (card->y == B_INFO_ROW_Y_ENEMY) ? -2 : 0;

    sprite = &gSprites[card->hpBarSpriteId];
    sprite->x = card->x + (B_INFO_CARD_W / 2) - 16;
    sprite->y = card->y + 46 + contentYOffset;

    UpdateHpBarTiles(card->hpBarSpriteId, hp, maxHp);
    UpdateHpBarEndcaps(
        card->hpBarLeftEndcapSpriteId,
        card->hpBarRightEndcapSpriteId,
        sprite->x, sprite->y, B_INFO_HP_BAR_SEGMENTS
    );
    sprite->invisible = FALSE;
}

static u32 GetBarGfxId(u32 hp, u32 maxHp)
{
    switch (GetHPBarLevel(hp, maxHp))
    {
    case HP_BAR_GREEN:
    case HP_BAR_FULL:
        return HEALTHBOX_GFX_HP_BAR_GREEN;
    case HP_BAR_YELLOW:
        return HEALTHBOX_GFX_HP_BAR_YELLOW;
    case HP_BAR_RED:
    default:
        return HEALTHBOX_GFX_HP_BAR_RED;
    }

    return HEALTHBOX_GFX_HP_BAR_RED;
}

static u32 GetAilmentFromBattler(enum BattlerId battler)
{
    if (!IsBattlerAlive(battler))
        return AILMENT_FNT;
    return GetAilmentFromStatus(gBattleMons[battler].status1);
}

static void Overview_GetCursorPos(const struct BattleInfoCard *card, s16 *outX, s16 *outY)
{
    *outX = card->x + 2;
    *outY = card->y + (B_INFO_CARD_H / 2) + 2;
}

static void Overview_InitCursor(void)
{
    s16 cursorX;
    s16 cursorY;

    DestroySpriteById(&sData->cursorSpriteId);

    Overview_GetCursorPos(&sData->cards[sData->selectedCard], &cursorX, &cursorY);
    sData->cursorSpriteId = CreateSprite(&sSpriteTemplate_BattleInfoCursor, cursorX, cursorY, 0);
    if (sData->cursorSpriteId != SPRITE_NONE)
        gSprites[sData->cursorSpriteId].oam.priority = 0;
}

static void Overview_UpdateCursorPos(void)
{
    struct BattleInfoCard *card;
    card = &sData->cards[sData->selectedCard];
    Overview_GetCursorPos(card, &gSprites[sData->cursorSpriteId].x, &gSprites[sData->cursorSpriteId].y);
}

static void Task_BattleMenuStatus_HandleInput(u8 taskId)
{
    if (sData->page == B_INFO_PAGE_OVERVIEW)
        Overview_HandleInput(taskId);
    else
        Detail_HandleInput(taskId);
}

static void Overview_HandleInput(u8 taskId)
{
    if (JOY_NEW(DPAD_LEFT))
    {
        Overview_TryMoveCursor(B_INFO_CURSOR_LEFT);
    }
    else if (JOY_NEW(DPAD_RIGHT))
    {
        Overview_TryMoveCursor(B_INFO_CURSOR_RIGHT);
    }
    else if (JOY_NEW(DPAD_UP))
    {
        Overview_TryMoveCursor(B_INFO_CURSOR_UP);
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        Overview_TryMoveCursor(B_INFO_CURSOR_DOWN);
    }
    else if (JOY_NEW(A_BUTTON) && CanViewCard(GetSelectedBattler()))
    {
        PlaySE(SE_SELECT);
        sData->menuState = B_INFO_STATE_CLEAR_PAGE;
        sData->page = B_INFO_PAGE_DETAIL;
        gTasks[taskId].func = Task_BattleInfoLoadPage;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        sData->menuState = B_INFO_STATE_EXIT;
        gTasks[taskId].func = Task_BattleInfoLoadPage;
    }
}

static void Detail_HandleInput(u8 taskId)
{
    s32 scrollDir = 0;

    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        sData->menuState = B_INFO_STATE_CLEAR_PAGE;
        sData->page = B_INFO_PAGE_OVERVIEW;
        gTasks[taskId].func = Task_BattleInfoLoadPage;
    }
    else if (JOY_NEW(L_BUTTON))
    {
        PlaySE(SE_SELECT);
        Detail_CycleBattler(-1);
    }
    else if (JOY_NEW(R_BUTTON))
    {
        PlaySE(SE_SELECT);
        Detail_CycleBattler(1);
    }
    else
    {
        if (JOY_REPEAT(DPAD_UP))
            scrollDir = -1;
        else if (JOY_REPEAT(DPAD_DOWN))
            scrollDir = 1;

        if (scrollDir != 0 && Detail_TryMoveEffectCursor(scrollDir))
        {
            PlaySE(SE_SELECT);
            Detail_RefreshEffectsSection();
        }
    }
}

static void Overview_TryMoveCursor(u32 direction)
{
    u32 currSelectedCard = sData->selectedCard;

    switch (direction)
    {
    case B_INFO_CURSOR_LEFT:
    case B_INFO_CURSOR_RIGHT:
        if (IsDoubleBattle())
            sData->selectedCard ^= 1;
        break;
    case B_INFO_CURSOR_UP:
    case B_INFO_CURSOR_DOWN:
        if (IsDoubleBattle())
            sData->selectedCard ^= 2;
        else
            sData->selectedCard ^= 1;
        break;
    }

    Overview_UpdateCardSelectionHighlight(currSelectedCard);
    Overview_UpdateCursorPos();
}

static void Overview_UpdateCardSelectionHighlight(u32 oldSelectedIndex)
{
    Overview_UpdateOldSelectedCard(oldSelectedIndex);
    Overview_UpdateNewSelectedCard();
    CopyBgTilemapBufferToVram(B_INFO_BACKDROP_BG);
}

static void Overview_UpdateOldSelectedCard(u32 oldSelectedIndex)
{
    Overview_DrawCardBackground(&sData->cards[oldSelectedIndex], FALSE);
}

static void Overview_UpdateNewSelectedCard(void)
{
    Overview_DrawCardBackground(&sData->cards[sData->selectedCard], TRUE);
}

static u32 GetCardCount(void)
{
    return gBattlersCount;
}

static bool32 CanViewCard(enum BattlerId battler)
{
    return IsBattlerAlive(battler);
}

static enum BattlerId GetSelectedBattler(void)
{
    return sData->cards[sData->selectedCard].battler;
}

static enum BattlerId GetBattlerFromSlot(u32 slot)
{
    if (IsDoubleBattle())
    {
        switch (slot)
        {
        case 0: return B_BATTLER_1;
        case 1: return B_BATTLER_3;
        case 2: return B_BATTLER_0;
        case 3: return B_BATTLER_2;
        }
    }
    else
    {
        switch (slot)
        {
        case 0: return B_BATTLER_1;
        case 1: return B_BATTLER_0;
        }
    }

    return B_BATTLER_1;
}

static void PrintTextOnWindow(struct PrintText *text)
{
    AddTextPrinterParameterized4(
        text->windowId,
        text->font,
        text->left,
        text->top,
        text->letterSpacing,
        text->lineSpacing,
        text->color,
        text->speed,
        text->string
    );
}

static u32 MakeEven(u32 value)
{
    if (value % 2 != 0)
        value++;
    return value;
}

static u32 PixelsToTiles(u32 width)
{
    return (width + TILE_WIDTH - 1) / TILE_WIDTH;
}
