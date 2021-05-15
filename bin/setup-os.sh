#!/usr/bin/env bash

set -euo pipefail

# Don't run as root, we will switch to root later

if [ "$EUID" -eq 0 ]; then
	echo "Don't run as root."
	exit 1
fi

git config --global user.email 'christopherfujino@gmail.com'
git config --global user.name 'Christopher Fujino'

sudo apt-get update
sudo apt-get upgrade --yes

# npm & python needed for reveal.js
sudo apt-get install --yes\
	git \
	make \
	curl \
	clang \
	cmake \
	libgtk-3-dev \
	ninja-build \
	vim \
	npm \
	python
