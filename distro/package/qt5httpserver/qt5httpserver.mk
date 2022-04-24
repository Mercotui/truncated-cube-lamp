################################################################################
#
# qt5httpserver
#
################################################################################
QT5HTTPSERVER_VERSION = 5.15
QT5HTTPSERVER_SITE = git://code.qt.io/qt-extensions/qthttpserver.git
QT5HTTPSERVER_GIT_SUBMODULES = YES
QT5HTTPSERVER_SYNC_QT_HEADERS = YES
QT5HTTPSERVER_INSTALL_STAGING = YES

$(eval $(qmake-package))
