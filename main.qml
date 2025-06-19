import QtQuick
import QtQuick.Controls
import MyModule 1.0 as MyModule

ApplicationWindow {
  visible: true
  width: 640
  height: 640
  title: qsTr("Dolls Studio")
  header: MenuBar {
    Menu {
      title: qsTr("&File")
      Action {
        text: qsTr("&Open...")
        onTriggered: console.log("Open action triggered")
      }
      MenuSeparator { }
      Action {
        text: qsTr("&Exit")
        onTriggered: Qt.quit()
      }
    }
  }
  Rectangle {
    anchors.fill: parent
    anchors.margins: 12

    MyModule.MyVtkItem {
      anchors.fill: parent
    }
  }
}
