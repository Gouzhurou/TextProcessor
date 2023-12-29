#include <stdlib.h>
#include <locale.h>
#include "Text.h"
#include "menu.h"
#include "inputOutput.h"
#include "textProcessing.h"
#include "additional.h"
#define N 1000

int main(){
    // dynamically allocate memory for an array of strings
    struct Text text;
    text.arr = malloc(sizeof(struct Sentence) * N);
    for (int i = 0; i < N; i++){
        text.arr[i].arr = malloc(sizeof(wchar_t) * N);
    }
    text.count = 0;

    setlocale(LC_ALL, "");
    input(&text);
    output(&text);

    wchar_t action = L'0';
    while(action != L'5'){
        action = chooseAction(&text);
    }

    for (size_t i = 0; i < N; i++){
        free(text.arr[i].arr);
    }
    free(text.arr);
    return 0;
}
