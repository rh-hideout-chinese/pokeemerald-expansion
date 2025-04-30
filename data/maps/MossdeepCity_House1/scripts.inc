MossdeepCity_House1_MapScripts::
	.byte 0

MossdeepCity_House1_EventScript_BlackBelt::
	lock
	faceplayer
	bufferleadmonspeciesname STR_VAR_1
	msgbox MossdeepCity_House1_Text_HmmYourPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetPokeblockNameByMonNature
	goto_if_eq VAR_RESULT, 0, MossdeepCity_House1_EventScript_NeutralNature
	msgbox MossdeepCity_House1_Text_ItLikesXPokeblocks, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House1_EventScript_NeutralNature::
	msgbox MossdeepCity_House1_Text_DoesntLikeOrDislikePokeblocks, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House1_EventScript_Woman::
	msgbox MossdeepCity_House1_Text_HusbandCanTellPokeblockMonLikes, MSGBOX_NPC
	end

MossdeepCity_House1_Text_HmmYourPokemon:
    .string "啊！\n你的{STR_VAR_1}……$"

MossdeepCity_House1_Text_ItLikesXPokeblocks:
    .string "它喜欢{STR_VAR_1}\n是吧？\p不，我肯定它\n就是喜欢{STR_VAR_1}！$"

MossdeepCity_House1_Text_DoesntLikeOrDislikePokeblocks:
    .string "它看来并没什么\n特别喜欢或不喜欢的树果。$"

MossdeepCity_House1_Text_HusbandCanTellPokeblockMonLikes:
    .string "我的丈夫一眼就能看出\n宝可梦喜欢什么样的树果。$"

