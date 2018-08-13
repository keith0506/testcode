#include <stdlib.h>
class TimerItem {
public:
    TimerItem();
    ~TimerItem();
    void set(int timer_id, void * act, int interval, int timeout);
    const void * get_act() const {
        return _act;
    }
    void set_act(void *act) {
        _act = act;
    }
    int get_interval() const {
        return _interval;
    }
    void set_interval(int interval) {
        _interval = interval;
    }
    int get_timer_id() const {
        return _timer_id;
    }
    void set_timer_id(int timer_id) {
        _timer_id = timer_id;
    }
    void set_timeout(int ot)
	{
		_timeout = ot;
	}

	int get_timeout() const
	{
		return _timeout;
	}
    void set_ring_index(int index) {
        _ring_index = index;
    }
    int get_ring_index() const {
        return _ring_index;
    }

private:
    void *_act;
    int _timer_id;
    int _interval;
    int _timeout;
    int _ring_index;
};