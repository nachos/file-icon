#include "file-icon.h"

FileIcon::FileIcon(String::Utf8Value path) : _path(path) {
//  IntPtr hModule = IntPtr.Zero;
//  try
//  {
//      hModule = NativeMethods.LoadLibraryEx(fileName, IntPtr.Zero, LOAD_LIBRARY_AS_DATAFILE);
//      if (hModule == IntPtr.Zero)
//          throw new Win32Exception();
//
//      // Enumerate the icon resource and build .ico files in memory.
//
//      var tmpData = new List<byte[]>();
//
//      ENUMRESNAMEPROC callback = (h, t, name, l) =>
//      {
//          // Refer to the following URL for the data structures used here:
//          // http://msdn.microsoft.com/en-us/library/ms997538.aspx
//
//          // RT_GROUP_ICON resource consists of a GRPICONDIR and GRPICONDIRENTRY's.
//
//          var dir = GetDataFromResource(hModule, RT_GROUP_ICON, name);
//
//          // Calculate the size of an entire .icon file.
//
//          int count = BitConverter.ToUInt16(dir, 4);  // GRPICONDIR.idCount
//          int len = 6 + 16 * count;                   // sizeof(ICONDIR) + sizeof(ICONDIRENTRY) * count
//          for (int i = 0; i < count; ++i)
//              len += BitConverter.ToInt32(dir, 6 + 14 * i + 8);   // GRPICONDIRENTRY.dwBytesInRes
//
//          using (var dst = new BinaryWriter(new MemoryStream(len)))
//          {
//              // Copy GRPICONDIR to ICONDIR.
//
//              dst.Write(dir, 0, 6);
//
//              int picOffset = 6 + 16 * count; // sizeof(ICONDIR) + sizeof(ICONDIRENTRY) * count
//
//              for (int i = 0; i < count; ++i)
//              {
//                  // Load the picture.
//
//                  ushort id = BitConverter.ToUInt16(dir, 6 + 14 * i + 12);    // GRPICONDIRENTRY.nID
//                  var pic = GetDataFromResource(hModule, RT_ICON, (IntPtr)id);
//
//                  // Copy GRPICONDIRENTRY to ICONDIRENTRY.
//
//                  dst.Seek(6 + 16 * i, SeekOrigin.Begin);
//
//                  dst.Write(dir, 6 + 14 * i, 8);  // First 8bytes are identical.
//                  dst.Write(pic.Length);          // ICONDIRENTRY.dwBytesInRes
//                  dst.Write(picOffset);           // ICONDIRENTRY.dwImageOffset
//
//                  // Copy a picture.
//
//                  dst.Seek(picOffset, SeekOrigin.Begin);
//                  dst.Write(pic, 0, pic.Length);
//
//                  picOffset += pic.Length;
//              }
//
//              tmpData.Add(((MemoryStream)dst.BaseStream).ToArray());
//          }
//
//          return true;
//      };
//      NativeMethods.EnumResourceNames(hModule, RT_GROUP_ICON, callback, IntPtr.Zero);
//
//      iconData = tmpData.ToArray();
//  }
//  finally
//  {
//      if (hModule != IntPtr.Zero)
//          NativeMethods.FreeLibrary(hModule);
//  }
}

FileIcon::~FileIcon() {
}

Nan::Persistent<v8::Function> FileIcon::constructor;

NAN_MODULE_INIT(FileIcon::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(FileIcon::New);
  tpl->SetClassName(Nan::New("FileIcon").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

//  SetPrototypeMethod(tpl, "getValue", FileIcon::GetValue);
//  SetPrototypeMethod(tpl, "plusOne", FileIcon::PlusOne);

  constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("FileIcon").ToLocalChecked(),
    Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(FileIcon::New) {
  if (info.IsConstructCall()) {
    v8::String::Utf8Value filePathV8(info[0]->ToString());
    FileIcon *obj = new FileIcon(filePathV8);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New(constructor());
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}
//
//NAN_METHOD(FileIcon::PlusOne) {
//  FileIcon* obj = Nan::ObjectWrap::Unwrap<FileIcon>(info.This());
//  obj->value_ += 1;
//  info.GetReturnValue().Set(obj->value_);
//}
//
//NAN_METHOD(FileIcon::GetValue) {
//  FileIcon* obj = Nan::ObjectWrap::Unwrap<FileIcon>(info.This());
//  info.GetReturnValue().Set(obj->value_);
//}