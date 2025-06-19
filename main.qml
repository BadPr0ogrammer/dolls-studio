import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import MyModule 1.0 as MyModule

ApplicationWindow {
  visible: true
  width: 640
  height: 640
  title: qsTr("Dolls Studio")
  header: MenuBar {
    Menu {
      id: menuOpen
      title: qsTr("&File")
      Action {
        text: qsTr("&Open...")
        onTriggered: fileDialog.open()
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
      objectName: "myVtkItem"
      anchors.fill: parent
    }
  }
  FileDialog {
    id: fileDialog
    //currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
    onAccepted: { ModelAc.handleFileSelected(selectedFile) }

  }
}
