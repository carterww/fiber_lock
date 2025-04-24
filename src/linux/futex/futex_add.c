#include "fiber_atomic/atomic.h"
#include "fiber_lock/futex.h"

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#define fiber_futex_add _fiber_futex_add
#endif

int fiber_futex_add(fiber_futex *futex, int value)
{
	return fiber_atomic_add_fetch(futex, value, FIBER_ATOMIC_ACQ_REL);
}

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#undef fiber_futex_add
int (*fiber_futex_add_fn_ptr)(fiber_futex *, int) = _fiber_futex_add;
#endif
