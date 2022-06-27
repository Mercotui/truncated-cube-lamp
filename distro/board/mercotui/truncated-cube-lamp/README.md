# Overlays

The secrets overlay can be used to add secrets to the device.

## SSH

To use ssh you should rename:

```bash
rootfs_secrets_overlay/root/.ssh/authorized_keys.template
```

to:

```bash
rootfs_secrets_overlay/root/.ssh/authorized_keys
```

And add your public key.

## Caddy LetsEncrypt

To use Caddy's automatic lets encrypt support you should copy:

```bash
truncated-cube-lamp/server/Caddyfile.production
```

to:

```bash
rootfs_secrets_overlay/etc/caddy/Caddyfile
```

And fill in the missing values.
