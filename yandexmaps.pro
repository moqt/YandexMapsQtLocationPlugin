TARGET = qtgeoservices_yandexmaps

QT += location-private positioning-private network concurrent

QT_FOR_CONFIG += location-private
qtConfig(location-labs-plugin): DEFINES += LOCATIONLABS

android {
    QT += androidextras
}

INCLUDEPATH += ../




HEADERS += \
    qgeoserviceproviderpluginyandexmaps.h \
    qgeocodingmanagerengineyandexmaps.h \
    qgeocodereplyyandexmaps.h \
    qgeomapreplyyandexmaps.h \
    qgeotiledmapyandexmaps.h \
    qgeotiledmappingmanagerengineyandexmaps.h \
    qgeotilefetcheryandexmaps.h

SOURCES += \
    qgeoserviceproviderpluginyandexmaps.cpp \
    qgeocodingmanagerengineyandexmaps.cpp \
    qgeocodereplyyandexmaps.cpp \
    qgeomapreplyyandexmaps.cpp \
    qgeotiledmapyandexmaps.cpp \
    qgeotiledmappingmanagerengineyandexmaps.cpp \
    qgeotilefetcheryandexmaps.cpp


OTHER_FILES += \
    yandexmaps_plugin.json


PLUGIN_TYPE = geoservices
PLUGIN_CLASS_NAME = QGeoServiceProviderFactoryYandexmaps
load(qt_plugin)

DESTDIR = $$[QT_INSTALL_PLUGINS]/$$PLUGIN_TYPE

