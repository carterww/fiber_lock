#include "futex_syscall.h"

#include <errno.h>
#include <stdint.h>

#include <linux/futex.h>

#include "debug.h"
#include "fiber_lock/errno.h"
#include "fiber_lock/futex.h"

static void timespec_from_ms(struct timespec *ts, unsigned long timeout_ms)
{
	time_t time_ms = (time_t)timeout_ms;
	ts->tv_sec = time_ms / 1000;
	ts->tv_nsec = (time_ms % 1000) * (time_t)1000000;
}

static void timespec_diff(struct timespec *tout, struct timespec *start,
			  struct timespec *end)
{
	time_t rem_sec, rem_ns;

	rem_sec = tout->tv_sec - (end->tv_sec - start->tv_sec);
	rem_ns = tout->tv_nsec - (end->tv_nsec - start->tv_nsec);

	if (rem_ns < 0) {
		rem_ns += 1000000000;
		rem_sec -= 1;
	}

	tout->tv_sec = rem_sec;
	tout->tv_nsec = rem_ns;
}

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#define fiber_futex_wait_timeout _fiber_futex_wait_timeout
#endif

int fiber_futex_wait_timeout(fiber_futex *futex, int expected,
			     unsigned long timeout_ms)
{
	long syscall_res = -1;
	struct timespec timeout;
	int value;

	timespec_from_ms(&timeout, timeout_ms);

	while ((value = fiber_futex_load(futex)) == expected) {
		struct timespec start, end;

		/* 400 cycles on a 2GHz processor is about 200 ns. The clock^ and
                 * futex syscall will likely be at least 400 cycles so we shoud just
                 * timeout.
                 * ^ clock_gettime does not always issue a syscall.
                 */
		if (timeout.tv_sec <= 0 && timeout.tv_nsec <= 200) {
			return FBR_LOCK_ETIMEDOUT;
		}

		clock_gettime(CLOCK_MONOTONIC, &start);
		syscall_res = _fiber_lock_futex_syscall_linux_timeout(
			(uint32_t *)futex, NULL,
			FUTEX_WAIT | FUTEX_PRIVATE_FLAG, (uint32_t)expected,
			&timeout, 0);
		if (syscall_res == -1 && errno != EINTR) {
			break;
		}
		clock_gettime(CLOCK_MONOTONIC, &end);

		timespec_diff(&timeout, &start, &end);
	}
	if (syscall_res == 0) {
		return 0;
	}
	if (value != expected || errno == EAGAIN) {
		return FBR_LOCK_EAGAIN;
	} else if (errno == ETIMEDOUT) {
		return FBR_LOCK_ETIMEDOUT;
	}

	fiber_assert(errno != EACCES);
	fiber_assert(errno != EFAULT);
	fiber_assert(errno != EINVAL);
	panic(1);
}

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#undef fiber_futex_wait_timeout
int (*fiber_futex_wait_timeout_fn_ptr)(fiber_futex *, int, unsigned long) =
	_fiber_futex_wait_timeout;
#endif
