#define _POSIX_C_SOURCE (200112L)

#include <errno.h>

#include "debug.h"
#include "fiber_lock/errno.h"
#include "fiber_lock/spin.h"

#if defined(FIBER_LOCK_SPIN_INTERCEPT)
#define fiber_spin_lock _fiber_spin_lock
#endif

int fiber_spin_lock(fiber_spinlock *spin)
{
	int res;

	fiber_assert(spin != NULL);
	res = pthread_spin_lock(spin);

	switch (res) {
	case 0:
		return res;
	case EDEADLOCK:
		return FBR_LOCK_EDEADLK;
	default:
		panic(1);
	}
}

#if defined(FIBER_LOCK_SPIN_INTERCEPT)
#undef fiber_spin_lock
int (*fiber_spin_lock_fn_ptr)(fiber_spinlock *) = _fiber_spin_lock;
#endif
