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
struct js_event global_event;

extern "C" __attribute__((visibility("default"))) __attribute__((used))
struct js_event *flushFD(int fd) {
  struct js_event e;
  ssize_t bytes_read;
  bytes_read = read(fd, &e, sizeof(e));
  if (bytes_read <= 0) {
    // errno will be EAGAIN when there is nothing to read from the buffer
    if (errno != EAGAIN) {
      fprintf(stderr, "Oops! Error reading: %d\n", errno);
      exit(1);
    }
    // no events to flush
    return nullptr;
  }
  // These are not true events, but initialization events to ID available
  // buttons.
  if (e.type & JS_EVENT_INIT) {
    // These are ignored
    // If you want to dynamically map these buttons from your Flutter code, you
    // must return these events
    return nullptr;
  }
  global_event = e;
  return &global_event;
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
