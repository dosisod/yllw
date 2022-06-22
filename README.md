# yllw

A suckless X11 blue light filter in less then 100 lines of C.

## Why?

I've been wanting to start using X11, and this seemed like a small enough
application to start with.

## Installing Dependencies

### Arch Linux

```
$ pacman -S cairo libxfixes libxrandr libxcomposite
```

### Ubuntu (22.04)

```
$ apt install libcairo2-dev libxfixes-dev libxrandr-dev libxcomposite-dev
```

## Building and Running

```
$ git clone https://github.com/dosisod/yllw
$ cd yllw

$ make
$ ./yllw # run local version

$ sudo make install
$ yllw # run installed version
```

## Configuring

You can modify and recompile `config.h`, or use the command line arguments:

```
$ yllw -h
usage: ./yllw [-r n] [-g n] [-b n] [-a n]
```

## Notes

* Multi-monitor support is untested
* Doesn't check if `yllw` is already running when first starting
* Manpage doesn't exist (yet)
* `yllw` needs to be started manually. Considering using cronjob to start it
