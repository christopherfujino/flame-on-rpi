//import 'dart:io' as io;
import 'dart:ffi' as ffi;

import 'package:joystick_plugin/joystick_plugin.dart';

// These are defined in linux/joystick.h
const int JS_EVENT_BUTTON = 0x01;
const int JS_EVENT_AXIS = 0x02;
const int JS_EVENT_INIT = 0x80;

enum ButtonPress {
  Up,
  Down,
}

enum XAxis {
  Left,
  Right,
}

enum YAxis {
  Up,
  Down,
}

class Game {
  final int fd = openFD();

  static XAxis lastX = XAxis.Left; // Arbitrary initial value
  static YAxis lastY = YAxis.Up; // Arbitrary initial value

  void update() {
    final ffi.Pointer<JSEvent> event = flushFD(fd);
    if (event != ffi.nullptr) {
      switch (event.ref.type) {
        case JS_EVENT_BUTTON:
          final ButtonPress pressType = event.ref.value == 1 ? ButtonPress.Down : ButtonPress.Up;
          switch (event.ref.number) {
            case 0:
              buttonA(pressType);
              break;
            case 1:
              buttonB(pressType);
              break;
            case 2:
              buttonX(pressType);
              break;
            case 3:
              buttonY(pressType);
              break;
            case 4:
              buttonL(pressType);
              break;
            case 5:
              buttonR(pressType);
              break;
            case 6:
              buttonSelect(pressType);
              break;
            case 7:
              buttonStart(pressType);
              break;
            default:
              // TODO just ignore these
              throw Exception("Oops! Unsupported button: ${event.ref.number}");
          }
          break;
        case JS_EVENT_AXIS:
          switch (event.ref.number) {
            case 6: // X-axis
              if (event.ref.value > 0) {
                lastX = XAxis.Right;
                buttonRight(ButtonPress.Down);
              } else if (event.ref.value < 0) {
                lastX = XAxis.Left;
                buttonLeft(ButtonPress.Down);
              } else {
                if (lastX == XAxis.Right) {
                  buttonRight(ButtonPress.Up);
                } else {
                  buttonLeft(ButtonPress.Up);
                }
              }
              break;
            case 7: // Y-axis
              if (event.ref.value > 0) {
                lastY = YAxis.Down;
                buttonDown(ButtonPress.Down);
              } else if (event.ref.value < 0) {
                lastY = YAxis.Up;
                buttonUp(ButtonPress.Down);
              } else {
                if (lastY == YAxis.Up) {
                  buttonUp(ButtonPress.Up);
                } else {
                  buttonDown(ButtonPress.Up);
                }
              }
              break;
          }
          break;
        case JS_EVENT_INIT:
          // These should be discarded by the C code
          throw Exception('Received unexpected JS_EVENT_INIT event');
        default:
          throw Exception('Unknown event type ${event.ref.type}');
      }
    }
  }

  void buttonUp(ButtonPress press) => print('You ${press == ButtonPress.Down ? 'pressed' : 'released'} up!');
  void buttonRight(ButtonPress press) => print('You ${press == ButtonPress.Down ? 'pressed' : 'released'} right!');
  void buttonDown(ButtonPress press) => print('You ${press == ButtonPress.Down ? 'pressed' : 'released'} down!');
  void buttonLeft(ButtonPress press) => print('You ${press == ButtonPress.Down ? 'pressed' : 'released'} left!');
  void buttonB(ButtonPress press) => print('You ${press == ButtonPress.Down ? 'pressed' : 'released'} B!');
  void buttonA(ButtonPress press) => print('You ${press == ButtonPress.Down ? 'pressed' : 'released'} A!');
  void buttonX(ButtonPress press) => print('You ${press == ButtonPress.Down ? 'pressed' : 'released'} X!');
  void buttonY(ButtonPress press) => print('You ${press == ButtonPress.Down ? 'pressed' : 'released'} Y!');
  void buttonL(ButtonPress press) => print('You ${press == ButtonPress.Down ? 'pressed' : 'released'} L!');
  void buttonR(ButtonPress press) => print('You ${press == ButtonPress.Down ? 'pressed' : 'released'} R!');
  void buttonStart(ButtonPress press) => print('You ${press == ButtonPress.Down ? 'pressed' : 'released'} start!');
  void buttonSelect(ButtonPress press) => print('You ${press == ButtonPress.Down ? 'pressed' : 'released'} select!');
}

void main() {
  final Game game = Game();
  while (true) {
    game.update();
  }
}
