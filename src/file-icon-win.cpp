#include <nan.h>

using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;
using Nan::GetFunction;
using Nan::New;
using Nan::Set;

NAN_METHOD(Test) {
  info.GetReturnValue().Set(5);
}

NAN_MODULE_INIT(InitAll) {
  Set(target, New<String>("test").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(Test)).ToLocalChecked());
}

NODE_MODULE(fileIcon, InitAll)