.set LOCALID_CURATOR, 2
.set LOCALID_ARTIST_2, 8

LilycoveCity_LilycoveMuseum_1F_MapScripts::
	.byte 0

LilycoveCity_LilycoveMuseum_1F_EventScript_Greeter::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_WelcomeToLilycoveMuseum, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Curator::
	lockall
	applymovement LOCALID_CURATOR, Common_Movement_FacePlayer
	message LilycoveCity_LilycoveMuseum_1F_Text_ImCuratorHaveYouViewedOurPaintings
	waitmessage
	multichoice 20, 8, MULTI_VIEWED_PAINTINGS, TRUE
	goto_if_eq VAR_RESULT, 0, LilycoveCity_LilycoveMuseum_1F_EventScript_SawPaintings
	goto_if_eq VAR_RESULT, 1, LilycoveCity_LilycoveMuseum_1F_EventScript_NotYet
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_NotYet::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_NotDisturbYouTakeYourTime, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_SawPaintings::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_HaveYouAnInterestInPaintings, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LilycoveCity_LilycoveMuseum_1F_EventScript_NotInterested
	goto_if_eq VAR_RESULT, YES, LilycoveCity_LilycoveMuseum_1F_EventScript_InterestedInPaintings
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_NotInterested::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_HonoredYoudVisitInSpiteOfThat, MSGBOX_SIGN
	releaseall
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_InterestedInPaintings::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ExcellentCanYouComeWithMe, MSGBOX_SIGN
	applymovement LOCALID_CURATOR, LilycoveCity_LilycoveMuseum_1F_Movement_CuratorEnterStairs
	waitmovement 0
	removeobject LOCALID_CURATOR
	switch VAR_FACING
	case DIR_NORTH, LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorNorth
	case DIR_WEST, LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorWest
	case DIR_EAST, LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorEast
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorNorth::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorNorth
	waitmovement 0
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_2F, 11, 8
	waitstate
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorWest::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorWest
	waitmovement 0
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_2F, 11, 8
	waitstate
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorEast::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorEast
	waitmovement 0
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_2F, 11, 8
	waitstate
	end

LilycoveCity_LilycoveMuseum_1F_Movement_CuratorEnterStairs:
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorWest:
	walk_left
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorEast:
	walk_right
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorNorth:
	walk_up
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_EventScript_OldPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_VeryOldPainting, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FantasyPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_OddLandscapeFantasticScenery, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_WomanPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBeautifulWoman, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_LegendaryPokemonPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfLegendaryPokemon, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_GrassPokemonPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfGrassPokemon, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_BerryPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBerries, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_EventScript_BirdSculpture::
	msgbox LilycoveCity_LilycoveMuseum_Text_BirdPokemonSculptureReplica, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_PokeBallSculpture::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_BigPokeBallCarvedFromStone, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_StoneTablet::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_StoneTabletWithAncientText, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_SchoolKidM::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_MustntForgetLoveForFineArts, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Artist1::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ThisMuseumIsInspiration, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_NinjaBoy::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ThisLadyIsPretty, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Woman1::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ThisPokemonIsAdorable, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Woman2::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_HeardMuseumGotNewPaintings, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_PsychicM::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_CuratorHasBeenCheerful, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Artist2::
	lock
	faceplayer
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_AimToSeeGreatPaintings, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARTIST_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FatMan::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_MuseumTouristDestination, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_Text_WelcomeToLilycoveMuseum:
    .string "欢迎来到水静市博物馆，\p请随意观赏\n我们这里优秀的\l宝可梦艺术品。$"

LilycoveCity_LilycoveMuseum_1F_Text_ImCuratorHaveYouViewedOurPaintings:
    .string "我是这个美术馆的\n馆长，\p很高兴能在这里\n看到你这样的年轻人。\p你看过我们的\n展品了吗？$"

LilycoveCity_LilycoveMuseum_1F_Text_NotDisturbYouTakeYourTime:
    .string "啊，我不打扰你了，\n尽情地观赏吧。$"

LilycoveCity_LilycoveMuseum_1F_Text_HaveYouAnInterestInPaintings:
    .string "嗯？我想你\n是宝可梦训练师吧。\p你也喜欢\n绘画吗？$"

LilycoveCity_LilycoveMuseum_1F_Text_HonoredYoudVisitInSpiteOfThat:
    .string "哦…\p尽管那样，还是\n很感谢你能来参观。$"

LilycoveCity_LilycoveMuseum_1F_Text_ExcellentCanYouComeWithMe:
    .string "啊，很好！\n你喜欢绘画！\p那么，可以请你跟我来吗？$"

LilycoveCity_LilycoveMuseum_1F_Text_VeryOldPainting:
    .string "这幅画已经有些年代了，\n到处都开始剥落。$"

LilycoveCity_LilycoveMuseum_1F_Text_OddLandscapeFantasticScenery:
    .string "一幅画着奇妙景色的\n风景画。$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBeautifulWoman:
    .string "画着一个美丽的妇女\n微笑着看着膝上的宝可梦。$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfLegendaryPokemon:
    .string "传说生活在很久以前的\n宝可梦的画，\p是画家凭借想象\n画出来的。$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfGrassPokemon:
    .string "画着草系宝可梦\n在微风中轻轻摇摆。\p看上去它们非常喜欢\n轻风的抚摸。$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBerries:
    .string "画着诱人的树果。\p看着这幅画，口水都流下来了！$"

LilycoveCity_LilycoveMuseum_Text_BirdPokemonSculptureReplica:
    .string "是一件著名雕塑的仿制品，\p描绘了一只古代飞行系宝可梦。$"

LilycoveCity_LilycoveMuseum_1F_Text_BigPokeBallCarvedFromStone:
    .string "用一块黑色石头雕刻成的\n巨大精灵球，\p显然是过去\n节庆时使用的。$"

LilycoveCity_LilycoveMuseum_1F_Text_StoneTabletWithAncientText:
    .string "是一块刻着宝可梦，\n密密麻麻写着\l不认识的古文字的\l巨大石匾。$"

LilycoveCity_LilycoveMuseum_1F_Text_WorksOfMagnificence:
    .string "嗯…\n多么华丽啊…$"

LilycoveCity_LilycoveMuseum_1F_Text_MustntForgetLoveForFineArts:
    .string "和宝可梦一同战斗很有趣，\n我承认，\p但人们不能忘记\n对艺术的热爱。$"

LilycoveCity_LilycoveMuseum_1F_Text_ThisMuseumIsInspiration:
    .string "这家美术博物馆…这里有\n很多优秀的画作，\p馆长也是个杰出的人。\p对我们这样的艺术家来说，\n这间博物馆总能给我们带来灵感。$"

LilycoveCity_LilycoveMuseum_1F_Text_ThisLadyIsPretty:
    .string "这位女士真漂亮！\n就像我妈妈一样！$"

LilycoveCity_LilycoveMuseum_1F_Text_ThisPokemonIsAdorable:
    .string "这只宝可梦真可爱！\n就像我们的小宝宝一样！$"

LilycoveCity_LilycoveMuseum_1F_Text_HeardMuseumGotNewPaintings:
    .string "听说这间美术博物馆\n弄了些新画作，\p所以我赶来了。\p那些新画\n放在二楼吗？$"

LilycoveCity_LilycoveMuseum_1F_Text_CuratorHasBeenCheerful:
    .string "最近馆长总是\n兴高采烈，\p我敢说他身上\n肯定发生了什么好事。$"

LilycoveCity_LilycoveMuseum_1F_Text_AimToSeeGreatPaintings:
    .string "我立志要来这里\n观赏大量作品学习绘画，\p我一直梦想某一天\n我的画作也能挂在这里。$"

LilycoveCity_LilycoveMuseum_1F_Text_MuseumTouristDestination:
    .string "美术博物馆已经成为\n一个旅游景点，\p这对水静市来说也是好消息…\n不，是对整个丰缘地区都是好消息！\p我听说——楼上的画全部\n属于同一个训练师。$"

