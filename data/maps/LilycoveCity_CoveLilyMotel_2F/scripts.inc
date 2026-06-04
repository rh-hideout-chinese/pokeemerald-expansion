LilycoveCity_CoveLilyMotel_2F_MapScripts::
	.byte 0

LilycoveCity_CoveLilyMotel_2F_EventScript_GameDesigner::
	lock
	faceplayer
	call_if_unset FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex
	call_if_set FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	specialvar VAR_RESULT, HasAllHoennMons
	goto_if_eq VAR_RESULT, TRUE, LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex, MSGBOX_DEFAULT
	return

LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare::
	setflag FLAG_TEMP_2
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	goto LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma::
	message LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	special Special_ShowDiploma
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Programmer::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GraphicArtist::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_FatMan::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Woman::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GameBoyKid::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_IN_LILYCOVE, LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_IN_LILYCOVE
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy, MSGBOX_DEFAULT
	release
	end

LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex:
    .string "我是游戏设计师。\p哦，是吗？\n你在收集宝可梦图鉴？\p完成它并不容易，\n但也别放弃。\p如果你完成了，\n就来给我看看吧。$"

LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis:
    .string "哇！太棒了！\n真的太棒了！\p这个宝可梦图鉴完成了！\n你一定很喜欢宝可梦！\p我好感动！\p我给你一件能彰显出\n你的成绩的东西吧！$"

LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer:
    .string "我？你在跟我说话？\n我是程序员，\p我想知道这儿的老虎机\n是怎么样的。$"

LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist:
    .string "我是美术设计师！\n丰缘地区的宝可梦很有趣吧？$"

LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute:
    .string "泳圈女孩很可爱，不是吗？\n跟这么可爱的泳圈女孩对战……\p哇，太棒了！\p还有双胞胎！也很可爱不是吗？\n跟双胞胎2对2对战……\p哇，那是难以形容的快乐！$"

LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart:
    .string "海风轻轻地挑逗着我的心。\n在这里的感觉真好！$"

LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy:
    .string "你永远不知道什么时候\n会碰上挑战的人，\p所以我出门的时候\n从来都带着GBA。$"

LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles:
    .string "亚希达： …… …… ……\n…… …… ……Zzz……\p…… …… ……嗯？！\n哦，抱歉抱歉！我在打盹了！\p我是来看看\n宝可梦华丽大赛的。\p虽说看上去也确实挺有趣的，\n但是……\p像我这样的纯粹主义者——\n更钟爱对战与强大的训练家。\p但这只是就我而言。\p{PLAYER}{KUN}，希望你能享受一切，\n包括道馆，华丽大赛，对战帐篷，\l所有的一切！$"

LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy:
    .string "亚希达：我想赢得华丽大赛\n也需要策略。\p要我说，制定华丽大赛的战略\n也是成为一个优秀训练家的途径之一。$"

