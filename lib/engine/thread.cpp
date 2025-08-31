//
// Created by Cacahuète on 10/03/2024.
//

#include "thread.h"
#include <3ds.h>

#define STACKSIZE (4 * 1024)

ThreadWrapper::ThreadWrapper(ThreadFunc main) {
    _main = main;
}

void ThreadWrapper::start() {
    s32 mainThreadPriority = 0;
    svcGetThreadPriority(&mainThreadPriority, CUR_THREAD_HANDLE);

    _thread = threadCreate(_main,
                           nullptr,
                           STACKSIZE,
                           mainThreadPriority - 1,
                           -2,
                           false);
}

void ThreadWrapper::join() {
    threadJoin(_thread, 0);
}
