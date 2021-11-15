import QtQuick 2.0
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

import cpp.invoker 1.0



Rectangle {
    id:rect
    objectName: "mapLoaded"
    //эти переменные должны импортироваться из .ini
    property var mapProvider: "osm";
    property var cacheParam: "osm.mapping.cache.directory"; // Вероятнее всего, это не верный параметр для гугла
    property var cacheDir: "osmCache/";
    property var mapModeSat: 5;
    property var mapModeMap: 0;

    property var dAzimuth: 0.0;
    property var dLength: 0.0;
    property var dAngle: 0.0;
    property var dTime: 0.0;
    property var predictLength: 0.2;

    property var planeSpeed: 80.0;
    //---------------------------------------------
    property var rectMajor: 0.0;
    property var rectMinor: 0.0;

    property var imageArray: []
    property var coordinate: QtPositioning.coordinate(0,0);
    property var panToCurrentlocation: QtPositioning.coordinate(51.660784, 39.200268);

    property var enableTooltip: true;
    property var enableMarkerPlacement: false;
    property var enableRoute: true;
    property var enablePlane: true;
    property var enableRuler: false;
    property var rulerSecondBoolean: false;
    property var ruler1c: QtPositioning.coordinate(0,0);
    property var ruler2c: QtPositioning.coordinate(0,0);
    property var gOpacity: 100;

    onMapProviderChanged: {
        console.log("Map mode changed.");
        //googlemaps.name = mapProvider;
    }

    Invoker {
        id: markerDialog
    }

    function loadSettings(provider, d_azimuth, d_length, drift_angle, capture_time, predict_range)
    {
        console.log("QML settings loaded!");
        if(provider==="google")
        {
            mapProvider = "googlemaps";
            cacheParam = "googlemaps.mapping.cache.directory"; // Другое название
            cacheDir = "googleCache/";
            mapModeSat = 3;
            mapModeMap = 0;
        } else if(provider==="esri") {
            mapModeSat = 9;
            mapModeMap = 5;
            mapProvider = "mapboxgl";
            cacheParam = "mapboxgl.mapping.cache.directory"; // Другое название
            cacheDir = "mapboxglCache/";

        } else if(provider==="osm") {
            mapModeSat = 5;
            mapModeMap = 0;
            mapProvider = "osm";
            cacheParam = "osm.mapping.cache.directory";
            cacheDir = "osmCache/";
        }
        dAzimuth = d_azimuth;
        dLength = convertGeoKMeters(d_length);
        dAngle = drift_angle;
        dTime = capture_time;
        predictLength = convertGeoKMeters(predict_range);

        //Math block
        var b = 0.5*(180-dAzimuth);
        var c = 90-b;
        c = c*Math.PI/180;
        var radAzimuth = (dAzimuth*Math.PI)/180;
        var side = dLength/(Math.cos(c));
        rectMajor = side*Math.sqrt(2-2*Math.cos(radAzimuth));
        rectMinor = rectMajor*0.15;
        //console.log("Большая сторона полигона: ", rectMajor, " , меньшая сторона полигона: ", rectMinor);
        //-----------
    }

    function rulerHandler()
    {
        enableRuler = true;
    }

    function ruler()
    {
        var dx = Math.abs(ruler1c.longitude-ruler2c.longitude);
        var dy = Math.abs(ruler1c.latitude-ruler2c.latitude);
        var output = 111.12*Math.sqrt(dx*dx+dy*dy);
        //console.log("Ruler output: ", output, " km");
        rulerText.text = "Линейка: "+output.toFixed(3)+" км";
        rulerLine.addCoordinate(ruler1c);
        rulerLine.addCoordinate(ruler2c);
        return output; //шрифт у линейки должен быть жирный и больше, передвинуть текст надо к зумслайдеру
    }

    function convertGeoKMeters (metric)
    {
        //1 градус = 111.12 км
        return metric*0.00899928;
    }

    function transformRotate(fileCounter, arg)
    {
        console.log(fileCounter);
        imageArray[fileCounter].sourceItem.rotation += arg;
    }

    function transformScale(fileCounter, arg)
    {
        console.log(fileCounter);
        imageArray[fileCounter].zoomLevel += arg;
    }

    //С ФУНКЦИЙ СПИНБОКСОВ ПОСТУПАЮТ ЗНАЧЕНИЯ В МЕТРАХ, НУЖНО ДЕЛИТЬ ИХ НА 111120
    function transformX(fileCounter, arg1)
    {
        imageArray[fileCounter].coordinate.longitude += (arg1/111120);
    }
    function transformY(fileCounter, arg1)
    {
        imageArray[fileCounter].coordinate.latitude += (arg1/111120);
    }
    function swapMapModes(satellite)
    {
        if(satellite) {
            mapView.activeMapType = mapView.supportedMapTypes[mapModeSat]//sat
            routeLengthText.color = "white";
            overlayPlane.color = "#03DAC6";
            mapPolyline.line.color = "#03DAC6";
            mapPredictLine.line.color = '#93E5DD';
            predictPoly.color = '#93E5DD';
            predictPoly.border.color = '#03DAC6';
        }
        else {
            mapView.activeMapType = mapView.supportedMapTypes[mapModeMap]//map
            routeLengthText.color = "black";
            overlayPlane.color = "darkRed";
            mapPolyline.line.color = "darkRed";
            mapPredictLine.line.color = '#ff7a7a';
            predictPoly.color = '#ff7a7a';
            predictPoly.border.color = 'darkRed';
        }
    }

    function clearRoute()
    {
        mapPolyline.path = [];
        mapPredictLine.path = [];
    }

    function changeDrawRoute(arg)
    {
        if(arg===0)
        {
            enableRoute = false;
        }
        else
        {
            enableRoute = true;
        }
    }

    function panGPS()
    {
        mapView.center = panToCurrentlocation;
    }

    function clearPredict()
    {
        mapPredictLine.path = [];
        predictPoly.path = [];
    }

    function drawRoute(lat, lon)
    {
        if(enableRoute) {
            var angle = 0.0;
            var radAngle = 0.0;
            mapPolyline.addCoordinate(QtPositioning.coordinate(lat,lon));
            routeLengthText.text = "Точки трека: " + mapPolyline.pathLength();
            var dx = lat - panToCurrentlocation.latitude;
            var dy = lon - panToCurrentlocation.longitude;
            if(dx!==0&&dy!==0)
            {
                var tan = dy/dx;
                radAngle = Math.atan(tan);
                angle = (radAngle * 180) / Math.PI;
                if(dx<0)
                {
                    angle += 180;
                }
                planeMapItem.rotationAngle = angle; //загадка //проблема в том, как qml считает центр вращения, так как предикт работает как ожидалось //почему-то все не работает на других провайдерах карт
                //нужно попробовать переносить центр вращения картинки каждый вызов функции drawRoute()
                var p_lat = lat+Math.sin((90-angle)*Math.PI/180) * predictLength;
                var p_lon = lon+Math.cos((90-angle)*Math.PI/180) * predictLength;
                /*
                    1 точка -> малое основание трапеции, лежит дальше от иконки
                    2 точка -> малое основание трапеции, лежит ближе к иконке
                    3 точка -> большее основание трапеции, лежит дальше от иконки
                    4 точка -> большее основание трапеции, лежит ближе к иконке
                  */
                var speedxtime = (planeSpeed/3600)*dTime;
                speedxtime = convertGeoKMeters(speedxtime);

                var y1 = lat+Math.sin((90-angle)*Math.PI/180) * speedxtime;
                var x1 = lon+Math.cos((90-angle)*Math.PI/180) * speedxtime;
                var y2 = lat+Math.sin((90-angle)*Math.PI/180) * (speedxtime - rectMinor);
                var x2 = lon+Math.cos((90-angle)*Math.PI/180) * (speedxtime - rectMinor);

                var beta = Math.atan((2*dLength)/(rectMajor-rectMinor));
                var side = dLength / (Math.sin(beta));
                beta = beta * 180 / Math.PI;
                beta = beta + (90-angle);

                var y3 = lat+Math.sin((90-angle)*Math.PI/180) * speedxtime + Math.sin(beta*Math.PI/180) * side;
                var x3 = lon+Math.cos((90-angle)*Math.PI/180) * speedxtime + Math.cos(beta*Math.PI/180) * side;
                var y4 = lat+Math.sin((90-angle)*Math.PI/180) * speedxtime + Math.sin(beta*Math.PI/180) * side - Math.sin((90-angle)*Math.PI/180) * rectMajor;
                var x4 = lon+Math.cos((90-angle)*Math.PI/180) * speedxtime + Math.cos(beta*Math.PI/180) * side - Math.cos((90-angle)*Math.PI/180) * rectMajor;

                clearPredict();
                mapPredictLine.addCoordinate(QtPositioning.coordinate(lat,lon));
                predictPoly.addCoordinate(QtPositioning.coordinate(y1, x1));
                predictPoly.addCoordinate(QtPositioning.coordinate(y2, x2));
                predictPoly.addCoordinate(QtPositioning.coordinate(y4, x4));
                predictPoly.addCoordinate(QtPositioning.coordinate(y3, x3));
                mapPredictLine.addCoordinate(QtPositioning.coordinate(p_lat, p_lon));
            }
            panToCurrentlocation = QtPositioning.coordinate(lat,lon);
        }
        if(enablePlane) {
            planeMapItem.coordinate = QtPositioning.coordinate(lat, lon);
        }
    }

    function prepareMarker()
    {
        enableMarkerPlacement = true;
    }
    function addMarker(lat, lon, name, mcolor)
    {
        //console.log(lat, lon, markerName);
        var marker = Qt.createQmlObject('import QtQuick 2.0; import QtLocation 5.12; import QtGraphicalEffects 1.0; MapQuickItem{ }', mapView, "dynamic");
        marker.anchorPoint.x = 64;
        marker.anchorPoint.y = 64+32;
        marker.coordinate = QtPositioning.coordinate(lat, lon);
        marker.sourceItem = Qt.createQmlObject('
import QtQuick 2.0;
import QtGraphicalEffects 1.0;
Item {
    id: markerQI; visible: true; enabled: true; opacity: 1;
    Text {
        anchors.horizontalCenter: markerSource.horizontalCenter;
        anchors.bottom: markerSource.bottom;
        anchors.bottomMargin: 30;
        font.weight: Font.Thin;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment : Text.AlignBottom;
        text: "'+name+'"; color: "'+mcolor+'";
    }
    Image {
        id: markerSource;
        scale: 0.35;
        source: "qrc:/img/mapMarker.png"
        MouseArea {
            id: markerHoverArea
            propagateComposedEvents: true
            anchors.centerIn: parent;
            width: 150;
            height: 200;
            hoverEnabled: true
            onEntered: {
                markerCross.enabled = true;
                markerCross.visible = true;
            }
            onExited: {
                markerCross.enabled = false;
                markerCross.visible = false;
            }
            onDoubleClicked:
            {
                        markerQI.visible = false;
                        markerQI.enabled = false;
            }
        }
    }
    Image {
        id: markerCross;
        enabled: false;
        visible: false;
        scale: 0.35;
        source: "qrc:/img/close.png";
        anchors.right: markerSource.right;
        anchors.rightMargin: 20;
        anchors.bottom: markerSource.top;
        anchors.bottomMargin: -62;
    }
    ColorOverlay {
        anchors.fill: markerSource;
        source: markerSource;
        scale: 0.35;
        opacity: 0.5;
        color: "'+mcolor+'"
    }
}', mapView, "dynamic");
        //marker.zoomLevel = 16.5;
        mapView.addMapItem(marker);
        enableMarkerPlacement = false;
    }


    function addRulerPoint(lat, lon)
    {
        var rulerPoint = Qt.createQmlObject('import QtQuick 2.0; import QtLocation 5.12; import QtGraphicalEffects 1.0; MapQuickItem{ }', mapView, "dynamic");
        rulerPoint.anchorPoint.x = 128;
        rulerPoint.anchorPoint.y = 128;
        rulerPoint.coordinate = QtPositioning.coordinate(lat, lon);
        rulerPoint.sourceItem = Qt.createQmlObject('
import QtQuick 2.0;
import QtGraphicalEffects 1.0;
Item {
    id: rulerPointSource; visible: true; enabled: true; opacity: 0.9;
    Image {
        id: rulerPointImage;
        scale: 0.07;
        source: "qrc:/img/mapRulerPoint.png"
    }
    ColorOverlay {
        anchors.fill: rulerPointImage;
        source: rulerPointImage;
        scale: 0.07;
        opacity: 1;
        color: "#e8e8e8"
    }
}', mapView, "dynamic");
        mapView.addMapItem(rulerPoint);
    }

    function pan(centerlat, centerlon, dx, dy, x0, y0, angle, filename)
    {
        console.log("panned");
        mapView.center = QtPositioning.coordinate(centerlat, centerlon);
        mapView.zoomLevel = 14
    }
    function addImage(centerlat, centerlon, dx, dy, x0, y0, angle, filename)
    {
        console.log("Displaying image from " + filename);
        var item = Qt.createQmlObject('import QtQuick 2.0; import QtLocation 5.12; MapQuickItem {  }', mapView, "dynamic");
        //one degree = 111 120 meters
        item.anchorPoint.x = 0;
        item.anchorPoint.y = 0;
        item.coordinate = QtPositioning.coordinate(centerlat, centerlon);
        item.sourceItem = Qt.createQmlObject('
import QtQuick 2.0;
import QtGraphicalEffects 1.12;
Rectangle {
    opacity: 1;
    transformOrigin: Item.TopLeft;
    rotation: 0
    Image {
        id: imageSource;
        opacity: 50;
        source: "file:///'+ filename +'"
        visible: false
    }
    Image {
        id: mask
        source: "qrc:/img/jpeg_opacityMask.png"
        sourceSize: Qt.size(imageSource.width, imageSource.height)
        visible: false
    }
    OpacityMask {
        anchors.fill: imageSource
        source: imageSource
        maskSource: mask
    }
}', mapView, "dynamic");
        item.zoomLevel = 17.2; //https://developer.here.com/documentation/data-layers/dev_guide/topics/zoom-levels.html
        mapView.addMapItem(item);
        item.sourceItem.rotation = angle+y0;
        imageArray.push(item);          //если изображения будут отображены не по очереди, то все ломается (возможно, если реворкнуть showButton через чекбоксы, будет лучше)
        //change opacity of newly created jpg
        changeOpacityOfCurrentImage(gOpacity);
    }
    function changeOpacityOfCurrentImage(opacity)
    {
        gOpacity = opacity;
        var realOpacity = gOpacity/100;
        for (var i in imageArray) {
            imageArray[i].sourceItem.opacity = realOpacity;
        }
    }
    function drawTooltip()
    {
        tooltip.visible = true;
        latText.visible = true;
    }
    function changeTooltipPosition()
    {
        if(enableTooltip === true)
        {
            if(mapMouseArea.pressed)
            {
                clearTooltip();
            }
            else {
                drawTooltip();
                tooltip.x = mapMouseArea.mouseX;
                tooltip.y = mapMouseArea.mouseY;
                var coordToStr = mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY));
                //console.log(coordToStr);
                latText.text = "Ш: <b><i>"+coordToStr.latitude.toFixed(5)+"</b></i>,   Д: <b><i>"+coordToStr.longitude.toFixed(5)+"</b></i>";
            }
        }
        else {
            clearTooltip();
        }
    }

    function changeTooltipCheckBox(arg1)
    {
        //console.log(arg1);
        if(arg1 === 2) {
            enableTooltip = true;
        }
        else enableTooltip = false;
    }

    function clearTooltip()
    {
        tooltip.visible = false;
        latText.visible = false;
    }


/*
    Plugin {
        id: googlemaps
        name: mapProvider
    }
*/
    Map {
        id: mapView
        anchors.fill: parent
        activeMapType: mapView.supportedMapTypes[mapModeSat]//3
        plugin: Plugin {
            name: mapProvider;
            PluginParameter {
                name: cacheParam;
                value: cacheDir;
            }
        }
        center: QtPositioning.coordinate(51.660784, 39.200268); //51.660784, 39.200268
        zoomLevel: 15
        copyrightsVisible: false

        MapQuickItem {
            property alias rotationAngle: rotation.angle
            id: planeMapItem
            anchorPoint.x: 20;
            anchorPoint.y: 20;
            transform: Rotation {
                        id: rotation
                        origin { x: 20;
                                 y: 20  }
                        angle: 0
                    }
            z:5
            sourceItem: Image {
                id: planeSource;
                layer.enabled: true
                transformOrigin: Item.Center
                source: "qrc:/img/planeIco.png"
            }
            ColorOverlay {
                id: overlayPlane;
                anchors.fill: planeMapItem;
                source: planeSource;
                opacity: 1;
                color: "#03DAC6"
            }
        }

        MapPolyline {
            id: mapPolyline
            line.width: 4
            opacity: 0.8
            line.color: '#03DAC6'
            path: [ ]
        }
        MapPolyline {
            id: rulerLine
            line.width: 5
            opacity: 0.9
            line.color: '#e8e8e8'
            path: [ ]
        }
        MapPolyline {
            id: mapPredictLine
            line.width: 4
            opacity: 0.4
            line.color: '#93E5DD'
            path: [ ]
        }
        MapPolygon {
            id: predictPoly
            opacity: 0.4
            border.color: "#03DAC6" //03DAC6
            border.width: 2
            color: "#93E5DD"
            path: []
        }

        MouseArea {
            id: mapMouseArea
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onEntered: {
                drawTooltip();
            }
            onPositionChanged: {
                changeTooltipPosition();
            }
            onClicked:
            {
                //coordToMarker = mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY));
                if(rulerSecondBoolean === false & enableRuler === false)
                {
                    rulerLine.path = [];
                }

                if(rulerSecondBoolean === true & mouse.button === Qt.LeftButton)
                {
                    ruler2c = mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY));
                    rulerSecondBoolean = false;
                    addRulerPoint(ruler2c.latitude, ruler2c.longitude);
                    ruler();
                }
                if(enableRuler === true & mouse.button === Qt.LeftButton)
                {
                    rulerLine.path = [];
                    ruler1c = mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY));
                    rulerSecondBoolean = true;
                    addRulerPoint(ruler1c.latitude, ruler1c.longitude);
                    enableRuler = false;
                }

                if(rulerSecondBoolean === true & mouse.button === Qt.RightButton)
                {
                    rulerSecondBoolean = false;
                }
                else if(enableRuler === true & mouse.button === Qt.RightButton)
                {
                    enableRuler = false;
                }


                if(enableMarkerPlacement===true)
                {
                    var markerCoord = mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY));
                    markerDialog.qmlDialogMarker(markerCoord.latitude, markerCoord.longitude);
                }
            }

            onExited: {
                clearTooltip();
            }

            Slider {
                id: slider
                x: 592
                width: 40
                opacity: 0.5
                live: true
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 150
                anchors.top: parent.top
                anchors.topMargin: 50
                anchors.right: parent.right
                anchors.rightMargin: 8
                snapMode: Slider.NoSnap
                to: 0
                from: 1
                layer.enabled: false
                transformOrigin: Item.BottomRight
                wheelEnabled: false
                clip: false
                orientation: Qt.Vertical
                value: 0.75
                onMoved: mapView.zoomLevel = (1-value)*19;
            }

            Text {
                id: routeLengthText;
                x: 609
                y: 458
                color: "#ffffff"
                text: qsTr("Точки трека: ---")
                anchors.right: parent.right
                anchors.rightMargin: 8
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 8
                font.pixelSize: 9
            }

            Rectangle {
                id: rectangle
                height: 22
                color: "#242424"
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0

                Text {
                    id: rulerText
                    width: 109
                    height: 14
                    color: "#FFFFFF"
                    text: qsTr("Линейка: 0.000 км")
                    font.bold: true
                    font.weight: Font.Bold
                    textFormat: Text.RichText
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    anchors.top: parent.top
                    anchors.topMargin: 3
                    font.pixelSize: 12
                }
            }

        }

        Popup {
            id: popup
            modal: true
            focus: true
            visible: true
            width: 0
            height: 0
            Rectangle {
                id: tooltip
                color: "white"
                width: 148
                height: 15
                radius: 1
                opacity: 0.75
                Text {
                    id: latText
                    enabled: false
                    anchors.fill: parent
                    textFormat: Text.StyledText
                }
            }
        }
        Component.onCompleted: {
            mapView.addMapItem(planeMapItem);
        }
    }
}







/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:9;anchors_height:270;anchors_width:40;anchors_x:592;anchors_y:8}
D{i:15;anchors_x:"-685";anchors_y:872}D{i:14;anchors_width:200;anchors_x:146;anchors_y:76}
}
##^##*/
