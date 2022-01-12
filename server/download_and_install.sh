curl -o caddy "https://caddyserver.com/api/download?os=linux&arch=arm64&p=github.com%2Fcaddy-dns%2Fcloudflare&idempotency=11454617590519"
systemctl stop caddy
cp caddy /usr/bin/caddy
cp Caddyfile.production /etc/caddy/Caddyfile
