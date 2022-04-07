# Truncated Cube Linux

This directory contains everything needed to build a Linux image for the
truncated cube lamp.

## Build requirements

On fedora 35, additional packages have to be installed to build Truncated Cube
Linux:

```txt
perl
```

## Building

Enter the buildroot directory, and run the following commands to build a
firmware image.

```bash
make BR2_EXTERNAL=.. truncated-cube-lamp_defconfig
make
```

## Editing the config

Enter the buildroot directory, and run the following commands to make changes to
the defconfig.

```bash
make BR2_EXTERNAL=.. truncated-cube-lamp_defconfig
make nconfig
make savedefconfig
```
