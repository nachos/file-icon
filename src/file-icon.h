#ifndef FILEICON_H
#define FILEICON_H

#include <nan.h>

using Nan::ObjectWrap;

class FileIcon : public ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit FileIcon(double value = 0);
  ~FileIcon();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void PlusOne(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Persistent<v8::Function> constructor;
  double value_;
};

#endif