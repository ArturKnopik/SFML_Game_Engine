#pragma once

#ifdef KOD_EXPORT
#define KOD_API __declspec(dllexport)
#else
#define KOD_API __declspec(dllimport)
#endif
