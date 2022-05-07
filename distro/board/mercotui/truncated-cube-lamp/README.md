# Overlays

The secrets overlay can be used to add secrets to the device.

To use ssh you should rename:

```bash
rootfs_secrets_overlay/root/.ssh/authorized_keys.template
```

to:

```bash
rootfs_secrets_overlay/root/.ssh/authorized_keys
```

And add your public key.
