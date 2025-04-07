VerdanturfTown_FriendshipRatersHouse_MapScripts::
	.byte 0

VerdanturfTown_FriendshipRatersHouse_EventScript_FriendshipRater::
	lock
	faceplayer
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_SeeHowMuchPokemonLikesYou, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	switch VAR_RESULT
	case FRIENDSHIP_NONE, VerdanturfTown_FriendshipRatersHouse_EventScript_DetestsYou
	case FRIENDSHIP_1_TO_49, VerdanturfTown_FriendshipRatersHouse_EventScript_VeryWary
	case FRIENDSHIP_50_TO_99, VerdanturfTown_FriendshipRatersHouse_EventScript_NotUsedToYou
	case FRIENDSHIP_100_TO_149, VerdanturfTown_FriendshipRatersHouse_EventScript_GettingUsedToYou
	case FRIENDSHIP_150_TO_199, VerdanturfTown_FriendshipRatersHouse_EventScript_LikesYouQuiteALot
	case FRIENDSHIP_200_TO_254, VerdanturfTown_FriendshipRatersHouse_EventScript_VeryHappy
	case FRIENDSHIP_MAX, VerdanturfTown_FriendshipRatersHouse_EventScript_AdoresYou
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_DetestsYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_DetestsYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_VeryWary::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_VeryWary, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_NotUsedToYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_NotUsedToYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_GettingUsedToYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_GettingUsedToYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_LikesYouQuiteALot::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_LikesYouQuiteALot, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_VeryHappy::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_VeryHappy, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_AdoresYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_AdoresYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_Pikachu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_Pikachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VerdanturfTown_FriendshipRatersHouse_Text_SeeHowMuchPokemonLikesYou:
    .string "让我看看你的宝可梦，\n我能看出它对你的感情如何。\p哎，\n你的宝可梦…$"

VerdanturfTown_FriendshipRatersHouse_Text_AdoresYou:
    .string "它很敬仰你，\n非常非常喜欢你。\l看着它，我也很开心。$"

VerdanturfTown_FriendshipRatersHouse_Text_VeryHappy:
    .string "它看上去很高兴，\n明显很喜欢你。$"

VerdanturfTown_FriendshipRatersHouse_Text_LikesYouQuiteALot:
    .string "它挺喜欢你的，\n看上去还想再被宠一些。$"

VerdanturfTown_FriendshipRatersHouse_Text_GettingUsedToYou:
    .string "它开始习惯和你相处了，\n好像已经开始相信你。$"

VerdanturfTown_FriendshipRatersHouse_Text_NotUsedToYou:
    .string "它还不太习惯和你相处，\n很难说是喜欢你还是讨厌你。$"

VerdanturfTown_FriendshipRatersHouse_Text_VeryWary:
    .string "它的警惕心很强，\n眼神特别吓人。\l它一点也不喜欢你。$"

VerdanturfTown_FriendshipRatersHouse_Text_DetestsYou:
    .string "有些遗憾…\p你的宝可梦非常厌恶你。\n这没让你感到愧疚吗？$"

VerdanturfTown_FriendshipRatersHouse_Text_Pikachu:
    .string "皮卡丘：皮卡！皮卡！$"

