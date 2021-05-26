#!/usr/bin/env bash

set -euo pipefail

sudo apt-get update
sudo apt-get upgrade --yes

# npm & python needed for reveal.js
# liblzma-dev for app
sudo apt-get install --yes\
  git \
  make \
  curl \
  clang \
  cmake \
  libgtk-3-dev \
  ninja-build \
  vim \
  python \
  liblzma-dev \
  libgl1-mesa-dev \
  libgles2-mesa-dev \
  libegl1-mesa-dev \
  libdrm-dev \
  libgbm-dev \
  ttf-mscorefonts-installer \
  fontconfig \
  libsystemd-dev \
  libinput-dev \
  libudev-dev \
  libxkbcommon-dev
