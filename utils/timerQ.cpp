#include "timerQ.h"
#include <unistd.h>
int main() {
    TimerQueue tq;
    for(int i = 1; i < 15; i++)
        tq.schedule(NULL, i, 0);
    while(1) {
        int timeval = tq.expire();
        usleep(1000000);
    }
    return 0;
}