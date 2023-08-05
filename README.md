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
make distclean; make
```
or we can build the separated binary for `mgmtcli` and `server`
```
make distclean
make server
make mgmtcli
```

For production release:

```sh

```

#### Starting the software

For starting the software:

```sh
mgmtcli
```
TESTING: Starting server to receive messages from `mgmtcli`
```sh
server
```

For example:

```sh
-- Help
       show  Show running system information
  configure  Change system settings
unconfigure  Unconfigure system settings
       exit  Exit interpreter

mgmtcli $ show frequency synchronization interfaces brief 
-------------------------------------------------------------------------------
Frequency Synchronization Interfaces Brief:
------------------------------------------------------------------------------- 
Flags:  > - Up                D - Down              S - Assigned for selection
        d - SSM Disabled      x - Peer timed out    i - Init state
        s - Output squelched, 
Fl   Interfaces               QLrcv QLuse Pri QLsnd Output driven by        
==== ======================== ===== ===== === ===== ========================Decode header message_type: 10 length=4

mgmtcli $ 
```

## References
[LLDP](https://github.com/lldpd/lldpd)
[GNU readline](https://web.mit.edu/gnu/doc/html/rlman_toc.html#SEC21)

## License

MIT

**Free Software, Hell Yeah!**

