#include "ruby.h"
//#include "ext_help.h"
#include <errno.h>
#include <inttypes.h>
#include "hid.h"

#define GET_RAWHID(name, val)         \
  void              **name;           \
  Data_Get_Struct(val, void, name)

VALUE RawHID;
VALUE RawHIDError;

VALUE RawHID_new(VALUE class, VALUE vendorId, VALUE productId) {
  hid_t   *hid = NULL;
  int      vId = NUM2INT(vendorId);
  int      pId = NUM2INT(productId);
  
  VALUE self = Data_Make_Struct(class, hid_t, NULL, rawhid_close, hid);
  if(hid == NULL) {
    rb_raise(RawHIDError, "Out of memory");
  }
  rb_iv_set(self, "@vendorId", vendorId);
  rb_iv_set(self, "@productId", productId);
  
  rb_funcall(self, rb_intern("open"), 0);

  return self;
}

VALUE RawHID_open(VALUE self) {
  GET_RAWHID(hid, self);
  int      vId = NUM2INT(rb_iv_get(self, "@vendorId"));
  int      pId = NUM2INT(rb_iv_get(self, "@productId"));
  int      devices_opened = rawhid_open(1, &hid, vId, pId, -1, -1);
  if(devices_opened == 0) {
    rb_raise(RawHIDError, "Unable to open device");
  }
  return self;
}

VALUE RawHID_send(int argc, VALUE *argv, VALUE class) {
  VALUE    data, timeout_val;
  GET_RAWHID(hid, class);
  
  rb_scan_args(argc, argv, "11", &data, &timeout_val);
  
  char    *buf = StringValuePtr(data);
  int      len = RSTRING_LEN(data);
  int      timeout = (NIL_P(timeout_val)) ? 0 : NUM2INT(timeout_val);
  
  if(len == 0) {
    return INT2NUM(0);
  }
  int sent = rawhid_send(hid, buf, len, timeout);
  return INT2NUM(sent);
}

VALUE RawHID_close(VALUE class) {
  GET_RAWHID(hid, class);
  rawhid_close(hid) ? Qtrue : Qfalse;
}

VALUE RawHID_recv(int argc, VALUE *argv, VALUE class) {
  VALUE    data, len_val, timeout_val;
  GET_RAWHID(hid, class);
  
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
  int received = rawhid_recv(hid, buf, len, timeout);
  
  if(received < 0) {
    return INT2NUM(received);
  }
  data = rb_str_new(buf, received);
  return data;
}

void Init_teensy_rawhid() {
  RawHID = rb_define_class("RawHID", rb_cObject);
  RawHIDError = rb_define_class_under(RawHID, "RawHIDError", rb_eRuntimeError);
  
  rb_define_singleton_method(RawHID, "new", RawHID_new, 2);
  rb_define_method(RawHID, "raw_send", RawHID_send, -1);
  rb_define_method(RawHID, "raw_recv", RawHID_recv, -1);
  rb_define_method(RawHID, "open", RawHID_open, 0);
  rb_define_method(RawHID, "close", RawHID_close, 0);
  
}



