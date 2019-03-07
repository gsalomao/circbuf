/******************************************************************************
 * @brief Circular buffer module.
 *****************************************************************************/

#include "circbuf.h"

/**
 * Initialize circular buffer.
 *
 * @param   buffer  Circular buffer to be initialized.
 * @param   memory  Memory area where data will be stored.
 * @param   size    Memory size.
 */
void circbuf_init(circbuf_t *buffer, void *memory, size_t size)
{
    buffer->memory = (uint8_t *) memory;
    buffer->size = size;

    circbuf_clean(buffer);
}

/**
 * Copy content from a circular buffer (source) to another circular buffer
 * (destination).
 *
 * @note    This operation does not change any value in the source buffer).
 *
 * @param   dest_buffer     Destination circular buffer.
 * @param   src_buffer      Source circular buffer.
 *
 * @retval  true:   Source buffer was copied with success to destination buffer.
 * @retval  false:  There is no enough space in the destination buffer to hold
 *                  the amount of data stored in source buffer.
 */
bool circbuf_copy(circbuf_t *dest_buffer, const circbuf_t *src_buffer)
{
    bool b_result = false;

    if (dest_buffer->size >= src_buffer->len)
    {
        size_t read_idx = src_buffer->read_idx;

        dest_buffer->read_idx = 0;
        dest_buffer->write_idx = 0;

        while (dest_buffer->write_idx < src_buffer->len)
        {
            dest_buffer->memory[dest_buffer->write_idx++] =
                    src_buffer->memory[read_idx++];

            read_idx %= src_buffer->size;
        }

        dest_buffer->len = src_buffer->len;

        b_result = true;
    }

    return b_result;
}

/**
 * Write data to circular buffer.
 *
 * @param   buffer  Circular buffer to be written.
 * @param   data    Data to be written in circular buffer.
 * @param   size    Data size (number of bytes to be written).
 *
 * @retval  true:   Data was written with success.
 * @retval  false:  There is no available space for data.
 */
bool circbuf_write(circbuf_t *buffer, uint8_t *data, size_t size)
{
    bool b_result = false;

    if ((buffer->len + size) <= buffer->size)
    {
        while (size--)
        {
            buffer->memory[buffer->write_idx] = *data++;

            buffer->write_idx = (buffer->write_idx + 1) % buffer->size;
            buffer->len++;
        }

        b_result = true;
    }

    return b_result;
}

/**
 * Read data from circular buffer.
 *
 * @param   buffer  Circular buffer to be read.
 * @param   data    Pointer where read data shall be stored.
 * @param   num     Number of bytes to read.
 *
 * @return  Number of bytes read.
 */
size_t circbuf_read(circbuf_t *buffer, uint8_t *data, size_t num)
{
    size_t num_bytes_read = 0;

    while (buffer->len && (num_bytes_read < num))
    {
        *data++ = buffer->memory[buffer->read_idx];

        buffer->read_idx = (buffer->read_idx + 1) % buffer->size;
        buffer->len--;
        num_bytes_read++;
    }

    return num_bytes_read;
}
