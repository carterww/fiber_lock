#define _POSIX_C_SOURCE (199506L)

#include <errno.h>

#include "debug.h"
#include "fiber_lock/mutex.h"

#if defined(FIBER_LOCK_MUTEX_INTERCEPT)
#define fiber_mutex_lock _fiber_mutex_lock
#endif

int fiber_mutex_lock(fiber_mutex *mut)
{
	int res;

	fiber_assert(mut != NULL);
	res = pthread_mutex_lock(mut);

	/* Invalid mutex or PTHREAD_PRIO_PROTECT issue (N/A here) */
	fiber_assert(res != EINVAL);
	/* Max number of recursive locks exceeded */
	fiber_assert(res != EAGAIN);

	switch (res) {
	case 0:
		return res;
	case EDEADLK: /* Caller already owns mutex */
		return 0;
	default:
		panic(1);
	}
}

#if defined(FIBER_LOCK_MUTEX_INTERCEPT)
#undef fiber_mutex_lock
int (*fiber_mutex_lock_fn_ptr)(fiber_mutex *) = _fiber_mutex_lock;
#endif
