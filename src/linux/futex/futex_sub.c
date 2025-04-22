#include "fiber_atomic/atomic.h"
#include "fiber_lock/futex.h"

int fiber_futex_sub(fiber_futex *futex, int value)
{
	return fiber_atomic_sub_fetch(futex, value, FIBER_ATOMIC_ACQ_REL);
}
