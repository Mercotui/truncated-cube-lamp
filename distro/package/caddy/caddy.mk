################################################################################
#
# caddy
#
################################################################################

CADDY_VERSION = 1.0
CADDY_LICENSE = Apache-2.0
CADDY_LICENSE_FILES = COPYING
CADDY_SITE = $(BR2_EXTERNAL_TRUNCATED_CUBE_LINUX_PATH)/../server
CADDY_SITE_METHOD = local

define CADDY_INSTALL_TARGET_CMDS
    # This is a hack, but I can't be bothered to build this GO application
    # from source when there is a perfectly fine binary available.
    wget --output-document=$(TARGET_DIR)/usr/bin/caddy "https://caddyserver.com/api/download?os=linux&arch=arm64&p=github.com%2Fcaddy-dns%2Fcloudflare"
    $(INSTALL) -D -m 0644 $(@D)/caddy.service $(TARGET_DIR)/etc/systemd/system/
    $(INSTALL) -D -m 0644 $(@D)/Caddyfile.production $(TARGET_DIR)/etc/caddy/Caddyfile
endef

define CADDY_USERS
    caddy -1 caddy -1 * /home/caddy - - www "Caddy web server"
endef

define CADDY_PERMISSIONS
    /usr/bin/caddy f 0755 root root - - - - -
endef

$(eval $(generic-package))
