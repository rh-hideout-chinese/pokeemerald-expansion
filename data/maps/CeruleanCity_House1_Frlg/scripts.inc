CeruleanCity_House1_Frlg_MapScripts::
	.byte 0

CeruleanCity_House1_EventScript_BadgeGuy::
	lock
	faceplayer
	msgbox CeruleanCity_House1_Text_BadgesHaveAmazingSecrets
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeAnotherBadge::
	message CeruleanCity_House1_Text_DescribeWhichBadge
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BADGES
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, CeruleanCity_House1_EventScript_DescribeBoulderBadge
	case 1, CeruleanCity_House1_EventScript_DescribeCascadeBadge
	case 2, CeruleanCity_House1_EventScript_DescribeThunderBadge
	case 3, CeruleanCity_House1_EventScript_DescribeRainbowBadge
	case 4, CeruleanCity_House1_EventScript_DescribeSoulBadge
	case 5, CeruleanCity_House1_EventScript_DescribeMarshBadge
	case 6, CeruleanCity_House1_EventScript_DescribeVolcanoBadge
	case 7, CeruleanCity_House1_EventScript_DescribeEarthBadge
	case 8, CeruleanCity_House1_EventScript_StopDescribingBadges
	case 127, CeruleanCity_House1_EventScript_StopDescribingBadges
	end

CeruleanCity_House1_EventScript_DescribeBoulderBadge::
	msgbox CeruleanCity_House1_Text_AttackStatFlash
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeCascadeBadge::
	msgbox CeruleanCity_House1_Text_ObeyLv30Cut
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeThunderBadge::
	msgbox CeruleanCity_House1_Text_SpeedStatFly
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeRainbowBadge::
	msgbox CeruleanCity_House1_Text_ObeyLv50Strength
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeSoulBadge::
	msgbox CeruleanCity_House1_Text_DefenseStatSurf
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeMarshBadge::
	msgbox CeruleanCity_House1_Text_ObeyLv70RockSmash
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeVolcanoBadge::
	msgbox CeruleanCity_House1_Text_SpStatsWaterfall
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeEarthBadge::
	msgbox CeruleanCity_House1_Text_AllMonsWillObeyYou
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_StopDescribingBadges::
	msgbox CeruleanCity_House1_Text_ComeVisitAnytime
	release
	end

CeruleanCity_House1_Text_BadgesHaveAmazingSecrets::
    .string "只有有能力的训练家能够\n"
    .string "收集到宝可梦徽章。\p"
    .string "我看你应该是他们中的一个。\p"
    .string "那些徽章都有着惊人的秘密，\n"
    .string "你知道吗？$"

CeruleanCity_House1_Text_DescribeWhichBadge::
    .string "那现在……\p"
    .string "我应该描述八个徽章中的\n"
    .string "哪一个呢？$"

CeruleanCity_House1_Text_ComeVisitAnytime::
    .string "你随时都可以来找我。$"

CeruleanCity_House1_Text_AttackStatFlash::
    .string "稍微提高你的宝可梦的攻击。\p"
    .string "也可以让你在不战斗\n"
    .string "的时候使用闪光。$"

CeruleanCity_House1_Text_ObeyLv30Cut::
    .string "30级以内的宝可梦\n"
    .string "都会听你的话。\p"
    .string "包括你交换得来的宝可梦。\p"
    .string "但是较高级别的宝可梦\n"
    .string "仍然很难控制。\p"
    .string "也可以让你在\n"
    .string "不战斗的时候使用居合斩。$"

CeruleanCity_House1_Text_SpeedStatFly::
    .string "稍微提高你的宝可梦的速度。\p"
    .string "也可以让你在\n"
    .string "不战斗的时候使用飞翔。$"

CeruleanCity_House1_Text_ObeyLv50Strength::
    .string "50级以内的宝可梦\n"
    .string "都会听你的话。\p"
    .string "包括你交换得来的宝可梦。\p"
    .string "但是较高级别的宝可梦\n"
    .string "仍然很难控制。\p"
    .string "也可以让你在\n"
    .string "不战斗的时候使用怪力。$"

CeruleanCity_House1_Text_DefenseStatSurf::
    .string "稍微提高你的宝可梦的防御。\p"
    .string "也可以让你在\n"
    .string "不战斗的时候使用冲浪。$"

CeruleanCity_House1_Text_ObeyLv70RockSmash::
    .string "70级以内的宝可梦\n"
    .string "都会听你的话。\p"
    .string "包括你交换得来的宝可梦。\p"
    .string "但是较高级别的宝可梦\n"
    .string "仍然很难控制。\p"
    .string "也可以让你在\n"
    .string "不战斗的时候使用碎岩。$"

CeruleanCity_House1_Text_SpStatsWaterfall::
    .string "稍微提高你的宝可梦的特攻和特防。\p"
    .string "也可以让你在\n"
    .string "不战斗的时候使用攀瀑。$"

CeruleanCity_House1_Text_AllMonsWillObeyYou::
    .string "所有的宝可梦都会听你的话了！$"

