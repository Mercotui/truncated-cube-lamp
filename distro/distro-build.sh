#!/usr/bin/env bash

# sync repos
repo sync

# configure the environment
export MACHINE=raspberrypi3
source ./setup-environment.sh

# build!
bitbake b2qt-embedded-qt6-image
bitbake meta-toolchain-b2qt-embedded-qt6-sdk
