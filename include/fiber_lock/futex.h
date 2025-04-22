/* See LICENSE file for copyright and license details. */

#ifndef FIBER_LOCK_FUTEX_H
#define FIBER_LOCK_FUTEX_H

#if defined(FIBER_LOCK_FUTEX_LINUX)
#if defined(__linux__)
#include <linux/futex.h>
#include <sys/syscall.h>
#else
#error "FIBER_LOCK_FUTEX_LINUX was specified but __linux__ is not defined."
#endif /* __linux__ */

#if !defined(SYS_futex)
#error "FIBER_LOCK_FUTEX_LINUX was specified but SYS_futex is not defined."
#endif /* !SYS_futex */

/* If an error occurs here it is because an int is not 32 bits on your
 * platform. A futex must be 4 bytes aligned to 4 bytes on Linux.
 */
typedef char _static_assert_int_4_bytes[sizeof(int) == 4 ? 1 : -1];
typedef int fiber_futex;
#else
#error "No futex implementation specified."
typedef void fiber_futex;
#endif /* FIBER_LOCK_FUTEX_LINUX */

/* Loads the value from fiber_futex.
 * @param futex -> Pointer to the futex to load.
 * @returns -> The futex's value.
 */
int fiber_futex_load(fiber_futex *futex);

/* Sets a fiber_futex to a value.
 * @param futex -> Pointer to the futex to set.
 * @param value -> Value the futex should be set to.
 */
void fiber_futex_set(fiber_futex *futex, int value);

/* Adds value to the futex and returns the new value.
 * @param futex -> Pointer to the futex to add to.
 * @param value -> Value to add to the futex.
 * @returns -> The futex's new value.
 */
int fiber_futex_add(fiber_futex *futex, int value);

/* Subtracts value from the futex and returns the new value.
 * @param futex -> Pointer to the futex to add to.
 * @param value -> Value to subtract from the futex.
 * @returns -> The futex's new value.
 */
int fiber_futex_sub(fiber_futex *futex, int value);

/* Sets a a fiber_futex to a value and puts the old value in old_out.
 * @param futex -> Pointer to the futex to set.
 * @param value -> Value the futex should be set to.
 * @returns -> The futex's old value.
 */
int fiber_futex_exchange(fiber_futex *futex, int value);

/* Sets a a fiber_futex to a value if futex's value equals expected's value.
 * If is_weak is true, this call can fail even if the values are equal. If
 * the operation fails, the value of futex is written to expected.
 * @param futex -> Pointer to the futex to set.
 * @param expected -> Pointer to the alue the futex must have for the exchange
 * to be sucessful. If the exchange fails, futex's value will be written to
 * expected.
 * @param value -> Value the futex should be set to.
 * @param is_weak -> Boolean value indicating if the compare and exchange
 * should be weak.
 * @returns -> False (0) indicating a failure, true (not 0) otherwise.
 */
int fiber_futex_cmp_xchng(fiber_futex *futex, int *expected, int value,
			  int is_weak);

/* Block indefinitely if the futex's value equals expected. 
 * @param futex -> Pointer to the futex to potentially block on.
 * @param expected -> Value the futex should contain if the thread
 * should block.
 * @returns -> 0 if the thread was woken up by fiber_futex_wake, an
 * error otherwise.
 * @error FBR_LOCK_EAGAIN -> The futex's value did not match expected.
 */
int fiber_futex_wait(fiber_futex *futex, int expected);

/* Block for timeout_ms milliseconds if the futex's value equals expected. 
 * @param futex -> Pointer to the futex to potentially block on.
 * @param expected -> Value the futex should contain if the thread
 * should block.
 * @returns -> 0 if the thread was woken up by fiber_futex_wake, an
 * error otherwise.
 * @error FBR_LOCK_EAGAIN -> The futex's value did not match expected.
 * @error FBR_LOCK_ETIMEDOUT -> The timeout was reached.
 */
int fiber_futex_wait_timeout(fiber_futex *futex, int expected,
			     unsigned long timeout_ms);

/* Wake up at most *num_threads threads waiting on futex.
 * @param futex -> Pointer to the futex the thread(s) are waiting on.
 * @param num_threads -> Pointer to the maximum number of threads to wake.
 * If an error isn't returned, the actual number of threads woken up is put
 * into this variable.
 * @returns -> 0 if the call was successful, an error otherwise.
 * @error FBR_LOCK_EINVAL -> *num_threads is not a positive integer.
 */
int fiber_futex_wake(fiber_futex *futex, int *num_threads);

#endif /* FIBER_LOCK_FUTEX_H */
