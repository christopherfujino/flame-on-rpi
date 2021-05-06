//import 'dart:io' as io;

import 'package:joystick_plugin/joystick_plugin.dart';

void main() {
  print('hello from dart');
  print(add(1, 2));
  final int fd = openFD();
  print('got fd $fd');
  while (true) {
    //io.sleep(Duration(milliseconds: 50));
    final int x = flushFD(fd);
    if (x >= 0) {
      print('pressed button $x');
    }
  }
}
