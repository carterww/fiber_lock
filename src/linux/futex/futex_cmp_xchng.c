#include "fiber_atomic/atomic.h"
#include "fiber_lock/futex.h"

int fiber_futex_cmp_xchng(fiber_futex *futex, int *expected, int value,
			  int is_weak)
{
	return fiber_atomic_cmp_xchng(futex, expected, value, is_weak,
				      FIBER_ATOMIC_ACQ_REL,
				      FIBER_ATOMIC_ACQUIRE);
}
