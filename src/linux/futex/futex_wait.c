#include "futex_syscall.h"

#include <errno.h>
#include <stdint.h>

#include <linux/futex.h>

#include "debug.h"
#include "fiber_lock/errno.h"
#include "fiber_lock/futex.h"

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#define fiber_futex_wait _fiber_futex_wait
#endif

int fiber_futex_wait(fiber_futex *futex, int expected)
{
	long syscall_res = -1;
	int value;

	while ((value = fiber_futex_load(futex)) == expected) {
		syscall_res = _fiber_lock_futex_syscall_linux_timeout(
			(uint32_t *)futex, NULL,
			FUTEX_WAIT | FUTEX_PRIVATE_FLAG, (uint32_t)expected,
			NULL, 0);
		if (syscall_res == -1 && errno != EINTR) {
			break;
		}
	}
	if (syscall_res == 0) {
		return 0;
	}
	if (value != expected || errno == EAGAIN) {
		return FBR_LOCK_EAGAIN;
	}

	fiber_assert(errno != EACCES);
	fiber_assert(errno != EFAULT);
	fiber_assert(errno != EINVAL);
	fiber_assert(errno != ETIMEDOUT);
	panic(1);
}

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#undef fiber_futex_wait
int (*fiber_futex_wait_fn_ptr)(fiber_futex *, int) = _fiber_futex_wait;
#endif
