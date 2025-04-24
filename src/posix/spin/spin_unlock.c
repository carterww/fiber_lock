#define _POSIX_C_SOURCE (200112L)

#include "debug.h"
#include "fiber_lock/spin.h"

#if defined(FIBER_LOCK_SPIN_INTERCEPT)
#define fiber_spin_unlock _fiber_spin_unlock
#endif

int fiber_spin_unlock(fiber_spinlock *spin)
{
	int res;

	fiber_assert(spin != NULL);
	res = pthread_spin_unlock(spin);

	fiber_assert(res == 0);
	return res;
}

#if defined(FIBER_LOCK_SPIN_INTERCEPT)
#undef fiber_spin_unlock
int (*fiber_spin_unlock_fn_ptr)(fiber_spinlock *) = _fiber_spin_unlock;
#endif
