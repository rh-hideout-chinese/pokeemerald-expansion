const u8 gEasyChatWord_Meet[] = _("吸引");
const u8 gEasyChatWord_Play[] = _("玩");
const u8 gEasyChatWord_Hurried[] = _("过头");
const u8 gEasyChatWord_Goes[] = _("一生");
const u8 gEasyChatWord_Giddy[] = _("头晕");
const u8 gEasyChatWord_Happy[] = _("开心");
const u8 gEasyChatWord_Happiness[] = _("高兴");
const u8 gEasyChatWord_Excite[] = _("兴奋");
const u8 gEasyChatWord_Important[] = _("重要");
const u8 gEasyChatWord_Funny[] = _("有趣");
const u8 gEasyChatWord_Got[] = _("轻松");
const u8 gEasyChatWord_GoHome[] = _("回家");
const u8 gEasyChatWord_Disappointed[] = _("失望");
const u8 gEasyChatWord_Disappoints[] = _("意识");
const u8 gEasyChatWord_Sad[] = _("难过");
const u8 gEasyChatWord_Try[] = _("尝试");
const u8 gEasyChatWord_Tries[] = _("消息");
const u8 gEasyChatWord_Hears[] = _("听到");
const u8 gEasyChatWord_Think[] = _("试试");
const u8 gEasyChatWord_Hear[] = _("听见");
const u8 gEasyChatWord_Wants[] = _("想要");
const u8 gEasyChatWord_Misheard[] = _("听错了");
const u8 gEasyChatWord_Dislike[] = _("讨厌");
const u8 gEasyChatWord_Angry[] = _("生气");
const u8 gEasyChatWord_Anger[] = _("欺骗");
const u8 gEasyChatWord_Scary[] = _("可怕");
const u8 gEasyChatWord_Lonesome[] = _("孤单");
const u8 gEasyChatWord_Disappoint[] = _("希望");
const u8 gEasyChatWord_Joy[] = _("喜悦");
const u8 gEasyChatWord_Gets[] = _("获得");
const u8 gEasyChatWord_Never[] = _("从不");
const u8 gEasyChatWord_Darn[] = _("可恶");
const u8 gEasyChatWord_Downcast[] = _("沮丧");
const u8 gEasyChatWord_Incredible[] = _("不可思议");
const u8 gEasyChatWord_Likes[] = _("喜欢");
const u8 gEasyChatWord_Dislikes[] = _("不喜欢");
const u8 gEasyChatWord_Boring[] = _("无聊");
const u8 gEasyChatWord_Care[] = _("关心");
const u8 gEasyChatWord_Cares[] = _("一切");
const u8 gEasyChatWord_AllRight[] = _("所有");
const u8 gEasyChatWord_Adore[] = _("崇拜");
const u8 gEasyChatWord_Disaster[] = _("灾难");
const u8 gEasyChatWord_Enjoy[] = _("享受");
const u8 gEasyChatWord_Enjoys[] = _("成为");
const u8 gEasyChatWord_Eat[] = _("吃");
const u8 gEasyChatWord_Lacking[] = _("缺乏");
const u8 gEasyChatWord_Bad[] = _("坏");
const u8 gEasyChatWord_Hard[] = _("困难");
const u8 gEasyChatWord_Terrible[] = _("该");
const u8 gEasyChatWord_Should[] = _("应该");
const u8 gEasyChatWord_Nice[] = _("不错");
const u8 gEasyChatWord_Drink[] = _("不够");
const u8 gEasyChatWord_Surprise[] = _("惊喜");
const u8 gEasyChatWord_Fear[] = _("后悔");
const u8 gEasyChatWord_Want[] = _("等不及");
const u8 gEasyChatWord_Wait[] = _("等待");
const u8 gEasyChatWord_Satisfied[] = _("满意");
const u8 gEasyChatWord_See[] = _("看看");
const u8 gEasyChatWord_Rare[] = _("稀有");
const u8 gEasyChatWord_Negative[] = _("不利");
const u8 gEasyChatWord_Done[] = _("完成");
const u8 gEasyChatWord_Danger[] = _("危险");
const u8 gEasyChatWord_Defeated[] = _("被打败");
const u8 gEasyChatWord_Beat[] = _("击败");
const u8 gEasyChatWord_Great[] = _("很棒");
const u8 gEasyChatWord_Romantic[] = _("浪漫");
const u8 gEasyChatWord_Question[] = _("问题");
const u8 gEasyChatWord_Understand[] = _("不幸");
const u8 gEasyChatWord_Understands[] = _("离开");

const struct EasyChatWordInfo gEasyChatGroup_Feelings[] = {
    [EC_INDEX(EC_WORD_MEET)] =
    {
        .text = COMPOUND_STRING("吸引"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ADORE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_PLAY)] =
    {
        .text = COMPOUND_STRING("玩"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ALL_RIGHT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HURRIED)] =
    {
        .text = COMPOUND_STRING("过头"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ANGER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_GOES)] =
    {
        .text = COMPOUND_STRING("一生"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ANGRY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_GIDDY)] =
    {
        .text = COMPOUND_STRING("头晕"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_BAD),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HAPPY)] =
    {
        .text = COMPOUND_STRING("开心"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_BEAT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HAPPINESS)] =
    {
        .text = COMPOUND_STRING("高兴"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_BORING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_EXCITE)] =
    {
        .text = COMPOUND_STRING("兴奋"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_CARE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_IMPORTANT)] =
    {
        .text = COMPOUND_STRING("重要"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_CARES),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FUNNY)] =
    {
        .text = COMPOUND_STRING("有趣"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DANGER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_GOT)] =
    {
        .text = COMPOUND_STRING("轻松"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DARN),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_GO_HOME)] =
    {
        .text = COMPOUND_STRING("回家"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DEFEATED),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DISAPPOINTED)] =
    {
        .text = COMPOUND_STRING("失望"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DISAPPOINT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DISAPPOINTS)] =
    {
        .text = COMPOUND_STRING("意识"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DISAPPOINTED),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SAD)] =
    {
        .text = COMPOUND_STRING("难过"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DISAPPOINTS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TRY)] =
    {
        .text = COMPOUND_STRING("尝试"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DISASTER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TRIES)] =
    {
        .text = COMPOUND_STRING("消息"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DISLIKE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HEARS)] =
    {
        .text = COMPOUND_STRING("听到"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DISLIKES),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THINK)] =
    {
        .text = COMPOUND_STRING("试试"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DONE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HEAR)] =
    {
        .text = COMPOUND_STRING("听见"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DOWNCAST),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WANTS)] =
    {
        .text = COMPOUND_STRING("想要"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DRINK),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MISHEARD)] =
    {
        .text = COMPOUND_STRING("听错了"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_EAT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DISLIKE)] =
    {
        .text = COMPOUND_STRING("讨厌"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ENJOY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ANGRY)] =
    {
        .text = COMPOUND_STRING("生气"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ENJOYS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ANGER)] =
    {
        .text = COMPOUND_STRING("欺骗"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_EXCITE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SCARY)] =
    {
        .text = COMPOUND_STRING("可怕"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_FEAR),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LONESOME)] =
    {
        .text = COMPOUND_STRING("孤单"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_FUNNY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DISAPPOINT)] =
    {
        .text = COMPOUND_STRING("希望"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_GETS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_JOY)] =
    {
        .text = COMPOUND_STRING("喜悦"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_GIDDY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_GETS)] =
    {
        .text = COMPOUND_STRING("获得"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_GO_HOME),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NEVER)] =
    {
        .text = COMPOUND_STRING("从不"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_GOES),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DARN)] =
    {
        .text = COMPOUND_STRING("可恶"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_GOT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DOWNCAST)] =
    {
        .text = COMPOUND_STRING("沮丧"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_GREAT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_INCREDIBLE)] =
    {
        .text = COMPOUND_STRING("不可思议"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HAPPINESS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LIKES)] =
    {
        .text = COMPOUND_STRING("喜欢"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HAPPY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DISLIKES)] =
    {
        .text = COMPOUND_STRING("不喜欢"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HARD),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BORING)] =
    {
        .text = COMPOUND_STRING("无聊"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HEAR),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CARE)] =
    {
        .text = COMPOUND_STRING("关心"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HEARS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CARES)] =
    {
        .text = COMPOUND_STRING("一切"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HURRIED),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ALL_RIGHT)] =
    {
        .text = COMPOUND_STRING("所有"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_IMPORTANT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ADORE)] =
    {
        .text = COMPOUND_STRING("崇拜"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_INCREDIBLE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DISASTER)] =
    {
        .text = COMPOUND_STRING("灾难"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_JOY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ENJOY)] =
    {
        .text = COMPOUND_STRING("享受"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_LACKING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ENJOYS)] =
    {
        .text = COMPOUND_STRING("成为"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_LIKES),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_EAT)] =
    {
        .text = COMPOUND_STRING("吃"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_LONESOME),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LACKING)] =
    {
        .text = COMPOUND_STRING("缺乏"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_MEET),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BAD)] =
    {
        .text = COMPOUND_STRING("坏"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_MISHEARD),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HARD)] =
    {
        .text = COMPOUND_STRING("困难"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_NEGATIVE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TERRIBLE)] =
    {
        .text = COMPOUND_STRING("该"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_NEVER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SHOULD)] =
    {
        .text = COMPOUND_STRING("应该"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_NICE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NICE)] =
    {
        .text = COMPOUND_STRING("不错"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_PLAY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DRINK)] =
    {
        .text = COMPOUND_STRING("不够"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_QUESTION),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SURPRISE)] =
    {
        .text = COMPOUND_STRING("惊喜"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_RARE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FEAR)] =
    {
        .text = COMPOUND_STRING("后悔"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ROMANTIC),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WANT)] =
    {
        .text = COMPOUND_STRING("等不及"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_SAD),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WAIT)] =
    {
        .text = COMPOUND_STRING("等待"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_SATISFIED),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SATISFIED)] =
    {
        .text = COMPOUND_STRING("满意"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_SCARY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SEE)] =
    {
        .text = COMPOUND_STRING("看看"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_SEE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_RARE)] =
    {
        .text = COMPOUND_STRING("稀有"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_SHOULD),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NEGATIVE)] =
    {
        .text = COMPOUND_STRING("不利"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_SURPRISE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DONE)] =
    {
        .text = COMPOUND_STRING("完成"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_TERRIBLE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DANGER)] =
    {
        .text = COMPOUND_STRING("危险"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_THINK),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DEFEATED)] =
    {
        .text = COMPOUND_STRING("被打败"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_TRIES),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BEAT)] =
    {
        .text = COMPOUND_STRING("击败"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_TRY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_GREAT)] =
    {
        .text = COMPOUND_STRING("很棒"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_UNDERSTAND),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ROMANTIC)] =
    {
        .text = COMPOUND_STRING("浪漫"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_UNDERSTANDS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_QUESTION)] =
    {
        .text = COMPOUND_STRING("问题"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_WAIT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_UNDERSTAND)] =
    {
        .text = COMPOUND_STRING("不幸"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_WANT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_UNDERSTANDS)] =
    {
        .text = COMPOUND_STRING("离开"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_WANTS),
        .enabled = TRUE,
    },
};
