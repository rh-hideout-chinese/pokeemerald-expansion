BattleFrontier_BattlePyramidFloor_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattlePyramidFloor_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidFloor_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePyramidFloor_OnTransition
	.byte 0

BattleFrontier_BattlePyramidFloor_OnFrame:
	map_script_2 VAR_TEMP_D, 1, BattleFrontier_BattlePyramidFloor_EventScript_UpdateLight
	map_script_2 VAR_TEMP_PLAYING_PYRAMID_MUSIC, 0, BattleFrontier_BattlePyramidFloor_EventScript_PlayPyramidMusic
	map_script_2 VAR_TEMP_F, 1, BattleFrontier_BattlePyramidFloor_EventScript_ShowMapName
	.2byte 0

BattleFrontier_BattlePyramidFloor_EventScript_UpdateLight::
	lockall
	@ pyramid_updatelight, cant use macro because it straddles the loop
	setvar VAR_0x8004, BATTLE_PYRAMID_FUNC_UPDATE_LIGHT
	setvar VAR_0x8005, 4
	setvar VAR_0x8006, PYRAMID_LIGHT_INCR_RADIUS
	setvar VAR_0x8007, SE_SAVE
	setvar VAR_RESULT, 0
BattleFrontier_BattlePyramidFloor_EventScript_UpdateLightLoop::
	special CallBattlePyramidFunction
	delay 2
	goto_if_ne VAR_RESULT, 2, BattleFrontier_BattlePyramidFloor_EventScript_UpdateLightLoop
	setvar VAR_TEMP_D, 0
	releaseall
	end

BattleFrontier_BattlePyramidFloor_EventScript_ShowMapName::
	special ShowMapNamePopup
	setvar VAR_TEMP_F, 0
	end

BattleFrontier_BattlePyramidFloor_EventScript_PlayPyramidMusic::
	playbgm MUS_B_PYRAMID, FALSE
	setvar VAR_TEMP_PLAYING_PYRAMID_MUSIC, 1
	end

BattleFrontier_BattlePyramidFloor_OnResume:
	pyramid_setfloorpal
	frontier_getstatus
	switch VAR_TEMP_CHALLENGE_STATUS
	case 0, BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge
	case CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramid_EventScript_WarpToLobby
	case CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, B_OUTCOME_LOST, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	goto_if_eq VAR_RESULT, B_OUTCOME_DREW, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	goto_if_eq VAR_RESULT, B_OUTCOME_FORFEITED, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	frontier_isbattletype BATTLE_TYPE_TRAINER  @ VAR_RESULT seems to be ignored here
	setvar VAR_TEMP_D, 1
BattleFrontier_BattlePyramidFloor_EventScript_ResetParty::
	pyramid_resetparty
	end

BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
	pyramid_set PYRAMID_DATA_TRAINER_FLAGS, 255
BattleFrontier_BattlePyramid_EventScript_WarpToLobby::
	pyramid_updatelight 0, PYRAMID_LIGHT_SET_RADIUS
	pyramid_clearhelditems
	special HealPlayerParty
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_LOBBY, 7, 13
	waitstate
	end

BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge::
	pyramid_save CHALLENGE_STATUS_SAVING
	special SavePlayerParty
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	pyramid_settrainers
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidFloor_OnTransition:
	call BattleFrontier_BattlePyramidFloor_EventScript_SetLightRadius
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidFloor_EventScript_SetLightRadius::
	pyramid_updatelight 32, PYRAMID_LIGHT_SET_RADIUS
	return

BattlePyramid_WarpToNextFloor::
	call BattleFrontier_EventScript_IncrementWinStreak
	frontier_get FRONTIER_DATA_BATTLE_NUM  @ Floor number
	addvar VAR_RESULT, 1
	frontier_set FRONTIER_DATA_BATTLE_NUM, VAR_RESULT
	goto_if_eq VAR_RESULT, 7, BattlePyramid_WarpToTop
	pyramid_seedfloor
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_RESULT, 0
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR, 1, 1
	waitstate
	end

BattlePyramid_WarpToTop::
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_TOP, 17, 17
	waitstate
	end

@ TRAINER_PHILLIP is used as a placeholder
BattlePyramid_TrainerBattle::
	trainerbattle TRAINER_BATTLE_HILL, OBJ_ID_NONE, TRAINER_PHILLIP, BattleFacility_TrainerBattle_PlaceholderText, BattleFacility_TrainerBattle_PlaceholderText, NULL, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, FALSE, FALSE, FALSE
	pyramid_showhint
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattlePyramid_FindItemBall::
	pyramid_setitem
	callstd STD_FIND_ITEM
	goto_if_eq VAR_0x8007, 0, BattlePyramid_FindItemBallEnd
	pyramid_hideitem
BattlePyramid_FindItemBallEnd::
	end

BattlePyramid_Retire::
	goto BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost

@ Also used by Trainer Hill
BattleFacility_TrainerBattle_PlaceholderText::
    .string "测试信息。$"

gText_BattlePyramidConfirmRest::
    .string "要中断对战金字塔的探索\n需要先进行存档,\l可以吗？$"

gText_BattlePyramidConfirmRetire::
    .string "你确实要中断\n金字塔的探索吗？$"

BattlePyramid_Text_ExitHintUp1::
    .string "本层的出口方向是：\n{UP_ARROW}$"

BattlePyramid_Text_ExitHintLeft1::
    .string "本层的出口方向是：\n{LEFT_ARROW}$"

BattlePyramid_Text_ExitHintRight1::
    .string "本层的出口方向是：\n{RIGHT_ARROW}$"

BattlePyramid_Text_ExitHintDown1::
    .string "本层的出口方向是：\n{DOWN_ARROW}$"

BattlePyramid_Text_ExitHintUp2::
    .string "出口位于本层的\n{UP_ARROW} 方向。$"

BattlePyramid_Text_ExitHintLeft2::
    .string "出口位于本层的\n{LEFT_ARROW} 方向。$"

BattlePyramid_Text_ExitHintRight2::
    .string "出口位于本层的\n{RIGHT_ARROW} 方向。$"

BattlePyramid_Text_ExitHintDown2::
    .string "出口位于本层的\n{DOWN_ARROW} 方向。$"

BattlePyramid_Text_ExitHintUp3::
    .string "出口在通过\n{UP_ARROW} 的路上。$"

BattlePyramid_Text_ExitHintLeft3::
    .string "出口在通过\n{LEFT_ARROW} 的路上。$"

BattlePyramid_Text_ExitHintRight3::
    .string "出口在通过\n{RIGHT_ARROW} 的路上。$"

BattlePyramid_Text_ExitHintDown3::
    .string "出口在通过\n{DOWN_ARROW} 的路上。$"

BattlePyramid_Text_ExitHintUp4::
    .string "在本层，出口位于\n{UP_ARROW} 方向的某个位置。$"

BattlePyramid_Text_ExitHintLeft4::
    .string "在本层，出口位于\n{LEFT_ARROW} 方向的某个位置。$"

BattlePyramid_Text_ExitHintRight4::
    .string "在本层，出口位于\n{RIGHT_ARROW} 方向的某个位置。$"

BattlePyramid_Text_ExitHintDown4::
    .string "在本层，出口位于\n{DOWN_ARROW} 方向的某个位置。$"

BattlePyramid_Text_ExitHintUp5::
    .string "出口吗？\n在 {UP_ARROW} 。$"

BattlePyramid_Text_ExitHintLeft5::
    .string "出口吗？\n在 {LEFT_ARROW} 。$"

BattlePyramid_Text_ExitHintRight5::
    .string "出口吗？\n在 {RIGHT_ARROW} 。$"

BattlePyramid_Text_ExitHintDown5::
    .string "出口吗？\n在 {DOWN_ARROW} 。$"

BattlePyramid_Text_ExitHintUp6::
    .string "出口出现在\n{UP_ARROW} 方向。$"

BattlePyramid_Text_ExitHintLeft6::
    .string "出口出现在\n{LEFT_ARROW} 方向。$"

BattlePyramid_Text_ExitHintRight6::
    .string "出口出现在\n{RIGHT_ARROW} 方向。$"

BattlePyramid_Text_ExitHintDown6::
    .string "出口出现在\n{DOWN_ARROW} 方向。$"

BattlePyramid_Text_EightItemsRemaining1::
    .string "你在寻找道具吗？\p还有8个道具\n没找到呢！$"

BattlePyramid_Text_SevenItemsRemaining1::
    .string "你在寻找道具吗？\p还有7个道具\n没找到呢！$"

BattlePyramid_Text_SixItemsRemaining1::
    .string "你在寻找道具吗？\p还有6个道具\n没找到呢！$"

BattlePyramid_Text_FiveItemsRemaining1::
    .string "你在寻找道具吗？\p还有5个道具\n没找到呢！$"

BattlePyramid_Text_FourItemsRemaining1::
    .string "你在寻找道具吗？\p还有4个道具\n没找到呢！$"

BattlePyramid_Text_ThreeItemsRemaining1::
    .string "你在寻找道具吗？\p还有3个道具\n没找到呢！$"

BattlePyramid_Text_TwoItemsRemaining1::
    .string "你在寻找道具吗？\p还有2个道具\n没找到呢！$"

BattlePyramid_Text_OneItemRemaining1::
    .string "你在寻找道具吗？\p还有1个道具\n没找到呢！$"

BattlePyramid_Text_ZeroItemsRemaining1::
    .string "你在寻找道具吗？\p这儿已经没有道具\n可以寻找的了。$"

BattlePyramid_Text_EightItemsRemaining2::
    .string "因为你获胜，那我就告诉你\n一个秘密做奖励吧！\p在这里共有\n8个道具哦！$"

BattlePyramid_Text_SevenItemsRemaining2::
    .string "因为你获胜，那我就告诉你\n一个秘密做奖励吧！\p在这里共有\n7个道具哦！$"

BattlePyramid_Text_SixItemsRemaining2::
    .string "因为你获胜，那我就告诉你\n一个秘密做奖励吧！\p在这里共有\n6个道具哦！$"

BattlePyramid_Text_FiveItemsRemaining2::
    .string "因为你获胜，那我就告诉你\n一个秘密做奖励吧！\p在这里共有\n5个道具哦！$"

BattlePyramid_Text_FourItemsRemaining2::
    .string "因为你获胜，那我就告诉你\n一个秘密做奖励吧！\p在这里共有\n4个道具哦！$"

BattlePyramid_Text_ThreeItemsRemaining2::
    .string "因为你获胜，那我就告诉你\n一个秘密做奖励吧！\p在这里共有\n3个道具哦！$"

BattlePyramid_Text_TwoItemsRemaining2::
    .string "因为你获胜，那我就告诉你\n一个秘密做奖励吧！\p在这里共有\n2个道具哦！$"

BattlePyramid_Text_OneItemRemaining2::
    .string "因为你获胜，那我就告诉你\n一个秘密做奖励吧！\p在这里还有\n1个道具哦！$"

BattlePyramid_Text_ZeroItemsRemaining2::
    .string "因为你获胜，那我就告诉你\n一个秘密做奖励吧！\p这里已经没有\n任何道具了！$"

BattlePyramid_Text_EightItemsRemaining3::
    .string "你的包包还能放下几个道具？\p我估计，在这一层还有\n8个道具。$"

BattlePyramid_Text_SevenItemsRemaining3::
    .string "你的包包还能放下几个道具？\p我估计，在这一层还有\n7个道具。$"

BattlePyramid_Text_SixItemsRemaining3::
    .string "你的包包还能放下几个道具？\p我估计，在这一层还有\n6个道具。$"

BattlePyramid_Text_FiveItemsRemaining3::
    .string "你的包包还能放下几个道具？\p我估计，在这一层还有\n5个道具。$"

BattlePyramid_Text_FourItemsRemaining3::
    .string "你的包包还能放下几个道具？\p我估计，在这一层还有\n4个道具。$"

BattlePyramid_Text_ThreeItemsRemaining3::
    .string "你的包包还能放下几个道具？\p我估计，在这一层还有\n3个道具。$"

BattlePyramid_Text_TwoItemsRemaining3::
    .string "你的包包还能放下几个道具？\p我估计，在这一层还有\n2个道具。$"

BattlePyramid_Text_OneItemRemaining3::
    .string "你的包包还能放下几个道具？\p我估计，在这一层可能只剩\n1个道具了。$"

BattlePyramid_Text_ZeroItemsRemaining3::
    .string "你的包包还能放下几个道具？\p我估计，这一层已经没有\n道具可以找了。$"

BattlePyramid_Text_EightItemsRemaining4::
    .string "你真强！\n给你个提示吧！\p在地面上有\n8个道具哦！$"

BattlePyramid_Text_SevenItemsRemaining4::
    .string "你真强！\n给你个提示吧！\p在地面上有\n7个道具哦！$"

BattlePyramid_Text_SixItemsRemaining4::
    .string "你真强！\n给你个提示吧！\p在地面上有\n6个道具哦！$"

BattlePyramid_Text_FiveItemsRemaining4::
    .string "你真强！\n给你个提示吧！\p在地面上有\n5个道具哦！$"

BattlePyramid_Text_FourItemsRemaining4::
    .string "你真强！\n给你个提示吧！\p在地面上有\n4个道具哦！$"

BattlePyramid_Text_ThreeItemsRemaining4::
    .string "你真强！\n给你个提示吧！\p在地面上有\n3个道具哦！$"

BattlePyramid_Text_TwoItemsRemaining4::
    .string "你真强！\n给你个提示吧！\p在地面上有\n2个道具哦！$"

BattlePyramid_Text_OneItemRemaining4::
    .string "你真强！\n给你个提示吧！\p在地面上有\n1个道具哦！$"

BattlePyramid_Text_ZeroItemsRemaining4::
    .string "你真强！\n给你个提示吧！\p地面上已经没有\n任何道具了。$"

BattlePyramid_Text_EightItemsRemaining5::
    .string "在这层塔里，\n我听说有8个道具……$"

BattlePyramid_Text_SevenItemsRemaining5::
    .string "在这层塔里，\n我听说有7个道具……$"

BattlePyramid_Text_SixItemsRemaining5::
    .string "在这层塔里，\n我听说有6个道具……$"

BattlePyramid_Text_FiveItemsRemaining5::
    .string "在这层塔里，\n我听说有5个道具……$"

BattlePyramid_Text_FourItemsRemaining5::
    .string "在这层塔里，\n我听说有4个道具……$"

BattlePyramid_Text_ThreeItemsRemaining5::
    .string "在这层塔里，\n我听说有3个道具……$"

BattlePyramid_Text_TwoItemsRemaining5::
    .string "在这层塔里，\n我听说有2个道具……$"

BattlePyramid_Text_OneItemRemaining5::
    .string "在这层塔里，\n我听说有1个道具……$"

BattlePyramid_Text_ZeroItemsRemaining5::
    .string "在这层塔里，\n我听说这儿没道具……$"

BattlePyramid_Text_EightItemsRemaining6::
    .string "你有没有搜集道具呢？\p我认为这一层应该有\n8个道具吧。$"

BattlePyramid_Text_SevenItemsRemaining6::
    .string "你有没有搜集道具呢？\p我认为这一层应该有\n7个道具吧。$"

BattlePyramid_Text_SixItemsRemaining6::
    .string "你有没有搜集道具呢？\p我认为这一层应该有\n6个道具吧。$"

BattlePyramid_Text_FiveItemsRemaining6::
    .string "你有没有搜集道具呢？\p我认为这一层应该有\n5个道具吧。$"

BattlePyramid_Text_FourItemsRemaining6::
    .string "你有没有搜集道具呢？\p我认为这一层应该有\n4个道具吧。$"

BattlePyramid_Text_ThreeItemsRemaining6::
    .string "你有没有搜集道具呢？\p我认为这一层应该有\n3个道具吧。$"

BattlePyramid_Text_TwoItemsRemaining6::
    .string "你有没有搜集道具呢？\p我认为这一层应该有\n2个道具吧。$"

BattlePyramid_Text_OneItemRemaining6::
    .string "你有没有搜集道具呢？\p我认为这一层应该还有\n1个道具吧。$"

BattlePyramid_Text_ZeroItemsRemaining6::
    .string "你有没有搜集道具呢？\p我认为这一层应该\n没有道具了。$"

BattlePyramid_Text_SevenTrainersRemaining1::
    .string "你是很强！\p可还有7个比我\n更强的训练家等着你！$"

BattlePyramid_Text_SixTrainersRemaining1::
    .string "你是很强！\p可还有6个比我\n更强的训练家等着你！$"

BattlePyramid_Text_FiveTrainersRemaining1::
    .string "你是很强！\p可还有5个比我\n更强的训练家等着你！$"

BattlePyramid_Text_FourTrainersRemaining1::
    .string "你是很强！\p可还有4个比我\n更强的训练家等着你！$"

BattlePyramid_Text_ThreeTrainersRemaining1::
    .string "你是很强！\p可还有3个比我\n更强的训练家等着你！$"

BattlePyramid_Text_TwoTrainersRemaining1::
    .string "你是很强！\p可还有2个比我\n更强的训练家等着你！$"

BattlePyramid_Text_OneTrainersRemaining1::
    .string "你是很强！\p可还有1个比我\n更强的训练家等着你！$"

BattlePyramid_Text_ZeroTrainersRemaining1::
    .string "你真强！\p现在已经没有人\n能够打败你了！$"

BattlePyramid_Text_SevenTrainersRemaining2::
    .string "真不幸！\p后面还有7位训练家！\n他们中或许有人比你弱！$"

BattlePyramid_Text_SixTrainersRemaining2::
    .string "真不幸！\p后面还有6位训练家！\n他们中或许有人比你弱！$"

BattlePyramid_Text_FiveTrainersRemaining2::
    .string "真不幸！\p后面还有5位训练家！\n他们中或许有人比你弱！$"

BattlePyramid_Text_FourTrainersRemaining2::
    .string "真不幸！\p后面还有4位训练家！\n他们中或许有人比你弱！$"

BattlePyramid_Text_ThreeTrainersRemaining2::
    .string "真不幸！\p后面还有3位训练家！\n他们中或许有人比你弱！$"

BattlePyramid_Text_TwoTrainersRemaining2::
    .string "真不幸！\p后面还有2位训练家！\n他们中或许有人比你弱！$"

BattlePyramid_Text_OneTrainersRemaining2::
    .string "真不幸！\p后面还有1位训练家！\n他或许比你弱！$"

BattlePyramid_Text_ZeroTrainersRemaining2::
    .string "真不幸！\p后面已经没有训练家\n可以和你一起对战了。$"

BattlePyramid_Text_SevenTrainersRemaining3::
    .string "真是一场漂亮的对战！\p本层还有7位训练家\n你能打败他们吧？$"

BattlePyramid_Text_SixTrainersRemaining3::
    .string "真是一场漂亮的对战！\p本层还有6位训练家\n你能打败他们吧？$"

BattlePyramid_Text_FiveTrainersRemaining3::
    .string "真是一场漂亮的对战！\p本层还有5位训练家\n你能打败他们吧？$"

BattlePyramid_Text_FourTrainersRemaining3::
    .string "真是一场漂亮的对战！\p本层还有4位训练家\n你能打败他们吧？$"

BattlePyramid_Text_ThreeTrainersRemaining3::
    .string "真是一场漂亮的对战！\p本层还有3位训练家\n你能打败他们吧？$"

BattlePyramid_Text_TwoTrainersRemaining3::
    .string "真是一场漂亮的对战！\p本层还有2位训练家\n你能打败他们吧？$"

BattlePyramid_Text_OneTrainersRemaining3::
    .string "真是一场漂亮的对战！\p本层还有1位训练家\n你能打败他吧？$"

BattlePyramid_Text_ZeroTrainersRemaining3::
    .string "真是一场漂亮的对战！\p你已经打败了本层\n所有的训练家。$"

BattlePyramid_Text_SevenTrainersRemaining4::
    .string "或许你能轻松通过\n本层其他7位训练家吧！$"

BattlePyramid_Text_SixTrainersRemaining4::
    .string "或许你能轻松通过\n本层其他6位训练家吧！$"

BattlePyramid_Text_FiveTrainersRemaining4::
    .string "或许你能轻松通过\n本层其他5位训练家吧！$"

BattlePyramid_Text_FourTrainersRemaining4::
    .string "或许你能轻松通过\n本层其他4位训练家吧！$"

BattlePyramid_Text_ThreeTrainersRemaining4::
    .string "或许你能轻松通过\n本层其他3位训练家吧！$"

BattlePyramid_Text_TwoTrainersRemaining4::
    .string "或许你能轻松通过\n本层其他2位训练家吧！$"

BattlePyramid_Text_OneTrainersRemaining4::
    .string "或许你能轻松通过\n本层剩下那1位训练家吧！$"

BattlePyramid_Text_ZeroTrainersRemaining4::
    .string "已经没有人\n能打败你了……$"

BattlePyramid_Text_SevenTrainersRemaining5::
    .string "你还需要打败\n7位专业训练家。$"

BattlePyramid_Text_SixTrainersRemaining5::
    .string "你还需要打败\n6位专业训练家。$"

BattlePyramid_Text_FiveTrainersRemaining5::
    .string "你还需要打败\n5位专业训练家。$"

BattlePyramid_Text_FourTrainersRemaining5::
    .string "你还需要打败\n4位专业训练家。$"

BattlePyramid_Text_ThreeTrainersRemaining5::
    .string "你还需要打败\n3位专业训练家。$"

BattlePyramid_Text_TwoTrainersRemaining5::
    .string "你还需要打败\n2位专业训练家。$"

BattlePyramid_Text_OneTrainersRemaining5::
    .string "你还需要打败\n1位专业训练家。$"

BattlePyramid_Text_ZeroTrainersRemaining5::
    .string "你的技术真娴熟！\p这儿已经没有训练家\n能打败你了。$"

BattlePyramid_Text_SevenTrainersRemaining6::
    .string "你能继续保持打败\n剩下7位训练家的信心吗？$"

BattlePyramid_Text_SixTrainersRemaining6::
    .string "你能继续保持打败\n剩下6位训练家的信心吗？$"

BattlePyramid_Text_FiveTrainersRemaining6::
    .string "你能继续保持打败\n剩下5位训练家的信心吗？$"

BattlePyramid_Text_FourTrainersRemaining6::
    .string "你能继续保持打败\n剩下4位训练家的信心吗？$"

BattlePyramid_Text_ThreeTrainersRemaining6::
    .string "你能继续保持打败\n剩下3位训练家的信心吗？$"

BattlePyramid_Text_TwoTrainersRemaining6::
    .string "你能继续保持打败\n剩下2位训练家的信心吗？$"

BattlePyramid_Text_OneTrainersRemaining6::
    .string "你能继续保持打败\n剩下1位训练家的信心吗？$"

BattlePyramid_Text_ZeroTrainersRemaining6::
    .string "已经没有训练家\n可以和你对战了……$"
