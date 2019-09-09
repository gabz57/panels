#ifndef LOCALTIME_H
#define LOCALTIME_H

#include <sys/time.h>

typedef int64_t tmillis_t;
typedef int64_t tus_t;

using namespace rgb_matrix;

static tmillis_t GetTimeInMillis() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

static tus_t GetTimeInMicros() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000000 + tp.tv_usec;
}

static void SleepUs(tus_t u_seconds) {
    if (u_seconds <= 0) return;
    struct timespec ts;
    ts.tv_sec = u_seconds / 1000000;
    ts.tv_nsec = (u_seconds % 1000000) * 1000;
    nanosleep(&ts, NULL);
}

static void SleepMillis(tmillis_t milli_seconds) {
    if (milli_seconds <= 0) return;
    struct timespec ts;
    ts.tv_sec = milli_seconds / 1000;
    ts.tv_nsec = (milli_seconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

#endif //LOCALTIME_H
