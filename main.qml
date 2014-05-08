import QtQuick 2.1
import QtQuick.Controls 1.0

ApplicationWindow {
    id: window
    title: "Commands for " + commandModel.getName() + " - " + commandModel.getVersion()

    width: 600
    height: 400
    minimumHeight: 400
    minimumWidth: 570

    TableView {
        id: tableview
        anchors.bottom: filterBar.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottomMargin: 2
        model: commandModel

        TableViewColumn {
            title: qsTr("Command")
            role: "name"
        }
        TableViewColumn {
            title: qsTr("Description")
            role: "description"
        }
    }

    TextField {
        id: filterBar
        y: 377
        height: 22
        text: qsTr("")
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: run.left
        anchors.rightMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        font.pixelSize: 12
        placeholderText: qsTr("Filter")
    }

    Button {
        id: run
        width: 100
        height: 22
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        //anchors.left: searchBar.right
        anchors.top: tableview.bottom
        anchors.topMargin: 2
        text: qsTr("Run")
        anchors.leftMargin: 46

    }

}

