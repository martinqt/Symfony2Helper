import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: window
    objectName: "Window"
    title: "Commands for " + commandModel.getName() + " - " + commandModel.getVersion()

    width: 600
    height: 400
    minimumHeight: 400
    minimumWidth: 570

    ColumnLayout {
        id: vertLay
        objectName: "MainLayout"
        anchors.fill: parent
        anchors.margins: 0
        spacing: 4

        TableView {
            id: tableView
            objectName: "TableView"
            model: commandModel
            Layout.fillWidth: true
            Layout.fillHeight: true

            onClicked: {
                commandModel.getCompleteDescription(row)
            }

            TableViewColumn {
                id: nameColumn
                title: qsTr("Command")
                role: "name"
                width: 225
            }
            TableViewColumn {
                id: descColumn
                title: qsTr("Description")
                role: "description"
                width: tableView.width-nameColumn.width-19
            }
        }

        TextArea {
            id: desc
            readOnly: true
            Layout.fillWidth: true
        }

        GroupBox{
            Layout.fillWidth: true
            flat: true
            anchors.margins: 0

            RowLayout {
                id: row
                anchors.fill: parent

                TextField {
                    id: filterBar
                    text: qsTr("")
                    font.pixelSize: 12
                    placeholderText: qsTr("Filter")
                    Layout.fillWidth: true
                }

                Button {
                    id: run
                    text: qsTr("Run")

                }
            }
        }
    }
}

