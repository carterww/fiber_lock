#include "futex_syscall.h"

#include <limits.h>
#include <stdint.h>

#include <linux/futex.h>

#include "debug.h"
#include "fiber_lock/errno.h"
#include "fiber_lock/futex.h"

int fiber_futex_wake(fiber_futex *futex, int *num_threads)
{
	long num_woken;
	uint32_t num_threads_uint;

	if (*num_threads <= 0) {
		return FBR_LOCK_EINVAL;
	}
	num_threads_uint = (uint32_t)*num_threads;

	num_woken = _fiber_lock_futex_syscall_linux_timeout(
		(uint32_t *)futex, NULL, FUTEX_WAKE | FUTEX_PRIVATE_FLAG,
		num_threads_uint, NULL, 0);

	fiber_assert(num_woken >= 0 && num_woken <= INT_MAX);

	return (int)num_woken;
}
