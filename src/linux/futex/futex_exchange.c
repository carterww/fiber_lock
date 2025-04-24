#include "fiber_atomic/atomic.h"
#include "fiber_lock/futex.h"

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#define fiber_futex_exchange _fiber_futex_exchange
#endif

int fiber_futex_exchange(fiber_futex *futex, int value)
{
	return fiber_atomic_exchange(futex, value, FIBER_ATOMIC_ACQ_REL);
}

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#undef fiber_futex_exchange
int (*fiber_futex_exchange_fn_ptr)(fiber_futex *, int) = _fiber_futex_exchange;
#endif
