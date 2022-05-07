################################################################################
#
# truncated_cube_lamp_service
#
################################################################################

TRUNCATED_CUBE_LAMP_WEBSITE_VERSION = 1.0
TRUNCATED_CUBE_LAMP_WEBSITE_LICENSE = MIT
TRUNCATED_CUBE_LAMP_WEBSITE_SITE = $(BR2_EXTERNAL_TRUNCATED_CUBE_LINUX_PATH)/../website/dist
TRUNCATED_CUBE_LAMP_WEBSITE_SITE_METHOD = local

define TRUNCATED_CUBE_LAMP_WEBSITE_INSTALL_TARGET_CMDS
		$(INSTALL) -d $(TARGET_DIR)/var/www/html
		cp -r $(@D)/* $(TARGET_DIR)/var/www/html
endef

$(eval $(generic-package))
