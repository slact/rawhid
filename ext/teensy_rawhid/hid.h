#ifdef OS_LINUX
#include "hid_LINUX.h"
#elifdef OS_MACOSX
#include "hid_MACOSX.h"
#elifdef OS_WINDOWS
#include "hid_WINDOWS.h"
#endif

typedef struct hid_struct hid_t;

int rawhid_open(int max, hid_t **devs, int vid, int pid, int usage_page, int usage);
int rawhid_recv(hid_t *hid, void *buf, int len, int timeout);
int rawhid_send(hid_t *hid, void *buf, int len, int timeout);
int rawhid_close(hid_t *hid);

