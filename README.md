# Yandex Maps plugin for QtLocation
YandexMaps plugin for QtLocation module

***Tested with Qt 5.15.2***

## Supported features:
- Online geocoding
- Reverse geocoding
- Online mapping

## Integration
- Build the project to install plugin
- Add the reference in your app pro file 
```
include(YandexMapsPlugin/qt_plugin_qtgeoservices_yandexmaps.pri) 
```

## Declare plugin in QML
```
    property Plugin pluginYandex: Plugin {
        name: 'yandexmaps'
        PluginParameter {
            name: "yandexmaps.geocode.apikey"; value: "YOUR-KEY"
        }
    }    
```

## Available parameters:
- yandexmaps.apikey
- yandexmaps.geocode.apikey
- yandexmaps.maps.apikey
- yandexmaps.maps.language
- yandexmaps.maps.scale
- yandexmaps.maps.tilesize
- yandexmaps.cachefolder
- yandexmaps.useragent
