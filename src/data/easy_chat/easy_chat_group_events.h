const u8 gEasyChatWord_Appeal[] = _("吸引力");
const u8 gEasyChatWord_Events[] = _("活动");
const u8 gEasyChatWord_StayAtHome[] = _("家里蹲");
const u8 gEasyChatWord_Berry[] = _("树果");
const u8 gEasyChatWord_Contest[] = _("华丽大赛");
const u8 gEasyChatWord_Mc[] = _("主持人");
const u8 gEasyChatWord_Judge[] = _("评委");
const u8 gEasyChatWord_Super[] = _("外表");
const u8 gEasyChatWord_Stage[] = _("舞台");
const u8 gEasyChatWord_HallOfFame[] = _("名人堂");
const u8 gEasyChatWord_Evolution[] = _("大会");
const u8 gEasyChatWord_Hyper[] = _("超级");
const u8 gEasyChatWord_BattleTower[] = _("对战塔");
const u8 gEasyChatWord_Leaders[] = _("首领");
const u8 gEasyChatWord_BattleRoom[] = _("对战室");
const u8 gEasyChatWord_Hidden[] = _("隐藏");
const u8 gEasyChatWord_SecretBase[] = _("秘密基地");
const u8 gEasyChatWord_Blend[] = _("混合");
const u8 gEasyChatWord_POKEBLOCK[] = _("宝可方块");
const u8 gEasyChatWord_Master[] = _("大师");
const u8 gEasyChatWord_Rank[] = _("场");
const u8 gEasyChatWord_Ribbon[] = _("奖牌");
const u8 gEasyChatWord_Crush[] = _("粉碎");
const u8 gEasyChatWord_Direct[] = _("直接");
const u8 gEasyChatWord_Tower[] = _("塔");
const u8 gEasyChatWord_Union[] = _("联合");
const u8 gEasyChatWord_Room[] = _("房间");
const u8 gEasyChatWord_Wireless[] = _("无线");
const u8 gEasyChatWord_Frontier[] = _("开拓区");

const struct EasyChatWordInfo gEasyChatGroup_Events[] = {
    [EC_INDEX(EC_WORD_APPEAL)] =
    {
        .text = COMPOUND_STRING("吸引力"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_APPEAL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_EVENTS)] =
    {
        .text = COMPOUND_STRING("活动"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_BATTLE_ROOM),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_STAY_AT_HOME)] =
    {
        .text = COMPOUND_STRING("家里蹲"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_BATTLE_TOWER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BERRY)] =
    {
        .text = COMPOUND_STRING("树果"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_BERRY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CONTEST)] =
    {
        .text = COMPOUND_STRING("华丽大赛"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_BLEND),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MC)] =
    {
        .text = COMPOUND_STRING("主持人"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_CONTEST),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_JUDGE)] =
    {
        .text = COMPOUND_STRING("评委"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_CRUSH),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SUPER)] =
    {
        .text = COMPOUND_STRING("外表"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DIRECT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_STAGE)] =
    {
        .text = COMPOUND_STRING("舞台"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_EVENTS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HALL_OF_FAME)] =
    {
        .text = COMPOUND_STRING("名人堂"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_EVOLUTION),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_EVOLUTION)] =
    {
        .text = COMPOUND_STRING("大会"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_FRONTIER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HYPER)] =
    {
        .text = COMPOUND_STRING("超级"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HALL_OF_FAME),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BATTLE_TOWER)] =
    {
        .text = COMPOUND_STRING("对战塔"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HIDDEN),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LEADERS)] =
    {
        .text = COMPOUND_STRING("首领"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HYPER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BATTLE_ROOM)] =
    {
        .text = COMPOUND_STRING("对战室"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_JUDGE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HIDDEN)] =
    {
        .text = COMPOUND_STRING("隐藏"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_LEADERS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SECRET_BASE)] =
    {
        .text = COMPOUND_STRING("秘密基地"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_MASTER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BLEND)] =
    {
        .text = COMPOUND_STRING("混合"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_MC),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_POKEBLOCK)] =
    {
        .text = COMPOUND_STRING("宝可方块"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_POKEBLOCK),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MASTER)] =
    {
        .text = COMPOUND_STRING("大师"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_RANK),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_RANK)] =
    {
        .text = COMPOUND_STRING("场"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_RIBBON),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_RIBBON)] =
    {
        .text = COMPOUND_STRING("奖牌"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ROOM),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CRUSH)] =
    {
        .text = COMPOUND_STRING("粉碎"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_SECRET_BASE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DIRECT)] =
    {
        .text = COMPOUND_STRING("直接"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_STAGE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TOWER)] =
    {
        .text = COMPOUND_STRING("塔"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_STAY_AT_HOME),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_UNION)] =
    {
        .text = COMPOUND_STRING("联合"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_SUPER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ROOM)] =
    {
        .text = COMPOUND_STRING("房间"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_TOWER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WIRELESS)] =
    {
        .text = COMPOUND_STRING("无线"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_UNION),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FRONTIER)] =
    {
        .text = COMPOUND_STRING("开拓区"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_WIRELESS),
        .enabled = TRUE,
    },
};
