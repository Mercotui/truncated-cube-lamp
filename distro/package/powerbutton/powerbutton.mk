################################################################################
#
# powerbutton
#
################################################################################

POWERBUTTON_VERSION = 1.0
POWERBUTTON_LICENSE = MIT
POWERBUTTON_SITE = $(BR2_EXTERNAL_TRUNCATED_CUBE_LINUX_PATH)/../powerbutton
POWERBUTTON_SITE_METHOD = local

define POWERBUTTON_INSTALL_TARGET_CMDS
    $(INSTALL) -d $(TARGET_DIR)/usr/local/bin/
    $(INSTALL) -D -m 0755 $(@D)/powerbutton.py $(TARGET_DIR)/usr/local/bin/
    $(INSTALL) -D -m 0644 $(@D)/powerbutton.service $(TARGET_DIR)/etc/systemd/system/
endef

$(eval $(generic-package))
