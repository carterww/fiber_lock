#include "fiber_atomic/atomic.h"
#include "fiber_lock/futex.h"

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#define fiber_futex_load _fiber_futex_load
#endif

int fiber_futex_load(fiber_futex *futex)
{
	return fiber_atomic_load(futex, FIBER_ATOMIC_ACQUIRE);
}

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#undef fiber_futex_load
int (*fiber_futex_load_fn_ptr)(fiber_futex *) = _fiber_futex_load;
#endif
