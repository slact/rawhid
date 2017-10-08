#include "ruby.h"
//#include "ext_help.h"
#include <errno.h>
#include <inttypes.h>
#include "hid.h"

#define GET_RAWHID(name, val)         \
  void               *name;           \
  Data_Get_Struct(val, void, name)

VALUE RawHID;
VALUE RawHIDError;

VALUE RawHID_new(VALUE class, VALUE vendorId, VALUE productId) {
  void    *dev = NULL;
  int      vId = NUM2INT(vendorId);
  int      pId = NUM2INT(pId);
  int      devices_opened = rawhid_open(1, &dev, vId, pId, -1, -1);
  if(devices_opened == 0 || dev == NULL) {
    rb_raise(RawHIDError, "Unable to open device");
  }
  
  VALUE self = Data_Wrap_Struct(class, NULL, rawhid_close, dev);
  return self;
}

VALUE RawHID_send(int argc, VALUE *argv, VALUE class) {
  VALUE    data, timeout_val;
  GET_RAWHID(dev, class);
  
  rb_scan_args(argc, argv, "11", &data, &timeout_val);
  
  char    *buf = StringValuePtr(data);
  int      len = RSTRING_LEN(data);
  int      timeout = (NIL_P(timeout_val)) ? 0 : NUM2INT(timeout_val);
  
  if(len == 0) {
    return INT2NUM(0);
  }
  int sent = rawhid_send(dev, buf, len, timeout);
  if(sent == -1) {
    rb_raise(RawHIDError, "Error sending data to device");
  }
  return INT2NUM(sent);
}

VALUE RawHID_recv(int argc, VALUE *argv, VALUE class) {
  VALUE    data, len_val, timeout_val;
  GET_RAWHID(dev, class);
  
  rb_scan_args(argc, argv, "11", &len_val,  &timeout_val);
  
  int      len = NUM2INT(len_val);
  int      timeout = (NIL_P(timeout_val)) ? 0 : NUM2INT(timeout_val);
  char     staticbuf[64];
  char    *buf=NULL;
  
  if(len <= 64) {
    buf = staticbuf;
  }
  else {
    buf = malloc(len);
    if(!buf) {
      rb_raise(RawHIDError, "Out of memory");
    }
  }
  int received = rawhid_recv(dev, buf, len, timeout);
  
  if(received == -1) {
    rb_raise(RawHIDError, "Error receiving data from device");
  }
  data = rb_str_new(buf, received);
  return data;
}

void Init_teensy_rawhid() {
  RawHID = rb_define_class("RawHID", rb_cObject);
  RawHIDError = rb_define_class_under(RawHID, "RawHIDError", rb_eRuntimeError);
  
  rb_define_singleton_method(RawHID, "new", RawHID_new, 2);
  rb_define_method(RawHID, "send", RawHID_send, -1);
  rb_define_method(RawHID, "recv", RawHID_recv, -1);
  
}



