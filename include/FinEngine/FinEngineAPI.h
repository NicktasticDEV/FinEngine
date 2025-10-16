#pragma once

#if defined(_WIN32) || defined(__CYGWIN__)
  #if defined(FINENGINE_BUILD_DLL)
    #define FINENGINE_API __declspec(dllexport)
  #else
    #define FINENGINE_API __declspec(dllimport)
  #endif
#else
  #define FINENGINE_API
#endif
