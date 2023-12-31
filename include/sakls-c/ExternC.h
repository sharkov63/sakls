///
/// \file ExternC.h
/// Defines an 'extern "C"' wrapper.
///
#ifndef SAKLS_C_EXTERN_C_H
#define SAKLS_C_EXTERN_C_H

#ifdef __cplusplus
#define SAKLS_EXTERN_C_BEGIN extern "C" {
#define SAKLS_EXTERN_C_END }
#else
#define SAKLS_EXTERN_C_BEGIN
#define SAKLS_EXTERN_C_END
#endif

#endif
