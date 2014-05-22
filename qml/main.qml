import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: mainWindow
    title: "Symfony2 Tools"

    width: 350
    height: 150

    function consoleReady() {
        consoleStatus.visible = false;
        consoleButton.enabled = true;
    }

    function composerReady() {
        composerStatus.visible = false;
        composerButton.enabled = true;
    }

    Connections {
        target: cpp

        onConsoleReady: {
            consoleReady();
        }

        onComposerReady: {
            composerReady();
        }
    }

    GridLayout {
        id: gird
        anchors.fill: parent
        anchors.margins: 0
        columns: 1

        ColumnLayout {
            id: leftCol

            RowLayout {
                id: consoleRow

                Button {
                    id: consoleButton
                    text: qsTr("Console")
                    enabled: cpp.isConsoleReady()

                    onClicked: {
                        cpp.displayConsole()
                    }
                }

                ProgressBar {
                    id: consoleStatus
                    indeterminate: true
                    visible: !cpp.isConsoleReady()

                    Layout.fillWidth: true
                }
            }

            RowLayout {
                id: translationRow

                Button {
                    id: translationButton
                    text: qsTr("Translation")
                    enabled: false
                }
            }

            RowLayout {
                id: composerRow

                Button {
                    id: composerButton
                    text: qsTr("Composer")
                    enabled: cpp.isComposerReady()

                    onClicked: {
                        cpp.displayComposer()
                    }
                }

                ProgressBar {
                    id: composerStatus
                    indeterminate: true
                    visible: !cpp.isComposerReady()

                    Layout.fillWidth: true
                }
            }

            RowLayout {
                id: commonRow

                Button {
                    id: cacheButton
                    text: qsTr("Clear cache")
                    enabled: false
                }

                Button {
                    id: schemaButton
                    text: qsTr("Update database schema")
                    enabled: false
                }
            }

            RowLayout {
                id: commonRow2

                Button {
                    id: testButton
                    text: qsTr("Run tests")
                    enabled: false
                }

                Button {
                    id: reloadButton
                    text: qsTr("Reload tools")
                    enabled: false
                }
            }
        }
    }
}
