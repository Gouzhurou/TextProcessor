#ifndef TEXT_H
#define TEXT_H
#include <wchar.h>

struct Text{
    struct Sentence* arr;
    size_t count;
};

struct Sentence{
    wchar_t* arr;
};

#endif //TEXT_H