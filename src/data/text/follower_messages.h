extern const u8 EventScript_FollowerIsShivering[];
extern const u8 EventScript_FollowerNostalgia[];
extern const u8 EventScript_FollowerHopping[];
extern const u8 EventScript_FollowerJumpOnPlayer[];
extern const u8 EventScript_FollowerCuddling[];
extern const u8 EventScript_FollowerShiverCuddling[];
extern const u8 EventScript_FollowerGetCloser[];
extern const u8 EventScript_FollowerPokingPlayer[];
extern const u8 EventScript_FollowerLookAround[];
extern const u8 EventScript_FollowerLookAway[];
extern const u8 EventScript_FollowerLookAwayBark[];
extern const u8 EventScript_FollowerLookAwayPoke[];
extern const u8 EventScript_FollowerPokeGround[];
extern const u8 EventScript_FollowerStartled[];
extern const u8 EventScript_FollowerFastHopping[];
extern const u8 EventScript_FollowerDizzy[];
extern const u8 EventScript_FollowerLookAroundScared[];
extern const u8 EventScript_FollowerDance[];
extern const u8 EventScript_FollowerLookUp[];

// 'Generic', unconditional happy messages
static const u8 sHappyMsg00[] = _("{STR_VAR_1}戳了戳\n你的肚子！");
static const u8 sHappyMsg01[] = _("{STR_VAR_1}看起来既\n开心又害羞！");
static const u8 sHappyMsg02[] = _("{STR_VAR_1}高兴地\n跟了上来！");
static const u8 sHappyMsg03[] = _("{STR_VAR_1}非常平静。");
static const u8 sHappyMsg04[] = _("{STR_VAR_1}好像很高兴\n能和你一起走路！");
static const u8 sHappyMsg05[] = _("{STR_VAR_1}正散发着\n健康的光芒。");
static const u8 sHappyMsg06[] = _("{STR_VAR_1}看起来\n非常开心。");
static const u8 sHappyMsg07[] = _("{STR_VAR_1}使起了\n劲儿来！");
static const u8 sHappyMsg08[] = _("{STR_VAR_1}正在闻着\n周围的气味。");
static const u8 sHappyMsg09[] = _("{STR_VAR_1}在\n开心地跳着！");
static const u8 sHappyMsg10[] = _("{STR_VAR_1}仍然\n精神十足！");
static const u8 sHappyMsg11[] = _("它似乎闻到了\n烟的味道。");
static const u8 sHappyMsg12[] = _("它戳了戳你的肚子！");
static const u8 sHappyMsg13[] = _("它正在伸展身体\n放松身心。");
static const u8 sHappyMsg14[] = _("{STR_VAR_1}好像想到\n前面去！");
static const u8 sHappyMsg15[] = _("{STR_VAR_1}努力地\n在你后面跟着……");
static const u8 sHappyMsg16[] = _("{STR_VAR_1}开心地靠了过来！");
static const u8 sHappyMsg17[] = _("{STR_VAR_1}活力十足！");
static const u8 sHappyMsg18[] = _("{STR_VAR_1}看起来\n很高兴！");
static const u8 sHappyMsg19[] = _("{STR_VAR_1}开心地\n不能平静！");
static const u8 sHappyMsg20[] = _("{STR_VAR_1}缓缓地\n点了点头。");
static const u8 sHappyMsg21[] = _("{STR_VAR_1}干劲十足！");
static const u8 sHappyMsg22[] = _("{STR_VAR_1}用心地听着\n四周的声音！");
static const u8 sHappyMsg23[] = _("{STR_VAR_1}看起来好像\n非常感兴趣！");
static const u8 sHappyMsg24[] = _("{STR_VAR_1}勉强地跟了\n上来。");
static const u8 sHappyMsg25[] = _("{STR_VAR_1}看着\n你笑了笑。");
static const u8 sHappyMsg26[] = _("{STR_VAR_1}开心地\n看着你笑。");
static const u8 sHappyMsg27[] = _("它正在闻着花香。");
static const u8 sHappyMsg28[] = _("{STR_VAR_1}一脸开心地\n看着你！");
static const u8 sHappyMsg29[] = _("{STR_VAR_1}转了过来\n并冲着你笑了笑。");
static const u8 sHappyMsg30[] = _("{STR_VAR_1}开心地\n向你靠了过来！");
// Conditional messages begin here, index 31
static const u8 sHappyMsg31[] = _("它好像因为好天气\n非常开心。");
static const u8 sHappyMsg32[] = _("{STR_VAR_1}的心情\n非常平静与自信。");

const struct FollowerMsgInfo gFollowerHappyMessages[] = {
    {sHappyMsg00, EventScript_FollowerPokingPlayer},
    {sHappyMsg01}, {sHappyMsg02}, {sHappyMsg03}, {sHappyMsg04}, {sHappyMsg05}, {sHappyMsg06}, {sHappyMsg07},
    {sHappyMsg08, EventScript_FollowerLookAround},
    {sHappyMsg09, EventScript_FollowerHopping},
    {sHappyMsg10}, {sHappyMsg11},
    {sHappyMsg12, EventScript_FollowerPokingPlayer},
    {sHappyMsg13, EventScript_FollowerLookAround},
    {sHappyMsg14}, {sHappyMsg15},
    {sHappyMsg16, EventScript_FollowerCuddling},
    {sHappyMsg17}, {sHappyMsg18},
    {sHappyMsg19, EventScript_FollowerFastHopping},
    {sHappyMsg20}, {sHappyMsg21}, {sHappyMsg22}, {sHappyMsg23}, {sHappyMsg24}, {sHappyMsg25}, {sHappyMsg26}, {sHappyMsg27}, {sHappyMsg28}, {sHappyMsg29},
    {sHappyMsg30, EventScript_FollowerCuddling},
    {sHappyMsg31}, {sHappyMsg32},
};

// Unconditional neutral messages
static const u8 sNeutralMsg00[] = _("{STR_VAR_1}一个劲地\n戳着地面。");
static const u8 sNeutralMsg01[] = _("{STR_VAR_1}正保持着\n警惕！");
static const u8 sNeutralMsg02[] = _("{STR_VAR_1}\n正在看着远方。");
static const u8 sNeutralMsg03[] = _("{STR_VAR_1}不停地\n环视着周围。");
static const u8 sNeutralMsg04[] = _("它啊～地\n打了个哈欠。");
static const u8 sNeutralMsg05[] = _("它正在警惕四周！");
static const u8 sNeutralMsg06[] = _("{STR_VAR_1}看着\n你笑了笑。");
static const u8 sNeutralMsg07[] = _("{STR_VAR_1}紧张地\n在四处张望。");
static const u8 sNeutralMsg08[] = _("{STR_VAR_1}打起了精神！");
static const u8 sNeutralMsg09[] = _("{STR_VAR_1}跳了一支\n精彩的舞!");
static const u8 sNeutralMsg10[] = _("{STR_VAR_1}干劲十足！");
static const u8 sNeutralMsg11[] = _("{STR_VAR_1}一直在眺望\n远方。");
static const u8 sNeutralMsg12[] = _("{STR_VAR_1}正在警惕四周！");
static const u8 sNeutralMsg13[] = _("{STR_VAR_1}朝着远处\n吼了出来！");

const struct FollowerMsgInfo gFollowerNeutralMessages[] = {
    {sNeutralMsg00, EventScript_FollowerPokeGround},
    {sNeutralMsg01},
    {sNeutralMsg02, EventScript_FollowerLookAway},
    {sNeutralMsg03, EventScript_FollowerLookAround},
    {sNeutralMsg04},
    {sNeutralMsg05, EventScript_FollowerLookAround},
    {sNeutralMsg06}, {sNeutralMsg07}, {sNeutralMsg08},
    {sNeutralMsg09, EventScript_FollowerDance},
    {sNeutralMsg10},
    {sNeutralMsg11, EventScript_FollowerLookAway},
    {sNeutralMsg12},
    {sNeutralMsg13, EventScript_FollowerLookAwayBark},
};

// Unconditional sad messages
static const u8 sSadMsg00[] = _("{STR_VAR_1}晕乎乎的。");
static const u8 sSadMsg01[] = _("{STR_VAR_1}踩了踩\n你的脚。");
static const u8 sSadMsg02[] = _("{STR_VAR_1}好像有点累了。");
// Conditional messages begin, index 3
static const u8 sSadMsg03[] = _("{STR_VAR_1}不太开心。");
static const u8 sSadMsg04[] = _("{STR_VAR_1}看起来\n快要倒下了！");
static const u8 sSadMsg05[] = _("{STR_VAR_1}差点就\n摔倒了！");
static const u8 sSadMsg06[] = _("{STR_VAR_1}努力地\n在你后面跟着……");
static const u8 sSadMsg07[] = _("{STR_VAR_1}紧张了。");

const struct FollowerMsgInfo gFollowerSadMessages[] = {
    {sSadMsg00, EventScript_FollowerDizzy},
    {sSadMsg01}, {sSadMsg02},
    {sSadMsg03}, {sSadMsg04}, {sSadMsg05}, {sSadMsg06}, {sSadMsg07},
};

// Unconditional upset messages
static const u8 sUpsetMsg00[] = _("{STR_VAR_1}好像\n有点不开心了。");
static const u8 sUpsetMsg01[] = _("{STR_VAR_1}看起来\n好像有点不开心……");
static const u8 sUpsetMsg02[] = _("……\n它看起来有点冷。");
// Conditional messages, index 3
static const u8 sUpsetMsg03[] = _("{STR_VAR_1}在草丛里躲着雨。");

const struct FollowerMsgInfo gFollowerUpsetMessages[] = {
    {sUpsetMsg00}, {sUpsetMsg01},
    {sUpsetMsg02, EventScript_FollowerIsShivering},
    {sUpsetMsg03},
};

// Unconditional angry messages
static const u8 sAngryMsg00[] = _("{STR_VAR_1}重重地\n吼了起来！");
static const u8 sAngryMsg01[] = _("{STR_VAR_1}摆出了\n生气的表情。");
static const u8 sAngryMsg02[] = _("{STR_VAR_1}看起来\n很生气！");
static const u8 sAngryMsg03[] = _("它转了过来\n摆出挑衅的表情。");
static const u8 sAngryMsg04[] = _("{STR_VAR_1}突然大叫了\n起来！");

const struct FollowerMsgInfo gFollowerAngryMessages[] = {
    {sAngryMsg00}, {sAngryMsg01}, {sAngryMsg02},
    {sAngryMsg03, EventScript_FollowerLookAway},
    {sAngryMsg04},
};

// Unconditional pensive messages
static const u8 sPensiveMsg00[] = _("{STR_VAR_1}安静的\n盯着下面看。");
static const u8 sPensiveMsg01[] = _("{STR_VAR_1}在四下张望！");
static const u8 sPensiveMsg02[] = _("{STR_VAR_1}一直盯着下面看。");
static const u8 sPensiveMsg03[] = _("{STR_VAR_1}强忍着\n睡意……");
static const u8 sPensiveMsg04[] = _("{STR_VAR_1}正在环视n着周围。");
static const u8 sPensiveMsg05[] = _("{STR_VAR_1}正看着\n周围发呆。");
static const u8 sPensiveMsg06[] = _("{STR_VAR_1}打了个\n大哈欠！");
static const u8 sPensiveMsg07[] = _("{STR_VAR_1}正在惬意\n地放松着。");
static const u8 sPensiveMsg08[] = _("{STR_VAR_1}一直在盯着\n你的脸。");
static const u8 sPensiveMsg09[] = _("{STR_VAR_1}一直在盯着\n你的脸。");
static const u8 sPensiveMsg10[] = _("{STR_VAR_1}对你非常\n感兴趣！");
static const u8 sPensiveMsg11[] = _("{STR_VAR_1}一直盯着\n下面看。");
static const u8 sPensiveMsg12[] = _("{STR_VAR_1}不停地\n闻着地面上的气味。");
static const u8 sPensiveMsg13[] = _("它一直在盯着什么\n都没有的地方……");
static const u8 sPensiveMsg14[] = _("{STR_VAR_1}目光锐利，全神贯注！");
static const u8 sPensiveMsg15[] = _("{STR_VAR_1}正在集中精神。");
static const u8 sPensiveMsg16[] = _("{STR_VAR_1}看着你\n点了点头。");
static const u8 sPensiveMsg17[] = _("{STR_VAR_1}看起来好像\n有点紧张。");
static const u8 sPensiveMsg18[] = _("{STR_VAR_1}看着\n你的脚印。");
static const u8 sPensiveMsg19[] = _("{STR_VAR_1}一直看着\n你的眼睛……");

const struct FollowerMsgInfo gFollowerPensiveMessages[] = {
    {sPensiveMsg00},
    {sPensiveMsg01, EventScript_FollowerLookAround},
    {sPensiveMsg02}, {sPensiveMsg03}, {sPensiveMsg04},
    {sPensiveMsg05, EventScript_FollowerLookAround},
    {sPensiveMsg06}, {sPensiveMsg07}, {sPensiveMsg08}, {sPensiveMsg09}, {sPensiveMsg10},
    {sPensiveMsg11, EventScript_FollowerLookAway},
    {sPensiveMsg12, EventScript_FollowerPokeGround},
    {sPensiveMsg13, EventScript_FollowerLookAway},
    {sPensiveMsg14}, {sPensiveMsg15}, {sPensiveMsg16}, {sPensiveMsg17}, {sPensiveMsg18}, {sPensiveMsg19},
};

// All 'love' messages are unconditional
static const u8 sLoveMsg00[] = _("{STR_VAR_1}突然\n靠到了你的身边！");
static const u8 sLoveMsg01[] = _("{STR_VAR_1}的脸颊\n变得红通通的！");
static const u8 sLoveMsg02[] = _("哇！{STR_VAR_1}突然抱着\n你了！");
static const u8 sLoveMsg03[] = _("哇！{STR_VAR_1}\n突然想和你玩！");
static const u8 sLoveMsg04[] = _("{STR_VAR_1}戳了戳\n你的脚。");
static const u8 sLoveMsg05[] = _("{STR_VAR_1}\n好像害羞了。");
static const u8 sLoveMsg06[] = _("啊{STR_VAR_1}啪地一下\n靠在了你身边。");
static const u8 sLoveMsg07[] = _("{STR_VAR_1}一脸崇拜\n地看着你！");
static const u8 sLoveMsg08[] = _("{STR_VAR_1}开心地\n靠了过来！");
static const u8 sLoveMsg09[] = _("{STR_VAR_1}突然\n靠到了你的脚边！");

const struct FollowerMsgInfo gFollowerLoveMessages[] = {
    {sLoveMsg00, EventScript_FollowerGetCloser},
    {sLoveMsg01},
    {sLoveMsg02, EventScript_FollowerCuddling},
    {sLoveMsg03},
    {sLoveMsg04, EventScript_FollowerCuddling},
    {sLoveMsg05},
    {sLoveMsg06, EventScript_FollowerCuddling},
    {sLoveMsg07},
    {sLoveMsg08, EventScript_FollowerGetCloser},
    {sLoveMsg09},
};

// Unconditional surprised messages
static const u8 sSurpriseMsg00[] = _("{STR_VAR_1}差点就\n摔倒了！");
static const u8 sSurpriseMsg01[] = _("{STR_VAR_1}向着\n你咬了过来！");
static const u8 sSurpriseMsg02[] = _("{STR_VAR_1}好像还不习惯\n他的名字。");
static const u8 sSurpriseMsg03[] = _("{STR_VAR_1}一直盯着下面看。");
static const u8 sSurpriseMsg04[] = _("它摔了一小跤，\n有点慌慌的！");
static const u8 sSurpriseMsg05[] = _("{STR_VAR_1}好像是在\n诉说着什么一般地低吼着。");
static const u8 sSurpriseMsg06[] = _("{STR_VAR_1}挺起了身板！");
static const u8 sSurpriseMsg07[] = _("{STR_VAR_1}转了过来\n并吼叫了起来！");
static const u8 sSurpriseMsg08[] = _("{STR_VAR_1}转了过来！");
static const u8 sSurpriseMsg09[] = _("它好像因为突然被搭话\n所以吓了一跳！");
static const u8 sSurpriseMsg10[] = _("嗅了嗅，\n闻到了很香的味道！");
static const u8 sSurpriseMsg11[] = _("{STR_VAR_1}感到很清爽。");
static const u8 sSurpriseMsg12[] = _("{STR_VAR_1}看起来\n快要倒下了！");
static const u8 sSurpriseMsg13[] = _("{STR_VAR_1}差点就\n摔倒了！");
static const u8 sSurpriseMsg14[] = _("{STR_VAR_1}小心地\n跟了上来！");
static const u8 sSurpriseMsg15[] = _("{STR_VAR_1}因为\n紧张，所以很激动。");
static const u8 sSurpriseMsg16[] = _("{STR_VAR_1}好像因为\n奇怪的气味，所以\l吓了一跳！");
static const u8 sSurpriseMsg17[] = _("{STR_VAR_1}因为害怕，\n向你身上靠了过来！");
static const u8 sSurpriseMsg18[] = _("{STR_VAR_1}感觉到了\n奇怪的气味。");
static const u8 sSurpriseMsg19[] = _("{STR_VAR_1}因为\n紧张，所以很激动。");
// Conditional messages, index 20
static const u8 sSurpriseMsg20[] = _("{STR_VAR_1} 似乎对下雨感到非常惊讶！");

const struct FollowerMsgInfo gFollowerSurpriseMessages[] = {
    {sSurpriseMsg00},
    {sSurpriseMsg01, EventScript_FollowerPokingPlayer},
    {sSurpriseMsg02}, {sSurpriseMsg03}, {sSurpriseMsg04}, {sSurpriseMsg05}, {sSurpriseMsg06},
    {sSurpriseMsg07, EventScript_FollowerLookAwayBark},
    {sSurpriseMsg08, EventScript_FollowerLookAway},
    {sSurpriseMsg09},
    {sSurpriseMsg10, EventScript_FollowerLookAround},
    {sSurpriseMsg11}, {sSurpriseMsg12}, {sSurpriseMsg13}, {sSurpriseMsg14}, {sSurpriseMsg15}, {sSurpriseMsg16},
    {sSurpriseMsg17, EventScript_FollowerCuddling},
    {sSurpriseMsg18},
    {sSurpriseMsg19, EventScript_FollowerLookAround},
    {sSurpriseMsg20},
};

// Unconditional curious messages
static const u8 sCuriousMsg00[] = _("它东张西望的，\n好像在找着什么。");
static const u8 sCuriousMsg01[] = _("它没有在看路，\n不小心撞到了你！");
static const u8 sCuriousMsg02[] = _("嗅了嗅，\n似乎附近有什么东西！");
static const u8 sCuriousMsg03[] = _("{STR_VAR_1}正在\n骨碌骨碌地\l滚着石头玩。");
static const u8 sCuriousMsg04[] = _("{STR_VAR_1}东张西望地\n在找着什么。");
static const u8 sCuriousMsg05[] = _("{STR_VAR_1}正在\n闻着你的气味。");
static const u8 sCuriousMsg06[] = _("{STR_VAR_1}好像有点\n犹豫……");

const struct FollowerMsgInfo gFollowerCuriousMessages[] = {
    {sCuriousMsg00, EventScript_FollowerLookAround},
    {sCuriousMsg01, EventScript_FollowerPokingPlayer},
    {sCuriousMsg02}, {sCuriousMsg03},
    {sCuriousMsg04, EventScript_FollowerLookAround},
    {sCuriousMsg05}, {sCuriousMsg06},
};

// Unconditional music messages
static const u8 sMusicMsg00[] = _("{STR_VAR_1}使出全力\n炫耀了一番！");
static const u8 sMusicMsg01[] = _("{STR_VAR_1}精神十足地\n动了起来！");
static const u8 sMusicMsg02[] = _("哇！{STR_VAR_1}，好像\n在高兴地跳舞。");
static const u8 sMusicMsg03[] = _("{STR_VAR_1}开心地\n跟在后面！");
static const u8 sMusicMsg04[] = _("{STR_VAR_1}好像\n想和你玩！");
static const u8 sMusicMsg05[] = _("{STR_VAR_1}在开心地\n跳着！");
static const u8 sMusicMsg06[] = _("{STR_VAR_1}\n竟然在哼着歌！");
static const u8 sMusicMsg07[] = _("{STR_VAR_1}向着\n你的腿咬了过来！");
static const u8 sMusicMsg08[] = _("{STR_VAR_1}转了过来\n并看着你！");
static const u8 sMusicMsg09[] = _("{STR_VAR_1}努力地，\n表现自己！");
static const u8 sMusicMsg10[] = _("哇！{STR_VAR_1}突然\n开心动了起来！");
static const u8 sMusicMsg11[] = _("{STR_VAR_1}好像非常\n开心！");
static const u8 sMusicMsg12[] = _("{STR_VAR_1}轻快地\n动了起来！");
static const u8 sMusicMsg13[] = _("它似乎闻到了一种\n令它怀念的熟悉味道……");
// Conditional music messages, index 14
static const u8 sMusicMsg14[] = _("{STR_VAR_1}因为下雨了\n非常高兴。");

const struct FollowerMsgInfo gFollowerMusicMessages[] = {
    {sMusicMsg00, EventScript_FollowerLookAround},
    {sMusicMsg01},
    {sMusicMsg02, EventScript_FollowerDance},
    {sMusicMsg03},
    {sMusicMsg04, EventScript_FollowerHopping},
    {sMusicMsg05, EventScript_FollowerHopping},
    {sMusicMsg06}, {sMusicMsg07}, {sMusicMsg08}, {sMusicMsg09},
    {sMusicMsg10, EventScript_FollowerDance},
    {sMusicMsg11},
    {sMusicMsg12, EventScript_FollowerHopping},
    {sMusicMsg13, EventScript_FollowerNostalgia},
    {sMusicMsg14}
};


static const u8 sPoisonedMsg00[] = _("{STR_VAR_1}中毒了，\n浑身都在发抖……");

const struct FollowerMsgInfo gFollowerPoisonedMessages[] = {
    {sPoisonedMsg00, EventScript_FollowerIsShivering},
};
