//
// Created by Andrew Wade on 12/16/18.
//

#ifndef TESTABLE_PP_H
#define TESTABLE_PP_H

#ifdef __cplusplus
extern "C" {
#endif
#define _DO_NOTHING(...)
#define _GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N

#define COUNT(...) _GET_NTH_ARG("ignored", ##__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define _CONCAT2(a, b) a b
#define _CONCAT3(a, b, c) a b c
#define _CONCAT4(a, b, c, d) a b c d
#define _CONCAT5(a, b, c, d, e) a b c d e
#define _CONCAT6(a, b, c, d, e, f) a b c d e f
#define _CONCAT7(a, b, c, d, e, f, g) a b c d e f g
#define _CONCAT8(a, b, c, d, e, f, g, h) a b c d e f g h
#define _CONCAT9(a, b, c, d, e, f, g, h, i) a b c d e f g h i

#define _CONCAT_OVERRIDE(_1, _2, _3, NAME, ...) NAME

#define CONCAT(...) _GET_NTH_ARG("ignored", __VA_ARGS__, _CONCAT9, _CONCAT8, _CONCAT7, _CONCAT6, _CONCAT5, _CONCAT4, _CONCAT3, _CONCAT2)(__VA_ARGS__)

#define _ODD_ARGS1(a) a
#define _ODD_ARGS2(a, b) a
#define _ODD_ARGS3(a, b, c) a, c
#define _ODD_ARGS4(a, b, c, d) a, c
#define _ODD_ARGS5(a, b, c, d, e) a, c, e

#define _ODD_OVERRIDE(_1, _2, _3, _4, _5, NAME, ...) NAME
#define ODD_ARGS(...) _ODD_OVERRIDE(__VA_ARGS__, _ODD_ARGS5, _ODD_ARGS4, _ODD_ARGS3, _ODD_ARGS2, _ODD_ARGS1)(__VA_ARGS__)

#define _EVEN_ARGS1(a)
#define _EVEN_ARGS2(a, b) b
#define _EVEN_ARGS3(a, b, c) b
#define _EVEN_ARGS4(a, b, c, d) b, d
#define _EVEN_ARGS5(a, b, c, d, e) b, d
#define _EVEN_ARGS6(a, b, c, d, e, f) b, d, f

#define _EVEN_OVERRIDE(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
#define EVEN_ARGS(...) _EVEN_OVERRIDE(__VA_ARGS__, _EVEN_ARGS6, _EVEN_ARGS5, _EVEN_ARGS4, _EVEN_ARGS3, _EVEN_ARGS2, _EVEN_ARGS1)(__VA_ARGS__)

#define _PAIR_ARGS2(a, b) a b
#define _PAIR_ARGS4(a, b, c, d) a b, c d
#define _PAIR_ARGS6(a, b, c, d, e, f) a b, c d, e f

#define _PAIR_OVERRIDE(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
#define PAIR_ARGS(...) _PAIR_OVERRIDE(__VA_ARGS__, _PAIR_ARGS6,_DO_NOTHING,_PAIR_ARGS4,_DO_NOTHING, _PAIR_ARGS2)(__VA_ARGS__)

#define COMMA ,
#define SEMICOL ;


#define _JOIN_ARGS1(s, a)                   a
#define _JOIN_ARGS2(s, a, b)                a s b
#define _JOIN_ARGS3(s, a, b, c)             a s b s c
#define _JOIN_ARGS4(s, a, b, c, d)          a s b s c s d
#define _JOIN_ARGS5(s, a, b, c, d, e)       a s b s c s d s e
#define _JOIN_ARGS6(s, a, b, c, d, e, f)    a s b s c s d s e f

#define _JOIN_OVERRIDE(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
#define JOIN_ARGS(separator, ...) _JOIN_OVERRIDE(__VA_ARGS__, _JOIN_ARGS6, _JOIN_ARGS5, _JOIN_ARGS4, _JOIN_ARGS3, _JOIN_ARGS2, _JOIN_ARGS1, _DO_NOTHING)(separator, __VA_ARGS__)

#define DEF_ARGS(...) JOIN_ARGS(SEMICOL, __VA_ARGS__)

#define _INIT_VAR1(name, value) {#name, value}
#define _INIT_VAR2(name, value, ...) {$name, value}

#define _LIST_FOREACH1_1(macro, ...) macro(__VA_ARGS__)
#define _LIST_FOREACH1_2(macro, ...) macro(__VA_ARGS__) _LIST_FOREACH_1(macro, __VA_ARGS__)
#define _LIST_FOREACH1_3(macro, ...) macro(arg) _LIST_FOREACH_2(macro, __VA_ARGS__)
#define _LIST_FOREACH1_4(macro, ...) macro(arg) _LIST_FOREACH_3(macro, __VA_ARGS__)
#define _LIST_FOREACH1_5(macro, ...) macro(arg) _LIST_FOREACH_4(macro, __VA_ARGS__)
#define _LIST_FOREACH1_6(macro, ...) macro(arg) _LIST_FOREACH_5(macro, __VA_ARGS__)
#define _LIST_FOREACH1_7(macro, ...) macro(arg) _LIST_FOREACH_6(macro, __VA_ARGS__)
#define _LIST_FOREACH1_8(macro, ...) macro(arg) _LIST_FOREACH_7(macro, __VA_ARGS__)
#define _LIST_FOREACH1_9(macro, ...) macro(arg) _LIST_FOREACH_8(macro, __VA_ARGS__)

#define _LIST_FOREACH2_2(macro, a, b, ...) macro(a, b)
#define _LIST_FOREACH2_4(macro, a, b, ...) _LIST_FOREACH2_2(macro, a, b), _LIST_FOREACH2_2(macro, __VA_ARGS__)
#define _LIST_FOREACH2_6(macro, a, b, ...) _LIST_FOREACH2_2(macro, a, b), _LIST_FOREACH2_4(macro, __VA_ARGS__)
#define _LIST_FOREACH2_8(macro, a, b, ...) _LIST_FOREACH2_2(macro, a, b), _LIST_FOREACH2_6(macro, __VA_ARGS__)
#define _LIST_FOREACH2_10(macro, a, b, ...) _LIST_FOREACH2_2(macro, a, b), _LIST_FOREACH2_8(macro, __VA_ARGS__)

#define LIST_FOREACH1(macro, ...) _GET_NTH_ARG(__VA_ARGS__, _LIST_FOREACH1_9, _LIST_FOREACH1_8, _LIST_FOREACH1_7, _LIST_FOREACH1_6, _LIST_FOREACH1_5, _LIST_FOREACH1_4, _LIST_FOREACH1_3, _LIST_FOREACH1_2, _LIST_FOREACH1_1, _DO_NOTHING)(macro, ##__VA_ARGS__)

#define LIST_FOREACH2(macro, ...) _GET_NTH_ARG(__VA_ARGS__, _LIST_FOREACH2_10, _LIST_FOREACH2_10, _LIST_FOREACH2_8, _LIST_FOREACH2_8, _LIST_FOREACH2_6, _LIST_FOREACH2_6, _LIST_FOREACH2_4, _LIST_FOREACH2_4, _LIST_FOREACH2_2, _LIST_FOREACH2_2, _DO_NOTHING, _DO_NOTHING)(macro, ##__VA_ARGS__)


#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__
#define IIF(c) PRIMITIVE_CAT(IIF_, c)
#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t

#define COMPL(b) PRIMITIVE_CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

#define BITBAND(x) PRIMITIVE_CAT(BITBAND_, x)
#define BITBAND_0(y) 0
#define BITBAND_1(y) y

#define CHECK_N(x, n, ...) n
#define CHECK(...) CHECK_N(__VA_ARGS__, 0,)
#define PROBE(x) x, 1,

#define IS_PAREN(x) CHECK(IS_PAREN_PROBE x)
#define IS_PAREN_PROBE(...) PROBE(~)

#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_, x))
#define NOT_0 PROBE(~)

#define BOOL(x) COMPL(NOT(x))
#define IF(c) IIF(BOOL(c))

#define EAT(...)
#define EXPAND(...) __VA_ARGS__
#define WHEN(c) IF(c)(EXPAND, EAT)

#define PRIMITIVE_COMPARE(x, y) IS_PAREN \
( \
COMPARE_ ## x ( COMPARE_ ## y) (())  \
)

#define COMPARE_foo(x) x
#define COMPARE_bar(x) x
#define COMPARE_void(x) x

#define IS_COMPARABLE(x) IS_PAREN(CAT(COMPARE_, x) (()))
#define NOT_EQUAL(x, y) \
IIF(BITBAND(IS_COMPARABLE(x))(IS_COMPARABLE(y)) ) \
( \
   PRIMITIVE_COMPARE, \
   1 EAT \
)(x, y)

#define EQUAL(x, y) COMPL(NOT_EQUAL(x, y))

#define IS_VOID(x) EQUAL(x, void)


#define TVAL(type) \
IF(IS_VOID(type)) (int x;, 4 + 3)

void test() {
    TVAL(void);
}




#ifdef __cplusplus
};
#endif

#endif //TESTABLE_PP_H
