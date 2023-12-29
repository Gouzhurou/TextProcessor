#include "additional.h"
#include <wchar.h>
#include <stdlib.h>
#include <math.h>
#include "Text.h"
#define N 1000

int newSentence(struct Text text){
    // looking for similar sentences
    size_t n = text.count;
    towlower(*(text.arr[n].arr));
    int check = 1;
    for(size_t i = 0; i < n; i++){
        towlower(*(text.arr[i].arr));
        if (!wcscmp(text.arr[n].arr, text.arr[i].arr))
            check = 0;
    }
    return check;
}

wchar_t** wordsOfSentence(struct Sentence sen, size_t* num_words, int needLower){
    // dynamically allocate memory for an array of words
    wchar_t** words = malloc(sizeof(wchar_t*) * wcslen(sen.arr));
    for (size_t i = 0; i < wcslen(sen.arr); i++){
        words[i] = malloc(sizeof(wchar_t) * N);
    }
    wchar_t c;
    // set the character number of a sentence
    size_t index_sen = 0;
    // amount of words
    *num_words = 0;
    while(index_sen < wcslen(sen.arr)){
        // set the character number of a single word
        size_t index_char = 0;
        // write the word up to ',' or ' '
        while(index_sen < wcslen(sen.arr) && wcschr(L", ", sen.arr[index_sen]) == NULL){
            if(needLower) {
                words[*num_words][index_char] = towlower(sen.arr[index_sen]);
            }
            else{
                words[*num_words][index_char] = sen.arr[index_sen];
            }
            index_sen++;
            index_char++;
        }
        words[*num_words][index_char] = L'\0';
        // ignore all signs ',' and ' '
        while(index_sen < wcslen(sen.arr) && wcschr(L", ", sen.arr[index_sen]) != NULL){
            index_sen++;
        }
        *(num_words) += 1;
    }
    return words;
}

int sentenceIsRussian(struct Sentence sen){
    // L"абвгдеёжзийклмнопрстуфхцчшщыъьэюя"
    int isRussian = 1;
    for (size_t i = 0; i < wcslen(sen.arr); i++){
        if (wcschr(L"абвгдеёжзийклмнопрстуфхцчшщыъьэюя, ", towlower(sen.arr[i])) == NULL){
            isRussian = 0;
            break;
        }
    }
    return isRussian;
}

size_t* commasOfSentence(struct Sentence sen, wchar_t** words, size_t numWords){
    // create array: 1 - there is comma after sentence; 0 - isn`t
    size_t* commas = malloc(sizeof(size_t) * numWords);
    for (size_t i = 0; i < numWords; i++){
        commas[i] = 0;
    }
    size_t indexWord = 0;
    size_t indexSen = wcslen(words[indexWord]);
    // go in a cycle to the penultimate word
    while(indexWord < numWords - 1){
        // find comma after word with number indexWord
        while(wcschr(L" ,", sen.arr[indexSen]) != NULL){
            if (sen.arr[indexSen] == L',')
                commas[indexWord] = 1;
            indexSen++;
        }
        indexWord++;
        indexSen += wcslen(words[indexWord]);
    }
    return commas;
}

size_t* countLatinLetters(wchar_t** words, size_t numWords, int lenNumWords){
    // L"абвгдеёжзийклмнопрстуфхцчшщыъьэюя"
    // int count of words
    // initially the number of Latin letters is 0 in each word
    size_t* countLatin = malloc(sizeof(size_t) * numWords);
    for (size_t i = 0; i < numWords; i++){
        countLatin[i] = 0;
    }
    for (size_t i = 0; i < numWords; i++){
        size_t lenWord = wcslen(words[i]);
        for (size_t j = 0; j < lenWord; j++)
            if (wcschr(L"abcdefghijklmnopwrstuvwxyz", towlower(words[i][j])) != NULL)
                countLatin[i]++;
    }
    // add the index of the word to the end of the number of latin letters
    for (size_t i = 0; i < numWords; i++){
        countLatin[i] = countLatin[i] * (size_t) pow(10, lenNumWords) + i;
    }
    return countLatin;
}

int cmp(const void* a, const void* b){
    const size_t* aa = (const size_t*) a;
    const size_t* bb = (const size_t*) b;
    if (*aa > *bb) return -1;
    if (*aa < *bb) return 1;
    return 0;
}


int isPalindrome(wchar_t* word){
    // count half word length
    int halfWordLength = wcslen(word) / 2;
//    wprintf(L"halfWordLength: %zd\n", halfWordLength);
    // flag that means word is palindrome
    int isPalindrome = 1;
    // compare two half word
    for (size_t i = 0; i < halfWordLength; i++){
        if (word[i] != word[wcslen(word) - 1 - i]){
            isPalindrome = 0;
            break;
        }
    }
    return isPalindrome;
}


int* findIndexMaxElems(int* array, size_t len){
    int* numsMaxElem = malloc(sizeof(size_t) * len);
    for (size_t i = 0; i < len; i++){
        numsMaxElem[i] = 0;
    }
    size_t max = array[0];
    numsMaxElem[0] = 1;
    for (size_t i = 1; i < len; i++){
        if (max < array[i]){
            max = array[i];
            for (size_t j = 0; j < len; j++){
                numsMaxElem[j] = 0;
            }
            numsMaxElem[i] = 1;
        }
        if (max == array[i]){
            numsMaxElem[i] = 1;
        }
    }
    return numsMaxElem;
}
