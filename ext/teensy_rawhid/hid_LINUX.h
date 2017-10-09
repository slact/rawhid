#include <usb.h>
struct hid_struct {
	usb_dev_handle *usb;
	int open;
	int iface;
	int ep_in;
	int ep_out;
	struct hid_struct *prev;
	struct hid_struct *next;
};
