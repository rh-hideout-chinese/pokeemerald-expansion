MtPyre_5F_MapScripts::
	.byte 0

@ Seems like the scripts for the 4F and 5F were swapped

MtPyre_4F_EventScript_Tasha::
	trainerbattle_single TRAINER_TASHA, MtPyre_4F_Text_TashaIntro, MtPyre_4F_Text_TashaDefeat
	msgbox MtPyre_4F_Text_TashaPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_4F_Text_TashaIntro:
    .string "我热爱一切恐怖的事物…\n就像一种病…\p当我在此…\n我因恐惧而颤抖…$"

MtPyre_4F_Text_TashaDefeat:
    .string "我讨厌失败…$"

MtPyre_4F_Text_TashaPostBattle:
    .string "我想看看可怕的东西…\n我不能离开…\p呐…\n你不想和我一起来吗？$"

