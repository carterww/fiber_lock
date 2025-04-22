#include "fiber_atomic/atomic.h"
#include "fiber_lock/futex.h"

void fiber_futex_set(fiber_futex *futex, int value)
{
	fiber_atomic_store(futex, value, FIBER_ATOMIC_RELEASE);
}
