import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: window
    objectName: "Window"
    title: "Commands for " + commandModel.getName() + " - " + commandModel.getVersion()

    width: 800
    height: 400
    minimumHeight: 400
    minimumWidth: 570

    function lock() {
        run.enabled = false;
        parameters.enabled = false;
    }

    function unlock() {
        run.enabled = true;
        parameters.enabled = true;
    }

    Connections {
        target: commandModel
        onCompleted: {
            window.unlock()
        }
    }

    GridLayout {
        id: graidLay
        objectName: "MainLayout"
        anchors.fill: parent
        anchors.margins: 0
        columns: 2

        ColumnLayout {
            id: leftColumn

            TableView {
                id: tableView
                objectName: "TableView"
                model: commandModel
                Layout.fillWidth: true
                Layout.fillHeight: true

                onClicked: {
                    desc.text = commandModel.getCompleteDescription(row)
                    parameters.text = ""
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
                    width: tableView.width-nameColumn.width-18
                }
            }

            TextArea {
                id: desc
                readOnly: true
                Layout.fillWidth: true
                textFormat: TextEdit.RichText
            }

            /*GroupBox{
                Layout.fillWidth: true
                flat: true
                anchors.margins: 0*/

                RowLayout {
                    id: rowLay
                    anchors.bottom: window.bottom

                    TextField {
                        id: parameters
                        text: qsTr("")
                        font.pixelSize: 12
                        placeholderText: qsTr("Parameters")
                        Layout.fillWidth: true

                        onAccepted: {
                            commandModel.runCommand(tableView.currentRow, parameters.text)
                            window.lock()
                        }
                    }

                    Button {
                        id: run
                        text: qsTr("Run")

                        onClicked: {
                            commandModel.runCommand(tableView.currentRow, parameters.text)
                            window.lock()
                        }
                    }
                //}
            }
        }

        ColumnLayout {
            id: rightColumn

            TextArea {
                id: consoleDisplay
                readOnly: true
                Layout.fillWidth: true
                Layout.fillHeight: true
                textFormat: TextEdit.RichText
            }

            TextField {
                id: consoleInput
                text: qsTr("")
                font.pixelSize: 12
                Layout.fillWidth: true
            }
        }
    }
}

