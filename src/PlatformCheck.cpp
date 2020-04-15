/*
    All this checking is to ensure MicroLang 
    can be cross platform and it includes the right headers
    depending on each platform
*/

#if defined(_WIN32)
    #define PLATFORM_NAME "windows" // Windows
    #include <windows.h>
#elif defined(_WIN64)
    #define PLATFORM_NAME "windows" // Windows
    #include <windows.h>
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM_NAME "windows" // Windows (Cygwin POSIX under Microsoft Window)
    #include <windows.h>
#elif defined(__ANDROID__)
    #define PLATFORM_NAME "android" // Android (implies Linux, so it must come first)
#elif defined(__linux__)
    #define PLATFORM_NAME "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and others
    
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
    #include <sys/param.h>
    #if defined(BSD)
        #define PLATFORM_NAME "bsd" // FreeBSD, NetBSD, OpenBSD, DragonFly BSD
    #endif
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #define PLATFORM_NAME "ios" // Apple iOS
    #elif TARGET_OS_IPHONE == 1
        #define PLATFORM_NAME "ios" // Apple iOS
    #elif TARGET_OS_MAC == 1
        #define PLATFORM_NAME "osx" // Apple OSX
    #endif
#else
    #define PLATFORM_NAME NULL
#endif

// Return a name of platform, if determined, otherwise - an empty string
const char *get_platform_name() {
    return (PLATFORM_NAME == NULL) ? "" : PLATFORM_NAME;
}
