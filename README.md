## ALOGE is not safe in signal handler
This demostrate that logging event to logcat buffer in signal handler
is not safe and can deadlock the process in Android.
(This should be fixed in latest Android release)

## Usage

```adb console
$ log_unsafe 

Another adb console
$ logcat

Another adb console
$ while [ 1 ] ; do kill -17 `pidof log_unsafe`; done
```

## Output
Something like:
```E/        (15695): hello
E/        (15695): in SigChldHandler
E/        (15695): hello
E/        (15695): hello
```
And then log_unsafe hangs, from strace it is dead lock waiting for mutex in signal
handler, while it already holding the mutex in the main process thread.
