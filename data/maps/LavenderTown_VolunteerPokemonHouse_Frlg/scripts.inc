LavenderTown_VolunteerPokemonHouse_Frlg_MapScripts::
	.byte 0

LavenderTown_VolunteerPokemonHouse_EventScript_MrFuji::
	lock
	faceplayer
	goto_if_set FLAG_GOT_POKE_FLUTE, LavenderTown_VolunteerPokemonHouse_EventScript_AlreadyHavePokeFlute
	msgbox LavenderTown_VolunteerPokemonHouse_Text_IdLikeYouToHaveThis
	checkitemspace ITEM_POKE_FLUTE
	goto_if_eq VAR_RESULT, FALSE, LavenderTown_VolunteerPokemonHouse_EventScript_NoRoomForPokeFlute
	setflag FLAG_GOT_POKE_FLUTE
	giveitem_msg LavenderTown_VolunteerPokemonHouse_Text_ReceivedPokeFluteFromMrFuji, ITEM_POKE_FLUTE, 1, MUS_RG_OBTAIN_KEY_ITEM
	msgbox LavenderTown_VolunteerPokemonHouse_Text_ExplainPokeFlute
	release
	end

LavenderTown_VolunteerPokemonHouse_EventScript_AlreadyHavePokeFlute::
	msgbox LavenderTown_VolunteerPokemonHouse_Text_HasPokeFluteHelpedYou
	release
	end

LavenderTown_VolunteerPokemonHouse_EventScript_NoRoomForPokeFlute::
	msgbox LavenderTown_VolunteerPokemonHouse_Text_MustMakeRoomForThis
	release
	end

LavenderTown_VolunteerPokemonHouse_EventScript_LittleGirl::
	lock
	faceplayer
	famechecker FAMECHECKER_MRFUJI, 0
	msgbox LavenderTown_VolunteerPokemonHouse_Text_MrFujiLooksAfterOrphanedMons
	release
	end

LavenderTown_VolunteerPokemonHouse_EventScript_LittleBoy::
	msgbox LavenderTown_VolunteerPokemonHouse_Text_MonsNiceToHug, MSGBOX_NPC
	end

LavenderTown_VolunteerPokemonHouse_EventScript_Youngster::
	lock
	faceplayer
	goto_if_set FLAG_RESCUED_MR_FUJI, LavenderTown_VolunteerPokemonHouse_EventScript_YoungsterFujiBack
	msgbox LavenderTown_VolunteerPokemonHouse_Text_WhereDidMrFujiGo
	release
	end

LavenderTown_VolunteerPokemonHouse_EventScript_YoungsterFujiBack::
	msgbox LavenderTown_VolunteerPokemonHouse_Text_MrFujiWasPrayingForCubonesMother
	release
	end

LavenderTown_VolunteerPokemonHouse_EventScript_Nidorino::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_NIDORINO, CRY_MODE_NORMAL
	msgbox LavenderTown_VolunteerPokemonHouse_Text_Nidorino
	waitmoncry
	release
	end

LavenderTown_VolunteerPokemonHouse_EventScript_Psyduck::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PSYDUCK, CRY_MODE_NORMAL
	msgbox LavenderTown_VolunteerPokemonHouse_Text_Psyduck
	waitmoncry
	release
	end

LavenderTown_VolunteerPokemonHouse_EventScript_PokemonFanMagazine::
	lockall
	famechecker FAMECHECKER_MRFUJI, 2
	msgbox LavenderTown_VolunteerPokemonHouse_Text_GrandPrizeDrawingClipped
	releaseall
	end

LavenderTown_VolunteerPokemonHouse_EventScript_Bookshelf::
	msgbox LavenderTown_VolunteerPokemonHouse_Text_PokemonMagazinesLineShelf, MSGBOX_SIGN
	end

LavenderTown_PokemonCenter_1F_Text_HearMrFujiNotFromAroundHere::
    .string "我不久前搬来这个城镇。\p"
    .string "我听说富士老人也不是\n"
    .string "生来就在这儿的。$"

LavenderTown_VolunteerPokemonHouse_Text_WhereDidMrFujiGo::
    .string "真奇怪，富士老人不在这儿。\n"
    .string "他会去哪儿呢？$"

LavenderTown_VolunteerPokemonHouse_Text_MrFujiWasPrayingForCubonesMother::
    .string "富士老人正在独自为\n"
    .string "卡拉卡拉的妈妈祈祷。$"

LavenderTown_VolunteerPokemonHouse_Text_MrFujiLooksAfterOrphanedMons::
    .string "这是富士老人的家。\p"
    .string "他真的非常和蔼。\p"
    .string "他照顾那些被遗弃的\n"
    .string "和孤独的宝可梦。$"

LavenderTown_VolunteerPokemonHouse_Text_MonsNiceToHug::
    .string "太温馨了！\n"
    .string "宝可梦靠在一起真美好！$"

LavenderTown_VolunteerPokemonHouse_Text_Nidorino::
    .string "尼多力诺：噶哦！$"

LavenderTown_VolunteerPokemonHouse_Text_Psyduck::
    .string "可达鸭：呱啪！$"

LavenderTown_VolunteerPokemonHouse_Text_IdLikeYouToHaveThis::
    .string "富士老人：{PLAYER}……\p"
    .string "收集宝可梦图鉴\n"
    .string "需要花很多时间。\p"
    .string "如果对宝可梦没有很深的感情，\n"
    .string "你可能会在中途放弃。\p"
    .string "我不确定这个是否能帮到你，\n"
    .string "不过还是给你吧。$"

LavenderTown_VolunteerPokemonHouse_Text_ReceivedPokeFluteFromMrFuji::
    .string "{PLAYER}从富士老人那里\n"
    .string "获得了宝可梦笛子。$"

LavenderTown_VolunteerPokemonHouse_Text_ExplainPokeFlute::
    .string "听见宝可梦笛子的声音，\n"
    .string "沉睡中的宝可梦会马上清醒。\p"
    .string "试着把它用在\n"
    .string "那些沉睡不醒的宝可梦身上。$"

LavenderTown_VolunteerPokemonHouse_Text_MustMakeRoomForThis::
    .string "你必须为这个腾出空间！$"

LavenderTown_VolunteerPokemonHouse_Text_HasPokeFluteHelpedYou::
    .string "富士老人：我的宝可梦笛子\n"
    .string "帮到你了吗？$"

LavenderTown_VolunteerPokemonHouse_Text_GrandPrizeDrawingClipped::
    .string "宝可梦爱好者杂志\n"
    .string "每月大抽奖！\p"
    .string "回函单在……\p"
    .string "没了！已经被剪掉了。\n"
    .string "一定是有人已经申请过了。$"

LavenderTown_VolunteerPokemonHouse_Text_PokemonMagazinesLineShelf::
    .string "宝可梦杂志在书架上摆了一排。\p"
    .string "深入宝可梦……\p"
    .string "宝可梦爱好者……$"

