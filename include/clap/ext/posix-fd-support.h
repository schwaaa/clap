#pragma once

#include "../plugin.h"

// This extension let your plugin hook itself into the host select/poll/epoll/kqueue reactor.
static CLAP_CONSTEXPR const char CLAP_EXT_POSIX_FD_SUPPORT[] = "clap.posix-fd-support";

#ifdef __cplusplus
extern "C" {
#endif

enum {
   // IO events flags, they can be used to form a mask which describes:
   // - which events you are interested in (register_fd/modify_fd)
   // - which events happened (on_fd)
   CLAP_POSIX_FD_READ = 1 << 0,
   CLAP_POSIX_FD_WRITE = 1 << 1,
   CLAP_POSIX_FD_ERROR = 1 << 2,
};
typedef uint32_t clap_posix_fd_flags_t;

typedef struct clap_plugin_posix_fd_support {
   // This callback is "level-triggered".
   // It means that a writable fd will continuously produce "on_fd()" events;
   // don't forget using modify_fd() to remove the write notification once you're
   // done writting.
   //
   // [main-thread]
   void (*on_fd)(const clap_plugin_t *plugin, int fd, clap_posix_fd_flags_t flags);
} clap_plugin_posix_fd_support_t;

typedef struct clap_host_posix_fd_support {
   // [main-thread]
   bool (*register_fd)(const clap_host_t *host, int fd, clap_posix_fd_flags_t flags);

   // [main-thread]
   bool (*modify_fd)(const clap_host_t *host, int fd, clap_posix_fd_flags_t flags);

   // [main-thread]
   bool (*unregister_fd)(const clap_host_t *host, int fd);
} clap_host_posix_fd_support_t;

#ifdef __cplusplus
}
#endif
