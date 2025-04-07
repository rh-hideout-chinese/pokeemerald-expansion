.set LOCALID_CAPT_STERN, 1
.set LOCALID_ARCHIE, 2
.set LOCALID_GRUNT_1, 3
.set LOCALID_GRUNT_2, 4

SlateportCity_OceanicMuseum_2F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_2F_EventScript_CaptStern::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, TRUE
	addobject LOCALID_GRUNT_1
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter
	waitmovement 0
	addobject LOCALID_GRUNT_2
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter
	waitmovement 0
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	call_if_eq VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts, MSGBOX_DEFAULT
	call_if_ne VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth
	call_if_eq VAR_FACING, DIR_WEST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_1, SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat
	msgbox SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_2, SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_GRUNT_1, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_GRUNT_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_MeddlingKid, MSGBOX_DEFAULT
	closemessage
	delay 35
	addobject LOCALID_ARCHIE
	applymovement LOCALID_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_ArchieWarning, MSGBOX_DEFAULT
	closemessage
	savebgm MUS_DUMMY
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	fadescreen FADE_FROM_BLACK
	delay 30
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_AQUA_GRUNTS
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_DEVON_PARTS
	call Common_EventScript_PlayerHandedOverTheItem
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	removeobject LOCALID_CAPT_STERN
	setflag FLAG_HIDE_ROUTE_110_TEAM_AQUA
	call_if_eq VAR_REGISTER_BIRCH_STATE, 0, SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch
	setflag FLAG_DELIVERED_DEVON_GOODS
	clearflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1
	fadescreen FADE_FROM_BLACK
	release
	end

SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch::
	setvar VAR_REGISTER_BIRCH_STATE, 1
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts::
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth::
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest::
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth:
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest:
	walk_up
	walk_left
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_Unused:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	delay_8
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter:
	walk_down
	walk_right
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated:
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_fast_down
	walk_in_place_faster_up
	step_end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_PressureExperiment::
	msgbox SlateportCity_OceanicMuseum_2F_Text_PressureExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_HoennModel::
	msgbox SlateportCity_OceanicMuseum_2F_Text_HoennModel, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_DeepSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SurfaceSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSTidalReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmarineReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmersibleReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSAnneReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron3::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts:
    .string "你好，你在找库斯诺吉？\n我就是。\p啊！那是我向得文的\n兹伏奇订购的部件吧？\p非常感谢！\n我们可以开始准备出航了。$"

SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts:
    .string "嘿嘿嘿，别急！\n那些部件是我们的！$"

SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou:
    .string "库斯诺吉馆长：什—什么？\n你们是什么人？$"

SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua:
    .string "我们是水舰队！\p我们老大想要那些部件！\n闭上嘴，乖乖把东西交出来！$"

SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat:
    .string "啊啊！\n竟然被小孩打败了！$"

SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious:
    .string "天啊，灾难啊…\n老大会暴走的…$"

SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis:
    .string "哼，为自己的无能哭泣吧！\n我来应付这家伙！$"

SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat:
    .string "什么？！\n我也输了！$"

SlateportCity_OceanicMuseum_2F_Text_MeddlingKid:
    .string "怎么办？不拿到部件的话，\n我们会有大麻烦的！\p啊，想不到竟会被个麻烦的\n小毛孩子妨碍了！$"

SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong:
    .string "我还在奇怪你们抢个部件怎么\n用了那么久，一上来就看到你们\l几个蠢货被个孩子收拾了。$"

SlateportCity_OceanicMuseum_2F_Text_ArchieWarning:
    .string "我们是热爱大海的\n水舰队！\p我就是水舰队的首领\n水梧桐！\p你为什么妨碍我们？\p…不，不可能！\n你不是火岩队的人吧？\p等等，这也不对，\n你的衣着和他们不一样。\p… … … … … …\n… … … … … …\p人类，宝可梦…所有的生命\n都因大海而存在，\p因此我们水舰队\n致力于扩展海洋。\p你也这么想吧？\n我们双肩上挑着沉重的担子。\p啊，好吧…\n对你这么大的孩子来说，要理解\l我们崇高的理想还太勉强了些。\p但我警告你，\n别再妨碍我们的计划，\p否则我会让你知道\n我们的厉害！\p好好记住！$"

SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs:
    .string "库斯诺吉馆长：你是…\n啊，是吗，你是{PLAYER}{KUN}…\p刚才的形势太紧张了！\n谢谢你救了我！\p噢，对了，我差点忘了\n你还带着得文送来的部件！$"

SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo:
    .string "库斯诺吉馆长：呼！\n没时间了！\p我们得赶快开始\n我们的海底探索了。\p再次谢谢你，不过\n我现在得走了！\p随便观赏一下\n我们的展品吧。$"

SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip:
    .string "我在这儿看到了一艘模型船，\p这让我想起了武斗镇附近的\n那艘被遗弃的海船……$"

SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum:
    .string "别在博物馆里面\n到处乱跑！$"

SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine:
    .string "哇，潜水艇真棒！\n我也想进里面看一看！$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1:
    .string "牌子上写着\n“水质样本 1”。\p海洋是连成一片的，\n但不同地域的海水并不相同。$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2:
    .string "牌子上写着\n“水质样本 2”。\p不同地域的海水\n含盐量也不同吗？$"

SlateportCity_OceanicMuseum_2F_Text_PressureExperiment:
    .string "一个橡皮球不断地\n收缩，扩张。\p“在大海中，水由于\n自身重量形成内部的压力。\p浅水中这一压力\n并不明显，\p但在非常深的水里，\n一小片地方的水压\l甚至可以达到上万吨。”$"

SlateportCity_OceanicMuseum_2F_Text_HoennModel:
    .string "“丰缘地区模型”\p是丰缘地区的\n微缩景观。\p未白镇在哪儿呢？$"

SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay:
    .string "海水循环的演示。\p“在海地附近，海水由于\n温度和含盐量的不同，\l形成了环流。”$"

SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay:
    .string "海水循环的演示。\p“在洋面上，海水\n被风吹动，形成洋流。”$"

SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica:
    .string "“正在库斯诺吉的船厂建造的\p破浪号游船的\n等比例模型。”$"

SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica:
    .string "“潜艇探险者1号\p洋底探险用\n高级潜水艇的模型。”$"

SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica:
    .string "“潜水者\p海底探险用的坚固的\n无人探测器的模型。”$"

SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica:
    .string "“环游世界的\p豪华定期船\nS.S.安尼的模型。”$"

