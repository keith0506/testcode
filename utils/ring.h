#include <set>
#include <vector>
#define MAX_RING_SIZE 4

using namespace std;
typedef set<int> ESet;
typedef vector<ESet> RingVec;

class IRingEvent {
public:
    virtual void on_event(int ring_id, int timer_id) = 0;
};
/*
 *   assume we have 4 ring.
 *   MAX_RING_SIZE scales on each ring, each unit is a set struct
 */
class TimerRing {
public:
    TimerRing(int ring_id = 0);
    ~TimerRing();
    void reset();
    bool add_element(int ring_pos, int timer_id);
    bool del_element(int pos, int timer_id);
    bool cycle(int &scale, IRingEvent* handler);
    int get_pos() const { return _pos; };
    int set_pos(int pos) { _pos = pos; };
    int  get_ring_id() const { return _ring_id;};
    void set_ring_id(int id) { _ring_id = id; };
    
private:
    void clear();
    int _ring_id;
    int _pos;
    RingVec _ring; // element is set
};