#include "easy_chat.h"

#include "easy_chat_group_pokemon.h"
#include "easy_chat_group_trainer.h"
#include "easy_chat_group_status.h"
#include "easy_chat_group_battle.h"
#include "easy_chat_group_greetings.h"
#include "easy_chat_group_people.h"
#include "easy_chat_group_voices.h"
#include "easy_chat_group_speech.h"
#include "easy_chat_group_endings.h"
#include "easy_chat_group_feelings.h"
#include "easy_chat_group_conditions.h"
#include "easy_chat_group_actions.h"
#include "easy_chat_group_lifestyle.h"
#include "easy_chat_group_hobbies.h"
#include "easy_chat_group_time.h"
#include "easy_chat_group_misc.h"
#include "easy_chat_group_adjectives.h"
#include "easy_chat_group_events.h"
#include "easy_chat_group_move_1.h"
#include "easy_chat_group_move_2.h"
#include "easy_chat_group_trendy_saying.h"
#include "easy_chat_group_pokemon2.h"

const struct EasyChatGroup gEasyChatGroups[EC_NUM_GROUPS] = {
    [EC_GROUP_POKEMON] =
    {
        .name = COMPOUND_STRING("宝可梦"),
        .wordData = {.valueList = gEasyChatGroup_Pokemon},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Pokemon),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Pokemon),
    },
    [EC_GROUP_TRAINER] =
    {
        .name = COMPOUND_STRING("训练家"),
        .wordData = {.words = gEasyChatGroup_Trainer},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Trainer),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Trainer) - 6, // Excludes Red, Green, Flame, Gold, Leaf, and Silver
    },
    [EC_GROUP_STATUS] =
    {
        .name = COMPOUND_STRING("状态"),
        .wordData = {.words = gEasyChatGroup_Status},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Status),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Status),
    },
    [EC_GROUP_BATTLE] =
    {
        .name = COMPOUND_STRING("战斗"),
        .wordData = {.words = gEasyChatGroup_Battle},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Battle),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Battle),
    },
    [EC_GROUP_GREETINGS] =
    {
        .name = COMPOUND_STRING("问候语"),
        .wordData = {.words = gEasyChatGroup_Greetings},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Greetings),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Greetings),
    },
    [EC_GROUP_PEOPLE] =
    {
        .name = COMPOUND_STRING("人们"),
        .wordData = {.words = gEasyChatGroup_People},
        .numWords = ARRAY_COUNT(gEasyChatGroup_People),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_People),
    },
    [EC_GROUP_VOICES] =
    {
        .name = COMPOUND_STRING("拟声词"),
        .wordData = {.words = gEasyChatGroup_Voices},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Voices),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Voices),
    },
    [EC_GROUP_SPEECH] =
    {
        .name = COMPOUND_STRING("口语用词"),
        .wordData = {.words = gEasyChatGroup_Speech},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Speech),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Speech),
    },
    [EC_GROUP_ENDINGS] =
    {
        .name = COMPOUND_STRING("句子结束语"),
        .wordData = {.words = gEasyChatGroup_Endings},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Endings),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Endings),
    },
    [EC_GROUP_FEELINGS] =
    {
        .name = COMPOUND_STRING("感受"),
        .wordData = {.words = gEasyChatGroup_Feelings},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Feelings),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Feelings),
    },
    [EC_GROUP_CONDITIONS] =
    {
        .name = COMPOUND_STRING("状况"),
        .wordData = {.words = gEasyChatGroup_Conditions},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Conditions),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Conditions),
    },
    [EC_GROUP_ACTIONS] =
    {
        .name = COMPOUND_STRING("动作"),
        .wordData = {.words = gEasyChatGroup_Actions},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Actions),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Actions),
    },
    [EC_GROUP_LIFESTYLE] =
    {
        .name = COMPOUND_STRING("生活相关"),
        .wordData = {.words = gEasyChatGroup_Lifestyle},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Lifestyle),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Lifestyle),
    },
    [EC_GROUP_HOBBIES] =
    {
        .name = COMPOUND_STRING("爱好"),
        .wordData = {.words = gEasyChatGroup_Hobbies},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Hobbies),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Hobbies),
    },
    [EC_GROUP_TIME] =
    {
        .name = COMPOUND_STRING("事件"),
        .wordData = {.words = gEasyChatGroup_Time},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Time),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Time),
    },
    [EC_GROUP_MISC] =
    {
        .name = COMPOUND_STRING("各类杂项"),
        .wordData = {.words = gEasyChatGroup_Misc},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Misc),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Misc),
    },
    [EC_GROUP_ADJECTIVES] =
    {
        .name = COMPOUND_STRING("各类形容词"),
        .wordData = {.words = gEasyChatGroup_Adjectives},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Adjectives),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Adjectives),
    },
    [EC_GROUP_EVENTS] =
    {
        .name = COMPOUND_STRING("事件"),
        .wordData = {.words = gEasyChatGroup_Events},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Events),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Events),
    },
    [EC_GROUP_MOVE_1] =
    {
        .name = COMPOUND_STRING("招式1"),
        .wordData = {.valueList = gEasyChatGroup_Move1},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Move1),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Move1),
    },
    [EC_GROUP_MOVE_2] =
    {
        .name = COMPOUND_STRING("招式2"),
        .wordData = {.valueList = gEasyChatGroup_Move2},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Move2),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Move2),
    },
    [EC_GROUP_TRENDY_SAYING] =
    {
        .name = COMPOUND_STRING("流行语"),
        .wordData = {.words = gEasyChatGroup_TrendySaying},
        .numWords = ARRAY_COUNT(gEasyChatGroup_TrendySaying),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_TrendySaying),
    },
    [EC_GROUP_POKEMON_NATIONAL] =
    {
        .name = COMPOUND_STRING("宝可梦2"),
        .wordData = {.valueList = gEasyChatGroup_Pokemon2},
        .numWords = ARRAY_COUNT(gEasyChatGroup_Pokemon2),
        .numEnabledWords = ARRAY_COUNT(gEasyChatGroup_Pokemon2),
    },
};
