//
// Created by Andrew Wade on 6/26/18.
//

#ifndef TESTABLE_PLATFORM_H
#define TESTABLE_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************** Port Definitions ************************/

#ifndef VOID
#define VOID void
#endif /* VOID */

#ifndef NULL
#define NULL ((void*)0)
#endif /* NULL */

#ifndef BOOL
#define BOOL _Bool
#endif

#ifndef CHAR
#define CHAR char
#endif /* CHAR */

#ifndef UCHAR
#define UCHAR unsigned char
#endif /* UCHAR */

#ifndef SHORT
#define SHORT short
#endif /* SHORT */

#ifndef USHORT
#define USHORT unsigned short
#endif /* USHORT */

#ifndef INT
#define INT int
#endif /* INT */

#ifndef UINT
#define UINT unsigned int
#endif /* UINT */

#ifndef U64
#define U64 unsigned long
#endif

#ifndef U32
#define U32 unsigned int
#endif

#ifndef U16
#define U16 unsigned short
#endif

#ifndef U8
#define U8 unsigned char
#endif

#ifndef I64
#define I64 unsigned long
#endif

#ifndef I32
#define I32 int
#endif

#ifndef I16
#define I16 short
#endif

#ifndef I8
#define I8 char
#endif

#ifndef LONG
#define LONG long
#endif /* LONG */

#ifndef ULONG
#define ULONG unsigned long
#endif /* ULONG */

#ifndef SIZE
#define SIZE unsigned long
#endif

#ifndef FLOAT
#define FLOAT float
#endif /* FLOAT */

#ifndef DOUBLE
#define DOUBLE double
#endif /* DOUBLE */

/* allow variadic macros */
#ifndef TEST_SUPPORT_VARIADIC_MACROS
#define TEST_SUPPORT_VARIADIC_MACROS 1
#endif

/* test output macro */
#ifndef TEST_OUTPUT
#define TEST_OUTPUT(fmt, ...) printf(fmt, ##__VA_ARGS__)

#define LOG_TEST_FAIL(test)
#define LOG_TEST_PASS(test)
#define LOG_TEST_SKIP(test)
#endif /* TEST_OUTPUT */

/******************* End of Port Definitions *********************/

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_PORTABLE_H
