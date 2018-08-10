#include "timer_item.h"
TimerItem::TimerItem(): _act(NULL), _timer_id(0), _interval(0), _timeout(0) {}
void TimerItem::set(int timer_id, void * act, int interval, int timeout) {
    _timer_id = timer_id;
    _act = act;
    _interval = interval;
    _timeout = timeout;
}