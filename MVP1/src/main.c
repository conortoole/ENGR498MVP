#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/uart.h>

#include "BluetoothMod.h"
#include "GPSMod.h"

#define SLEEP_TIME_MS   500

void Bluetooth_signal(struct Bluetooth* bluetooth) {
    int err;

    printk("Starting Beacon\n");

    // Enable Bluetooth
    err = bt_enable(Bluetooth_ready(bluetooth, err));
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
    }
}

void main(void)
{
    struct GPS gps;
    struct Bluetooth bluetooth;
    // bool devices_connected = true;

    // Initialize GPS module
    GPS_init(&gps);

    // Initialize Bluetooth module
    Bluetooth_init(&bluetooth);

    // Wait until both devices are connected
    // while (!devices_connected) {
    //     devices_connected = Bluetooth_is_connected(&bluetooth) && GPS_is_connected(&gps);
    // }

    bool loop_sequence = true;

    // Main loop
    while (loop_sequence) {
        // Update GPS data
        GPS_update_data(&gps);

        // Update Bluetooth packet data with GPS data
        Bluetooth_update_adata(&bluetooth, GPS_get_data(&gps));

        // Send Bluetooth signal
        Bluetooth_signal(&bluetooth);

        // Sleep for a specified time
        k_msleep(SLEEP_TIME_MS);
    }
}