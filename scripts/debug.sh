#!/usr/bin/env sh
set -e

case "$1" in
  server)
    openocd -f board/st_nucleo_f4.cfg
    ;;
  gdb)
    arm-none-eabi-gdb build/conan/app/astra-os-fw \
      -ex "target remote :3333"
    ;;
esac
