#include <signal.h>
#include <cutils/log.h>

static void SigChldHandler(int)
{
	ALOGE("in SigChldHandler");
}

int main()
{

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SigChldHandler;

	int err = sigaction(SIGCHLD, &sa, NULL);
	if (err < 0) {
		ALOGW("Error setting SIGCHLD handler: %d", errno);
	}

	while(1){
		ALOGE("hello");
	}
	return 0;
}
