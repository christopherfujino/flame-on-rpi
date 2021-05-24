# Flame on Raspberry Pi

## Introduction

My name is Christopher Fujino
- Release engineer on the Flutter team

https://github.com/christopherfujino/flame-on-rpi

## Disclaimers

- I am not paid to build Flutter apps
- I am not paid to speak--opinions are my own
- This workflow is a proof of concept, but not production-ready

## Objectives

- Retro console-style game
- Stable Flutter and Flame versions
- Build and run game from Raspberry Pi

## The Game

Video (demo of shooter game in android emulator)

## The Game on Raspberry Pi

Video (demo of shooter game on raspberry pi, with mouse UI)

## Thank you

Thanks!

## Tree

Flame on Raspberry Pi

## What is Flame?

> 2D game engine made on top of **Flutter**

- Flame games are 100% Flutter apps.

## What is Flutter?

https://flutter.dev

> UI toolkit for building beautiful, natively-compiled applications for mobile,
> web, desktop, and embedded devices from a single codebase.

This includes **Linux desktop** apps!

### Flutter for Desktop

- In public Beta
- Supports Windows, macOS, and Linux

### Flutter for Linux

- Requires GTK and Xorg
- Experimental **Linux ARM64** support!

## What is ARM64?

https://www.youtube.com/watch?v=NNol7fRGo2E

- supports both 32-bit and 64-bit kernels

## What is the Raspberry Pi?

> Your tiny, dual-display, desktop computer and robot brains, smart home hub,
> media centre, networked AI core, factory controller, and much more.

https://www.raspberrypi.org/products/raspberry-pi-4-model-b/specifications/

- Broadcom BCM2711, Quad-core Cortex-A72 (**ARM v8**) 64-bit SoC @ 1.5GHz
- 8gb LPDDR4-3200 SDRAM (also available in 2gb and 4gb)
- 2.4 GHz and 5.0 GHz IEEE 802.11ac wireless, Bluetooth 5.0, BLE
- Gigabit Ethernet
- 2 USB 3.0 ports, 2 USB 2.0 ports
- **OpenGL ES 3.0** graphics

## Operating System

Raspberry Pi OS (formerly Raspbian) is a Debian-based operating system. It only
officially has a 32-bit build

...but there is a [beta version](https://downloads.raspberrypi.org/raspios_arm64/images/raspios_arm64-2021-04-09/)
of Raspberry Pi OS 64-bit.

## Setup

- Raspberry Pi 4b 8gb model
- Raspberry Pi OS ARM64 [2021-04-09 build](https://downloads.raspberrypi.org/raspios_arm64/images/raspios_arm64-2021-04-09/2021-03-04-raspios-buster-arm64.zip)
- Flutter 2.0.0 Stable
  - On Ubuntu I had to use the snap, on Raspberry Pi OS I had to use from source
- Flame Engine 1.0.0-releasecandidate.11
- Linux x64 Desktop Machine for testing (optional but recommended)

## Gamepad

https://www.kernel.org/doc/Documentation/input/joystick-api.txt

[dart:ffi](https://dart.dev/guides/libraries/c-interop)

## Final Demo

Video of game playing full-screen with gamepad.

## Q&A

Thanks!
