#include "nan.h"
using namespace v8;

#include "keytar.h"

namespace {

NAN_METHOD(AddPassword) {
  Nan::HandleScope scope;
  bool success = keytar::AddPassword(*String::Utf8Value(info[0]),
                                     *String::Utf8Value(info[1]),
                                     *String::Utf8Value(info[2]));
  info.GetReturnValue().Set(Nan::New<Boolean>(success));
}

NAN_METHOD(GetPassword) {
  Nan::HandleScope scope;
  std::string password;
  bool success = keytar::GetPassword(*String::Utf8Value(info[0]),
                                     *String::Utf8Value(info[1]),
                                     &password);
  if (success) {
    Local<String> val =
      Nan::New<String>(password.data(), password.length()).ToLocalChecked();
    info.GetReturnValue().Set(val);
  } else {
    info.GetReturnValue().Set(Nan::Null());
  }
}

NAN_METHOD(DeletePassword) {
  Nan::HandleScope scope;
  bool success = keytar::DeletePassword(*String::Utf8Value(info[0]),
                                        *String::Utf8Value(info[1]));
  info.GetReturnValue().Set(Nan::New<Boolean>(success));
}

NAN_METHOD(FindPassword) {
  Nan::HandleScope scope;
  std::string password;
  bool success = keytar::FindPassword(*String::Utf8Value(info[0]), &password);
  if (success) {
    Local<String> val =
      Nan::New<String>(password.data(), password.length()).ToLocalChecked();
    info.GetReturnValue().Set(val);
  } else {
    info.GetReturnValue().Set(Nan::Null());
  }
}

NAN_MODULE_INIT(Init) {
  Nan::SetMethod(target, "getPassword", GetPassword);
  Nan::SetMethod(target, "addPassword", AddPassword);
  Nan::SetMethod(target, "deletePassword", DeletePassword);
  Nan::SetMethod(target, "findPassword", FindPassword);
}

}  // namespace

NODE_MODULE(keytar, Init)
