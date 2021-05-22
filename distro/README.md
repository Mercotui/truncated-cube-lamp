# Linux Distro

Because we need something that runs on a Pi and has qt6 🙃

## Building

Yocto is a bit picky for host machines, so we use an ubuntu container.

```bash
# First this container needs a big ass storage location, up to 50 GB:
export YOCTOWORKDIR=<some big storage location for 50 GB>

#Then we can build the conainter
podman build . -t yoctohost
#Prepare the workdir to be write accessible to our yoctohost user.
podman unshare chown 1001:1001 -R $YOCTOWORKDIR

# To start the container, run:
podman run -it -v $YOCTOWORKDIR:/home/yoctohost/workdir:Z yoctohost
```

From inside this container we run

```bash
cd /home/yoctohost/workdir
../buid-distro.sh
```
