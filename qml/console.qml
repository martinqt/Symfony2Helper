import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0

Window {
    id: window
    objectName: "commandWindow"
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

    function printConsole(type, text) {
        if(type === 0) {
            consoleDisplay.append(text)
        }
        else if(type === 1) {
            consoleDisplay.append("<br/><span style=\"color: #004DD1;\">"+text+"</span><br/>")
        }
        else if(type === 2) {
            consoleDisplay.append("<br/><span style=\"color: #DE1A00;\">"+text+"</span><br/>")
        }

    }

    Connections {
        target: commandModel
        onCompleted: {
            window.unlock()
        }

        onPrint: {
            window.printConsole(type, text)
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
            }
        }

        ColumnLayout {
            id: rightColumn
            width: window.width*2/3

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

