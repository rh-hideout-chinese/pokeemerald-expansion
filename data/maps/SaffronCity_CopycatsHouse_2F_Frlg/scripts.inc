SaffronCity_CopycatsHouse_2F_Frlg_MapScripts::
	.byte 0

SaffronCity_CopycatsHouse_2F_EventScript_Doduo::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DODUO, CRY_MODE_NORMAL
	msgbox SaffronCity_CopycatsHouse_2F_Text_Doduo
	waitmoncry
	release
	end

SaffronCity_CopycatsHouse_2F_EventScript_Doll::
	lock
	msgbox SaffronCity_CopycatsHouse_2F_Text_RareMonOnlyDoll
	release
	end

SaffronCity_CopycatsHouse_2F_EventScript_Copycat::
	lock
	faceplayer
	checkitem ITEM_POKE_DOLL
	goto_if_eq VAR_RESULT, TRUE, EventScript_MimicTutor
	checkplayergender
	call_if_eq VAR_RESULT, MALE, SaffronCity_CopycatsHouse_2F_EventScript_MimicPlayerMale
	call_if_eq VAR_RESULT, FEMALE, SaffronCity_CopycatsHouse_2F_EventScript_MimicPlayerFemale
	release
	end

SaffronCity_CopycatsHouse_2F_EventScript_MimicPlayerMale::
	msgbox SaffronCity_CopycatsHouse_2F_Text_MimickingFavoriteHobbyMale
	return

SaffronCity_CopycatsHouse_2F_EventScript_MimicPlayerFemale::
	msgbox SaffronCity_CopycatsHouse_2F_Text_MimickingFavoriteHobbyFemale
	return

SaffronCity_CopycatsHouse_2F_EventScript_Computer::
	msgbox SaffronCity_CopycatsHouse_2F_Text_MySecrets, MSGBOX_SIGN
	end

SaffronCity_CopycatsHouse_2F_EventScript_Game::
	msgbox SaffronCity_CopycatsHouse_2F_Text_MarioWearingABucket, MSGBOX_SIGN
	end

SaffronCity_CopycatsHouse_2F_Text_MimickingFavoriteHobbyMale::
    .string "{PLAYER}：嗨！\n"
    .string "你喜欢宝可梦吗？\p"
    .string "{PLAYER}：喔，不，我只是问问你罢了。\p"
    .string "{PLAYER}：嗯？\n"
    .string "你确实很厉害！\p"
    .string "模仿少女：嗯？快速模仿？\n"
    .string "对，那是我的爱好！$"

SaffronCity_CopycatsHouse_2F_Text_MimickingFavoriteHobbyFemale::
    .string "{PLAYER}：嗨。\n"
    .string "你一定热爱着宝可梦\p"
    .string "{PLAYER}：不，不是问我。\n"
    .string "我是在问你。\p"
    .string "{PLAYER}：再说一遍？\n"
    .string "你真古怪！\l"
    .string "模仿少女：嗯？快速模仿？\l"
    .string "那是我的最爱！$"

Text_MimicTeach::
    .string "哇塞！\n"
    .string "皮皮玩偶\p"
    .string "给我的？\n"
    .string "谢谢你！\p"
    .string "你想要什么？\n"
    .string "我能教给你模仿这个技能。$"

Text_MimicDeclined::
    .string "你不喜欢模仿？$"

Text_MimicWhichMon::
    .string "我真的很喜欢模仿！\n"
    .string "谁想要来学会这个技能？$"

Text_MimicTaughtMale::
    .string "{PLAYER}：嗨！\n"
    .string "首先要谢谢你！\p"
    .string "{PLAYER}：再说一遍？\p"
    .string "{PLAYER}：模仿我的动作\n"
    .string "很有意思吗？\p"
    .string "模仿少女：你敢打赌的吧！\n"
    .string "那真是太有意思了！$"

Text_MimicTaughtFemale::
    .string "{PLAYER}：嗨\n"
    .string "谢谢你为我做的一切！\p"
    .string "{PLAYER}：再说一遍？\p"
    .string "{PLAYER}：学我说话\n"
    .string "很有意思吗？\p"
    .string "模仿达人：你敢打赌吗？\n"
    .string "那真是太有意思了！$"

SaffronCity_CopycatsHouse_2F_Text_Doduo::
    .string "嘟嘟：嘻嘻！\p"
    .string "魔镜魔镜告诉我，\n"
    .string "谁是这个世界上最漂亮的人？$"

SaffronCity_CopycatsHouse_2F_Text_RareMonOnlyDoll::
    .string "这真是少见的宝可梦啊！\n"
    .string "嗯？这只是个玩偶！$"

SaffronCity_CopycatsHouse_2F_Text_MarioWearingABucket::
    .string "游戏里马力欧\n"
    .string "正在用头顶蘑菇！$"

SaffronCity_CopycatsHouse_2F_Text_MySecrets::
    .string "……\p"
    .string "我的秘密！\p"
    .string "我的特长：模仿！\n"
    .string "我的爱好：收集玩偶！\l"
    .string "我最喜欢的宝可梦：皮皮！$"

