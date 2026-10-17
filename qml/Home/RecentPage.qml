import QtQuick 2.15
import QtQuick.Layouts
import BetterClipboard
import "../component"

Rectangle{
    id: recentPage
    anchors.fill: parent
    radius: 8

    property var datas: [
        {text: "dsjaio", color: "red", tag: "reads"}
    ]



    SearchBar{
        id: searchBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 40
    }

    ListView {
        id: recentListView

        anchors.top: searchBar.bottom
        anchors.topMargin: 8
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        clip: true

        model: datas
        delegate: DataCard {
            width: recentListView.width
            dataText: model.text
            dataColor: model.color
            dataTag: model.tag
        }
    }

}


