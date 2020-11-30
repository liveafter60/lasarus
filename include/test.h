#ifndef __LASARUS_TEST_H__
#define __LASARUS_TEST_H__

#include <stddef.h>

typedef void (lsr_test)(void);

enum lsr_test_status {
        LSR_TEST_STATUS_OK = 0,
        LSR_TEST_STATUS_SKIP,
        LSR_TEST_STATUS_FAIL,
        __LSR_TEST_STATUS_LEN__,
};

typedef struct lsr_test_case lsr_test_case;
typedef struct lsr_test_suite lsr_test_suite;
typedef struct lsr_test_harness lsr_test_harness;


lsr_test_case *lsr_test_case_new(const char *ctx, const char *in,
                const char *out, lsr_test *test);
void lsr_test_case_dispose(lsr_test_case **ctx);
enum lsr_test_status lsr_test_case_status(const lsr_test_case *ctx);
const char *lsr_test_case_msg(const lsr_test_case *ctx);
void lsr_test_case_exec(lsr_test_case *ctx);

lsr_test_suite *lsr_test_suite_new(const char *desc);
void lsr_test_suite_dispose(lsr_test_suite **ctx);
size_t lsr_test_suite_len(const  lsr_test_suite *ctx);
int lsr_test_suite_pass(const lsr_test_suite *ctx);
int lsr_test_suite_skip(const lsr_test_suite *ctx);
int lsr_test_suite_fail(const lsr_test_suite *ctx);
void lsr_test_suite_push(lsr_test_suite *ctx, const lsr_test_case *tc);
void lsr_test_suite_exec(lsr_test_suite *ctx);


lsr_test_harness *lsr_test_harness_new(const char *file);
void lsr_test_harness_dispose(lsr_test_harness **ctx);
void lsr_test_harness_push(lsr_test_harness *ctx, const lsr_test_suite *ts);
void lsr_test_harness_exec(lsr_test_harness *ctx);
int lsr_test_harness_len(const lsr_test_harness *ctx);
int lsr_test_harness_pass(const lsr_test_harness *ctx);
int lsr_test_harness_skip(const lsr_test_harness *ctx);
int lsr_test_harness_fail(const lsr_test_harness *ctx);


#endif /* !__LASARUS_TEST_H__ */

