import QtQuick 2.15
import QtQuick.Layouts
import BetterClipboard
import QtQuick.Controls
import HuskarUI.Basic
import "../component"

Rectangle{
    id: historyPage
    anchors.fill: parent
    radius: 8

    Global { id: global1 }

    HusTabView {
        id: historyTabView

        anchors.top: historyPage.top
        anchors.bottom: historyPage.bottom
        anchors.left: historyPage.left
        anchors.right: historyPage.right

        anchors.topMargin: 8
        anchors.bottomMargin: 5
        anchors.leftMargin: 5
        anchors.rightMargin: 5

        initModel: global1.historyPageTabModel

        contentDelegate: Rectangle{
            id: hidtoryPageDelegate
            anchors.fill: parent
            radius: 8


            SearchBar{
                id: searchBar
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                height: 40
            }

            GridView {
                id: recentGridView

                anchors.top: searchBar.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                anchors.topMargin: 8
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                anchors.bottomMargin: 5

                clip: true

                cellWidth: width / 2
                cellHeight: 155

                ScrollBar.vertical: HusScrollBar {}

                model: {
                    switch (historyTabView.currentIndex) {
                    case 1: return codeDataModel
                    case 2: return emailDataModel
                    case 3: return urlDataModel
                    case 4: return magneticseedDataModel
                    default: return textDataModel
                    }
                }

                delegate: Item {
                    width: recentGridView.cellWidth
                    height: recentGridView.cellHeight

                    DataCard {
                        width: parent.width - 8
                        height: 148
                        anchors.centerIn: parent

                        dataText: model.text
                        dataType: model.type
                        dataTag: model.tag
                        dataTimestamp: model.timestamp
                    }
                }
            }
        }
    }
}


