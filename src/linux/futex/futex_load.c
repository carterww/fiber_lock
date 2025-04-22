#include "fiber_atomic/atomic.h"
#include "fiber_lock/futex.h"

int fiber_futex_load(fiber_futex *futex)
{
	return fiber_atomic_load(futex, FIBER_ATOMIC_ACQUIRE);
}
