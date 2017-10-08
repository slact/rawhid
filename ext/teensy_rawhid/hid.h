
int rawhid_open(int max, void **devs, int vid, int pid, int usage_page, int usage);
int rawhid_recv(void *dev, void *buf, int len, int timeout);
int rawhid_send(void *dev, void *buf, int len, int timeout);
void rawhid_close(void *dev);

