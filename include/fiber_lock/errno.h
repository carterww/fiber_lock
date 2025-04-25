/* See LICENSE file for copyright and license details. */

#ifndef FIBER_LOCK_ERRNO_H
#define FIBER_LOCK_ERRNO_H

/* Starting these at 1,000 so Fiber can use them directly
 * without worrying about duplicates.
 */
#define FBR_LOCK_ENO_RSC (-1000)
#define FBR_LOCK_EPTHRD_PERM (-1001)
#define FBR_LOCK_ENOMEM (-1002)
#define FBR_LOCK_EBUSY (-1003)
#define FBR_LOCK_ESEM_RNG (-1004)
#define FBR_LOCK_EAGAIN (-1005)
#define FBR_LOCK_EINTR (-1006)
#define FBR_LOCK_EDEADLK (-1007)
#define FBR_LOCK_ETIMEDOUT (-1008)
#define FBR_LOCK_EINVAL (-1009)

#endif /* FIBER_LOCK_ERRNO_H */
