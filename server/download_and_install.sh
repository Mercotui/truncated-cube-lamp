# This file can be used to install a custom version of caddy,
# that supports the cloudflare dns API for automatic lets encrypt verification
# It's a bit of a hack and has been replaced by the, admittedly also bit hacky,
# buildroot package found in ../distro/package/caddy.
curl -o caddy "https://caddyserver.com/api/download?os=linux&arch=arm64&p=github.com%2Fcaddy-dns%2Fcloudflare"
systemctl stop caddy
cp caddy /usr/bin/caddy
cp Caddyfile.production /etc/caddy/Caddyfile
