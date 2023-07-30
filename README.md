# `mgmtclient`
## Management Cient

`mgmtclient` is a management command line interfaces, allows to send commands (show/config/etc.) to a `daemon`.

## Features

- Support `mgmtcli` to entering the command lines from stdin
    - Support a command line trees that built from sub-daemons
    - Support `?` for helpstring and `tab` for auto complete token texts
- Use Unix Domain Socket (uds) to establish and communicate between a client `mgmtclient` and a server `daemon`

## Tech

`mgmtclient` uses a number of open source projects to work properly:

- [LLDP](https://github.com/lldpd/lldpd) - lldpd: implementation of IEEE 802.1ab (LLDP)
- [GNU readline](https://web.mit.edu/gnu/doc/html/rlman_toc.html#SEC21) - Programming with GNU Readline

## Prerequisite Installation
Install the library

```sh
sudo apt-get install libreadline-dev
```

## Development

#### Building for source

`mgmtclient` requires [GCC](https://gcc.gnu.org/) to run.

For building the software:

```sh
make clean; make
```

For production release:

```sh

```

#### Starting the software

For starting the software:

```sh
./mgmtcli
```

For example:

```sh
[mgmtcli] $ ?
-- Help
      exit  Exit interpreter

[mgmtcli] $ exit

```

## References
[LLDP](https://github.com/lldpd/lldpd)
[GNU readline](https://web.mit.edu/gnu/doc/html/rlman_toc.html#SEC21)

## License

MIT

**Free Software, Hell Yeah!**

