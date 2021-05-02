import 'dart:async';
import 'dart:ffi' as ffi;

import 'package:flutter/services.dart';

ffi.DynamicLibrary joystickLib = ffi.DynamicLibrary.open('libjoystick_plugin_plugin.so');

typedef AddC = ffi.Int32 Function(ffi.Int32 x, ffi.Int32 y);
typedef AddDart = int Function(int x, int y);

final AddDart add = joystickLib.lookup<ffi.NativeFunction<AddC>>('add').asFunction();

class JoystickPlugin {
  static const MethodChannel _channel =
      const MethodChannel('joystick_plugin');

  static Future<String> get platformVersion async {
    final String version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }
}
