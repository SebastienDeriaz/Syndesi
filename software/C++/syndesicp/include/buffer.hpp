/**
 * @file buffer.hpp
 *
 * @brief General purpose buffer
 *
 * @author Sébastien Deriaz
 * @date 16.08.2022
 */

#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>

using std::byte;
using namespace std;

namespace syndesi {

/**
 * @brief Buffer class
 *
 */
class Buffer {
    class rawBuffer {
       private:
        byte* _data = nullptr;
        size_t _length = 0;
        // Buffer is defined externaly and not managed
        bool external = false;

       public:
        rawBuffer(){};
        rawBuffer(size_t length) {
            _data = reinterpret_cast<byte*>(malloc(length));
            if (_data == nullptr) {
                throw std::bad_alloc();
            } else {
                _length = length;
            }
        };
        ~rawBuffer() {
            if (_data != nullptr && !external) {
                free(reinterpret_cast<void*>(_data));
            }
        };
        rawBuffer(byte* buffer, size_t length) {
            _data = buffer;
            _length = length;
            external = true;
        };

        byte* start() {return _data;};
        size_t length() const { return _length; };
    };

   public:
    /**
     * @brief Construct a new empty Buffer object with size length
     *
     * @param length
     */
    Buffer();
    Buffer(size_t length);
    ~Buffer();
    Buffer(Buffer* parent, size_t offset, size_t length = 0);
    Buffer(char* buffer, size_t length);

   private:
    size_t _total_offset;
    size_t _offset;
    shared_ptr<rawBuffer> _data = nullptr;
    size_t _clipLength = 0;

   public:
    void allocate(size_t length);

    void deallocate();

    /**
     * @brief Create a subbuffer (with an offset compared to the first one)
     *
     * @param parent the parent buffer
     * @param offset the start offset of the data
     */
    void fromParent(const Buffer* parent, size_t offset, size_t length = 0);

    /**
     * @brief Init with the given buffer
     *
     * @param buffer
     * @param length
     */
    void fromBuffer(byte* buffer, size_t length);

    /**
     * @brief Create a sub-buffer
     *
     * @param offset offset from start
     * @param length length of sub-buffer (default to max)
     */
    Buffer offset(size_t offset, size_t length = 0);

    size_t length() const;

    /**
     * @brief Get the raw data pointer
     *
     */
    byte* data() const { return _data->start() + _offset; };

    /**
     * @brief Get the sub-buffer offset (from base buffer)
     *
     * @return size_t
     */
    size_t getOffset();
};
}  // namespace syndesi

#endif  // BUFFER_H