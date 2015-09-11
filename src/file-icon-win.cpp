#include <nan.h>

using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;
using Nan::GetFunction;
using Nan::New;
using Nan::Set;

NAN_METHOD(Get) {
  const char* path = "C:\\Windows\\System32\\calc.exe";
  SHFILEINFO s_sfi;

  ::SHGetFileInfo(path, FILE_ATTRIBUTE_NORMAL, &s_sfi, sizeof(s_sfi),
      SHGFI_ICON | SHGFI_USEFILEATTRIBUTES | SHGFI_SMALLICON);
  ICONINFO stIconInfo;
  GetIconInfo(s_sfi.hIcon, &stIconInfo);
  info.GetReturnValue().Set(5);
}

NAN_MODULE_INIT(InitAll) {
  Set(target, New<String>("get").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(Get)).ToLocalChecked());
}

NODE_MODULE(fileIcon, InitAll)