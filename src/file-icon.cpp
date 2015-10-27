#include "file-icon.h"

#include <iostream>
#include <fstream>

char * GetDataFromResource(HMODULE hModule, LPCTSTR type, LPTSTR name) {
  HRSRC hResInfo = FindResource(hModule, name, type);

  if (hResInfo == NULL) {
    // TODO: exception
  }

  HGLOBAL hResData = LoadResource(hModule, hResInfo);

  if (hResData == NULL) {
    // TODO: exception
  }
  LPVOID pResData = LockResource(hResData);

  if (pResData == NULL) {
    // TODO: exception
  }

  unsigned int size = SizeofResource(hModule, hResInfo);

  if (size == 0) {
    // TODO: exception
  }

  char * buffer;

  memcpy (buffer, pResData, size);

  return buffer;
}

BOOL CALLBACK EnumResNameProc(HMODULE hModule, LPCTSTR lpszType, LPTSTR lpszName, LONG_PTR lParam) {
  std::list<std::string> *names = (std::list<std::string>*)lParam;
  names->push_back(lpszName);
  return TRUE;
}


FileIcon::FileIcon(std::string path) : _path(path) {
  HMODULE hModule = NULL;

  hModule = LoadLibraryEx(_path.c_str(), NULL, LOAD_LIBRARY_AS_DATAFILE);

  if (hModule == NULL) {
  // TODO: exception here
//        Nan::ErrnoException(GetLastError());
      return;
  }

  std::list<std::string> names;

  BOOL success = EnumResourceNames(hModule, RT_GROUP_ICON, EnumResNameProc, (LONG_PTR)&names);

  for (std::list<std::string>::iterator it=_names.begin(); it != _names.end(); ++it) {
      char* iconGroupData = GetDataFromResource(hModule, RT_GROUP_ICON, *it);

      GRPICONDIR hola = iconGroupData;
      hola.idCount;
  }

  if(!success) {
    // TODO: throw something
  }

  if (hModule != NULL) {
    FreeLibrary(hModule);
  }
}

FileIcon::~FileIcon() {
}

Nan::Persistent<v8::Function> FileIcon::constructor;

NAN_MODULE_INIT(FileIcon::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(FileIcon::New);
  tpl->SetClassName(Nan::New("FileIcon").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  SetPrototypeMethod(tpl, "getAllIcons", FileIcon::GetAllIcons);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("FileIcon").ToLocalChecked(),
    Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(FileIcon::New) {
  if (info.IsConstructCall()) {
    if (info.Length() < 1 || !info[0]->IsString())
    {
        Nan::ThrowTypeError("path must be a string");
        return;
    }
    FileIcon *obj = new FileIcon(*v8::String::Utf8Value(info[0]->ToString()));
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

NAN_METHOD(FileIcon::GetAllIcons) {
  FileIcon* obj = Nan::ObjectWrap::Unwrap<FileIcon>(info.This());

  v8::Local<v8::Array> returnValue = Nan::New<v8::Array>();

    int i = 0;
    for (std::list<std::string>::iterator it=obj->_names.begin(); it != obj->_names.end(); ++it) {
        returnValue->Set(i, Nan::New((*it).c_str()).ToLocalChecked());
        i++;
    }

  info.GetReturnValue().Set(returnValue);
//  info.GetReturnValue().Set(Nan::New(obj->_names).ToLocalChecked());
}