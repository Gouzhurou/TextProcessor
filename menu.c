#include "menu.h"
#include "inputOutput.h"
#include "textProcessing.h"
#include <wchar.h>
#include "Text.h"
#define N 1000

wchar_t chooseAction(struct Text* text){
    wchar_t action[N];
    wprintf(L"Доступные действия:\n");
    wprintf(L"1:  Распечатать каждое слово, которое встречается минимум три раза в тексте,\n\tа также количество вхождений каждого такого слова в текст.\n");
    wprintf(L"2:  Заменить каждый символ цифры на число вхождений данной цифры во всем\n\tтексте.\n");
    wprintf(L"3:  Отсортировать слова в предложения по уменьшению количеству латинских букв\n\tв словах.\n");
    wprintf(L"4:  Поменять порядок слов на обратный в предложениях, которые состоят только из\n\tкириллических букв.\n");
    wprintf(L"5:  Выход из программы.\n");
    wprintf(L"6:  Найти в тексте T предложение, с максимальным количеством слов-палиндромов.\n\tПри равенстве количества, результатом считать то, где суммарная\n\tдлина слов-палиндромов больше. Регистр учитывать..\n");
    wprintf(L"Введите действие: ");
    fgetws(action, N, stdin);
    if (wcslen(action) > 2)
        action[0] = L'*';
    switch (action[0]) {
        case L'1':
            wordsThreeOrMoreTimes(*text);
            break;
        case L'2':
            digitToCount(text);
            output(text);
            break;
        case L'3':
            sortWords(text);
            output(text);
            break;
        case L'4':
            reverseRussian(text);
            output(text);
            break;
        case L'5':
            wprintf(L"До встречи\n\n");
            break;
        case L'6':
            senWithMaxCountPalindromes(*text);
            break;
        default:
            wprintf(L"Введенного вами действия не существует. Попробуйте снова\n\n");
    }
    return action[0];
}

