// SPDX-License-Identifier: GPL-3.0-or-later
#include "puzzle_spec.h"

#include <limits.h>
#include <stddef.h>

#include "bits.h"
#include "oracle.h"

puzzle_spec_t puzzle_specs[] = {

    {
        .name = "absVal",
        .return_type = INT_RET,
        .num_args = 1,
        .arg_types = {INT_ARG, UNUSED_ARG, UNUSED_ARG},
        .arg_min = {INT_MIN, 0, 0},
        .arg_max = {INT_MAX, 0, 0},
        .test_func = (int (*)(void)) test_absVal,
        .impl_func = (int (*)(void)) absVal,
    },
    {
        .name = "addOK",
        .return_type = INT_RET,
        .num_args = 2,
        .arg_types = {INT_ARG, INT_ARG, UNUSED_ARG},
        .arg_min = {INT_MIN, INT_MIN, 0},
        .arg_max = {INT_MAX, INT_MAX, 0},
        .test_func = (int (*)(void)) test_addOK,
        .impl_func = (int (*)(void)) addOK,
    },
    {
        .name = "bitNor",
        .return_type = INT_RET,
        .num_args = 2,
        .arg_types = {INT_ARG, INT_ARG, UNUSED_ARG},
        .arg_min = {INT_MIN, INT_MIN, 0},
        .arg_max = {INT_MAX, INT_MAX, 0},
        .test_func = (int (*)(void)) test_bitNor,
        .impl_func = (int (*)(void)) bitNor,
    },
    {
        .name = "copyLSB",
        .return_type = INT_RET,
        .num_args = 1,
        .arg_types = {INT_ARG, UNUSED_ARG, UNUSED_ARG},
        .arg_min = {INT_MIN, 0, 0},
        .arg_max = {INT_MAX, 0, 0},
        .test_func = (int (*)(void)) test_copyLSB,
        .impl_func = (int (*)(void)) copyLSB,
    },
    {
        .name = "distinctNegation",
        .return_type = INT_RET,
        .num_args = 1,
        .arg_types = {INT_ARG, UNUSED_ARG, UNUSED_ARG},
        .arg_min = {INT_MIN, 0, 0},
        .arg_max = {INT_MAX, 0, 0},
        .test_func = (int (*)(void)) test_distinctNegation,
        .impl_func = (int (*)(void)) distinctNegation,
    },
    {
        .name = "floatAbsVal",
        .return_type = UNSIGNED_RET,
        .num_args = 1,
        .arg_types = {FLOAT_AS_UNSIGNED_ARG, UNUSED_ARG, UNUSED_ARG},
        .arg_min = {0, 0, 0},
        .arg_max = {UINT_MAX, 0, 0},
        .test_func = (int (*)(void)) test_floatAbsVal,
        .impl_func = (int (*)(void)) floatAbsVal,
    },
    {
        .name = "floatFloat2Int",
        .return_type = UNSIGNED_RET,
        .num_args = 1,
        .arg_types = {FLOAT_AS_UNSIGNED_ARG, UNUSED_ARG, UNUSED_ARG},
        .arg_min = {0, 0, 0},
        .arg_max = {UINT_MAX, 0, 0},
        .test_func = (int (*)(void)) test_floatFloat2Int,
        .impl_func = (int (*)(void)) floatFloat2Int,
    },
    {
        .name = "floatIsLess",
        .return_type = UNSIGNED_RET,
        .num_args = 2,
        .arg_types = {FLOAT_AS_UNSIGNED_ARG, FLOAT_AS_UNSIGNED_ARG, UNUSED_ARG},
        .arg_min = {0, 0, 0},
        .arg_max = {UINT_MAX, UINT_MAX, 0},
        .test_func = (int (*)(void)) test_floatIsLess,
        .impl_func = (int (*)(void)) floatIsLess,
    },
    {
        .name = "isAsciiDigit",
        .return_type = INT_RET,
        .num_args = 1,
        .arg_types = {INT_ARG, UNUSED_ARG, UNUSED_ARG},
        .arg_min = {INT_MIN, 0, 0},
        .arg_max = {INT_MAX, 0, 0},
        .test_func = (int (*)(void)) test_isAsciiDigit,
        .impl_func = (int (*)(void)) isAsciiDigit,
    },
    {
        .name = "isGreater",
        .return_type = INT_RET,
        .num_args = 2,
        .arg_types = {INT_ARG, INT_ARG, UNUSED_ARG},
        .arg_min = {INT_MIN, INT_MIN, 0},
        .arg_max = {INT_MAX, INT_MAX, 0},
        .test_func = (int (*)(void)) test_isGreater,
        .impl_func = (int (*)(void)) isGreater,
    },
    {
        .name = "isZero",
        .return_type = INT_RET,
        .num_args = 1,
        .arg_types = {INT_ARG, UNUSED_ARG, UNUSED_ARG},
        .arg_min = {INT_MIN, 0, 0},
        .arg_max = {INT_MAX, 0, 0},
        .test_func = (int (*)(void)) test_isZero,
        .impl_func = (int (*)(void)) isZero,
    },
    {
        .name = "leastBitPos",
        .return_type = INT_RET,
        .num_args = 1,
        .arg_types = {INT_ARG, UNUSED_ARG, UNUSED_ARG},
        .arg_min = {INT_MIN, 0, 0},
        .arg_max = {INT_MAX, 0, 0},
        .test_func = (int (*)(void)) test_leastBitPos,
        .impl_func = (int (*)(void)) leastBitPos,
    },
    // Sentinel value at end
    {
        .name = NULL,
    }

};
