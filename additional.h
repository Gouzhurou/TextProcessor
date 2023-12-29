#include "Text.h"
#include <wchar.h>

int newSentence(struct Text text);

wchar_t** wordsOfSentence(struct Sentence sen, size_t* num_words, int needLower);

int sentenceIsRussian(struct Sentence sen);

size_t* commasOfSentence(struct Sentence sen, wchar_t** words, size_t numWords);

size_t* countLatinLetters(wchar_t** words, size_t numWords, int lenNumWords);

int cmp(const void* a, const void* b);

int isPalindrome(wchar_t* word);

int* findIndexMaxElems(int* array, size_t len);