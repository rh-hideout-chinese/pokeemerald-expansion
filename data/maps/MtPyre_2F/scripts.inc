MtPyre_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, CaveHole_FixCrackedGround
	map_script MAP_SCRIPT_ON_RESUME, MtPyre_2F_SetHoleWarp
	.byte 0

MtPyre_2F_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_MT_PYRE_1F
	end

MtPyre_2F_EventScript_Woman::
	msgbox MtPyre_2F_Text_MemoriesOfSkitty, MSGBOX_NPC
	end

MtPyre_2F_EventScript_PokefanM::
	msgbox MtPyre_2F_Text_TumbledFromFloorAbove, MSGBOX_NPC
	end

MtPyre_2F_EventScript_Mark::
	trainerbattle_single TRAINER_MARK, MtPyre_2F_Text_MarkIntro, MtPyre_2F_Text_MarkDefeat
	msgbox MtPyre_2F_Text_MarkPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Luke::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_LukeIntro, MtPyre_2F_Text_LukeDefeat, MtPyre_2F_Text_LukeNotEnoughMons
	msgbox MtPyre_2F_Text_LukePostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Dez::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_DezIntro, MtPyre_2F_Text_DezDefeat, MtPyre_2F_Text_DezNotEnoughMons
	msgbox MtPyre_2F_Text_DezPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Leah::
	trainerbattle_single TRAINER_LEAH, MtPyre_2F_Text_LeahIntro, MtPyre_2F_Text_LeahDefeat
	msgbox MtPyre_2F_Text_LeahPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Zander::
	trainerbattle_single TRAINER_ZANDER, MtPyre_2F_Text_ZanderIntro, MtPyre_2F_Text_ZanderDefeat
	msgbox MtPyre_2F_Text_ZanderPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_Text_MemoriesOfSkitty:
    .string "一想到我亲爱的向尾喵……\n眼睛里总会不知不觉地蓄满泪水。$"

MtPyre_2F_Text_TumbledFromFloorAbove:
    .string "啊噢……地上\n到处都是洞，\p我一个不小心\n从楼上掉下来了。$"

MtPyre_2F_Text_MarkIntro:
    .string "嘿！你也是来找宝可梦的吗？\n一直跟着我干什么！你这无礼的家伙！$"

MtPyre_2F_Text_MarkDefeat:
    .string "啊呀呀呀！\n抱歉，请原谅我！$"

MtPyre_2F_Text_MarkPostBattle:
    .string "这儿少有人来，所以\n我想应该有珍稀宝可梦。$"

MtPyre_2F_Text_LukeIntro:
    .string "辉：我们来这儿试胆子。\p呵呵，如果她看到我有多棒，\n一定会迷恋上我的！\p没错！我会让她知道\n我有多厉害！$"

MtPyre_2F_Text_LukeDefeat:
    .string "辉：哎哟！$"

MtPyre_2F_Text_LukePostBattle:
    .string "辉：好吧，我们输了，但是没关系！\n我就在这里，就算是试胆子，\l也没什么可害怕的！$"

MtPyre_2F_Text_LukeNotEnoughMons:
    .string "辉：想跟我战斗的话\n就多带些宝可梦来，\p否则我就不能让我的她知道\n我有多帅了！$"

MtPyre_2F_Text_DezIntro:
    .string "真子：我与男友一起\n来这儿试胆子。\p虽然确实很害怕，但只要有他\n在我身边就都没什么。\p没错！我要打败你，\n让他看起来更帅！$"

MtPyre_2F_Text_DezDefeat:
    .string "真子：哇啊啊啊！好可怕！$"

MtPyre_2F_Text_DezPostBattle:
    .string "真子：我们之间感情这么好，\n输了也不介意！$"

MtPyre_2F_Text_DezNotEnoughMons:
    .string "真子：如果想挑战我们，你至少\n得带两只宝可梦。\p我的男友很强，\n仅仅一只宝可梦没用的喔。$"

MtPyre_2F_Text_LeahIntro:
    .string "生面孔呢……\n在什么都没发生前快离开！$"

MtPyre_2F_Text_LeahDefeat:
    .string "哼……\n你还挺难对付嘛。$"

MtPyre_2F_Text_LeahPostBattle:
    .string "从我曾祖母时代起，我们家族的人\n便是一直这里的训练家……\p守护这座山是\n我的责任……$"

MtPyre_2F_Text_ZanderIntro:
    .string "呀啊啊啊！！\n我好害怕啊！$"

MtPyre_2F_Text_ZanderDefeat:
    .string "不——！\n我输了！$"

MtPyre_2F_Text_ZanderPostBattle:
    .string "每次看到什么东西活动\n我就会被吓一跳……\p我真不该来这里训练……$"

