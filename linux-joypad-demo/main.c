// For manipulating file descriptors
#include <fcntl.h> // for open(), O_RDONLY
#include <stdio.h>
#include <unistd.h> // for read()
#include <linux/joystick.h> // For js_event

// https://www.kernel.org/doc/Documentation/input/joystick-api.txt

int main() {
  char device[] = "/dev/input/js0";
  struct js_event e;
  ssize_t bytes_read;

  int joystick = open(device, O_RDONLY);
  while(1) {
    bytes_read = read(joystick, &e, sizeof(e));
    if (bytes_read <= 0) {
      printf("bytes_read == %zu\n", bytes_read);
      break;
    }
    if (e.type & JS_EVENT_INIT) {
      // ignore
      continue;
    }
    printf("Read successful:\n");
    printf("\tjs_event.number:\t%u\n", e.number);
    switch (e.type) {
      case JS_EVENT_BUTTON:
        printf("\tjs_event.type:\t\tJS_EVENT_BUTTON\n");
        printf("\tjs_event.value:\t\t%s\n", e.value == 0 ? "release" : "press");
        break;
      case JS_EVENT_AXIS:
        printf("\tjs_event.type:\t\tJS_EVENT_AXIS\n");
        printf("\tjs_event.value:\t\t%i\n", e.value);
        break;
      default:
        printf("Oops! unknown js_event.type: 0x%x\n", e.type);
        return 1;
    }
  }
  return 0;
}

enum Button {
  Up = 0,
  Right = 1,
  Down = 2,
  Left = 3,
  Y = 4,
  B = 5,
  A = 6,
  X = 7,
};

enum PressType {
  UpPress = 0,
  DownPress = 1,
};

struct ButtonPress {
  enum Button button;
  enum PressType pressType;
};

void parsePress(
  struct js_event event,
  struct ButtonPress *press) {
  // 1 is pressed, 0 is not
  static char ButtonMap[8] = {

  };
  enum PressType pressType;
  enum Button button;
}
