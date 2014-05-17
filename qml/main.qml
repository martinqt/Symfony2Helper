import QtQuick 2.0
import QtQuick.Controls 1.0

ApplicationWindow {
    id: mainWindow
    title: "Symfony2 Tools"

    width: 400
    height: 200

    Button {
        id: consoleButton
        text: qsTr("Console")

        onClicked: {
            cpp.displayConsole()
        }
    }
}
