//
//  Generated file. Do not edit.
//

#include "generated_plugin_registrant.h"

#include <joystick_plugin/joystick_plugin.h>

void fl_register_plugins(FlPluginRegistry* registry) {
  g_autoptr(FlPluginRegistrar) joystick_plugin_registrar =
      fl_plugin_registry_get_registrar_for_plugin(registry, "JoystickPlugin");
  joystick_plugin_register_with_registrar(joystick_plugin_registrar);
}
