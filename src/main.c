/******************************************************************************
 * @brief Circular buffer application test.
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "circbuf.h"

/**
 * Size of the circular buffer.
 */
#define BUFFER_SIZE         10

static inline void print_buffer_state(const circbuf_t *buf);

/**
 * @brief Application which test the circular buffer module.
 */
int main()
{
    uint8_t buffer_memory[BUFFER_SIZE];
    circbuf_t buffer;

    /* Initialize circular buffer */
    circbuf_init(&buffer, buffer_memory, sizeof(buffer_memory));

    /* Print buffer info */
    printf("*** Buffer info ***\n");
    printf("Size: %d\n", (int) circbuf_size(&buffer));
    printf("Len: %d\n", (int) circbuf_len(&buffer));
    printf("\n");

    while (1)
    {
        bool b_result;
        uint8_t value = rand();

        printf("Storing %d... ", value);

        /* Store value in circular buffer */
        b_result = circbuf_write(&buffer, &value, sizeof(value));

        if (b_result)
        {
            size_t len;
            uint8_t stored = 0;

            printf("OK\n");

            printf("Restoring %d... ", value);

            /* Restore value from circular buffer */
            len = circbuf_read(&buffer, &stored, sizeof(stored));

            /* Check if restored value is correct */
            if ((len == sizeof(stored)) && (stored == value))
            {
                printf("OK\n");

                /* Print current buffer state */
                print_buffer_state(&buffer);
            }
            else
            {
                printf("Error\n");
            }
        }
        else
        {
            printf("Error\n");
        }

        printf("\n");

        /* Wait for a while */
        sleep(1);
    }

    return 0;
}

/**
 * @brief Print buffer state.
 *
 * @param buf  Circular buffer to print its state.
 */
static inline void print_buffer_state(const circbuf_t *buf)
{
    printf("Read: %d ; Write: %d\n", (int) buf->read_idx, (int) buf->write_idx);
}
