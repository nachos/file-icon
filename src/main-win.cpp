#include <nan.h>
#include <gdiplus.h>
#include <shlwapi.h>

#include "file-icon.h"

using namespace Gdiplus;

#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib,"Shlwapi.lib")

using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;
using Nan::GetFunction;
using Nan::New;
using Nan::NewBuffer;
using Nan::Set;

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

IStream* HICONToIStream(HICON hIcon) {
  GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR gdiplusToken;
  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

  Bitmap* b = Bitmap::FromHICON(hIcon);

  CLSID   encoderClsid;

  GetEncoderClsid(L"image/png", &encoderClsid);
  IStream* pStream = SHCreateMemStream(NULL, 0);

  b->Save(pStream, &encoderClsid, NULL);

  delete b;
  GdiplusShutdown(gdiplusToken);

  return pStream;
}

char * IStreamToByteArray(IStream* pStream, ULONG* bytesSaved) {
  STATSTG myStreamStats = {0};
  pStream->Stat(&myStreamStats, 0);
  char* streamData = new char[myStreamStats.cbSize.QuadPart];
  LARGE_INTEGER li;
  li.QuadPart = 0;

  pStream->Seek(li, STREAM_SEEK_SET, NULL);
  pStream->Read(streamData, myStreamStats.cbSize.QuadPart, bytesSaved);

  pStream->Release();

  return streamData;
}

NAN_METHOD(Get) {
  String::Utf8Value filePathV8(info[0]->ToString());
  const char* filePath = *filePathV8;

  SHFILEINFO s_sfi;

  ::SHGetFileInfo(filePath, FILE_ATTRIBUTE_NORMAL, &s_sfi, sizeof(s_sfi),
  SHGFI_ICON | SHGFI_USEFILEATTRIBUTES | SHGFI_LARGEICON);

  IStream* pStream = HICONToIStream(s_sfi.hIcon);
  ULONG bytesSaved = 0;

  char* streamData = IStreamToByteArray(pStream, &bytesSaved);

  info.GetReturnValue().Set(NewBuffer(streamData, bytesSaved).ToLocalChecked());
}

NODE_MODULE(fileIcon, FileIcon::Init)