#include "fiber_atomic/atomic.h"
#include "fiber_lock/futex.h"

int fiber_futex_exchange(fiber_futex *futex, int value)
{
	return fiber_atomic_exchange(futex, value, FIBER_ATOMIC_ACQ_REL);
}
