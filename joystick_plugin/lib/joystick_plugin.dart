//import 'dart:async';
import 'dart:ffi';

//import 'package:flutter/services.dart';

DynamicLibrary joystickLib = DynamicLibrary.open('libjoystick_plugin_plugin.so');

typedef OpenFDC = Int32 Function();
typedef OpenFDDart = int Function();

final OpenFDDart openFD = joystickLib.lookup<NativeFunction<OpenFDC>>('openFD').asFunction();

//struct js_event {
//	__u32 time;	/* event timestamp in milliseconds */
//	__s16 value;	/* value */
//	__u8 type;	/* event type */
//	__u8 number;	/* axis/button number */
//};

class JSEvent extends Struct {
  @Uint32()
  external int time; // event timestamp in milliseconds

  @Int16()
  external int value; // value

  @Uint8()
  external int type; // event type

  @Uint8()
  external int number; // axis/button number
}

typedef FlushFDC = Pointer<JSEvent> Function(Int32 fd);
typedef FlushFDDart = Pointer<JSEvent> Function(int fd);

final FlushFDDart flushFD = joystickLib.lookup<NativeFunction<FlushFDC>>('flushFD').asFunction();
