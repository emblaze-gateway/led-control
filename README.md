# Control built-in LED indicator

Control over the Tinkerboard2/2S built-in LED indicator.


## Usage

/path/to/led\_control {on | off} {LED0 | LED1 | LED2}

- LED0: Red
- LED1: Green
- LED2: Orange


## How to Build

`cmake` is a prerequisite.

```bash
$ cd led-control
$ cmake .
$ make
$ sudo make install
```


## Example

```bash
$ ./led_control on LED0
$ ./led_control off LED1
```
