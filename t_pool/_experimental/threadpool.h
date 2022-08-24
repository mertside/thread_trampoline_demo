/*                                                                              
 * _THREADPOOL_H_                                                       
 *
 * on 2022/08/22                                                       
 *                                                                              
 */   
#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <stdbool.h>
#include <stddef.h>

struct tpool;
typedef struct tpool tpool_t;

typedef void (*thread_func_t)(void *arg);

tpool_t *tpool_create(size_t num);
void tpool_destroy(tpool_t *tm);

// Adds work to the queue for processing. 
bool tpool_add_work(tpool_t *tm, thread_func_t func, void *arg);

// Blocks until all work has been completed.
void tpool_wait(tpool_t *tm);

#endif /* __THREADPOOL_H__ */
