#!/usr/bin/env bash

set -euo pipefail

apt-get update && apt-get upgrade --yes
apt-get install --yes\
	git \
	make \
	curl \
	clang \
	cmake \
	libgtk-3-dev \
	ninja-build \
	vim

git config --global user.email 'christopherfujino@gmail.com'
git config --global user.name 'Christopher Fujino'
