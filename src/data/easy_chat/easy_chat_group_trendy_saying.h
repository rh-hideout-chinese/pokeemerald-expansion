const u8 gEasyChatWord_KthxBye[] = _("谢谢，再见。");
const u8 gEasyChatWord_YesSirExcl[] = _("是，先生！");
const u8 gEasyChatWord_AvantGarde[] = _("前卫");
const u8 gEasyChatWord_Couple[] = _("情侣");
const u8 gEasyChatWord_MuchObliged[] = _("非常感谢");
const u8 gEasyChatWord_YeehawExcl[] = _("耶！");
const u8 gEasyChatWord_Mega[] = _("超");
const u8 gEasyChatWord_1HitKOExcl[] = _("一击KO！");
const u8 gEasyChatWord_Destiny[] = _("命运");
const u8 gEasyChatWord_Cancel[] = _("取消");
const u8 gEasyChatWord_New[] = _("新");
const u8 gEasyChatWord_Flatten[] = _("扁平化");
const u8 gEasyChatWord_Kidding[] = _("开玩笑");
const u8 gEasyChatWord_Loser[] = _("失败者");
const u8 gEasyChatWord_Losing[] = _("失败");
const u8 gEasyChatWord_Happening[] = _("发生");
const u8 gEasyChatWord_HipAnd[] = _("嘻哈和");
const u8 gEasyChatWord_Shake[] = _("摇摆");
const u8 gEasyChatWord_Shady[] = _("阴暗");
const u8 gEasyChatWord_Upbeat[] = _("乐观");
const u8 gEasyChatWord_Modern[] = _("现代");
const u8 gEasyChatWord_SmellYa[] = _("再见");
const u8 gEasyChatWord_Bang[] = _("砰");
const u8 gEasyChatWord_Knockout[] = _("击倒");
const u8 gEasyChatWord_Hassle[] = _("麻烦");
const u8 gEasyChatWord_Winner[] = _("赢家");
const u8 gEasyChatWord_Fever[] = _("狂热");
const u8 gEasyChatWord_Wannabe[] = _("想要成为");
const u8 gEasyChatWord_Baby[] = _("宝贝");
const u8 gEasyChatWord_Heart[] = _("心");
const u8 gEasyChatWord_Old[] = _("老");
const u8 gEasyChatWord_Young[] = _("年轻");
const u8 gEasyChatWord_Ugly[] = _("丑陋");

const struct EasyChatWordInfo gEasyChatGroup_TrendySaying[] = {
    [EC_INDEX(EC_WORD_KTHX_BYE)] =
    {
        .text = gEasyChatWord_KthxBye,
        .alphabeticalOrder = EC_INDEX(EC_WORD_1_HIT_KO_EXCL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_YES_SIR_EXCL)] =
    {
        .text = gEasyChatWord_YesSirExcl,
        .alphabeticalOrder = EC_INDEX(EC_WORD_AVANT_GARDE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_AVANT_GARDE)] =
    {
        .text = gEasyChatWord_AvantGarde,
        .alphabeticalOrder = EC_INDEX(EC_WORD_BABY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_COUPLE)] =
    {
        .text = gEasyChatWord_Couple,
        .alphabeticalOrder = EC_INDEX(EC_WORD_BANG),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MUCH_OBLIGED)] =
    {
        .text = gEasyChatWord_MuchObliged,
        .alphabeticalOrder = EC_INDEX(EC_WORD_CANCEL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_YEEHAW_EXCL)] =
    {
        .text = gEasyChatWord_YeehawExcl,
        .alphabeticalOrder = EC_INDEX(EC_WORD_COUPLE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MEGA)] =
    {
        .text = gEasyChatWord_Mega,
        .alphabeticalOrder = EC_INDEX(EC_WORD_DESTINY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_1_HIT_KO_EXCL)] =
    {
        .text = gEasyChatWord_1HitKOExcl,
        .alphabeticalOrder = EC_INDEX(EC_WORD_FEVER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DESTINY)] =
    {
        .text = gEasyChatWord_Destiny,
        .alphabeticalOrder = EC_INDEX(EC_WORD_FLATTEN),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CANCEL)] =
    {
        .text = gEasyChatWord_Cancel,
        .alphabeticalOrder = EC_INDEX(EC_WORD_HAPPENING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NEW)] =
    {
        .text = gEasyChatWord_New,
        .alphabeticalOrder = EC_INDEX(EC_WORD_HASSLE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FLATTEN)] =
    {
        .text = gEasyChatWord_Flatten,
        .alphabeticalOrder = EC_INDEX(EC_WORD_HEART),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_KIDDING)] =
    {
        .text = gEasyChatWord_Kidding,
        .alphabeticalOrder = EC_INDEX(EC_WORD_HIP_AND),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LOSER)] =
    {
        .text = gEasyChatWord_Loser,
        .alphabeticalOrder = EC_INDEX(EC_WORD_KIDDING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LOSING)] =
    {
        .text = gEasyChatWord_Losing,
        .alphabeticalOrder = EC_INDEX(EC_WORD_KNOCKOUT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HAPPENING)] =
    {
        .text = gEasyChatWord_Happening,
        .alphabeticalOrder = EC_INDEX(EC_WORD_KTHX_BYE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HIP_AND)] =
    {
        .text = gEasyChatWord_HipAnd,
        .alphabeticalOrder = EC_INDEX(EC_WORD_LOSER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SHAKE)] =
    {
        .text = gEasyChatWord_Shake,
        .alphabeticalOrder = EC_INDEX(EC_WORD_LOSING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SHADY)] =
    {
        .text = gEasyChatWord_Shady,
        .alphabeticalOrder = EC_INDEX(EC_WORD_MEGA),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_UPBEAT)] =
    {
        .text = gEasyChatWord_Upbeat,
        .alphabeticalOrder = EC_INDEX(EC_WORD_MODERN),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MODERN)] =
    {
        .text = gEasyChatWord_Modern,
        .alphabeticalOrder = EC_INDEX(EC_WORD_MUCH_OBLIGED),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SMELL_YA)] =
    {
        .text = gEasyChatWord_SmellYa,
        .alphabeticalOrder = EC_INDEX(EC_WORD_NEW),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BANG)] =
    {
        .text = gEasyChatWord_Bang,
        .alphabeticalOrder = EC_INDEX(EC_WORD_OLD),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_KNOCKOUT)] =
    {
        .text = gEasyChatWord_Knockout,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SHADY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HASSLE)] =
    {
        .text = gEasyChatWord_Hassle,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SHAKE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WINNER)] =
    {
        .text = gEasyChatWord_Winner,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SMELL_YA),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FEVER)] =
    {
        .text = gEasyChatWord_Fever,
        .alphabeticalOrder = EC_INDEX(EC_WORD_UGLY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WANNABE)] =
    {
        .text = gEasyChatWord_Wannabe,
        .alphabeticalOrder = EC_INDEX(EC_WORD_UPBEAT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BABY)] =
    {
        .text = gEasyChatWord_Baby,
        .alphabeticalOrder = EC_INDEX(EC_WORD_WANNABE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HEART)] =
    {
        .text = gEasyChatWord_Heart,
        .alphabeticalOrder = EC_INDEX(EC_WORD_WINNER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_OLD)] =
    {
        .text = gEasyChatWord_Old,
        .alphabeticalOrder = EC_INDEX(EC_WORD_YEEHAW_EXCL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_YOUNG)] =
    {
        .text = gEasyChatWord_Young,
        .alphabeticalOrder = EC_INDEX(EC_WORD_YES_SIR_EXCL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_UGLY)] =
    {
        .text = gEasyChatWord_Ugly,
        .alphabeticalOrder = EC_INDEX(EC_WORD_YOUNG),
        .enabled = TRUE,
    },
};
