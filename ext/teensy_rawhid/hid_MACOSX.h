#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDLib.h>

#include "hid.h"

#define BUFFER_SIZE 64
// a list of all opened HID devices, so the caller can
// simply refer to them by number
typedef struct hid_struct hid_t;
typedef struct buffer_struct buffer_t;

struct hid_struct {
	IOHIDDeviceRef ref;
	int open;
	uint8_t buffer[BUFFER_SIZE];
	buffer_t *first_buffer;
	buffer_t *last_buffer;
	struct hid_struct *prev;
	struct hid_struct *next;
};
struct buffer_struct {
	struct buffer_struct *next;
	uint32_t len;
	uint8_t buf[BUFFER_SIZE];
};
