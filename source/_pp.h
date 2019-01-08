//
// Created by Andrew Wade on 12/16/18.
//

#ifndef TESTABLE_PP_H
#define TESTABLE_PP_H

#ifdef __cplusplus
extern "C" {
#endif
#define _DO_NOTHING(...)
#define _GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10,  N, ...) N

#define COUNT(...) _GET_NTH_ARG("ignored", ##__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

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

#define _PAIR_ARGS1(a) a
#define _PAIR_ARGS2(a, b) a b
#define _PAIR_ARGS4(a, b, c, d) a b, c d
#define _PAIR_ARGS6(a, b, c, d, e, f) a b, c d, e f

#define _PAIR_OVERRIDE(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
#define LIST_PAIRS(...) _PAIR_OVERRIDE(__VA_ARGS__, _PAIR_ARGS6,_DO_NOTHING,_PAIR_ARGS4,_DO_NOTHING, _PAIR_ARGS2, _DO_NOTHING)(__VA_ARGS__)

#define COMMA() ,
#define SEMICOL() ;
#define PASS(...) __VA_ARGS__
#define EAT(...)


#define _MAP_1(macro, ...) macro(__VA_ARGS__)
#define _MAP_2(macro, ...) macro(__VA_ARGS__) _LIST_FOREACH_1(macro, __VA_ARGS__)
#define _MAP_3(macro, ...) macro(arg) _LIST_FOREACH_2(macro, __VA_ARGS__)
#define _MAP_4(macro, ...) macro(arg) _LIST_FOREACH_3(macro, __VA_ARGS__)
#define _MAP_5(macro, ...) macro(arg) _LIST_FOREACH_4(macro, __VA_ARGS__)
#define _MAP_6(macro, ...) macro(arg) _LIST_FOREACH_5(macro, __VA_ARGS__)
#define _MAP_7(macro, ...) macro(arg) _LIST_FOREACH_6(macro, __VA_ARGS__)
#define _MAP_8(macro, ...) macro(arg) _LIST_FOREACH_7(macro, __VA_ARGS__)
#define _MAP_9(macro, ...) macro(arg) _LIST_FOREACH_8(macro, __VA_ARGS__)

#define _MAP_PAIRS_0(macro, sep)
#define _MAP_PAIRS_1(macro, sep, a, ...) a
#define _MAP_PAIRS_2(macro, sep, a, b, ...) macro(a, b)
#define _MAP_PAIRS_4(macro, sep, a, b, ...) _MAP_PAIRS_2(macro, sep, a, b) sep() _MAP_PAIRS_2(macro, sep, __VA_ARGS__)
#define _MAP_PAIRS_6(macro, sep, a, b, ...) _MAP_PAIRS_2(macro, sep, a, b)sep() _MAP_PAIRS_4(macro, sep, __VA_ARGS__)
#define _MAP_PAIRS_8(macro, sep, a, b, ...) _MAP_PAIRS_2(macro, sep, a, b)sep() _MAP_PAIRS_6(macro, sep, __VA_ARGS__)
#define _MAP_PAIRS_10(macro, sep, a, b, ...) _MAP_PAIRS_2(macro, sep, a, b)sep() _MAP_PAIRS_8(macro, sep, __VA_ARGS__)

#define MAP(macro, sep, ...) _GET_NTH_ARG(__VA_ARGS__, _MAP_9, _MAP_8, _MAP_7, _MAP_6, _MAP_5, _MAP_4, _MAP_3, _MAP_2, _MAP_1, _DO_NOTHING)(macro, sep, ##__VA_ARGS__)

#define MAP_PAIRS(macro, sep, ...) _GET_NTH_ARG(__VA_ARGS__, _MAP_PAIRS_10, EAT, _MAP_PAIRS_8, EAT, _MAP_PAIRS_6, EAT, _MAP_PAIRS_4, EAT, _MAP_PAIRS_2, _MAP_PAIRS_1, _DO_NOTHING)(macro, sep, ##__VA_ARGS__)


#define CAT3(a, b, c) a ## b ## c
#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__
#define IF_ELSE(c) PRIMITIVE_CAT(_IF_ELSE_, c)
#define _IF_ELSE_0(t, ...) __VA_ARGS__
#define _IF_ELSE_1(t, ...) t

#define COMPL(b) PRIMITIVE_CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

#define BITAND(x) PRIMITIVE_CAT(BITAND_, x)
#define BITAND_0(y) 0
#define BITAND_1(y) y

#define AND(a, b) CAT3(_AND_, a, b)
#define _AND_00   0
#define _AND_01   0
#define _AND_10   0
#define _AND_11   1

#define OR(a, b) CAT3(_OR_, a, b)
#define _OR_00 0
#define _OR_01 1
#define _OR_10 1
#define _OR_11 1

#define CHECK_N(x, n, ...) n
#define CHECK(...) CHECK_N(__VA_ARGS__, 0,)
#define PROBE(x) x, 1,

#define IS_PAREN(x) CHECK(IS_PAREN_PROBE x)
#define IS_PAREN_PROBE(...) PROBE(~)

#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_, x))
#define NOT_0 PROBE(~)

#define BOOL(x) COMPL(NOT(x))

#define IF(c) _IF(BOOL(c))
#define _IF(c) PRIMITIVE_CAT(_IF_,c)
#define _IF_0(...)
#define _IF_1(...) __VA_ARGS__

#define EAT(...)
#define EXPAND(...) __VA_ARGS__
#define WHEN(c) IF(c)(EXPAND, EAT)
#define FIRST(a, ...) a

#define PRIMITIVE_COMPARE(x, y) IS_PAREN \
( \
COMPARE_ ## x ( COMPARE_ ## y) (())  \
)


#define COMPARE_void(x) x
#define COMPARE_1(x) x

#define IS_COMPARABLE(x) IS_PAREN(CAT(COMPARE_, x) (()))
#define NOT_EQUAL(x, y) \
IF_ELSE(BITAND(IS_COMPARABLE(x))(IS_COMPARABLE(y)) ) \
( \
   PRIMITIVE_COMPARE, \
   1 EAT \
)(x, y)

#define EQUAL(x, y) COMPL(NOT_EQUAL(x, y))

#define TYPE_IS_VOID(x) EQUAL(x, void)


#define HAS_NO_ARGS(...) OR(NOT(COUNT(__VA_ARGS__)), \
AND(EQUAL(COUNT(__VA_ARGS__), 1), TYPE_IS_VOID(FIRST(__VA_ARGS__))))

#define HAS_ARGS(...) NOT(HAS_NO_ARGS(__VA_ARGS__))

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_PP_H
