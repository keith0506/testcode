#include "ring.h"
TimerRing::TimerRing(int ring_id): _ring_id(ring_id) {
    for(int i = 0; i < MAX_RING_SIZE; i++) {
        ESet element_set;
        _ring.push_back(element_set);
    }
    _pos = 0;
}
TimerRing::~TimerRing() {
    clear();
}
void TimerRing::reset() {
    _pos = 0;
}
bool TimerRing::add_element(int ring_pos, int timer_id) {
    bool ret = false;
    // invalid condition: 1. pos == _pos, timer should be trigger now!
    //                    2. invalid _ring_id
    if (ring_pos != _pos || _ring_id == 0) {
        _ring[ring_pos].insert(ESet::value_type(timer_id));
        ret = true;
    }
    return ret;
}
bool TimerRing::del_element(int ring_pos, int timer_id) {
    _ring[_pos].erase(timer_id);
    return true;
}
bool TimerRing::cycle(int &scale, IRingEvent* handler) {
	if(handler == NULL)
		return false; // meaningless if no handler
    
	bool ret = false;
	int new_pos = scale + _pos;
	if(new_pos >= MAX_RING_SIZE) {
		ret = true;
		scale = scale + _pos - MAX_RING_SIZE;
	}
	else {
		scale = 0;
    }

	ESet::iterator tid; // timer id iterator
	for(int pos = _pos; pos < new_pos; pos ++)
	{
        pos %= MAX_RING_SIZE;
        
		for(tid = _ring[pos].begin(); tid != _ring[pos].end(); ++ tid) { // trigger ring pointer timer
			handler->on_event(_ring_id, *tid);
		}
		_ring[pos].clear(); // remove all element in set

		_pos ++; // ring pointer move forward
		if(_pos >= MAX_RING_SIZE) {
			_pos = _pos % MAX_RING_SIZE;
		}

		for(tid = _ring[_pos].begin(); tid != _ring[_pos].end(); ++ tid) {
			handler->on_event(_ring_id, *tid);
		}
		_ring[_pos].clear();
	}

	return ret;
}
void TimerRing::clear() {
    for (int i = 0; i < MAX_RING_SIZE; i++) {
        _ring[i].clear();
    }
}
