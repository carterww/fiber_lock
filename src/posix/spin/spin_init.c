#define _POSIX_C_SOURCE (200112L)

#include <errno.h>

#include "debug.h"
#include "fiber_lock/errno.h"
#include "fiber_lock/spin.h"

#if defined(FIBER_LOCK_SPIN_INTERCEPT)
#define fiber_spin_init _fiber_spin_init
#endif

int fiber_spin_init(fiber_spinlock *spin)
{
	int res;

	fiber_assert(spin != NULL);
	res = pthread_spin_init(spin, PTHREAD_PROCESS_PRIVATE);

	switch (res) {
	case 0:
		return res;
	case EAGAIN:
		return FBR_LOCK_EAGAIN;
	case ENOMEM:
		return FBR_LOCK_ENOMEM;
	default:
		panic(1);
	}
}
