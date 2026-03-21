VermilionCity_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VermilionCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

VermilionCity_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_VERMILION_CITY
	end

VermilionCity_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

VermilionCity_PokemonCenter_1F_EventScript_Man::
	msgbox VermilionCity_PokemonCenter_1F_Text_PoisonedMonFaintedWhileWalking, MSGBOX_NPC
	end

VermilionCity_PokemonCenter_1F_EventScript_Hiker::
	msgbox VermilionCity_PokemonCenter_1F_Text_TrainerMonsStrongerThanWild, MSGBOX_NPC
	end

VermilionCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox VermilionCity_PokemonCenter_1F_Text_AllMonWeakToSpecificTypes, MSGBOX_NPC
	end

VermilionCity_PokemonCenter_1F_EventScript_VSSeekerWoman::
	lock
	faceplayer
	goto_if_set FLAG_GOT_VS_SEEKER, VermilionCity_PokemonCenter_1F_EventScript_ExplainVSSeeker
	msgbox VermilionCity_PokemonCenter_1F_Text_UrgeToBattleSomeoneAgain
	setflag FLAG_GOT_VS_SEEKER
	giveitem ITEM_VS_SEEKER
	goto_if_eq VAR_RESULT, FALSE, EventScript_BagIsFull
	msgbox VermilionCity_PokemonCenter_1F_Text_UseDeviceForRematches
	release
	end

VermilionCity_PokemonCenter_1F_EventScript_ExplainVSSeeker::
	msgbox VermilionCity_PokemonCenter_1F_Text_ExplainVSSeeker
	release
	end

VermilionCity_PokemonCenter_1F_Text_TrainerMonsStrongerThanWild::
    .string "即使是相同的等级，\n"
    .string "宝可梦能拥有非常不同的\l"
    .string "技能和力量。\p"
    .string "训练家培育的宝可梦\n"
    .string "要强于野生的。$"

VermilionCity_PokemonCenter_1F_Text_PoisonedMonFaintedWhileWalking::
    .string "我的宝可梦中毒了！\n"
    .string "我们走路的时候它会进入濒死状态！$"

VermilionCity_PokemonCenter_1F_Text_AllMonWeakToSpecificTypes::
    .string "确实一只等级高的\n"
    .string "宝可梦会更厉害……\p"
    .string "但是，所有的宝可梦在对上\n"
    .string "特定的系的时候都会有弱点。\p"
    .string "所以，没有一只永远强大的宝可梦。$"

VermilionCity_PokemonCenter_1F_Text_UrgeToBattleSomeoneAgain::
    .string "对曾经战斗过的人\n"
    .string "你有过……\p"
    .string "想要再次挑战的欲望吗？\n"
    .string "我想你肯定有过。\p"
    .string "我也想一次又一次地\n"
    .string "和从前的某些人战斗。\p"
    .string "我就是以这样的方式在战斗着。\n"
    .string "拿着这个吧！$"

VermilionCity_PokemonCenter_1F_Text_UseDeviceForRematches::
    .string "用这个装置你可以找到\n"
    .string "曾经战斗过的训练家再战。\p"
    .string "但是你在使用前得把电充好。$"

VermilionCity_PokemonCenter_1F_Text_ExplainVSSeeker::
    .string "你是怎样使用对战搜寻器的？\n"
    .string "这没什么困难的。\p"
    .string "使用时会发出哔-哔-嘟的声音，\n"
    .string "你再看看周围的训练家。\p"
    .string "如过任何训练家想再战，\n"
    .string "它会让你马上知道。\p"
    .string "当你在室外时，\n"
    .string "记得先充好电。$"
