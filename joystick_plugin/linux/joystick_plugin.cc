#include "include/joystick_plugin/joystick_plugin.h"

#include <errno.h> // errno
// For manipulating file descriptors
#include <fcntl.h> // for open(), O_RDONLY
#include <stdio.h>
#include <stdlib.h> // for exit()
#include <unistd.h> // for read()
#include <linux/joystick.h> // For js_event

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>
#include <sys/utsname.h>

#include <cstring>

#define JOYSTICK_PLUGIN(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), joystick_plugin_get_type(), \
                              JoystickPlugin))

// start my code
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
  static Button lastX = Left; // Arbitrary initial value
  static Button lastY = Up; // Arbitrary initial value
  enum PressType pressType;
  enum Button button;

  printf("Read successful:\n");
  switch (e.type) {
    case JS_EVENT_BUTTON:
      pressType = e.value == 1 ? DownPress : UpPress;
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
          // TODO just ignore these
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

extern "C" __attribute__((visibility("default"))) __attribute__((used))
int flushFD(int fd) {
  struct js_event e;
  ssize_t bytes_read;
  bytes_read = read(fd, &e, sizeof(e));
  if (bytes_read <= 0) {
    if (errno != EAGAIN) {
      fprintf(stderr, "Oops! Error reading: %d\n", errno);
      exit(1);
    }
    // no events to flush
    return -1;
  }
  if (e.type & JS_EVENT_INIT) {
    // ignore
    return -2; // TODO huh?
  }
  struct ButtonPress buttonPress = parsePress(e);
  printf("\tbutton\t= %i\n", buttonPress.button);
  printf("\ttype\t= %i\n", buttonPress.pressType);
  return buttonPress.button;
  //printf("Exiting flushFD...\n");
}

extern "C" __attribute__((visibility("default"))) __attribute__((used))
int openFD() {
  char device[] = "/dev/input/js0";
  int fd = open(device, O_NONBLOCK);
  if (fd == -1) {
    fprintf(stderr, "Error number %i while trying to open joystick\n", errno);
    exit(1);
  }
  printf("Opened %i\n", fd);
  return fd;
}

extern "C" __attribute__((visibility("default"))) __attribute__((used))
int add(int x, int y) {
  return x + y;
}

// end my code

struct _JoystickPlugin {
  GObject parent_instance;
};

G_DEFINE_TYPE(JoystickPlugin, joystick_plugin, g_object_get_type())

// Called when a method call is received from Flutter.
static void joystick_plugin_handle_method_call(
    JoystickPlugin* self,
    FlMethodCall* method_call) {
  g_autoptr(FlMethodResponse) response = nullptr;

  //const gchar* method = fl_method_call_get_name(method_call);

  response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());

  fl_method_call_respond(method_call, response, nullptr);
}

static void joystick_plugin_dispose(GObject* object) {
  G_OBJECT_CLASS(joystick_plugin_parent_class)->dispose(object);
}

static void joystick_plugin_class_init(JoystickPluginClass* klass) {
  G_OBJECT_CLASS(klass)->dispose = joystick_plugin_dispose;
}

static void joystick_plugin_init(JoystickPlugin* self) {}

static void method_call_cb(FlMethodChannel* channel, FlMethodCall* method_call,
                           gpointer user_data) {
  JoystickPlugin* plugin = JOYSTICK_PLUGIN(user_data);
  joystick_plugin_handle_method_call(plugin, method_call);
}

void joystick_plugin_register_with_registrar(FlPluginRegistrar* registrar) {
  JoystickPlugin* plugin = JOYSTICK_PLUGIN(
      g_object_new(joystick_plugin_get_type(), nullptr));

  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
  g_autoptr(FlMethodChannel) channel =
      fl_method_channel_new(fl_plugin_registrar_get_messenger(registrar),
                            "joystick_plugin",
                            FL_METHOD_CODEC(codec));
  fl_method_channel_set_method_call_handler(channel, method_call_cb,
                                            g_object_ref(plugin),
                                            g_object_unref);

  g_object_unref(plugin);
}
