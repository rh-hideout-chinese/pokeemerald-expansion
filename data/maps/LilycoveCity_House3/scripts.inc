LilycoveCity_House3_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_House3_OnTransition
	.byte 0

LilycoveCity_House3_OnTransition:
	random 4
	copyvar VAR_TEMP_1, VAR_RESULT
	end

LilycoveCity_House3_EventScript_PokefanF::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LilycoveCity_House3_EventScript_DeclinePokeblockLearn
	msgbox LilycoveCity_House3_Text_ExplainPokeblocks, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_DeclinePokeblockLearn::
	msgbox LilycoveCity_House3_Text_OhAreYouSure, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_Man::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_HappyToHaveQuadruplets, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_GameBoyKid1::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid2::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid3::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid4::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_WereDoingMultiBattle::
	msgbox LilycoveCity_House3_Text_GoingToWinMultiBattles, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereMixingRecords::
	msgbox LilycoveCity_House3_Text_LikeMixingAtRecordCorner, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereBlendingBerries::
	msgbox LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereDoingContest::
	msgbox LilycoveCity_House3_Text_GoingToEnterContest, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks:
    .string "啊，天哪，天哪，你是一个人旅行吗？\n但你真得很年轻！真不错！\p我的孩子也该\n好好向你学习！\p我？我是宝可方块专家，\p假如我认真起来，\n我就能混合出极棒的宝可方块。\p你想听我这个专家的\n指教吗？$"

LilycoveCity_House3_Text_OhAreYouSure:
    .string "哦？是吗？\p不要总是试图\n独自完成一切！$"

LilycoveCity_House3_Text_ExplainPokeblocks:
    .string "啊，好！你很聪明！\n虽然有点长，但你得竖起耳朵听好了！\p准备好了吗？\p如果看看宝可方块，\n你会发现它们都有一个细腻度。\p值越小，说明\n质量越好，要牢牢记住！\p好的宝可方块细腻度低，\n等级却高。\p比起普通宝可方块，一只宝可梦\n应该吃更多更好的宝可方块。\p还有一点很重要，\p如果想制作细腻的宝可方块，\n就得使用不同的树果。\p不要吝啬——树果的种类\n会影响到宝可方块细腻度。\p另外，\p混合树果的人越多，\n宝可方块就越细腻，\p因此你得叫上其他人\n一起来制作宝可方块。\p关于怎么制作好的宝可方块，\n这些就是你要知道的。\p如果每个人都有喜爱的宝可梦，\n细腻的宝可方块，\l幸福的家庭，世界会变得更美好。\p别放弃，亲爱的！$"

LilycoveCity_House3_Text_HappyToHaveQuadruplets:
    .string "妻子生下四胞胎的时候，\n我真的大吃一惊，\p但现在看着他们一起玩耍，\n我觉得很幸福。$"

LilycoveCity_House3_Text_GoingToWinMultiBattles:
    .string "我们在进行多人战斗，\n我肯定会赢的。$"

LilycoveCity_House3_Text_LikeMixingAtRecordCorner:
    .string "我们喜欢在联机中心\n混合物品，\p但究竟是什么混合起来了？$"

LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender:
    .string "我们要用树果混合器\n制作出超级宝可方块！$"

LilycoveCity_House3_Text_GoingToEnterContest:
    .string "我要让大家看看\n我强大的宝可梦，所以我们\l一起去参加华丽大赛。$"

