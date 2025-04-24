#include "fiber_atomic/atomic.h"
#include "fiber_lock/futex.h"

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#define fiber_futex_sub _fiber_futex_sub
#endif

int fiber_futex_sub(fiber_futex *futex, int value)
{
	return fiber_atomic_sub_fetch(futex, value, FIBER_ATOMIC_ACQ_REL);
}

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#undef fiber_futex_sub
int (*fiber_futex_sub_fn_ptr)(fiber_futex *, int) = _fiber_futex_sub;
#endif
