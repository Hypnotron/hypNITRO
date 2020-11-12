#pragma once
#include <cstdio>
#if !defined(NDEBUG) && !defined(DISABLE_LOGGING)
    #include <SDL.h>
#endif

namespace debug {
    #if defined(NDEBUG) || defined(DISABLE_LOGGING)
        constexpr char* message {nullptr};
        inline int write(char* buffer, const char* fmt, ...) {
            return 0;
        }
        inline void info() {}
        inline void warn() {}
        inline void error() {}
    #else
        char message[2048];
        constexpr int (*write)(char* buffer, const char* fmt, ...) 
              = &std::sprintf;
        inline void info() {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", message);
        }
        inline void warn() {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", message);
        }
        inline void error() {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", message);
        }
    #endif
}


