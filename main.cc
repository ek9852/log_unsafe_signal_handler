#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <cutils/log.h>
#include <pthread.h>

static pthread_mutex_t log_lock = PTHREAD_MUTEX_INITIALIZER;

static void lock(sigset_t *sigflags)
{
    /*
     * If we trigger a signal handler in the middle of locked activity and the
     * signal handler logs a message, we could get into a deadlock state.
     */
    sigset_t all;

    sigfillset(&all);
    pthread_sigmask(SIG_BLOCK, &all, sigflags);
    pthread_mutex_lock(&log_lock);
}

static void unlock(sigset_t *sigflags)
{
    pthread_mutex_unlock(&log_lock);
    pthread_sigmask(SIG_UNBLOCK, sigflags, NULL);
}

static void SigChldHandler(int)
{
    sigset_t sigflags;
    lock(&sigflags);
    unlock(&sigflags);
}

int main()
{

    sigset_t sigflags;
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SigChldHandler;

	int err = sigaction(SIGCHLD, &sa, NULL);
	if (err < 0) {
		ALOGW("Error setting SIGCHLD handler: %d", errno);
	}

	while(1) {
            lock(&sigflags);
            sleep(1);
            printf("hello\n");
            unlock(&sigflags);
	}
	return 0;
}
