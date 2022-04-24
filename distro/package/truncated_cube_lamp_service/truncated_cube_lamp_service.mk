################################################################################
#
# truncated_cube_lamp_service
#
################################################################################

TRUNCATED_CUBE_LAMP_SERVICE_VERSION = 1.0
TRUNCATED_CUBE_LAMP_SERVICE_SITE = $(BR2_EXTERNAL_TRUNCATED_CUBE_LINUX_PATH)/../service
TRUNCATED_CUBE_LAMP_SERVICE_SITE_METHOD = local

$(eval $(cmake-package))
