#include "textProcessing.h"
#include "Text.h"
#include "additional.h"
#include <wchar.h>
#include <stdlib.h>
#define N 1000

void wordsThreeOrMoreTimes(struct Text text){
    // Распечатать каждое слово, которое встречается минимум три раза в тексте,
    // а также количество вхождений каждого такого слова в текст.
    // creat list of words
    wchar_t words[N][N];
    // create counts of words list - all counts = 0
    size_t count[N] = {0};
    // current word count
    size_t count_of_words = 0;
    // check every sentence
    for(size_t i = 0; i < text.count; i++){
        // split the sentence into separate words
        size_t num_words;
        wchar_t** words_of_sen = wordsOfSentence(text.arr[i], &num_words, 1);
        // work with each word separately
        for(size_t j = 0; j < num_words; j++){
            int need_to_add = 1;
            // check if a word is in the list
            for(size_t k = 0; k < count_of_words; k++){
                if (!wcscmp(words_of_sen[j], words[k])) {
                    need_to_add = 0;
                    count[k]++;
                    break;
                }
            }
            // add the word to the list if it hasn't been added before
            if (need_to_add){
                wmemcpy(words[count_of_words], words_of_sen[j], wcslen(words_of_sen[j]) + 1);
                count[count_of_words] = 1;
                count_of_words++;
            }
        }
        // clear the memory
        for (size_t j = 0; j < num_words; j++){
            free(words_of_sen[j]);
        }
        free(words_of_sen);
    }
    // print the right words
    int hasNotRightWords = 1;
    for (size_t i = 0; i < count_of_words; i++){
        if (count[i] >= 3){
            wprintf(L"The word '%ls' occurs %zd times in the text\n", words[i], count[i]);
            hasNotRightWords = 0;
        }
    }
    if (hasNotRightWords)
        fputws(L"В данном тексте есть только слова, встречающиеся менее 3 раз\n", stdout);
}

void digitToCount(struct Text* text){
    // Заменить каждый символ цифры на число вхождений данной цифры во всем тексте.
    int countOfDigits[10] = {0};
    int hasCountInSentence = 0;
    // count the number of occurrences of a number in the text
    for(size_t i = 0; i < text->count; i++){
        // copy sentence
        wchar_t* sen = malloc(sizeof(wchar_t) * (wcslen(text->arr[i].arr) + 1));
        wmemcpy(sen, text->arr[i].arr, wcslen(text->arr[i].arr) + 1);
        // work with the sentence as long as it has numbers
        while(wcscspn(sen, L"0123456789") != wcslen(sen)){
            hasCountInSentence = 1;
            size_t index = wcscspn(sen, L"0123456789");
            wchar_t letter[2];
            letter[0] = *(sen + index);
            letter[1] = L'\0';
            countOfDigits[_wtoi(letter)]++;
            *(sen + index) = L'*';
        }
        // clean the memory
        free(sen);
    }
    if (!hasCountInSentence)
        wprintf(L"В вашем тексте нет цифр\n");
    else
        //  change the numbers to their quantities
        for(size_t i = 0; i < text->count; i++){
            // current sentence index after the replaced number
            wchar_t* index_sen = text->arr[i].arr;
            // number of characters up to the replaced number including it
            size_t before = 0;
            // work with the sentence until we replace all the numbers
            while(wcscspn(index_sen, L"0123456789") != wcslen(index_sen)){
                // first number index
                size_t index = wcscspn(index_sen, L"0123456789");
                // translate the found character into a number
                wchar_t letter[2];
                letter[0] = *(index_sen + index);
                letter[1] = L'\0';
                size_t digit = _wtoi(letter);
                // copy the sentence after the number into a separate variable
                wchar_t* lastPartSentence = malloc(sizeof(wchar_t) * (wcslen(index_sen) - index));
                wmemcpy(lastPartSentence, index_sen + index + 1, wcslen(index_sen) - index);
                lastPartSentence[wcslen(index_sen) - index] = '\0';
                // convert the quantity of occurrences of a number to a string
                wchar_t quantity[N];
                _itow(countOfDigits[digit], quantity, 10);
                quantity[wcslen(quantity)] = L'\0';
                // length of quantity
                size_t lenOfQuantity = wcslen(quantity);
                // replace the number with its quantity
                wmemcpy(text->arr[i].arr + index + before, quantity,  lenOfQuantity + 1);
                *(text->arr[i].arr + index + before + lenOfQuantity) = L'\0';
                // change the quantity of characters up to the replaced number including it
                before += index + lenOfQuantity;
                // put back the last part of the sentence
                wmemcpy(text->arr[i].arr + before, lastPartSentence,  wcslen(lastPartSentence));
                *(text->arr[i].arr + before + wcslen(lastPartSentence) + 1) = L'\0';
                // change current sentence index after the replaced number
                index_sen = text->arr[i].arr + before;
                // clean the memory
                free(lastPartSentence);
            }
        }
}


void reverseRussian(struct Text* text){
    // Поменять порядок слов на обратный в предложениях, которые состоят только из кириллических букв.
    int russianSentence = 0;
    for (size_t i = 0; i < text->count; i++){
        // find only sentence with russian words divided ' ' or ','
        if (!sentenceIsRussian(text->arr[i]))
            continue;
        russianSentence = 1;
        size_t num_words;
        wchar_t** words_of_sen = wordsOfSentence(text->arr[i], &num_words, 1);
        // an array indicating which words should be followed by commas
        size_t* commas = commasOfSentence(text->arr[i], words_of_sen, num_words);
        size_t indexSen = 0;
        int com = 0;
        while (num_words > 0) {
            num_words--;
            // copy word in sentence
            wmemcpy(text->arr[i].arr + indexSen, words_of_sen[num_words], wcslen(words_of_sen[num_words]));
            indexSen += wcslen(words_of_sen[num_words]);
            text->arr[i].arr[indexSen] = L'\0';
            if(num_words != 0){
                // copy the comma if it exists
                if(commas[com]){
                    text->arr[i].arr[indexSen] = L',';
                    indexSen++;
                    text->arr[i].arr[indexSen] = L'\0';
                }
                // copy space
                text->arr[i].arr[indexSen] = L' ';
                indexSen++;
                text->arr[i].arr[indexSen] = L'\0';
            }
            com++;
        }
        // clean the memory
        free(commas);
        for (size_t j = 0; j < num_words; j++){
            free(words_of_sen[j]);
        }
        free(words_of_sen);
    }
    if (!russianSentence){
        wprintf(L"В вашем тексте нет русских предложений\n");
    }
}


void sortWords(struct Text* text){
    // Отсортировать слова в предложения по уменьшению количеству латинских букв в словах.
    for (size_t i = 0; i < text->count; i++){
        // find words
        size_t num_words;
        wchar_t** words_of_sen = wordsOfSentence(text->arr[i], &num_words, 1);
        // an array indicating which words should be followed by commas
        size_t* commas = commasOfSentence(text->arr[i], words_of_sen, num_words);
        // looking for the number of characters in the number of words
        int num = (int) num_words;
        wchar_t numWordsInStr[N];
        _itow(num, numWordsInStr, 10);
        numWordsInStr[wcslen(numWordsInStr)] = L'\0';
        int lenNumWords = (int) wcslen(numWordsInStr);
        // number of Latin letters in words
        size_t* countLatinChar = countLatinLetters(words_of_sen, num_words, lenNumWords);
        // sort numbers of Latin letters in words
        qsort(countLatinChar, num_words, sizeof(size_t), cmp);
        // collect the sentence
        size_t indexSen = 0;
        for (size_t j = 0; j < num_words; j++) {
            wchar_t* indexStr = malloc(sizeof(wchar_t) * (lenNumWords + 1));
            // convert the number of latin letters to a string
            wchar_t* countIndex = malloc(sizeof(wchar_t) * N);
            _itow((int) countLatinChar[j], countIndex, 10);
            countIndex[wcslen(countIndex)] = L'\0';
            // copy index
            wmemcpy(indexStr, countIndex + wcslen(countIndex) - lenNumWords, lenNumWords + 1);
            indexStr[lenNumWords + 1] = L'\0';
            // convert index in digit
            int index = _wtoi(indexStr);
            // copy word in sentence
            wmemcpy(text->arr[i].arr + indexSen, words_of_sen[index], wcslen(words_of_sen[index]));
            indexSen += wcslen(words_of_sen[index]);
            text->arr[i].arr[indexSen] = L'\0';
            if(j != num_words - 1){
                // copy the comma if it exists
                if(commas[j]){
                    text->arr[i].arr[indexSen] = L',';
                    indexSen++;
                    text->arr[i].arr[indexSen] = L'\0';
                }
                // copy space
                text->arr[i].arr[indexSen] = L' ';
                indexSen++;
                text->arr[i].arr[indexSen] = L'\0';
            }
        }
        // clean the memory
        free(commas);
        for (size_t j = 0; j < num_words; j++){
            free(words_of_sen[j]);
        }
        free(words_of_sen);
    }
}


void senWithMaxCountPalindromes(struct Text text){
    // array of counts palindromes in sentences
    int countPalindromes[text.count];
    for (size_t i = 0; i < text.count; i++){
        countPalindromes[i] = 0;
    }
    // array of sums lengths palindromes in sentences
    int sumOfLengthsPalindromes[text.count];
    for (size_t i = 0; i < text.count; i++){
        sumOfLengthsPalindromes[i] = 0;
    }
    // check each sentence
    for (size_t i = 0; i < text.count; i++){
        // words of sentence
        size_t numWords;
        wchar_t** words = wordsOfSentence(text.arr[i], &numWords, 0);
        // check each word
        for (size_t j = 0; j < numWords; j++){
            if (isPalindrome(words[j])){
                countPalindromes[i]++;
                sumOfLengthsPalindromes[i] += wcslen(words[j]);
            }
        }
        free(words);
    }
//    for (size_t i = 0; i < text.count; i++){
//        wprintf(L"countPalindromes in %zd sen: %zd\n", i, countPalindromes[i]);
//    }
//    for (size_t i = 0; i < text.count; i++){
//        wprintf(L"sumOfLengthsPalindromes in %zd sen: %zd\n", i, sumOfLengthsPalindromes[i]);
//    }
    int* hasMaxCountP = findIndexMaxElems(countPalindromes, text.count);
//    for (size_t i = 0; i < text.count; i++){
//        wprintf(L"hasMaxCountP in %zd sen: %zd\n", i, hasMaxCountP[i]);
//    }
    for (size_t i = 0; i < text.count; i++){
        if (!hasMaxCountP[i]){
            sumOfLengthsPalindromes[i] = 0;
        }
    }
    int* hasMaxLenP = findIndexMaxElems(sumOfLengthsPalindromes, text.count);
//    for (size_t i = 0; i < text.count; i++){
//        wprintf(L"hasMaxLenP in %zd sen: %zd\n", i, hasMaxLenP[i]);
//    }
    for (size_t i = 0; i < text.count; i++){
        if (hasMaxLenP[i] == 1){
            wprintf(L"Your sentence:\n%ls\n", text.arr[i].arr);
            break;
        }
    }
}

