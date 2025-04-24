#include "fiber_atomic/atomic.h"
#include "fiber_lock/futex.h"

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#define fiber_futex_cmp_xchng _fiber_futex_cmp_xchng
#endif

int fiber_futex_cmp_xchng(fiber_futex *futex, int *expected, int value,
			  int is_weak)
{
	return fiber_atomic_cmp_xchng(futex, expected, value, is_weak,
				      FIBER_ATOMIC_ACQ_REL,
				      FIBER_ATOMIC_ACQUIRE);
}

#if defined(FIBER_LOCK_FUTEX_INTERCEPT)
#undef fiber_futex_cmp_xchng
int (*fiber_futex_cmp_xchng_fn_ptr)(fiber_futex *, int *, int,
				    int) = _fiber_futex_cmp_xchng;
#endif
