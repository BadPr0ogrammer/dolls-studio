import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
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
  SplitView {
    anchors.fill: parent
    orientation: Qt.Horizontal
    Rectangle {
      SplitView.minimumWidth: 200
      SplitView.fillWidth: true
      SplitView.fillHeight: true
      MyModule.MyVtkItem {
        anchors.fill: parent
        objectName: "myVtkItem"
      }
    }
    TreeView {
      SplitView.preferredWidth: 200
      SplitView.maximumWidth: 400
      SplitView.fillHeight: true
      model: myTreeModel
      delegate: TreeViewDelegate {}
    }
  }
  FileDialog {
    id: fileDialog
    onAccepted: { MyModel.handleFileSelected(selectedFile) }
  }
}
