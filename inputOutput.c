#include "inputOutput.h"
#include <wchar.h>
#include "additional.h"
#include "Text.h"

void input(struct Text* text){
    fputws(L"Input you text:\n", stdout);
    wchar_t c;
    while(1){
        size_t index_char = 0;
        c = getwchar();
        // ignore all ' ', '.' and '\t' characters at the beginning of a sentence
        while(wcschr(L" ,.\t", c) != NULL)
            c = getwchar();
        // when a line break character is encountered, we end the text input
        if(c == L'\n')
            break;
        do{
            // write a character in a sentence
            text->arr[text->count].arr[index_char] = c;
            // increase character index by 1
            index_char += 1;
            c = getwchar();
        }while(c != L'.' && c != L'\n');
        // delete all ' ', '.' and '\t' characters at the ending of a sentence
        while(wcschr(L" .\t", text->arr[text->count].arr[index_char - 1]) != NULL)
            index_char -= 1;
        text->arr[text->count].arr[index_char] = L'\0';

        // skip the sentence that was already there
        if (newSentence(*text))
            text->count += 1;
        // when a line break character is encountered, we end the text input
        if(c == L'\n')
            break;
    }
//    wprintf(L"count strs: %zd\n", (*text).count);
}

void output(struct Text* text){
    wprintf(L"Your text:\n");
    for (size_t i = 0; i < text->count; i++){
        wprintf(L"%ls. ",  text->arr[i].arr);
    }
    wprintf(L"\n\n");
}