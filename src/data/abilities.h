const struct Ability gAbilitiesInfo[ABILITIES_COUNT] =
{
    [ABILITY_NONE] =
    {
        .name = _("-------"),
        .description = COMPOUND_STRING("没有特性"),
        .aiRating = 0,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_STENCH] =
    {
        .name = _("恶臭"),
        .description = COMPOUND_STRING("释放臭味，有时会使对手畏缩"),
        .aiRating = 1,
    },

    [ABILITY_DRIZZLE] =
    {
        .name = _("降雨"),
        .description = COMPOUND_STRING("出场时，会将天气变为下雨"),
        .aiRating = 9,
    },

    [ABILITY_SPEED_BOOST] =
    {
        .name = _("加速"),
        .description = COMPOUND_STRING("每一回合速度会变快"),
        .aiRating = 9,
    },

    [ABILITY_BATTLE_ARMOR] =
    {
        .name = _("战斗盔甲"),
        .description = COMPOUND_STRING("不会被攻击击中要害"),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_STURDY] =
    {
        .name = _("结实"),
        .description = COMPOUND_STRING("HP全满时不会被一击打倒"),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DAMP] =
    {
        .name = _("湿气"),
        .description = COMPOUND_STRING("双方无法使用爆炸类的招式"),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_LIMBER] =
    {
        .name = _("柔软"),
        .description = COMPOUND_STRING("不会变为麻痹状态"),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SAND_VEIL] =
    {
        .name = _("沙隐"),
        .description = COMPOUND_STRING("沙暴时，闪避率会提高"),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_STATIC] =
    {
        .name = _("静电"),
        .description = COMPOUND_STRING("有时会让接触的对手麻痹"),
        .aiRating = 4,
    },

    [ABILITY_VOLT_ABSORB] =
    {
        .name = _("蓄电"),
        .description = COMPOUND_STRING("受到电属性攻击时会回复"),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_WATER_ABSORB] =
    {
        .name = _("储水"),
        .description = COMPOUND_STRING("受到水属性攻击时会回复"),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_OBLIVIOUS] =
    {
        .name = _("迟钝"),
        .description = COMPOUND_STRING("不会因着迷挑衅威吓动摇"),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_CLOUD_NINE] =
    {
        .name = _("无关天气"),
        .description = COMPOUND_STRING("任何天气的影响都会消失"),
        .aiRating = 5,
    },

    [ABILITY_COMPOUND_EYES] =
    {
        .name = _("复眼"),
        .description = COMPOUND_STRING("招式的命中率会提高"),
        .aiRating = 7,
    },

    [ABILITY_INSOMNIA] =
    {
        .name = _("不眠"),
        .description = COMPOUND_STRING("不会陷入睡眠状态"),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_COLOR_CHANGE] =
    {
        .name = _("变色"),
        .description = COMPOUND_STRING("属性会变为对手招式的属性"),
        .aiRating = 2,
    },

    [ABILITY_IMMUNITY] =
    {
        .name = _("免疫"),
        .description = COMPOUND_STRING("不会变为中毒状态"),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_FLASH_FIRE] =
    {
        .name = _("引火"),
        .description = COMPOUND_STRING("受火属性攻击会强化火招式"),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SHIELD_DUST] =
    {
        .name = _("鳞粉"),
        .description = COMPOUND_STRING("不会受到招式追加效果影响"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_OWN_TEMPO] =
    {
        .name = _("我行我素"),
        .description = COMPOUND_STRING("不会被混乱或威吓"),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SUCTION_CUPS] =
    {
        .name = _("吸盘"),
        .description = COMPOUND_STRING("让替换宝可梦的招式无效"),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_INTIMIDATE] =
    {
        .name = _("威吓"),
        .description = COMPOUND_STRING("出场时降低对手的攻击"),
        .aiRating = 7,
    },

    [ABILITY_SHADOW_TAG] =
    {
        .name = _("踩影"),
        .description = COMPOUND_STRING("使对手无法逃走或替换"),
        .aiRating = 10,
    },

    [ABILITY_ROUGH_SKIN] =
    {
        .name = _("粗糙皮肤"),
        .description = COMPOUND_STRING("受到攻击时弄伤接触的对手"),
        .aiRating = 6,
    },

    [ABILITY_WONDER_GUARD] =
    {
        .name = _("神奇守护"),
        .description = COMPOUND_STRING("只有效果绝佳招式才能击中"),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_LEVITATE] =
    {
        .name = _("飘浮"),
        .description = COMPOUND_STRING("不会受地面属性招式攻击"),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EFFECT_SPORE] =
    {
        .name = _("孢子"),
        .description = COMPOUND_STRING("有时会使接触的对手异常"),
        .aiRating = 4,
    },

    [ABILITY_SYNCHRONIZE] =
    {
        .name = _("同步"),
        .description = COMPOUND_STRING("将自己异常状态传染给对手"),
        .aiRating = 4,
    },

    [ABILITY_CLEAR_BODY] =
    {
        .name = _("恒净之躯"),
        .description = COMPOUND_STRING("不会因为对手而被降低能力"),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_NATURAL_CURE] =
    {
        .name = _("自然回复"),
        .description = COMPOUND_STRING("被换下后治愈异常状态"),
        .aiRating = 7,
    },

    [ABILITY_LIGHTNING_ROD] =
    {
        .name = _("避雷针"),
        .description = COMPOUND_STRING("吸引免疫电招式并提高特攻"),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_SERENE_GRACE] =
    {
        .name = _("天恩"),
        .description = COMPOUND_STRING("招式的追加效果容易出现"),
        .aiRating = 8,
    },

    [ABILITY_SWIFT_SWIM] =
    {
        .name = _("悠游自如"),
        .description = COMPOUND_STRING("下雨天气时，速度会提高"),
        .aiRating = 6,
    },

    [ABILITY_CHLOROPHYLL] =
    {
        .name = _("叶绿素"),
        .description = COMPOUND_STRING("晴天时，速度会提高"),
        .aiRating = 6,
    },

    [ABILITY_ILLUMINATE] =
    {
        .name = _("发光"),
        .description = COMPOUND_STRING("命中率不会被降低"),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_TRACE] =
    {
        .name = _("复制"),
        .description = COMPOUND_STRING("出场时，复制对手的特性"),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_HUGE_POWER] =
    {
        .name = _("大力士"),
        .description = COMPOUND_STRING("物理攻击的威力会变为2倍"),
        .aiRating = 10,
    },

    [ABILITY_POISON_POINT] =
    {
        .name = _("毒刺"),
        .description = COMPOUND_STRING("有时会让接触到的对手中毒"),
        .aiRating = 4,
    },

    [ABILITY_INNER_FOCUS] =
    {
        .name = _("精神力"),
        .description = COMPOUND_STRING("不会畏缩或被威吓影响"),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MAGMA_ARMOR] =
    {
        .name = _("熔岩铠甲"),
        .description = COMPOUND_STRING("不会变为冰冻状态"),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_WATER_VEIL] =
    {
        .name = _("水幕"),
        .description = COMPOUND_STRING("不会变为灼伤状态"),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_MAGNET_PULL] =
    {
        .name = _("磁力"),
        .description = COMPOUND_STRING("使钢属性宝可梦无法逃走"),
        .aiRating = 9,
    },

    [ABILITY_SOUNDPROOF] =
    {
        .name = _("隔音"),
        .description = COMPOUND_STRING("不受到声音招式的影响"),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_RAIN_DISH] =
    {
        .name = _("雨盘"),
        .description = COMPOUND_STRING("下雨天气时，缓缓回复HP"),
        .aiRating = 3,
    },

    [ABILITY_SAND_STREAM] =
    {
        .name = _("扬沙"),
        .description = COMPOUND_STRING("出场时，会把天气变为沙暴"),
        .aiRating = 9,
    },

    [ABILITY_PRESSURE] =
    {
        .name = _("压迫感"),
        .description = COMPOUND_STRING("减少对手使用招式的PP"),
        .aiRating = 5,
    },

    [ABILITY_THICK_FAT] =
    {
        .name = _("厚脂肪"),
        .description = COMPOUND_STRING("使火冰属性的招式伤害减半"),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EARLY_BIRD] =
    {
        .name = _("早起"),
        .description = COMPOUND_STRING("睡眠时会提早醒来"),
        .aiRating = 4,
    },

    [ABILITY_FLAME_BODY] =
    {
        .name = _("火焰之躯"),
        .description = COMPOUND_STRING("有时会让接触的对手灼伤"),
        .aiRating = 4,
    },

    [ABILITY_RUN_AWAY] =
    {
        .name = _("逃跑"),
        .description = COMPOUND_STRING("野生宝可梦面前一定能逃走"),
        .aiRating = 0,
    },

    [ABILITY_KEEN_EYE] =
    {
        .name = _("锐利目光"),
        .description = COMPOUND_STRING("命中率不会被降低"),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_HYPER_CUTTER] =
    {
        .name = _("怪力钳"),
        .description = COMPOUND_STRING("不会被对手降低攻击"),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PICKUP] =
    {
        .name = _("捡拾"),
        .description = COMPOUND_STRING("有时会捡来对手用过的道具"),
        .aiRating = 1,
    },

    [ABILITY_TRUANT] =
    {
        .name = _("懒惰"),
        .description = COMPOUND_STRING("每隔一回合就会休息"),
        .aiRating = -2,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_HUSTLE] =
    {
        .name = _("活力"),
        .description = COMPOUND_STRING("攻击变高，但命中率会降低"),
        .aiRating = 7,
    },

    [ABILITY_CUTE_CHARM] =
    {
        .name = _("迷人之躯"),
        .description = COMPOUND_STRING("有时会让接触到的对手着迷"),
        .aiRating = 2,
    },

    [ABILITY_PLUS] =
    {
        .name = _("正电"),
        .description = COMPOUND_STRING("场上有同类特性会提高特攻"),
        .aiRating = 0,
    },

    [ABILITY_MINUS] =
    {
        .name = _("负电"),
        .description = COMPOUND_STRING("场上有同类特性会提高特攻"),
        .aiRating = 0,
    },

    [ABILITY_FORECAST] =
    {
        .name = _("阴晴不定"),
        .description = COMPOUND_STRING("受天气影响改变形态"),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_STICKY_HOLD] =
    {
        .name = _("黏着"),
        .description = COMPOUND_STRING("道具不会被对手夺走"),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SHED_SKIN] =
    {
        .name = _("蜕皮"),
        .description = COMPOUND_STRING("有时会治愈异常状态"),
        .aiRating = 7,
    },

    [ABILITY_GUTS] =
    {
        .name = _("毅力"),
        .description = COMPOUND_STRING("异常状态时攻击会提高"),
        .aiRating = 6,
    },

    [ABILITY_MARVEL_SCALE] =
    {
        .name = _("神奇鳞片"),
        .description = COMPOUND_STRING("异常状态时防御会提高"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_LIQUID_OOZE] =
    {
        .name = _("污泥浆"),
        .description = COMPOUND_STRING("吸收污泥的对手会减少HP"),
        .aiRating = 3,
    },

    [ABILITY_OVERGROW] =
    {
        .name = _("茂盛"),
        .description = COMPOUND_STRING("HP低时强化草属性招式"),
        .aiRating = 5,
    },

    [ABILITY_BLAZE] =
    {
        .name = _("猛火"),
        .description = COMPOUND_STRING("HP低时强化火属性招式"),
        .aiRating = 5,
    },

    [ABILITY_TORRENT] =
    {
        .name = _("激流"),
        .description = COMPOUND_STRING("HP低时强化水属性招式"),
        .aiRating = 5,
    },

    [ABILITY_SWARM] =
    {
        .name = _("虫之预感"),
        .description = COMPOUND_STRING("HP低时强化虫属性招式"),
        .aiRating = 5,
    },

    [ABILITY_ROCK_HEAD] =
    {
        .name = _("坚硬脑袋"),
        .description = COMPOUND_STRING("不会受反作用力减少HP"),
        .aiRating = 5,
    },

    [ABILITY_DROUGHT] =
    {
        .name = _("日照"),
        .description = COMPOUND_STRING("出场时，会将天气变为晴朗"),
        .aiRating = 9,
    },

    [ABILITY_ARENA_TRAP] =
    {
        .name = _("沙穴"),
        .description = COMPOUND_STRING("在战斗中让对手无法逃走"),
        .aiRating = 9,
    },

    [ABILITY_VITAL_SPIRIT] =
    {
        .name = _("干劲"),
        .description = COMPOUND_STRING("不会变为睡眠状态"),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_WHITE_SMOKE] =
    {
        .name = _("白色烟雾"),
        .description = COMPOUND_STRING("不会被对手降低能力"),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_PURE_POWER] =
    {
        .name = _("瑜伽之力"),
        .description = COMPOUND_STRING("物理攻击的威力会变为2倍"),
        .aiRating = 10,
    },

    [ABILITY_SHELL_ARMOR] =
    {
        .name = _("硬壳盔甲"),
        .description = COMPOUND_STRING("对手的攻击不会击中要害"),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_AIR_LOCK] =
    {
        .name = _("气闸"),
        .description = COMPOUND_STRING("所有天气的影响都会消失"),
        .aiRating = 5,
    },

    [ABILITY_TANGLED_FEET] =
    {
        .name = _("蹒跚"),
        .description = COMPOUND_STRING("在混乱状态时闪避率会提高"),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MOTOR_DRIVE] =
    {
        .name = _("电气引擎"),
        .description = COMPOUND_STRING("免疫电属性攻击并提高速度"),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_RIVALRY] =
    {
        .name = _("斗争心"),
        .description = COMPOUND_STRING("对同性别对手变强反之变弱"),
        .aiRating = 1,
    },

    [ABILITY_STEADFAST] =
    {
        .name = _("不屈之心"),
        .description = COMPOUND_STRING("每次畏缩时速度会提高"),
        .aiRating = 2,
    },

    [ABILITY_SNOW_CLOAK] =
    {
        .name = _("雪隐"),
        .description = COMPOUND_STRING("下雪天气时，闪避率会提高"),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_GLUTTONY] =
    {
        .name = _("贪吃鬼"),
        .description = COMPOUND_STRING("会在一半HP时提前吃树果"),
        .aiRating = 3,
    },

    [ABILITY_ANGER_POINT] =
    {
        .name = _("愤怒穴位"),
        .description = COMPOUND_STRING("要害被击中时攻击变为最大"),
        .aiRating = 4,
    },

    [ABILITY_UNBURDEN] =
    {
        .name = _("轻装"),
        .description = COMPOUND_STRING("失去道具时速度会提高"),
        .aiRating = 7,
    },

    [ABILITY_HEATPROOF] =
    {
        .name = _("耐热"),
        .description = COMPOUND_STRING("受火属性招式的伤害减半"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SIMPLE] =
    {
        .name = _("单纯"),
        .description = COMPOUND_STRING("能力变化会变为平时的2倍"),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_DRY_SKIN] =
    {
        .name = _("干燥皮肤"),
        .description = COMPOUND_STRING("雨天回复HP，晴天减少"),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DOWNLOAD] =
    {
        .name = _("下载"),
        .description = COMPOUND_STRING("根据情况提升攻击或特攻"),
        .aiRating = 7,
    },

    [ABILITY_IRON_FIST] =
    {
        .name = _("铁拳"),
        .description = COMPOUND_STRING("使用拳类招式的威力会提高"),
        .aiRating = 6,
    },

    [ABILITY_POISON_HEAL] =
    {
        .name = _("毒疗"),
        .description = COMPOUND_STRING("中毒时反而会回复HP"),
        .aiRating = 8,
    },

    [ABILITY_ADAPTABILITY] =
    {
        .name = _("适应力"),
        .description = COMPOUND_STRING("强化自身同属性的招式"),
        .aiRating = 8,
    },

    [ABILITY_SKILL_LINK] =
    {
        .name = _("连续攻击"),
        .description = COMPOUND_STRING("连续招式总能使出最高次数"),
        .aiRating = 7,
    },

    [ABILITY_HYDRATION] =
    {
        .name = _("湿润之躯"),
        .description = COMPOUND_STRING("下雨天气时治愈异常状态"),
        .aiRating = 4,
    },

    [ABILITY_SOLAR_POWER] =
    {
        .name = _("太阳之力"),
        .description = COMPOUND_STRING("晴天时减少HP提高特攻"),
        .aiRating = 3,
    },

    [ABILITY_QUICK_FEET] =
    {
        .name = _("飞毛腿"),
        .description = COMPOUND_STRING("变为异常状态时速度会提高"),
        .aiRating = 5,
    },

    [ABILITY_NORMALIZE] =
    {
        .name = _("一般皮肤"),
        .description = COMPOUND_STRING("招式变为一般属性并强化"),
        .aiRating = -1,
    },

    [ABILITY_SNIPER] =
    {
        .name = _("狙击手"),
        .description = COMPOUND_STRING("击中要害时，威力提升"),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_GUARD] =
    {
        .name = _("魔法防守"),
        .description = COMPOUND_STRING("不会受到攻击以外的伤害"),
        .aiRating = 9,
    },

    [ABILITY_NO_GUARD] =
    {
        .name = _("无防守"),
        .description = COMPOUND_STRING("双方的招式都必定会击中"),
        .aiRating = 8,
    },

    [ABILITY_STALL] =
    {
        .name = _("慢出"),
        .description = COMPOUND_STRING("使出招式的顺序必定为最后"),
        .aiRating = -1,
    },

    [ABILITY_TECHNICIAN] =
    {
        .name = _("技术高手"),
        .description = COMPOUND_STRING("强化低威力的招式"),
        .aiRating = 8,
    },

    [ABILITY_LEAF_GUARD] =
    {
        .name = _("叶子防守"),
        .description = COMPOUND_STRING("晴天时不会变为异常状态"),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_KLUTZ] =
    {
        .name = _("笨拙"),
        .description = COMPOUND_STRING("无法使用持有的道具"),
        .aiRating = -1,
    },

    [ABILITY_MOLD_BREAKER] =
    {
        .name = _("破格"),
        .description = COMPOUND_STRING("使用招式不受对手特性影响"),
        .aiRating = 7,
    },

    [ABILITY_SUPER_LUCK] =
    {
        .name = _("超幸运"),
        .description = COMPOUND_STRING("攻击容易击中对手的要害"),
        .aiRating = 3,
    },

    [ABILITY_AFTERMATH] =
    {
        .name = _("引爆"),
        .description = COMPOUND_STRING("昏厥时伤害接触的对手"),
        .aiRating = 5,
    },

    [ABILITY_ANTICIPATION] =
    {
        .name = _("危险预知"),
        .description = COMPOUND_STRING("可以察觉到对手的危险招式"),
        .aiRating = 2,
    },

    [ABILITY_FOREWARN] =
    {
        .name = _("预知梦"),
        .description = COMPOUND_STRING("出场时，读取1个对手的招式"),
        .aiRating = 2,
    },

    [ABILITY_UNAWARE] =
    {
        .name = _("纯朴"),
        .description = COMPOUND_STRING("可无视对手能力变化攻击"),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_TINTED_LENS] =
    {
        .name = _("有色眼镜"),
        .description = COMPOUND_STRING("提升效果不好的招式威力"),
        .aiRating = 7,
    },

    [ABILITY_FILTER] =
    {
        .name = _("过滤"),
        .description = COMPOUND_STRING("减轻效果绝佳的攻击伤害"),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SLOW_START] =
    {
        .name = _("慢启动"),
        .description = COMPOUND_STRING("在5回合内攻击和速度减半"),
        .aiRating = -2,
    },

    [ABILITY_SCRAPPY] =
    {
        .name = _("胆量"),
        .description = COMPOUND_STRING("招式可击中幽灵并无视威吓"),
        .aiRating = 6,
    },

    [ABILITY_STORM_DRAIN] =
    {
        .name = _("引水"),
        .description = COMPOUND_STRING("吸引免疫水招式并提高特攻"),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_ICE_BODY] =
    {
        .name = _("冰冻之躯"),
        .description = COMPOUND_STRING("下雪天气时会缓缓回复HP"),
        .aiRating = 3,
    },

    [ABILITY_SOLID_ROCK] =
    {
        .name = _("坚硬岩石"),
        .description = COMPOUND_STRING("减轻效果绝佳的攻击伤害"),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SNOW_WARNING] =
    {
        .name = _("降雪"),
        .description = COMPOUND_STRING("出场时会将天气变为下雪"),
        .aiRating = 8,
    },

    [ABILITY_HONEY_GATHER] =
    {
        .name = _("采蜜"),
        .description = COMPOUND_STRING("战斗结束时有时捡来甜甜蜜"),
        .aiRating = 0,
    },

    [ABILITY_FRISK] =
    {
        .name = _("察觉"),
        .description = COMPOUND_STRING("出场时，可察觉对手持有物"),
        .aiRating = 3,
    },

    [ABILITY_RECKLESS] =
    {
        .name = _("舍身"),
        .description = COMPOUND_STRING("强化有反作用力伤害的招式"),
        .aiRating = 6,
    },

    [ABILITY_MULTITYPE] =
    {
        .name = _("多属性"),
        .description = COMPOUND_STRING("属性会根据持有的石板改变"),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_FLOWER_GIFT] =
    {
        .name = _("花之礼"),
        .description = COMPOUND_STRING("晴天时提升我方攻击和特防"),
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_BAD_DREAMS] =
    {
        .name = _("梦魇"),
        .description = COMPOUND_STRING("给予睡眠状态的对手伤害"),
        .aiRating = 4,
    },

    [ABILITY_PICKPOCKET] =
    {
        .name = _("顺手牵羊"),
        .description = COMPOUND_STRING("盗取接触到的对手的道具"),
        .aiRating = 3,
    },

    [ABILITY_SHEER_FORCE] =
    {
        .name = _("强行"),
        .description = COMPOUND_STRING("消除追加效果以强化招式"),
        .aiRating = 8,
    },

    [ABILITY_CONTRARY] =
    {
        .name = _("唱反调"),
        .description = COMPOUND_STRING("能力的升降变化发生逆转"),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_UNNERVE] =
    {
        .name = _("紧张感"),
        .description = COMPOUND_STRING("让对手紧张得无法食用树果"),
        .aiRating = 3,
    },

    [ABILITY_DEFIANT] =
    {
        .name = _("不服输"),
        .description = COMPOUND_STRING("被降低能力时大幅提高攻击"),
        .aiRating = 5,
    },

    [ABILITY_DEFEATIST] =
    {
        .name = _("软弱"),
        .description = COMPOUND_STRING("HP减半时攻击特攻会减半"),
        .aiRating = -1,
    },

    [ABILITY_CURSED_BODY] =
    {
        .name = _("诅咒之躯"),
        .description = COMPOUND_STRING("受击时有时会使招式定身法"),
        .aiRating = 4,
    },

    [ABILITY_HEALER] =
    {
        .name = _("治愈之心"),
        .description = COMPOUND_STRING("有时会治愈异常状态的同伴"),
        .aiRating = 0,
    },

    [ABILITY_FRIEND_GUARD] =
    {
        .name = _("友情防守"),
        .description = COMPOUND_STRING("可以减少我方的伤害"),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_WEAK_ARMOR] =
    {
        .name = _("碎裂铠甲"),
        .description = COMPOUND_STRING("受物理攻击降防御提高速度"),
        .aiRating = 2,
    },

    [ABILITY_HEAVY_METAL] =
    {
        .name = _("重金属"),
        .description = COMPOUND_STRING("自身的重量会变为2倍"),
        .aiRating = -1,
        .breakable = TRUE,
    },

    [ABILITY_LIGHT_METAL] =
    {
        .name = _("轻金属"),
        .description = COMPOUND_STRING("自身的重量会减半"),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MULTISCALE] =
    {
        .name = _("多重鳞片"),
        .description = COMPOUND_STRING("HP全满时减轻受到的伤害"),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_TOXIC_BOOST] =
    {
        .name = _("中毒激升"),
        .description = COMPOUND_STRING("中毒时提高物理招式的威力"),
        .aiRating = 6,
    },

    [ABILITY_FLARE_BOOST] =
    {
        .name = _("受热激升"),
        .description = COMPOUND_STRING("灼伤时提高特殊招式的威力"),
        .aiRating = 5,
    },

    [ABILITY_HARVEST] =
    {
        .name = _("收获"),
        .description = COMPOUND_STRING("可多次生成被使用掉的树果"),
        .aiRating = 5,
    },

    [ABILITY_TELEPATHY] =
    {
        .name = _("心灵感应"),
        .description = COMPOUND_STRING("闪避己方的招式伤害"),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_MOODY] =
    {
        .name = _("心情不定"),
        .description = COMPOUND_STRING("每回合某能力提高，某项降低"),
        .aiRating = 10,
    },

    [ABILITY_OVERCOAT] =
    {
        .name = _("防尘"),
        .description = COMPOUND_STRING("无视沙暴与粉末或孢子招式"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_POISON_TOUCH] =
    {
        .name = _("毒手"),
        .description = COMPOUND_STRING("接触时可能会使对手中毒"),
        .aiRating = 4,
    },

    [ABILITY_REGENERATOR] =
    {
        .name = _("再生力"),
        .description = COMPOUND_STRING("换下后HP会少量回复"),
        .aiRating = 8,
    },

    [ABILITY_BIG_PECKS] =
    {
        .name = _("健壮胸肌"),
        .description = COMPOUND_STRING("不会受到防御降低的效果"),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_SAND_RUSH] =
    {
        .name = _("拨沙"),
        .description = COMPOUND_STRING("沙暴天气时，速度会提高"),
        .aiRating = 6,
    },

    [ABILITY_WONDER_SKIN] =
    {
        .name = _("奇迹皮肤"),
        .description = COMPOUND_STRING("不易受到变化招式攻击"),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANALYTIC] =
    {
        .name = _("分析"),
        .description = COMPOUND_STRING("在最后使出招式时威力提高"),
        .aiRating = 5,
    },

    [ABILITY_ILLUSION] =
    {
        .name = _("幻觉"),
        .description = COMPOUND_STRING("幻化成同行宝可梦迷惑对手"),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_IMPOSTER] =
    {
        .name = _("变身者"),
        .description = COMPOUND_STRING("变身为当前面对的宝可梦"),
        .aiRating = 9,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_INFILTRATOR] =
    {
        .name = _("穿透"),
        .description = COMPOUND_STRING("能穿透壁障或替身进行攻击"),
        .aiRating = 6,
    },

    [ABILITY_MUMMY] =
    {
        .name = _("木乃伊"),
        .description = COMPOUND_STRING("被接触后将对手变为木乃伊"),
        .aiRating = 5,
    },

    [ABILITY_MOXIE] =
    {
        .name = _("自信过度"),
        .description = COMPOUND_STRING("打倒对手时攻击会提高"),
        .aiRating = 7,
    },

    [ABILITY_JUSTIFIED] =
    {
        .name = _("正义之心"),
        .description = COMPOUND_STRING("受恶属性攻击时提高攻击"),
        .aiRating = 4,
    },

    [ABILITY_RATTLED] =
    {
        .name = _("胆怯"),
        .description = COMPOUND_STRING("受恶鬼虫攻击威吓提高速度"),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_BOUNCE] =
    {
        .name = _("魔法镜"),
        .description = COMPOUND_STRING("反弹对手使出的变化招式"),
        .aiRating = 9,
        .breakable = TRUE,
    },

    [ABILITY_SAP_SIPPER] =
    {
        .name = _("食草"),
        .description = COMPOUND_STRING("免疫草属性攻击并提高攻击"),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_PRANKSTER] =
    {
        .name = _("恶作剧之心"),
        .description = COMPOUND_STRING("可以率先使出变化招式"),
        .aiRating = 8,
    },

    [ABILITY_SAND_FORCE] =
    {
        .name = _("沙之力"),
        .description = COMPOUND_STRING("沙暴时，强化岩地钢属性招式"),
        .aiRating = 4,
    },

    [ABILITY_IRON_BARBS] =
    {
        .name = _("铁刺"),
        .description = COMPOUND_STRING("用铁刺给予接触的对手伤害"),
        .aiRating = 6,
    },

    [ABILITY_ZEN_MODE] =
    {
        .name = _("达摩模式"),
        .description = COMPOUND_STRING("HP一半以下时改变样子"),
        .aiRating = -1,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = B_UPDATED_ABILITY_DATA >= GEN_7,
    },

    [ABILITY_VICTORY_STAR] =
    {
        .name = _("胜利之星"),
        .description = COMPOUND_STRING("自己和同伴的命中率会提高"),
        .aiRating = 6,
    },

    [ABILITY_TURBOBLAZE] =
    {
        .name = _("涡轮火焰"),
        .description = COMPOUND_STRING("使用招式不受对手特性影响"),
        .aiRating = 7,
    },

    [ABILITY_TERAVOLT] =
    {
        .name = _("兆级电压"),
        .description = COMPOUND_STRING("使用招式不受对手特性影响"),
        .aiRating = 7,
    },

    [ABILITY_AROMA_VEIL] =
    {
        .name = _("芳香幕"),
        .description = COMPOUND_STRING("防守向己方发出的心灵攻击"),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_FLOWER_VEIL] =
    {
        .name = _("花幕"),
        .description = COMPOUND_STRING("守护己方草宝可梦能力状态"),
        .aiRating = 0,
    },

    [ABILITY_CHEEK_POUCH] =
    {
        .name = _("颊囊"),
        .description = COMPOUND_STRING("食用任意树果HP都会回复"),
        .aiRating = 4,
    },

    [ABILITY_PROTEAN] =
    {
        .name = _("变幻自如"),
        .description = COMPOUND_STRING("一次性变为使出招式的属性"),
        .aiRating = 8,
    },

    [ABILITY_FUR_COAT] =
    {
        .name = _("毛皮大衣"),
        .description = COMPOUND_STRING("受物理招式的伤害会减半"),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MAGICIAN] =
    {
        .name = _("魔术师"),
        .description = COMPOUND_STRING("夺走被自己击中对手的道具"),
        .aiRating = 3,
    },

    [ABILITY_BULLETPROOF] =
    {
        .name = _("防弹"),
        .description = COMPOUND_STRING("防守球和弹类招式"),
        .aiRating = 7,
    },

    [ABILITY_COMPETITIVE] =
    {
        .name = _("好胜"),
        .description = COMPOUND_STRING("被降低能力时大幅提高特攻"),
        .aiRating = 5,
    },

    [ABILITY_STRONG_JAW] =
    {
        .name = _("强壮之颚"),
        .description = COMPOUND_STRING("啃咬类招式的威力会提高"),
        .aiRating = 6,
    },

    [ABILITY_REFRIGERATE] =
    {
        .name = _("冰冻皮肤"),
        .description = COMPOUND_STRING("一般招式变为冰属性并强化"),
        .aiRating = 8,
    },

    [ABILITY_SWEET_VEIL] =
    {
        .name = _("甜幕"),
        .description = COMPOUND_STRING("己方宝可梦不会睡眠"),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_STANCE_CHANGE] =
    {
        .name = _("战斗切换"),
        .description = COMPOUND_STRING("根据招式切换刀剑盾牌形态"),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_GALE_WINGS] =
    {
        .name = _("疾风之翼"),
        .description = COMPOUND_STRING("满HP时能先使出飞行招式"),
        .aiRating = 6,
    },

    [ABILITY_MEGA_LAUNCHER] =
    {
        .name = _("超级发射器"),
        .description = COMPOUND_STRING("强化波动和波导类招式"),
        .aiRating = 7,
    },

    [ABILITY_GRASS_PELT] =
    {
        .name = _("草之毛皮"),
        .description = COMPOUND_STRING("青草场地时，防御会提高"),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SYMBIOSIS] =
    {
        .name = _("共生"),
        .description = COMPOUND_STRING("会把道具传递给同伴"),
        .aiRating = 0,
    },

    [ABILITY_TOUGH_CLAWS] =
    {
        .name = _("硬爪"),
        .description = COMPOUND_STRING("接触类招式威力会提高"),
        .aiRating = 7,
    },

    [ABILITY_PIXILATE] =
    {
        .name = _("妖精皮肤"),
        .description = COMPOUND_STRING("一般招式变妖精属性并强化"),
        .aiRating = 8,
    },

    [ABILITY_GOOEY] =
    {
        .name = _("黏滑"),
        .description = COMPOUND_STRING("降低接触自己的对手的速度"),
        .aiRating = 5,
    },

    [ABILITY_AERILATE] =
    {
        .name = _("飞行皮肤"),
        .description = COMPOUND_STRING("一般招式变飞行属性并强化"),
        .aiRating = 8,
    },

    [ABILITY_PARENTAL_BOND] =
    {
        .name = _("亲子爱"),
        .description = COMPOUND_STRING("亲子俩可以合计攻击2次"),
        .aiRating = 10,
    },

    [ABILITY_DARK_AURA] =
    {
        .name = _("暗黑气场"),
        .description = COMPOUND_STRING("全体的恶属性招式变强"),
        .aiRating = 6,
    },

    [ABILITY_FAIRY_AURA] =
    {
        .name = _("妖精气场"),
        .description = COMPOUND_STRING("全体的妖精属性招式变强"),
        .aiRating = 6,
    },

    [ABILITY_AURA_BREAK] =
    {
        .name = _("气场破坏"),
        .description = COMPOUND_STRING("让气场的效果发生逆转"),
        .aiRating = 3,
    },

    [ABILITY_PRIMORDIAL_SEA] =
    {
        .name = _("始源之海"),
        .description = COMPOUND_STRING("变为不受火属性攻击的天气"),
        .aiRating = 10,
    },

    [ABILITY_DESOLATE_LAND] =
    {
        .name = _("终结之地"),
        .description = COMPOUND_STRING("变为不受水属性攻击的天气"),
        .aiRating = 10,
    },

    [ABILITY_DELTA_STREAM] =
    {
        .name = _("德尔塔气流"),
        .description = COMPOUND_STRING("变为飞行弱点消失的天气"),
        .aiRating = 10,
    },

    [ABILITY_STAMINA] =
    {
        .name = _("持久力"),
        .description = COMPOUND_STRING("受到攻击时，防御会提高"),
        .aiRating = 6,
    },

    [ABILITY_WIMP_OUT] =
    {
        .name = _("跃跃欲逃"),
        .description = COMPOUND_STRING("HP变为一半时会慌张逃走"),
        .aiRating = 3,
    },

    [ABILITY_EMERGENCY_EXIT] =
    {
        .name = _("危险回避"),
        .description = COMPOUND_STRING("HP变为一半时会回避危险"),
        .aiRating = 3,
    },

    [ABILITY_WATER_COMPACTION] =
    {
        .name = _("遇水凝固"),
        .description = COMPOUND_STRING("受水招式攻击大幅提高防御"),
        .aiRating = 4,
    },

    [ABILITY_MERCILESS] =
    {
        .name = _("不仁不义"),
        .description = COMPOUND_STRING("攻击中毒对手必定击中要害"),
        .aiRating = 4,
    },

    [ABILITY_SHIELDS_DOWN] =
    {
        .name = _("界限盾壳"),
        .description = COMPOUND_STRING("HP变为一半时更有攻击性"),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_STAKEOUT] =
    {
        .name = _("蹲守"),
        .description = COMPOUND_STRING("对替换出场的对手加倍伤害"),
        .aiRating = 6,
    },

    [ABILITY_WATER_BUBBLE] =
    {
        .name = _("水泡"),
        .description = COMPOUND_STRING("降低火招式伤害且不会灼伤"),
        .aiRating = 8,
    },

    [ABILITY_STEELWORKER] =
    {
        .name = _("钢能力者"),
        .description = COMPOUND_STRING("钢属性的招式威力会提高"),
        .aiRating = 6,
    },

    [ABILITY_BERSERK] =
    {
        .name = _("怒火冲天"),
        .description = COMPOUND_STRING("受击HP变一半时提高特攻"),
        .aiRating = 5,
    },

    [ABILITY_SLUSH_RUSH] =
    {
        .name = _("拨雪"),
        .description = COMPOUND_STRING("下雪天气时，速度会提高"),
        .aiRating = 5,
    },

    [ABILITY_LONG_REACH] =
    {
        .name = _("远隔"),
        .description = COMPOUND_STRING("可以不接触对手使出招式"),
        .aiRating = 3,
    },

    [ABILITY_LIQUID_VOICE] =
    {
        .name = _("湿润之声"),
        .description = COMPOUND_STRING("所有声音招式都变为水属性"),
        .aiRating = 5,
    },

    [ABILITY_TRIAGE] =
    {
        .name = _("先行治疗"),
        .description = COMPOUND_STRING("可以率先使出回复招式"),
        .aiRating = 7,
    },

    [ABILITY_GALVANIZE] =
    {
        .name = _("电气皮肤"),
        .description = COMPOUND_STRING("一般招式变为电属性并强化"),
        .aiRating = 8,
    },

    [ABILITY_SURGE_SURFER] =
    {
        .name = _("冲浪之尾"),
        .description = COMPOUND_STRING("电气场地时速度会变为2倍"),
        .aiRating = 4,
    },

    [ABILITY_SCHOOLING] =
    {
        .name = _("鱼群"),
        .description = COMPOUND_STRING("HP多则聚众变强少则分散"),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_DISGUISE] =
    {
        .name = _("画皮"),
        .description = COMPOUND_STRING("通过画皮防住1次攻击"),
        .aiRating = 8,
        .breakable = TRUE,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_BATTLE_BOND] =
    {
        .name = _("牵绊变身"),
        .description = COMPOUND_STRING("打倒对手时提高能力"),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_POWER_CONSTRUCT] =
    {
        .name = _("群聚变形"),
        .description = COMPOUND_STRING("HP一半时变成完全体形态"),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_CORROSION] =
    {
        .name = _("腐蚀"),
        .description = COMPOUND_STRING("可使钢毒属性的宝可梦中毒"),
        .aiRating = 5,
    },

    [ABILITY_COMATOSE] =
    {
        .name = _("绝对睡眠"),
        .description = COMPOUND_STRING("在半梦半醒的状态下攻击"),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_QUEENLY_MAJESTY] =
    {
        .name = _("女王的威严"),
        .description = COMPOUND_STRING("使对手无法使出先制招式"),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_INNARDS_OUT] =
    {
        .name = _("飞出的内在物"),
        .description = COMPOUND_STRING("被击倒时造成剩余HP伤害"),
        .aiRating = 5,
    },

    [ABILITY_DANCER] =
    {
        .name = _("舞者"),
        .description = COMPOUND_STRING("跟随着其他舞蹈使出舞蹈"),
        .aiRating = 5,
    },

    [ABILITY_BATTERY] =
    {
        .name = _("蓄电池"),
        .description = COMPOUND_STRING("提高我方的特殊招式的威力"),
        .aiRating = 0,
    },

    [ABILITY_FLUFFY] =
    {
        .name = _("毛茸茸"),
        .description = COMPOUND_STRING("减轻接触伤害，但害怕火伤害"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_DAZZLING] =
    {
        .name = _("鲜艳之躯"),
        .description = COMPOUND_STRING("使对手无法使出先制招式"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SOUL_HEART] =
    {
        .name = _("魂心"),
        .description = COMPOUND_STRING("有宝可梦昏厥时，特攻会提高"),
        .aiRating = 7,
    },

    [ABILITY_TANGLING_HAIR] =
    {
        .name = _("卷发"),
        .description = COMPOUND_STRING("降低接触自己的对手的速度"),
        .aiRating = 5,
    },

    [ABILITY_RECEIVER] =
    {
        .name = _("接球手"),
        .description = COMPOUND_STRING("继承被打倒的同伴的特性"),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POWER_OF_ALCHEMY] =
    {
        .name = _("化学之力"),
        .description = COMPOUND_STRING("继承被打倒的同伴的特性"),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_BEAST_BOOST] =
    {
        .name = _("异兽提升"),
        .description = COMPOUND_STRING("打倒对手时，提升最高能力"),
        .aiRating = 7,
    },

    [ABILITY_RKS_SYSTEM] =
    {
        .name = _("AR系统"),
        .description = COMPOUND_STRING("根据存储碟改变自己属性"),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_ELECTRIC_SURGE] =
    {
        .name = _("电气制造者"),
        .description = COMPOUND_STRING("出场时，会布下电气场地"),
        .aiRating = 8,
    },

    [ABILITY_PSYCHIC_SURGE] =
    {
        .name = _("精神制造者"),
        .description = COMPOUND_STRING("出场时，会布下精神场地"),
        .aiRating = 8,
    },

    [ABILITY_MISTY_SURGE] =
    {
        .name = _("薄雾制造者"),
        .description = COMPOUND_STRING("出场时，会布下薄雾场地"),
        .aiRating = 8,
    },

    [ABILITY_GRASSY_SURGE] =
    {
        .name = _("青草制造者"),
        .description = COMPOUND_STRING("出场时，会布下青草场地"),
        .aiRating = 8,
    },

    [ABILITY_FULL_METAL_BODY] =
    {
        .name = _("金属防护"),
        .description = COMPOUND_STRING("不因对手招式特性降低能力"),
        .aiRating = 4,
    },

    [ABILITY_SHADOW_SHIELD] =
    {
        .name = _("幻影防守"),
        .description = COMPOUND_STRING("HP全满时减少受到的伤害"),
        .aiRating = 8,
    },

    [ABILITY_PRISM_ARMOR] =
    {
        .name = _("棱镜装甲"),
        .description = COMPOUND_STRING("减轻所受效果绝佳的伤害"),
        .aiRating = 6,
    },

    [ABILITY_NEUROFORCE] =
    {
        .name = _("脑核之力"),
        .description = COMPOUND_STRING("增强效果绝佳招式的伤害"),
        .aiRating = 6,
    },

    [ABILITY_INTREPID_SWORD] =
    {
        .name = _("不挠之剑"),
        .description = COMPOUND_STRING("首次出场时，攻击会提高"),
        .aiRating = 3,
    },

    [ABILITY_DAUNTLESS_SHIELD] =
    {
        .name = _("不屈之盾"),
        .description = COMPOUND_STRING("首次出场时，防御会提高"),
        .aiRating = 3,
    },

    [ABILITY_LIBERO] =
    {
        .name = _("自由者"),
        .description = COMPOUND_STRING("一次性变为使出招式的属性"),
    },

    [ABILITY_BALL_FETCH] =
    {
        .name = _("捡球"),
        .description = COMPOUND_STRING("拾取捕捉失败的精灵球"),
        .aiRating = 0,
    },

    [ABILITY_COTTON_DOWN] =
    {
        .name = _("棉絮"),
        .description = COMPOUND_STRING("受攻击降低其他宝可梦速度"),
        .aiRating = 3,
    },

    [ABILITY_PROPELLER_TAIL] =
    {
        .name = _("螺旋尾鳍"),
        .description = COMPOUND_STRING("招式不被对手特性招式吸引"),
        .aiRating = 2,
    },

    [ABILITY_MIRROR_ARMOR] =
    {
        .name = _("镜甲"),
        .description = COMPOUND_STRING("反弹自己受到的能力降低"),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_GULP_MISSILE] =
    {
        .name = _("一口导弹"),
        .description = COMPOUND_STRING("冲浪潜水时会吐出猎物攻击"),
        .aiRating = 3,
        .cantBeCopied = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_STALWART] =
    {
        .name = _("坚毅"),
        .description = COMPOUND_STRING("招式不被对手特性招式吸引"),
        .aiRating = 2,
    },

    [ABILITY_STEAM_ENGINE] =
    {
        .name = _("蒸汽机"),
        .description = COMPOUND_STRING("受水火攻击时速度巨幅提高"),
        .aiRating = 3,
    },

    [ABILITY_PUNK_ROCK] =
    {
        .name = _("庞克摇滚"),
        .description = COMPOUND_STRING("强化声音招式并减轻其影响"),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SAND_SPIT] =
    {
        .name = _("吐沙"),
        .description = COMPOUND_STRING("受到攻击时，会刮起沙暴"),
        .aiRating = 5,
    },

    [ABILITY_ICE_SCALES] =
    {
        .name = _("冰鳞粉"),
        .description = COMPOUND_STRING("受到的特殊攻击伤害会减半"),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_RIPEN] =
    {
        .name = _("熟成"),
        .description = COMPOUND_STRING("使树果成熟，效果变为2倍"),
        .aiRating = 4,
    },

    [ABILITY_ICE_FACE] =
    {
        .name = _("结冻头"),
        .description = COMPOUND_STRING("头部的冰能代承受物理攻击"),
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .breakable = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_POWER_SPOT] =
    {
        .name = _("能量点"),
        .description = COMPOUND_STRING("相邻宝可梦招式威力会提升"),
        .aiRating = 2,
    },

    [ABILITY_MIMICRY] =
    {
        .name = _("拟态"),
        .description = COMPOUND_STRING("属性会根据场地而变化"),
        .aiRating = 2,
    },

    [ABILITY_SCREEN_CLEANER] =
    {
        .name = _("除障"),
        .description = COMPOUND_STRING("出场时，消除双方墙壁类效果"),
        .aiRating = 3,
    },

    [ABILITY_STEELY_SPIRIT] =
    {
        .name = _("钢之意志"),
        .description = COMPOUND_STRING("我方钢属性攻击威力会提高"),
        .aiRating = 2,
    },

    [ABILITY_PERISH_BODY] =
    {
        .name = _("灭亡之躯"),
        .description = COMPOUND_STRING("受接触攻击双方3回合昏厥"),
        .aiRating = -1,
    },

    [ABILITY_WANDERING_SPIRIT] =
    {
        .name = _("游魂"),
        .description = COMPOUND_STRING("与接触攻击的宝可梦换特性"),
        .aiRating = 2,
    },

    [ABILITY_GORILLA_TACTICS] =
    {
        .name = _("一猩一意"),
        .description = COMPOUND_STRING("攻击提高但只能用最初招式"),
        .aiRating = 4,
    },

    [ABILITY_NEUTRALIZING_GAS] =
    {
        .name = _("化学变化气体"),
        .description = COMPOUND_STRING("在场时全场特性消失或无效"),
        .aiRating = 5,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_PASTEL_VEIL] =
    {
        .name = _("粉彩护幕"),
        .description = COMPOUND_STRING("守护己方不会中毒"),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_HUNGER_SWITCH] =
    {
        .name = _("饱了又饿"),
        .description = COMPOUND_STRING("每回合结束时交替改变样子"),
        .aiRating = 2,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUICK_DRAW] =
    {
        .name = _("速击"),
        .description = COMPOUND_STRING("有时能比对手先一步行动"),
        .aiRating = 4,
    },

    [ABILITY_UNSEEN_FIST] =
    {
        .name = _("无形拳"),
        .description = COMPOUND_STRING("接触招式可以无视守护效果"),
        .aiRating = 6,
    },

    [ABILITY_CURIOUS_MEDICINE] =
    {
        .name = _("怪药"),
        .description = COMPOUND_STRING("出场时将我方能力变化复原"),
        .aiRating = 3,
    },

    [ABILITY_TRANSISTOR] =
    {
        .name = _("电晶体"),
        .description = COMPOUND_STRING("电属性的招式威力会提高"),
        .aiRating = 6,
    },

    [ABILITY_DRAGONS_MAW] =
    {
        .name = _("龙颚"),
        .description = COMPOUND_STRING("龙属性的招式威力会提高"),
        .aiRating = 6,
    },

    [ABILITY_CHILLING_NEIGH] =
    {
        .name = _("苍白嘶鸣"),
        .description = COMPOUND_STRING("打倒对手时会提高攻击"),
        .aiRating = 7,
    },

    [ABILITY_GRIM_NEIGH] =
    {
        .name = _("漆黑嘶鸣"),
        .description = COMPOUND_STRING("打倒对手时会提高特攻"),
        .aiRating = 7,
    },

    [ABILITY_AS_ONE_ICE_RIDER] =
    {
        .name = _("人马一体"),
        .description = COMPOUND_STRING("兼备紧张感和苍白嘶鸣特性"),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_AS_ONE_SHADOW_RIDER] =
    {
        .name = _("人马一体"),
        .description = COMPOUND_STRING("兼备紧张感和漆黑嘶鸣特性"),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_LINGERING_AROMA] =
    {
        .name = _("甩不掉的气味"),
        .description = COMPOUND_STRING("被接触会沾上甩不掉的气味"),
        .aiRating = 5,
    },

    [ABILITY_SEED_SOWER] =
    {
        .name = _("掉出种子"),
        .description = COMPOUND_STRING("受到攻击时会生成青草场地"),
        .aiRating = 5,
    },

    [ABILITY_THERMAL_EXCHANGE] =
    {
        .name = _("热交换"),
        .description = COMPOUND_STRING("受火攻击提高攻击，不会灼伤"),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANGER_SHELL] =
    {
        .name = _("愤怒甲壳"),
        .description = COMPOUND_STRING("受击HP变一半时变得愤怒"),
        .aiRating = 3,
    },

    [ABILITY_PURIFYING_SALT] =
    {
        .name = _("洁净之盐"),
        .description = COMPOUND_STRING("免疫异常，减轻幽灵伤害"),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_WELL_BAKED_BODY] =
    {
        .name = _("焦香之躯"),
        .description = COMPOUND_STRING("免疫火招式并大幅提升防御"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_WIND_RIDER] =
    {
        .name = _("乘风"),
        .description = COMPOUND_STRING("免疫风招式，顺风时提高攻击"),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_GUARD_DOG] =
    {
        .name = _("看门犬"),
        .description = COMPOUND_STRING("使对方无法替换并免疫威吓"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ROCKY_PAYLOAD] =
    {
        .name = _("搬岩"),
        .description = COMPOUND_STRING("岩石属性的招式威力会提高"),
        .aiRating = 6,
    },

    [ABILITY_WIND_POWER] =
    {
        .name = _("风力发电"),
        .description = COMPOUND_STRING("受风招式时会变为充电状态"),
        .aiRating = 4,
    },

    [ABILITY_ZERO_TO_HERO] =
    {
        .name = _("全能变身"),
        .description = COMPOUND_STRING("换下后会变为全能形态"),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_COMMANDER] =
    {
        .name = _("发号施令"),
        .description = COMPOUND_STRING("进入吃吼霸口中发出指令"),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_ELECTROMORPHOSIS] =
    {
        .name = _("电力转换"),
        .description = COMPOUND_STRING("受到伤害时，会变为充电状态"),
        .aiRating = 5,
    },

    [ABILITY_PROTOSYNTHESIS] =
    {
        .name = _("古代活性"),
        .description = COMPOUND_STRING("晴天时提升最高能力"),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUARK_DRIVE] =
    {
        .name = _("夸克充能"),
        .description = COMPOUND_STRING("电气场地上提升最高能力"),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_GOOD_AS_GOLD] =
    {
        .name = _("黄金之躯"),
        .description = COMPOUND_STRING("不会受到变化招式的影响"),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_VESSEL_OF_RUIN] =
    {
        .name = _("灾祸之鼎"),
        .description = COMPOUND_STRING("降低其他的宝可梦的特攻"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SWORD_OF_RUIN] =
    {
        .name = _("灾祸之剑"),
        .description = COMPOUND_STRING("降低其他的宝可梦的防御"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_TABLETS_OF_RUIN] =
    {
        .name = _("灾祸之简"),
        .description = COMPOUND_STRING("降低其他的宝可梦的攻击"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_BEADS_OF_RUIN] =
    {
        .name = _("灾祸之玉"),
        .description = COMPOUND_STRING("降低其他的宝可梦的特防"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ORICHALCUM_PULSE] =
    {
        .name = _("绯红脉动"),
        .description = COMPOUND_STRING("造成晴天，在晴天下提升物攻"),
        .aiRating = 8,
    },

    [ABILITY_HADRON_ENGINE] =
    {
        .name = _("强子引擎"),
        .description = COMPOUND_STRING("生成电场，在电场上提升特攻"),
        .aiRating = 8,
    },

    [ABILITY_OPPORTUNIST] =
    {
        .name = _("跟风"),
        .description = COMPOUND_STRING("跟随对手趁机同样提高能力"),
        .aiRating = 5,
    },

    [ABILITY_CUD_CHEW] =
    {
        .name = _("反刍"),
        .description = COMPOUND_STRING("吃树果后会反刍再吃1次"),
        .aiRating = 4,
    },

    [ABILITY_SHARPNESS] =
    {
        .name = _("锋锐"),
        .description = COMPOUND_STRING("提高切割对手的招式的威力"),
        .aiRating = 7,
    },

    [ABILITY_SUPREME_OVERLORD] =
    {
        .name = _("大将"),
        .description = COMPOUND_STRING("按被打倒数提升攻击特攻"),
        .aiRating = 6,
    },

    [ABILITY_COSTAR] =
    {
        .name = _("同台共演"),
        .description = COMPOUND_STRING("出场时，复制同伴的能力变化"),
        .aiRating = 5,
    },

    [ABILITY_TOXIC_DEBRIS] =
    {
        .name = _("毒满地"),
        .description = COMPOUND_STRING("受物理伤害时，会散布毒菱"),
        .aiRating = 4,
    },

    [ABILITY_ARMOR_TAIL] =
    {
        .name = _("尾甲"),
        .description = COMPOUND_STRING("使对手无法使出先制招式"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_EARTH_EATER] =
    {
        .name = _("食土"),
        .description = COMPOUND_STRING("受到地面属性攻击时会回复"),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MYCELIUM_MIGHT] =
    {
        .name = _("菌丝之力"),
        .description = COMPOUND_STRING("变化招式变慢，但无视特性"),
        .aiRating = 2,
    },

    [ABILITY_HOSPITALITY] =
    {
        .name = _("款待"),
        .description = COMPOUND_STRING("出场时回复同伴少量HP"),
        .aiRating = 5,
    },

    [ABILITY_MINDS_EYE] =
    {
        .name = _("心眼"),
        .description = COMPOUND_STRING("兼具胆量以及锐利目光特性"),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_TEAL_MASK] =
    {
        .name = _("面影辉映"),
        .description = COMPOUND_STRING("将回忆铭记，提高自己的速度"),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK] =
    {
        .name = _("面影辉映"),
        .description = COMPOUND_STRING("将回忆铭记，提高自己的攻击"),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_WELLSPRING_MASK] =
    {
        .name = _("面影辉映"),
        .description = COMPOUND_STRING("将回忆铭记，提高自己的特防"),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK] =
    {
        .name = _("面影辉映"),
        .description = COMPOUND_STRING("将回忆铭记，提高自己的防御"),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TOXIC_CHAIN] =
    {
        .name = _("毒锁链"),
        .description = COMPOUND_STRING("有时能让击中对手陷入剧毒"),
        .aiRating = 8,
    },

    [ABILITY_SUPERSWEET_SYRUP] =
    {
        .name = _("甘露之蜜"),
        .description = COMPOUND_STRING("首次出场时降低对手闪避率"),
        .aiRating = 5,
    },

    [ABILITY_TERA_SHIFT] =
    {
        .name = _("太晶变形"),
        .description = COMPOUND_STRING("出场时，会变为太晶形态"),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TERA_SHELL] =
    {
        .name = _("太晶甲壳"),
        .description = COMPOUND_STRING("HP全满时抵抗所有属性"),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_TERAFORM_ZERO] =
    {
        .name = _("归零化境"),
        .description = COMPOUND_STRING("会将天气场地影响全部归零"),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POISON_PUPPETEER] =
    {
        .name = _("毒傀儡"),
        .description = COMPOUND_STRING("因其招式而中毒时会混乱"),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },
};
