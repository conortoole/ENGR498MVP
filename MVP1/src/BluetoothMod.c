#include "BluetoothMod.h"

// Structure to hold Bluetooth data
struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),    //0
	BT_DATA_BYTES(BT_DATA_UUID16_ALL, 0xaa, 0xfe),      //1
	BT_DATA_BYTES(BT_DATA_SVC_DATA16,  //0              //2
		      0xaa,					   //1
			  0xfe,                    //2
		      0x10,                    //3
		      0x00,                    //4
		      'S',                     //5
		      't',                     //6
			  'a',                     //7
			  'r',                     //8
			  't',                     //9
			  'i',                     //10
			  'n',                     //11
			  'g',                     //12
			  '-',                     //13
			  'R',                     //14
			  'e',                     //15
			  'm',                     //16
			  'o',                     //17
			  't',                     //18
			  'e',                     //19
			  '-',                     //20
			  'I',                     //21
			  'D',                     //22
			  '-',                     //23
			  'B',                     //24
			  'e',                     //25
			  'a',                     //26
			  'c',                     //27
			  'o',                     //28
			  'n'	                   //29
              )
};

// Structure to hold Bluetooth service data
static const struct bt_data sd[] = {
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

// void Bluetooth_connect(struct Bluetooth* bluetooth) {
	
// }

// bool Bluetooth_is_connected(struct Bluetooth* bluetooth) {
// 	return bluetooth->connected;
// }

void Bluetooth_set_device_name(struct Bluetooth* bluetooth) {
	char name[30] = DEVICE_NAME;
	strcpy(bluetooth->DeviceName, name);
}

void Bluetooth_set_adata(struct Bluetooth* bluetooth) {
	bluetooth->AData = ad;
}

void Bluetooth_set_sdata(struct Bluetooth* bluetooth) {
	bluetooth->SData = sd;
}

void Bluetooth_init(struct Bluetooth* bluetooth) {
	Bluetooth_set_device_name(bluetooth);
	Bluetooth_set_adata(bluetooth);
	Bluetooth_set_sdata(bluetooth);
	bluetooth->connected = false;
}

void Bluetooth_update_adata(struct Bluetooth* bluetooth, uint8_t* newData) { //new data is 29 bytes long
	memcpy(ad + 2, newData, 29);
}	

int Bluetooth_ready(struct Bluetooth* bluetooth, int err) {
	char addr_s[30];
	bt_addr_le_t addr = {0};
	size_t count = 1;

	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return 1;
	}

	printk("Bluetooth initialized\n");

	err = bt_le_adv_start(BT_LE_ADV_NCONN_IDENTITY, ad, ARRAY_SIZE(ad),
			      sd, ARRAY_SIZE(sd));
	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return 1;
	}

	bt_id_get(&addr, &count);
	bt_addr_le_to_str(&addr, addr_s, sizeof(addr_s));

	printk("Beacon started, advertising as %s\n", addr_s);

	return 0;
}
