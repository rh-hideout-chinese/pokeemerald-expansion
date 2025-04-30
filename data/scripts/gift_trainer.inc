MysteryGiftScript_VisitingTrainer::
	setvaddress MysteryGiftScript_VisitingTrainer
	special ValidateEReaderTrainer
	vgoto_if_eq VAR_RESULT, 0, MysteryGiftScript_VisitingTrainerArrived
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainerInstructions
	waitmessage
	waitbuttonpress
	release
	end

MysteryGiftScript_VisitingTrainerArrived:
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainerArrived
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftVisitingTrainerInstructions:
	.string "感谢使用\n"
	.string "神秘礼物系统。\p"
	.string "由于拥有神秘卡片\n"
	.string "你可以进行调查\l"
	.string "宝可梦商场。\p"
	.string "通过调查你可以邀请\n"
	.string "训练家去琉璃市。\p"
	.string "……让我给你一个\n"
	.string "调查的密码吧：\p"
	.string "“GIVE ME\n"
	.string "AWESOME TRAINER”\p"
	.string "把这个写在调查上并发送到\n"
	.string "无线通信系统。$"

sText_MysteryGiftVisitingTrainerArrived:
	.string "感谢使用\n"
	.string "神秘礼物系统。\p"
	.string "一位训练家已经来到\n"
	.string "琉璃市寻找你。\p"
	.string "系统你可以享受\n"
	.string "与训练家的战斗。\p"
	.string "你可以邀请其他训练家\n"
	.string "通过填写密码。\p"
	.string "试着找寻其他\n"
	.string "有用的密码吧。$"
