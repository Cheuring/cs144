#ifndef TIMER_HH
#define TIMER_HH

#include <cstdint>
#include <cstdlib>
class Timer {
private:
    uint32_t _time_count{0};
    uint32_t _time_out{0};
    bool _is_running{false};

public:
    Timer() = default;
    Timer(const uint32_t time_out) : _time_out(time_out){}

    void stop(){ _is_running = false; }
    void set_time_out(const uint32_t time_out){ _time_out = time_out; }
    uint32_t get_time_out() { return _time_out; }
    void restart() { _is_running = true; _time_count = 0; }
    void tick(const size_t gap){
        if(_is_running){
            _time_count += gap;
        }
    }
    bool check_time_out() const { return _is_running && _time_count >= _time_out; }
    bool is_running() const { return _is_running; }
};

#endif