#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity): dataStream(capacity), readidx(0), writeidx(0), _capacity(capacity), isEnd(false), _error(false){}

size_t ByteStream::write(const string &data) {
    size_t count = 0;
    size_t sz = data.size();
    while(writeidx - readidx < _capacity && count < sz){
        dataStream[(writeidx++)%_capacity] = data[count++];
    }
    return count;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t count = 0;
    string s(len, '\0');
    size_t tempidx = readidx;
    while(count<len && tempidx < writeidx){
        s[count++] = dataStream[(tempidx++)%_capacity];
    }
    return s;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t dis = writeidx - readidx;
    if(dis > len)
        readidx += len;
    else
        readidx = writeidx;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string ans = peek_output(len);
    pop_output(len);
    return ans;
}

void ByteStream::end_input() {
    isEnd = true;
}

bool ByteStream::input_ended() const {
    return isEnd;
}

size_t ByteStream::buffer_size() const {
    return writeidx - readidx;
}

bool ByteStream::buffer_empty() const {
    return readidx == writeidx;
}

bool ByteStream::eof() const {
    return isEnd && readidx == writeidx;
}

size_t ByteStream::bytes_written() const {
    return writeidx;
}

size_t ByteStream::bytes_read() const {
    return readidx;
}

size_t ByteStream::remaining_capacity() const {
    return _capacity - (writeidx - readidx);
}
