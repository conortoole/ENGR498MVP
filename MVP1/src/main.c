#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/uart.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

void main(void)
{
    
    const struct device *uart_dev;
    uint8_t gps_data[256];
    int gps_data_index = 0;
    int longitude = 0;
    int latitude = 0;

    uart_dev = device_get_binding("UART_0");
    if (!uart_dev) {
        printk("Error: could not bind to device.\n");
        return;
    }

    struct uart_config uart_cfg = {
        .baudrate = 9600,
        .data_bits = UART_CFG_DATA_BITS_8,
        .parity = UART_CFG_PARITY_NONE,
        .stop_bits = UART_CFG_STOP_BITS_1,
    };

    uart_configure(uart_dev, &uart_cfg);

    while (1) {

        uint8_t rx_data;
        if (uart_poll_in(uart_dev, &rx_data) == 0){
            if (rx_data == '\n') {
                // End of line, process the complete GPS data
                gps_data[gps_data_index] = '\0'; // Null-terminate the string
                printk("GPS Data: %s\n", gps_data);
                //longitude = gps_data[];
                // Reset the index for the next set of data
                gps_data_index = 0;
            } else {
                // Store the received character in the buffer
                if (gps_data_index < 256 - 1) {
                    gps_data[gps_data_index++] = rx_data;
                } else {
                    // Buffer overflow, handle it accordingly
                    printk("GPS Data Buffer Overflow\n");
                    gps_data_index = 0; // Reset the index
                }
            }
        }
        k_sleep(K_MSEC(1000));  // Sleep for 1 second (adjust as needed)
    }
}