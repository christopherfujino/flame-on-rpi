# Flame on the Raspberry Pi

Presentation [slide deck](https://docs.google.com/presentation/d/1SZP-DKN3A7NbbZr_ph5wViepDqIyLXmplH0BO0ZaDPY/edit#slide=id.gdcc98730aa_0_194)

## Videos

- [demo 1](https://youtu.be/_LZrw9Tvd5U)
- [demo 2](https://youtu.be/DVlXpGtyGmc)

## OS

[Raspberry Pi OS ARM64 beta](https://downloads.raspberrypi.org/raspios_arm64/images/raspios_arm64-2021-04-09)

## Flutter

Flutter version 2.0.0

Must install from source: `git clone https://github.com/flutter/flutter -b stable`

`$ bin/flutter config --enable-linux-desktop`

## Debugging

```
dart pub global activate devtools
ssh -L $PORT:localhost:$PORT $USER@$RASPBERRY_PI_IP
dart pub global run devtools
```
