import 'dart:ffi';

DynamicLibrary joystickLib = DynamicLibrary.open('libjoystick_plugin_plugin.so');

typedef OpenFDC = Int32 Function();
typedef OpenFDDart = int Function();

final OpenFDDart openFD = joystickLib.lookup<NativeFunction<OpenFDC>>('openFD').asFunction();

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

// These are defined in linux/joystick.h
const int JS_EVENT_BUTTON = 0x01;
const int JS_EVENT_AXIS = 0x02;
const int JS_EVENT_INIT = 0x80;
