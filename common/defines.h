#pragma once

#ifdef __cplusplus
#define CPP_GUARD_S extern "C" {
#define CPP_GUARD_E }
#else 
#define CPP_GUARD_S
#define CPP_GUARD_E
#endif

#ifdef WINDOWS
#define PUB __declspec(dllexport)
#define CALL __cdecl
#else
#define PUB
#define CALL
#endif
