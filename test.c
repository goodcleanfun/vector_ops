#include <stdint.h>
#include "greatest/greatest.h"

#define VECTOR_NAME test_vector
#define VECTOR_TYPE int32_t
#define VECTOR_TYPE_ABS abs
#define VECTOR_TYPE_UNSIGNED uint32_t
#include "numeric.h"
#undef VECTOR_NAME
#undef VECTOR_TYPE
#undef VECTOR_TYPE_ABS
#undef VECTOR_TYPE_UNSIGNED


TEST test_vector_math(void) {
    size_t n = 10;
    int32_t *v = malloc(n * sizeof(int32_t));
    for (size_t i = 0; i < n; i++) {
        v[n - i - 1] = i;
    }

    ASSERT_EQ(test_vector_max(v, n), 9);
    ASSERT_EQ(test_vector_min(v, n), 0);
    ASSERT_EQ(test_vector_argmax(v, n), 0);
    ASSERT_EQ(test_vector_argmin(v, n), 9);
    test_vector_sort(v, n);
    size_t *order = test_vector_argsort(v, n);
    for (size_t i = 0; i < n; i++) {
        ASSERT_EQ(order[i], i);
    }
    free(order);
    ASSERT_EQ(test_vector_argmax(v, n), 9);
    ASSERT_EQ(test_vector_argmin(v, n), 0);
    ASSERT_EQ(test_vector_sum(v, n), 45);
    ASSERT_EQ(test_vector_product(v, n), 0);
    ASSERT_EQ(test_vector_l1_norm(v, n), 45);
    ASSERT_EQ(test_vector_l2_norm(v, n), 16.881943016134134);
    ASSERT_EQ(test_vector_sum_sq(v, n), 285);
    ASSERT_EQ(test_vector_mean(v, n), 4.5);
    ASSERT_EQ(test_vector_var(v, n), 8.25);
    ASSERT_EQ(test_vector_std(v, n), 2.8722813232690143);
    test_vector_add(v, 1, n);
    for (size_t i = 0; i < n; i++) {
        ASSERT_EQ(v[i], i + 1);
    }
    ASSERT_EQ(test_vector_product(v, n), 3628800);
    test_vector_sub(v, 1, n);
    for (size_t i = 0; i < n; i++) {
        ASSERT_EQ(v[i], i);
    }
    test_vector_mul(v, 2, n);
    for (size_t i = 0; i < n; i++) {
        ASSERT_EQ(v[i], i * 2);
    }
    test_vector_div(v, 2, n);
    for (size_t i = 0; i < n; i++) {
        ASSERT_EQ(v[i], i);
    }

    int32_t *v_copy = malloc(n * sizeof(int32_t));
    ASSERT(v_copy != NULL);
    test_vector_copy(v_copy, v, n);

    test_vector_add_vector(v, v_copy, n);
    for (size_t i = 0; i < n; i++) {
        ASSERT_EQ(v[i], i * 2);
    }
    test_vector_sub_vector(v, v_copy, n);
    for (size_t i = 0; i < n; i++) {
        ASSERT_EQ(v[i], i);
    }

    test_vector_add_vector_scaled(v, v_copy, 2, n);
    for (size_t i = 0; i < n; i++) {
        ASSERT_EQ(v[i], i + 2 * i);
    }
    test_vector_sub_vector_scaled(v, v_copy, 2, n);
    for (size_t i = 0; i < n; i++) {
        ASSERT_EQ(v[i], i);
    }

    // avoid division by 0
    test_vector_add(v, 1, n);
    test_vector_add(v_copy, 1, n);
    test_vector_mul_vector(v, v_copy, n);
    for (size_t i = 0; i < n; i++) {
        ASSERT_EQ(v[i], (i + 1) * (i + 1));
    }
    test_vector_div_vector(v, v_copy, n);
    for (size_t i = 0; i < n; i++) {
        ASSERT_EQ(v[i], i + 1);
    }

    test_vector_mul_vector_scaled(v, v_copy, 2, n);
    for (size_t i = 0; i < n; i++) {
        ASSERT_EQ(v[i], (i + 1) * (i + 1) * 2);
    }
    test_vector_div_vector_scaled(v, v_copy, 2, n);
    for (size_t i = 0; i < n; i++) {
        ASSERT_EQ(v[i], i + 1);
    }

    test_vector_sub(v, 1, n);
    test_vector_sub(v_copy, 1, n);

    ASSERT_EQ(test_vector_dot(v, v_copy, n), 285);

    free(v);
    PASS();
}

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* command-line options, initialization. */

    RUN_TEST(test_vector_math);

    GREATEST_MAIN_END();        /* display results */
}
