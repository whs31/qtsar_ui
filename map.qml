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
    property var imageArray: []
    property var coordinate: QtPositioning.coordinate(0,0);
    property var panToCurrentlocation: QtPositioning.coordinate(51.660784, 39.200268);

    property var enableTooltip: true;
    property var enableMarkerPlacement: false;
    property var enableRoute: true;
    property var enablePlane: true;

    property var gOpacity: 100;

    Invoker {
        id: markerDialog
    }
    function transformScale(fileCounter: int, arg: double)
    {
        imageArray[fileCounter-1].zoomLevel += arg;
    }

    //С ФУНКЦИЙ СПИНБОКСОВ ПОСТУПАЮТ ЗНАЧЕНИЯ В МЕТРАХ, НУЖНО ДЕЛИТЬ ИХ НА 111120
    function transformX(fileCounter: int, arg1: double)
    {
        imageArray[fileCounter-1].coordinate.longitude += (arg1/111120); //fix
    }
    function transformY(fileCounter: int, arg1: double)
    {
        imageArray[fileCounter-1].coordinate.latitude += (arg1/111120); //fix
    }
    function swapMapModes(satellite: bool)
    {
        if(satellite) {
            mapView.activeMapType = mapView.supportedMapTypes[3]//sat
            routeLengthText.color = "white";
        }
        else {
            mapView.activeMapType = mapView.supportedMapTypes[0]//map
            routeLengthText.color = "black";
        }
    }

    function clearRoute()
    {
        var path = mapPolyline.path;
        for (var i = path.length; i >= 0; i--)
        {
            mapPolyline.removeCoordinate(i);
        }
    }

    function changeDrawRoute(arg: int)
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

    function drawRoute(lat: float, lon: float)
    {
        if(enableRoute) {
            mapPolyline.addCoordinate(QtPositioning.coordinate(lat,lon));
            routeLengthText.text = "Точки трека: " + mapPolyline.pathLength();
            var dx = lat - panToCurrentlocation.latitude;
            var dy = lon - panToCurrentlocation.longitude;
            var angle = 0.0;
            if(dx!==0&&dy!==0)
            {
                angle = (Math.atan(dy/dx)* 180)/ Math.PI;
                if(dx<0)
                {
                    angle += 180;
                }
                planeMapItem.transform[0].angle = angle;
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
    function addMarker(lat: float, lon: float, name: QString, mcolor: QColor)
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

    function pan(centerlat: float, centerlon: float, dx: float, dy: float, x0: float, y0: float, angle: float, filename: Qstring)
    {
        console.log("panned");
        mapView.center = QtPositioning.coordinate(centerlat, centerlon);
        mapView.zoomLevel = 14
    }
    function addImage(centerlat: float, centerlon: float, dx: float, dy: float, x0: float, y0: float, angle: float, filename: Qstring)
    {
        console.log("Displaying image from " + filename);
        var item = Qt.createQmlObject('import QtQuick 2.0; import QtLocation 5.12; MapQuickItem{}', mapView, "dynamic");
        //one degree = 111 120 meters
            item.anchorPoint.x = -x0-1.5*y0;
            item.anchorPoint.y = 1.5*y0;
            item.coordinate = QtPositioning.coordinate(centerlat, centerlon);
            item.sourceItem = Qt.createQmlObject('import QtQuick 2.0; Rectangle { opacity: 0.99; Image{ id: imageSource; opacity: 50; source: "file:///'+ filename +'"} }', mapView, "dynamic");
            item.zoomLevel = 16.5
            mapView.addMapItem(item);
            imageArray.push(item);
            //change opacity of newly created jpg
            changeOpacityOfCurrentImage(gOpacity);
    }
    function changeOpacityOfCurrentImage(opacity: int)
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



    Plugin {
        id: googlemaps
        name: "googlemaps"//g
    }

    Map {
        id: mapView
        anchors.fill: parent
        activeMapType: mapView.supportedMapTypes[3]//3
        plugin: googlemaps
        center: QtPositioning.coordinate(51.660784, 39.200268); //51.660784, 39.200268
        zoomLevel: 15
        copyrightsVisible: false

        MapQuickItem {
            id: planeMapItem
            anchorPoint.x: planeSource.width*0.175*0.5;
            anchorPoint.y: planeSource.height*0.175*0.5;
            transform: Rotation {
                origin.x: planeSource.width*0.175*0.5; origin.y: planeSource.height*0.175*0.5; angle: 0
            }

            sourceItem: Image {
                id: planeSource;
                scale: 0.175;
                source: "qrc:/img/planeIco.png"
            }
        }

        MapPolyline {
            id: mapPolyline
            line.width: 4
                opacity: 0.8
                line.color: 'yellow'
                path: [ ]
        }
        MouseArea {
            id: mapMouseArea
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            onEntered: {
                drawTooltip();
            }
            onPositionChanged: {
                changeTooltipPosition();
            }
            onClicked:
            {
                //coordToMarker = mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY));
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
                anchors.bottomMargin: 294
                anchors.top: parent.top
                anchors.topMargin: 8
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
                font.pixelSize: 12
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
}
##^##*/
