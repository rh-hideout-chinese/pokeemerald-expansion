#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_ai_record.h"
#include "battle_controllers.h"
#include "battle_message.h"
#include "battle_setup.h"
#include "battle_special.h"
#include "battle_z_move.h"
#include "data.h"
#include "event_data.h"
#include "frontier_util.h"
#include "graphics.h"
#include "international_string_util.h"
#include "item.h"
#include "link.h"
#include "menu.h"
#include "palette.h"
#include "recorded_battle.h"
#include "string_util.h"
#include "strings.h"
#include "test_runner.h"
#include "text.h"
#include "trainer_hill.h"
#include "trainer_slide.h"
#include "trainer_tower.h"
#include "window.h"
#include "line_break.h"
#include "constants/abilities.h"
#include "constants/battle_dome.h"
#include "constants/battle_string_ids.h"
#include "constants/frontier_util.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/opponents.h"
#include "constants/species.h"
#include "constants/trainers.h"
#include "constants/trainer_hill.h"
#include "constants/weather.h"

struct BattleWindowText
{
    u8 fillValue;
    u8 fontId;
    u8 x;
    u8 y;
    union {
        struct {
            DEPRECATED("Use color.background instead") u8 bgColor;
            DEPRECATED("Use color.foreground instead") u8 fgColor;
            DEPRECATED("Use color.shadow instead") u8 shadowColor;
            DEPRECATED("Use color.accent instead") u8 accentColor;
        };
        union TextColor color;
    };
    u8 letterSpacing;
    u8 lineSpacing;
    u8 speed;
};

#if TESTING
EWRAM_DATA u16 sBattlerAbilities[MAX_BATTLERS_COUNT] = {0};
#else
static EWRAM_DATA u16 sBattlerAbilities[MAX_BATTLERS_COUNT] = {0};
#endif
EWRAM_DATA struct BattleMsgData *gBattleMsgDataPtr = NULL;

// todo: make some of those names less vague: attacker/target vs pkmn, etc.

static const u8 sText_EmptyString4[] = _("");

const u8 gText_PkmnShroudedInMist[] = _("{B_ATK_TEAM1}被\n白雾包围了！");
const u8 gText_PkmnGettingPumped[] = _("{B_DEF_NAME_WITH_PREFIX}\n现在干劲十足！");
const u8 gText_PkmnsXPreventsSwitching[] = _("因{B_BUFF1}的{B_LAST_ABILITY}\n而无法进行替换！\p");
const u8 gText_StatSharply[] = _("大幅");
const u8 gText_StatRose[] = _("提高了！");
const u8 gText_StatFell[] = _("降低了！");
const u8 gText_DefendersStatRose[] = _("{B_DEF_NAME_WITH_PREFIX}的\n{B_BUFF1}{B_BUFF2}提高了！");
static const u8 sText_GotAwaySafely[] = _("{PLAY_SE SE_FLEE}顺利逃走了！\p");
static const u8 sText_PlayerDefeatedLinkTrainer[] = _("战胜了\n{B_LINK_OPPONENT1_NAME}！");
static const u8 sText_TwoLinkTrainersDefeated[] = _("战胜了\n{B_LINK_OPPONENT1_NAME}和{B_LINK_OPPONENT2_NAME}！");
static const u8 sText_PlayerLostAgainstLinkTrainer[] = _("被{B_LINK_OPPONENT1_NAME}\n打败了！");
static const u8 sText_PlayerLostToTwo[] = _("被{B_LINK_OPPONENT1_NAME}和{B_LINK_OPPONENT2_NAME}\n打败了！");
static const u8 sText_PlayerBattledToDrawLinkTrainer[] = _("和{B_LINK_OPPONENT1_NAME}\n打成了平局！");
static const u8 sText_PlayerBattledToDrawVsTwo[] = _("与{B_LINK_OPPONENT1_NAME}和{B_LINK_OPPONENT2_NAME}\n打成了平局！");
static const u8 sText_WildFled[] = _("{PLAY_SE SE_FLEE}{B_LINK_OPPONENT1_NAME}逃走了！"); //not in gen 5+, replaced with match was forfeited text
static const u8 sText_TwoWildFled[] = _("{PLAY_SE SE_FLEE}{B_LINK_OPPONENT1_NAME}和\n{B_LINK_OPPONENT2_NAME}逃走了！"); //not in gen 5+, replaced with match was forfeited text
static const u8 sText_PlayerDefeatedLinkTrainerTrainer1[] = _("战胜了\n{B_TRAINER1_NAME_WITH_CLASS}！\p");
static const u8 sText_OpponentMon1Appeared[] = _("{B_OPPONENT_MON1_NAME}出现了！\p");
static const u8 sText_WildPkmnAppeared[] = _("啊！野生的\n{B_OPPONENT_MON1_NAME}扑过来了！\p");
static const u8 sText_LegendaryPkmnAppeared[] = _("{B_OPPONENT_MON1_NAME}出现了！\p");
static const u8 sText_WildPkmnAppearedPause[] = _("啊！野生的\n{B_OPPONENT_MON1_NAME}扑过来了！{PAUSE 127}");
static const u8 sText_TwoWildPkmnAppeared[] = _("啊！野生的\n{B_OPPONENT_MON1_NAME}和{B_OPPONENT_MON2_NAME}扑过来了！\p");
static const u8 sText_GhostAppearedCantId[] = _("幽灵出现了！\p可恶！\n无法辨认出幽灵的正体！\p");
static const u8 sText_TheGhostAppeared[] = _("幽灵出现了！\p");
static const u8 sText_Trainer1WantsToBattle[] = _("{B_TRAINER1_NAME_WITH_CLASS}\n前来挑战了！\p");
static const u8 sText_LinkTrainerWantsToBattle[] = _("{B_LINK_OPPONENT1_NAME}\n前来挑战了！");
static const u8 sText_TwoLinkTrainersWantToBattle[] = _("{B_LINK_OPPONENT1_NAME}和{B_LINK_OPPONENT2_NAME}\n前来挑战了！");
static const u8 sText_Trainer1SentOutPkmn[] = _("{B_TRAINER1_NAME_WITH_CLASS}\n派出了{B_OPPONENT_MON1_NAME}！");
static const u8 sText_Trainer1SentOutTwoPkmn[] = _("{B_TRAINER1_NAME_WITH_CLASS}\n派出了{B_OPPONENT_MON1_NAME}和{B_OPPONENT_MON2_NAME}！");
static const u8 sText_Trainer1SentOutPkmn2[] = _("{B_TRAINER1_NAME_WITH_CLASS}\n派出了{B_BUFF1}！");
static const u8 sText_LinkTrainerIntroSendOutPkmn[] = _("{B_LINK_OPPONENT1_NAME}\n派出了{B_LINK_OPPONENT_MON1_NAME}！");
static const u8 sText_LinkTrainerSentOutPkmn[] = _("{B_LINK_OPPONENT1_NAME}派出了\n{B_BUFF1}！");
static const u8 sText_LinkTrainer2SentOutPkmn2[] = _("{B_LINK_OPPONENT2_NAME}派出了\n{B_BUFF1}！");
static const u8 sText_LinkTrainerSentOutTwoPkmn[] = _("{B_LINK_OPPONENT1_NAME}派出了\n{B_OPPONENT_MON1_NAME}和{B_OPPONENT_MON2_NAME}！");
static const u8 sText_TwoLinkTrainersIntroSendOutPkmn[] = _("{B_LINK_OPPONENT1_NAME}派出了{B_LINK_OPPONENT_MON1_NAME}！\n{B_LINK_OPPONENT2_NAME}派出了{B_LINK_OPPONENT_MON2_NAME}！");
static const u8 sText_LinkTrainerSentOutPkmn2[] = _("{B_LINK_OPPONENT1_NAME}派出了\n{B_LINK_OPPONENT_MON2_NAME}！");
static const u8 sText_LinkTrainerMultiSentOutPkmn[] = _("{B_LINK_SCR_TRAINER_NAME}派出了\n{B_BUFF1}！");
static const u8 sText_GoPkmn[] = _("上吧！{B_PLAYER_MON1_NAME}！");
static const u8 sText_GoTwoPkmn[] = _("上吧！{B_PLAYER_MON1_NAME}！\n{B_PLAYER_MON2_NAME}！");
static const u8 sText_GoPkmn2[] = _("上吧！{B_BUFF1}！");
static const u8 sText_DoItPkmn[] = _("交给你了！{B_BUFF1}！");
static const u8 sText_GoForItPkmn[] = _("加油！{B_BUFF1}！");
static const u8 sText_JustALittleMorePkmn[] = _("只差一点了！\n加油！{B_BUFF1}！"); //currently unused, will require code changes
static const u8 sText_YourFoesWeakGetEmPkmn[] = _("对手变弱了！\n机会来了！{B_BUFF1}！");
static const u8 sText_LinkPartnerSentOutPkmn1GoPkmn[] = _("{B_LINK_PARTNER_NAME}派出了{B_LINK_PLAYER_MON2_NAME}！\n上吧！{B_LINK_PLAYER_MON1_NAME}！");
static const u8 sText_LinkPartnerSentOutPkmn2GoPkmn[] = _("{B_LINK_PARTNER_NAME}派出了{B_LINK_PLAYER_MON2_NAME}\n上吧！{B_LINK_PLAYER_MON1_NAME}！");
static const u8 sText_LinkPartnerSentOutPkmn1[] = _("{B_LINK_PARTNER_NAME}派出了{B_BUFF1}！");
static const u8 sText_LinkPartnerSentOutPkmn2[] = _("{B_LINK_PARTNER_NAME}派出了{B_BUFF1}！");
static const u8 sText_LinkPartnerWithdrewPkmn1[] = _("{B_LINK_PARTNER_NAME}换下了{B_LINK_PLAYER_MON1_NAME}！");
static const u8 sText_LinkPartnerWithdrewPkmn2[] = _("{B_LINK_PARTNER_NAME}换下了{B_LINK_PLAYER_MON2_NAME}！");
static const u8 sText_PkmnSwitchOut[] = _("{B_BUFF1}，替换！\n回来！"); //currently unused, I believe its used for when you switch on a Pokémon in shift mode
static const u8 sText_PkmnThatsEnough[] = _("{B_BUFF1}，好了！\n回来！");
static const u8 sText_PkmnComeBack[] = _("{B_BUFF1}，\n回来！");
static const u8 sText_PkmnOkComeBack[] = _("{B_BUFF1}，很好！\n回来！");
static const u8 sText_PkmnGoodComeBack[] = _("{B_BUFF1}，干得漂亮！\n回来！");
static const u8 sText_Trainer1WithdrewPkmn[] = _("{B_TRAINER1_NAME_WITH_CLASS}换下了\n{B_BUFF1}！");
static const u8 sText_Trainer2WithdrewPkmn[] = _("{B_TRAINER2_NAME_WITH_CLASS}换下了\n{B_BUFF1}！");
static const u8 sText_LinkTrainer1WithdrewPkmn[] = _("{B_LINK_OPPONENT1_NAME}换下了\n{B_BUFF1}！");
static const u8 sText_LinkTrainer2WithdrewPkmn[] = _("{B_LINK_OPPONENT2_NAME}换下了{B_BUFF1}！");
static const u8 sText_WildPkmnPrefix[] = _("野生的");
static const u8 sText_FoePkmnPrefix[] = _("对手的");
static const u8 sText_WildPkmnPrefixLower[] = _("野生的");
static const u8 sText_FoePkmnPrefixLower[] = _("对手的");
static const u8 sText_EmptyString8[] = _("");
static const u8 sText_FoePkmnPrefix2[] = _("对手");
static const u8 sText_AllyPkmnPrefix[] = _("我方");
static const u8 sText_FoePkmnPrefix3[] = _("对手");
static const u8 sText_AllyPkmnPrefix2[] = _("我方");
static const u8 sText_FoePkmnPrefix4[] = _("对手");
static const u8 sText_AllyPkmnPrefix3[] = _("我方");
static const u8 sText_AttackerUsedX[] = _("{B_ATK_NAME_WITH_PREFIX}使出了\n{B_BUFF3}！");
static const u8 sText_ExclamationMark[] = _("！");
static const u8 sText_ExclamationMark2[] = _("！");
static const u8 sText_ExclamationMark3[] = _("！");
static const u8 sText_ExclamationMark4[] = _("！");
static const u8 sText_ExclamationMark5[] = _("！");
static const u8 sText_HP[] = _("HP");
static const u8 sText_Attack[] = _("攻击");
static const u8 sText_Defense[] = _("防御");
static const u8 sText_Speed[] = _("速度");
static const u8 sText_SpAttack[] = _("特攻");
static const u8 sText_SpDefense[] = _("特防");
static const u8 sText_Accuracy[] = _("命中率");
static const u8 sText_Evasiveness[] = _("闪避率");

const u8 *const gStatNamesTable[NUM_BATTLE_STATS] =
{
    [STAT_HP]      = sText_HP,
    [STAT_ATK]     = sText_Attack,
    [STAT_DEF]     = sText_Defense,
    [STAT_SPEED]   = sText_Speed,
    [STAT_SPATK]   = sText_SpAttack,
    [STAT_SPDEF]   = sText_SpDefense,
    [STAT_ACC]     = sText_Accuracy,
    [STAT_EVASION] = sText_Evasiveness,
};
const u8 *const gPokeblockWasTooXStringTable[FLAVOR_COUNT] =
{
    [FLAVOR_SPICY]  = COMPOUND_STRING("太辣了！"),
    [FLAVOR_DRY]    = COMPOUND_STRING("太涩了！"),
    [FLAVOR_SWEET]  = COMPOUND_STRING("太甜了！"),
    [FLAVOR_BITTER] = COMPOUND_STRING("太苦了！"),
    [FLAVOR_SOUR]   = COMPOUND_STRING("太酸了！"),
};

static const u8 sText_Someones[] = _("某人的");
static const u8 sText_Lanettes[] = _("真由美的"); //no decapitalize until it is everywhere
static const u8 sText_Bills[] = _("正辉的");
static const u8 sText_EnigmaBerry[] = _("谜芝果"); //no decapitalize until it is everywhere
static const u8 sText_BerrySuffix[] = _("果"); //no decapitalize until it is everywhere
const u8 gText_EmptyString3[] = _("");

static const u8 sText_TwoInGameTrainersDefeated[] = _("战胜了\n{B_TRAINER1_NAME_WITH_CLASS}和\l{B_TRAINER2_NAME_WITH_CLASS}！\p");

// New battle strings.
const u8 gText_drastically[] = _("巨幅");
const u8 gText_severely[] = _("巨幅");
static const u8 sText_TerrainReturnedToNormal[] = _("场地恢复了正常！"); // Unused

const u8 *const gBattleStringsTable[STRINGID_COUNT] =
{
    [STRINGID_TRAINER1LOSETEXT]                     = COMPOUND_STRING("{B_TRAINER1_LOSE_TEXT}"),
    [STRINGID_PKMNGAINEDEXP]                        = COMPOUND_STRING("{B_BUFF1}获得了{B_BUFF2}\n{B_BUFF3}经验值！\p"),
    [STRINGID_PKMNGREWTOLV]                         = COMPOUND_STRING("{B_BUFF1}\n上升到了等级{B_BUFF2}！{WAIT_SE}\p"),
    [STRINGID_PKMNLEARNEDMOVE]                      = COMPOUND_STRING("{B_BUFF1}\n学会了{B_BUFF2}！{WAIT_SE}\p"),
    [STRINGID_TRYTOLEARNMOVE1]                      = COMPOUND_STRING("{B_BUFF1}想要学习\n{B_BUFF2}。\p"),
    [STRINGID_TRYTOLEARNMOVE2]                      = COMPOUND_STRING("但是，{B_BUFF1}已经不能\n习得更多的招式。\p"),
    [STRINGID_TRYTOLEARNMOVE3]                      = COMPOUND_STRING("为了学习{B_BUFF2}，\n要忘记其他的招式吗？"),
    [STRINGID_PKMNFORGOTMOVE]                       = COMPOUND_STRING("{B_BUFF1}把{B_BUFF2}的\n使用方法忘得干干净净了！\p"),
    [STRINGID_STOPLEARNINGMOVE]                     = COMPOUND_STRING("{PAUSE 32}要放弃学习\n{B_BUFF2}吗？"),
    [STRINGID_DIDNOTLEARNMOVE]                      = COMPOUND_STRING("{B_BUFF1}没有学习\n{B_BUFF2}就结束了！\p"),
    [STRINGID_PKMNLEARNEDMOVE2]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n学会了{B_BUFF1}！"),
    [STRINGID_PKMNPROTECTEDITSELF]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n在攻击中守护住了自己！"),
    [STRINGID_STATSWONTINCREASE2]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的\n能力已经无法再提高了！"),
    [STRINGID_ITDOESNTAFFECT]                       = COMPOUND_STRING("对于{B_DEF_NAME_WITH_PREFIX2}，\n好像没有效果……"),
    [STRINGID_SCR_ITDOESNTAFFECT]                   = COMPOUND_STRING("对于{B_SCR_NAME_WITH_PREFIX2}，\n好像没有效果……"),
    [STRINGID_BATTLERFAINTED]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}倒下了！\p"),
    [STRINGID_PLAYERGOTMONEY]                       = COMPOUND_STRING("作为奖金，\n{B_PLAYER_NAME}获得了¥{B_BUFF1}！\p"),
    [STRINGID_PLAYERWHITEOUT]                       = COMPOUND_STRING("{B_PLAYER_NAME}的手上没有\n可以战斗的宝可梦！\p"),
    [STRINGID_PLAYERWHITEOUT2_WILD]                 = COMPOUND_STRING("{B_PLAYER_NAME}在慌乱中\n丢失了¥{B_BUFF1}……"),
    [STRINGID_PLAYERWHITEOUT2_TRAINER]              = COMPOUND_STRING("{B_PLAYER_NAME}支付了¥{B_BUFF1}\n作为奖金……"),
    [STRINGID_PLAYERWHITEOUT3]                      = COMPOUND_STRING("………………\n………………\p{B_PLAYER_NAME}的眼前变得一片漆黑！"),
    [STRINGID_PREVENTSESCAPE]                       = COMPOUND_STRING("因{B_SCR_NAME_WITH_PREFIX}的\n{B_SCR_ABILITY}而无法逃走！\p"),
    [STRINGID_HITXTIMES]                            = COMPOUND_STRING("击中了{B_BUFF1}次！"), //SV has dynamic plural here
    [STRINGID_PKMNFELLASLEEP]                       = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}睡着了！"),
    [STRINGID_PKMNMADESLEEP]                        = COMPOUND_STRING("因{B_SCR_NAME_WITH_PREFIX2}的{B_BUFF1}，\n{B_EFF_NAME_WITH_PREFIX2}睡着了！"), //not in gen 5+, ability popup
    [STRINGID_PKMNALREADYASLEEP]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n已经睡着了！"),
    [STRINGID_PKMNALREADYASLEEP2]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n已经睡着了！"),
    [STRINGID_PKMNWASPOISONED]                      = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}中毒了！"),
    [STRINGID_PKMNPOISONEDBY]                       = COMPOUND_STRING("因{B_SCR_NAME_WITH_PREFIX}的{B_BUFF1}，\n{B_EFF_NAME_WITH_PREFIX2}中毒了！"), //not in gen 5+, ability popup
    [STRINGID_PKMNHURTBYPOISON]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n受到了毒的伤害！"),
    [STRINGID_PKMNALREADYPOISONED]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n已经中毒了。"),
    [STRINGID_PKMNBADLYPOISONED]                    = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}中剧毒了！"),
    [STRINGID_PKMNENERGYDRAINED]                    = COMPOUND_STRING("从{B_DEF_NAME_WITH_PREFIX}那里\n吸取了体力！"),
    [STRINGID_PKMNWASBURNED]                        = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}被灼伤了！"),
    [STRINGID_PKMNBURNEDBY]                         = COMPOUND_STRING("因{B_SCR_NAME_WITH_PREFIX2}的{B_BUFF1}，\n{B_EFF_NAME_WITH_PREFIX2}被灼伤了！"), //not in gen 5+, ability popup
    [STRINGID_PKMNHURTBYBURN]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n受到了灼伤的伤害！"),
    [STRINGID_PKMNWASFROZEN]                        = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}冻住了！"),
    [STRINGID_PKMNFROZENBY]                         = COMPOUND_STRING("因{B_SCR_NAME_WITH_PREFIX2}的{B_BUFF1}，\n{B_EFF_NAME_WITH_PREFIX2}冻住了！"), //not in gen 5+, ability popup
    [STRINGID_PKMNISFROZEN]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n因冻住了而无法行动！"),
    [STRINGID_PKMNWASDEFROSTED]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n冰冻被融化了！"),
    [STRINGID_PKMNWASDEFROSTEDBY]                   = COMPOUND_STRING("因{B_SCR_NAME_WITH_PREFIX}的\n{B_CURRENT_MOVE}，冰冻被融化了！"),
    [STRINGID_PKMNWASPARALYZED]                     = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}麻痹了，\n很难使出招式！"),
    [STRINGID_PKMNWASPARALYZEDBY]                   = COMPOUND_STRING("因{B_SCR_NAME_WITH_PREFIX}的{B_BUFF1}，\n{B_EFF_NAME_WITH_PREFIX2}麻痹了，\l很难使出招式！"), //not in gen 5+, ability popup
    [STRINGID_PKMNISPARALYZED]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n因身体麻痹而无法行动！"),
    [STRINGID_PKMNISALREADYPARALYZED]               = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n已经麻痹了。"),
    [STRINGID_PKMNHEALEDPARALYSIS]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}的\n麻痹被解除了！"),
    [STRINGID_STATSWONTINCREASE]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的\n{B_BUFF1}已经无法再提高了！"),
    [STRINGID_STATSWONTDECREASE]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}的\n{B_BUFF1}已经无法再降低了！"),
    [STRINGID_PKMNISCONFUSED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n正在混乱中！"),
    [STRINGID_PKMNHEALEDCONFUSION]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的\n混乱解除了！"),
    [STRINGID_PKMNWASCONFUSED]                      = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}混乱了！"),
    [STRINGID_PKMNALREADYCONFUSED]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n已经混乱了。"),
    [STRINGID_PKMNFELLINLOVE]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n着迷了！"),
    [STRINGID_PKMNINLOVE]                           = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX2}让\n{B_ATK_NAME_WITH_PREFIX}着迷了！"),
    [STRINGID_PKMNIMMOBILIZEDBYLOVE]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n因着迷了而无法使出招式！"),
    [STRINGID_PKMNCHANGEDTYPE]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n变成了{B_BUFF1}属性！"),
    [STRINGID_PKMNFLINCHED]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}畏缩了，\n无法使出招式！"),
    [STRINGID_PKMNREGAINEDHEALTH]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}的\n体力回复了！"),
    [STRINGID_PKMNHPFULL]                           = COMPOUND_STRING("但是，{B_DEF_NAME_WITH_PREFIX}的\n体力是全满的！"),
    [STRINGID_PKMNRAISEDSPDEF]                      = COMPOUND_STRING("光墙使{B_ATK_TEAM2}的\n特殊抗性提高了！"),
    [STRINGID_PKMNRAISEDDEF]                        = COMPOUND_STRING("反射壁使{B_ATK_TEAM2}的\n物理抗性提高了！"),
    [STRINGID_PKMNAURORAVEIL]                       = COMPOUND_STRING("极光幕使{B_ATK_TEAM2}的\n物理和特殊抗性提高了！"),
    [STRINGID_PKMNCOVEREDBYVEIL]                    = COMPOUND_STRING("{B_ATK_TEAM1}被\n神秘之幕包围了！"),
    [STRINGID_PKMNUSEDSAFEGUARD]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n正受到神秘之幕的保护！"),
    [STRINGID_PKMNSAFEGUARDEXPIRED]                 = COMPOUND_STRING("包围{B_ATK_TEAM1}的\n神秘之幕消失了！"),
    [STRINGID_PKMNWENTTOSLEEP]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}睡着了！"), //not in gen 5+
    [STRINGID_PKMNSLEPTHEALTHY]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}睡着了，\n并且变得精力充沛！"),
    [STRINGID_PKMNWHIPPEDWHIRLWIND]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}周围的\n空气产生了旋涡！"),
    [STRINGID_PKMNTOOKSUNLIGHT]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n吸收了光！"),
    [STRINGID_PKMNLOWEREDHEAD]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n把头缩了进去！"),
    [STRINGID_PKMNFLEWHIGH]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n飞向了高空！"),
    [STRINGID_PKMNDUGHOLE]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n钻入了地里！"),
    [STRINGID_PKMNSQUEEZEDBYBIND]                   = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}\n被{B_ATK_NAME_WITH_PREFIX2}紧紧绑住了！"),
    [STRINGID_PKMNTRAPPEDINVORTEX]                  = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}\n被困在了旋涡之中！"),
    [STRINGID_PKMNWRAPPEDBY]                        = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}\n被{B_ATK_NAME_WITH_PREFIX2}紧紧束缚住了！"),
    [STRINGID_PKMNCLAMPED]                          = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX2}\n被{B_ATK_NAME_WITH_PREFIX}的贝壳夹住了！"),
    [STRINGID_PKMNHURTBY]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}受到了\n{B_BUFF1}的伤害。"),
    [STRINGID_PKMNFREEDFROM]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}摆脱了\n{B_BUFF1}的束缚！"),
    [STRINGID_PKMNCRASHED]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}因势头过猛\n而撞到了地面！"),
    [STRINGID_PKMNSHROUDEDINMIST]                   = gText_PkmnShroudedInMist,
    [STRINGID_PKMNPROTECTEDBYMIST]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n正受到白雾的保护！"),
    [STRINGID_PKMNGETTINGPUMPED]                    = gText_PkmnGettingPumped,
    [STRINGID_PKMNHITWITHRECOIL]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n受到了反作用力造成的伤害！"),
    [STRINGID_PKMNPROTECTEDITSELF2]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n摆出了防守的架势！"),
    [STRINGID_PKMNBUFFETEDBYSANDSTORM]              = COMPOUND_STRING("沙暴袭击了\n{B_ATK_NAME_WITH_PREFIX}！"),
    [STRINGID_PKMNPELTEDBYHAIL]                     = COMPOUND_STRING("冰雹袭击了\n{B_ATK_NAME_WITH_PREFIX}！"),
    [STRINGID_PKMNSEEDED]                           = COMPOUND_STRING("将种子种植在了\n{B_DEF_NAME_WITH_PREFIX}身上！"),
    [STRINGID_PKMNEVADEDATTACK]                     = COMPOUND_STRING("没有击中{B_DEF_NAME_WITH_PREFIX}！"),
    [STRINGID_PKMNSAPPEDBYLEECHSEED]                = COMPOUND_STRING("寄生植物夺取了\n{B_ATK_NAME_WITH_PREFIX}的体力！"),
    [STRINGID_PKMNFASTASLEEP]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n正在呼呼大睡。"),
    [STRINGID_PKMNWOKEUP]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n醒过来了！"),
    [STRINGID_PKMNWOKEUPINUPROAR]                   = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX2}\n被吵醒了！"),
    [STRINGID_PKMNCAUSEDUPROAR]                     = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}\n吵闹了起来！"),
    [STRINGID_PKMNMAKINGUPROAR]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n吵闹个不停！"),
    [STRINGID_PKMNCALMEDDOWN]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n平静了下来！"),
    [STRINGID_PKMNSTOCKPILED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n蓄力了{B_BUFF1}次！"),
    [STRINGID_PKMNCANTSLEEPINUPROAR2]               = COMPOUND_STRING("但是，{B_DEF_NAME_WITH_PREFIX2}\n吵闹个不停，无法入睡！"),
    [STRINGID_UPROARKEPTPKMNAWAKE]                  = COMPOUND_STRING("但是，{B_DEF_NAME_WITH_PREFIX2}\n被吵得无法入睡！"),
    [STRINGID_PKMNSTAYEDAWAKEUSING]                 = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}不会睡着！"), //not in gen 5+, ability popup
    [STRINGID_PKMNSTORINGENERGY]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n正在忍耐。"),
    [STRINGID_PKMNUNLEASHEDENERGY]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的\n忍耐被解除了！"),
    [STRINGID_PKMNFATIGUECONFUSION]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n因精疲力尽而混乱了！"),
    [STRINGID_PLAYERPICKEDUPMONEY]                  = COMPOUND_STRING("{B_PLAYER_NAME}捡到了\n¥{B_BUFF1}！\p"),
    [STRINGID_PKMNUNAFFECTED]                       = COMPOUND_STRING("对于{B_DEF_NAME_WITH_PREFIX}，\n完全没有效果！"),
    [STRINGID_PKMNTRANSFORMEDINTO]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n变身成了{B_BUFF1}！"),
    [STRINGID_PKMNMADESUBSTITUTE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的\n替身出现了！"),
    [STRINGID_PKMNHASSUBSTITUTE]                    = COMPOUND_STRING("但是，{B_ATK_NAME_WITH_PREFIX}的\n替身已经出现了。"),
    [STRINGID_SUBSTITUTEDAMAGED]                    = COMPOUND_STRING("替身代替{B_DEF_NAME_WITH_PREFIX2}\n承受了攻击！\p"),
    [STRINGID_PKMNSUBSTITUTEFADED]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n替身消失了……\p"),
    [STRINGID_PKMNMUSTRECHARGE]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n因攻击的反作用力而无法动弹！"),
    [STRINGID_PKMNRAGEBUILDING]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}的\n怒气正在上升！"),
    [STRINGID_PKMNMOVEWASDISABLED]                  = COMPOUND_STRING("封住了{B_DEF_NAME_WITH_PREFIX}的\n{B_BUFF1}！"),
    [STRINGID_PKMNMOVEISDISABLED]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}因定身法\n而无法使出{B_CURRENT_MOVE}！\p"),
    [STRINGID_PKMNMOVEDISABLEDNOMORE]               = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n定身法解除了！"),
    [STRINGID_PKMNGOTENCORE]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n接受了再来一次！"),
    [STRINGID_PKMNGOTENCOREDMOVE]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n只能使用{B_CURRENT_MOVE}！\p"),
    [STRINGID_PKMNENCOREENDED]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n再来一次状态解除了！"),
    [STRINGID_PKMNTOOKAIM]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}将目标对准了\n{B_DEF_NAME_WITH_PREFIX2}！"),
    [STRINGID_PKMNSKETCHEDMOVE]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n对{B_BUFF1}进行了写生！"),
    [STRINGID_PKMNTRYINGTOTAKEFOE]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n想和对手同归于尽！"),
    [STRINGID_PKMNTOOKFOE]                          = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n和对手同归于尽了！"),
    [STRINGID_PKMNREDUCEDPP]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}的PP减少了！"),
    [STRINGID_PKMNSTOLEITEM]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n从{B_EFF_NAME_WITH_PREFIX2}那里\l夺取了{B_LAST_ITEM}！"),
    [STRINGID_TARGETCANTESCAPENOW]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n无法逃走了！"),
    [STRINGID_PKMNFELLINTONIGHTMARE]                = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n开始做恶梦了！"),
    [STRINGID_PKMNLOCKEDINNIGHTMARE]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n正被恶梦缠身！"),
    [STRINGID_PKMNLAIDCURSE]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}削减了自己的体力，\n并向{B_DEF_NAME_WITH_PREFIX2}施加了咒术！"),
    [STRINGID_PKMNAFFLICTEDBYCURSE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n正受到诅咒！"),
    [STRINGID_SPIKESSCATTERED]                      = COMPOUND_STRING("{B_DEF_TEAM2}脚下\n散落着撒菱！"),
    [STRINGID_PKMNHURTBYSPIKES]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n受到了撒菱的伤害！"),
    [STRINGID_PKMNIDENTIFIED]                       = COMPOUND_STRING("识破了{B_DEF_NAME_WITH_PREFIX}的原形！"),
    [STRINGID_PKMNPERISHCOUNTFELL]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的\n灭亡计时变成{B_BUFF1}了！"),
    [STRINGID_PKMNBRACEDITSELF]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n摆出了挺住攻击的架势！"),
    [STRINGID_PKMNENDUREDHIT]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n挺住了攻击！"),
    [STRINGID_MAGNITUDESTRENGTH]                    = COMPOUND_STRING("震级{B_BUFF1}！"),
    [STRINGID_PKMNCUTHPMAXEDATTACK]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n削减了体力并释放了全部力量！"),
    [STRINGID_PKMNCOPIEDSTATCHANGES]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}复制了\n{B_DEF_NAME_WITH_PREFIX2}的能力变化！"),
    [STRINGID_PKMNGOTFREE]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}摆脱了\n{B_BUFF1}！"), //not in gen 5+, generic rapid spin?
    [STRINGID_PKMNSHEDLEECHSEED]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}摆脱了\n寄生种子的束缚！"), //not in gen 5+, generic rapid spin?
    [STRINGID_PKMNBLEWAWAYSPIKES]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n吹飞了撒菱！"), //not in gen 5+, generic rapid spin?
    [STRINGID_PKMNFLEDFROMBATTLE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n脱离了战斗！"),
    [STRINGID_PKMNFORESAWATTACK]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n预知了未来的攻击！"),
    [STRINGID_PKMNTOOKATTACK]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n受到了{B_BUFF1}的攻击！"),
    [STRINGID_PKMNATTACK]                           = COMPOUND_STRING("{B_BUFF1}的攻击！"), //not in gen 5+
    [STRINGID_PKMNCENTERATTENTION]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n变得万众瞩目了！"),
    [STRINGID_PKMNCHARGINGPOWER]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n开始充电了！"),
    [STRINGID_NATUREPOWERTURNEDINTO]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的\n自然之力变成了{B_CURRENT_MOVE}！"),
    [STRINGID_PKMNSTATUSNORMAL]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的\n状态复原了！"),
    [STRINGID_PKMNHASNOMOVESLEFT]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n没有可用来施展的招式！\p"),
    [STRINGID_PKMNSUBJECTEDTOTORMENT]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n遭到了无理取闹！"),
    [STRINGID_PKMNCANTUSEMOVETORMENT]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}遭到了无理取闹，\n因此无法继续使出相同的招式！\p"),
    [STRINGID_PKMNTIGHTENINGFOCUS]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n聚精会神了起来！"),
    [STRINGID_PKMNFELLFORTAUNT]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n中了挑衅！"),
    [STRINGID_PKMNCANTUSEMOVETAUNT]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX2}受到了挑衅，\n无法使出{B_CURRENT_MOVE}！\p"),
    [STRINGID_PKMNREADYTOHELP]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}摆出了\n帮助{B_DEF_NAME_WITH_PREFIX2}的架势！"),
    [STRINGID_PKMNSWITCHEDITEMS]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n互换了各自的道具"),
    [STRINGID_PKMNCOPIEDFOE]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}复制了\n{B_DEF_NAME_WITH_PREFIX2}的特性！"),
    [STRINGID_PKMNWISHCAMETRUE]                     = COMPOUND_STRING("{B_BUFF1}的\n祈愿实现了！"),
    [STRINGID_PKMNPLANTEDROOTS]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n扎下了根！"),
    [STRINGID_PKMNABSORBEDNUTRIENTS]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n从根上吸取了养分！"),
    [STRINGID_PKMNANCHOREDITSELF]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}扎下了根，\n屹立不动！"),
    [STRINGID_PKMNWASMADEDROWSY]                    = COMPOUND_STRING("让{B_DEF_NAME_WITH_PREFIX2}产生睡意了！"),
    [STRINGID_PKMNKNOCKEDOFF]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}拍落了\n{B_DEF_NAME_WITH_PREFIX2}的{B_LAST_ITEM}！"),
    [STRINGID_PKMNSWAPPEDABILITIES]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n互换了各自的特性！"),
    [STRINGID_PKMNSEALEDOPPONENTMOVE]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n封印了对手的招式！"),
    [STRINGID_PKMNCANTUSEMOVESEALED]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}因封印\n而无法使出{B_CURRENT_MOVE}！\p"),
    [STRINGID_PKMNWANTSGRUDGE]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n想向对手施放怨念！"),
    [STRINGID_PKMNLOSTPPGRUDGE]                     = COMPOUND_STRING("因为怨念，{B_ATK_NAME_WITH_PREFIX}失去了\n其招式{B_BUFF1}的所有PP！"),
    [STRINGID_PKMNSHROUDEDITSELF]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n获得了魔法反射的效果！"),
    [STRINGID_PKMNMOVEBOUNCED]                      = COMPOUND_STRING("将{B_EFF_NAME_WITH_PREFIX}的\n{B_CURRENT_MOVE}反射了回去！"),
    [STRINGID_PKMNWAITSFORTARGET]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n正在观察对手的动向！"),
    [STRINGID_PKMNSNATCHEDMOVE]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}抢夺了\n{B_SCR_NAME_WITH_PREFIX2}的招式！"),
    [STRINGID_PKMNMADEITRAIN]                       = COMPOUND_STRING("因{B_SCR_NAME_WITH_PREFIX}的{B_SCR_ABILITY}，\n开始下雨了！"), //not in gen 5+, ability popup
    [STRINGID_PKMNPROTECTEDBY]                      = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n受到了{B_DEF_ABILITY}的保护！"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSUSAGE]                    = COMPOUND_STRING("因{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}，\n{B_ATK_NAME_WITH_PREFIX2}不能使用\l{B_CURRENT_MOVE}！"), //I don't see this in SV text
    [STRINGID_PKMNRESTOREDHPUSING]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n体力回复了！"), //not in gen 5+, ability popup
    [STRINGID_PKMNCHANGEDTYPEWITH]                  = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}\n变成了{B_BUFF1}属性！"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSROMANCEWITH]              = COMPOUND_STRING("因为{B_DEF_ABILITY}，{B_DEF_NAME_WITH_PREFIX}\n不会着迷！"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSCONFUSIONWITH]            = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}不会混乱！"), //not in gen 5+, ability popup
    [STRINGID_PKMNRAISEDFIREPOWERWITH]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n提高了火属性招式的威力！"), //not in gen 5+, ability popup
    [STRINGID_PKMNANCHORSITSELFWITH]                = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n用吸盘吸住了！"), //not in gen 5+, ability popup
    [STRINGID_PKMNCUTSATTACKWITH]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX2}的攻击降低了！"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSSTATLOSSWITH]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n能力不会降低！"), //not in gen 5+, ability popup
    [STRINGID_PKMNHURTSWITH]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n因{B_DEF_NAME_WITH_PREFIX2}的{B_BUFF1}\l而受到了伤害！"),
    [STRINGID_PKMNTRACED]                           = COMPOUND_STRING("复制了{B_BUFF1}的\n{B_BUFF2}！"),
    [STRINGID_STATSHARPLY]                          = gText_StatSharply,
    [STRINGID_STATHARSHLY]                          = COMPOUND_STRING("大幅"),
    [STRINGID_ATTACKERSSTATROSE]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的\n{B_BUFF1}{B_BUFF2}提高了！"),
    [STRINGID_DEFENDERSSTATROSE]                    = gText_DefendersStatRose,
    [STRINGID_SCRIPTINGSTATROSE]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n{B_BUFF1}{B_BUFF2}提高了！"),
    [STRINGID_ATTACKERSSTATFELL]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的\n{B_BUFF1}{B_BUFF2}降低了！"),
    [STRINGID_DEFENDERSSTATFELL]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}的\n{B_BUFF1}{B_BUFF2}降低了！"),
    [STRINGID_CRITICALHIT]                          = COMPOUND_STRING("击中了要害！"),
    [STRINGID_ONEHITKO]                             = COMPOUND_STRING("一击必杀！"),
    [STRINGID_123POOF]                              = COMPOUND_STRING("{PAUSE 32}1，{PAUSE 15}2，{PAUSE 15}……{PAUSE 15}……{PAUSE 15}……{PAUSE 15}{PLAY_SE SE_BALL_BOUNCE_1}空！\p"),
    [STRINGID_ANDELLIPSIS]                          = COMPOUND_STRING("于是……\p"),
    [STRINGID_NOTVERYEFFECTIVE]                     = COMPOUND_STRING("好像效果不好……"),
    [STRINGID_SUPEREFFECTIVE]                       = COMPOUND_STRING("效果绝佳！"),
    [STRINGID_GOTAWAYSAFELY]                        = sText_GotAwaySafely,
    [STRINGID_WILDPKMNFLED]                         = COMPOUND_STRING("{PLAY_SE SE_FLEE}野生的{B_BUFF1}逃走了！"),
    [STRINGID_NORUNNINGFROMTRAINERS]                = COMPOUND_STRING("不行！不能在对战中\n临阵脱逃！\p"),
    [STRINGID_CANTESCAPE]                           = COMPOUND_STRING("无法逃走！\p"),
    [STRINGID_DONTLEAVEBIRCH]                       = COMPOUND_STRING("小田卷博士：别这样丢下我！\p"), //no decapitalize until it is everywhere
    [STRINGID_BUTNOTHINGHAPPENED]                   = COMPOUND_STRING("但是，什么也没有发生！"),
    [STRINGID_BUTITFAILED]                          = COMPOUND_STRING("但是，没有起到效果！！"),
    [STRINGID_ITHURTCONFUSION]                      = COMPOUND_STRING("不知所以地攻击了自己！"),
    [STRINGID_STARTEDTORAIN]                        = COMPOUND_STRING("开始下雨了！"),
    [STRINGID_DOWNPOURSTARTED]                      = COMPOUND_STRING("开始下大雨了！"), // corresponds to DownpourText in pokegold and pokecrystal and is used by Rain Dance in GSC
    [STRINGID_RAINCONTINUES]                        = COMPOUND_STRING("雨一直在下。"), //not in gen 5+
    [STRINGID_DOWNPOURCONTINUES]                    = COMPOUND_STRING("大雨一直在下。"), // unused
    [STRINGID_RAINSTOPPED]                          = COMPOUND_STRING("雨停了！"),
    [STRINGID_SANDSTORMBREWED]                      = COMPOUND_STRING("开始刮沙暴了！"),
    [STRINGID_SANDSTORMRAGES]                       = COMPOUND_STRING("飞沙走石。"),
    [STRINGID_SANDSTORMSUBSIDED]                    = COMPOUND_STRING("沙暴停止了！"),
    [STRINGID_SUNLIGHTGOTBRIGHT]                    = COMPOUND_STRING("日照变强了！"),
    [STRINGID_SUNLIGHTSTRONG]                       = COMPOUND_STRING("阳光很猛烈。"), //not in gen 5+
    [STRINGID_SUNLIGHTFADED]                        = COMPOUND_STRING("日照复原了！"),
    [STRINGID_STARTEDHAIL]                          = COMPOUND_STRING("开始下冰雹了！"),
    [STRINGID_HAILCONTINUES]                        = COMPOUND_STRING("冰雹还在持续。"),
    [STRINGID_HAILSTOPPED]                          = COMPOUND_STRING("冰雹不下了！"),
    [STRINGID_STATCHANGESGONE]                      = COMPOUND_STRING("所有能力都复原了！"),
    [STRINGID_COINSSCATTERED]                       = COMPOUND_STRING("金币散落一地！"),
    [STRINGID_TOOWEAKFORSUBSTITUTE]                 = COMPOUND_STRING("但是，体力已经不够\n放出替身了！"),
    [STRINGID_SHAREDPAIN]                           = COMPOUND_STRING("均分了彼此的体力！"),
    [STRINGID_BELLCHIMED]                           = COMPOUND_STRING("铃声响彻四周！"),
    [STRINGID_FAINTINTHREE]                         = COMPOUND_STRING("听过终焉之歌的宝可梦\n会在3回合后步向终焉！"),
    [STRINGID_NOPPLEFT]                             = COMPOUND_STRING("招式的剩余点数\n已经用完了！\p"), //not in gen 5+
    [STRINGID_BUTNOPPLEFT]                          = COMPOUND_STRING("但是，招式的剩余点数\n已经用完了！"),
    [STRINGID_PLAYERUSEDITEM]                       = COMPOUND_STRING("{B_PLAYER_NAME}\n使用了{B_LAST_ITEM}！"),
    [STRINGID_WALLYUSEDITEM]                        = COMPOUND_STRING("满充使用了{B_LAST_ITEM}！"), //no decapitalize until it is everywhere
    [STRINGID_TRAINERBLOCKEDBALL]                   = COMPOUND_STRING("球被训练家击飞了！"),
    [STRINGID_DONTBEATHIEF]                         = COMPOUND_STRING("拿别人东西的是小偷！"),
    [STRINGID_ITDODGEDBALL]                         = COMPOUND_STRING("它躲开了精灵球！\n这只宝可梦不能被收服！"),
    [STRINGID_PKMNBROKEFREE]                        = COMPOUND_STRING("不行！宝可梦从\n球里挣脱出来了！"),
    [STRINGID_ITAPPEAREDCAUGHT]                     = COMPOUND_STRING("啊啊！\n还以为捉到了！"),
    [STRINGID_AARGHALMOSTHADIT]                     = COMPOUND_STRING("真遗憾！\n差一点就捉到了！"),
    [STRINGID_SHOOTSOCLOSE]                         = COMPOUND_STRING("可惜啊！\n就还差一点点了！"),
    [STRINGID_GOTCHAPKMNCAUGHTPLAYER]               = COMPOUND_STRING("太好了！捉到{B_DEF_NAME}了！{WAIT_SE}{PLAY_BGM MUS_CAUGHT}\p"),
    [STRINGID_GOTCHAPKMNCAUGHTWALLY]                = COMPOUND_STRING("太好了！捉到{B_DEF_NAME}了！{WAIT_SE}{PLAY_BGM MUS_CAUGHT}{PAUSE 127}"),
    [STRINGID_GIVENICKNAMECAPTURED]                 = COMPOUND_STRING("要给{B_DEF_NAME}\n起昵称吗？"),
    [STRINGID_PKMNDATAADDEDTODEX]                   = COMPOUND_STRING("{B_DEF_NAME}的资料被\n新添加到宝可梦图鉴里了！\p"),
    [STRINGID_ITISRAINING]                          = COMPOUND_STRING("现在正在下雨！"),
    [STRINGID_SANDSTORMISRAGING]                    = COMPOUND_STRING("现在正在刮沙暴！"),
    [STRINGID_CANTESCAPE2]                          = COMPOUND_STRING("无法逃走！\p"),
    [STRINGID_PKMNIGNORESASLEEP]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}仍在睡觉，\n没有服从命令！"),
    [STRINGID_PKMNIGNOREDORDERS]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}没有服从命令！"),
    [STRINGID_PKMNBEGANTONAP]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}开始睡午觉了！"),
    [STRINGID_PKMNLOAFING]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}在偷懒！"),
    [STRINGID_PKMNWONTOBEY]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}不听话！"),
    [STRINGID_PKMNTURNEDAWAY]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}把头转向了一旁！"),
    [STRINGID_PKMNPRETENDNOTNOTICE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}在装傻！"),
    [STRINGID_ENEMYABOUTTOSWITCHPKMN]               = COMPOUND_STRING("{B_TRAINER1_NAME_WITH_CLASS}\n正准备派出{B_BUFF2}。\p要替换宝可梦吗？"),
    [STRINGID_CREPTCLOSER]                          = COMPOUND_STRING("{B_PLAYER_NAME}悄悄靠近了\n{B_OPPONENT_MON1_NAME}！"), //safari
    [STRINGID_CANTGETCLOSER]                        = COMPOUND_STRING("{B_PLAYER_NAME}不能再靠近了！"), //safari
    [STRINGID_PKMNWATCHINGCAREFULLY]                = COMPOUND_STRING("{B_OPPONENT_MON1_NAME}正在观察状况！"), //safari
    [STRINGID_PKMNCURIOUSABOUTX]                    = COMPOUND_STRING("{B_OPPONENT_MON1_NAME}对\n{B_BUFF1}感到好奇！"), //safari
    [STRINGID_PKMNENTHRALLEDBYX]                    = COMPOUND_STRING("{B_OPPONENT_MON1_NAME}被\n{B_BUFF1}深深吸引！"), //safari
    [STRINGID_PKMNIGNOREDX]                         = COMPOUND_STRING("{B_OPPONENT_MON1_NAME}完全忽视了\n{B_BUFF1}！"), //safari
    [STRINGID_THREWPOKEBLOCKATPKMN]                 = COMPOUND_STRING("{B_PLAYER_NAME}朝{B_OPPONENT_MON1_NAME}\n投掷了{POKEBLOCK}！"), //safari
    [STRINGID_OUTOFSAFARIBALLS]                     = COMPOUND_STRING("{PLAY_SE SE_DING_DONG}叮咚！时间到。\n狩猎游戏到此为止。\p"), //safari
    [STRINGID_PKMNSITEMCUREDPARALYSIS]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}用{B_LAST_ITEM}\n治愈了麻痹！"),
    [STRINGID_PKMNSITEMCUREDPOISON]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}用{B_LAST_ITEM}\n治愈了中毒！"),
    [STRINGID_PKMNSITEMHEALEDBURN]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}用{B_LAST_ITEM}\n治愈了灼伤！"),
    [STRINGID_PKMNSITEMDEFROSTEDIT]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}用{B_LAST_ITEM}\n治愈了冰冻状态！"),
    [STRINGID_PKMNSITEMWOKEIT]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}用{B_LAST_ITEM}\n让自己醒过来了！"),
    [STRINGID_PKMNSITEMSNAPPEDOUT]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}用{B_LAST_ITEM}\n治愈了混乱！"),
    [STRINGID_PKMNSITEMCUREDPROBLEM]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}用{B_LAST_ITEM}\n治愈了{B_BUFF1}状态！"),
    [STRINGID_PKMNSITEMRESTOREDHEALTH]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}用{B_LAST_ITEM}\n回复了体力！"),
    [STRINGID_PKMNSITEMRESTOREDPP]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}用{B_LAST_ITEM}\n回复了{B_BUFF1}的PP！"),
    [STRINGID_PKMNSITEMRESTOREDSTATUS]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}用{B_LAST_ITEM}\n复原了能力！"),
    [STRINGID_PKMNSITEMRESTOREDHPALITTLE]           = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}用{B_LAST_ITEM}\n回复了少许HP。"),
    [STRINGID_ITEMALLOWSONLYYMOVE]                  = COMPOUND_STRING("因为{B_LAST_ITEM}的效果，\n只能使出{B_CURRENT_MOVE}！\p"),
    [STRINGID_PKMNHUNGONWITHX]                      = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n用{B_LAST_ITEM}撑住了！"),
    [STRINGID_EMPTYSTRING3]                         = gText_EmptyString3,
    [STRINGID_PKMNSXRESTOREDHPALITTLE2]             = COMPOUND_STRING("因为{B_ATK_ABILITY}，{B_ATK_NAME_WITH_PREFIX}\n回复了少许HP。"),
    [STRINGID_PKMNSXWHIPPEDUPSANDSTORM]             = COMPOUND_STRING("因{B_SCR_NAME_WITH_PREFIX}的{B_SCR_ABILITY}，\n开始刮沙暴了！"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXPREVENTSYLOSS]                  = COMPOUND_STRING("因为{B_SCR_ABILITY}，{B_SCR_NAME_WITH_PREFIX}的\n{B_BUFF1}不会降低！"),
    [STRINGID_PKMNSXINFATUATEDY]                    = COMPOUND_STRING("因{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}，\n{B_ATK_NAME_WITH_PREFIX2}着迷了！"),
    [STRINGID_PKMNSXMADEYINEFFECTIVE]               = COMPOUND_STRING("因{B_SCR_NAME_WITH_PREFIX}的{B_SCR_ABILITY}，\n{B_CURRENT_MOVE}无效了！"),
    [STRINGID_ITSUCKEDLIQUIDOOZE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n吸到了污泥浆！"),
    [STRINGID_PKMNTRANSFORMED]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n样子发生了变化！"),
    [STRINGID_ELECTRICITYWEAKENED]                  = COMPOUND_STRING("电气的威力减弱了！"),
    [STRINGID_FIREWEAKENED]                         = COMPOUND_STRING("火焰的威力减弱了！"),
    [STRINGID_PKMNHIDUNDERWATER]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n潜入了水中！"),
    [STRINGID_PKMNSPRANGUP]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n高高地跳了起来！"),
    [STRINGID_HMMOVESCANTBEFORGOTTEN]               = COMPOUND_STRING("暂时无法忘记秘传招式。\p"),
    [STRINGID_XFOUNDONEY]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n捡来了{B_LAST_ITEM}！"),
    [STRINGID_PLAYERDEFEATEDTRAINER1]               = sText_PlayerDefeatedLinkTrainerTrainer1,
    [STRINGID_SOOTHINGAROMA]                        = COMPOUND_STRING("怡人的香气扩散了开来！"),
    [STRINGID_ITEMSCANTBEUSEDNOW]                   = COMPOUND_STRING("现在不能使用道具。{PAUSE 64}"), //not in gen 5+, i think
    [STRINGID_USINGITEMSTATOFPKMNROSE]              = COMPOUND_STRING("因为{B_LAST_ITEM}，{B_SCR_NAME_WITH_PREFIX}的\n{B_BUFF1}{B_BUFF2}提高了！"), //todo: update this, will require code changes
    [STRINGID_USINGITEMSTATOFPKMNFELL]              = COMPOUND_STRING("因为{B_LAST_ITEM}，{B_SCR_NAME_WITH_PREFIX}的\n{B_BUFF1}{B_BUFF2}降低了！"),
    [STRINGID_PKMNUSEDXTOGETPUMPED]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n使用了{B_LAST_ITEM}，拿出了干劲！"),
    [STRINGID_PKMNSXMADEYUSELESS]                   = COMPOUND_STRING("因{B_SCR_NAME_WITH_PREFIX}的{B_SCR_ABILITY}，\n{B_CURRENT_MOVE}无效了！"), //not in gen 5+, ability popup
    [STRINGID_PKMNTRAPPEDBYSANDTOMB]                = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}\n陷入了流沙地狱！"),
    [STRINGID_EMPTYSTRING4]                         = COMPOUND_STRING(""),
    [STRINGID_ABOOSTED]                             = COMPOUND_STRING("较为多的"),
    [STRINGID_PKMNSXINTENSIFIEDSUN]                 = COMPOUND_STRING("因{B_SCR_NAME_WITH_PREFIX}的{B_SCR_ABILITY}，\n日照变强了！"), //not in gen 5+, ability popup
    [STRINGID_YOUTHROWABALLNOWRIGHT]                = COMPOUND_STRING("应该是在这里扔精灵球的吧……\n我……试试看吧！"),
    [STRINGID_PKMNSXTOOKATTACK]                     = COMPOUND_STRING("因为{B_DEF_ABILITY}，{B_DEF_NAME_WITH_PREFIX}\n吸引了攻击！"), //In gen 5+ but without naming the ability
    [STRINGID_PKMNCHOSEXASDESTINY]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n将破灭之愿托付给了未来！"),
    [STRINGID_PKMNLOSTFOCUS]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}聚气时\n受到干扰，无法使出招式！"),
    [STRINGID_USENEXTPKMN]                          = COMPOUND_STRING("要替换宝可梦吗？"),
    [STRINGID_PKMNFLEDUSINGITS]                     = COMPOUND_STRING("{PLAY_SE SE_FLEE}{B_ATK_NAME_WITH_PREFIX}\n使用其所携带的{B_LAST_ITEM}逃走了！\p"),
    [STRINGID_PKMNFLEDUSING]                        = COMPOUND_STRING("{PLAY_SE SE_FLEE}{B_ATK_NAME_WITH_PREFIX}\n使用{B_ATK_ABILITY}逃走了！\p"), //not in gen 5+
    [STRINGID_PKMNWASDRAGGEDOUT]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n被拖进了战斗！\p"),
    [STRINGID_PKMNSITEMNORMALIZEDSTATUS]            = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}用{B_LAST_ITEM}\n治愈了异常状态！"),
    [STRINGID_TRAINER1USEDITEM]                     = COMPOUND_STRING("{B_ATK_TRAINER_NAME_WITH_CLASS}\n使用了{B_LAST_ITEM}！"),
    [STRINGID_BOXISFULL]                            = COMPOUND_STRING("盒子已满，\n无法再进行捕捉！\p"),
    [STRINGID_PKMNAVOIDEDATTACK]                    = COMPOUND_STRING("没有击中{B_SCR_NAME_WITH_PREFIX}！"),
    [STRINGID_PKMNSXMADEITINEFFECTIVE]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的{B_SCR_ABILITY}\n无法移除！"), //not in gen 5+, ability popup TODO：奇怪的改动
    [STRINGID_PKMNSXPREVENTSFLINCHING]              = COMPOUND_STRING("因为{B_EFF_ABILITY}，{B_EFF_NAME_WITH_PREFIX}\n不会畏缩！"), //not in gen 5+, ability popup
    [STRINGID_PKMNALREADYHASBURN]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n已经被灼伤了。"),
    [STRINGID_STATSWONTDECREASE2]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}的\n能力已经无法再降低了！"),
    [STRINGID_PKMNSXBLOCKSY]                        = COMPOUND_STRING("因为{B_SCR_ABILITY}，{B_SCR_NAME_WITH_PREFIX}\n抵御了{B_CURRENT_MOVE}！"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXWOREOFF]                        = COMPOUND_STRING("{B_ATK_TEAM1}的{B_BUFF1}消失了！"),
    [STRINGID_THEWALLSHATTERED]                     = COMPOUND_STRING("墙壁碎掉了！"), //not in gen5+, uses "your teams light screen wore off!" etc instead
    [STRINGID_PKMNSXCUREDITSYPROBLEM]               = COMPOUND_STRING("因为{B_SCR_ABILITY}，{B_SCR_NAME_WITH_PREFIX}的\n{B_BUFF1}状态治愈了！"), //not in gen 5+, ability popup
    [STRINGID_ATTACKERCANTESCAPE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n无法逃走！"),
    [STRINGID_PKMNOBTAINEDX]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n获得了{B_BUFF1}！"),
    [STRINGID_PKMNOBTAINEDX2]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n获得了{B_BUFF2}！"),
    [STRINGID_PKMNOBTAINEDXYOBTAINEDZ]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n获得了{B_BUFF1}！\p{B_DEF_NAME_WITH_PREFIX}\n获得了{B_BUFF2}！"),
    [STRINGID_BUTNOEFFECT]                          = COMPOUND_STRING("但是，没有效果！"),
    [STRINGID_TWOENEMIESDEFEATED]                   = sText_TwoInGameTrainersDefeated,
    [STRINGID_TRAINER2LOSETEXT]                     = COMPOUND_STRING("{B_TRAINER2_LOSE_TEXT}"),
    [STRINGID_PKMNINCAPABLEOFPOWER]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n似乎无法发挥自身的力量！"),
    [STRINGID_GLINTAPPEARSINEYE]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX2}的眼中\n闪过光芒！"),
    [STRINGID_PKMNGETTINGINTOPOSITION]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}正在就位！"),
    [STRINGID_PKMNBEGANGROWLINGDEEPLY]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}开始低吼！"),
    [STRINGID_PKMNEAGERFORMORE]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}意犹未尽！"),
    [STRINGID_DEFEATEDOPPONENTBYREFEREE]            = COMPOUND_STRING("根据判定的准则，\n{B_PLAYER_MON1_NAME}\l战胜了{B_OPPONENT_MON1_NAME}！"),
    [STRINGID_LOSTTOOPPONENTBYREFEREE]              = COMPOUND_STRING("根据判定的准则，\n{B_PLAYER_MON1_NAME}\l败给了{B_OPPONENT_MON1_NAME}！"),
    [STRINGID_TIEDOPPONENTBYREFEREE]                = COMPOUND_STRING("根据判定的准则，\n{B_PLAYER_MON1_NAME}\l和{B_OPPONENT_MON1_NAME}打成了平局！"),
    [STRINGID_QUESTIONFORFEITMATCH]                 = COMPOUND_STRING("确定要投降\n并中止这次挑战吗？"),
    [STRINGID_FORFEITEDMATCH]                       = COMPOUND_STRING("{B_PLAYER_NAME}选择了投降！"),
    [STRINGID_PKMNTRANSFERREDSOMEONESPC]            = gText_PkmnTransferredSomeonesPC,
    [STRINGID_PKMNTRANSFERREDLANETTESPC]            = gText_PkmnTransferredLanettesPC,
    [STRINGID_PKMNBOXSOMEONESPCFULL]                = gText_PkmnTransferredSomeonesPCBoxFull,
    [STRINGID_PKMNBOXLANETTESPCFULL]                = gText_PkmnTransferredLanettesPCBoxFull,
    [STRINGID_TRAINER1WINTEXT]                      = COMPOUND_STRING("{B_TRAINER1_WIN_TEXT}"),
    [STRINGID_TRAINER2WINTEXT]                      = COMPOUND_STRING("{B_TRAINER2_WIN_TEXT}"),
    [STRINGID_ENDUREDSTURDY]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n因{B_DEF_ABILITY}挺住了攻击！"),
    [STRINGID_POWERHERB]                            = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}用了{B_LAST_ITEM}后，\n充满了力量！"),
    [STRINGID_HURTBYITEM]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}因{B_LAST_ITEM}\n而受到了伤害！"),
    [STRINGID_GRAVITYINTENSIFIED]                   = COMPOUND_STRING("重力变强了！"),
    [STRINGID_TARGETWOKEUP]                         = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}\n醒过来了！"),
    [STRINGID_TAILWINDBLEW]                         = COMPOUND_STRING("从{B_ATK_TEAM2}身后\n吹起了顺风！"),
    [STRINGID_PKMNWENTBACK]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n要回到{B_ATK_TRAINER_NAME}的身边了！"),
    [STRINGID_PKMNCANTUSEITEMSANYMORE]              = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n无法使用道具了！"),
    [STRINGID_PKMNFLUNG]                            = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}\n投掷了{B_LAST_ITEM}！"),
    [STRINGID_PKMNPREVENTEDFROMHEALING]             = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}的\n回复行为被封住了！"),
    [STRINGID_PKMNSWITCHEDATKANDDEF]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n互换了攻击和防御！"),
    [STRINGID_PKMNSABILITYSUPPRESSED]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}的特性\n变得无效了！"),
    [STRINGID_SHIELDEDFROMCRITICALHITS]             = COMPOUND_STRING("因幸运咒语的力量，\n{B_ATK_TEAM2}的要害被隐藏了起来！"),
    [STRINGID_PKMNACQUIREDABILITY]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}的特性\n变为{B_DEF_ABILITY}了！"),
    [STRINGID_POISONSPIKESSCATTERED]                = COMPOUND_STRING("{B_DEF_TEAM2}脚下\n散落着毒菱！"),
    [STRINGID_PKMNSWITCHEDSTATCHANGES]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}和对手互换了\n自己的能力变化！"),
    [STRINGID_PKMNSURROUNDEDWITHVEILOFWATER]        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n套上了水环！"),
    [STRINGID_PKMNLEVITATEDONELECTROMAGNETISM]      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n因电磁力浮了起来！"),
    [STRINGID_PKMNTWISTEDDIMENSIONS]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n扭曲了时空！"),
    [STRINGID_POINTEDSTONESFLOAT]                   = COMPOUND_STRING("{B_DEF_TEAM2}周围开始浮现出\n尖锐的岩石！"),
    [STRINGID_TRAPPEDBYSWIRLINGMAGMA]               = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}\n被困在了熔岩旋涡之中！"),
    [STRINGID_VANISHEDINSTANTLY]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的身影\n瞬间消失了！"),
    [STRINGID_PROTECTEDTEAM]                        = COMPOUND_STRING("{B_ATK_TEAM2}周围正受到\n{B_CURRENT_MOVE}的保护！"),
    [STRINGID_SHAREDITSGUARD]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n平分了各自的防守"),
    [STRINGID_SHAREDITSPOWER]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n平分了各自的力量！"),
    [STRINGID_SWAPSDEFANDSPDEFOFALLPOKEMON]         = COMPOUND_STRING("凭空制造出了互换\n防御和特防的空间！"),
    [STRINGID_BECAMENIMBLE]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n变得身轻如燕了！"),
    [STRINGID_HURLEDINTOTHEAIR]                     = COMPOUND_STRING("让{B_DEF_NAME_WITH_PREFIX}\n浮在了空中！"),
    [STRINGID_HELDITEMSLOSEEFFECTS]                 = COMPOUND_STRING("凭空制造出了会让持有道具的\n效果消失的空间！"),
    [STRINGID_FELLSTRAIGHTDOWN]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n被击落，掉到了地面！"),
    [STRINGID_TARGETCHANGEDTYPE]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n变成了{B_BUFF1}属性！"),
    [STRINGID_KINDOFFER]                            = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n接受了对手的好意！"),
    [STRINGID_RESETSTARGETSSTATLEVELS]              = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}的\n能力变化消失了！"),
    [STRINGID_ALLYSWITCHPOSITION]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}和\n{B_SCR_NAME_WITH_PREFIX2}互换了场地！"),
    [STRINGID_REFLECTTARGETSTYPE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}变成了和\n{B_DEF_NAME_WITH_PREFIX2}相同的属性！"),
    [STRINGID_EMBARGOENDS]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n变得可以使用道具了！"),
    [STRINGID_ELECTROMAGNETISM]                     = COMPOUND_STRING("电磁力"),
    [STRINGID_BUFFERENDS]                           = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n{B_BUFF1}消失了！"),
    [STRINGID_TELEKINESISENDS]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n摆脱了意念移物！"),
    [STRINGID_TAILWINDENDS]                         = COMPOUND_STRING("{B_ATK_TEAM1}的顺风停止了！"),
    [STRINGID_LUCKYCHANTENDS]                       = COMPOUND_STRING("{B_ATK_TEAM1}的幸运咒语解除了！"),
    [STRINGID_TRICKROOMENDS]                        = COMPOUND_STRING("扭曲的时空复原了！"),
    [STRINGID_WONDERROOMENDS]                       = COMPOUND_STRING("奇妙空间被解除，\n防御和特防复原了！"),
    [STRINGID_MAGICROOMENDS]                        = COMPOUND_STRING("魔法空间被解除，\n道具的效果复原了！"),
    [STRINGID_MUDSPORTENDS]                         = COMPOUND_STRING("玩泥巴的效果消失了！"),
    [STRINGID_WATERSPORTENDS]                       = COMPOUND_STRING("玩水的效果消失了！"),
    [STRINGID_GRAVITYENDS]                          = COMPOUND_STRING("重力复原了！"),
    [STRINGID_AQUARINGHEAL]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX2}\n通过水环回复体力！"),
    [STRINGID_ELECTRICTERRAINENDS]                  = COMPOUND_STRING("脚下的电光消失不见了！"),
    [STRINGID_MISTYTERRAINENDS]                     = COMPOUND_STRING("脚下的雾气消失不见了！"),
    [STRINGID_PSYCHICTERRAINENDS]                   = COMPOUND_STRING("脚下的奇妙感觉消失了！"),
    [STRINGID_GRASSYTERRAINENDS]                    = COMPOUND_STRING("脚下的青草消失不见了！"),
    [STRINGID_TARGETABILITYSTATRAISE]               = COMPOUND_STRING("因为{B_DEF_ABILITY}，\n{B_DEF_NAME_WITH_PREFIX}的{B_BUFF1}{B_BUFF2}提高了！"), // Not in Gen 5+
    [STRINGID_TARGETSSTATWASMAXEDOUT]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}的{B_DEF_ABILITY}\n攻击被提高到了最大！"),
    [STRINGID_ATTACKERABILITYSTATRAISE]             = COMPOUND_STRING("因为{B_ATK_ABILITY}，\n{B_ATK_NAME_WITH_PREFIX}的{B_BUFF1}{B_BUFF2}提高了！"), // Not in Gen 5+
    [STRINGID_POISONHEALHPUP]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX2}\n利用毒素回复了体力！"),  // Not in Gen 5+
    [STRINGID_BADDREAMSDMG]                         = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n正被恶梦缠身！"),
    [STRINGID_MOLDBREAKERENTERS]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n打破了常规！"),
    [STRINGID_TERAVOLTENTERS]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n正在释放溅射气场！"),
    [STRINGID_TURBOBLAZEENTERS]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n正在释放炽焰气场！"),
    [STRINGID_SLOWSTARTENTERS]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n无法拿出平时的水平！"),
    [STRINGID_SLOWSTARTEND]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n恢复了平时的水平！"),
    [STRINGID_SOLARPOWERHPDROP]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}因{B_ATK_ABILITY}\n削减了体力！"),  // Not in Gen 5+
    [STRINGID_AFTERMATHDMG]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n受伤了！"),
    [STRINGID_ANTICIPATIONACTIVATES]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n发抖了！"),
    [STRINGID_FOREWARNACTIVATES]                    = COMPOUND_STRING("因{B_SCR_ABILITY}，{B_SCR_NAME_WITH_PREFIX2}察觉到了\n{B_EFF_NAME_WITH_PREFIX2}的{B_BUFF1}！"),
    [STRINGID_ICEBODYHPGAIN]                        = COMPOUND_STRING("因为{B_ATK_ABILITY}，\n{B_ATK_NAME_WITH_PREFIX}回复了少许HP。"), //don't think this message is displayed anymore
    [STRINGID_SNOWWARNINGHAIL]                      = COMPOUND_STRING("开始下冰雹了！"),
    [STRINGID_FRISKACTIVATES]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}察觉到了\n{B_DEF_NAME_WITH_PREFIX2}的{B_LAST_ITEM}！"),
    [STRINGID_UNNERVEENTERS]                        = COMPOUND_STRING("{B_EFF_TEAM1}因太紧张\n而无法食用树果！"),
    [STRINGID_HARVESTBERRY]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n收获了{B_LAST_ITEM}！"),
    [STRINGID_PROTEANTYPECHANGE]                    = COMPOUND_STRING("因为{B_ATK_ABILITY}，\n{B_ATK_NAME_WITH_PREFIX}变成了{B_BUFF1}属性！"),
    [STRINGID_SYMBIOSISITEMPASS]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}将{B_LAST_ITEM}\n传给了{B_EFF_NAME_WITH_PREFIX2}！"),
    [STRINGID_STEALTHROCKDMG]                       = COMPOUND_STRING("尖锐的岩石扎进了\n{B_SCR_NAME_WITH_PREFIX2}的体内！"),
    [STRINGID_TOXICSPIKESABSORBED]                  = COMPOUND_STRING("{B_EFF_TEAM2}脚下的\n毒菱消失不见了！"),
    [STRINGID_TOXICSPIKESPOISONED]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}中毒了！"),
    [STRINGID_TOXICSPIKESBADLYPOISONED]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}中剧毒了！"),
    [STRINGID_STICKYWEBSWITCHIN]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n被黏黏网粘住了！"),
    [STRINGID_HEALINGWISHCAMETRUE]                  = COMPOUND_STRING("治愈之愿\n在{B_SCR_NAME_WITH_PREFIX2}身上实现了！"),
    [STRINGID_HEALINGWISHHEALED]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n体力回复了！"),
    [STRINGID_LUNARDANCECAMETRUE]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n被神秘的月光包围了！"),
    [STRINGID_CURSEDBODYDISABLED]                    = COMPOUND_STRING("因{B_DEF_NAME_WITH_PREFIX2}的{B_DEF_ABILITY}，\n封住了{B_ATK_NAME_WITH_PREFIX}的\l{B_BUFF1}！"),
    [STRINGID_ATTACKERACQUIREDABILITY]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的特性\n变为{B_LAST_ABILITY}了！"), // Not in Gen 5+
    [STRINGID_TARGETABILITYSTATLOWER]               = COMPOUND_STRING("因为{B_DEF_ABILITY}，\n{B_DEF_NAME_WITH_PREFIX}的{B_BUFF1}{B_BUFF2}降低了！"), // Not in Gen 5+
    [STRINGID_TARGETSTATWONTGOHIGHER]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}的\n{B_BUFF1}已经无法再提高了！"),
    [STRINGID_PKMNMOVEBOUNCEDABILITY]               = COMPOUND_STRING("因{B_DEF_NAME_WITH_PREFIX2}的{B_DEF_ABILITY}，\n将{B_ATK_NAME_WITH_PREFIX}的\l{B_CURRENT_MOVE}反射了回去！"),
    [STRINGID_IMPOSTERTRANSFORM]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}因{B_LAST_ABILITY}\n变成了{B_DEF_NAME_WITH_PREFIX2}！"),
    [STRINGID_ASSAULTVESTDOESNTALLOW]               = COMPOUND_STRING("因为{B_LAST_ITEM}的效果，\n无法使出变化招式！\p"),
    [STRINGID_GRAVITYPREVENTSUSAGE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}因重力太强\n而无法使出{B_CURRENT_MOVE}！\p"),
    [STRINGID_HEALBLOCKPREVENTSUSAGE]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n因回复封锁而无法回复！\p"),
    [STRINGID_NOTDONEYET]                           = COMPOUND_STRING("这个招式的效果还没完成！\p"),
    [STRINGID_STICKYWEBUSED]                        = COMPOUND_STRING("{B_DEF_TEAM2}的脚下\n延伸出了黏黏网！"),
    [STRINGID_QUASHSUCCESS]                         = COMPOUND_STRING("延后了{B_DEF_NAME_WITH_PREFIX}的顺序！"),
    [STRINGID_PKMNBLEWAWAYTOXICSPIKES]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n吹飞了毒菱！"),
    [STRINGID_PKMNBLEWAWAYSTICKYWEB]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n吹飞了黏黏网！"),
    [STRINGID_PKMNBLEWAWAYSTEALTHROCK]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n吹飞了隐形岩！"),
    [STRINGID_IONDELUGEON]                          = COMPOUND_STRING("等离子雨倾盆而下！"),
    [STRINGID_TOPSYTURVYSWITCHEDSTATS]              = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX2}的\n能力变化颠倒过来了！"),
    [STRINGID_TERRAINBECOMESMISTY]                  = COMPOUND_STRING("脚下雾气缭绕！"),
    [STRINGID_TERRAINBECOMESGRASSY]                 = COMPOUND_STRING("脚下青草如茵！"),
    [STRINGID_TERRAINBECOMESELECTRIC]               = COMPOUND_STRING("脚下电光飞闪！"),
    [STRINGID_TERRAINBECOMESPSYCHIC]                = COMPOUND_STRING("脚下传来了奇妙的感觉！"),
    [STRINGID_TARGETELECTRIFIED]                    = COMPOUND_STRING("因为输电，{B_DEF_NAME_WITH_PREFIX}的\n招式变成了电属性！"),
    [STRINGID_MEGAEVOREACTING]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的{B_LAST_ITEM}和\n{B_ATK_TRAINER_NAME}的超级环起了反应！"), //actually displays the type of mega ring in inventory, but we didnt implement them :(
    [STRINGID_MEGAEVOEVOLVED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}超级进化成了\n超级{B_BUFF1}！"),
    [STRINGID_DRASTICALLY]                          = gText_drastically,
    [STRINGID_SEVERELY]                             = gText_severely,
    [STRINGID_INFESTATION]                          = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}受到了\n{B_ATK_NAME_WITH_PREFIX2}的死缠烂打！"),
    [STRINGID_NOEFFECTONTARGET]                     = COMPOUND_STRING("对于{B_DEF_NAME_WITH_PREFIX2}没有效果！"),
    [STRINGID_BURSTINGFLAMESHIT]                    = COMPOUND_STRING("爆裂出的火焰溅到了\n{B_EFF_NAME_WITH_PREFIX2}！"),
    [STRINGID_BESTOWITEMGIVING]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}从{B_ATK_NAME_WITH_PREFIX2}\n那里获得了{B_LAST_ITEM}！"),
    [STRINGID_THIRDTYPEADDED]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX2}\n增加了{B_BUFF1}属性！"),
    [STRINGID_FELLFORFEINT]                         = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}\n中了佯攻！"),
    [STRINGID_POKEMONCANNOTUSEMOVE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n无法使用{B_CURRENT_MOVE}！"),
    [STRINGID_COVEREDINPOWDER]                      = COMPOUND_STRING("向{B_DEF_NAME_WITH_PREFIX}\n抛洒了粉尘！"),
    [STRINGID_POWDEREXPLODES]                       = COMPOUND_STRING("和火焰起了反应，\n粉尘爆炸了！"),
    [STRINGID_BELCHCANTSELECT]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n因没有吃树果而无法使出招式！\p"),
    [STRINGID_SPECTRALTHIEFSTEAL]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n夺取了提高的那部分能力！"),
    [STRINGID_GRAVITYGROUNDING]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n因受到重力影响而无法待在空中！"),
    [STRINGID_MISTYTERRAINPREVENTS]                 = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n正受到薄雾场地的保护！"),
    [STRINGID_GRASSYTERRAINHEALS]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n因青草场地回复了体力！"),
    [STRINGID_ELECTRICTERRAINPREVENTS]              = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n正受到电气场地的保护！"),
    [STRINGID_PSYCHICTERRAINPREVENTS]               = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n正受到精神场地的保护！"),
    [STRINGID_SAFETYGOGGLESPROTECTED]               = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n因{B_LAST_ITEM}而不会受到影响！"),
    [STRINGID_FLOWERVEILPROTECTED]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n正受到花幕的保护！"),
    [STRINGID_AROMAVEILPROTECTED]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n正受到芳香幕的保护！"),
    [STRINGID_CELEBRATEMESSAGE]                     = COMPOUND_STRING("恭喜恭喜！\n{B_PLAYER_NAME}！"),
    [STRINGID_USEDINSTRUCTEDMOVE]                   = COMPOUND_STRING("根据{B_ATK_NAME_WITH_PREFIX2}的指示，\n{B_DEF_NAME_WITH_PREFIX}使出了招式！"),
    [STRINGID_THROATCHOPENDS]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n变得可以使出声音的招式了！"),
    [STRINGID_PKMNCANTUSEMOVETHROATCHOP]            = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX2}\n因深渊突刺的效果无法使出招式！\p"),
    [STRINGID_LASERFOCUS]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n磨砺了精神！"),
    [STRINGID_GEMACTIVATES]                         = COMPOUND_STRING("{B_LAST_ITEM}加强了\n{B_ATK_NAME_WITH_PREFIX2}的威力！"),
    [STRINGID_BERRYDMGREDUCES]                      = COMPOUND_STRING("{B_LAST_ITEM}减轻了\n对{B_SCR_NAME_WITH_PREFIX2}造成的伤害！"),
    [STRINGID_AIRBALLOONFLOAT]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX2}\n靠着气球浮在了空中！"),
    [STRINGID_AIRBALLOONPOP]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}的\n气球破了！"),
    [STRINGID_INCINERATEBURN]                       = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}的\n{B_LAST_ITEM}被烧没了！"),
    [STRINGID_BUGBITE]                              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}夺取\n并吃掉了{B_LAST_ITEM}！"),
    [STRINGID_ILLUSIONWOREOFF]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}造成的\n幻觉被解除了！"),
    [STRINGID_ATTACKERCUREDTARGETSTATUS]            = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n治愈了{B_DEF_NAME_WITH_PREFIX2}的异常状态！"),
    [STRINGID_ATTACKERLOSTFIRETYPE]                 = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}的火焰燃尽了！"),
    [STRINGID_HEALERCURE]                           = COMPOUND_STRING("因为{B_ATK_NAME_WITH_PREFIX}，\n{B_SCR_NAME_WITH_PREFIX2}的异常状态治愈了！"),
    [STRINGID_SCRIPTINGABILITYSTATRAISE]            = COMPOUND_STRING("因为{B_SCR_ABILITY}，\n{B_SCR_NAME_WITH_PREFIX}的{B_BUFF1}{B_BUFF2}提高了！"),
    [STRINGID_RECEIVERABILITYTAKEOVER]              = COMPOUND_STRING("继承了{B_SCR_NAME_WITH_PREFIX}的\n{B_SCR_ABILITY}！"),
    [STRINGID_PKNMABSORBINGPOWER]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n正在积蓄力量！"),
    [STRINGID_NOONEWILLBEABLETORUNAWAY]             = COMPOUND_STRING("下回合无法逃走！"),
    [STRINGID_DESTINYKNOTACTIVATES]                 = COMPOUND_STRING("{B_LAST_ITEM}让{B_DEF_NAME_WITH_PREFIX}\n着迷了！"),
    [STRINGID_CLOAKEDINAFREEZINGLIGHT]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n被冷光包围了！"),
    [STRINGID_CLEARAMULETWONTLOWERSTATS]            = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX2}的\n能力因{B_LAST_ITEM}不会降低！"),
    [STRINGID_FERVENTWISHREACHED]                   = COMPOUND_STRING("{B_ATK_TRAINER_NAME}衷心的祈愿\n传递到了{B_ATK_NAME_WITH_PREFIX2}那里！"),
    [STRINGID_AIRLOCKACTIVATES]                     = COMPOUND_STRING("天气的影响消失了！"),
    [STRINGID_PRESSUREENTERS]                       = COMPOUND_STRING("从{B_SCR_NAME_WITH_PREFIX}的身上\n感到了一种压迫感！"),
    [STRINGID_DARKAURAENTERS]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n正在释放暗黑气场！"),
    [STRINGID_FAIRYAURAENTERS]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n正在释放妖精气场！"),
    [STRINGID_AURABREAKENTERS]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n压制了所有气场！"),
    [STRINGID_COMATOSEENTERS]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n处于半梦半醒状态！"),
    [STRINGID_SCREENCLEANERENTERS]                  = COMPOUND_STRING("双方场上的反射壁、光墙\n和极光幕消失了！"),
    [STRINGID_FETCHEDPOKEBALL]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n捡来了{B_LAST_ITEM}！"),
    [STRINGID_ASANDSTORMKICKEDUP]                   = COMPOUND_STRING("开始刮沙暴了！"),
    [STRINGID_PKMNSWILLPERISHIN3TURNS]              = COMPOUND_STRING("双方将在3回合后灭亡！"), 
    [STRINGID_AURAFLAREDTOLIFE]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}让气场覆盖全身！"),
    [STRINGID_ASONEENTERS]                          = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n同时拥有了两种特性！"),
    [STRINGID_CURIOUSMEDICINEENTERS]                = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}的\n能力变化消失了！"),
    [STRINGID_CANACTFASTERTHANKSTO]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}用了{B_BUFF1}后，\n行动变快了！"),
    [STRINGID_MICLEBERRYACTIVATES]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}用{B_LAST_ITEM}\n提高了命中率！"),
    [STRINGID_PKMNSHOOKOFFTHETAUNT]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n挑衅效果解除了！"),
    [STRINGID_PKMNGOTOVERITSINFATUATION]            = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n着迷状态治愈了！"),
    [STRINGID_ITEMCANNOTBEREMOVED]                  = COMPOUND_STRING("无法夺取\n{B_ATK_NAME_WITH_PREFIX}的道具！"),
    [STRINGID_STICKYBARBTRANSFER]                   = COMPOUND_STRING("{B_LAST_ITEM}附着到了\n{B_ATK_NAME_WITH_PREFIX2}的身上！"),
    [STRINGID_PKMNBURNHEALED]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}的\n灼伤治愈了！"),
    [STRINGID_REDCARDACTIVATE]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}猛地向\n{B_ATK_NAME_WITH_PREFIX2}出示了红牌！"),
    [STRINGID_EJECTBUTTONACTIVATE]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n要用{B_LAST_ITEM}回去了！"),
    [STRINGID_ATKGOTOVERINFATUATION]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n用{B_LAST_ITEM}治愈了着迷状态！"),
    [STRINGID_TORMENTEDNOMORE]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n无理取闹的效果消失了！"),
    [STRINGID_HEALBLOCKEDNOMORE]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n回复封锁的效果消失了！"),
    [STRINGID_ATTACKERBECAMEFULLYCHARGED]           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n浑身充满了牵绊之力！\p"),
    [STRINGID_ATTACKERBECAMEASHSPECIES]             = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n变身成了小智版甲贺忍蛙！\p"),
    [STRINGID_EXTREMELYHARSHSUNLIGHT]               = COMPOUND_STRING("日照变得非常强了！"),
    [STRINGID_EXTREMESUNLIGHTFADED]                 = COMPOUND_STRING("日照复原了！"),
    [STRINGID_MOVEEVAPORATEDINTHEHARSHSUNLIGHT]     = COMPOUND_STRING("受强日照的影响，\n水属性的攻击被蒸发了！"),
    [STRINGID_EXTREMELYHARSHSUNLIGHTWASNOTLESSENED] = COMPOUND_STRING("强日照势头不减！"),
    [STRINGID_HEAVYRAIN]                            = COMPOUND_STRING("开始下起了暴雨！"),
    [STRINGID_HEAVYRAINLIFTED]                      = COMPOUND_STRING("暴雨停了！"),
    [STRINGID_MOVEFIZZLEDOUTINTHEHEAVYRAIN]         = COMPOUND_STRING("受暴雨的影响，\n火属性的攻击被扑灭了！"),
    [STRINGID_NORELIEFROMHEAVYRAIN]                 = COMPOUND_STRING("暴雨势头不减！"),
    [STRINGID_MYSTERIOUSAIRCURRENT]                 = COMPOUND_STRING("神秘的乱流\n保护着飞行属性宝可梦！"),
    [STRINGID_STRONGWINDSDISSIPATED]                = COMPOUND_STRING("神秘的乱流停止了！"),
    [STRINGID_MYSTERIOUSAIRCURRENTBLOWSON]          = COMPOUND_STRING("神秘的乱流势头不减！"),
    [STRINGID_ATTACKWEAKENEDBSTRONGWINDS]           = COMPOUND_STRING("神秘的乱流减弱了攻击！"),
    [STRINGID_STUFFCHEEKSCANTSELECT]                = COMPOUND_STRING("没有携带树果，无法使出招式！\p"),
    [STRINGID_PKMNREVERTEDTOPRIMAL]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的原始回归！\n恢复了原始的样子！"),
    [STRINGID_BUTPOKEMONCANTUSETHEMOVE]             = COMPOUND_STRING("但是，{B_ATK_NAME_WITH_PREFIX2}\n无法使用！"),
    [STRINGID_BUTHOOPACANTUSEIT]                    = COMPOUND_STRING("但是，现在的{B_ATK_NAME_WITH_PREFIX2}\n无法使用！"),
    [STRINGID_BROKETHROUGHPROTECTION]               = COMPOUND_STRING("打破了\n{B_DEF_NAME_WITH_PREFIX2}的防守！"),
    [STRINGID_ABILITYALLOWSONLYMOVE]                = COMPOUND_STRING("因为{B_ATK_ABILITY}的效果，\n只能使出{B_CURRENT_MOVE}！\p"),
    [STRINGID_SWAPPEDABILITIES]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n互换了各自的特性！"),
    [STRINGID_PKMNHEALEDPOISON]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}的毒\n消失得干干净净！"),
    [STRINGID_BATTLERTYPECHANGEDTO]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n变成了{B_BUFF1}属性！"),
    [STRINGID_BOTHCANNOLONGERESCAPE]                = COMPOUND_STRING("双方的宝可梦无法逃走了！"),
    [STRINGID_CANTESCAPEDUETOUSEDMOVE]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}受到\n背水一战的效果影响，无法逃走了！"),
    [STRINGID_PKMNBECAMEWEAKERTOFIRE]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n变得怕火了！"),
    [STRINGID_ABOUTTOUSEPOLTERGEIST]                = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}被\n{B_LAST_ITEM}袭击了！"),
    [STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE]       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}受到\n蛸固的效果影响，变得无法逃走了……"),
    [STRINGID_NEUTRALIZINGGASENTERS]                = COMPOUND_STRING("周围充满了化学变化气体！"),
    [STRINGID_NEUTRALIZINGGASOVER]                  = COMPOUND_STRING("化学变化气体的效果消失了！"),
    [STRINGID_TARGETTOOHEAVY]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n太重了，抬不起来！"),
    [STRINGID_PKMNTOOKTARGETHIGH]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n将{B_DEF_NAME_WITH_PREFIX2}带上了高空！"),
    [STRINGID_PKMNINSNAPTRAP]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n被捕兽夹困住了！"),
    [STRINGID_METEORBEAMCHARGING]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}身上\n溢出了宇宙之力！"),
    [STRINGID_HEATUPBEAK]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n开始给鸟嘴加热了！"),
    [STRINGID_COURTCHANGE]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n交换了双方的场地效果！"),
    [STRINGID_ZPOWERSURROUNDS]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n让Z力量笼罩了全身！"),
    [STRINGID_ZMOVEUNLEASHED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}开始释放\n全力的Z招式！"),
    [STRINGID_ZMOVERESETSSTATS]                     = COMPOUND_STRING("因为Z力量，{B_SCR_NAME_WITH_PREFIX}\n恢复了降低的能力！"),
    [STRINGID_ZMOVEALLSTATSUP]                      = COMPOUND_STRING("因为Z力量，{B_SCR_NAME_WITH_PREFIX}的\n能力提高了！"),
    [STRINGID_ZMOVEZBOOSTCRIT]                      = COMPOUND_STRING("因为Z力量，{B_SCR_NAME_WITH_PREFIX}\n变得容易击中要害了！"),
    [STRINGID_ZMOVERESTOREHP]                       = COMPOUND_STRING("因为Z力量，{B_SCR_NAME_WITH_PREFIX}的\n体力回复了！"),
    [STRINGID_ZMOVESTATUP]                          = COMPOUND_STRING("因为Z力量，{B_SCR_NAME_WITH_PREFIX}的\n能力提高了！"),
    [STRINGID_ZMOVEHPTRAP]                          = COMPOUND_STRING("因为Z力量，{B_SCR_NAME_WITH_PREFIX}\n将会回复来替换的宝可梦的HP！"),
    [STRINGID_ATTACKEREXPELLEDTHEPOISON]            = COMPOUND_STRING("为了不让你担心，\n{B_ATK_NAME_WITH_PREFIX}靠自己治愈了中毒！"),
    [STRINGID_ATTACKERSHOOKITSELFAWAKE]             = COMPOUND_STRING("为了不让你担心，\n{B_ATK_NAME_WITH_PREFIX}努力醒过来了！"),
    [STRINGID_ATTACKERBROKETHROUGHPARALYSIS]        = COMPOUND_STRING("为了不让你担心，\n{B_ATK_NAME_WITH_PREFIX}靠斗志治愈了麻痹！"),
    [STRINGID_ATTACKERHEALEDITSBURN]                = COMPOUND_STRING("为了不让你担心，\n{B_ATK_NAME_WITH_PREFIX}靠毅力治愈了灼伤！"),
    [STRINGID_ATTACKERMELTEDTHEICE]                 = COMPOUND_STRING("为了不让你担心，\n{B_ATK_NAME_WITH_PREFIX}努力融化了冰冻！"),
    [STRINGID_TARGETTOUGHEDITOUT]                   = COMPOUND_STRING("为了不让{B_PLAYER_NAME}伤心，\n{B_DEF_NAME_WITH_PREFIX}撑住了！"),
    [STRINGID_ATTACKERLOSTELECTRICTYPE]             = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n用尽电力了！"),
    [STRINGID_ATTACKERSWITCHEDSTATWITHTARGET]       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n互换了各自的{B_BUFF1}！"),
    [STRINGID_BEINGHITCHARGEDPKMNWITHPOWER]         = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX2}\n受到{B_CURRENT_MOVE}而充电了！"),
    [STRINGID_SUNLIGHTACTIVATEDABILITY]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX2}通过\n大晴天发动了古代活性！"),
    [STRINGID_STATWASHEIGHTENED]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的\n{B_BUFF1}升高了！"),
    [STRINGID_ELECTRICTERRAINACTIVATEDABILITY]      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX2}通过\n电气场地发动了夸克充能！"),
    [STRINGID_ABILITYWEAKENEDSURROUNDINGMONSSTAT]   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的{B_SCR_ABILITY}\n令周围的宝可梦的{B_BUFF1}减弱了！\p"),
    [STRINGID_ATTACKERGAINEDSTRENGTHFROMTHEFALLEN]  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}从\n被打倒的同伴身上得到力量了！"),
    [STRINGID_PKMNSABILITYPREVENTSABILITY]          = COMPOUND_STRING("因{B_SCR_NAME_WITH_PREFIX}的\n{B_SCR_ABILITY}，\p{B_DEF_NAME_WITH_PREFIX2}的\n{B_DEF_ABILITY}变得无效了！"), //not in gen 5+, ability popup
    [STRINGID_PREPARESHELLTRAP]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}设置了陷阱甲壳！"),
    [STRINGID_SHELLTRAPDIDNTWORK]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的\n陷阱甲壳没有被触发！"),
    [STRINGID_SPIKESDISAPPEAREDFROMTEAM]            = COMPOUND_STRING("{B_ATK_TEAM2}脚下的\n撒菱消失不见了！"),
    [STRINGID_TOXICSPIKESDISAPPEAREDFROMTEAM]       = COMPOUND_STRING("{B_ATK_TEAM2}脚下的\n毒菱消失不见了！"),
    [STRINGID_STICKYWEBDISAPPEAREDFROMTEAM]         = COMPOUND_STRING("{B_ATK_TEAM2}脚下的\n黏黏网消失不见了！"),
    [STRINGID_STEALTHROCKDISAPPEAREDFROMTEAM]       = COMPOUND_STRING("{B_ATK_TEAM2}周围的\n隐形岩消失不见了！"),
    [STRINGID_COULDNTFULLYPROTECT]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n没能防住攻击，受到了伤害！"),
    [STRINGID_STOCKPILEDEFFECTWOREOFF]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n蓄力后的效果消失了！"),
    [STRINGID_PKMNREVIVEDREADYTOFIGHT]              = COMPOUND_STRING("{B_BUFF1}复活\n并能继续战斗了！"),
    [STRINGID_ITEMRESTOREDSPECIESHEALTH]            = COMPOUND_STRING("{B_BUFF1}的\n体力回复了！"),
    [STRINGID_ITEMCUREDSPECIESSTATUS]               = COMPOUND_STRING("{B_BUFF1}\n从异常状态中恢复了！"), // Not in Gen 5+
    [STRINGID_ITEMRESTOREDSPECIESPP]                = COMPOUND_STRING("{B_BUFF1}\n回复了{B_BUFF2}的PP！"),
    [STRINGID_THUNDERCAGETRAPPED]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX2}被\n{B_ATK_NAME_WITH_PREFIX}困住了！"),
    [STRINGID_PKMNHURTBYFROSTBITE]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n受到了冻伤的伤害！"),
    [STRINGID_PKMNGOTFROSTBITE]                     = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}\n被冻伤了！"),
    [STRINGID_PKMNSITEMHEALEDFROSTBITE]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}用\n{B_LAST_ITEM}治愈了冻伤！"),
    [STRINGID_ATTACKERHEALEDITSFROSTBITE]           = COMPOUND_STRING("为了不让你担心，\n{B_ATK_NAME_WITH_PREFIX}努力治愈了冻伤！"),
    [STRINGID_PKMNFROSTBITEHEALED]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n冻伤痊愈了！"),
    [STRINGID_PKMNFROSTBITEHEALEDBY]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}用\n{B_CURRENT_MOVE}治愈了冻伤！"),
    [STRINGID_MIRRORHERBCOPIED]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}使用模仿香草\n模仿了对手的能力变化！"),
    [STRINGID_STARTEDSNOW]                          = COMPOUND_STRING("开始下雪了！"),
    [STRINGID_SNOWCONTINUES]                        = COMPOUND_STRING("漫天大雪。"), //not in gen 5+ (lol)
    [STRINGID_SNOWSTOPPED]                          = COMPOUND_STRING("雪停了！"),
    [STRINGID_SNOWWARNINGSNOW]                      = COMPOUND_STRING("开始下雪了！"),
    [STRINGID_PKMNITEMMELTED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}把{B_DEF_NAME_WITH_PREFIX2}的\n{B_LAST_ITEM}融化了！"),
    [STRINGID_ULTRABURSTREACTING]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX2}的身上\n开始溢出耀眼的光芒！"),
    [STRINGID_ULTRABURSTCOMPLETED]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}通过究极爆发\n现出了新的样子！"),
    [STRINGID_TEAMGAINEDEXP]                        = COMPOUND_STRING("通过学习装置，\n各自都获得了经验值！\p"),
    [STRINGID_CURRENTMOVECANTSELECT]                = COMPOUND_STRING("无法使用{B_BUFF1}！"),
    [STRINGID_TARGETISBEINGSALTCURED]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}\n陷入了盐腌状态！"),
    [STRINGID_TARGETISHURTBYSALTCURE]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}受到了\n{B_BUFF1}的伤害。"),
    [STRINGID_TARGETCOVEREDINSTICKYCANDYSYRUP]      = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}陷入了\n满身糖状态！"),
    [STRINGID_SHARPSTEELFLOATS]                     = COMPOUND_STRING("{B_DEF_TEAM2} 周围\n开始悬浮起尖锐的钢刺！"),
    [STRINGID_SHARPSTEELDMG]                        = COMPOUND_STRING("尖锐的钢刺扎进了\n{B_DEF_NAME_WITH_PREFIX2}体内！"),
    [STRINGID_PKMNBLEWAWAYSHARPSTEEL]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n吹飞了尖锐的钢刺！"),
    [STRINGID_SHARPSTEELDISAPPEAREDFROMTEAM]        = COMPOUND_STRING("{B_ATK_TEAM2}周围的\n钢刺消失了"),
    [STRINGID_TEAMTRAPPEDWITHVINES]                 = COMPOUND_STRING("{B_DEF_TEAM1}宝可梦\n被困在鞭子的猛击中！"),
    [STRINGID_PKMNHURTBYVINES]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}被暴露在\n超极巨灰飞鞭灭的猛击下疼痛难忍！"),
    [STRINGID_TEAMCAUGHTINVORTEX]                   = COMPOUND_STRING("{B_DEF_TEAM1}宝可梦\n被困在水流之中！"),
    [STRINGID_PKMNHURTBYVORTEX]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}被吞没在\n超极巨水炮轰灭的水流里疼痛难忍！"),
    [STRINGID_TEAMSURROUNDEDBYFIRE]                 = COMPOUND_STRING("{B_DEF_TEAM1}宝可梦\n被困在火焰之中！"),
    [STRINGID_PKMNBURNINGUP]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}被\n超极巨地狱灭焰的火焰包围酷热难耐！"),
    [STRINGID_TEAMSURROUNDEDBYROCKS]                = COMPOUND_STRING("{B_DEF_TEAM1}宝可梦\n被困在岩石之中！"),
    [STRINGID_PKMNHURTBYROCKSTHROWN]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}被困在\n超极巨炎石喷发的岩石之中疼痛难忍！"),
    [STRINGID_MOVEBLOCKEDBYDYNAMAX]                 = COMPOUND_STRING("被极巨化之力弹开了！"),
    [STRINGID_ZEROTOHEROTRANSFORMATION]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n变身后归来了！"),
    [STRINGID_THETWOMOVESBECOMEONE]                 = COMPOUND_STRING("两个招式合二为一！\n这是合体招式！！{PAUSE 16}"),
    [STRINGID_ARAINBOWAPPEAREDONSIDE]               = COMPOUND_STRING("彩虹出现在了{B_ATK_TEAM2}上空！"),
    [STRINGID_THERAINBOWDISAPPEARED]                = COMPOUND_STRING("彩虹从{B_ATK_TEAM2}上空消失了！"),
    [STRINGID_WAITINGFORPARTNERSMOVE]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}正在等待\n{B_ATK_PARTNER_NAME}的技能……{PAUSE 16}"),
    [STRINGID_SEAOFFIREENVELOPEDSIDE]               = COMPOUND_STRING("{B_DEF_TEAM2}周围被\n火海包围了！"),
    [STRINGID_HURTBYTHESEAOFFIRE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}受到了火海的伤害！"),
    [STRINGID_THESEAOFFIREDISAPPEARED]              = COMPOUND_STRING("{B_ATK_TEAM2}周围的火海\n消失不见了！"),
    [STRINGID_SWAMPENVELOPEDSIDE]                   = COMPOUND_STRING("在{B_DEF_TEAM2}周围\n延伸出了湿地！"),
    [STRINGID_THESWAMPDISAPPEARED]                  = COMPOUND_STRING("{B_ATK_TEAM2}周围的湿地\n消失不见了！"),
    [STRINGID_PKMNTELLCHILLINGRECEPTIONJOKE]        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}说出了冷笑话！"),
    [STRINGID_HOSPITALITYRESTORATION]               = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}喝光了\n{B_SCR_NAME_WITH_PREFIX2}泡的茶！"),
    [STRINGID_ELECTROSHOTCHARGING]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}吸收了电力！"),
    [STRINGID_ITEMWASUSEDUP]                        = COMPOUND_STRING("{B_LAST_ITEM}已完成使命，\n消失了……"),
    [STRINGID_ATTACKERLOSTITSTYPE]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}失去了\n{B_BUFF1}属性！"),
    [STRINGID_SHEDITSTAIL]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}使用\n断尾制作了替身！"),
    [STRINGID_CLOAKEDINAHARSHLIGHT]                 = COMPOUND_STRING("强光包围了{B_ATK_NAME_WITH_PREFIX}！"),
    [STRINGID_SUPERSWEETAROMAWAFTS]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX2}的蜜\n散发出了甜甜香气！"),
    [STRINGID_DIMENSIONSWERETWISTED]                = COMPOUND_STRING("时空被扭曲了！"),
    [STRINGID_BIZARREARENACREATED]                  = COMPOUND_STRING("空间变得离奇了！\n宝可梦的持有物失去了效果！"),
    [STRINGID_BIZARREAREACREATED]                   = COMPOUND_STRING("空间变得离奇了！\n宝可梦的防御和特防互换了！"),
    [STRINGID_TIDYINGUPCOMPLETE]                    = COMPOUND_STRING("大扫除完毕！"),
    [STRINGID_PKMNTERASTALLIZEDINTO]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}太晶化为了{B_BUFF1}属性！"), // Does not exist, meant to mimic form change strings
    [STRINGID_BOOSTERENERGYACTIVATES]               = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}通过{B_LAST_ITEM}\n发动了{B_SCR_ABILITY}！"),
    [STRINGID_FOGCREPTUP]                           = COMPOUND_STRING("开始起雾了！"),
    [STRINGID_FOGISDEEP]                            = COMPOUND_STRING("雾持续弥漫。"),
    [STRINGID_FOGLIFTED]                            = COMPOUND_STRING("雾散开了！"),
    [STRINGID_PKMNMADESHELLGLEAM]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}让甲壳发出光辉，\n使属性相克发生扭曲！！"),
    [STRINGID_FICKLEBEAMDOUBLED]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}拿出全力了！"),
    [STRINGID_COMMANDERACTIVATES]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}作为发号施令的要员\n而被{B_BUFF1}吞下去了！"),
    [STRINGID_POKEFLUTECATCHY]                      = COMPOUND_STRING("{B_PLAYER_NAME}吹响了{B_LAST_ITEM}！\p嗯……不错的音色！"),
    [STRINGID_POKEFLUTE]                            = COMPOUND_STRING("{B_PLAYER_NAME}吹响了{B_LAST_ITEM}！"),
    [STRINGID_MONHEARINGFLUTEAWOKE]                 = COMPOUND_STRING("宝可梦听到笛声醒了过来！"),
    [STRINGID_SUNLIGHTISHARSH]                      = COMPOUND_STRING("现在日照很强！"),
    [STRINGID_ITISHAILING]                          = COMPOUND_STRING("现在正在下冰雹！"),
    [STRINGID_ITISSNOWING]                          = COMPOUND_STRING("现在正在下雪！"),
    [STRINGID_ISCOVEREDWITHGRASS]                   = COMPOUND_STRING("脚下的青草正在生长！"),
    [STRINGID_MISTSWIRLSAROUND]                     = COMPOUND_STRING("脚下的雾气正在蔓延！"),
    [STRINGID_ELECTRICCURRENTISRUNNING]             = COMPOUND_STRING("脚下的电光正在闪烁！"),
    [STRINGID_SEEMSWEIRD]                           = COMPOUND_STRING("脚下传来阵阵奇妙的感觉！"),
    [STRINGID_WAGGLINGAFINGER]                      = COMPOUND_STRING("挥动手指后，使出了{B_CURRENT_MOVE}！"),
    [STRINGID_BLOCKEDBYSLEEPCLAUSE]                 = COMPOUND_STRING("因为催眠条款，\n{B_DEF_NAME_WITH_PREFIX2}不会被催眠！"),
    [STRINGID_SUPEREFFECTIVETWOFOES]                = COMPOUND_STRING("对{B_DEF_NAME_WITH_PREFIX2}和\n{B_DEF_PARTNER_NAME}效果绝佳！"),
    [STRINGID_NOTVERYEFFECTIVETWOFOES]              = COMPOUND_STRING("对{B_DEF_NAME_WITH_PREFIX2}和\n{B_DEF_PARTNER_NAME}效果不好。"),
    [STRINGID_ITDOESNTAFFECTTWOFOES]                = COMPOUND_STRING("对于{B_DEF_NAME_WITH_PREFIX2}和\n{B_DEF_PARTNER_NAME}，好像没有效果……"),
    [STRINGID_SENDCAUGHTMONPARTYORBOX]              = COMPOUND_STRING("要将{B_DEF_NAME}加入到同行宝可梦里吗？"),
    [STRINGID_PKMNSENTTOPCAFTERCATCH]               = gText_PkmnSentToPCAfterCatch,
    [STRINGID_PKMNDYNAMAXED]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}极巨化了！\n变得巨大无比！"),//原作无对应文本，个人翻译
    [STRINGID_PKMNGIGANTAMAXED]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}超极巨化了！\n变得巨大无比！"),
    [STRINGID_TIMETODYNAMAX]                        = COMPOUND_STRING("极巨化吧！"),
    [STRINGID_TIMETOGIGANTAMAX]                     = COMPOUND_STRING("超极巨化吧！"),
    [STRINGID_QUESTIONFORFEITBATTLE]                = COMPOUND_STRING("即将放弃对战直接投降。\n这将被判为输掉对战，可以吗？"),
    [STRINGID_POWERCONSTRUCTPRESENCEOFMANY]         = COMPOUND_STRING("你感受到了大量的气息……！"),
    [STRINGID_POWERCONSTRUCTTRANSFORM]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}\n变成了完全体形态！"),
    [STRINGID_ABILITYSHIELDPROTECTS]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}的特性\n正受到{B_LAST_ITEM}效果的保护！"),
    [STRINGID_MONTOOSCAREDTOMOVE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}太害怕了，\n无法动弹！"),
    [STRINGID_GHOSTGETOUTGETOUT]                    = COMPOUND_STRING("幽灵：走开……走开……"),
    [STRINGID_SILPHSCOPEUNVEILED]                   = COMPOUND_STRING("希尔佛检视镜识破了\n幽灵的正体！"),
    [STRINGID_GHOSTWASMAROWAK]                      = COMPOUND_STRING("幽灵的正体是嘎啦嘎啦！\p\n"),
    [STRINGID_TRAINER1MON1COMEBACK]                 = COMPOUND_STRING("{B_TRAINER1_NAME}：“回来吧，\n{B_OPPONENT_MON1_NAME}！”"),
    [STRINGID_THREWROCK]                            = COMPOUND_STRING("{B_PLAYER_NAME}向{B_OPPONENT_MON1_NAME}\n投掷了石头！"),
    [STRINGID_THREWBAIT]                            = COMPOUND_STRING("{B_PLAYER_NAME}向{B_OPPONENT_MON1_NAME}\n投掷了食物！"),
    [STRINGID_PKMNANGRY]                            = COMPOUND_STRING("{B_OPPONENT_MON1_NAME}发怒了！"),
    [STRINGID_PKMNEATING]                           = COMPOUND_STRING("{B_OPPONENT_MON1_NAME}正在吃东西！"),
    [STRINGID_PKMNDISGUISEWASBUSTED]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的画皮脱落了！"),
    [STRINGID_ZENMODETRIGGERED]                     = COMPOUND_STRING("{B_SCR_ABILITY}发动了！"),
    [STRINGID_ZENMODEENDED]                         = COMPOUND_STRING("{B_SCR_ABILITY}结束了！"),
    [STRINGID_SCRCUREDPARALYSIS]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n治愈了麻痹！"),
    [STRINGID_SCRCUREDPOISON]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n治愈了中毒！"),
    [STRINGID_SCRCUREDBURN]                         = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n治愈了灼伤！"),
    [STRINGID_SCRCUREDSLEEP]                        = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n让自己醒过来了！"),
    [STRINGID_SCRCUREDCONFUSION]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}\n治愈了混乱！"),
    [STRINGID_PARTYCUREDPARALYSIS]                  = COMPOUND_STRING("{B_BUFF1}\n治愈了麻痹！"),
    [STRINGID_PARTYCUREDPOISON]                     = COMPOUND_STRING("{B_BUFF1}\n治愈了中毒！"),
    [STRINGID_PARTYCUREDBURN]                       = COMPOUND_STRING("{B_BUFF1}\n治愈了灼伤！"),
    [STRINGID_PARTYCUREDSLEEP]                      = COMPOUND_STRING("{B_BUFF1}\n让自己醒过来了！"),
    [STRINGID_PARTYCUREDFREEZE]                     = COMPOUND_STRING("{B_BUFF1}\n治愈了冰冻状态！"),
    [STRINGID_PARTYCUREDFROSTBITE]                  = COMPOUND_STRING("{B_BUFF1}\n治愈了冻伤！"),
    [STRINGID_PKMNATKNOTLOWERED]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}的\n攻击不会降低！"),
    [STRINGID_REFLECTWOREOFF]                       = COMPOUND_STRING("{B_DEF_TEAM1}的反射壁消失了！"),
    [STRINGID_LIGHTSCREENWOREOFF]                   = COMPOUND_STRING("{B_DEF_TEAM1}的光墙消失了！"),
    [STRINGID_AURORAVEILWOREOFF]                    = COMPOUND_STRING("{B_DEF_TEAM1}的极光幕消失了！"),
    [STRINGID_STICKYWEBDISAPPEAREDFROMYOU]          = COMPOUND_STRING("脚下的黏黏网\n消失不见了！"),
};

const u16 gTrainerUsedItemStringIds[] =
{
    STRINGID_PLAYERUSEDITEM, STRINGID_TRAINER1USEDITEM
};

const u16 gZEffectStringIds[] =
{
    [B_MSG_Z_RESET_STATS] = STRINGID_ZMOVERESETSSTATS,
    [B_MSG_Z_ALL_STATS_UP]= STRINGID_ZMOVEALLSTATSUP,
    [B_MSG_Z_BOOST_CRITS] = STRINGID_ZMOVEZBOOSTCRIT,
    [B_MSG_Z_FOLLOW_ME]   = STRINGID_PKMNCENTERATTENTION,
    [B_MSG_Z_RECOVER_HP]  = STRINGID_ZMOVERESTOREHP,
    [B_MSG_Z_STAT_UP]     = STRINGID_ZMOVESTATUP,
    [B_MSG_Z_HP_TRAP]     = STRINGID_ZMOVEHPTRAP,
};

const u16 gMentalHerbCureStringIds[] =
{
    [B_MSG_MENTALHERBCURE_INFATUATION] = STRINGID_ATKGOTOVERINFATUATION,
    [B_MSG_MENTALHERBCURE_TORMENT]     = STRINGID_TORMENTEDNOMORE,
    [B_MSG_MENTALHERBCURE_DISABLE]     = STRINGID_PKMNMOVEDISABLEDNOMORE,
    [B_MSG_MENTALHERBCURE_HEALBLOCK]   = STRINGID_HEALBLOCKEDNOMORE,
    [B_MSG_MENTALHERBCURE_ENCORE]      = STRINGID_PKMNENCOREENDED,
    [B_MSG_MENTALHERBCURE_TAUNT]       = STRINGID_PKMNSHOOKOFFTHETAUNT,
};

const u16 gStartingStatusStringIds[B_MSG_STARTING_STATUS_COUNT] =
{
    [B_MSG_TERRAIN_SET_MISTY]    = STRINGID_TERRAINBECOMESMISTY,
    [B_MSG_TERRAIN_SET_ELECTRIC] = STRINGID_TERRAINBECOMESELECTRIC,
    [B_MSG_TERRAIN_SET_PSYCHIC]  = STRINGID_TERRAINBECOMESPSYCHIC,
    [B_MSG_TERRAIN_SET_GRASSY]   = STRINGID_TERRAINBECOMESGRASSY,
    [B_MSG_SET_TRICK_ROOM]       = STRINGID_DIMENSIONSWERETWISTED,
    [B_MSG_SET_MAGIC_ROOM]       = STRINGID_BIZARREARENACREATED,
    [B_MSG_SET_WONDER_ROOM]      = STRINGID_BIZARREAREACREATED,
    [B_MSG_SET_TAILWIND]         = STRINGID_TAILWINDBLEW,
    [B_MSG_SET_RAINBOW]          = STRINGID_ARAINBOWAPPEAREDONSIDE,
    [B_MSG_SET_SEA_OF_FIRE]      = STRINGID_SEAOFFIREENVELOPEDSIDE,
    [B_MSG_SET_SWAMP]            = STRINGID_SWAMPENVELOPEDSIDE,
    [B_MSG_SET_SPIKES]           = STRINGID_SPIKESSCATTERED,
    [B_MSG_SET_POISON_SPIKES]    = STRINGID_POISONSPIKESSCATTERED,
    [B_MSG_SET_STICKY_WEB]       = STRINGID_STICKYWEBUSED,
    [B_MSG_SET_STEALTH_ROCK]     = STRINGID_POINTEDSTONESFLOAT,
    [B_MSG_SET_SHARP_STEEL]      = STRINGID_SHARPSTEELFLOATS,
};

const u16 gTerrainStringIds[B_MSG_TERRAIN_COUNT] =
{
    [B_MSG_TERRAIN_SET_MISTY] = STRINGID_TERRAINBECOMESMISTY,
    [B_MSG_TERRAIN_SET_ELECTRIC] = STRINGID_TERRAINBECOMESELECTRIC,
    [B_MSG_TERRAIN_SET_PSYCHIC] = STRINGID_TERRAINBECOMESPSYCHIC,
    [B_MSG_TERRAIN_SET_GRASSY] = STRINGID_TERRAINBECOMESGRASSY,
    [B_MSG_TERRAIN_END_MISTY] = STRINGID_MISTYTERRAINENDS,
    [B_MSG_TERRAIN_END_ELECTRIC] = STRINGID_ELECTRICTERRAINENDS,
    [B_MSG_TERRAIN_END_PSYCHIC] = STRINGID_PSYCHICTERRAINENDS,
    [B_MSG_TERRAIN_END_GRASSY] = STRINGID_GRASSYTERRAINENDS,
};

const u16 gTerrainPreventsStringIds[] =
{
    [B_MSG_TERRAINPREVENTS_MISTY]    = STRINGID_MISTYTERRAINPREVENTS,
    [B_MSG_TERRAINPREVENTS_ELECTRIC] = STRINGID_ELECTRICTERRAINPREVENTS,
    [B_MSG_TERRAINPREVENTS_PSYCHIC]  = STRINGID_PSYCHICTERRAINPREVENTS
};

const u16 gHealingWishStringIds[] =
{
    STRINGID_HEALINGWISHCAMETRUE,
    STRINGID_LUNARDANCECAMETRUE
};

const u16 gDmgHazardsStringIds[] =
{
    [B_MSG_PKMNHURTBYSPIKES]   = STRINGID_PKMNHURTBYSPIKES,
    [B_MSG_STEALTHROCKDMG]     = STRINGID_STEALTHROCKDMG,
    [B_MSG_SHARPSTEELDMG]      = STRINGID_SHARPSTEELDMG,
    [B_MSG_POINTEDSTONESFLOAT] = STRINGID_POINTEDSTONESFLOAT,
    [B_MSG_SPIKESSCATTERED]    = STRINGID_SPIKESSCATTERED,
    [B_MSG_SHARPSTEELFLOATS]   = STRINGID_SHARPSTEELFLOATS,
};

const u16 gSwitchInAbilityStringIds[] =
{
    [B_MSG_SWITCHIN_MOLDBREAKER] = STRINGID_MOLDBREAKERENTERS,
    [B_MSG_SWITCHIN_TERAVOLT] = STRINGID_TERAVOLTENTERS,
    [B_MSG_SWITCHIN_TURBOBLAZE] = STRINGID_TURBOBLAZEENTERS,
    [B_MSG_SWITCHIN_SLOWSTART] = STRINGID_SLOWSTARTENTERS,
    [B_MSG_SWITCHIN_UNNERVE] = STRINGID_UNNERVEENTERS,
    [B_MSG_SWITCHIN_ANTICIPATION] = STRINGID_ANTICIPATIONACTIVATES,
    [B_MSG_SWITCHIN_FOREWARN] = STRINGID_FOREWARNACTIVATES,
    [B_MSG_SWITCHIN_PRESSURE] = STRINGID_PRESSUREENTERS,
    [B_MSG_SWITCHIN_DARKAURA] = STRINGID_DARKAURAENTERS,
    [B_MSG_SWITCHIN_FAIRYAURA] = STRINGID_FAIRYAURAENTERS,
    [B_MSG_SWITCHIN_AURABREAK] = STRINGID_AURABREAKENTERS,
    [B_MSG_SWITCHIN_COMATOSE] = STRINGID_COMATOSEENTERS,
    [B_MSG_SWITCHIN_SCREENCLEANER] = STRINGID_SCREENCLEANERENTERS,
    [B_MSG_SWITCHIN_ASONE] = STRINGID_ASONEENTERS,
    [B_MSG_SWITCHIN_CURIOUS_MEDICINE] = STRINGID_CURIOUSMEDICINEENTERS,
    [B_MSG_SWITCHIN_PASTEL_VEIL] = STRINGID_PKMNHEALEDPOISON,
    [B_MSG_SWITCHIN_NEUTRALIZING_GAS] = STRINGID_NEUTRALIZINGGASENTERS,
};

const u16 gMissStringIds[] =
{
    [B_MSG_MISSED]      = STRINGID_PKMNAVOIDEDATTACK,
    [B_MSG_PROTECTED]   = STRINGID_PKMNPROTECTEDITSELF,
    [B_MSG_AVOIDED_ATK] = STRINGID_PKMNAVOIDEDATTACK,
};

const u16 gNoEscapeStringIds[] =
{
    [B_MSG_CANT_ESCAPE]          = STRINGID_CANTESCAPE,
    [B_MSG_DONT_LEAVE_BIRCH]     = STRINGID_DONTLEAVEBIRCH,
    [B_MSG_PREVENTS_ESCAPE]      = STRINGID_PREVENTSESCAPE,
    [B_MSG_CANT_ESCAPE_2]        = STRINGID_CANTESCAPE2,
    [B_MSG_ATTACKER_CANT_ESCAPE] = STRINGID_ATTACKERCANTESCAPE
};

const u16 gMoveWeatherChangeStringIds[] =
{
    [B_MSG_STARTED_RAIN]      = STRINGID_STARTEDTORAIN,
    [B_MSG_STARTED_DOWNPOUR]  = STRINGID_DOWNPOURSTARTED, // Unused
    [B_MSG_WEATHER_FAILED]    = STRINGID_BUTITFAILED,
    [B_MSG_STARTED_SANDSTORM] = STRINGID_SANDSTORMBREWED,
    [B_MSG_STARTED_SUNLIGHT]  = STRINGID_SUNLIGHTGOTBRIGHT,
    [B_MSG_STARTED_HAIL]      = STRINGID_STARTEDHAIL,
    [B_MSG_STARTED_SNOW]      = STRINGID_STARTEDSNOW,
    [B_MSG_STARTED_FOG]       = STRINGID_FOGCREPTUP, // Unused, can use for custom moves that set fog
};

const u16 gAbilityWeatherChangeStringId[] =
{
    [B_MSG_STARTED_DRIZZLE]        = STRINGID_STARTEDTORAIN,
    [B_MSG_STARTED_SAND_STREAM]    = STRINGID_SANDSTORMBREWED,
    [B_MSG_STARTED_DROUGHT]        = STRINGID_SUNLIGHTGOTBRIGHT,
    [B_MSG_STARTED_HAIL_WARNING]   = STRINGID_STARTEDHAIL,
    [B_MSG_STARTED_SNOW_WARNING]   = STRINGID_STARTEDSNOW,
    [B_MSG_STARTED_DESOLATE_LAND]  = STRINGID_EXTREMELYHARSHSUNLIGHT,
    [B_MSG_STARTED_PRIMORDIAL_SEA] = STRINGID_HEAVYRAIN,
    [B_MSG_STARTED_STRONG_WINDS]   = STRINGID_MYSTERIOUSAIRCURRENT,
};

const u16 gWeatherEndsStringIds[B_MSG_WEATHER_END_COUNT] =
{
    [B_MSG_WEATHER_END_RAIN]                       = STRINGID_RAINSTOPPED,
    [B_MSG_WEATHER_END_SUN]                        = STRINGID_SUNLIGHTFADED,
    [B_MSG_WEATHER_END_SANDSTORM]                  = STRINGID_SANDSTORMSUBSIDED,
    [B_MSG_WEATHER_END_HAIL]                       = STRINGID_HAILSTOPPED,
    [B_MSG_WEATHER_END_SNOW]                       = STRINGID_SNOWSTOPPED,
    [B_MSG_WEATHER_END_FOG]                        = STRINGID_FOGLIFTED,
    [B_MSG_WEATHER_END_EXTREMELY_HARSH_SUNLIGHT]   = STRINGID_EXTREMESUNLIGHTFADED,
    [B_MSG_WEATHER_END_HEAVY_RAIN]                 = STRINGID_HEAVYRAINLIFTED,
    [B_MSG_WEATHER_END_STRONG_WINDS]               = STRINGID_STRONGWINDSDISSIPATED,
};

const u16 gWeatherTurnStringIds[] =
{
    [B_MSG_WEATHER_TURN_RAIN]         = STRINGID_RAINCONTINUES,
    [B_MSG_WEATHER_TURN_DOWNPOUR]     = STRINGID_DOWNPOURCONTINUES,
    [B_MSG_WEATHER_TURN_SUN]          = STRINGID_SUNLIGHTSTRONG,
    [B_MSG_WEATHER_TURN_SANDSTORM]    = STRINGID_SANDSTORMRAGES,
    [B_MSG_WEATHER_TURN_HAIL]         = STRINGID_HAILCONTINUES,
    [B_MSG_WEATHER_TURN_SNOW]         = STRINGID_SNOWCONTINUES,
    [B_MSG_WEATHER_TURN_FOG]          = STRINGID_FOGISDEEP,
    [B_MSG_WEATHER_TURN_STRONG_WINDS] = STRINGID_MYSTERIOUSAIRCURRENTBLOWSON,
};

const u16 gSandStormHailDmgStringIds[] =
{
    [B_MSG_SANDSTORM] = STRINGID_PKMNBUFFETEDBYSANDSTORM,
    [B_MSG_HAIL]      = STRINGID_PKMNPELTEDBYHAIL
};

const u16 gProtectLikeUsedStringIds[] =
{
    [B_MSG_PROTECTED_ITSELF] = STRINGID_PKMNPROTECTEDITSELF2,
    [B_MSG_BRACED_ITSELF]    = STRINGID_PKMNBRACEDITSELF,
    [B_MSG_PROTECTED_TEAM]   = STRINGID_PROTECTEDTEAM,
};

const u16 gBrokeProtectionStringIds[] =
{
    [B_MSG_FEINT]           = STRINGID_FELLFORFEINT,
    [B_MSG_HYPERSPACE_FURY] = STRINGID_BROKETHROUGHPROTECTION,
};

const u16 gReflectLightScreenSafeguardStringIds[] =
{
    [B_MSG_SIDE_STATUS_FAILED]     = STRINGID_BUTITFAILED,
    [B_MSG_SET_REFLECT_SINGLE]     = STRINGID_PKMNRAISEDDEF,
    [B_MSG_SET_REFLECT_DOUBLE]     = STRINGID_PKMNRAISEDDEF,
    [B_MSG_SET_LIGHTSCREEN_SINGLE] = STRINGID_PKMNRAISEDSPDEF,
    [B_MSG_SET_LIGHTSCREEN_DOUBLE] = STRINGID_PKMNRAISEDSPDEF,
    [B_MSG_SET_SAFEGUARD]          = STRINGID_PKMNCOVEREDBYVEIL,
    [B_MSG_SET_AURORA_VEIL]        = STRINGID_PKMNAURORAVEIL,
};

const u16 gLeechSeedStringIds[] =
{
    [B_MSG_LEECH_SEED_SET]   = STRINGID_PKMNSEEDED,
    [B_MSG_LEECH_SEED_MISS]  = STRINGID_PKMNEVADEDATTACK,
    [B_MSG_LEECH_SEED_FAIL]  = STRINGID_ITDOESNTAFFECT,
    [B_MSG_LEECH_SEED_DRAIN] = STRINGID_PKMNSAPPEDBYLEECHSEED,
    [B_MSG_LEECH_SEED_OOZE]  = STRINGID_ITSUCKEDLIQUIDOOZE,
};

const u16 gRestUsedStringIds[] =
{
    [B_MSG_REST]          = STRINGID_PKMNWENTTOSLEEP,
    [B_MSG_REST_STATUSED] = STRINGID_PKMNSLEPTHEALTHY
};

const u16 gUproarOverTurnStringIds[] =
{
    [B_MSG_UPROAR_CONTINUES] = STRINGID_PKMNMAKINGUPROAR,
    [B_MSG_UPROAR_ENDS]      = STRINGID_PKMNCALMEDDOWN
};

const u16 gWokeUpStringIds[] =
{
    [B_MSG_WOKE_UP]        = STRINGID_PKMNWOKEUP,
    [B_MSG_WOKE_UP_UPROAR] = STRINGID_PKMNWOKEUPINUPROAR
};

const u16 gUproarAwakeStringIds[] =
{
    [B_MSG_CANT_SLEEP_UPROAR]  = STRINGID_PKMNCANTSLEEPINUPROAR2,
    [B_MSG_UPROAR_KEPT_AWAKE]  = STRINGID_UPROARKEPTPKMNAWAKE,
};

const u16 gStatUpStringIds[] =
{
    [B_MSG_ATTACKER_STAT_CHANGED] = STRINGID_ATTACKERSSTATROSE,
    [B_MSG_DEFENDER_STAT_CHANGED] = STRINGID_DEFENDERSSTATROSE,
    [B_MSG_STAT_WONT_CHANGE]      = STRINGID_STATSWONTINCREASE,
    [B_MSG_STAT_CHANGE_EMPTY]     = STRINGID_EMPTYSTRING3,
    [B_MSG_STAT_CHANGED_ITEM]     = STRINGID_USINGITEMSTATOFPKMNROSE,
    [B_MSG_USED_DIRE_HIT]         = STRINGID_PKMNUSEDXTOGETPUMPED,
};

const u16 gStatDownStringIds[] =
{
    [B_MSG_ATTACKER_STAT_CHANGED] = STRINGID_ATTACKERSSTATFELL,
    [B_MSG_DEFENDER_STAT_CHANGED] = STRINGID_DEFENDERSSTATFELL,
    [B_MSG_STAT_WONT_CHANGE]      = STRINGID_STATSWONTDECREASE,
    [B_MSG_STAT_CHANGE_EMPTY]     = STRINGID_EMPTYSTRING3,
    [B_MSG_STAT_CHANGED_ITEM]     = STRINGID_USINGITEMSTATOFPKMNFELL,
};

// Index copied from move's index in sTrappingMoves
const u16 gWrappedStringIds[NUM_TRAPPING_MOVES] =
{
    [B_MSG_WRAPPED_BIND]        = STRINGID_PKMNSQUEEZEDBYBIND,     // MOVE_BIND
    [B_MSG_WRAPPED_WRAP]        = STRINGID_PKMNWRAPPEDBY,          // MOVE_WRAP
    [B_MSG_WRAPPED_FIRE_SPIN]   = STRINGID_PKMNTRAPPEDINVORTEX,    // MOVE_FIRE_SPIN
    [B_MSG_WRAPPED_CLAMP]       = STRINGID_PKMNCLAMPED,            // MOVE_CLAMP
    [B_MSG_WRAPPED_WHIRLPOOL]   = STRINGID_PKMNTRAPPEDINVORTEX,    // MOVE_WHIRLPOOL
    [B_MSG_WRAPPED_SAND_TOMB]   = STRINGID_PKMNTRAPPEDBYSANDTOMB,  // MOVE_SAND_TOMB
    [B_MSG_WRAPPED_MAGMA_STORM] = STRINGID_TRAPPEDBYSWIRLINGMAGMA, // MOVE_MAGMA_STORM
    [B_MSG_WRAPPED_INFESTATION] = STRINGID_INFESTATION,            // MOVE_INFESTATION
    [B_MSG_WRAPPED_SNAP_TRAP]   = STRINGID_PKMNINSNAPTRAP,         // MOVE_SNAP_TRAP
    [B_MSG_WRAPPED_THUNDER_CAGE]= STRINGID_THUNDERCAGETRAPPED,     // MOVE_THUNDER_CAGE
};

const u16 gMistUsedStringIds[] =
{
    [B_MSG_SET_MIST]    = STRINGID_PKMNSHROUDEDINMIST,
    [B_MSG_MIST_FAILED] = STRINGID_BUTITFAILED
};

const u16 gFocusEnergyUsedStringIds[] =
{
    [B_MSG_GETTING_PUMPED]      = STRINGID_PKMNGETTINGPUMPED,
    [B_MSG_FOCUS_ENERGY_FAILED] = STRINGID_BUTITFAILED
};

const u16 gTransformUsedStringIds[] =
{
    [B_MSG_TRANSFORMED]      = STRINGID_PKMNTRANSFORMEDINTO,
    [B_MSG_TRANSFORM_FAILED] = STRINGID_BUTITFAILED
};

const u16 gSubstituteUsedStringIds[] =
{
    [B_MSG_SET_SUBSTITUTE]    = STRINGID_PKMNMADESUBSTITUTE,
    [B_MSG_SUBSTITUTE_FAILED] = STRINGID_TOOWEAKFORSUBSTITUTE
};

const u16 gGotPoisonedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASPOISONED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNPOISONEDBY
};

const u16 gGotParalyzedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASPARALYZED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNWASPARALYZEDBY
};

const u16 gFellAsleepStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNFELLASLEEP,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNMADESLEEP,
};

const u16 gGotBurnedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASBURNED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNBURNEDBY
};

const u16 gGotFrostbiteStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNGOTFROSTBITE,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNGOTFROSTBITE,
};

const u16 gFrostbiteHealedStringIds[] =
{
    [B_MSG_FROSTBITE_HEALED]         = STRINGID_PKMNFROSTBITEHEALED,
    [B_MSG_FROSTBITE_HEALED_BY_MOVE] = STRINGID_PKMNFROSTBITEHEALEDBY
};

const u16 gGotFrozenStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASFROZEN,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNFROZENBY
};

const u16 gGotDefrostedStringIds[] =
{
    [B_MSG_DEFROSTED]         = STRINGID_PKMNWASDEFROSTED,
    [B_MSG_DEFROSTED_BY_MOVE] = STRINGID_PKMNWASDEFROSTEDBY
};

const u16 gKOFailedStringIds[] =
{
    [B_MSG_KO_MISS]       = STRINGID_PKMNEVADEDATTACK,
    [B_MSG_KO_UNAFFECTED] = STRINGID_PKMNUNAFFECTED
};

const u16 gAttractUsedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNFELLINLOVE,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNSXINFATUATEDY
};

const u16 gAbsorbDrainStringIds[] =
{
    [B_MSG_ABSORB]      = STRINGID_PKMNENERGYDRAINED,
    [B_MSG_ABSORB_OOZE] = STRINGID_ITSUCKEDLIQUIDOOZE
};

const u16 gSportsUsedStringIds[] =
{
    [B_MSG_WEAKEN_ELECTRIC] = STRINGID_ELECTRICITYWEAKENED,
    [B_MSG_WEAKEN_FIRE]     = STRINGID_FIREWEAKENED
};

const u16 gPartyStatusHealStringIds[] =
{
    [B_MSG_BELL]                     = STRINGID_BELLCHIMED,
    [B_MSG_BELL_SOUNDPROOF_ATTACKER] = STRINGID_BELLCHIMED,
    [B_MSG_BELL_SOUNDPROOF_PARTNER]  = STRINGID_BELLCHIMED,
    [B_MSG_BELL_BOTH_SOUNDPROOF]     = STRINGID_BELLCHIMED,
    [B_MSG_SOOTHING_AROMA]           = STRINGID_SOOTHINGAROMA
};

const u16 gFutureMoveUsedStringIds[] =
{
    [B_MSG_FUTURE_SIGHT] = STRINGID_PKMNFORESAWATTACK,
    [B_MSG_DOOM_DESIRE]  = STRINGID_PKMNCHOSEXASDESTINY
};

const u16 gBallEscapeStringIds[] =
{
    [BALL_NO_SHAKES]     = STRINGID_PKMNBROKEFREE,
    [BALL_1_SHAKE]       = STRINGID_ITAPPEAREDCAUGHT,
    [BALL_2_SHAKES]      = STRINGID_AARGHALMOSTHADIT,
    [BALL_3_SHAKES_FAIL] = STRINGID_SHOOTSOCLOSE
};

// Overworld weathers that don't have an associated battle weather default to "It is raining."
const u16 gWeatherStartsStringIds[] =
{
    [WEATHER_NONE]               = STRINGID_ITISRAINING,
    [WEATHER_SUNNY_CLOUDS]       = STRINGID_ITISRAINING,
    [WEATHER_SUNNY]              = STRINGID_ITISRAINING,
    [WEATHER_RAIN]               = STRINGID_ITISRAINING,
    [WEATHER_SNOW]               = (B_OVERWORLD_SNOW >= GEN_9 ? STRINGID_ITISSNOWING : STRINGID_ITISHAILING),
    [WEATHER_RAIN_THUNDERSTORM]  = STRINGID_ITISRAINING,
    [WEATHER_FOG_HORIZONTAL]     = STRINGID_FOGISDEEP,
    [WEATHER_VOLCANIC_ASH]       = STRINGID_ITISRAINING,
    [WEATHER_SANDSTORM]          = STRINGID_SANDSTORMISRAGING,
    [WEATHER_FOG_DIAGONAL]       = STRINGID_FOGISDEEP,
    [WEATHER_UNDERWATER]         = STRINGID_ITISRAINING,
    [WEATHER_SHADE]              = STRINGID_ITISRAINING,
    [WEATHER_DROUGHT]            = STRINGID_SUNLIGHTISHARSH,
    [WEATHER_DOWNPOUR]           = STRINGID_ITISRAINING,
    [WEATHER_UNDERWATER_BUBBLES] = STRINGID_ITISRAINING,
    [WEATHER_ABNORMAL]           = STRINGID_ITISRAINING
};

const u16 gTerrainStartsStringIds[] =
{
    [B_MSG_TERRAIN_SET_MISTY]    = STRINGID_MISTSWIRLSAROUND,
    [B_MSG_TERRAIN_SET_ELECTRIC] = STRINGID_ELECTRICCURRENTISRUNNING,
    [B_MSG_TERRAIN_SET_PSYCHIC]  = STRINGID_SEEMSWEIRD,
    [B_MSG_TERRAIN_SET_GRASSY]   = STRINGID_ISCOVEREDWITHGRASS,
};

const u16 gPrimalWeatherBlocksStringIds[] =
{
    [B_MSG_PRIMAL_WEATHER_FIZZLED_BY_RAIN]      = STRINGID_MOVEFIZZLEDOUTINTHEHEAVYRAIN,
    [B_MSG_PRIMAL_WEATHER_EVAPORATED_IN_SUN]    = STRINGID_MOVEEVAPORATEDINTHEHARSHSUNLIGHT,
};

const u16 gInobedientStringIds[] =
{
    [B_MSG_LOAFING]            = STRINGID_PKMNLOAFING,
    [B_MSG_WONT_OBEY]          = STRINGID_PKMNWONTOBEY,
    [B_MSG_TURNED_AWAY]        = STRINGID_PKMNTURNEDAWAY,
    [B_MSG_PRETEND_NOT_NOTICE] = STRINGID_PKMNPRETENDNOTNOTICE,
    [B_MSG_INCAPABLE_OF_POWER] = STRINGID_PKMNINCAPABLEOFPOWER
};

const u16 gSafariReactionStringIds[NUM_SAFARI_REACTIONS] =
{
    [B_MSG_MON_WATCHING] = STRINGID_PKMNWATCHINGCAREFULLY,
    [B_MSG_MON_ANGRY]    = STRINGID_PKMNANGRY,
    [B_MSG_MON_EATING]   = STRINGID_PKMNEATING
};

const u16 gSafariGetNearStringIds[] =
{
    [B_MSG_CREPT_CLOSER]    = STRINGID_CREPTCLOSER,
    [B_MSG_CANT_GET_CLOSER] = STRINGID_CANTGETCLOSER
};

const u16 gSafariPokeblockResultStringIds[] =
{
    [B_MSG_MON_CURIOUS]    = STRINGID_PKMNCURIOUSABOUTX,
    [B_MSG_MON_ENTHRALLED] = STRINGID_PKMNENTHRALLEDBYX,
    [B_MSG_MON_IGNORED]    = STRINGID_PKMNIGNOREDX
};

const u16 CureStatusBerryEffectStringID[] =
{
    [B_MSG_CURED_PARALYSIS] = STRINGID_PKMNSITEMCUREDPARALYSIS,
    [B_MSG_CURED_POISON] = STRINGID_PKMNSITEMCUREDPOISON,
    [B_MSG_CURED_BURN] = STRINGID_PKMNSITEMHEALEDBURN,
    [B_MSG_CURED_FREEZE] = STRINGID_PKMNSITEMDEFROSTEDIT,
    [B_MSG_CURED_FROSTBITE] = STRINGID_PKMNSITEMHEALEDFROSTBITE,
    [B_MSG_CURED_SLEEP] = STRINGID_PKMNSITEMWOKEIT,
    [B_MSG_CURED_CONFUSION] = STRINGID_PKMNSITEMSNAPPEDOUT,
};

const u16 gItemSwapStringIds[] =
{
    [B_MSG_ITEM_SWAP_TAKEN] = STRINGID_PKMNOBTAINEDX,
    [B_MSG_ITEM_SWAP_GIVEN] = STRINGID_PKMNOBTAINEDX2,
    [B_MSG_ITEM_SWAP_BOTH]  = STRINGID_PKMNOBTAINEDXYOBTAINEDZ
};

const u16 gFlashFireStringIds[] =
{
    [B_MSG_FLASH_FIRE_BOOST]    = STRINGID_PKMNRAISEDFIREPOWERWITH,
    [B_MSG_FLASH_FIRE_NO_BOOST] = STRINGID_PKMNSXMADEYINEFFECTIVE
};

const u16 gCaughtMonStringIds[] =
{
    [B_MSG_SENT_SOMEONES_PC]   = STRINGID_PKMNTRANSFERREDSOMEONESPC,
    [B_MSG_SENT_LANETTES_PC]   = STRINGID_PKMNTRANSFERREDLANETTESPC,
    [B_MSG_SOMEONES_BOX_FULL]  = STRINGID_PKMNBOXSOMEONESPCFULL,
    [B_MSG_LANETTES_BOX_FULL]  = STRINGID_PKMNBOXLANETTESPCFULL,
    [B_MSG_SWAPPED_INTO_PARTY] = STRINGID_PKMNSENTTOPCAFTERCATCH,
};

const u16 gRoomsStringIds[] =
{
    STRINGID_PKMNTWISTEDDIMENSIONS, STRINGID_TRICKROOMENDS,
    STRINGID_SWAPSDEFANDSPDEFOFALLPOKEMON, STRINGID_WONDERROOMENDS,
    STRINGID_HELDITEMSLOSEEFFECTS, STRINGID_MAGICROOMENDS,
    STRINGID_EMPTYSTRING3
};

const u16 gStatusConditionsStringIds[] =
{
    STRINGID_PKMNWASPOISONED, STRINGID_PKMNBADLYPOISONED, STRINGID_PKMNWASBURNED, STRINGID_PKMNWASPARALYZED, STRINGID_PKMNFELLASLEEP, STRINGID_PKMNGOTFROSTBITE
};

const u16 gDamageNonTypesStartStringIds[] =
{
    [B_MSG_TRAPPED_WITH_VINES]  = STRINGID_TEAMTRAPPEDWITHVINES,
    [B_MSG_CAUGHT_IN_VORTEX]    = STRINGID_TEAMCAUGHTINVORTEX,
    [B_MSG_SURROUNDED_BY_FIRE]  = STRINGID_TEAMSURROUNDEDBYFIRE,
    [B_MSG_SURROUNDED_BY_ROCKS] = STRINGID_TEAMSURROUNDEDBYROCKS,
};

const u16 gDamageNonTypesDmgStringIds[] =
{
    [B_MSG_HURT_BY_VINES]        = STRINGID_PKMNHURTBYVINES,
    [B_MSG_HURT_BY_VORTEX]       = STRINGID_PKMNHURTBYVORTEX,
    [B_MSG_BURNING_UP]           = STRINGID_PKMNBURNINGUP,
    [B_MSG_HURT_BY_ROCKS_THROWN] = STRINGID_PKMNHURTBYROCKSTHROWN,
};

const u16 gRemoveHazardsStringIds[] =
{
    [HAZARDS_SPIKES] = STRINGID_SPIKESDISAPPEAREDFROMTEAM,
    [HAZARDS_STICKY_WEB] = STRINGID_STICKYWEBDISAPPEAREDFROMTEAM,
    [HAZARDS_TOXIC_SPIKES] = STRINGID_TOXICSPIKESDISAPPEAREDFROMTEAM,
    [HAZARDS_STEALTH_ROCK] = STRINGID_STEALTHROCKDISAPPEAREDFROMTEAM,
    [HAZARDS_STEELSURGE] = STRINGID_SHARPSTEELDISAPPEAREDFROMTEAM,
};

const u16 gZenModeStringIds[] =
{
    [B_MSG_ZEN_MODE_TRIGGERED] = STRINGID_ZENMODETRIGGERED,
    [B_MSG_ZEN_MODE_ENDED] = STRINGID_ZENMODEENDED
};

const u16 gCureStatusStringIds[] = 
{
    [B_MSG_CURED_PARALYSIS] = STRINGID_SCRCUREDPARALYSIS,
    [B_MSG_CURED_POISON] = STRINGID_SCRCUREDPOISON,
    [B_MSG_CURED_BURN] = STRINGID_SCRCUREDBURN,
    [B_MSG_CURED_SLEEP] = STRINGID_SCRCUREDSLEEP,
    [B_MSG_CURED_FREEZE] = STRINGID_PKMNWASDEFROSTED,
    [B_MSG_CURED_FROSTBITE] = STRINGID_PKMNFROSTBITEHEALED,
    [B_MSG_CURED_CONFUSION] = STRINGID_SCRCUREDCONFUSION,
    [B_MSG_CURED_INFATUATION] = STRINGID_PKMNGOTOVERITSINFATUATION,
    [B_MSG_CURED_TAUNT] = STRINGID_PKMNSHOOKOFFTHETAUNT,
};

const u16 gPartyCureStatusStringIds[] = 
{
    [B_MSG_CURED_PARALYSIS] = STRINGID_PARTYCUREDPARALYSIS,
    [B_MSG_CURED_POISON] = STRINGID_PARTYCUREDPOISON,
    [B_MSG_CURED_BURN] = STRINGID_PARTYCUREDBURN,
    [B_MSG_CURED_SLEEP] = STRINGID_PARTYCUREDSLEEP,
    [B_MSG_CURED_FREEZE] = STRINGID_PARTYCUREDFREEZE,
    [B_MSG_CURED_FROSTBITE] = STRINGID_PARTYCUREDFROSTBITE,
    [B_MSG_CURED_CONFUSION] = STRINGID_SCRCUREDCONFUSION,
    [B_MSG_CURED_INFATUATION] = STRINGID_PKMNGOTOVERITSINFATUATION,
    [B_MSG_CURED_TAUNT] = STRINGID_PKMNSHOOKOFFTHETAUNT,
};

const u16 gHurtByStringIds[] =
{
    [B_MSG_HURT] = STRINGID_AFTERMATHDMG,
    [B_MSG_HURT_BY_ITEM] = STRINGID_PKMNHURTSWITH,
};

const u16 gBreakScreensStringIds[] =
{
    [B_MSG_BREAK_REFLECT] = STRINGID_REFLECTWOREOFF,
    [B_MSG_BREAK_LIGHT_SCREEN] = STRINGID_LIGHTSCREENWOREOFF,
    [B_MSG_BREAK_AURORA_VEIL] = STRINGID_AURORAVEILWOREOFF,
};

const u8 gText_PkmnIsEvolving[] = _("……哦！？\n{STR_VAR_1}的样子……！");
const u8 gText_CongratsPkmnEvolved[] = _("恭喜！{STR_VAR_1}\n进化为{STR_VAR_2}了！{WAIT_SE}\p");
const u8 gText_PkmnStoppedEvolving[] = _("什么……？{STR_VAR_1}的\n变化停止了！\p");
const u8 gText_EllipsisQuestionMark[] = _("……？\p");
const u8 gText_WhatWillPkmnDo[] = _("{B_BUFF1}\n要做什么呢？");
const u8 gText_WhatWillPkmnDo2[] = _("{B_PLAYER_NAME}\n要做什么呢？");
const u8 gText_WhatWillWallyDo[] = _("满充\n要做什么呢？");
const u8 gText_LinkStandby[] = _("{PAUSE 16}正在等待连接……");
const u8 gText_BattleMenu[] = _("战斗{CLEAR_TO 56}包包\n宝可梦{CLEAR_TO 56}逃走");
const u8 gText_SafariZoneMenu[] = _("精灵球{CLEAR_TO 56}方块\n靠近{CLEAR_TO 56}逃走");
const u8 gText_SafariZoneMenuFrlg[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW 13 14 15}精灵球{CLEAR_TO 56}诱饵\n石头{CLEAR_TO 56}逃走");
const u8 gText_MoveInterfacePP[] = _("PP");
const u8 gText_MoveInterfaceType[] = _("属性/");
const u8 gText_MoveInterfacePpType[] = _("{PALETTE 5}{BACKGROUND DYNAMIC_COLOR5}{TEXT_COLORS DYNAMIC_COLOR4 DYNAMIC_COLOR6 DYNAMIC_COLOR5}PP\n属性/");
const u8 gText_MoveInterfaceDynamicColors[] = _("{PALETTE 5}{BACKGROUND DYNAMIC_COLOR5}{TEXT_COLORS DYNAMIC_COLOR4 DYNAMIC_COLOR6 DYNAMIC_COLOR5}");
const u8 gText_WhichMoveToForget4[] = _("{PALETTE 5}{BACKGROUND DYNAMIC_COLOR5}{TEXT_COLORS DYNAMIC_COLOR4 DYNAMIC_COLOR6 DYNAMIC_COLOR5}要忘记\n哪个招式？");
const u8 gText_BattleYesNoChoice[] = _("{PALETTE 5}{BACKGROUND DYNAMIC_COLOR5}{TEXT_COLORS DYNAMIC_COLOR4 DYNAMIC_COLOR6 DYNAMIC_COLOR5}是\n否");
const u8 gText_BattleSwitchWhich[] = _("{PALETTE 5}{BACKGROUND DYNAMIC_COLOR5}{TEXT_COLORS DYNAMIC_COLOR4 DYNAMIC_COLOR6 DYNAMIC_COLOR5}与哪个招式\n交换位置?");
const u8 gText_BattleSwitchWhich2[] = _("{PALETTE 5}{BACKGROUND DYNAMIC_COLOR5}{TEXT_COLORS DYNAMIC_COLOR4 DYNAMIC_COLOR6 DYNAMIC_COLOR5}");
const u8 gText_BattleSwitchWhich3[] = _("{UP_ARROW}");
const u8 gText_BattleSwitchWhich4[] = _("{ESCAPE 4}");
const u8 gText_BattleSwitchWhich5[] = _("-");
const u8 gText_SafariBalls[] = _("狩猎球");
const u8 gText_SafariBallLeft[] = _("剩余：$");
const u8 gText_Sleep[] = _("睡眠");
const u8 gText_Poison[] = _("中毒");
const u8 gText_Burn[] = _("灼伤");
const u8 gText_Paralysis[] = _("麻痹");
const u8 gText_Ice[] = _("冰冻");
const u8 gText_Confusion[] = _("混乱");
const u8 gText_Love[] = _("着迷");
const u8 gText_SpaceAndSpace[] = _("和");
const u8 gText_CommaSpace[] = _("、");
const u8 gText_Space2[] = _(" ");
const u8 gText_LineBreak[] = _("\l");
const u8 gText_NewLine[] = _("\n");
const u8 gText_Are[] = _("是");
const u8 gText_Are2[] = _("是");
const u8 gText_BadEgg[] = _("坏蛋");
const u8 gText_BattleWallyName[] = _("满充");
const u8 gText_Win[] = _("{BACKGROUND TRANSPARENT}{ACCENT TRANSPARENT}胜");
const u8 gText_Loss[] = _("{BACKGROUND TRANSPARENT}{ACCENT TRANSPARENT}负");
const u8 gText_Draw[] = _("{BACKGROUND TRANSPARENT}{ACCENT TRANSPARENT}平");
static const u8 sText_SpaceIs[] = _("是");
static const u8 sText_ApostropheS[] = _("的");
const u8 gText_BattleTourney[] = _("赛程");

const u8 *const gRoundsStringTable[DOME_ROUNDS_COUNT] =
{
    [DOME_ROUND1]    = COMPOUND_STRING("第1轮比赛"),
    [DOME_ROUND2]    = COMPOUND_STRING("第2轮比赛"),
    [DOME_SEMIFINAL] = COMPOUND_STRING("半决赛"),
    [DOME_FINAL]     = COMPOUND_STRING("决赛"),
};

const u8 gText_TheGreatNewHope[] = _("伟大的崭新希望！\p");
const u8 gText_WillChampionshipDreamComeTrue[] = _("冠军之梦能否成真？！\p");
const u8 gText_AFormerChampion[] = _("前冠军！\p");
const u8 gText_ThePreviousChampion[] = _("前冠军！\p");
const u8 gText_TheUnbeatenChampion[] = _("不败冠军！\p");
const u8 gText_PlayerMon1Name[] = _("{B_PLAYER_MON1_NAME}");
const u8 gText_Vs[] = _("VS");
const u8 gText_OpponentMon1Name[] = _("{B_OPPONENT_MON1_NAME}");
const u8 gText_Mind[] = _("心");
const u8 gText_Skill[] = _("技");
const u8 gText_Body[] = _("体");
const u8 gText_Judgment[] = _("{B_BUFF1}{CLEAR 13}判定{CLEAR 13}{B_BUFF2}");
static const u8 sText_TwoTrainersSentPkmn[] = _("{B_TRAINER1_NAME_WITH_CLASS}\n派出了{B_OPPONENT_MON1_NAME}！\p{B_TRAINER2_NAME_WITH_CLASS}\n派出了{B_OPPONENT_MON2_NAME}！");
static const u8 sText_Trainer2SentOutPkmn[] = _("{B_TRAINER2_NAME_WITH_CLASS}\n派出了{B_BUFF1}！");
static const u8 sText_TwoTrainersWantToBattle[] = _("{B_TRAINER1_NAME_WITH_CLASS}和\n{B_TRAINER2_NAME_WITH_CLASS}\l前来挑战了！\p");
static const u8 sText_InGamePartnerSentOutZGoN[] = _("{B_PARTNER_NAME_WITH_CLASS}\n派出了{B_PLAYER_MON2_NAME}！\l上吧！{B_PLAYER_MON1_NAME}！");
static const u8 sText_InGamePartnerSentOutNGoZ[] = _("{B_PARTNER_NAME_WITH_CLASS}\n派出了{B_PLAYER_MON1_NAME}！\l上吧！{B_PLAYER_MON2_NAME}！");
static const u8 sText_InGamePartnerSentOutPkmn1[] = _("{B_PARTNER_NAME_WITH_CLASS}\n派出了{B_PLAYER_MON1_NAME}！");
static const u8 sText_InGamePartnerSentOutPkmn2[] = _("{B_PARTNER_NAME_WITH_CLASS}\n派出了{B_PLAYER_MON2_NAME}！");
static const u8 sText_InGamePartnerWithdrewPkmn1[] = _("{B_PARTNER_NAME_WITH_CLASS}\n换下了{B_PLAYER_MON1_NAME}！");
static const u8 sText_InGamePartnerWithdrewPkmn2[] = _("{B_PARTNER_NAME_WITH_CLASS}\n换下了{B_PLAYER_MON2_NAME}！");

const u16 gBattlePalaceFlavorTextTable[] =
{
    [B_MSG_GLINT_IN_EYE]   = STRINGID_GLINTAPPEARSINEYE,
    [B_MSG_GETTING_IN_POS] = STRINGID_PKMNGETTINGINTOPOSITION,
    [B_MSG_GROWL_DEEPLY]   = STRINGID_PKMNBEGANGROWLINGDEEPLY,
    [B_MSG_EAGER_FOR_MORE] = STRINGID_PKMNEAGERFORMORE,
};

const u8 *const gRefereeStringsTable[] =
{
    [B_MSG_REF_NOTHING_IS_DECIDED] = COMPOUND_STRING("裁判：如果3回合无法决出胜负，\n将由我们来裁定结果！"),
    [B_MSG_REF_THATS_IT]           = COMPOUND_STRING("裁判：到此为止！现在将由\n我们来裁定哪一方获胜！"),
    [B_MSG_REF_JUDGE_MIND]         = COMPOUND_STRING("裁判：判定准则其一，心！\n是否展现出斗志与勇气！\p"),
    [B_MSG_REF_JUDGE_SKILL]        = COMPOUND_STRING("裁判：判定准则其二，技！\n是否准确地使用了招式！\p"),
    [B_MSG_REF_JUDGE_BODY]         = COMPOUND_STRING("裁判：判定准则其三，体！\n是否保留了足够的体力！\p"),
    [B_MSG_REF_PLAYER_WON]         = COMPOUND_STRING("裁判：判定结果：{B_BUFF1}比{B_BUFF2}！\n胜者是{B_PLAYER_NAME}的{B_PLAYER_MON1_NAME}！\p"),
    [B_MSG_REF_OPPONENT_WON]       = COMPOUND_STRING("裁判：判定结果：{B_BUFF1}比{B_BUFF2}！\n胜者是{B_TRAINER1_NAME}的{B_OPPONENT_MON1_NAME}！\p"),
    [B_MSG_REF_DRAW]               = COMPOUND_STRING("裁判：判定结果：3比3！\n双方打成了平手！"),
    [B_MSG_REF_COMMENCE_BATTLE]    = COMPOUND_STRING("裁判：{B_PLAYER_MON1_NAME} VS {B_OPPONENT_MON1_NAME}！\n战斗开始！"),
};

static const u8 sText_Trainer1Fled[] = _( "{PLAY_SE SE_FLEE}{B_TRAINER1_NAME_WITH_CLASS}逃走了！");
static const u8 sText_PlayerLostAgainstTrainer1[] = _("被{B_TRAINER1_NAME_WITH_CLASS}打败了！");
static const u8 sText_PlayerBattledToDrawTrainer1[] = _("和{B_TRAINER1_NAME_WITH_CLASS}打成了平局！");
const u8 gText_RecordBattleToPass[] = _("要把你本次的对战\n保存到开拓通行证上吗？");
const u8 gText_BattleRecordedOnPass[] = _("{B_PLAYER_NAME}本次的对战\n保存到了开拓通行证中！");
static const u8 sText_LinkTrainerWantsToBattlePause[] = _("{B_LINK_OPPONENT1_NAME}\n前来挑战了！{PAUSE 49}");
static const u8 sText_TwoLinkTrainersWantToBattlePause[] = _("{B_LINK_OPPONENT1_NAME}和{B_LINK_OPPONENT2_NAME}\n前来挑战了！{PAUSE 49}");
static const u8 sText_Your1[] = _("我方");
static const u8 sText_Opposing1[] = _("对手");
static const u8 sText_Your2[] = _("我方");
static const u8 sText_Opposing2[] = _("对手");
static const u8 sText_EmptyStatus[] = _("$$$$$$$");

static const struct BattleWindowText sTextOnWindowsInfo_Normal[] =
{
    [B_WIN_MSG] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .color.foreground = 1,
        .color.background = 15,
        .color.accent = 15,
        .color.shadow = 6,
    },
    [B_WIN_ACTION_PROMPT] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.background = 15,
        .color.accent = 15,
        .color.shadow = 6,
    },
    [B_WIN_ACTION_MENU] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_PP] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 13 : 12,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 15 : 11,
    },
    [B_WIN_DUMMY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_PP_REMAINING] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 1,
        .speed = 0,
        .color.foreground = 12,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 11,
    },
    [B_WIN_MOVE_TYPE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_YESNO] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = 32,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 2,
    },
    [B_WIN_VS_PLAYER] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_OPPONENT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_OUTCOME_DRAW] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 6,
    },
    [B_WIN_VS_OUTCOME_LEFT] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 6,
    },
    [B_WIN_VS_OUTCOME_RIGHT] = {
        .fillValue = PIXEL_FILL(0x0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 6,
    },
    [B_WIN_MOVE_DESCRIPTION] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .color.foreground = TEXT_DYNAMIC_COLOR_4,
        .color.background = TEXT_DYNAMIC_COLOR_5,
        .color.accent = TEXT_DYNAMIC_COLOR_5,
        .color.shadow = TEXT_DYNAMIC_COLOR_6,
    },
};

static const struct BattleWindowText sTextOnWindowsInfo_KantoTutorial[] =
{
    [B_WIN_MSG] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .color.foreground = 1,
        .color.background = 15,
        .color.accent = 15,
        .color.shadow = 6,
    },
    [B_WIN_ACTION_PROMPT] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.background = 15,
        .color.accent = 15,
        .color.shadow = 6,
    },
    [B_WIN_ACTION_MENU] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_PP] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 13 : 12,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 15 : 11,
    },
    [B_WIN_DUMMY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_PP_REMAINING] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 1,
        .speed = 0,
        .color.foreground = 12,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 11,
    },
    [B_WIN_MOVE_TYPE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_YESNO] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = 32,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 2,
    },
    [B_WIN_VS_PLAYER] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_OPPONENT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_OUTCOME_DRAW] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 6,
    },
    [B_WIN_VS_OUTCOME_LEFT] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 6,
    },
    [B_WIN_VS_OUTCOME_RIGHT] = {
        .fillValue = PIXEL_FILL(0x0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 6,
    },
    [B_WIN_MOVE_DESCRIPTION] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .color.foreground = TEXT_DYNAMIC_COLOR_4,
        .color.background = TEXT_DYNAMIC_COLOR_5,
        .color.accent = TEXT_DYNAMIC_COLOR_5,
        .color.shadow = TEXT_DYNAMIC_COLOR_6,
    },
    [B_WIN_OAK_OLD_MAN] = {
        .fillValue = PIXEL_FILL(0x1),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 1,
        .speed = 1,
        .fgColor = 2,
        .bgColor = 1,
        .shadowColor = 3,
    },
};

static const struct BattleWindowText sTextOnWindowsInfo_Arena[] =
{
    [B_WIN_MSG] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .color.foreground = 1,
        .color.background = 15,
        .color.accent = 15,
        .color.shadow = 6,
    },
    [B_WIN_ACTION_PROMPT] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.background = 15,
        .color.accent = 15,
        .color.shadow = 6,
    },
    [B_WIN_ACTION_MENU] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_PP] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 13 : 12,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 15 : 11,
    },
    [B_WIN_DUMMY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_PP_REMAINING] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 1,
        .speed = 0,
        .color.foreground = 12,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 11,
    },
    [B_WIN_MOVE_TYPE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_YESNO] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = 32,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 2,
    },
    [ARENA_WIN_PLAYER_NAME] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [ARENA_WIN_VS] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [ARENA_WIN_OPPONENT_NAME] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [ARENA_WIN_MIND] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [ARENA_WIN_SKILL] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [ARENA_WIN_BODY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [ARENA_WIN_JUDGMENT_TITLE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [ARENA_WIN_JUDGMENT_TEXT] = {
        .fillValue = PIXEL_FILL(0x1),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .color.foreground = 2,
        .color.background = 1,
        .color.accent = 1,
        .color.shadow = 3,
    },
    [B_WIN_MOVE_DESCRIPTION] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .color.foreground = TEXT_DYNAMIC_COLOR_4,
        .color.background = TEXT_DYNAMIC_COLOR_5,
        .color.accent = TEXT_DYNAMIC_COLOR_5,
        .color.shadow = TEXT_DYNAMIC_COLOR_6,
    },
};

static const struct BattleWindowText *const sBattleTextOnWindowsInfo[] =
{
    [B_WIN_TYPE_NORMAL] = sTextOnWindowsInfo_Normal,
    [B_WIN_TYPE_ARENA]  = sTextOnWindowsInfo_Arena,
    [B_WIN_TYPE_KANTO_TUTORIAL] = sTextOnWindowsInfo_KantoTutorial,
};

static const u8 sRecordedBattleTextSpeeds[] = {8, 4, 1, 0};

void BufferStringBattle(enum StringID stringID, enum BattlerId battler)
{
    s32 i;
    const u8 *stringPtr = NULL;

    gBattleMsgDataPtr = (struct BattleMsgData *)(&gBattleResources->bufferA[battler][4]);
    gLastUsedItem = gBattleMsgDataPtr->lastItem;
    gLastUsedAbility = gBattleMsgDataPtr->lastAbility;
    gBattleScripting.battler = gBattleMsgDataPtr->scrActive;
    gBattleStruct->scriptPartyIdx = gBattleMsgDataPtr->bakScriptPartyIdx;
    gBattleStruct->hpScale = gBattleMsgDataPtr->hpScale;
    gPotentialItemEffectBattler = gBattleMsgDataPtr->itemEffectBattler;
    gBattleStruct->stringMoveType = gBattleMsgDataPtr->moveType;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        sBattlerAbilities[i] = gBattleMsgDataPtr->abilities[i];
    }
    for (i = 0; i < TEXT_BUFF_ARRAY_COUNT; i++)
    {
        gBattleTextBuff1[i] = gBattleMsgDataPtr->textBuffs[0][i];
        gBattleTextBuff2[i] = gBattleMsgDataPtr->textBuffs[1][i];
        gBattleTextBuff3[i] = gBattleMsgDataPtr->textBuffs[2][i];
    }

    switch (stringID)
    {
    case STRINGID_INTROMSG: // first battle msg
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                {
                    stringPtr = sText_TwoTrainersWantToBattle;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                {
                    stringPtr = sText_TwoLinkTrainersWantToBattle;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                    {
                        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
                            stringPtr = sText_LinkTrainerWantsToBattle;
                        else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                            stringPtr = sText_TwoTrainersWantToBattle;
                        else if (!(gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS))
                            stringPtr = sText_LinkTrainerWantsToBattlePause;
                        else
                            stringPtr = sText_TwoLinkTrainersWantToBattlePause;
                    }
                    else
                    {
                        stringPtr = sText_TwoLinkTrainersWantToBattle;
                    }
                }
                else
                {
                    if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_UNION_ROOM)
                        stringPtr = sText_Trainer1WantsToBattle;
                    else if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                        stringPtr = sText_LinkTrainerWantsToBattlePause;
                    else
                        stringPtr = sText_LinkTrainerWantsToBattle;
                }
            }
            else
            {
                if (BATTLE_TWO_VS_ONE_OPPONENT)
                    stringPtr = sText_Trainer1WantsToBattle;
                else if (gBattleTypeFlags & (BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER))
                    stringPtr = sText_TwoTrainersWantToBattle;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_TwoTrainersWantToBattle;
                else
                    stringPtr = sText_Trainer1WantsToBattle;
            }
        }
        else
        {
            if (IsGhostBattleWithoutScope())
                stringPtr = sText_GhostAppearedCantId;
            else if (gBattleTypeFlags & BATTLE_TYPE_GHOST)
                stringPtr = sText_TheGhostAppeared;
            else if (gBattleTypeFlags & BATTLE_TYPE_LEGENDARY)
                stringPtr = sText_LegendaryPkmnAppeared;
            else if (IsDoubleBattle() && IsValidForBattle(GetBattlerMon(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT))))
                stringPtr = sText_TwoWildPkmnAppeared;
            else if (gBattleTypeFlags & BATTLE_TYPE_CATCH_TUTORIAL)
                stringPtr = sText_WildPkmnAppearedPause;
            else
                stringPtr = sText_WildPkmnAppeared;
        }
        break;
    case STRINGID_INTROSENDOUT: // poke first send-out
        if (BattlerIsPlayer(battler) || BattlerIsPlayer(BATTLE_PARTNER(battler))
         || BattlerIsWally(battler) || BattlerIsWally(BATTLE_PARTNER(battler)))
        {
            if (IsDoubleBattle() && IsValidForBattle(GetBattlerMon(BATTLE_PARTNER(battler))))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_MULTI && (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK || gBattleTypeFlags & BATTLE_TYPE_LINK))
                {
                    if (BattlerIsPlayer(battler))
                        stringPtr = sText_LinkPartnerSentOutPkmn2GoPkmn; // Player is on left
                    else
                        stringPtr = sText_LinkPartnerSentOutPkmn1GoPkmn; // Link Partner on left
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                {
                    if (BattlerIsPlayer(battler) && (battler & BIT_FLANK) == B_FLANK_LEFT)
                        stringPtr = sText_InGamePartnerSentOutZGoN; // Player is on left
                    else
                        stringPtr = sText_InGamePartnerSentOutNGoZ; // Partner on left
                }
                else
                {
                    stringPtr = sText_GoTwoPkmn;
                }
            }
            else
            {
                stringPtr = sText_GoPkmn;
            }
        }
        else
        {
            if (IsDoubleBattle() && IsValidForBattle(GetBattlerMon(BATTLE_PARTNER(battler))))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK && BATTLE_TWO_VS_ONE_OPPONENT)
                    stringPtr = sText_LinkTrainerSentOutTwoPkmn;
                else if (BATTLE_TWO_VS_ONE_OPPONENT)
                    stringPtr = sText_Trainer1SentOutTwoPkmn;
                else if ((gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK && gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS) || (gBattleTypeFlags & BATTLE_TYPE_MULTI && (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK || gBattleTypeFlags & BATTLE_TYPE_LINK)))
                    stringPtr = sText_TwoLinkTrainersIntroSendOutPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS || gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                    stringPtr = sText_TwoTrainersSentPkmn;
                else if (BattlerIsLink(battler) || (BattlerIsRecorded(battler) && BattlerIsOpponent(battler))) // Link Opponent doubles and test opponent
                    stringPtr = sText_LinkTrainerSentOutTwoPkmn;
                else
                    stringPtr = sText_Trainer1SentOutTwoPkmn;
            }
            else if (BattlerIsLink(battler) || (BattlerIsRecorded(battler) && BattlerIsOpponent(battler)))
            {
                if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_UNION_ROOM)
                    stringPtr = sText_Trainer1SentOutPkmn;
                else
                    stringPtr = sText_LinkTrainerIntroSendOutPkmn;
            }
            else
            {
                stringPtr = sText_Trainer1SentOutPkmn;
            }
        }
        break;
    case STRINGID_RETURNMON: // sending poke to ball msg
        if ((GetBattlerPosition(battler) & BIT_FLANK) == B_FLANK_LEFT) // battler 0 and 1
        {
            if (BattlerIsPlayer(battler) || BattlerIsWally(battler)) // Player
            {
                if (*(&gBattleStruct->hpScale) == 0)
                    stringPtr = sText_PkmnThatsEnough;
                else if (*(&gBattleStruct->hpScale) == 1 || IsDoubleBattle())
                    stringPtr = sText_PkmnComeBack;
                else if (*(&gBattleStruct->hpScale) == 2)
                    stringPtr = sText_PkmnOkComeBack;
                else
                    stringPtr = sText_PkmnGoodComeBack;
            }
            else if (BattlerIsPartner(battler)) // Link or Ingame Partner
            {
                if (BattlerIsLink(battler) || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
                    stringPtr = sText_LinkPartnerWithdrewPkmn1;
                else
                    stringPtr = sText_InGamePartnerWithdrewPkmn1;
            }
            else if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_LINK_OPPONENT
             || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK) // Link Opponent A and test opponent
            {
                stringPtr = sText_LinkTrainer1WithdrewPkmn;
            }
            else // Opponent A
            {
                stringPtr = sText_Trainer1WithdrewPkmn;
            }
        }
        else // battler 2 and 3
        {
            if (BattlerIsPlayer(battler)) // Player
            {
                if (*(&gBattleStruct->hpScale) == 0)
                    stringPtr = sText_PkmnThatsEnough;
                else if (*(&gBattleStruct->hpScale) == 1 || IsDoubleBattle())
                    stringPtr = sText_PkmnComeBack;
                else if (*(&gBattleStruct->hpScale) == 2)
                    stringPtr = sText_PkmnOkComeBack;
                else
                    stringPtr = sText_PkmnGoodComeBack;
            }
            else if (BattlerIsPartner(battler)) // Link or Ingame Partner
            {
                if (BattlerIsLink(battler) || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
                    stringPtr = sText_LinkPartnerWithdrewPkmn2;
                else
                    stringPtr = sText_InGamePartnerWithdrewPkmn2;
            }
            else if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_LINK_OPPONENT
             || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK) // Link Opponent B and test opponent
            {
                if (BattleSideHasTwoTrainers(B_SIDE_OPPONENT))
                    stringPtr = sText_LinkTrainer2WithdrewPkmn;
                else
                    stringPtr = sText_LinkTrainer1WithdrewPkmn;
            }
            else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS) // Opponent B
            {
                stringPtr = sText_Trainer2WithdrewPkmn;
            }
            else // Opponent A
            {
                stringPtr = sText_Trainer1WithdrewPkmn;
            }
        }
        break;
    case STRINGID_SWITCHINMON: // switch-in msg
        if ((GetBattlerPosition(gBattleScripting.battler) & BIT_FLANK) == B_FLANK_LEFT) // battler 0 and 1
        {
            if (BattlerIsPlayer(gBattleScripting.battler)) // Player
            {
                if (*(&gBattleStruct->hpScale) == 0)
                    stringPtr = sText_GoPkmn2;
                else if (*(&gBattleStruct->hpScale) == 1 || IsDoubleBattle())
                    stringPtr = sText_DoItPkmn;
                else if (*(&gBattleStruct->hpScale) == 2)
                    stringPtr = sText_GoForItPkmn;
                else
                    stringPtr = sText_YourFoesWeakGetEmPkmn;
            }
            else if (BattlerIsPartner(gBattleScripting.battler)) // Link or Ingame Partner
            {
                if (BattlerIsLink(gBattleScripting.battler) || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
                    stringPtr = sText_LinkPartnerSentOutPkmn1;
                else
                    stringPtr = sText_InGamePartnerSentOutPkmn1;
            }
            else if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_LINK_OPPONENT
             || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK) // Link Opponent A and test opponent
            {
                stringPtr = sText_LinkTrainerSentOutPkmn;
            }
            else // Opponent A
            {
                stringPtr = sText_Trainer1SentOutPkmn;
            }
        }
        else // battler 2 and 3
        {
            if (BattlerIsPlayer(gBattleScripting.battler)) // Player
            {
                if (*(&gBattleStruct->hpScale) == 0)
                    stringPtr = sText_GoPkmn2;
                else if (*(&gBattleStruct->hpScale) == 1 || IsDoubleBattle())
                    stringPtr = sText_DoItPkmn;
                else if (*(&gBattleStruct->hpScale) == 2)
                    stringPtr = sText_GoForItPkmn;
                else
                    stringPtr = sText_YourFoesWeakGetEmPkmn;
            }
            else if (BattlerIsPartner(gBattleScripting.battler)) // Link or Ingame Partner
            {
                if (BattlerIsLink(gBattleScripting.battler) || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
                    stringPtr = sText_LinkPartnerSentOutPkmn2;
                else
                    stringPtr = sText_InGamePartnerSentOutPkmn2;
            }
            else if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_LINK_OPPONENT
             || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK) // Link Opponent B and test opponent
            {
                if (BattleSideHasTwoTrainers(B_SIDE_OPPONENT))
                    stringPtr = sText_LinkTrainer2SentOutPkmn2;
                else
                    stringPtr = sText_LinkTrainerSentOutPkmn2;
            }
            else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS) // Opponent B
            {
                stringPtr = sText_Trainer2SentOutPkmn;
            }
            else // Single trainer double Opponent A
            {
                stringPtr = sText_Trainer1SentOutPkmn2;
            }
        }
        break;
    case STRINGID_USEDMOVE: // Pokémon used a move msg
        if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT
         && !IsZMove(gBattleMsgDataPtr->currentMove)
         && !IsMaxMove(gBattleMsgDataPtr->currentMove))
            StringCopy(gBattleTextBuff3, gTypesInfo[*(&gBattleStruct->stringMoveType)].generic);
        else
            StringCopy(gBattleTextBuff3, GetMoveName(gBattleMsgDataPtr->currentMove));
        stringPtr = sText_AttackerUsedX;
        break;
    case STRINGID_BATTLEEND: // battle end
        if (gBattleTextBuff1[0] & B_OUTCOME_LINK_BATTLE_RAN)
        {
            gBattleTextBuff1[0] &= ~(B_OUTCOME_LINK_BATTLE_RAN);
            if (!(BattlerIsPlayer(battler) || BattlerIsPlayer(BATTLE_PARTNER(battler))) && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTextBuff1[0] == B_OUTCOME_LOST || gBattleTextBuff1[0] == B_OUTCOME_DREW)
                stringPtr = sText_GotAwaySafely;
            else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                stringPtr = sText_TwoWildFled;
            else
                stringPtr = sText_WildFled;
        }
        else
        {
            if (!(BattlerIsPlayer(battler) || BattlerIsPlayer(BATTLE_PARTNER(battler))) && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                        stringPtr = sText_TwoInGameTrainersDefeated;
                    else
                        stringPtr = sText_TwoLinkTrainersDefeated;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostToTwo;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawVsTwo;
                    break;
                }
            }
            else if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_UNION_ROOM)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainerTrainer1;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstTrainer1;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawTrainer1;
                    break;
                }
            }
            else
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainer;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstLinkTrainer;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawLinkTrainer;
                    break;
                }
            }
        }
        break;
    case STRINGID_TRAINERSLIDE:
        stringPtr = gBattleStruct->trainerSlideMsg;
        break;
    default: // load a string from the table
        if (stringID >= STRINGID_COUNT)
        {
            gDisplayedStringBattle[0] = EOS;
            return;
        }
        else
        {
            stringPtr = gBattleStringsTable[stringID];
        }
        break;
    }

    BattleStringExpandPlaceholdersToDisplayedString(stringPtr);
}

u32 BattleStringExpandPlaceholdersToDisplayedString(const u8 *src)
{
#ifndef NDEBUG
    u32 j, strWidth;
    u32 dstID = BattleStringExpandPlaceholders(src, gDisplayedStringBattle, sizeof(gDisplayedStringBattle));
    for (j = 1;; j++)
    {
        strWidth = GetStringLineWidth(0, gDisplayedStringBattle, 0, j, sizeof(gDisplayedStringBattle));
        if (strWidth == 0)
            break;
    }
    return dstID;
#else
    return BattleStringExpandPlaceholders(src, gDisplayedStringBattle, sizeof(gDisplayedStringBattle));
#endif
}

static const u8 *TryGetStatusString(u8 *src)
{
    u32 i;
    u8 status[8];
    u32 chars1, chars2;
    u8 *statusPtr;

    memcpy(status, sText_EmptyStatus, min(ARRAY_COUNT(status), ARRAY_COUNT(sText_EmptyStatus)));

    statusPtr = status;
    for (i = 0; i < ARRAY_COUNT(status); i++)
    {
        if (*src == EOS) break; // one line required to match -g
        *statusPtr = *src;
        src++;
        statusPtr++;
    }

    chars1 = *(u32 *)(&status[0]);
    chars2 = *(u32 *)(&status[4]);

    for (i = 0; i < ARRAY_COUNT(gStatusConditionStringsTable); i++)
    {
        if (chars1 == *(u32 *)(&gStatusConditionStringsTable[i][0][0])
            && chars2 == *(u32 *)(&gStatusConditionStringsTable[i][0][4]))
            return gStatusConditionStringsTable[i][1];
    }
    return NULL;
}

static void GetBattlerNick(enum BattlerId battler, u8 *dst)
{
    struct Pokemon *illusionMon = GetIllusionMonPtr(battler);
    struct Pokemon *mon = GetBattlerMon(battler);

    if (illusionMon != NULL)
        mon = illusionMon;
    GetMonData(mon, MON_DATA_NICKNAME, dst);
    StringGet_Nickname(dst);
}

#define HANDLE_NICKNAME_STRING_CASE(battler)                            \
    if (!IsOnPlayerSide(battler))                                       \
    {                                                                   \
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)                     \
            toCpy = sText_FoePkmnPrefix;                                \
        else                                                            \
            toCpy = sText_WildPkmnPrefix;                               \
        while (*toCpy != EOS)                                           \
        {                                                               \
            dst[dstID] = *toCpy;                                        \
            dstID++;                                                    \
            toCpy++;                                                    \
        }                                                               \
    }                                                                   \
    GetBattlerNick(battler, text);                                      \
    toCpy = text;

#define HANDLE_NICKNAME_STRING_LOWERCASE(battler)                       \
    if (!IsOnPlayerSide(battler))                       \
    {                                                                   \
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)                     \
            toCpy = sText_FoePkmnPrefixLower;                           \
        else                                                            \
            toCpy = sText_WildPkmnPrefixLower;                          \
        while (*toCpy != EOS)                                           \
        {                                                               \
            dst[dstID] = *toCpy;                                        \
            dstID++;                                                    \
            toCpy++;                                                    \
        }                                                               \
    }                                                                   \
    GetBattlerNick(battler, text);                                      \
    toCpy = text;

static const u8 *BattleStringGetOpponentNameByTrainerId(u16 trainerId, u8 *text, u8 multiplayerId, enum BattlerId battler)
{
    const u8 *toCpy = NULL;

    if (gBattleTypeFlags & BATTLE_TYPE_SECRET_BASE)
    {
        u32 i;
        for (i = 0; i < ARRAY_COUNT(gBattleResources->secretBase->trainerName); i++)
            text[i] = gBattleResources->secretBase->trainerName[i];
        text[i] = EOS;
        ConvertInternationalString(text, gBattleResources->secretBase->language);
        toCpy = text;
    }
    else if (trainerId == TRAINER_UNION_ROOM)
    {
        toCpy = gLinkPlayers[multiplayerId ^ BIT_SIDE].name;
    }
    else if (trainerId == TRAINER_LINK_OPPONENT)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            toCpy = gLinkPlayers[GetBattlerMultiplayerId(battler)].name;
        else
            toCpy = gLinkPlayers[GetBattlerMultiplayerId(battler) & BIT_SIDE].name;
    }
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        CopyFrontierBrainTrainerName(text);
        toCpy = text;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
    {
        GetFrontierTrainerName(text, trainerId);
        toCpy = text;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER && gMapHeader.regionMapSectionId == MAPSEC_TRAINER_TOWER_2)
    {
        GetTrainerTowerOpponentName(text);
        toCpy = text;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
    {
        GetTrainerHillTrainerName(text, trainerId);
        toCpy = text;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
    {
        GetEreaderTrainerName(text);
        toCpy = text;
    }
    else
    {
        enum TrainerClassID trainerClass = GetTrainerClassFromId(TRAINER_BATTLE_PARAM.opponentA);

        if (trainerClass == TRAINER_CLASS_RIVAL_EARLY_FRLG || trainerClass == TRAINER_CLASS_RIVAL_LATE_FRLG || trainerClass == TRAINER_CLASS_CHAMPION_FRLG)
            toCpy = GetExpandedPlaceholder(PLACEHOLDER_ID_RIVAL);
        else
            toCpy = GetTrainerNameFromId(trainerId);
    }

    assertf(DoesStringProperlyTerminate(toCpy, TRAINER_NAME_LENGTH + 1),"Opponent needs a valid name")
    {
        return sText_EmptyString4;
    }

    return toCpy;
}

static const u8 *BattleStringGetOpponentName(u8 *text, u8 multiplayerId, enum BattlerId battler)
{
    const u8 *toCpy = NULL;

    switch (GetBattlerPosition(battler))
    {
    case B_POSITION_OPPONENT_LEFT:
        toCpy = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentA, text, multiplayerId, battler);
        break;
    case B_POSITION_OPPONENT_RIGHT:
        if (gBattleTypeFlags & (BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_MULTI) && !BATTLE_TWO_VS_ONE_OPPONENT)
            toCpy = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentB, text, multiplayerId, battler);
        else
            toCpy = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentA, text, multiplayerId, battler);
        break;
    default:
        break;
    }

    return toCpy;
}

static const u8 *BattleStringGetPlayerName(u8 *text, enum BattlerId battler)
{
    const u8 *toCpy = NULL;

    switch (GetBattlerPosition(battler))
    {
    case B_POSITION_PLAYER_LEFT:
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            toCpy = gLinkPlayers[0].name;
        else
            toCpy = gSaveBlock2Ptr->playerName;
        break;
    case B_POSITION_PLAYER_RIGHT:
        if (((gBattleTypeFlags & BATTLE_TYPE_RECORDED) && !(gBattleTypeFlags & (BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER)))
            || gTestRunnerEnabled)
        {
            toCpy = gLinkPlayers[0].name;
        }
        else if ((gBattleTypeFlags & BATTLE_TYPE_LINK) && gBattleTypeFlags & (BATTLE_TYPE_RECORDED | BATTLE_TYPE_MULTI))
        {
            toCpy = gLinkPlayers[2].name;
        }
        else if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
        {
            GetFrontierTrainerName(text, gPartnerTrainerId);
            toCpy = text;
        }
        else
        {
            toCpy = gSaveBlock2Ptr->playerName;
        }
        break;
    default:
        break;
    }

    return toCpy;
}

static const u8 *BattleStringGetTrainerName(u8 *text, u8 multiplayerId, enum BattlerId battler)
{
    if (IsOnPlayerSide(battler))
        return BattleStringGetPlayerName(text, battler);
    else
        return BattleStringGetOpponentName(text, multiplayerId, battler);
}

static const u8 *BattleStringGetOpponentClassByTrainerId(u16 trainerId)
{
    const u8 *toCpy;

    if (gBattleTypeFlags & BATTLE_TYPE_SECRET_BASE)
        toCpy = gTrainerClasses[GetSecretBaseTrainerClass()].name;
    else if (trainerId == TRAINER_UNION_ROOM)
        toCpy = gTrainerClasses[GetUnionRoomTrainerClass()].name;
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
        toCpy = gTrainerClasses[GetFrontierBrainTrainerClass()].name;
    else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
        toCpy = gTrainerClasses[GetFrontierOpponentClass(trainerId)].name;
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER && gMapHeader.regionMapSectionId == MAPSEC_TRAINER_TOWER_2)
        toCpy = gTrainerClasses[GetTrainerTowerOpponentClass()].name;
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
        toCpy = gTrainerClasses[GetTrainerHillOpponentClass(trainerId)].name;
    else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
        toCpy = gTrainerClasses[GetEreaderTrainerClassId()].name;
    else if (trainerId == TRAINER_LINK_OPPONENT)
        toCpy = gTrainerClasses[TRAINER_NONE].name;
    else
        toCpy = gTrainerClasses[GetTrainerClassFromId(trainerId)].name;

    return toCpy;
}

// Ensure the defined length for an item name can contain the full defined length of a berry name.
// This ensures that custom Enigma Berry names will fit in the text buffer at the top of BattleStringExpandPlaceholders.
STATIC_ASSERT(BERRY_NAME_LENGTH + ARRAY_COUNT(sText_BerrySuffix) <= ITEM_NAME_LENGTH, BerryNameTooLong);

u32 BattleStringExpandPlaceholders(const u8 *src, u8 *dst, u32 dstSize)
{
    u32 dstID = 0; // if they used dstID, why not use srcID as well?
    const u8 *toCpy = NULL;
    u8 text[max(max(max(32, TRAINER_NAME_LENGTH + 1), POKEMON_NAME_LENGTH + 1), ITEM_NAME_LENGTH)];
    u8 *textStart = &text[0];
    u8 multiplayerId;
    u8 fontId = FONT_NORMAL;

    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
        multiplayerId = gRecordedBattleMultiplayerId;
    else
        multiplayerId = GetMultiplayerId();

    // Clear destination first
    while (dstID < dstSize)
    {
        dst[dstID] = EOS;
        dstID++;
    }

    dstID = 0;
    while (*src != EOS)
    {
        toCpy = NULL;

        if (*src == PLACEHOLDER_BEGIN)
        {
            src++;
            u32 classLength = 0;
            u32 nameLength = 0;
            const u8 *classString;
            const u8 *nameString;
            switch (*src)
            {
            case B_TXT_BUFF1:
                if (gBattleTextBuff1[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff1, gStringVar1);
                    toCpy = gStringVar1;
                }
                else
                {
                    toCpy = TryGetStatusString(gBattleTextBuff1);
                    if (toCpy == NULL)
                        toCpy = gBattleTextBuff1;
                }
                break;
            case B_TXT_BUFF2:
                if (gBattleTextBuff2[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff2, gStringVar2);
                    toCpy = gStringVar2;
                }
                else
                {
                    toCpy = gBattleTextBuff2;
                }
                break;
            case B_TXT_BUFF3:
                if (gBattleTextBuff3[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff3, gStringVar3);
                    toCpy = gStringVar3;
                }
                else
                {
                    toCpy = gBattleTextBuff3;
                }
                break;
            case B_TXT_COPY_VAR_1:
                toCpy = gStringVar1;
                break;
            case B_TXT_COPY_VAR_2:
                toCpy = gStringVar2;
                break;
            case B_TXT_COPY_VAR_3:
                toCpy = gStringVar3;
                break;
            case B_TXT_PLAYER_MON1_NAME: // first player poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT), text);
                toCpy = text;
                break;
            case B_TXT_OPPONENT_MON1_NAME: // first enemy poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), text);
                toCpy = text;
                break;
            case B_TXT_PLAYER_MON2_NAME: // second player poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT), text);
                toCpy = text;
                break;
            case B_TXT_OPPONENT_MON2_NAME: // second enemy poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT), text);
                toCpy = text;
                break;
            case B_TXT_LINK_PLAYER_MON1_NAME: // link first player poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT), text);
                toCpy = text;
                break;
            case B_TXT_LINK_OPPONENT_MON1_NAME: // link first opponent poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), text);
                toCpy = text;
                break;
            case B_TXT_LINK_PLAYER_MON2_NAME: // link second player poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT), text);
                toCpy = text;
                break;
            case B_TXT_LINK_OPPONENT_MON2_NAME: // link second opponent poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT), text);
                toCpy = text;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX_MON1: // Unused, to change into sth else.
                break;
            case B_TXT_ATK_PARTNER_NAME: // attacker partner name
                GetBattlerNick(BATTLE_PARTNER(gBattlerAttacker), text);
                toCpy = text;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX: // attacker name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattlerAttacker)
                break;
            case B_TXT_DEF_NAME_WITH_PREFIX: // target name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattlerTarget)
                break;
            case B_TXT_DEF_NAME: // target name
                GetBattlerNick(gBattlerTarget, text);
                toCpy = text;
                break;
            case B_TXT_DEF_PARTNER_NAME: // partner target name
                GetBattlerNick(BATTLE_PARTNER(gBattlerTarget), text);
                toCpy = text;
                break;
            case B_TXT_EFF_NAME_WITH_PREFIX: // effect battler name with prefix
                HANDLE_NICKNAME_STRING_CASE(gEffectBattler)
                break;
            case B_TXT_SCR_ACTIVE_NAME_WITH_PREFIX: // scripting active battler name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattleScripting.battler)
                break;
            case B_TXT_CURRENT_MOVE: // current move name
                if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT
                 && !IsZMove(gBattleMsgDataPtr->currentMove)
                 && !IsMaxMove(gBattleMsgDataPtr->currentMove))
                    toCpy = gTypesInfo[gBattleStruct->stringMoveType].generic;
                else
                    toCpy = GetMoveName(gBattleMsgDataPtr->currentMove);
                break;
            case B_TXT_LAST_MOVE: // originally used move name
                if (gBattleMsgDataPtr->originallyUsedMove >= MOVES_COUNT
                 && !IsZMove(gBattleMsgDataPtr->currentMove)
                 && !IsMaxMove(gBattleMsgDataPtr->currentMove))
                    toCpy = gTypesInfo[gBattleStruct->stringMoveType].generic;
                else
                    toCpy = GetMoveName(gBattleMsgDataPtr->originallyUsedMove);
                break;
            case B_TXT_LAST_ITEM: // last used item
                if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
                {
                    if (gLastUsedItem == ITEM_ENIGMA_BERRY_E_READER)
                    {
                        if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
                        {
                            if ((gBattleScripting.multiplayerId != 0 && (gPotentialItemEffectBattler & BIT_SIDE))
                                || (gBattleScripting.multiplayerId == 0 && !(gPotentialItemEffectBattler & BIT_SIDE)))
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                            {
                                toCpy = sText_EnigmaBerry;
                            }
                        }
                        else
                        {
                            if (gLinkPlayers[gBattleScripting.multiplayerId].id == gPotentialItemEffectBattler)
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                            {
                                toCpy = sText_EnigmaBerry;
                            }
                        }
                    }
                    else
                    {
                        CopyItemName(gLastUsedItem, text);
                        toCpy = text;
                    }
                }
                else
                {
                    CopyItemName(gLastUsedItem, text);
                    toCpy = text;
                }
                break;
            case B_TXT_LAST_ABILITY: // last used ability
                toCpy = gAbilitiesInfo[gLastUsedAbility].name;
                break;
            case B_TXT_ATK_ABILITY: // attacker ability
                toCpy = gAbilitiesInfo[sBattlerAbilities[gBattlerAttacker]].name;
                break;
            case B_TXT_DEF_ABILITY: // target ability
                toCpy = gAbilitiesInfo[sBattlerAbilities[gBattlerTarget]].name;
                break;
            case B_TXT_SCR_ACTIVE_ABILITY: // scripting active ability
                toCpy = gAbilitiesInfo[sBattlerAbilities[gBattleScripting.battler]].name;
                break;
            case B_TXT_EFF_ABILITY: // effect battler ability
                toCpy = gAbilitiesInfo[sBattlerAbilities[gEffectBattler]].name;
                break;
            case B_TXT_TRAINER1_CLASS: // trainer class name
                toCpy = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                break;
            case B_TXT_TRAINER1_NAME: // trainer1 name
                toCpy = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentA, text, multiplayerId, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT));
                break;
            case B_TXT_TRAINER1_NAME_WITH_CLASS: // trainer1 name with trainer class
                toCpy = textStart;
                classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                while (classString[classLength] != EOS)
                {
                    textStart[classLength] = classString[classLength];
                    classLength++;
                }
                textStart[classLength] = CHAR_SPACE;
                textStart += classLength + 1;
                nameString = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentA, textStart, multiplayerId, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT));
                if (nameString != textStart)
                {
                    while (nameString[nameLength] != EOS)
                    {
                        textStart[nameLength] = nameString[nameLength];
                        nameLength++;
                    }
                    textStart[nameLength] = EOS;
                }
                break;
            case B_TXT_LINK_PLAYER_NAME: // link player name
                toCpy = gLinkPlayers[multiplayerId].name;
                break;
            case B_TXT_LINK_PARTNER_NAME: // link partner name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_PARTNER(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_OPPONENT1_NAME: // link opponent 1 name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(LEFT_FOE(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_OPPONENT2_NAME: // link opponent 2 name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(RIGHT_FOE(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_SCR_TRAINER_NAME: // link scripting active name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(gBattleScripting.battler)].name;
                break;
            case B_TXT_PLAYER_NAME: // player name
                toCpy = BattleStringGetPlayerName(text, GetBattlerAtPosition(B_POSITION_PLAYER_LEFT));
                break;
            case B_TXT_TRAINER1_LOSE_TEXT: // trainerA lose text
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_WON_TEXT, TRAINER_BATTLE_PARAM.opponentA);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER && gMapHeader.regionMapSectionId == MAPSEC_TRAINER_TOWER_2)
                {
                    GetTrainerTowerOpponentLoseText(gStringVar4, 0);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_WON, TRAINER_BATTLE_PARAM.opponentA);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerALoseText();
                }
                break;
            case B_TXT_TRAINER1_WIN_TEXT: // trainerA win text
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_LOST_TEXT, TRAINER_BATTLE_PARAM.opponentA);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER && gMapHeader.regionMapSectionId == MAPSEC_TRAINER_TOWER_2)
                {
                    GetTrainerTowerOpponentWinText(gStringVar4, 0);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_LOST, TRAINER_BATTLE_PARAM.opponentA);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerWonSpeech();
                }
                break;
            case B_TXT_26: // ?
                if (!IsOnPlayerSide(gBattleScripting.battler))
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                        toCpy = sText_FoePkmnPrefix;
                    else
                        toCpy = sText_WildPkmnPrefix;
                    while (*toCpy != EOS)
                    {
                        dst[dstID] = *toCpy;
                        dstID++;
                        toCpy++;
                    }
                }
                GetMonData(&GetBattlerParty(gBattleScripting.battler)[gBattleStruct->scriptPartyIdx], MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_PC_CREATOR_NAME: // lanette pc
                if (FlagGet(FLAG_SYS_PC_LANETTE))
                    toCpy = IS_FRLG ? sText_Bills : sText_Lanettes;
                else
                    toCpy = sText_Someones;
                break;
            case B_TXT_ATK_PREFIX2:
                if (IsOnPlayerSide(gBattlerAttacker))
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_TXT_DEF_PREFIX2:
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_TXT_ATK_PREFIX1:
                if (IsOnPlayerSide(gBattlerAttacker))
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_TXT_DEF_PREFIX1:
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_TXT_ATK_PREFIX3:
                if (IsOnPlayerSide(gBattlerAttacker))
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break;
            case B_TXT_DEF_PREFIX3:
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break;
            case B_TXT_TRAINER2_CLASS:
                toCpy = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentB);
                break;
            case B_TXT_TRAINER2_NAME:
                toCpy = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentB, text, multiplayerId, GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT));
                break;
            case B_TXT_TRAINER2_NAME_WITH_CLASS:
                toCpy = textStart;
                classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentB);
                while (classString[classLength] != EOS)
                {
                    textStart[classLength] = classString[classLength];
                    classLength++;
                }
                textStart[classLength] = CHAR_SPACE;
                textStart += classLength + 1;
                nameString = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentB, textStart, multiplayerId, GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT));
                if (nameString != textStart)
                {
                    while (nameString[nameLength] != EOS)
                    {
                        textStart[nameLength] = nameString[nameLength];
                        nameLength++;
                    }
                    textStart[nameLength] = EOS;
                }
                break;
            case B_TXT_TRAINER2_LOSE_TEXT:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_WON_TEXT, TRAINER_BATTLE_PARAM.opponentB);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER && gMapHeader.regionMapSectionId == MAPSEC_TRAINER_TOWER_2)
                {
                    GetTrainerTowerOpponentLoseText(gStringVar4, 1);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_WON, TRAINER_BATTLE_PARAM.opponentB);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerBLoseText();
                }
                break;
            case B_TXT_TRAINER2_WIN_TEXT:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_LOST_TEXT, TRAINER_BATTLE_PARAM.opponentB);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER && gMapHeader.regionMapSectionId == MAPSEC_TRAINER_TOWER_2)
                {
                    GetTrainerTowerOpponentWinText(gStringVar4, 1);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_LOST, TRAINER_BATTLE_PARAM.opponentB);
                    toCpy = gStringVar4;
                }
                break;
            case B_TXT_PARTNER_CLASS:
                toCpy = gTrainerClasses[GetFrontierOpponentClass(gPartnerTrainerId)].name;
                break;
            case B_TXT_PARTNER_NAME:
                toCpy = BattleStringGetPlayerName(text, GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT));
                break;
            case B_TXT_PARTNER_NAME_WITH_CLASS:
                toCpy = textStart;
                classString = gTrainerClasses[GetFrontierOpponentClass(gPartnerTrainerId)].name;
                while (classString[classLength] != EOS)
                {
                    textStart[classLength] = classString[classLength];
                    classLength++;
                }
                textStart[classLength] = CHAR_SPACE;
                textStart += classLength + 1;
                nameString = BattleStringGetPlayerName(textStart, GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT));
                if (nameString != textStart)
                {
                    while (nameString[nameLength] != EOS)
                    {
                        textStart[nameLength] = nameString[nameLength];
                        nameLength++;
                    }
                    textStart[nameLength] = EOS;
                }
                break;
            case B_TXT_ATK_TRAINER_NAME:
                toCpy = BattleStringGetTrainerName(text, multiplayerId, gBattlerAttacker);
                break;
            case B_TXT_ATK_TRAINER_CLASS:
                switch (GetBattlerPosition(gBattlerAttacker))
                {
                case B_POSITION_PLAYER_RIGHT:
                    if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                        toCpy = gTrainerClasses[GetFrontierOpponentClass(gPartnerTrainerId)].name;
                    break;
                case B_POSITION_OPPONENT_LEFT:
                    toCpy = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                    break;
                case B_POSITION_OPPONENT_RIGHT:
                    if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS && !BATTLE_TWO_VS_ONE_OPPONENT)
                        toCpy = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentB);
                    else
                        toCpy = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                    break;
                default:
                    break;
                }
                break;
            case B_TXT_ATK_TRAINER_NAME_WITH_CLASS:
                toCpy = textStart;
                if (GetBattlerPosition(gBattlerAttacker) == B_POSITION_PLAYER_LEFT)
                {
                    textStart = StringCopy(textStart, BattleStringGetTrainerName(textStart, multiplayerId, gBattlerAttacker));
                }
                else
                {
                    classString = NULL;
                    switch (GetBattlerPosition(gBattlerAttacker))
                    {
                    case B_POSITION_PLAYER_RIGHT:
                        if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                            classString = gTrainerClasses[GetFrontierOpponentClass(gPartnerTrainerId)].name;
                        break;
                    case B_POSITION_OPPONENT_LEFT:
                        classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                        break;
                    case B_POSITION_OPPONENT_RIGHT:
                        if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS && !BATTLE_TWO_VS_ONE_OPPONENT)
                            classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentB);
                        else
                            classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                        break;
                    default:
                        break;
                    }
                    classLength = 0;
                    nameLength = 0;
                    while (classString[classLength] != EOS)
                    {
                        textStart[classLength] = classString[classLength];
                        classLength++;
                    }
                    textStart[classLength] = CHAR_SPACE;
                    textStart += 1 + classLength;
                    nameString = BattleStringGetTrainerName(textStart, multiplayerId, gBattlerAttacker);
                    if (nameString != textStart)
                    {
                        while (nameString[nameLength] != EOS)
                        {
                            textStart[nameLength] = nameString[nameLength];
                            nameLength++;
                        }
                        textStart[nameLength] = EOS;
                    }
                }
                break;
            case B_TXT_ATK_TEAM1:
                if (IsOnPlayerSide(gBattlerAttacker))
                    toCpy = sText_Your1;
                else
                    toCpy = sText_Opposing1;
                break;
            case B_TXT_ATK_TEAM2:
                if (IsOnPlayerSide(gBattlerAttacker))
                    toCpy = sText_Your2;
                else
                    toCpy = sText_Opposing2;
                break;
            case B_TXT_DEF_TEAM1:
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_Your1;
                else
                    toCpy = sText_Opposing1;
                break;
            case B_TXT_DEF_TEAM2:
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_Your2;
                else
                    toCpy = sText_Opposing2;
                break;
            case B_TXT_EFF_TEAM1:
                if (IsOnPlayerSide(gEffectBattler))
                    toCpy = sText_Your1;
                else
                    toCpy = sText_Opposing1;
                break;
            case B_TXT_EFF_TEAM2:
                if (IsOnPlayerSide(gEffectBattler))
                    toCpy = sText_Your2;
                else
                    toCpy = sText_Opposing2;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gBattlerAttacker)
                break;
            case B_TXT_DEF_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gBattlerTarget)
                break;
            case B_TXT_EFF_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gEffectBattler)
                break;
            case B_TXT_SCR_ACTIVE_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gBattleScripting.battler)
                break;
            }

            if (toCpy != NULL)
            {
                while (*toCpy != EOS)
                {
                    dst[dstID] = *toCpy;
                    dstID++;
                    toCpy++;
                }
            }

            if (*src == B_TXT_TRAINER1_LOSE_TEXT || *src == B_TXT_TRAINER2_LOSE_TEXT
                || *src == B_TXT_TRAINER1_WIN_TEXT || *src == B_TXT_TRAINER2_WIN_TEXT)
            {
                dst[dstID] = EXT_CTRL_CODE_BEGIN;
                dstID++;
                dst[dstID] = EXT_CTRL_CODE_PAUSE_UNTIL_PRESS;
                dstID++;
            }
        }
        else
        {
            dst[dstID] = *src;
            dstID++;
        }
        src++;
    }

    dst[dstID] = *src;
    dstID++;

    BreakStringAutomatic(dst, BATTLE_MSG_MAX_WIDTH, BATTLE_MSG_MAX_LINES, fontId, SHOW_SCROLL_PROMPT);

    return dstID;
}

static void IllusionNickHack(enum BattlerId battler, u32 partyId, u8 *dst)
{
    u32 id = PARTY_SIZE;
    struct Pokemon *party = GetBattlerParty(battler);
    struct Pokemon *mon = &party[partyId], *partnerMon;

    if (GetMonAbility(mon) == ABILITY_ILLUSION)
    {
        if (IsBattlerAlive(BATTLE_PARTNER(battler)))
            partnerMon = GetBattlerMon(BATTLE_PARTNER(battler));
        else
            partnerMon = mon;

        id = GetIllusionMonPartyId(party, mon, partnerMon, battler);
    }

    if (id != PARTY_SIZE)
        GetMonData(&party[id], MON_DATA_NICKNAME, dst);
    else
        GetMonData(mon, MON_DATA_NICKNAME, dst);
}

void ExpandBattleTextBuffPlaceholders(const u8 *src, u8 *dst)
{
    u32 srcID = 1;
    u32 value = 0;
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    u16 hword;

    *dst = EOS;
    while (src[srcID] != B_BUFF_EOS)
    {
        switch (src[srcID])
        {
        case B_BUFF_STRING: // battle string
            hword = T1_READ_16(&src[srcID + 1]);
            StringAppend(dst, gBattleStringsTable[hword]);
            srcID += 3;
            break;
        case B_BUFF_NUMBER: // int to string
            switch (src[srcID + 1])
            {
            case 1:
                value = src[srcID + 3];
                break;
            case 2:
                value = T1_READ_16(&src[srcID + 3]);
                break;
            case 4:
                value = T1_READ_32(&src[srcID + 3]);
                break;
            }
            ConvertIntToDecimalStringN(dst, value, STR_CONV_MODE_LEFT_ALIGN, src[srcID + 2]);
            srcID += src[srcID + 1] + 3;
            break;
        case B_BUFF_MOVE: // move name
            StringAppend(dst, GetMoveName(T1_READ_16(&src[srcID + 1])));
            srcID += 3;
            break;
        case B_BUFF_TYPE: // type name
            StringAppend(dst, gTypesInfo[src[srcID + 1]].name);
            srcID += 2;
            break;
        case B_BUFF_MON_NICK_WITH_PREFIX: // poke nick with prefix
        case B_BUFF_MON_NICK_WITH_PREFIX_LOWER: // poke nick with lowercase prefix
            if (!IsOnPlayerSide(src[srcID + 1]))
            {
                if (src[srcID] == B_BUFF_MON_NICK_WITH_PREFIX_LOWER)
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                        StringAppend(dst, sText_FoePkmnPrefixLower);
                    else
                        StringAppend(dst, sText_WildPkmnPrefixLower);
                }
                else
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                        StringAppend(dst, sText_FoePkmnPrefix);
                    else
                        StringAppend(dst, sText_WildPkmnPrefix);
                }
            }
            GetMonData(&GetBattlerParty(src[srcID + 1])[src[srcID + 2]], MON_DATA_NICKNAME, nickname);
            StringGet_Nickname(nickname);
            StringAppend(dst, nickname);
            srcID += 3;
            break;
        case B_BUFF_STAT: // stats
            StringAppend(dst, gStatNamesTable[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_SPECIES: // species name
            StringCopy(dst, GetSpeciesName(T1_READ_16(&src[srcID + 1])));
            srcID += 3;
            break;
        case B_BUFF_MON_NICK: // poke nick without prefix
            if (src[srcID + 2] == gBattlerPartyIndexes[src[srcID + 1]])
            {
                GetBattlerNick(src[srcID + 1], dst);
            }
            else if (gBattleScripting.illusionNickHack) // for STRINGID_ENEMYABOUTTOSWITCHPKMN
            {
                gBattleScripting.illusionNickHack = 0;
                IllusionNickHack(src[srcID + 1], src[srcID + 2], dst);
                StringGet_Nickname(dst);
            }
            else
            {
                GetMonData(&GetBattlerParty(src[srcID + 1])[src[srcID + 2]], MON_DATA_NICKNAME, dst);
                StringGet_Nickname(dst);
            }
            srcID += 3;
            break;
        case B_BUFF_NEGATIVE_FLAVOR: // flavor table
            StringAppend(dst, gPokeblockWasTooXStringTable[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_ABILITY: // ability names
            StringAppend(dst, gAbilitiesInfo[T1_READ_16(&src[srcID + 1])].name);
            srcID += 3;
            break;
        case B_BUFF_ITEM: // item name
            hword = T1_READ_16(&src[srcID + 1]);
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (hword == ITEM_ENIGMA_BERRY_E_READER)
                {
                    if (gLinkPlayers[gBattleScripting.multiplayerId].id == gPotentialItemEffectBattler)
                    {
                        StringCopy(dst, gEnigmaBerries[gPotentialItemEffectBattler].name);
                        StringAppend(dst, sText_BerrySuffix);
                    }
                    else
                    {
                        StringAppend(dst, sText_EnigmaBerry);
                    }
                }
                else
                {
                    CopyItemName(hword, dst);
                }
            }
            else
            {
                CopyItemName(hword, dst);
            }
            srcID += 3;
            break;
        }
    }
}

void BattlePutTextOnWindow(const u8 *text, u8 windowId)
{
    const struct BattleWindowText *textInfo = sBattleTextOnWindowsInfo[gBattleScripting.windowsType];
    bool32 copyToVram;
    struct TextPrinterTemplate printerTemplate;
    u8 speed;

    if (windowId & B_WIN_COPYTOVRAM)
    {
        windowId &= ~B_WIN_COPYTOVRAM;
        copyToVram = FALSE;
    }
    else
    {
        FillWindowPixelBuffer(windowId, textInfo[windowId].fillValue);
        copyToVram = TRUE;
    }

    printerTemplate.currentChar = text;
    printerTemplate.type = WINDOW_TEXT_PRINTER;
    printerTemplate.windowId = windowId;
    printerTemplate.fontId = textInfo[windowId].fontId;
    printerTemplate.x = textInfo[windowId].x;
    printerTemplate.y = textInfo[windowId].y;
    printerTemplate.currentX = printerTemplate.x;
    printerTemplate.currentY = printerTemplate.y;
    printerTemplate.letterSpacing = textInfo[windowId].letterSpacing;
    printerTemplate.lineSpacing = textInfo[windowId].lineSpacing;
    printerTemplate.color = textInfo[windowId].color;

    if (B_WIN_MOVE_NAME_1 <= windowId && windowId <= B_WIN_MOVE_NAME_4)
    {
        // We cannot check the actual width of the window because
        // B_WIN_MOVE_NAME_1 and B_WIN_MOVE_NAME_3 are 16 wide for
        // Z-move details.
        if (gBattleStruct->zmove.viewing && windowId == B_WIN_MOVE_NAME_1)
            printerTemplate.fontId = GetFontIdToFit(text, printerTemplate.fontId, printerTemplate.letterSpacing, 16 * TILE_WIDTH);
        else
            printerTemplate.fontId = GetFontIdToFit(text, printerTemplate.fontId, printerTemplate.letterSpacing, 8 * TILE_WIDTH);
    }

    if (printerTemplate.x == 0xFF)
    {
        u32 width = GetBattleWindowTemplatePixelWidth(gBattleScripting.windowsType, windowId);
        s32 alignX = GetStringCenterAlignXOffsetWithLetterSpacing(printerTemplate.fontId, printerTemplate.currentChar, width, printerTemplate.letterSpacing);
        printerTemplate.x = printerTemplate.currentX = alignX;
    }

    if (windowId == ARENA_WIN_JUDGMENT_TEXT || windowId == B_WIN_OAK_OLD_MAN)
        gTextFlags.useAlternateDownArrow = FALSE;
    else
        gTextFlags.useAlternateDownArrow = TRUE;

    if ((gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED)) || gTestRunnerEnabled || ((gBattleTypeFlags & BATTLE_TYPE_POKEDUDE) && windowId != B_WIN_OAK_OLD_MAN))
        gTextFlags.autoScroll = TRUE;
    else
        gTextFlags.autoScroll = FALSE;

    if (windowId == B_WIN_MSG || windowId == ARENA_WIN_JUDGMENT_TEXT || windowId == B_WIN_OAK_OLD_MAN)
    {
        if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            speed = 1;
        else if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            speed = sRecordedBattleTextSpeeds[GetTextSpeedInRecordedBattle()];
        else
            speed = GetPlayerTextSpeedDelay();

        gTextFlags.canABSpeedUpPrint = 1;
    }
    else
    {
        speed = textInfo[windowId].speed;
        gTextFlags.canABSpeedUpPrint = 0;
    }

    AddTextPrinter(&printerTemplate, speed, NULL);

    if (copyToVram)
    {
        PutWindowTilemap(windowId);
        CopyWindowToVram(windowId, COPYWIN_FULL);
    }
}

void SetPpNumbersPaletteInMoveSelection(enum BattlerId battler)
{
    struct ChooseMoveStruct *chooseMoveStruct = (struct ChooseMoveStruct *)(&gBattleResources->bufferA[battler][4]);
    const u16 *palPtr = gPPTextPalette;
    u8 var;

    if (!gBattleStruct->zmove.viewing)
        var = GetCurrentPpToMaxPpState(chooseMoveStruct->currentPp[gMoveSelectionCursor[battler]],
                         chooseMoveStruct->maxPp[gMoveSelectionCursor[battler]]);
    else
        var = 3;

    gPlttBufferUnfaded[BG_PLTT_ID(5) + 12] = palPtr[(var * 2) + 0];
    gPlttBufferUnfaded[BG_PLTT_ID(5) + 11] = palPtr[(var * 2) + 1];

    CpuCopy16(&gPlttBufferUnfaded[BG_PLTT_ID(5) + 12], &gPlttBufferFaded[BG_PLTT_ID(5) + 12], PLTT_SIZEOF(1));
    CpuCopy16(&gPlttBufferUnfaded[BG_PLTT_ID(5) + 11], &gPlttBufferFaded[BG_PLTT_ID(5) + 11], PLTT_SIZEOF(1));
}

u8 GetCurrentPpToMaxPpState(u8 currentPp, u8 maxPp)
{
    if (maxPp == currentPp)
    {
        return 3;
    }
    else if (maxPp <= 2)
    {
        if (currentPp > 1)
            return 3;
        else
            return 2 - currentPp;
    }
    else if (maxPp <= 7)
    {
        if (currentPp > 2)
            return 3;
        else
            return 2 - currentPp;
    }
    else
    {
        if (currentPp == 0)
            return 2;
        if (currentPp <= maxPp / 4)
            return 1;
        if (currentPp > maxPp / 2)
            return 3;
    }

    return 0;
}
