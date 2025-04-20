#define _POSIX_C_SOURCE (200112L)

#include <errno.h>

#include "debug.h"
#include "fiber_lock/errno.h"
#include "fiber_lock/spin.h"

#if defined(FIBER_LOCK_SPIN_INTERCEPT)
#define fiber_spin_trylock _fiber_spin_trylock
#endif

int fiber_spin_trylock(fiber_spinlock *spin)
{
	int res;

	fiber_assert(spin != NULL);
	res = pthread_spin_trylock(spin);

	switch (res) {
	case 0:
		return res;
	case EBUSY:
		return FBR_LOCK_EBUSY;
	default:
		panic(1);
	}
}
