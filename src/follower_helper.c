#include "global.h"
#include "data.h"
#include "event_scripts.h"
#include "follower_helper.h"
#include "constants/battle.h"
#include "constants/followers.h"
#include "constants/metatile_behaviors.h"
#include "constants/pokemon.h"
#include "constants/region_map_sections.h"
#include "constants/songs.h"
#include "constants/weather.h"

#define TYPE_NOT_TYPE1 NUMBER_OF_MON_TYPES

// difficult conditional messages follow
static const u8 sCondMsg00[] = _("{STR_VAR_1}开心地\n摇摆着身体。");
static const u8 sCondMsg01[] = _("{STR_VAR_1}优雅地\n摇摆着身体。");
static const u8* const sCelebiTexts[] = {sCondMsg00, sCondMsg01, NULL};
static const u8 sCondMsg02[] = _("{STR_VAR_1}发出火焰并\n大声地吼叫了起来！");
static const u8 sCondMsg03[] = _("{STR_VAR_1}猛地发出了\n火焰！");
static const u8 sCondMsg04[] = _("{STR_VAR_1}突然发出了\n火焰!");
static const u8 sCondMsg05[] = _("{STR_VAR_1}猛地放出了\n火焰！");
static const u8* const sFireTexts[] = {sCondMsg02, sCondMsg03, sCondMsg04, sCondMsg05, NULL};
static const u8 sCondMsg06[] = _("{STR_VAR_1}一直在盯着\n宝可梦联盟。");
static const u8 sCondMsg07[] = _("它一直在\n凝望着山峰。");
static const u8 sCondMsg08[] = _("传来了一股很香的气味。");
static const u8 sCondMsg09[] = _("它正在观察货架。");
static const u8 sCondMsg10[] = _("{STR_VAR_1}正盯着\n货架。");
static const u8* const sShopTexts[] = {sCondMsg09, sCondMsg10, NULL};
static const u8 sCondMsg11[] = _("{STR_VAR_1} 的眼神\n变得坚定了起来！ ");
static const u8 sCondMsg12[] = _("{STR_VAR_1}很喜欢自行车。");
static const u8 sCondMsg13[] = _("{STR_VAR_1}想摸这个\n机器!");
static const u8 sCondMsg14[] = _("{STR_VAR_1}随着船身摇晃\n 动了起来!");
static const u8 sCondMsg15[] = _("{STR_VAR_1}随着船身摇晃\n摇摆着身体。");
static const u8 sCondMsg16[] = _("{STR_VAR_1}好像还\n不想下船。");
static const u8* const sBoatTexts[] = {sCondMsg14, sCondMsg15, sCondMsg16, NULL};
static const u8 sCondMsg17[] = _("{STR_VAR_1} 用心地听着\n机器的声音!");
static const u8* const sMachineTexts[] = {sCondMsg13, sCondMsg17, NULL};
static const u8 sCondMsg18[] = _("哇!它突然向外泼水！");
static const u8 sCondMsg19[] = _("它在吹着空中的沙子！");
static const u8 sCondMsg20[] = _("{STR_VAR_1}正在盯着地面\n拔草玩。");
static const u8 sCondMsg21[] = _("它正盯着你的脚印。");
static const u8 sCondMsg22[] = _("{STR_VAR_1}看起来好像,\n有点紧张还有点恐惧。");
static const u8 sCondMsg23[] = _("{STR_VAR_1}对这个地方\n正保持着警惕!");
static const u8* const sElevatorTexts[] = {sCondMsg22, sCondMsg23, NULL};
static const u8 sCondMsg24[] = _("它感受到了一股凉\n冰冰的冷气。 ");
static const u8 sCondMsg25[] = _("它差点滑倒。");
static const u8 sCondMsg26[] = _("它摸到冰块\n后吓了一跳！");
static const u8* const sColdTexts[] = {sCondMsg24, sCondMsg25, sCondMsg26, NULL};
static const u8 sCondMsg27[] = _("它的脸颊上\n有一片花瓣!");
static const u8 sCondMsg28[] = _("{STR_VAR_1}突然发出了低吼!");
static const u8 sCondMsg29[] = _("{STR_VAR_1}在瑟瑟发抖！");
static const u8 sCondMsg30[] = _("{STR_VAR_1}好像有点不开心了。");
static const u8* const sFearTexts[] = {sCondMsg29, sCondMsg30, NULL};
static const u8 sCondMsg31[] = _("{STR_VAR_1}躲到草丛\n里面避雨。");
static const u8 sCondMsg32[] = _("{STR_VAR_1}感觉很冷，\n向你身上靠了过来!");
static const u8 sCondMsg33[] = _("{STR_VAR_1}开始盯着\n大海。");
static const u8 sCondMsg34[] = _("你的宝可梦正用心\n地盯着大海！");
static const u8 sCondMsg35[] = _("{STR_VAR_1}盯着大海\n发呆。");
static const u8* const sSeaTexts[] = {sCondMsg33, sCondMsg34, sCondMsg35, NULL};
static const u8 sCondMsg36[] = _("{STR_VAR_1}用心的听着\n瀑布的声音。");
static const u8 sCondMsg37[] = _("{STR_VAR_1}因为下雨\n看上去很开心！");
static const u8 sCondMsg38[] = _("{STR_VAR_1}正盯着水中地\n倒影发呆。");
static const u8 sCondMsg39[] = _("{STR_VAR_1}听着落叶\n沙沙作响的声音\l非常放松。");
static const u8 sCondMsg40[] = _("{STR_VAR_1}正啃咬冰块。");
static const u8 sCondMsg41[] = _("{STR_VAR_1}正摸着冰块。");
static const u8* const sIceTexts[] = {sCondMsg26, sCondMsg40, sCondMsg41, NULL};
static const u8 sCondMsg42[] = _("{STR_VAR_1}被灼伤了，\n好像很疼!");

// See the struct definition in follower_helper.h for more info
const struct FollowerMsgInfoExtended gFollowerConditionalMessages[COND_MSG_COUNT] =
{
    [COND_MSG_CELEBI] =
    {
        .text = (u8*)sCelebiTexts,
        .textSpread = 1,
        .script = EventScript_FollowerDance,
        .emotion = FOLLOWER_EMOTION_NEUTRAL,
        .conditions =
        {
            MATCH_SPECIES(SPECIES_CELEBI),
        },
    },
    [COND_MSG_FIRE] =
    {
        .text = (u8*)sFireTexts,
        .textSpread = 1,
        .emotion = FOLLOWER_EMOTION_NEUTRAL,
        .conditions =
        {
            MATCH_TYPES(TYPE_FIRE, TYPE_FIRE),
        },
    },
    [COND_MSG_EVER_GRANDE] =
    {
        .text = sCondMsg06,
        .script = EventScript_FollowerFaceUp,
        .emotion = FOLLOWER_EMOTION_HAPPY,
        .conditions =
        {
            MATCH_MAP(EVER_GRANDE_CITY),
        },
    },
    [COND_MSG_ROUTE_112] =
    {
        .text = sCondMsg07,
        .emotion = FOLLOWER_EMOTION_HAPPY,
        .conditions =
        {
            MATCH_MAP(ROUTE112),
        },
    },
    [COND_MSG_DAY_CARE] =
    {
        .text = sCondMsg08,
        .script = EventScript_FollowerNostalgia,
        .emotion = FOLLOWER_EMOTION_NEUTRAL,
        .conditions =
        {
            MATCH_MAP(ROUTE117_POKEMON_DAY_CARE)
        },
    },
    [COND_MSG_MART] =
    {
        .text = (u8*)sShopTexts,
        .textSpread = 1,
        .script = EventScript_FollowerLookAround,
        .emotion = FOLLOWER_EMOTION_NEUTRAL,
        .conditions =
        {
            MATCH_MUSIC(MUS_POKE_MART)
        },
    },
    [COND_MSG_VICTORY_ROAD] =
    {
        .text = sCondMsg11,
        .emotion = FOLLOWER_EMOTION_PENSIVE,
        .conditions =
        {
            MATCH_MUSIC(MUS_VICTORY_ROAD)
        },
    },
    [COND_MSG_BIKE_SHOP] =
    {
        .text = sCondMsg12,
        .emotion = FOLLOWER_EMOTION_PENSIVE,
        .conditions =
        {
            MATCH_MAP(MAUVILLE_CITY_BIKE_SHOP)
        },
    },
    [COND_MSG_MACHINES] =
    {
        .text = (u8*)sMachineTexts,
        .textSpread = 1,
        .emotion = FOLLOWER_EMOTION_MUSIC,
        .orFlag = 1, // match any of these maps
        .conditions =
        {
            MATCH_MAP(NEW_MAUVILLE_INSIDE),
            MATCH_MAP(SLATEPORT_CITY_STERNS_SHIPYARD_1F),
            MATCH_MAP(SLATEPORT_CITY_STERNS_SHIPYARD_2F),
        },
    },
    [COND_MSG_SAILING] =
    {
        .text = (u8*)sBoatTexts,
        .textSpread = 1,
        .emotion = FOLLOWER_EMOTION_MUSIC,
        .script = EventScript_FollowerLookAround,
        .conditions =
        {
            MATCH_MUSIC(MUS_SAILING),
        },
    },
    [COND_MSG_PUDDLE] =
    {
        .text = sCondMsg18,
        .script = EventScript_FollowerHopping,
        .emotion = FOLLOWER_EMOTION_MUSIC,
        .conditions =
        {
            MATCH_ON_MB(MB_SHALLOW_WATER, MB_PUDDLE),
        },
    },
    [COND_MSG_SAND] =
    {
        .text = sCondMsg19,
        .emotion = FOLLOWER_EMOTION_MUSIC,
        .conditions =
        {
            MATCH_ON_MB(MB_SAND, MB_DEEP_SAND),
        },
    },
    [COND_MSG_GRASS] =
    {
        .text = sCondMsg20,
        .emotion = FOLLOWER_EMOTION_MUSIC,
        .conditions =
        {
            MATCH_ON_MB(MB_TALL_GRASS, MB_LONG_GRASS),
        },
    },
    [COND_MSG_FOOTPRINTS] =
    {
        .text = sCondMsg21,
        .emotion = FOLLOWER_EMOTION_MUSIC,
        .conditions =
        {
            MATCH_ON_MB(MB_SAND, MB_FOOTPRINTS),
        },
    },
    [COND_MSG_ELEVATOR] =
    {
        .text = (u8*)sElevatorTexts,
        .textSpread = 1,
        .emotion = FOLLOWER_EMOTION_SURPRISE,
        .conditions =
        {
            MATCH_MAP(LILYCOVE_CITY_DEPARTMENT_STORE_ELEVATOR),
        },
    },
    [COND_MSG_ICE_ROOM] =
    {
        .text = (u8*)sColdTexts,
        .textSpread = 1,
        .emotion = FOLLOWER_EMOTION_SURPRISE,
        .conditions =
        {
            MATCH_MAP(SHOAL_CAVE_LOW_TIDE_ICE_ROOM),
        },
    },
    [COND_MSG_ROUTE_117] =
    {
        .text = sCondMsg27,
        .emotion = FOLLOWER_EMOTION_SURPRISE,
        .conditions =
        {
            MATCH_MAP(ROUTE117),
        },
    },
    [COND_MSG_DRAGON_GROWL] =
    {
        .text = sCondMsg28,
        .emotion = FOLLOWER_EMOTION_UPSET,
        .conditions =
        {
            MATCH_TYPES(TYPE_DRAGON, TYPE_DRAGON),
            MATCH_MAPSEC(MAPSEC_SKY_PILLAR),
        },
    },
    [COND_MSG_FEAR] =
    {
        .text = (u8*)sFearTexts,
        .textSpread = 1,
        .emotion = FOLLOWER_EMOTION_UPSET,
        .conditions =
        {
            MATCH_NOT_TYPES(TYPE_GHOST, TYPE_GHOST),
            MATCH_MAPSEC(MAPSEC_MT_PYRE),
            MATCH_MUSIC(MUS_MT_PYRE),
        },
    },
    [COND_MSG_FIRE_RAIN] =
    {
        .text = sCondMsg31,
        .emotion = FOLLOWER_EMOTION_UPSET,
        .conditions =
        {
            MATCH_TYPES(TYPE_FIRE, TYPE_FIRE),
            MATCH_WEATHER(WEATHER_RAIN, WEATHER_RAIN_THUNDERSTORM),
        },
    },
    [COND_MSG_FROZEN] =
    {
        .text = sCondMsg32,
        .emotion = FOLLOWER_EMOTION_UPSET,
        .conditions =
        {
           MATCH_STATUS(STATUS1_FREEZE),
        },
    },
    [COND_MSG_SEASIDE] =
    {
        .text = (u8*)sSeaTexts,
        .textSpread = 1,
        .script = EventScript_FollowerFaceResult,
        .emotion = FOLLOWER_EMOTION_MUSIC,
        .conditions =
        {
            MATCH_NEAR_MB(MB_OCEAN_WATER, 5),
        },
    },
    [COND_MSG_WATERFALL] =
    {
        .text = sCondMsg36,
        .script = EventScript_FollowerFaceResult,
        .emotion = FOLLOWER_EMOTION_MUSIC,
        .conditions =
        {
            MATCH_NEAR_MB(MB_WATERFALL, 5),
        },
    },
    [COND_MSG_RAIN] =
    {
        .text = sCondMsg37,
        .emotion = FOLLOWER_EMOTION_MUSIC,
        .conditions =
        {
        MATCH_NOT_TYPES(TYPE_FIRE, TYPE_FIRE),
        MATCH_WEATHER(WEATHER_RAIN, WEATHER_RAIN_THUNDERSTORM)
    }
    },
    [COND_MSG_REFLECTION] =
    {
        .text = sCondMsg38,
        .script = EventScript_FollowerFaceResult,
        .emotion = FOLLOWER_EMOTION_PENSIVE,
        .conditions =
        {
            MATCH_NEAR_MB(MB_POND_WATER, 1),
        },
    },
    [COND_MSG_LEAVES] =
    {
        .text = sCondMsg39,
        .emotion = FOLLOWER_EMOTION_PENSIVE,
        .conditions =
        {
            MATCH_MAPSEC(MAPSEC_PETALBURG_WOODS),
        },
    },
    [COND_MSG_ICE] =
    {
        .text = (u8*)sIceTexts,
        .textSpread = 1,
        .script = EventScript_FollowerFaceResult,
        .emotion = FOLLOWER_EMOTION_PENSIVE,
        .conditions =
        {
            MATCH_NEAR_MB(MB_ICE, 1),
        },
    },
    [COND_MSG_BURN] =
    {
        .text = sCondMsg42,
        .emotion = FOLLOWER_EMOTION_SAD,
        .conditions =
        {
            MATCH_STATUS(STATUS1_BURN),
        },
    },
};

// Pool of "unconditional" follower messages
const struct FollowerMessagePool gFollowerBasicMessages[FOLLOWER_EMOTION_LENGTH] =
{
    [FOLLOWER_EMOTION_HAPPY]    = {gFollowerHappyMessages,    EventScript_FollowerGeneric, FOLLOWER_HAPPY_MESSAGE_COUNT},
    [FOLLOWER_EMOTION_NEUTRAL]  = {gFollowerNeutralMessages,  EventScript_FollowerGeneric, FOLLOWER_NEUTRAL_MESSAGE_COUNT},
    [FOLLOWER_EMOTION_SAD]      = {gFollowerSadMessages,      EventScript_FollowerGeneric, FOLLOWER_SAD_MESSAGE_COUNT},
    [FOLLOWER_EMOTION_UPSET]    = {gFollowerUpsetMessages,    EventScript_FollowerGeneric, FOLLOWER_UPSET_MESSAGE_COUNT},
    [FOLLOWER_EMOTION_ANGRY]    = {gFollowerAngryMessages,    EventScript_FollowerGeneric, FOLLOWER_ANGRY_MESSAGE_COUNT},
    [FOLLOWER_EMOTION_PENSIVE]  = {gFollowerPensiveMessages,  EventScript_FollowerGeneric, FOLLOWER_PENSIVE_MESSAGE_COUNT},
    [FOLLOWER_EMOTION_LOVE]     = {gFollowerLoveMessages,     EventScript_FollowerGeneric, FOLLOWER_LOVE_MESSAGE_COUNT},
    [FOLLOWER_EMOTION_SURPRISE] = {gFollowerSurpriseMessages, EventScript_FollowerGeneric, FOLLOWER_SURPRISE_MESSAGE_COUNT},
    [FOLLOWER_EMOTION_CURIOUS]  = {gFollowerCuriousMessages,  EventScript_FollowerGeneric, FOLLOWER_CURIOUS_MESSAGE_COUNT},
    [FOLLOWER_EMOTION_MUSIC]    = {gFollowerMusicMessages,    EventScript_FollowerGeneric, FOLLOWER_MUSIC_MESSAGE_COUNT},
    [FOLLOWER_EMOTION_POISONED] = {gFollowerPoisonedMessages, EventScript_FollowerGeneric, FOLLOWER_POISONED_MESSAGE_COUNT},
};
