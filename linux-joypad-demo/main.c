// For manipulating file descriptors
#include <errno.h> // errno
#include <fcntl.h> // for open(), O_RDONLY
#include <stdio.h>
#include <stdlib.h> // for exit()
#include <unistd.h> // for read()
#include <linux/joystick.h> // For js_event

// https://www.kernel.org/doc/Documentation/input/joystick-api.txt

enum Button {
  Up = 0,
  Right = 1,
  Down = 2,
  Left = 3,
  Y = 4,
  B = 5,
  A = 6,
  X = 7,
  L = 8,
  R = 9,
  Select = 10,
  Start = 11,
};

enum PressType {
  UpPress = 0,
  DownPress = 1,
};

struct ButtonPress {
  enum Button button;
  enum PressType pressType;
};

struct ButtonPress parsePress(struct js_event e) {
  static int lastX = Left; // Arbitrary initial value
  static int lastY = Up; // Arbitrary initial value
  enum PressType pressType;
  enum Button button;

  printf("Read successful:\n");
  switch (e.type) {
    case JS_EVENT_BUTTON:
      pressType = e.value;
      switch (e.number) {
        case 0:
          button = A;
          break;
        case 1:
          button = B;
          break;
        case 2:
          button = X;
          break;
        case 3:
          button = Y;
          break;
        case 4:
          button = L;
          break;
        case 5:
          button = R;
          break;
        case 6:
          button = Select;
          break;
        case 7:
          button = Start;
          break;
        default:
          fprintf(stderr, "Oops! Unsupported button: %i\n", e.number);
          exit(1);
      }
      break;
    case JS_EVENT_AXIS:
      switch (e.number) {
        case 6: // X-axis
          if (e.value > 0) {
            button = lastX = Right;
            pressType = DownPress;
          } else if (e.value < 0) {
            button = lastX = Left;
            pressType = DownPress;
          } else {
            button = lastX;
            pressType = UpPress;
          }
          break;
        case 7: // Y-axis
          if (e.value > 0) {
            button = lastY = Down;
            pressType = DownPress;
          } else if (e.value < 0) {
            button = lastY = Up;
            pressType = DownPress;
          } else {
            button = lastY;
            pressType = UpPress;
          }
          break;
      }
      break;
    default:
      fprintf(stderr, "Oops! unknown js_event.type: 0x%x\n", e.type);
      exit(1);
  }

  return (struct ButtonPress){
    .button = button,
    .pressType = pressType,
  };
}

void flushFD(int fd) {
  struct js_event e;
  ssize_t bytes_read;
  while (read(fd, &e, sizeof(e)) > 0) {
    if (e.type & JS_EVENT_INIT) {
      // ignore
      continue;
    }
    struct ButtonPress buttonPress = parsePress(e);
    printf("\tbutton\t= %i\n", buttonPress.button);
    printf("\ttype\t= %i\n", buttonPress.pressType);
  }
  if (errno != EAGAIN) {
    fprintf(stderr, "Oops! %d\n", errno);
    exit(1);
  }
}

int main() {
  char device[] = "/dev/input/js0";

  int joystick = open(device, O_NONBLOCK);
  while(1) {
    flushFD(joystick);
  }
  return 0;
}
