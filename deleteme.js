var fs = require('fs');
var fileIcon = require('./lib');
//var diablo = fileIcon('D:\\Data\\Games\\Diablo III\\Diablo III Launcher.exe');
//
//console.log(diablo.length);
//
//fs.writeFileSync('diablo.png', diablo);

//var obj = new fileIcon.FileIcon('C:\\Windows\\System32\\calc.exe');
var obj = new fileIcon.FileIcon("C:\\Program Files (x86)\\Diablo III\\Diablo III Launcher.exe");

//console.log(obj.getValue());
//console.log(obj.plusOne());
//console.log(obj.getValue());

console.log(obj.getAllIcons());