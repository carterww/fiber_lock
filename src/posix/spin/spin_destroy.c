#define _POSIX_C_SOURCE (200112L)

#include "debug.h"
#include "fiber_lock/spin.h"

#if defined(FIBER_LOCK_SPIN_INTERCEPT)
#define fiber_spin_destroy _fiber_spin_destroy
#endif

int fiber_spin_destroy(fiber_spinlock *spin)
{
	int res;

	fiber_assert(spin != NULL);
	res = pthread_spin_destroy(spin);

	fiber_assert(res == 0);

	return res;
}
