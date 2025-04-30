BattleFrontier_Lounge5_MapScripts::
	.byte 0

BattleFrontier_Lounge5_EventScript_NatureGirl::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge5_Text_NatureGirlGreeting, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	special ChoosePartyMon
	waitstate
	lock
	faceplayer
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, BattleFrontier_Lounge5_EventScript_NatureGirlEgg
	special ShowNatureGirlMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlEgg::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlEgg, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlNoneShown, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_Gentleman::
	msgbox BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_BlackBelt::
	msgbox BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_LittleBoy::
	msgbox BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot, MSGBOX_NPC
	end

BattleFrontier_Lounge5_Text_NatureGirlGreeting::
	.string "呵呵！\n我能看出宝可梦在想什么哦！\p来吧！\n让我看看你的宝可梦！$"

BattleFrontier_Lounge5_Text_NatureGirlNoneShown::
    .string "砰！\n咔嚓！$"

BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow::
    .string "嗯嗯……\p它说它想去战斗！\n它说无论会受什么伤\l它都想去战斗！$"

BattleFrontier_Lounge5_Text_NatureGirlAttackHighDefenseLow::
    .string "嗯嗯……\p它说它想去战斗！\n但如果它受伤太重，\l它会更多照顾自己的！$"

BattleFrontier_Lounge5_Text_NatureGirlAttackHighSupportLow::
    .string "嗯嗯……\p它说它想去战斗！\n但如果它受伤太重，\l它还是想避开战斗！$"

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighAttackLow::
    .string "嗯嗯……\p它说它会照顾自己更多一些！\n但如果它受伤太重，\l它还是会报复！$"

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighDefenseLow::
	 .string "嗯嗯……\p它说它会照顾自己更多一些！\n它说不管受伤重不重\l它都会更多照顾自己！$"

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighSupportLow::
	.string "嗯嗯……\p它说它会小心躲开战斗的！\n它说就算受伤很重\l它还是想避开战斗！$"

BattleFrontier_Lounge5_Text_NatureGirlSupportHighAttackLow::
	.string "嗯嗯……\p它说它会小心躲开战斗的！\n但如果它受伤太重，\l它还是会报复！$"

BattleFrontier_Lounge5_Text_NatureGirlSupportHighDefenseLow::
	.string "嗯嗯……\p它说它会小心躲开战斗的！\n但如果它受伤太重，\l它会更多照顾自己的！$"

BattleFrontier_Lounge5_Text_NatureGirlSupportHighSupportLow::
	.string "嗯嗯……\p它说它会小心躲开战斗的！\n它说就算受伤很重\l它还是想避开战斗！$"

BattleFrontier_Lounge5_Text_NatureGirlEgg::
    .string "你在干什么傻事！蛋可在沉睡啊！\n我怎么跟它交谈呢！$"

BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon::
    .string "好像魔法一样啊！\n那边那位小女孩说她能\l懂得宝可梦在说什么！$"

BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound::
    .string "我感觉那个小女孩好像在\n说什么很深奥难明的话。$"

BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot::
    .string "我知道我知道！\p那个小女孩经常在\n红色的房子里玩！$"

