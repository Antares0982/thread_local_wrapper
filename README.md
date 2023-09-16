# Thread Local Wrapper
Toy `thread_local` wrapper to implement a workaround for broken MinGW-W64 thread model. See more details [here](https://github.com/msys2/MINGW-packages/issues/2519).

### How To Use

```c++
auto &object = Antares::tls_get<T>();
```

