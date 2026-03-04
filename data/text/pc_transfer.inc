gText_PkmnTransferredSomeonesPC::
    .string "已将{STR_VAR_2}传送到\n某人的电脑上，\p位于盒子\n“{STR_VAR_1}”里。$"

gText_PkmnTransferredLanettesPC::
	.string "已将{STR_VAR_2}传送到\n"
#if IS_FRLG
	.string "正辉的电脑上，\p"
#else
	.string "真由美的电脑上，\p"
#endif
	.string "位于盒子\n“{STR_VAR_1}”里。”$"

gText_PkmnTransferredSomeonesPCBoxFull::
	.string "某人的电脑上的盒子\n“{STR_VAR_3}”已满，\p{STR_VAR_2}传送到\n盒子“{STR_VAR_1}”里。$"

gText_PkmnTransferredLanettesPCBoxFull::
#if IS_FRLG
	.string "正辉的电脑上的盒子\n"
#else
	.string "真由美的电脑上的盒子\n"
#endif
	.string "“{STR_VAR_3}”已满，\p"
	.string "已将{STR_VAR_2}传送到\n"
	.string "盒子“{STR_VAR_1}”里。$"

gText_PkmnSentToPCAfterCatch::
	.string "已将{STR_VAR_2}传送到\n"
	.string "{B_PC_CREATOR_NAME}的电脑上。\p"
	.string "位于盒子\n“{STR_VAR_1}”里。$"

gText_PlayerObtainedTheMon::
	.string "{PLAYER}获得了\n"
	.string "{STR_VAR_1}！$"

gText_NoMoreRoomForPokemon::
    .string "没有寄存宝可梦的空间了！\p所有宝可梦盒子都已放满，\n无法容纳新的宝可梦！$"

gText_NicknameThisPokemon::
    .string "要给{STR_VAR_1}\n起昵称吗？$"
