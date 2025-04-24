#include "fiber_atomic/atomic.h"
#include "fiber_lock/futex.h"

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#define fiber_futex_set _fiber_futex_set
#endif

void fiber_futex_set(fiber_futex *futex, int value)
{
	fiber_atomic_store(futex, value, FIBER_ATOMIC_RELEASE);
}

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#undef fiber_futex_set
void (*fiber_futex_set_fn_ptr)(fiber_futex *, int) = _fiber_futex_set;
#endif
