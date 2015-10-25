{
  "targets": [
    {
      "target_name": "fileIcon",
      "sources": ["src/main-win.cpp", "src/file-icon.h", "src/file-icon.cpp"],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    }
  ]
}
