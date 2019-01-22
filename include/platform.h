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
