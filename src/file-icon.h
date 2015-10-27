#ifndef FILEICON_H
#define FILEICON_H

#include <nan.h>
#include <list>

class FileIcon : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init);

 private:
  explicit FileIcon(std::string path);
  ~FileIcon();

  static NAN_METHOD(New);
//  static NAN_METHOD(GetIcon);
  static NAN_METHOD(GetAllIcons);
  static Nan::Persistent<v8::Function> constructor;
  std::string _path;
};

#endif