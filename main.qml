import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: appWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Krestiki-Noliki")

    signal qmlSignal(string msg);
    signal tapOnCell(int row, int col);

    Component.onCompleted: {
        for (var idx = 0; idx < 3; ++idx)
            for (var jdx = 0; jdx < 3; ++jdx) {
                var newObject = Qt.createQmlObject('import QtQuick 2.0; Rectangle {border.width: 1; width: parent.width / 3; height: parent.height / 3; x: parent.width / 3 * ' + jdx + '; y: parent.height / 3 *' + idx + ';color: "lightblue"; property int num: 12; }',
                                                   appWindow,
                                                   "cell_" + idx + "_" + jdx);
            }
    }

    MouseArea {
        id: mainHandler
        anchors.fill: parent
        onClicked: function(e) { appWindow.tapOnCell(e.y / appWindow.height * 3, e.x / appWindow.width * 3) }
    }

    Text {
        id: infoText
        z: 1
        anchors.centerIn: parent
        text: "Tap to start"
        font.pointSize: 24
    }

    function myQmlFunction(msg) {
        console.error(msg);
    }

    function switchCell(row, col, value) {
        infoText.text = "";
        var el = findItemById("cell_" + idx + "_" + jdx);
        console.log(el);
    }

    function endGame(whoWon) {
        infoText.text = whoWon + " has been won";
        mainHandler.onClicked = null;
    }
}
