import 'dart:ffi' as ffi;
//import 'dart:io' as io;
//import 'package:ffi/ffi.dart' as pffi;

// C func
typedef flush_fd = ffi.Void Function(ffi.Int32 fd);
typedef FlushFDDart = void Function(int fd);

typedef open_fd = ffi.Int32 Function();
typedef OpenFDDart = int Function();

void main() async {
  //final io.File sharedLibrary = io.File('./main.o');
  final ffi.DynamicLibrary dylib = ffi.DynamicLibrary.open('./libjoystick_library.so');
  final FlushFDDart flushFD = dylib.lookup<ffi.NativeFunction<flush_fd>>('flushFD').asFunction<FlushFDDart>();
  final OpenFDDart openFD = dylib.lookup<ffi.NativeFunction<open_fd>>('openFD').asFunction<OpenFDDart>();

  final int fd = openFD();
  while (true) {
    flushFD(fd);
  }
}
