//
// Created by lwilkinson on 10/30/21.
//
// Adapted from: https://gist.github.com/keisukefukuda/8141120
//

#ifndef CSC2222_PAPIDEMO_PAPI_UTILS_H
#define CSC2222_PAPIDEMO_PAPI_UTILS_H

#include <iostream>
#include <papi.h>

#define ERRCODE(ecode) case ecode : err = #ecode; break
#define PAPI_SAFE_CALL(stmt) do {                 \
    int ret = (stmt);                             \
    if (ret < PAPI_OK) {                          \
      const char *err = "(unknown)";              \
      switch(ret) {                               \
        ERRCODE(PAPI_EATTR);                      \
        ERRCODE(PAPI_EBUF);                       \
        ERRCODE(PAPI_EBUG);                       \
        ERRCODE(PAPI_ECLOST);                     \
        ERRCODE(PAPI_ECMP);                       \
        /*ERRCODE(PAPI_ESBSTR); same value -4 */  \
        ERRCODE(PAPI_ECNFLCT);                    \
        ERRCODE(PAPI_ECOMBO);                     \
        ERRCODE(PAPI_ECOUNT);                     \
        ERRCODE(PAPI_EINVAL);                     \
        ERRCODE(PAPI_EINVAL_DOM);                 \
        ERRCODE(PAPI_EISRUN);                     \
        ERRCODE(PAPI_EMISC);                      \
        ERRCODE(PAPI_ENOCMP);                     \
        ERRCODE(PAPI_ENOCNTR);                    \
        ERRCODE(PAPI_ENOEVNT);                    \
        ERRCODE(PAPI_ENOEVST);                    \
        ERRCODE(PAPI_ENOIMPL);                    \
        ERRCODE(PAPI_ENOINIT);                    \
        ERRCODE(PAPI_ENOMEM);                     \
        ERRCODE(PAPI_ENOSUPP);                    \
        ERRCODE(PAPI_ENOTPRESET);                 \
        ERRCODE(PAPI_ENOTRUN);                    \
        ERRCODE(PAPI_EPERM);                      \
        ERRCODE(PAPI_ESYS);                       \
      }                                           \
      fprintf(stderr,                             \
           "%s:%d :[PAPI] %s failed: %s (%d).\n", \
           __FILE__, __LINE__, #stmt, err, ret);  \
      exit(-1);                                   \
    }                                             \
} while(0)

//For Error codes please see https://www.ibm.com/docs/en/zos/2.2.0?topic=papi-return-codes
#define ERROR_RETURN(retval) { \
    if(retval !=PAPI_OK)                \
    {                              \
    fprintf(stderr, "Error %d %s:line %d: \n", retval,__FILE__,__LINE__);  exit(retval); \
    }\
}

#endif //CSC2222_PAPIDEMO_PAPI_UTILS_H
