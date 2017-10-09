#include "hid_LINUX.h"

typedef struct hid_struct hid_t;

int rawhid_open(int max, hid_t **devs, int vid, int pid, int usage_page, int usage);
int rawhid_recv(hid_t *hid, void *buf, int len, int timeout);
int rawhid_send(hid_t *hid, void *buf, int len, int timeout);
int rawhid_close(hid_t *hid);

