import QtQuick 2.0
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Controls 2.12

Rectangle {
    id:rect
    objectName: "mapLoaded"
    property var imageArray: []
    property var coordinate: QtPositioning.coordinate(0,0);
    property var coordToMarker: QtPositioning.coordinate(0,0);
    property var panToCurrentlocation: QtPositioning.coordinate(51.660784, 39.200268);

    property var enableTooltip: true;
    property var enableMarkerPlacement: false;
    property var enableRoute: true;
    property var markerName: "Новый маркер";


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
            panToCurrentlocation = QtPositioning.coordinate(lat,lon);
        }
    }

    function prepareMarker()
    {
        enableMarkerPlacement = true;
    }
    function addMarker(lat: float, lon: float)
    {
        console.log(lat, lon, markerName);
        var marker = Qt.createQmlObject('import QtQuick 2.0; import QtLocation 5.12; MapQuickItem{}', mapView, "dynamic");
        marker.anchorPoint.x = 64;
        marker.anchorPoint.y = 64+32;
        marker.coordinate = QtPositioning.coordinate(lat, lon);
        marker.sourceItem = Qt.createQmlObject('import QtQuick 2.0; Item { Text {anchors.horizontalCenter : markerSource.horizontalCenter; anchors.bottom : markerSource.bottom; anchors.bottomMargin: 30; font.weight: Font.Thin; horizontalAlignment: Text.AlignHCenter; verticalAlignment : Text.AlignBottom; text: "'+markerName+'"; color: "white"} Image{ id: markerSource; scale: 0.35; source: "qrc:/img/mapMarker.png" }}', mapView, "dynamic");
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
    }
    function changeOpacityOfCurrentImage(opacity: int)
    {
        var realOpacity = opacity/100;
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
            //onPressed: clearTooltip();
            //onReleased: drawTooltip();
            onClicked:
            {
                coordToMarker = mapView.toCoordinate(Qt.point(mapMouseArea.mouseX,mapMouseArea.mouseY));
                if(enableMarkerPlacement===true)
                {
                    dialogNameMarker.open();
                    //console.log(markerName);
                }
            }

            onExited: {
                clearTooltip();
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
    }
    Dialog {
        id: dialogNameMarker
        anchors.centerIn: parent
        title: "Новый маркер"
        modal: true
        font.weight: Font.Thin
        width: 320
        height: 160
        standardButtons: StandardButton.Ok
        Row {
            anchors.centerIn: parent
            Label {
                text: "Введите название нового маркера:  "
                color: "gray"
            }
            TextInput {
                id: inputDialog
                cursorVisible: true
                text: "Новый маркер"
                overwriteMode: true
                selectByMouse: true
            }
        }
        onAccepted: {
            console.log(inputDialog.text);
            markerName = inputDialog.text;
            addMarker(coordToMarker.latitude, coordToMarker.longitude);
        }
    }

}






