#define _POSIX_C_SOURCE (199506L)

#include <errno.h>

#include "debug.h"
#include "fiber_lock/errno.h"
#include "fiber_lock/mutex.h"

#if defined(FIBER_LOCK_MUTEX_INTERCEPT)
#define fiber_mutex_init _fiber_mutex_init
#endif

int fiber_mutex_init(fiber_mutex *mut)
{
	int res;

	fiber_assert(mut != NULL);
	res = pthread_mutex_init(mut, NULL);

	fiber_assert(res != EINVAL); /* This only occurs if attr is invalid */
	fiber_assert(res != EBUSY); /* Attempted to reinitialize a mutex */

	switch (res) {
	case 0:
		return res;
	case EAGAIN: /* System did not have resource to init mutx (excluding mem). */
		return FBR_LOCK_ENO_RSC;
	case EPERM: /* Does not have permission to init mutex */
		return FBR_LOCK_EPTHRD_PERM;
	case ENOMEM: /* No memory */
		return FBR_LOCK_ENOMEM;
	default:
		panic(1);
	}
}

#if defined(FIBER_LOCK_MUTEX_INTERCEPT)
#undef fiber_mutex_init
int (*fiber_mutex_init_fn_ptr)(fiber_mutex *) = _fiber_mutex_init;
#endif
