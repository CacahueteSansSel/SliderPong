//
// Created by Cacahuète on 10/03/2024.
//

#ifndef LET_THREAD_H
#define LET_THREAD_H

#include <3ds.h>

class ThreadWrapper {
public:
    explicit ThreadWrapper(ThreadFunc main);

    void start();
    void join();
private:
    Thread _thread;
    ThreadFunc _main;
};


#endif //LET_THREAD_H
