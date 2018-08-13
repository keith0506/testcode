#include <iostream>
#include <list>
#include <sys/time.h>

#include "log.h"
#include "ring.h"
#include "timer_item.h"
#define RINGS_SIZE	4
#define RING_DELAY 5
#define UNIET32_MAX 0x7fffffff
#define FIRST_ROUND   (0)                                                 // seconds
#define SECOND_ROUND  (MAX_RING_SIZE)                                     // minutes
#define THIRD_ROUND   (MAX_RING_SIZE * MAX_RING_SIZE)                     // hours
#define FORTH_ROUND   (MAX_RING_SIZE * MAX_RING_SIZE * MAX_RING_SIZE)     // days

class TimerQueue: public IRingEvent {
public:
	TimerQueue(size_t heap_size = 1024) {
        // initialize timer obj heap
        _heap_size = 0;
        alloc_heap(heap_size);
        _used_num = 0;
	    _cur_heap_pos = 0;
        
        struct timeval tv;
        gettimeofday(&tv, NULL);

        _start_time = tv.tv_sec;
        _pre_time = _start_time;

        for (int index = 0; index < RINGS_SIZE; index ++) {
            _rings[index].set_ring_id(index);
        }
    }
	~TimerQueue() {
        // free _heap
        // remove timer node
        // delete TimerItem
    }

    int get_ring_pos (int distance, int * wheel) {
        if (distance <= 0)
            return -1;
        if (distance / FORTH_ROUND) {
            *wheel = 3;
            return distance % FORTH_ROUND;
        }
        if (distance / THIRD_ROUND) {
            *wheel = 2;
            return distance % THIRD_ROUND;
        }
        if (distance / SECOND_ROUND) {
            *wheel = 1;
            return distance % SECOND_ROUND;
        }
        *wheel = 0;
        return distance;
    }
	// insert a timer
	int schedule(void* act, int delay, int interval = 0){
        int timer_id = get_free_timer_id();
        TimerItem *timer_obj = new TimerItem;

        if (!timer_obj) {
            log_debug("Create timer item failed")
        }
        struct timeval tv;
        gettimeofday(&tv, NULL);
        int cur_timer = tv.tv_sec;

        /*
        fetch timer obj from pool, decrease pool
        */
        int distance = delay;
        if (cur_timer > _start_time) {
            distance = cur_timer - _start_time + delay;
        }
        distance %= UNIET32_MAX;
        log_debug("timer id: %d, distance: %d\n", timer_id, distance);
        timer_obj->set(timer_id, act, interval, 0);
        _heap[timer_id] = timer_obj;

        // lock
        timer_obj->set_ring_index(insert_node(distance, timer_id));
        // unlock
        return timer_id;
    }
	// cancel a timer
	void cancel_timer(int timer_id, const void **act){
        if(timer_id < _heap_size && _heap[timer_id] != NULL) {
            TimerItem * timer_obj = _heap[timer_id];
            if (act) {
                *act = timer_obj->get_act(); // Todo
            }
            delete_node(timer_obj);
            _free_timerid_list.push_back(timer_id);
            _heap[timer_id] = NULL;
            delete timer_obj;
            // increase timer poll
        }
    }
	// reset a timer
	int reset_timer(int timer_id, int delay, int interval = 0)
    {
        return 0;
    }

    // scan timeout timer, return next timeout interval [10, 50] ms
	virtual int expire() {
        int ret = RING_DELAY;
        struct timeval tv;
        gettimeofday(&tv, NULL);

        int cur_timer = tv.tv_sec;
        if (cur_timer > _pre_time) {
            int scale = cur_timer - _pre_time;
            log_debug("scale: %d\n", scale);
            if (scale > 0) {
                ret = revolver(scale);
                _pre_time = cur_timer;
            }
        }
        return ret;
    }

	// implement interface
	void on_event(int ring_id, int timer_id) {
        // get timer obj by timer_id
        log_debug("timer triggerred, ring_id: %d, timer_id: %d\n", ring_id, timer_id);
    }

	// indicate heap is full
	bool full() const {
        return _used_num == _heap_size;
    }

protected:
//Todo: implement a dynamic buffer, which provide malloc, realloc, resize operation
//Todo: reduce the heap when not using. NOTE: resize won't reduce capcity of vector, size is correct
    // input: size = 0, double size the heap
    //            != 0, resize with size
	void alloc_heap(size_t size) {
        if(size == 0) // double the heap
            size = _heap_size * 2;
        _heap.resize(size);
        log_debug("try to alloc :%lu byte heap\n", size);
        for (int i = 0; i < size; i ++) {
            _heap[_heap_size] = NULL;
            _free_timerid_list.push_back(_heap_size);
            _heap_size ++;
        }
        return;
    }
    // input: distance, timer_id
    // ret: ring index
	int insert_node(int node, int timer_id) {
        int wheel = 0;
        int pos = get_ring_pos(node, &wheel);
        log_debug("insert to wheel: %d, pos: %d\n", wheel, pos);
        if (wheel >= 0 && wheel <= 3) {
            _rings[wheel].add_element(pos, timer_id);
            return wheel;
        }
        log_debug("Add ring failed")
        return -1;
    }
	void delete_node(TimerItem *node) {
        int wheel = 0;
        int pos = get_ring_pos(node->get_timeout(), &wheel); // save pos/ring id in TimerItem??
        if (wheel >= 0 && wheel <= 3) {
            _rings[wheel].del_element(pos, node->get_timer_id());
        }
    }

	int revolver(int scale) {
        int ret = RING_DELAY;
        char index = 0;
        int rewind_scale = scale;
        while (rewind_scale > 0) {
            index = 0;
            // scan the first ring
            if (_rings[index].cycle(rewind_scale, this)) {
                log_debug("round first lap\n");
                index++;
                int sc = 1;
                // scan the next ring
                while (_rings[index].cycle(sc, this)) {
                    sc = 1;
                    index ++;
                    if (index >= RINGS_SIZE)
                    {
                        struct timeval tv;
                        gettimeofday(&tv, NULL);
                        _start_time = tv.tv_sec;
                        break;
                    }
                }
            }
        }
        return ret;
    } 
    int get_free_timer_id() {
        if (full()) {
            alloc_heap(0);
        }
        int ret = _free_timerid_list.front();
        _free_timerid_list.pop_front();
        // check _heap[ret] is NULL
        if (_heap[ret] != NULL)
            log_debug("alloc a using item")
        return ret;
    }
protected:

	// timer obj heap
	vector<TimerItem*>   _heap;
    std::list<int>	    _free_timerid_list;
	size_t			    _heap_size;
	// used count of HEAP
	int				    _used_num;
	int				    _cur_heap_pos;
	// init time value
    int				    _start_time;
    // last expire time
    int				    _pre_time;
	// timer ring
	TimerRing		    _rings[RINGS_SIZE];	//0 is low，3 is high. 256 scales in each wheel
};