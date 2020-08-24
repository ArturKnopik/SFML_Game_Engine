#pragma once

#ifdef KOD_API_EXPORT
  #define KOD_API __declspec(dllexport)
#else
  #define KOD_API __declspec(dllimport)
#endif
