#ifndef FILEICON_H
#define FILEICON_H

#include <nan.h>

using v8::String;

class FileIcon : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init);

 private:
  explicit FileIcon(String::Utf8Value path);
  ~FileIcon();

  static NAN_METHOD(New);
//  static NAN_METHOD(GetIcon);
//  static NAN_METHOD(GetAllIcons);
  static Nan::Persistent<v8::Function> constructor;
  String::Utf8Value _path;
};

#endif