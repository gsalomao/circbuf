/******************************************************************************
 * @brief Circular buffer module.
 *****************************************************************************/

#ifndef CIRCBUF_H_
#define CIRCBUF_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/** Circular buffer. */
typedef struct
{
    uint8_t *memory;
    size_t size;
    size_t len;
    size_t read_idx;
    size_t write_idx;

} circbuf_t;

/**
 * Get number of bytes in circular buffer.
 *
 * @param   buffer  Circular buffer to get the length.
 * @return  Number of bytes in the given circular buffer.
 */
static inline size_t circbuf_len(circbuf_t *buffer)
{
    return buffer->len;
}

/**
 * Get the size of the circular buffer.
 *
 * @param  buffer  Circular buffer to get the size.
 * @param  Size of the circular buffer.
 */
static inline size_t circbuf_size(circbuf_t *buffer)
{
    return buffer->size;
}

/**
 * Clean circular buffer.
 *
 * @param   buffer  Circular buffer to be cleaned.
 */
static inline void circbuf_clean(circbuf_t *buffer)
{
    buffer->len = 0;
    buffer->read_idx = 0;
    buffer->write_idx = 0;
}

void circbuf_init(circbuf_t *buffer, void *memory, size_t size);
bool circbuf_copy(circbuf_t *dest_buffer, const circbuf_t *src_buffer);
bool circbuf_write(circbuf_t *buffer, uint8_t *data, size_t size);
size_t circbuf_read(circbuf_t *buffer, uint8_t *data, size_t num);

#endif /* CIRCBUF_H_ */
