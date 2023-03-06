#pragma once

#include "../audio-ports.h"

#ifdef __cplusplus
extern "C" {
#endif

// This extension lets the host add and remove audio ports
static CLAP_CONSTEXPR const char CLAP_EXT_EXTENSIBLE_AUDIO_PORTS[] =
   "clap.extensible-audio-ports.draft0";

typedef struct clap_plugin_extensible_audio_ports {
   // Asks the plugin to add a new port (at the end of the list), with the following settings.
   // Returns true on success.
   // port_type and port_details are analogous to what you'll find in audio-ports.h
   // [main-thread && !is_active]
   bool(CLAP_ABI *add_port)(const clap_plugin_t *plugin,
                            bool                 is_input,
                            uint32_t             channel_count,
                            const char          *port_type,
                            const void          *port_details);

   // Asks the plugin to remove a port.
   // Returns true on success.
   // [main-thread && !is_active]
   bool(CLAP_ABI *remove_port)(const clap_plugin_t *plugin, bool is_input, uint32_t index);
} clap_plugin_extensible_audio_ports_t;

#ifdef __cplusplus
}
#endif