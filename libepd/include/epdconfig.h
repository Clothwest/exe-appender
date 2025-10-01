#pragma once

#if defined(LIBEPD_BUILD_AS_DLL)

#if defined(EPD_LIB)
#define EPD_API __declspec(dllexport)
#else
#define EPD_API __declspec(dllimport)
#endif

#else

#define EPD_API extern

#endif
