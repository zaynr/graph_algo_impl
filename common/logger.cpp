//
// Created by 曾锃煜 on 2019/12/6.
//

#include <cstdio>
#include <cstdarg>
#include <thread>
#include <chrono>
#include "logger.h"

using namespace std::chrono;

void PrintToTerm(const char* func, const int line, const char* fmt, ...) {
    static uint64_t tid;
    pthread_threadid_np(nullptr, &tid);
    auto duration = system_clock::now().time_since_epoch();
    auto h = (duration_cast<hours>(duration).count() + 8) % 24;
    auto m = duration_cast<minutes>(duration).count() % 60;
    auto s = duration_cast<seconds>(duration).count() % 60;
    auto ms = duration_cast<milliseconds>(duration).count() % 1000;
    printf("%.2ld:%.2ld:%.2lld.%.3lld|0x%.7llx|", h, m, s, ms, tid);
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    printf("    |%s(%d)\n", func, line);
}
