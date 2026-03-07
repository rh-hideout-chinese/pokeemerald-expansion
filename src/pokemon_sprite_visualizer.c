#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_gfx_sfx_util.h"
#include "battle_environment.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_object_movement.h"
#include "field_weather.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "item.h"
#include "item_icon.h"
#include "list_menu.h"
#include "m4a.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "palette_util.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_animation.h"
#include "pokemon_sprite_visualizer.h"
#include "pokemon_icon.h"
#include "reset_rtc_screen.h"
#include "scanline_effect.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text_window.h"
#include "trainer_pokemon_sprites.h"

#include "constants/global.h"
#include "constants/battle_anim.h"
#include "constants/event_objects.h"
#include "constants/items.h"
#include "constants/rgb.h"
#include "constants/songs.h"

extern const struct BattleEnvironment gBattleEnvironmentInfo[BATTLE_ENVIRONMENT_COUNT];
extern const struct CompressedSpriteSheet gSpriteSheet_EnemyShadow;
extern const struct CompressedSpriteSheet gSpriteSheet_EnemyShadowsSized;
extern const struct SpriteTemplate gSpriteTemplate_EnemyShadow;
extern const struct SpritePalette sSpritePalettes_HealthBoxHealthBar[2];
extern const struct UCoords8 sBattlerCoords[][MAX_BATTLERS_COUNT] ;
static const u16 sBgColor[] = {RGB_WHITE};

static struct PokemonSpriteVisualizer *GetStructPtr(u8 taskId)
{
    u8 *taskDataPtr = (u8 *)(&gTasks[taskId].data[0]);

    return (struct PokemonSpriteVisualizer*)(T1_READ_PTR(taskDataPtr));
}

//BgTemplates
static const struct BgTemplate sBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 24,
        .screenSize = 2,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 1,
        .charBaseIndex = BACKGROUND_1_CHAR_BASE,
        .mapBaseIndex = BACKGROUND_1_MAP_BASE,
        .screenSize = 2,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 1,
        .mapBaseIndex = 30,
        .screenSize = 1,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    },
   {
        .bg = 3,
        .charBaseIndex = BACKGROUND_3_CHAR_BASE,
        .mapBaseIndex = BACKGROUND_3_MAP_BASE,
        .screenSize = 1,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    },
};

#define TEXT_AREA_Y      14
#define TEXT_AREA_HEIGHT  6

//WindowTemplates
static const struct WindowTemplate sPokemonSpriteVisualizerWindowTemplate[] =
{
    [WIN_NAME_NUMBERS] =
    {
        .bg = 0,
        .tilemapLeft = 15,
        .tilemapTop = 12,
        .width = 15,
        .height = 2,
        .paletteNum = 0xF,
        .baseBlock = 1
    },
    [WIN_INSTRUCTIONS] =
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 15,
        .height = 4,
        .paletteNum = 0xF,
        .baseBlock = 1 + 30
    },
    [WIN_BOTTOM_LEFT] =
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = TEXT_AREA_Y,
        .width = 6,
        .height = TEXT_AREA_HEIGHT,
        .paletteNum = 0xF,
        .baseBlock = 1 + 30 + 60
    },
    [WIN_BOTTOM_RIGHT] =
    {
        .bg = 0,
        .tilemapLeft = 7,
        .tilemapTop = TEXT_AREA_Y,
        .width = 24,
        .height = TEXT_AREA_HEIGHT,
        .paletteNum = 0xF,
        .baseBlock = 1 + 30 + 60 + 36
    },
    [WIN_FOOTPRINT] =
    {
        .bg = 0,
        .tilemapLeft = 27,
        .tilemapTop = TEXT_AREA_Y,
        .width = 2,
        .height = 2,
        .paletteNum = 0xF,
        .baseBlock = 1 + 30 + 60 + 36 + 144,
    },
    DUMMY_WIN_TEMPLATE,
};

//Lookup tables
const u8 gBackAnimNames[][23 + 1] =
{
    [BACK_ANIM_NONE]                    = _("无"),
    [BACK_ANIM_H_VIBRATE]               = _("横向振动"),
    [BACK_ANIM_H_SLIDE]                 = _("横向滑动"),
    [BACK_ANIM_H_SPRING]                = _("横向弹跳"),
    [BACK_ANIM_H_SPRING_REPEATED]       = _("重复横向弹跳"),
    [BACK_ANIM_SHRINK_GROW]             = _("收缩变大"),
    [BACK_ANIM_GROW]                    = _("变大"),
    [BACK_ANIM_CIRCLE_COUNTERCLOCKWISE] = _("逆时针转圈"),
    [BACK_ANIM_H_SHAKE]                 = _("横向摇晃"),
    [BACK_ANIM_V_SHAKE]                 = _("纵向摇晃"),
    [BACK_ANIM_V_SHAKE_H_SLIDE]         = _("纵向摇晃 横向滑动"),
    [BACK_ANIM_V_STRETCH]               = _("纵向拉伸"),
    [BACK_ANIM_H_STRETCH]               = _("横向拉伸"),
    [BACK_ANIM_GROW_STUTTER]            = _("断断续续变大"),
    [BACK_ANIM_V_SHAKE_LOW]             = _("纵向摇晃 低"),
    [BACK_ANIM_TRIANGLE_DOWN]           = _("向下三角形移动"),
    [BACK_ANIM_CONCAVE_ARC_LARGE]       = _("大凹弧"),
    [BACK_ANIM_CONVEX_DOUBLE_ARC]       = _("双凸弧"),
    [BACK_ANIM_CONCAVE_ARC_SMALL]       = _("小凹弧"),
    [BACK_ANIM_DIP_RIGHT_SIDE]          = _("右侧倾斜"),
    [BACK_ANIM_SHRINK_GROW_VIBRATE]     = _("收缩 变大 振动"),
    [BACK_ANIM_JOLT_RIGHT]              = _("右摇"),
    [BACK_ANIM_SHAKE_FLASH_YELLOW]      = _("摇晃 闪烁黄光"),
    [BACK_ANIM_SHAKE_GLOW_RED]          = _("摇晃 闪烁红光"),
    [BACK_ANIM_SHAKE_GLOW_GREEN]        = _("摇晃 闪烁绿光"),
    [BACK_ANIM_SHAKE_GLOW_BLUE]         = _("摇晃 闪烁蓝光"),
};
const u8 gFrontAnimNames[][34] =
{
    [ANIM_V_SQUISH_AND_BOUNCE]               = _("纵向挤压和弹跳"),
    [ANIM_CIRCULAR_STRETCH_TWICE]            = _("两次圆形拉伸"),
    [ANIM_H_VIBRATE]                         = _("横向振动"),
    [ANIM_H_SLIDE]                           = _("横向滑动"),
    [ANIM_V_SLIDE]                           = _("纵向滑动"),
    [ANIM_BOUNCE_ROTATE_TO_SIDES]            = _("弹跳 向侧面旋转"),
    [ANIM_V_JUMPS_H_JUMPS]                   = _("纵向跳跃 横向跳跃"),
    [ANIM_ROTATE_TO_SIDES]                   = _("向侧面旋转"),
    [ANIM_ROTATE_TO_SIDES_TWICE]             = _("向侧面旋转两下"),
    [ANIM_GROW_VIBRATE]                      = _("变大震动"),
    [ANIM_ZIGZAG_FAST]                       = _("快速Z形"),
    [ANIM_SWING_CONCAVE]                     = _("凹摆"),
    [ANIM_SWING_CONCAVE_FAST]                = _("快速凹摆"),
    [ANIM_SWING_CONVEX]                      = _("凸摆"),
    [ANIM_SWING_CONVEX_FAST]                 = _("快速凸摆"),
    [ANIM_H_SHAKE]                           = _("横向摇晃"),
    [ANIM_V_SHAKE]                           = _("纵向摇晃"),
    [ANIM_CIRCULAR_VIBRATE]                  = _("圆形震动"),
    [ANIM_TWIST]                             = _("扭转"),
    [ANIM_SHRINK_GROW]                       = _("收缩变大"),
    [ANIM_CIRCLE_C_CLOCKWISE]                = _("顺时针旋转"),
    [ANIM_GLOW_BLACK]                        = _("黑色发光"),
    [ANIM_H_STRETCH]                         = _("横向伸展"),
    [ANIM_V_STRETCH]                         = _("纵向伸展"),
    [ANIM_RISING_WOBBLE]                     = _("上升摆动"),
    [ANIM_V_SHAKE_TWICE]                     = _("纵向摇晃两下"),
    [ANIM_TIP_MOVE_FORWARD]                  = _("尖端向前移动"),
    [ANIM_H_PIVOT]                           = _("横向旋转"),
    [ANIM_V_SLIDE_WOBBLE]                    = _("纵向滑动摆动"),
    [ANIM_H_SLIDE_WOBBLE]                    = _("横向滑动摆动"),
    [ANIM_V_JUMPS_BIG]                       = _("纵向大跳跃"),
    [ANIM_SPIN_LONG]                         = _("长旋转"),
    [ANIM_GLOW_ORANGE]                       = _("发橙光"),
    [ANIM_GLOW_RED]                          = _("发红光"),
    [ANIM_GLOW_BLUE]                         = _("发蓝光"),
    [ANIM_GLOW_YELLOW]                       = _("发黄光"),
    [ANIM_GLOW_PURPLE]                       = _("发紫光"),
    [ANIM_BACK_AND_LUNGE]                    = _("后弓箭步"),
    [ANIM_BACK_FLIP]                         = _("后空翻"),
    [ANIM_FLICKER]                           = _("闪烁"),
    [ANIM_BACK_FLIP_BIG]                     = _("大后空翻"),
    [ANIM_FRONT_FLIP]                        = _("前空翻"),
    [ANIM_TUMBLING_FRONT_FLIP]               = _("翻滚前空翻"),
    [ANIM_FIGURE_8]                          = _("8字形"),
    [ANIM_FLASH_YELLOW]                      = _("黄色闪烁"),
    [ANIM_SWING_CONCAVE_FAST_SHORT]          = _("快速短距离凹摆"),
    [ANIM_SWING_CONVEX_FAST_SHORT]           = _("快速短距离凹摆"),
    [ANIM_ROTATE_UP_SLAM_DOWN]               = _("向上旋转猛击向下"),
    [ANIM_DEEP_V_SQUISH_AND_BOUNCE]          = _("深纵向挤压弹跳"),
    [ANIM_H_JUMPS]                           = _("横向跳跃"),
    [ANIM_H_JUMPS_V_STRETCH]                 = _("横向跳跃纵向伸展"),
    [ANIM_ROTATE_TO_SIDES_FAST]              = _("快速向侧面旋转"),
    [ANIM_ROTATE_UP_TO_SIDES]                = _("向上向侧面旋转"),
    [ANIM_FLICKER_INCREASING]                = _("渐增闪烁"),
    [ANIM_TIP_HOP_FORWARD]                   = _("向前倾斜跳跃"),
    [ANIM_PIVOT_SHAKE]                       = _("旋转摇晃"),
    [ANIM_TIP_AND_SHAKE]                     = _("倾斜并摇晃"),
    [ANIM_VIBRATE_TO_CORNERS]                = _("向角落震动"),
    [ANIM_GROW_IN_STAGES]                    = _("分阶段变大"),
    [ANIM_V_SPRING]                          = _("纵向弹跳"),
    [ANIM_V_REPEATED_SPRING]                 = _("纵向重复弹跳"),
    [ANIM_SPRING_RISING]                     = _("弹跳上升"),
    [ANIM_H_SPRING]                          = _("横向弹跳"),
    [ANIM_H_REPEATED_SPRING_SLOW]            = _("横向重复弹跳慢速"),
    [ANIM_H_SLIDE_SHRINK]                    = _("横向滑动收缩"),
    [ANIM_LUNGE_GROW]                        = _("弓步变大"),
    [ANIM_CIRCLE_INTO_BG]                    = _("转圈入背景"),
    [ANIM_RAPID_H_HOPS]                      = _("快速横向跳跃"),
    [ANIM_FOUR_PETAL]                        = _("四瓣形移动"),
    [ANIM_V_SQUISH_AND_BOUNCE_SLOW]          = _("纵向挤压弹跳慢速"),
    [ANIM_H_SLIDE_SLOW]                      = _("横向滑动慢速"),
    [ANIM_V_SLIDE_SLOW]                      = _("纵向滑动慢速"),
    [ANIM_BOUNCE_ROTATE_TO_SIDES_SMALL]      = _("弹跳向侧面小幅旋转"),
    [ANIM_BOUNCE_ROTATE_TO_SIDES_SLOW]       = _("弹跳向侧面慢速旋转"),
    [ANIM_BOUNCE_ROTATE_TO_SIDES_SMALL_SLOW] = _("弹跳向侧面小幅旋转慢速"),
    [ANIM_ZIGZAG_SLOW]                       = _("锯齿形慢速"),
    [ANIM_H_SHAKE_SLOW]                      = _("横向慢速摇晃"),
    [ANIM_V_SHAKE_SLOW]                      = _("纵向慢速摇晃"),
    [ANIM_TWIST_TWICE]                       = _("扭动两次"),
    [ANIM_CIRCLE_C_CLOCKWISE_SLOW]           = _("顺时针慢速旋转"),
    [ANIM_V_SHAKE_TWICE_SLOW]                = _("纵向慢速摇晃两次"),
    [ANIM_V_SLIDE_WOBBLE_SMALL]              = _("纵向滑行小幅度摇摆"),
    [ANIM_V_JUMPS_SMALL]                     = _("纵向小幅度跳跃"),
    [ANIM_SPIN]                              = _("旋转"),
    [ANIM_TUMBLING_FRONT_FLIP_TWICE]         = _("翻滚前空翻两次"),
    [ANIM_DEEP_V_SQUISH_AND_BOUNCE_TWICE]    = _("纵向深蹲挤压 弹跳两次"),
    [ANIM_H_JUMPS_V_STRETCH_TWICE]           = _("横向跳跃 纵向伸展两次"),
    [ANIM_V_SHAKE_BACK]                      = _("纵向向后摇晃"),
    [ANIM_V_SHAKE_BACK_SLOW]                 = _("纵向慢速向后摇晃"),
    [ANIM_V_SHAKE_H_SLIDE_SLOW]              = _("纵向摇晃 横向慢速滑动"),
    [ANIM_V_STRETCH_BOTH_ENDS_SLOW]          = _("纵向缓慢拉伸两端"),
    [ANIM_H_STRETCH_FAR_SLOW]                = _("横向缓慢拉伸远距离"),
    [ANIM_V_SHAKE_LOW_TWICE]                 = _("纵向低速摇晃两次"),
    [ANIM_H_SHAKE_FAST]                      = _("横向快速摇晃"),
    [ANIM_H_SLIDE_FAST]                      = _("横向快速滑动"),
    [ANIM_H_VIBRATE_FAST]                    = _("横向快速振动"),
    [ANIM_H_VIBRATE_FASTEST]                 = _("横向最快振动"),
    [ANIM_V_SHAKE_BACK_FAST]                 = _("纵向快速向后摇晃"),
    [ANIM_V_SHAKE_LOW_TWICE_SLOW]            = _("纵向慢速低速摇晃两次"),
    [ANIM_V_SHAKE_LOW_TWICE_FAST]            = _("纵向快速低速摇晃两次"),
    [ANIM_CIRCLE_C_CLOCKWISE_LONG]           = _("顺时针转圈 长"),
    [ANIM_GROW_STUTTER_SLOW]                 = _("慢速变大"),
    [ANIM_V_SHAKE_H_SLIDE]                   = _("纵向摇动 横向滑动"),
    [ANIM_V_SHAKE_H_SLIDE_FAST]              = _("纵向摇动 横向快速滑动"),
    [ANIM_TRIANGLE_DOWN_SLOW]                = _("三角形向下缓慢"),
    [ANIM_TRIANGLE_DOWN]                     = _("三角形向下"),
    [ANIM_TRIANGLE_DOWN_TWICE]               = _("三角形向下两次"),
    [ANIM_GROW]                              = _("变大"),
    [ANIM_GROW_TWICE]                        = _("变大两次"),
    [ANIM_H_SPRING_FAST]                     = _("横向快速弹起"),
    [ANIM_H_SPRING_SLOW]                     = _("横向缓慢弹起"),
    [ANIM_H_REPEATED_SPRING_FAST]            = _("横向反复快速弹起"),
    [ANIM_H_REPEATED_SPRING]                 = _("横向反复弹起"),
    [ANIM_SHRINK_GROW_FAST]                  = _("收缩 快速变大"),
    [ANIM_SHRINK_GROW_SLOW]                  = _("收缩 缓慢变大"),
    [ANIM_V_STRETCH_BOTH_ENDS]               = _("纵向两端拉伸"),
    [ANIM_V_STRETCH_BOTH_ENDS_TWICE]         = _("纵向两端拉伸两次"),
    [ANIM_H_STRETCH_FAR_TWICE]               = _("横向向远拉伸两次"),
    [ANIM_H_STRETCH_FAR]                     = _("横向向远拉伸"),
    [ANIM_GROW_STUTTER_TWICE]                = _("变大 停顿两次"),
    [ANIM_GROW_STUTTER]                      = _("变大 停顿"),
    [ANIM_CONCAVE_ARC_LARGE_SLOW]            = _("大凹弧 慢速"),
    [ANIM_CONCAVE_ARC_LARGE]                 = _("大凹弧"),
    [ANIM_CONCAVE_ARC_LARGE_TWICE]           = _("大凹弧 两次"),
    [ANIM_CONVEX_DOUBLE_ARC_SLOW]            = _("双凸弧 慢速"),
    [ANIM_CONVEX_DOUBLE_ARC]                 = _("双凸弧"),
    [ANIM_CONVEX_DOUBLE_ARC_TWICE]           = _("双凸弧 两次"),
    [ANIM_CONCAVE_ARC_SMALL_SLOW]            = _("小凹弧 慢速"),
    [ANIM_CONCAVE_ARC_SMALL]                 = _("小凹弧"),
    [ANIM_CONCAVE_ARC_SMALL_TWICE]           = _("小凹弧 两次"),
    [ANIM_H_DIP]                             = _("水平倾斜"),
    [ANIM_H_DIP_FAST]                        = _("水平快速倾斜"),
    [ANIM_H_DIP_TWICE]                       = _("水平倾斜两圈"),
    [ANIM_SHRINK_GROW_VIBRATE_FAST]          = _("快速收缩变大振动"),
    [ANIM_SHRINK_GROW_VIBRATE]               = _("快速收缩变大振动"),
    [ANIM_SHRINK_GROW_VIBRATE_SLOW]          = _("慢速收缩变大振动"),
    [ANIM_JOLT_RIGHT_FAST]                   = _("快速右摇"),
    [ANIM_JOLT_RIGHT]                        = _("右摇"),
    [ANIM_JOLT_RIGHT_SLOW]                   = _("慢速右摇"),
    [ANIM_SHAKE_FLASH_YELLOW_FAST]           = _("快速摇晃闪黄光"),
    [ANIM_SHAKE_FLASH_YELLOW]                = _("快速摇晃闪黄光"),
    [ANIM_SHAKE_FLASH_YELLOW_SLOW]           = _("慢速摇晃闪黄光"),
    [ANIM_SHAKE_GLOW_RED_FAST]               = _("快速摇晃发红光"),
    [ANIM_SHAKE_GLOW_RED]                    = _("快速摇晃发红光"),
    [ANIM_SHAKE_GLOW_RED_SLOW]               = _("慢速摇晃发红光"),
    [ANIM_SHAKE_GLOW_GREEN_FAST]             = _("快速摇晃发绿光"),
    [ANIM_SHAKE_GLOW_GREEN]                  = _("快速摇晃发绿光"),
    [ANIM_SHAKE_GLOW_GREEN_SLOW]             = _("慢速摇晃发绿光"),
    [ANIM_SHAKE_GLOW_BLUE_FAST]              = _("快速摇晃发蓝光"),
    [ANIM_SHAKE_GLOW_BLUE]                   = _("快速摇晃发蓝光"),
    [ANIM_SHAKE_GLOW_BLUE_SLOW]              = _("慢速摇晃发蓝光"),
    [ANIM_SHAKE_GLOW_BLACK_SLOW]             = _("慢速摇晃发黑光"),
    [ANIM_SHAKE_GLOW_WHITE_SLOW]             = _("慢速摇晃发白光"),
    [ANIM_SHAKE_GLOW_PURPLE_SLOW]            = _("慢速摇晃发紫光"),
};

#define MOVE_BACKGROUND_NAME_LENGTH 28
const u8 gMoveBackgroundNames[BG_COUNT][MOVE_BACKGROUND_NAME_LENGTH] =
{
    [BG_NONE]                      = _("无"),
    [BG_DARK]                      = _("恶"),
    [BG_GHOST]                     = _("幽灵"),
    [BG_PSYCHIC]                   = _("超能力"),
    [BG_IMPACT_OPPONENT]           = _("冲击 - 对手"),
    [BG_IMPACT_PLAYER]             = _("冲击 - 我方"),
    [BG_IMPACT_CONTESTS]           = _("冲击 - 华丽大赛"),
    [BG_DRILL]                     = _("钻头"),
    [BG_DRILL_CONTESTS]            = _("钻头 - 华丽大赛"),
    [BG_HIGHSPEED_OPPONENT]        = _("高速 - 对手"),
    [BG_HIGHSPEED_PLAYER]          = _("高速 - 我方"),
    [BG_THUNDER]                   = _("雷电"),
    [BG_GUILLOTINE_OPPONENT]       = _("极落钳 - 对手"),
    [BG_GUILLOTINE_PLAYER]         = _("极落钳 - 我方"),
    [BG_GUILLOTINE_CONTESTS]       = _("极落钳 - 华丽大赛"),
    [BG_ICE]                       = _("冰"),
    [BG_COSMIC]                    = _("宇宙"),
    [BG_IN_AIR]                    = _("空中"),
    [BG_SKY]                       = _("天空"),
    [BG_SKY_CONTESTS]              = _("天空 - 华丽大赛"),
    [BG_AURORA]                    = _("极光"),
    [BG_FISSURE]                   = _("地裂"),
    [BG_BUG_OPPONENT]              = _("虫 - 对手"),
    [BG_BUG_PLAYER]                = _("虫 - 我方"),
    [BG_SOLAR_BEAM_OPPONENT]       = _("日光束 - 对手"),
    [BG_SOLAR_BEAM_PLAYER]         = _("日光束 - 我方"),
    [BG_SOLAR_BEAM_CONTESTS]       = _("日光束 - 华丽大赛"),
    [BG_MAGMA_STORM]               = _("熔岩风暴"),
    [BG_GIGA_IMPACT_OPPONENT]      = _("终极冲击 - 对手"),
    [BG_GIGA_IMPACT_PLAYER]        = _("终极冲击 - 我方"),
    [BG_GIGA_IMPACT_CONTESTS]      = _("终极冲击 - 华丽大赛"),
    [BG_TRICK_ROOM]                = _("戏法空间"),
    [BG_ROCK_WRECKER]              = _("岩石炮"),
    [BG_SPACIAL_REND_OPPONENT]     = _("亚空裂斩 - 对手"),
    [BG_SPACIAL_REND_PLAYER]       = _("亚空裂斩 - 我方"),
    [BG_DARK_VOID]                 = _("暗黑洞"),
    [BG_WATER]                     = _("水"),
    [BG_NIGHTMARE]                 = _("噩梦"),
    [BG_LEAF_STORM]                = _("飞叶风暴"),
    [BG_FIRE]                      = _("火"),
    [BG_FIRE_2]                    = _("火 2"),
    [BG_WATER_2]                   = _("水 2"),
    [BG_POISON]                    = _("毒"),
    [BG_AEROBLAST]                 = _("气旋攻击"),
    [BG_HURRICANE]                 = _("暴风"),
    [BG_ELECTRIC_TERRAIN]          = _("电气场地"),
    [BG_GRASSY_TERRAIN]            = _("青草场地"),
    [BG_MISTY_TERRAIN]             = _("薄雾场地"),
    [BG_PSYCHIC_TERRAIN]           = _("精神场地"),
    [BG_FOCUS_BLAST]               = _("真气弹"),
    [BG_GUNK_SHOT]                 = _("垃圾射击"),
    [BG_HYDRO_CANNON]              = _("加农水炮"),
    [BG_WONDER_ROOM]               = _("奇妙空间"),
    [BG_MAGIC_ROOM]                = _("魔法空间"),
    [BG_HYPERSPACE_FURY]           = _("异次元狂怒"),
    [BG_BOLT_STRIKE]               = _("雷击"),
    [BG_ZMOVE_ACTIVATE]            = _("Z招式发动"),
    [BG_TECTONIC_RAGE]             = _("地平天成大裂斩"),
    [BG_ROCK_FIELD_DAY]            = _("岩石场地 - 白天"),
    [BG_ROCK_FIELD_AFTERNOON]      = _("岩石场地 - 傍晚"),
    [BG_ROCK_FIELD_NIGHT]          = _("岩石场地 - 夜晚"),
    [BG_ZMOVE_MOUNTAIN]            = _("Z招式山脉"),
    [BG_NEVERENDING_NIGHTMARE]     = _("无尽暗夜之诱惑"),
    [BG_WATER_PULSE]               = _("水之波动"),
    [BG_INFERNO_OVERDRIVE]         = _("超强极限爆焰"),
    [BG_BLOOM_DOOM]                = _("绚烂缤纷花绽放"),
    [BG_SHATTERED_PSYCHE]          = _("至高精神破坏波"),
    [BG_TWINKLE_TACKLE]            = _("可爱星星飞天撞"),
    [BG_BLACK_HOLE_ECLIPSE]        = _("黑洞吞噬万物灭"),
    [BG_SOULSTEALING_7STAR_STRIKE] = _("七星夺魂腿"),
    [BG_MALICIOUS_MOONSAULT]       = _("极恶飞跃粉碎击"),
    [BG_CLANGOROUS_SOULBLAZE]      = _("炽魂热舞烈音爆"),
    [BG_SNUGGLE_FOREVER]           = _("亲密无间大乱揍"),
    [BG_MAX_LIGHTNING]             = _("极巨闪电"),
    [BG_GARBAGE_FALLS]             = _("垃圾坠落"),
    [BG_HYPER_BEAM]                = _("破坏光线"), 
    [BG_DYNAMAX_CANNON]            = _("极巨炮"),
    [BG_AURA_SPHERE]               = _("波导弹"),
    [BG_STEEL_BEAM_OPPONENT]       = _("铁蹄光线 - 对手"),
    [BG_STEEL_BEAM_PLAYER]         = _("铁蹄光线 - 我方"),
    [BG_CHLOROBLAST]               = _("叶绿爆震"),
    [BG_RAINBOW_PLAYER]            = _("彩虹 - 我方"),
    [BG_RAINBOW_OPPONENT]          = _("彩虹 - 对手"),
    [BG_SWAMP]                     = _("湿地"),
};

const u8 sShadowSizeLabels[][8] =
{
    [SHADOW_SIZE_S]                 = _(" 小   "),
    [SHADOW_SIZE_M]                 = _(" 中   "),
    [SHADOW_SIZE_L]                 = _(" 大   "),
    [SHADOW_SIZE_XL_BATTLE_ONLY]    = _(" 特大"),
};

//Function declarations
static void PrintDigitChars(struct PokemonSpriteVisualizer *data);
static void SetUpModifyArrows(struct PokemonSpriteVisualizer *data);
static void UpdateBattlerValue(struct PokemonSpriteVisualizer *data);
static void ValueToCharDigits(u8 *charDigits, u32 newValue, u8 maxDigits);
static bool32 TryMoveDigit(struct PokemonSpriteVisualizerModifyArrows *modArrows, bool32 moveUp);
static void CB2_PokemonSpriteVisualizerRunner(void);
static void ResetBGs_PokemonSpriteVisualizer(u16);
static void HandleInput_PokemonSpriteVisualizer(u8);
static void ReloadPokemonSprites(struct PokemonSpriteVisualizer *data);
static void Exit_PokemonSpriteVisualizer(u8);

//Text handling functions
static void UNUSED PadString(const u8 *src, u8 *dst)
{
    u32 i;

    for (i = 0; i < 17 && src[i] != EOS; i++)
        dst[i] = src[i];

    for (; i < 17; i++)
        dst[i] = CHAR_SPACE;

    dst[i] = EOS;
}

static const struct SubmenuText sSubmenuText[] =
{
    [SUBMENU_SPECIES] =
    {
        .instructions = COMPOUND_STRING("{START_BUTTON} 异色\n{B_BUTTON} 退出  {A_BUTTON} 动画与背景$"),
        .instructionsGender = COMPOUND_STRING("{START_BUTTON} 异色 {SELECT_BUTTON} 性别\n{B_BUTTON} 退出  {A_BUTTON} 动画与背景$"),
    },

    [SUBMENU_ANIMS_BG] =
    {
        .instructions = COMPOUND_STRING("{START_BUTTON} 异色\n{B_BUTTON} 返回  {A_BUTTON} 图片坐标$"),
        .instructionsGender = COMPOUND_STRING("{START_BUTTON} 异色 {SELECT_BUTTON} 性别\n{B_BUTTON} 返回  {A_BUTTON} 图片坐标$"),
    },

    [SUBMENU_SPRITE_COORDS] =
    {
#if B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE
        .instructions = COMPOUND_STRING("{START_BUTTON} 异色\n{B_BUTTON} 返回  {A_BUTTON} 阴影坐标$"),
        .instructionsGender = COMPOUND_STRING("{START_BUTTON} 异色 {SELECT_BUTTON} 性别\n{B_BUTTON} 返回  {A_BUTTON} 阴影坐标$"),
#else
        .instructions = COMPOUND_STRING("{START_BUTTON} 异色\n{B_BUTTON} 返回  {A_BUTTON} 移动背景$"),
        .instructionsGender = COMPOUND_STRING("{START_BUTTON} 异色 {SELECT_BUTTON} 性别\n{B_BUTTON} 返回  {A_BUTTON} 移动背景$"),
#endif
        .bottomLeft = COMPOUND_STRING("背面坐标：\n正面坐标：\n正面高度："),
    },

    [SUBMENU_SHADOW_COORDS] =
    {
#if B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE
        .instructions = COMPOUND_STRING("{START_BUTTON} 异色\n{B_BUTTON} 返回  {A_BUTTON} 移动背景$"),
        .instructionsGender = COMPOUND_STRING("{START_BUTTON} 异色 {SELECT_BUTTON} 性别\n{B_BUTTON} 返回  {A_BUTTON} 移动背景$"),
#else
        .instructions = COMPOUND_STRING("$"),
        .instructionsGender = COMPOUND_STRING("$"),
#endif
        .bottomLeft = COMPOUND_STRING("横坐标：\n纵坐标：\n大小："),
    },

    [SUBMENU_MOVE_BACKGROUNDS] =
    {
        .instructions = COMPOUND_STRING("{START_BUTTON} 异色\n{B_BUTTON} 返回$"),
        .instructionsGender = COMPOUND_STRING("{START_BUTTON} 异色 {SELECT_BUTTON} 性别\n{B_BUTTON} 返回$"),
        .bottomLeft = COMPOUND_STRING("招式背景："),
    },
};

static void PrintInstructionsOnWindow(struct PokemonSpriteVisualizer *data)
{
    u8 fontId = FONT_SMALL;
    u8 x = 2;
    u16 species = data->modifyArrows.currValue;

    u8 textBottom[] = _("背面：\n正面：\n背景：$");
    u8 textBottomForms[] = _("背面：\n正面：\n背景：\n形态：$");

    u8 textL[] = _("{L_BUTTON}");
    u8 textR[] = _("{R_BUTTON}");

    //Instruction window
    FillWindowPixelBuffer(WIN_INSTRUCTIONS, 0x11);

    if (SpeciesHasGenderDifferences(species))
        AddTextPrinterParameterized(WIN_INSTRUCTIONS, fontId, sSubmenuText[data->currentSubmenu].instructionsGender, x, 0, 0, NULL);
    else
        AddTextPrinterParameterized(WIN_INSTRUCTIONS, fontId, sSubmenuText[data->currentSubmenu].instructions, x, 0, 0, NULL);

    CopyWindowToVram(WIN_INSTRUCTIONS, COPYWIN_FULL);

    //Bottom left text
    FillWindowPixelBuffer(WIN_BOTTOM_LEFT, PIXEL_FILL(0));
    if ((data->currentSubmenu == SUBMENU_SPECIES) || (data->currentSubmenu == SUBMENU_ANIMS_BG))
    {
        AddTextPrinterParameterized(WIN_BOTTOM_LEFT, fontId, textL, 30, 0, 0, NULL);
        AddTextPrinterParameterized(WIN_BOTTOM_LEFT, fontId, textR, 30, 12, 0, NULL);
        if (GetSpeciesFormTable(species) != NULL)
            AddTextPrinterParameterized(WIN_BOTTOM_LEFT, fontId, textBottomForms, 0, 0, 0, NULL);
        else
            AddTextPrinterParameterized(WIN_BOTTOM_LEFT, fontId, textBottom, 0, 0, 0, NULL);
    }
    else
        AddTextPrinterParameterized(WIN_BOTTOM_LEFT, fontId, sSubmenuText[data->currentSubmenu].bottomLeft, 0, 0, 0, NULL);
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
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

//Digit and arrow functions
#define VAL_U16     0
static void PrintDigitChars(struct PokemonSpriteVisualizer *data)
{
    s32 i;
    u16 species = data->modifyArrows.currValue;
    u8 text[MODIFY_DIGITS_MAX + POKEMON_NAME_LENGTH + 8];

    for (i = 0; i < data->modifyArrows.maxDigits; i++)
        text[i] = data->modifyArrows.charDigits[i];

    text[i++] = CHAR_SPACE;
    text[i++] = CHAR_HYPHEN;

    if (SpeciesHasGenderDifferences(species))
    {
        if (data->isFemale)
            text[i++] = CHAR_FEMALE;
        else
            text[i++] = CHAR_MALE;
        text[i++] = CHAR_HYPHEN;
    }

    text[i++] = CHAR_SPACE;
    StringCopy(&text[i], GetSpeciesName(species));

    FillWindowPixelBuffer(WIN_NAME_NUMBERS, 0x11);
    AddTextPrinterParameterized(WIN_NAME_NUMBERS, FONT_NORMAL, text, 6, 0, 0, NULL);
}

static u32 CharDigitsToValue(u8 *charDigits, u8 maxDigits)
{
    s32 i;
    u8 id = 0;
    u32 newValue = 0;
    u8 valueDigits[MODIFY_DIGITS_MAX];

    for (i = 0; i < MODIFY_DIGITS_MAX; i++)
        valueDigits[i] = charDigits[i] - CHAR_0;

    if (maxDigits >= MODIFY_DIGITS_MAX)
        newValue += valueDigits[id++] * 1000;
    if (maxDigits >= MODIFY_DIGITS_MAX - 1)
        newValue += valueDigits[id++] * 100;
    if (maxDigits >= MODIFY_DIGITS_MAX - 2)
        newValue += valueDigits[id++] * 10;
    if (maxDigits >= MODIFY_DIGITS_MAX - 3)
        newValue += valueDigits[id++];

    return newValue;
}

static void ValueToCharDigits(u8 *charDigits, u32 newValue, u8 maxDigits)
{
    s32 i;
    u8 valueDigits[MODIFY_DIGITS_MAX];
    u8 id = 0;

    if (maxDigits >= MODIFY_DIGITS_MAX)
        valueDigits[id++] = newValue / 1000;
    if (maxDigits >= MODIFY_DIGITS_MAX - 1)
        valueDigits[id++] = (newValue % 1000) / 100;
    if (maxDigits >= MODIFY_DIGITS_MAX - 2)
        valueDigits[id++] = (newValue % 100) / 10;
    if (maxDigits >= MODIFY_DIGITS_MAX - 3)
        valueDigits[id++] = newValue % 10;

    for (i = 0; i < MODIFY_DIGITS_MAX; i++)
        charDigits[i] = valueDigits[i] + CHAR_0;
}

static void SetArrowInvisibility(struct PokemonSpriteVisualizer *data)
{
    switch (data->currentSubmenu)
    {
    case SUBMENU_SPECIES:
        gSprites[data->modifyArrows.arrowSpriteId[0]].invisible = FALSE;
        gSprites[data->modifyArrows.arrowSpriteId[1]].invisible = FALSE;
        gSprites[data->optionArrows.arrowSpriteId[0]].invisible = TRUE;
        gSprites[data->yPosModifyArrows.arrowSpriteId[0]].invisible = TRUE;
        break;
    case SUBMENU_ANIMS_BG:
    case SUBMENU_MOVE_BACKGROUNDS:
        gSprites[data->modifyArrows.arrowSpriteId[0]].invisible = TRUE;
        gSprites[data->modifyArrows.arrowSpriteId[1]].invisible = TRUE;
        gSprites[data->optionArrows.arrowSpriteId[0]].invisible = FALSE;
        gSprites[data->yPosModifyArrows.arrowSpriteId[0]].invisible = TRUE;
        break;
    case SUBMENU_SPRITE_COORDS:
    case SUBMENU_SHADOW_COORDS:
        gSprites[data->modifyArrows.arrowSpriteId[0]].invisible = TRUE;
        gSprites[data->modifyArrows.arrowSpriteId[1]].invisible = TRUE;
        gSprites[data->optionArrows.arrowSpriteId[0]].invisible = TRUE;
        gSprites[data->yPosModifyArrows.arrowSpriteId[0]].invisible = FALSE;
        break;
    }
}

static void SetUpModifyArrows(struct PokemonSpriteVisualizer *data)
{
    LoadSpritePalette(&gSpritePalette_Arrow);
    data->modifyArrows.arrowSpriteId[0] = CreateSprite(&gSpriteTemplate_Arrow, MODIFY_DIGITS_ARROW_X, MODIFY_DIGITS_ARROW1_Y, 0);
    data->modifyArrows.arrowSpriteId[1] = CreateSprite(&gSpriteTemplate_Arrow, MODIFY_DIGITS_ARROW_X, MODIFY_DIGITS_ARROW2_Y, 0);
    gSprites[data->modifyArrows.arrowSpriteId[1]].animNum = 1;

    data->modifyArrows.minValue = 1;
    data->modifyArrows.maxValue = NUM_SPECIES - 1;
    data->modifyArrows.maxDigits = 4;
    data->modifyArrows.modifiedValPtr = &data->currentmonId;
    data->modifyArrows.typeOfVal = VAL_U16;
    data->modifyArrows.currValue = data->currentmonId;

    data->modifyArrows.currentDigit = 0;
    ValueToCharDigits(data->modifyArrows.charDigits, data->modifyArrows.currValue, data->modifyArrows.maxDigits);
}

static void SetUpOptionArrows(struct PokemonSpriteVisualizer *data)
{
    LoadSpritePalette(&gSpritePalette_Arrow);
    data->optionArrows.arrowSpriteId[0] = CreateSprite(&gSpriteTemplate_Arrow, OPTIONS_ARROW_1_X, OPTIONS_ARROW_Y, 0);
    gSprites[data->optionArrows.arrowSpriteId[0]].animNum = 2;

    data->optionArrows.currentDigit = 0;

    gSprites[data->optionArrows.arrowSpriteId[0]].invisible = TRUE;
}

static void SetUpYPosModifyArrows(struct PokemonSpriteVisualizer *data)
{
    LoadSpritePalette(&gSpritePalette_Arrow);
    data->yPosModifyArrows.arrowSpriteId[0] = CreateSprite(&gSpriteTemplate_Arrow, OPTIONS_ARROW_1_X, OPTIONS_ARROW_Y, 0);
    gSprites[data->yPosModifyArrows.arrowSpriteId[0]].animNum = 2;

    data->yPosModifyArrows.currentDigit = 0;

    gSprites[data->yPosModifyArrows.arrowSpriteId[0]].invisible = TRUE;
}

static bool32 TryMoveDigit(struct PokemonSpriteVisualizerModifyArrows *modArrows, bool32 moveUp)
{
    s32 i;
    u8 charDigits[MODIFY_DIGITS_MAX];
    u32 newValue;

    for (i = 0; i < MODIFY_DIGITS_MAX; i++)
        charDigits[i] = modArrows->charDigits[i];

    if (moveUp)
    {
        if (charDigits[modArrows->currentDigit] == CHAR_9)
        {
            charDigits[modArrows->currentDigit] = CHAR_0;
            for (i = modArrows->currentDigit - 1; i >= 0; i--)
            {
                if (charDigits[i] == CHAR_9)
                    charDigits[i] = CHAR_0;
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
                    charDigits[i] = CHAR_9;
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
        for (i = 0; i < MODIFY_DIGITS_MAX; i++)
             modArrows->charDigits[i] = charDigits[i];
        return TRUE;
    }
}

static void UpdateBattlerValue(struct PokemonSpriteVisualizer *data)
{
    switch (data->modifyArrows.typeOfVal)
    {
    case VAL_U16:
        *(u16*)(data->modifyArrows.modifiedValPtr) = data->modifyArrows.currValue;
        break;
    }
}

static void BattleLoadOpponentMonSpriteGfxCustom(u16 species, bool8 isFemale, bool8 isShiny, enum BattlerId battler)
{
    const u16 *palette = GetMonSpritePalFromSpecies(species, isShiny, isFemale);
    u16 paletteOffset = OBJ_PLTT_ID(battler);

    LoadPalette(palette, paletteOffset, PLTT_SIZE_4BPP);
    LoadPalette(palette, BG_PLTT_ID(8) + BG_PLTT_ID(battler), PLTT_SIZE_4BPP);
}

static void SetConstSpriteValues(struct PokemonSpriteVisualizer *data)
{
    u16 species = SanitizeSpeciesId(data->currentmonId);
    data->constSpriteValues.frontPicCoords = gSpeciesInfo[species].frontPicYOffset;
    data->constSpriteValues.frontElevation = gSpeciesInfo[species].enemyMonElevation;
    data->constSpriteValues.backPicCoords = gSpeciesInfo[species].backPicYOffset;
}

static void ResetOffsetSpriteValues(struct PokemonSpriteVisualizer *data)
{
    data->offsetsSpriteValues.offset_back_picCoords = 0;
    data->offsetsSpriteValues.offset_front_picCoords = 0;
    data->offsetsSpriteValues.offset_front_elevation = 0;
}

static void ResetShadowSettings(struct PokemonSpriteVisualizer *data)
{
    if (B_ENEMY_MON_SHADOW_STYLE <= GEN_3 || P_GBA_STYLE_SPECIES_GFX == TRUE)
        return;
    u16 species = SanitizeSpeciesId(data->currentmonId);
    data->shadowSettings.definedX = gSpeciesInfo[species].enemyShadowXOffset;
    data->shadowSettings.definedY = gSpeciesInfo[species].enemyShadowYOffset;
    data->shadowSettings.definedSize = gSpeciesInfo[species].enemyShadowSize;

    data->shadowSettings.overrideX = data->shadowSettings.definedX;
    data->shadowSettings.overrideY = data->shadowSettings.definedY;
    data->shadowSettings.overrideSize = data->shadowSettings.definedSize;
}

static u8 GetBattlerSpriteFinal_YCustom(u16 species, s8 offset_picCoords, s8 offset_elevation)
{
    u16 offset;
    u8 y;
    species = SanitizeSpeciesId(species);

    //FrontPicCoords
    offset = gSpeciesInfo[species].frontPicYOffset + offset_picCoords;

    //Elevation
    offset -= gSpeciesInfo[species].enemyMonElevation + offset_elevation;

    //Main position
    y = offset + sBattlerCoords[0][1].y;

    if (y > DISPLAY_HEIGHT - MON_PIC_HEIGHT + 8)
        y = DISPLAY_HEIGHT - MON_PIC_HEIGHT + 8;

    return y;
}

static void UpdateShadowSpriteInvisible(struct PokemonSpriteVisualizer *data)
{
    if (B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE)
        return;

    if (data->constSpriteValues.frontElevation + data->offsetsSpriteValues.offset_front_elevation == 0)
        gSprites[data->frontShadowSpriteIdPrimary].invisible = TRUE;
    else
        gSprites[data->frontShadowSpriteIdPrimary].invisible = FALSE;
}

#define tFrontSpriteId  data[0]
#define tSpriteSide     data[1]
#define tShadowXOffset  data[2]
#define tShadowYOffset  data[3]

#define SPRITE_SIDE_LEFT    0
#define SPRITE_SIDE_RIGHT   1


static void SpriteCB_EnemyShadowCustom(struct Sprite *shadowSprite)
{
    u8 frontSpriteId = shadowSprite->tFrontSpriteId;
    struct Sprite *battlerSprite = &gSprites[frontSpriteId];

    s8 xOffset = 0, yOffset = 0;
    if (B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE)
    {
        xOffset = shadowSprite->tShadowXOffset + (shadowSprite->tSpriteSide == SPRITE_SIDE_LEFT ? -16 : 16);
        yOffset = shadowSprite->tShadowYOffset + 16;

        shadowSprite->y = battlerSprite->y + yOffset;
    }

    shadowSprite->x = battlerSprite->x + xOffset;
    shadowSprite->x2 = battlerSprite->x2;
}

static void SpriteCB_Follower(struct Sprite *sprite)
{
    if (sprite->data[3] == 0)
    {
        sprite->data[3] = 120;
        switch (sprite->animNum)
        {
        case 4:
            StartSpriteAnim(sprite, GetMoveDirectionAnimNum(DIR_NORTH));
            break;
        case 5:
            StartSpriteAnim(sprite, GetMoveDirectionAnimNum(DIR_WEST));
            break;
        case 6:
            StartSpriteAnim(sprite, GetMoveDirectionAnimNum(DIR_EAST));
            break;
        default:
        case 7:
            StartSpriteAnim(sprite, GetMoveDirectionAnimNum(DIR_SOUTH));
            break;
        }
    }
    else
    {
        sprite->data[3]--;
    }
}

static void LoadAndCreateEnemyShadowSpriteCustom(struct PokemonSpriteVisualizer *data)
{
    bool8 invisible = FALSE;
    u16 species = SanitizeSpeciesId(data->currentmonId);

    if (B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE)
    {
        invisible = gSpeciesInfo[species].suppressEnemyShadow;

        LoadCompressedSpriteSheet(&gSpriteSheet_EnemyShadowsSized);
        LoadSpritePalette(&sSpritePalettes_HealthBoxHealthBar[0]);
        u8 x = sBattlerCoords[0][1].x;
        u8 y = sBattlerCoords[0][1].y;
        s8 xOffset = data->shadowSettings.overrideX;
        s8 yOffset = data->shadowSettings.overrideY;
        u8 size = data->shadowSettings.overrideSize;

        data->frontShadowSpriteIdPrimary = CreateSprite(&gSpriteTemplate_EnemyShadow, x, y, 0xC8);
        gSprites[data->frontShadowSpriteIdPrimary].tFrontSpriteId = data->frontspriteId;
        gSprites[data->frontShadowSpriteIdPrimary].tSpriteSide = SPRITE_SIDE_LEFT;
        gSprites[data->frontShadowSpriteIdPrimary].tShadowXOffset = (u8)xOffset;
        gSprites[data->frontShadowSpriteIdPrimary].tShadowYOffset = (u8)yOffset;
        gSprites[data->frontShadowSpriteIdPrimary].callback = SpriteCB_EnemyShadowCustom;
        gSprites[data->frontShadowSpriteIdPrimary].oam.priority = 0;
        gSprites[data->frontShadowSpriteIdPrimary].oam.tileNum += 8 * size;
        gSprites[data->frontShadowSpriteIdPrimary].invisible = invisible;

        data->frontShadowSpriteIdSecondary = CreateSprite(&gSpriteTemplate_EnemyShadow, x, y, 0xC8);
        gSprites[data->frontShadowSpriteIdSecondary].tFrontSpriteId = data->frontspriteId;
        gSprites[data->frontShadowSpriteIdSecondary].tSpriteSide = SPRITE_SIDE_RIGHT;
        gSprites[data->frontShadowSpriteIdSecondary].tShadowXOffset = (u8)xOffset;
        gSprites[data->frontShadowSpriteIdSecondary].tShadowYOffset = (u8)yOffset;
        gSprites[data->frontShadowSpriteIdSecondary].callback = SpriteCB_EnemyShadowCustom;
        gSprites[data->frontShadowSpriteIdSecondary].oam.priority = 0;
        gSprites[data->frontShadowSpriteIdSecondary].oam.tileNum += (8 * size) + 4;
        gSprites[data->frontShadowSpriteIdSecondary].invisible = invisible;
    }
    else
    {
        if (gSpeciesInfo[species].enemyMonElevation == 0)
            invisible = TRUE;

        LoadCompressedSpriteSheet(&gSpriteSheet_EnemyShadow);
        LoadSpritePalette(&sSpritePalettes_HealthBoxHealthBar[0]);
        u8 x = sBattlerCoords[0][1].x;
        u8 y = sBattlerCoords[0][1].y;

        data->frontShadowSpriteIdPrimary = CreateSprite(&gSpriteTemplate_EnemyShadow, x, y + 29, 0xC8);
        gSprites[data->frontShadowSpriteIdPrimary].data[0] = data->frontspriteId;

        gSprites[data->frontShadowSpriteIdPrimary].callback = SpriteCB_EnemyShadowCustom;
        gSprites[data->frontShadowSpriteIdPrimary].oam.priority = 0;
        gSprites[data->frontShadowSpriteIdPrimary].invisible = invisible;
    }
}

//Battle background functions
static void LoadBattleBg(enum BattleEnvironments battleEnvironment)
{
    DecompressDataWithHeaderVram(gBattleEnvironmentInfo[battleEnvironment].background.tileset, (void *)(BG_CHAR_ADDR(BACKGROUND_3_CHAR_BASE)));
    DecompressDataWithHeaderVram(gBattleEnvironmentInfo[battleEnvironment].background.tilemap, (void *)(BG_SCREEN_ADDR(BACKGROUND_3_MAP_BASE)));
    LoadPalette(gBattleEnvironmentInfo[battleEnvironment].palette, BG_PLTT_ID(2), 3 * PLTT_SIZE_4BPP);
}

static void PrintBattleBgName(u8 battleEnvironment)
{
    u8 fontId = FONT_SMALL;
    FillWindowPixelRect(WIN_BOTTOM_RIGHT, PIXEL_FILL(0), 0, 24, 80, gFonts[fontId].maxLetterHeight);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, gBattleEnvironmentInfo[battleEnvironment].name, 0, 24, 0, NULL);
}

static void UpdateBattleBg(u8 taskId, bool8 increment)
{
    struct PokemonSpriteVisualizer *data = GetStructPtr(taskId);

    if (increment) {
        data->battleEnvironment = (data->battleEnvironment + 1) % (BATTLE_ENVIRONMENT_RAYQUAZA + 1); // Can use BATTLE_ENVIRONMENT_COUNT once the remaining environments have sprites
    }
    else
    {
        if (data->battleEnvironment == BATTLE_ENVIRONMENT_GRASS)
            data->battleEnvironment = BATTLE_ENVIRONMENT_RAYQUAZA;
        else
            data->battleEnvironment -= 1;
    }

    PrintBattleBgName(data->battleEnvironment);
    LoadBattleBg(data->battleEnvironment);
}

//Move background functions
static void LoadMoveBackground(u8 moveBackground)
{
    DecompressDataWithHeaderVram(gBattleAnimBackgroundTable[moveBackground].tilemap, (void *)BG_SCREEN_ADDR(BACKGROUND_3_MAP_BASE));
    DecompressDataWithHeaderVram(gBattleAnimBackgroundTable[moveBackground].image, (void *)BG_CHAR_ADDR(BACKGROUND_3_CHAR_BASE));
    LoadPalette(gBattleAnimBackgroundTable[moveBackground].palette, BG_PLTT_ID(2), PLTT_SIZE_4BPP);
    //Fill text area with white to avoid overlap with backgrounds
    CpuFill32(0x11111111, (void *)(BG_CHAR_ADDR(BACKGROUND_1_CHAR_BASE) + TILE_OFFSET_4BPP(1)), TILE_SIZE_4BPP);
    CpuFill32(0xF001F001, (void *)(BG_SCREEN_ADDR(BACKGROUND_1_MAP_BASE) + sizeof(u16) * 32 * TEXT_AREA_Y), sizeof(u16) * 32 * TEXT_AREA_HEIGHT);
}

static void PrintMoveBackgroundName(u8 moveBackground)
{
    FillWindowPixelBuffer(WIN_BOTTOM_RIGHT, PIXEL_FILL(0));
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, FONT_SMALL, gMoveBackgroundNames[moveBackground], 0, 0, 0, NULL);
}

static void UpdateMoveBackground(u8 taskId, bool8 increment)
{
    struct PokemonSpriteVisualizer *data = GetStructPtr(taskId);

    if (increment)
    {
        data->moveBackground = (data->moveBackground + 1) % BG_COUNT;
        if (data->moveBackground == BG_NONE)
            data->moveBackground = BG_DARK;
    }
    else
    {
        data->moveBackground -= 1;
        if (data->moveBackground == BG_NONE)
            data->moveBackground = BG_SWAMP;
    }

    PrintMoveBackgroundName(data->moveBackground);
    LoadMoveBackground(data->moveBackground);
}

static void DrawFollowerSprite(struct PokemonSpriteVisualizer *data)
{
    if (!OW_POKEMON_OBJECT_EVENTS)
        return;

    u16 species = SanitizeSpeciesId(data->currentmonId);
    u16 graphicsId = species + OBJ_EVENT_MON;
    if (data->isShiny)
        graphicsId += OBJ_EVENT_MON_SHINY;
    if (data->isFemale)
        graphicsId += OBJ_EVENT_MON_FEMALE;
    data->followerspriteId = CreateObjectGraphicsSprite(graphicsId,
                                                        SpriteCB_Follower,
                                                        VISUALIZER_FOLLOWER_X,
                                                        VISUALIZER_FOLLOWER_Y,
                                                        0);
    gSprites[data->followerspriteId].oam.priority = 0;

    const struct ObjectEventGraphicsInfo *graphicsInfo = SpeciesToGraphicsInfo(species, data->isShiny, data->isFemale);
    gSprites[data->followerspriteId].oam.shape = graphicsInfo->oam->shape;
    gSprites[data->followerspriteId].oam.size = graphicsInfo->oam->size;
    gSprites[data->followerspriteId].images = graphicsInfo->images;
    gSprites[data->followerspriteId].anims = graphicsInfo->anims;
    gSprites[data->followerspriteId].subspriteTables = graphicsInfo->subspriteTables;
}

// *******************************
// Main functions
static void UpdateMonAnimNames(u8 taskId)
{
    struct PokemonSpriteVisualizer *data = GetStructPtr(taskId);
    u8 frontAnim = data->animIdFront;
    u8 backAnim = data->animIdBack;
    u8 text[34];
    u8 fontId = FONT_SMALL;
    u8 textNum[4];

    FillWindowPixelBuffer(WIN_BOTTOM_RIGHT, PIXEL_FILL(0));

    //Back
    StringCopy(text, gBackAnimNames[backAnim]);
    ConvertIntToDecimalStringN(textNum, backAnim, STR_CONV_MODE_LEADING_ZEROS, 3);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, textNum, 0, 0, 0, NULL);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, text, 18, 0, 0, NULL);
    //Front
    StringCopy(text, gFrontAnimNames[frontAnim]);
    ConvertIntToDecimalStringN(textNum, frontAnim, STR_CONV_MODE_LEADING_ZEROS, 3);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, textNum, 0, 12, 0, NULL);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, text, 18, 12, 0, NULL);

    PrintBattleBgName(data->battleEnvironment);
}

static void UpdateYPosOffsetText(struct PokemonSpriteVisualizer *data)
{
    u8 text[34];
    u8 fontId = FONT_SMALL;
    u8 textConst[] = _("原数值：");
    u8 textNew[] = _("新数值：");
    u8 x_const_val = 50;
    u8 x_new_text = 70;
    u8 x_new_val = 110;
    u8 y = 0;

    u8 backPicCoords    = data->constSpriteValues.backPicCoords;
    u8 frontPicCoords   = data->constSpriteValues.frontPicCoords;
    u8 frontElevation   = data->constSpriteValues.frontElevation;

    s8 offset_back_picCoords    = data->offsetsSpriteValues.offset_back_picCoords;
    s8 offset_front_picCoords   = data->offsetsSpriteValues.offset_front_picCoords;
    s8 offset_front_elevation   = data->offsetsSpriteValues.offset_front_elevation;

    u8 newBackPicCoords    = backPicCoords   +  offset_back_picCoords;
    u8 newFrontPicCoords   = frontPicCoords  +  offset_front_picCoords;
    u8 newFrontElevation   = frontElevation  +  offset_front_elevation;

    FillWindowPixelBuffer(WIN_BOTTOM_RIGHT, PIXEL_FILL(0));

    //Back
    y = 0;
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, textConst, 0, y, 0, NULL);
    ConvertIntToDecimalStringN(text, backPicCoords , STR_CONV_MODE_LEFT_ALIGN, 2);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, text, x_const_val, y, 0, NULL);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, textNew, x_new_text, y, 0, NULL);
    ConvertIntToDecimalStringN(text, newBackPicCoords , STR_CONV_MODE_LEFT_ALIGN, 2);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, text, x_new_val, y, 0, NULL);
    //Front picCoords
    y = 12;
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, textConst, 0, y, 0, NULL);
    ConvertIntToDecimalStringN(text, frontPicCoords , STR_CONV_MODE_LEFT_ALIGN, 2);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, text, x_const_val, y, 0, NULL);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, textNew, x_new_text, y, 0, NULL);
    ConvertIntToDecimalStringN(text, newFrontPicCoords , STR_CONV_MODE_LEFT_ALIGN, 2);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, text, x_new_val, y, 0, NULL);
    //Front elevation
    y = 24;
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, textConst, 0, y, 0, NULL);
    ConvertIntToDecimalStringN(text, frontElevation , STR_CONV_MODE_LEFT_ALIGN, 2);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, text, x_const_val, y, 0, NULL);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, textNew, x_new_text, y, 0, NULL);
    ConvertIntToDecimalStringN(text, newFrontElevation , STR_CONV_MODE_LEFT_ALIGN, 2);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, text, x_new_val, y, 0, NULL);
}

#define ABS(val)    (val < 0 ? val * -1 : val)
#define ITOA_SIGNED(buf, val)                                                       \
{                                                                                   \
    buf[0] = val < 0 ? CHAR_HYPHEN : CHAR_SPACER;                                   \
    ConvertIntToDecimalStringN(&text[1], ABS(val), STR_CONV_MODE_LEFT_ALIGN, 2);    \
}

static void UpdateShadowSettingsText(struct PokemonSpriteVisualizer *data)
{
    if (B_ENEMY_MON_SHADOW_STYLE <= GEN_3 || P_GBA_STYLE_SPECIES_GFX == TRUE)
        return;

    u8 text[16];
    u8 fontId = FONT_SMALL;
    u8 textConst[] = _("原数值：");
    u8 textNew[] = _("新数值：");
    u8 x_const_val = 50;
    u8 x_new_text = 70;
    u8 x_new_val = 110;
    u8 y = 0;

    FillWindowPixelBuffer(WIN_BOTTOM_RIGHT, PIXEL_FILL(0));

    // X offset
    y = 0;
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, textConst, 0, y, 0, NULL);
    ITOA_SIGNED(text, data->shadowSettings.definedX);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, text, x_const_val, y, 0, NULL);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, textNew, x_new_text, y, 0, NULL);
    ITOA_SIGNED(text, data->shadowSettings.overrideX);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, text, x_new_val, y, 0, NULL);

    // Y offset
    y = 12;
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, textConst, 0, y, 0, NULL);
    ITOA_SIGNED(text, data->shadowSettings.definedY);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, text, x_const_val, y, 0, NULL);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, textNew, x_new_text, y, 0, NULL);
    ITOA_SIGNED(text, data->shadowSettings.overrideY);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, text, x_new_val, y, 0, NULL);

    // Shadow Size
    y = 24;
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, textConst, 0, y, 0, NULL);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, sShadowSizeLabels[data->shadowSettings.definedSize], x_const_val, y, 0, NULL);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, textNew, x_new_text, y, 0, NULL);
    AddTextPrinterParameterized(WIN_BOTTOM_RIGHT, fontId, sShadowSizeLabels[data->shadowSettings.overrideSize], x_new_val, y, 0, NULL);
}

static void ResetPokemonSpriteVisualizerWindows(void)
{
    u8 i;

    FreeAllWindowBuffers();
    InitWindows(sPokemonSpriteVisualizerWindowTemplate);

    for (i = 0; i < WIN_END + 1; i++)
    {
        FillWindowPixelBuffer(i, PIXEL_FILL(0));
        PutWindowTilemap(i);
        CopyWindowToVram(i, COPYWIN_FULL);
    }
}

#define MALE_PERSONALITY 0xFE
#define FEMALE_PERSONALITY 0X0

void CB2_Pokemon_Sprite_Visualizer(void)
{
    u8 taskId;
    const u16 *palette;
    struct PokemonSpriteVisualizer *data;
    u16 species;
    s16 offset_y;
    u8 front_x = sBattlerCoords[0][1].x;
    u8 front_y;

    switch (gMain.state)
    {
    case 0:
    default:
        SetVBlankCallback(NULL);
        FreeMonSpritesGfx();
        ResetBGs_PokemonSpriteVisualizer(0);
        DmaFillLarge16(3, 0, (u8 *)VRAM, VRAM_SIZE, 0x1000)
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        gMain.state = 1;
        break;
    case 1:
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        ResetPaletteFade();
        FreeAllSpritePalettes();
        gReservedSpritePaletteCount = 8;
        ResetAllPicSprites();
        BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
        LoadPalette(GetTextWindowPalette(0), BG_PLTT_ID(15), 2 * PLTT_SIZE_4BPP);

        FillBgTilemapBufferRect(0, 0, 0, 0, 32, 20, 15);
        InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
        LoadBattleBg(BATTLE_ENVIRONMENT_GRASS);

        gMain.state++;
        break;
    case 2:
        ResetPokemonSpriteVisualizerWindows();
        gMain.state++;
        break;
    case 3:
        AllocateMonSpritesGfx();

        LoadPalette(sBgColor, BG_PLTT_ID(0), 2);
        LoadMonIconPalette(SPECIES_BULBASAUR);

        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        ShowBg(3);

        //input task handler
        taskId = CreateTask(HandleInput_PokemonSpriteVisualizer, 0);

        data = AllocZeroed(sizeof(struct PokemonSpriteVisualizer));
        SetStructPtr(taskId, data);

        data->currentmonId = SPECIES_BULBASAUR;
        species = SanitizeSpeciesId(data->currentmonId);

        //Print instructions
        PrintInstructionsOnWindow(data);

        //Palettes
        palette = GetMonSpritePalFromSpecies(species, data->isShiny, data->isFemale);
        LoadSpritePaletteWithTag(palette, species);
        //Front
        HandleLoadSpecialPokePic(TRUE, gMonSpritesGfxPtr->spritesGfx[1], species, (data->isFemale ? FEMALE_PERSONALITY : MALE_PERSONALITY));
        BattleLoadOpponentMonSpriteGfxCustom(species, data->isFemale, data->isShiny, 1);
        SetMultiuseSpriteTemplateToPokemon(species, 1);
        gMultiuseSpriteTemplate.paletteTag = species;
        front_y = GetBattlerSpriteFinal_YCustom(species, 0, 0);
        data->frontspriteId = CreateSprite(&gMultiuseSpriteTemplate, front_x, front_y, 0);
        gSprites[data->frontspriteId].oam.paletteNum = 1;
        gSprites[data->frontspriteId].callback = SpriteCallbackDummy;
        gSprites[data->frontspriteId].oam.priority = 0;
        //Front Shadow
        LoadAndCreateEnemyShadowSpriteCustom(data);

        //Back
        HandleLoadSpecialPokePic(FALSE, gMonSpritesGfxPtr->spritesGfx[2], species, (data->isFemale ? FEMALE_PERSONALITY : MALE_PERSONALITY));
        BattleLoadOpponentMonSpriteGfxCustom(species, data->isFemale, data->isShiny, 5);
        SetMultiuseSpriteTemplateToPokemon(species, 2);
        offset_y = gSpeciesInfo[species].backPicYOffset;
        data->backspriteId = CreateSprite(&gMultiuseSpriteTemplate, VISUALIZER_MON_BACK_X, VISUALIZER_MON_BACK_Y + offset_y, 0);
        gSprites[data->backspriteId].oam.paletteNum = 5;
        gSprites[data->backspriteId].callback = SpriteCallbackDummy;
        gSprites[data->backspriteId].oam.priority = 0;

        //Icon Sprite
        data->iconspriteId = CreateMonIcon(species, SpriteCB_MonIcon, VISUALIZER_ICON_X, VISUALIZER_ICON_Y, 4, (data->isFemale ? FEMALE_PERSONALITY : MALE_PERSONALITY));
        gSprites[data->iconspriteId].oam.priority = 0;

        //Follower Sprite
        DrawFollowerSprite(data);

        //Modify Arrows
        SetUpModifyArrows(data);
        PrintDigitChars(data);

        //Option Arrow
        SetUpOptionArrows(data);

        //Modify Y Pos Arrow
        SetUpYPosModifyArrows(data);

        //Anim names
        data->animIdBack = GetSpeciesBackAnimSet(species) + 1;
        data->animIdFront = gSpeciesInfo[species].frontAnimId;
        UpdateMonAnimNames(taskId);

        //Footprint
        DrawFootprint(WIN_FOOTPRINT, species);
        CopyWindowToVram(WIN_FOOTPRINT, COPYWIN_GFX);

        gMain.state++;
        break;
    case 4:
        EnableInterrupts(1);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(CB2_PokemonSpriteVisualizerRunner);
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, 0xFFFF, 0x80);
        break;
    }
}

static void CB2_PokemonSpriteVisualizerRunner(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void ResetBGs_PokemonSpriteVisualizer(u16 a)
{
    if (!(a & DISPCNT_BG0_ON))
    {
        ClearGpuRegBits(0, DISPCNT_BG0_ON);
        SetGpuReg(REG_OFFSET_BG0CNT, 0);
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    }
    if (!(a & DISPCNT_BG1_ON))
    {
        ClearGpuRegBits(0, DISPCNT_BG1_ON);
        SetGpuReg(REG_OFFSET_BG1CNT, 0);
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    }
    if (!(a & DISPCNT_BG2_ON))
    {
        ClearGpuRegBits(0, DISPCNT_BG2_ON);
        SetGpuReg(REG_OFFSET_BG2CNT, 0);
        SetGpuReg(REG_OFFSET_BG2HOFS, 0);
        SetGpuReg(REG_OFFSET_BG2VOFS, 0);
    }
    if (!(a & DISPCNT_BG3_ON))
    {
        ClearGpuRegBits(0, DISPCNT_BG3_ON);
        SetGpuReg(REG_OFFSET_BG3CNT, 0);
        SetGpuReg(REG_OFFSET_BG3HOFS, 0);
        SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    }
    if (!(a & DISPCNT_OBJ_ON))
    {
        ClearGpuRegBits(0, DISPCNT_OBJ_ON);
        ResetSpriteData();
        FreeAllSpritePalettes();
        gReservedSpritePaletteCount = 8;
    }
}

static void ApplyOffsetSpriteValues(struct PokemonSpriteVisualizer *data)
{
    u16 species = SanitizeSpeciesId(data->currentmonId);
    //Back
    gSprites[data->backspriteId].y = VISUALIZER_MON_BACK_Y + gSpeciesInfo[species].backPicYOffset + data->offsetsSpriteValues.offset_back_picCoords;
    //Front
    gSprites[data->frontspriteId].y = GetBattlerSpriteFinal_YCustom(species, data->offsetsSpriteValues.offset_front_picCoords, data->offsetsSpriteValues.offset_front_elevation);

    if (data->currentSubmenu == SUBMENU_SPRITE_COORDS)
        UpdateShadowSpriteInvisible(data);
}

static void UpdateSubmenuOneOptionValue(u8 taskId, bool8 increment)
{
    struct PokemonSpriteVisualizer *data = GetStructPtr(taskId);
    u16 species = SanitizeSpeciesId(data->currentmonId);
    u8 option = data->submenuYpos[1];

    switch (option)
    {
    case 0:
        if (increment)
        {
            if (data->animIdBack >= BACK_ANIM_SHAKE_GLOW_BLUE)
                data->animIdBack = 1;
            else
                data->animIdBack += 1;
        }
        else
        {
            if (data->animIdBack <= 1)
                data->animIdBack = BACK_ANIM_SHAKE_GLOW_BLUE;
            else
                data->animIdBack -= 1;
        }
        UpdateMonAnimNames(taskId);
        break;
    case 1:
        if (increment)
            data->animIdFront = (data->animIdFront + 1) % ANIM_COUNT;
        else
        {
            if (data->animIdFront == ANIM_V_SQUISH_AND_BOUNCE)
                data->animIdFront = ANIM_SHAKE_GLOW_PURPLE_SLOW;
            else
                data->animIdFront -= 1;
        }
        UpdateMonAnimNames(taskId);
        break;
    case 2:
        UpdateBattleBg(taskId, increment);
        break;
    case 3:
        if (GetSpeciesFormTable(species) != NULL)
        {
            struct PokemonSpriteVisualizerModifyArrows *modArrows = &data->modifyArrows;
            u8 formId = GetFormIdFromFormSpeciesId(species);
            const u16 *formTable = GetSpeciesFormTable(species);
            if (increment)
            {
                if (formTable[formId + 1] != FORM_SPECIES_END)
                    modArrows->currValue = GetFormSpeciesId(species, formId + 1);
                else
                    modArrows->currValue = formTable[0];
            }
            else
            {
                if (formTable[formId] == formTable[0])
                {
                    u8 lastForm;
                    for (lastForm = 0; formTable[lastForm] != FORM_SPECIES_END; lastForm++)
                    {
                        if (formTable[lastForm + 1] == FORM_SPECIES_END)
                            break;
                    }
                    modArrows->currValue = formTable[lastForm];
                }
                else
                    modArrows->currValue = GetFormSpeciesId(species, formId - 1);
            }
            data->animIdBack = GetSpeciesBackAnimSet(modArrows->currValue) + 1;
            data->animIdFront = gSpeciesInfo[modArrows->currValue].frontAnimId;
            UpdateMonAnimNames(taskId);
            ResetOffsetSpriteValues(data);
            ResetShadowSettings(data);

            UpdateBattlerValue(data);
            ReloadPokemonSprites(data);
            VBlankIntrWait();
            PlaySE(SE_DEX_SCROLL);
        }
        break;
    default:
        break;
    }
}

static void UpdateSubmenuTwoOptionValue(u8 taskId, bool8 increment)
{
    struct PokemonSpriteVisualizer *data = GetStructPtr(taskId);
    u16 species = SanitizeSpeciesId(data->currentmonId);
    u8 option = data->submenuYpos[2];
    s8 offset;
    u8 y;

    switch (option)
    {
    case 0: //Back picCoords
        offset = data->offsetsSpriteValues.offset_back_picCoords;
        if (increment)
        {
            if (offset == MAX_Y_OFFSET)
                offset = -data->constSpriteValues.backPicCoords;
            else
                offset += 1;
        }
        else
        {
            if (offset == -data->constSpriteValues.backPicCoords)
                offset = MAX_Y_OFFSET;
            else
                offset -= 1;
        }
        data->offsetsSpriteValues.offset_back_picCoords = offset;
        gSprites[data->backspriteId].y = VISUALIZER_MON_BACK_Y + gSpeciesInfo[species].backPicYOffset + offset;
        break;
    case 1: //Front picCoords
        offset = data->offsetsSpriteValues.offset_front_picCoords;
        if (increment)
        {
            if (offset == MAX_Y_OFFSET)
                offset = -data->constSpriteValues.frontPicCoords;
            else
                offset += 1;
        }
        else
        {
            if (offset == -data->constSpriteValues.frontPicCoords)
                offset = MAX_Y_OFFSET;
            else
                offset -= 1;
        }
        data->offsetsSpriteValues.offset_front_picCoords = offset;
        y = GetBattlerSpriteFinal_YCustom(species, offset, data->offsetsSpriteValues.offset_front_elevation);
        gSprites[data->frontspriteId].y = y;
        break;
    case 2: //Front elevation
        offset = data->offsetsSpriteValues.offset_front_elevation;
        if (increment)
        {
            if (offset == MAX_Y_OFFSET)
                offset = -data->constSpriteValues.frontElevation;
            else
                offset += 1;
        }
        else
        {
            if (offset == -data->constSpriteValues.frontElevation)
                offset = MAX_Y_OFFSET;
            else
                offset -= 1;
        }
        data->offsetsSpriteValues.offset_front_elevation = offset;
        y = GetBattlerSpriteFinal_YCustom(species, data->offsetsSpriteValues.offset_front_picCoords, offset);
        gSprites[data->frontspriteId].y = y;
        UpdateShadowSpriteInvisible(data);
        break;
    }

    UpdateYPosOffsetText(data);
}

static void UpdateShadowSettingsValue(u8 taskId, bool8 increment)
{
    if (B_ENEMY_MON_SHADOW_STYLE <= GEN_3 || P_GBA_STYLE_SPECIES_GFX == TRUE)
        return;

    struct PokemonSpriteVisualizer *data = GetStructPtr(taskId);
    u8 option = data->submenuYpos[2];
    s8 *offset;
    s16 *leftTarget, *rightTarget;
    if (option == 0)
    {
        offset = &data->shadowSettings.overrideX;
        leftTarget = &gSprites[data->frontShadowSpriteIdPrimary].tShadowXOffset;
        rightTarget = &gSprites[data->frontShadowSpriteIdSecondary].tShadowXOffset;
    }
    else
    {
        offset = &data->shadowSettings.overrideY;
        leftTarget = &gSprites[data->frontShadowSpriteIdPrimary].tShadowYOffset;
        rightTarget = &gSprites[data->frontShadowSpriteIdSecondary].tShadowYOffset;
    }

    *offset = *offset + (increment ? 1 : -1);
    if (*offset > 20)
        *offset = -20;
    else if (*offset < -20)
        *offset = 20;
    UpdateShadowSettingsText(data);

    *leftTarget = (s16)*offset;
    *rightTarget = (s16)*offset;
}

static void UpdateShadowSizeValue(u8 taskId, bool8 increment)
{
    if (B_ENEMY_MON_SHADOW_STYLE <= GEN_3 || P_GBA_STYLE_SPECIES_GFX == TRUE)
        return;

    struct PokemonSpriteVisualizer *data = GetStructPtr(taskId);
    s8 update;

    if (increment)
    {
        if (data->shadowSettings.overrideSize == SHADOW_SIZE_XL_BATTLE_ONLY)
        {
            update = -data->shadowSettings.overrideSize;
            data->shadowSettings.overrideSize = SHADOW_SIZE_S;
        }
        else
        {
            update = 1;
            data->shadowSettings.overrideSize += 1;
        }
    }
    else
    {
        if (data->shadowSettings.overrideSize == SHADOW_SIZE_S)
        {
            update = SHADOW_SIZE_XL_BATTLE_ONLY;
            data->shadowSettings.overrideSize = update;
        }
        else
        {
            update = -1;
            data->shadowSettings.overrideSize -= 1;
        }
    }

    UpdateShadowSettingsText(data);
    gSprites[data->frontShadowSpriteIdPrimary].oam.tileNum += (8 * update);
    gSprites[data->frontShadowSpriteIdSecondary].oam.tileNum += (8 * update);
}

static void UpdateSubmenuFourOptionValue(u8 taskId, bool8 increment)
{
    struct PokemonSpriteVisualizer *data = GetStructPtr(taskId);

    switch (data->submenuYpos[1])
    {
    case 0:
        UpdateMoveBackground(taskId, increment);
        break;
    default:
        break;
    }
}

#define READ_PTR_FROM_TASK(taskId, dataId)              \
    (void *)(                                           \
    ((u16)(gTasks[taskId].data[dataId]) |               \
    ((u16)(gTasks[taskId].data[dataId + 1]) << 16)))

#define STORE_PTR_IN_TASK(ptr, taskId, dataId)          \
{                                                       \
    gTasks[taskId].data[dataId] = (u32)(ptr);           \
    gTasks[taskId].data[dataId + 1] = (u32)(ptr) >> 16; \
}

#define sAnimId    data[2]
#define sAnimDelay data[3]

static void Task_AnimateAfterDelay(u8 taskId)
{
    if (--gTasks[taskId].sAnimDelay == 0)
    {
        LaunchAnimationTaskForFrontSprite(READ_PTR_FROM_TASK(taskId, 0), gTasks[taskId].sAnimId);
        DestroyTask(taskId);
    }
}

static void OpenSubmenu(u32 submenu, u8 taskId)
{
    struct PokemonSpriteVisualizer *data = GetStructPtr(taskId);
    data->currentSubmenu = submenu;
    PrintInstructionsOnWindow(data);
    SetArrowInvisibility(data);

    switch (submenu)
    {
    case SUBMENU_SPECIES:
    case SUBMENU_ANIMS_BG:
        break;
    case SUBMENU_SPRITE_COORDS:
        SetConstSpriteValues(data);
        UpdateYPosOffsetText(data);
        break;
    case SUBMENU_SHADOW_COORDS:
        UpdateShadowSettingsText(data);
        break;
    case SUBMENU_MOVE_BACKGROUNDS:
        if (data->submenuYpos[1] > 0)
            data->submenuYpos[1] = 0;

        data->optionArrows.currentDigit = data->submenuYpos[1];
        gSprites[data->optionArrows.arrowSpriteId[0]].y = OPTIONS_ARROW_Y + data->optionArrows.currentDigit * 12;
        data->moveBackground = BG_DARK;
        PrintMoveBackgroundName(data->moveBackground);
        LoadMoveBackground(data->moveBackground);
        break;
    default:
        errorf("Invalid submenu index %d", submenu);
        break;
    }
}

static void HandleInput_PokemonSpriteVisualizer(u8 taskId)
{
    struct PokemonSpriteVisualizer *data = GetStructPtr(taskId);
    u16 species = SanitizeSpeciesId(data->currentmonId);
    struct Sprite *Frontsprite = &gSprites[data->frontspriteId];
    struct Sprite *Backsprite = &gSprites[data->backspriteId];

    if (JOY_NEW(L_BUTTON)  && (Backsprite->callback == SpriteCallbackDummy))
    {
        PlayCryInternal(species, 0, 120, 10, CRY_MODE_NORMAL);
        LaunchAnimationTaskForBackSprite(Backsprite, data->animIdBack-1);
    }
    if (JOY_NEW(R_BUTTON) && (Frontsprite->callback == SpriteCallbackDummy))
    {
        PlayCryInternal(species, 0, 120, 10, CRY_MODE_NORMAL);
        if (HasTwoFramesAnimation(species))
            StartSpriteAnim(Frontsprite, 1);

        if (gSpeciesInfo[species].frontAnimDelay != 0)
        {
            // Animation has delay, start delay task
            u8 taskId = CreateTask(Task_AnimateAfterDelay, 0);
            STORE_PTR_IN_TASK(Frontsprite, taskId, 0);
            gTasks[taskId].sAnimId = data->animIdFront;
            gTasks[taskId].sAnimDelay = gSpeciesInfo[species].frontAnimDelay;
        }
        else
        {
            // No delay, start animation
            LaunchAnimationTaskForFrontSprite(Frontsprite, data->animIdFront);
        }
    }

    if (JOY_NEW(START_BUTTON))
    {
        data->isShiny = !data->isShiny;

        if (data->isShiny)
            PlaySE(SE_SHINY);

        ReloadPokemonSprites(data);
        ApplyOffsetSpriteValues(data);
    }
    if (JOY_NEW(SELECT_BUTTON) && SpeciesHasGenderDifferences(species))
    {
        data->isFemale = !data->isFemale;
        PrintDigitChars(data);
        UpdateBattlerValue(data);
        ReloadPokemonSprites(data);
        VBlankIntrWait();
        PlaySE(SE_DEX_SCROLL);
    }

    if (data->currentSubmenu == SUBMENU_SPECIES)
    {
        if (JOY_NEW(A_BUTTON))
        {
            OpenSubmenu(SUBMENU_ANIMS_BG, taskId);
        }
        else if (JOY_NEW(B_BUTTON))
        {
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
            gTasks[taskId].func = Exit_PokemonSpriteVisualizer;
            PlaySE(SE_PC_OFF);
        }
        else if (JOY_NEW(DPAD_DOWN))
        {
            if (TryMoveDigit(&data->modifyArrows, FALSE))
            {
                data->isFemale = FALSE;
                PrintDigitChars(data);
                UpdateBattlerValue(data);
                ResetShadowSettings(data);
                ReloadPokemonSprites(data);
                data->animIdBack = GetSpeciesBackAnimSet(species) + 1;
                data->animIdFront = gSpeciesInfo[species].frontAnimId;
                UpdateMonAnimNames(taskId);
                ResetOffsetSpriteValues(data);
            }
            PlaySE(SE_DEX_SCROLL);
            VBlankIntrWait();
        }
        else if (JOY_NEW(DPAD_UP))
        {
            if (TryMoveDigit(&data->modifyArrows, TRUE))
            {
                data->isFemale = FALSE;
                PrintDigitChars(data);
                UpdateBattlerValue(data);
                ResetShadowSettings(data);
                ReloadPokemonSprites(data);
                data->animIdBack = GetSpeciesBackAnimSet(species) + 1;
                data->animIdFront = gSpeciesInfo[species].frontAnimId;
                UpdateMonAnimNames(taskId);
                ResetOffsetSpriteValues(data);
            }

            PlaySE(SE_DEX_SCROLL);
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
        else if (JOY_NEW(DPAD_RIGHT))
        {
            if (data->modifyArrows.currentDigit != (data->modifyArrows.maxDigits - 1))
            {
                data->modifyArrows.currentDigit++;
                gSprites[data->modifyArrows.arrowSpriteId[0]].x2 += 6;
                gSprites[data->modifyArrows.arrowSpriteId[1]].x2 += 6;
            }
        }
    }
    else if (data->currentSubmenu == SUBMENU_ANIMS_BG)
    {
        if (JOY_NEW(A_BUTTON))
        {
            OpenSubmenu(SUBMENU_SPRITE_COORDS, taskId);

            if (data->followerspriteId != 0)
                gSprites[data->followerspriteId].invisible = TRUE;
        }
        else if (JOY_NEW(B_BUTTON))
        {
            OpenSubmenu(SUBMENU_SPECIES, taskId);
            if (data->submenuYpos[1] == 3)
            {
                data->submenuYpos[1] = 2;
                data->optionArrows.currentDigit = data->submenuYpos[1];
                gSprites[data->optionArrows.arrowSpriteId[0]].y = OPTIONS_ARROW_Y + data->optionArrows.currentDigit * 12;
            }
        }
        else if (JOY_NEW(DPAD_DOWN))
        {
            data->submenuYpos[1] += 1;
            if (data->submenuYpos[1] >= 3)
            {
                if ((GetSpeciesFormTable(species) == NULL) || (data->submenuYpos[1] >= 4))
                    data->submenuYpos[1] = 0;
            }
            data->optionArrows.currentDigit = data->submenuYpos[1];
            gSprites[data->optionArrows.arrowSpriteId[0]].y = OPTIONS_ARROW_Y + data->optionArrows.currentDigit * 12;
        }
        else if (JOY_NEW(DPAD_UP))
        {
            if (data->submenuYpos[1] == 0)
            {
                if (GetSpeciesFormTable(species) != NULL)
                    data->submenuYpos[1] = 3;
                else
                    data->submenuYpos[1] = 2;
            }
            else
                data->submenuYpos[1] -= 1;

            data->optionArrows.currentDigit = data->submenuYpos[1];
            gSprites[data->optionArrows.arrowSpriteId[0]].y = OPTIONS_ARROW_Y + data->optionArrows.currentDigit * 12;
        }
        else if (JOY_NEW(DPAD_LEFT))
        {
            UpdateSubmenuOneOptionValue(taskId, FALSE);
        }
        else if (JOY_NEW(DPAD_RIGHT))
        {
            UpdateSubmenuOneOptionValue(taskId, TRUE);
        }
    }
    else if (data->currentSubmenu == SUBMENU_SPRITE_COORDS)
    {
        if (JOY_NEW(A_BUTTON))
        {
            if (B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE)
                OpenSubmenu(SUBMENU_SHADOW_COORDS, taskId);
            else
                OpenSubmenu(SUBMENU_MOVE_BACKGROUNDS, taskId);
        }
        else if (JOY_NEW(B_BUTTON))
        {
            OpenSubmenu(SUBMENU_ANIMS_BG, taskId);
            UpdateMonAnimNames(taskId);

            if (data->followerspriteId != 0)
                gSprites[data->followerspriteId].invisible = FALSE;
        }
        else if (JOY_NEW(DPAD_DOWN))
        {
            data->submenuYpos[2] += 1;
            if (data->submenuYpos[2] >= 3)
                data->submenuYpos[2] = 0;

            data->yPosModifyArrows.currentDigit = data->submenuYpos[2];
            gSprites[data->yPosModifyArrows.arrowSpriteId[0]].y = OPTIONS_ARROW_Y + data->yPosModifyArrows.currentDigit * 12;
        }
        else if (JOY_NEW(DPAD_UP))
        {
            if (data->submenuYpos[2] == 0)
                data->submenuYpos[2] = 2;
            else
                data->submenuYpos[2] -= 1;

            data->yPosModifyArrows.currentDigit = data->submenuYpos[2];
            gSprites[data->yPosModifyArrows.arrowSpriteId[0]].y = OPTIONS_ARROW_Y + data->yPosModifyArrows.currentDigit * 12;
        }
        else if (JOY_NEW(DPAD_LEFT))
        {
            UpdateSubmenuTwoOptionValue(taskId, FALSE);
        }
        else if (JOY_NEW(DPAD_RIGHT))
        {
            UpdateSubmenuTwoOptionValue(taskId, TRUE);
        }
    }
    else if (data->currentSubmenu == SUBMENU_SHADOW_COORDS)
    {
        if (JOY_NEW(A_BUTTON))
        {
            OpenSubmenu(SUBMENU_MOVE_BACKGROUNDS, taskId);
        }
        else if (JOY_NEW(B_BUTTON))
        {
            OpenSubmenu(SUBMENU_SPRITE_COORDS, taskId);
        }
        else if (JOY_NEW(DPAD_DOWN))
        {
            data->submenuYpos[2] += 1;
            if (data->submenuYpos[2] >= 3)
                data->submenuYpos[2] = 0;

            data->yPosModifyArrows.currentDigit = data->submenuYpos[2];
            gSprites[data->yPosModifyArrows.arrowSpriteId[0]].y = OPTIONS_ARROW_Y + data->yPosModifyArrows.currentDigit * 12;
        }
        else if (JOY_NEW(DPAD_UP))
        {
            if (data->submenuYpos[2] == 0)
                data->submenuYpos[2] = 2;
            else
                data->submenuYpos[2] -= 1;

            data->yPosModifyArrows.currentDigit = data->submenuYpos[2];
            gSprites[data->yPosModifyArrows.arrowSpriteId[0]].y = OPTIONS_ARROW_Y + data->yPosModifyArrows.currentDigit * 12;
        }
        else if (JOY_NEW(DPAD_LEFT))
        {
            if (data->submenuYpos[2] < 2)
                UpdateShadowSettingsValue(taskId, FALSE);
            else
                UpdateShadowSizeValue(taskId, FALSE);
        }
        else if (JOY_NEW(DPAD_RIGHT))
        {
            if (data->submenuYpos[2] < 2)
                UpdateShadowSettingsValue(taskId, TRUE);
            else
                UpdateShadowSizeValue(taskId, TRUE);
        }
    }
    else if (data->currentSubmenu == SUBMENU_MOVE_BACKGROUNDS)
    {
        if (JOY_NEW(B_BUTTON))
        {
            if (B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE)
                OpenSubmenu(SUBMENU_SHADOW_COORDS, taskId);
            else
                OpenSubmenu(SUBMENU_SPRITE_COORDS, taskId);
            LoadBattleBg(data->battleEnvironment);
        }
        else if (JOY_NEW(DPAD_LEFT))
        {
            UpdateSubmenuFourOptionValue(taskId, FALSE);
        }
        else if (JOY_NEW(DPAD_RIGHT))
        {
            UpdateSubmenuFourOptionValue(taskId, TRUE);
        }
    }
}
#undef sDelay
#undef sAnimId

static void ReloadPokemonSprites(struct PokemonSpriteVisualizer *data)
{
    const u16 *palette;
    u16 species = SanitizeSpeciesId(data->currentmonId);
    s16 offset_y;
    u8 front_x = sBattlerCoords[0][1].x;
    u8 front_y;

    DestroySprite(&gSprites[data->frontspriteId]);
    DestroySprite(&gSprites[data->backspriteId]);
    DestroySprite(&gSprites[data->iconspriteId]);

    if (data->followerspriteId != 0)
        DestroySprite(&gSprites[data->followerspriteId]);

    DestroySprite(&gSprites[data->frontShadowSpriteIdPrimary]);
    if (B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE)
        DestroySprite(&gSprites[data->frontShadowSpriteIdSecondary]);

    FreeMonSpritesGfx();
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
    ResetAllPicSprites();
    FreeMonIconPalettes();

    AllocateMonSpritesGfx();
    LoadMonIconPalettePersonality(species, (data->isFemale ? FEMALE_PERSONALITY : MALE_PERSONALITY));

    //Update instructions
    PrintInstructionsOnWindow(data);

    //Palettes
    palette = GetMonSpritePalFromSpecies(species, data->isShiny, data->isFemale);
    LoadSpritePaletteWithTag(palette, species);
    //Front
    HandleLoadSpecialPokePic(TRUE, gMonSpritesGfxPtr->spritesGfx[1], species, (data->isFemale ? FEMALE_PERSONALITY : MALE_PERSONALITY));
    BattleLoadOpponentMonSpriteGfxCustom(species, data->isFemale, data->isShiny, 1);
    SetMultiuseSpriteTemplateToPokemon(species, 1);
    gMultiuseSpriteTemplate.paletteTag = species;
    front_y = GetBattlerSpriteFinal_YCustom(species, 0, 0);
    data->frontspriteId = CreateSprite(&gMultiuseSpriteTemplate, front_x, front_y, 0);
    gSprites[data->frontspriteId].oam.paletteNum = 1;
    gSprites[data->frontspriteId].callback = SpriteCallbackDummy;
    gSprites[data->frontspriteId].oam.priority = 0;
    //Front Shadow
    LoadAndCreateEnemyShadowSpriteCustom(data);

    //Back
    HandleLoadSpecialPokePic(FALSE, gMonSpritesGfxPtr->spritesGfx[2], species, (data->isFemale ? FEMALE_PERSONALITY : MALE_PERSONALITY));
    BattleLoadOpponentMonSpriteGfxCustom(species, data->isFemale, data->isShiny, 5);
    SetMultiuseSpriteTemplateToPokemon(species, 2);
    offset_y = gSpeciesInfo[species].backPicYOffset;
    data->backspriteId = CreateSprite(&gMultiuseSpriteTemplate, VISUALIZER_MON_BACK_X, VISUALIZER_MON_BACK_Y + offset_y, 0);
    gSprites[data->backspriteId].oam.paletteNum = 5;
    gSprites[data->backspriteId].callback = SpriteCallbackDummy;
    gSprites[data->backspriteId].oam.priority = 0;

    //Icon Sprite
    data->iconspriteId = CreateMonIcon(species, SpriteCB_MonIcon, VISUALIZER_ICON_X, VISUALIZER_ICON_Y, 4, (data->isFemale ? FEMALE_PERSONALITY : MALE_PERSONALITY));
    gSprites[data->iconspriteId].oam.priority = 0;

    //Follower Sprite
    DrawFollowerSprite(data);

    //Modify Arrows
    LoadSpritePalette(&gSpritePalette_Arrow);
    data->modifyArrows.arrowSpriteId[0] = CreateSprite(&gSpriteTemplate_Arrow, MODIFY_DIGITS_ARROW_X + (data->modifyArrows.currentDigit * 6), MODIFY_DIGITS_ARROW1_Y, 0);
    data->modifyArrows.arrowSpriteId[1] = CreateSprite(&gSpriteTemplate_Arrow, MODIFY_DIGITS_ARROW_X + (data->modifyArrows.currentDigit * 6), MODIFY_DIGITS_ARROW2_Y, 0);
    gSprites[data->modifyArrows.arrowSpriteId[1]].animNum = 1;

    //Option Arrow
    LoadSpritePalette(&gSpritePalette_Arrow);
    data->optionArrows.arrowSpriteId[0] = CreateSprite(&gSpriteTemplate_Arrow, OPTIONS_ARROW_1_X, OPTIONS_ARROW_Y + data->optionArrows.currentDigit * 12, 0);
    gSprites[data->optionArrows.arrowSpriteId[0]].animNum = 2;

    //Y Pos Modify Arrow
    LoadSpritePalette(&gSpritePalette_Arrow);
    data->yPosModifyArrows.arrowSpriteId[0] = CreateSprite(&gSpriteTemplate_Arrow, OPTIONS_ARROW_1_X, OPTIONS_ARROW_Y + data->yPosModifyArrows.currentDigit * 12, 0);
    gSprites[data->yPosModifyArrows.arrowSpriteId[0]].animNum = 2;

    //Arrow invisibility
    SetArrowInvisibility(data);

    //Footprint
    DrawFootprint(WIN_FOOTPRINT, species);
    CopyWindowToVram(WIN_FOOTPRINT, COPYWIN_GFX);
}

static void Exit_PokemonSpriteVisualizer(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        struct PokemonSpriteVisualizer *data = GetStructPtr(taskId);
        Free(data);
        FreeMonSpritesGfx();
        DestroyTask(taskId);
        SetMainCallback2(CB2_ReturnToFieldWithOpenMenu);
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, TRACKS_ALL, 0x100);
    }
}
