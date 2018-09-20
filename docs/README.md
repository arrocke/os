# Documentation

## Development

> Building the kernel requires `make`, `gcc`, and `nasm` to be installed. Debugging the kernel requires `bochs`.

### Building the Kernel

Build the kernel with `make build`. This generates an ISO file that can be installed in a virtual machine or on an X86 machine.

### Runnning the Kernel

If `bochs` is installed, running `make test` will start the emulator. The `build/log/os_log.log` will contain the operating system log.
