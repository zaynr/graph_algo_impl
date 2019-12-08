//
// Created by 曾锃煜 on 2019/12/6.
//

#pragma once

void PrintToTerm(const char* func, int line, const char* fmt, ...);

#ifdef _DEBUG
#define LOG(fmt, ...) \
    PrintToTerm(__FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#else
#define LOG(fmt, ...) ((void)0)
#endif
