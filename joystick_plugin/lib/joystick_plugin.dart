import 'dart:async';
import 'dart:ffi' as ffi;

import 'package:flutter/services.dart';

ffi.DynamicLibrary joystickLib = ffi.DynamicLibrary.open('libjoystick_plugin_plugin.so');

typedef AddC = ffi.Int32 Function(ffi.Int32 x, ffi.Int32 y);
typedef AddDart = int Function(int x, int y);

final AddDart add = joystickLib.lookup<ffi.NativeFunction<AddC>>('add').asFunction();

typedef OpenFDC = ffi.Int32 Function();
typedef OpenFDDart = int Function();

final OpenFDDart openFD = joystickLib.lookup<ffi.NativeFunction<OpenFDC>>('openFD').asFunction();

typedef FlushFDC = ffi.Int32 Function(ffi.Int32 fd);
typedef FlushFDDart = int Function(int fd);

final FlushFDDart flushFD = joystickLib.lookup<ffi.NativeFunction<FlushFDC>>('flushFD').asFunction();
