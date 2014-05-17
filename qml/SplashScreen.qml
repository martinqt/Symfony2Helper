import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0

Window {
    id: window
    width: 500
    height: 200

    ColumnLayout {
        id: column
        anchors.fill: parent

        Image {
            id: image
            source: "qrc:/icons/sf2_large"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        ProgressBar {
            id: progress
            indeterminate: true
            Layout.fillWidth: true
        }

    }
}
