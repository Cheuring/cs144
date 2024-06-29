#include "stream_reassembler.hh"

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity), _capacity(capacity), _stream(capacity), _curidx(0), _eofidx(SIZE_MAX), _unassembled_num(0) {}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    if(eof) _eofidx = min(_eofidx, index + data.size());
    auto st = max(index, _curidx);
    auto ed = min(data.size() + index, min(_curidx + _capacity - _output.buffer_size(), _eofidx));
    for(size_t i = st, j = st - index; i < ed; ++i, ++j){
        auto &t = _stream[i % _capacity];
        if(t.second){
            if(t.first != data[j]) __throw_runtime_error("StreamReassembler::push_substring: Inconsistent substrings!");
        }else{
            t = {data[j], true};
            ++_unassembled_num;
        }
    }

    string str;
    while(_curidx < _eofidx && _stream[_curidx % _capacity].second){
        str += _stream[_curidx % _capacity].first;
        _stream[_curidx % _capacity] = {0, false};
        --_unassembled_num;
        ++_curidx;
    }
    _output.write(str);
    if(_curidx == _eofidx) _output.end_input(); 
}

size_t StreamReassembler::unassembled_bytes() const { return _unassembled_num; }

bool StreamReassembler::empty() const { return _unassembled_num == 0; }
