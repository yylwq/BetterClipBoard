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
            id: historyPageDelegate
            anchors.fill: parent
            radius: 8

            property var curProxyModel: {
                switch (historyTabView.currentIndex) {
                case 1: return codeSearchProxyModel
                case 2: return emailSearchProxyModel
                case 3: return urlSearchProxyModel
                case 4: return magneticseedSearchProxyModel
                default: return textSearchProxyModel
                }
            }

            SearchBar{
                id: searchBar
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                height: 40

                Component.onCompleted: {
                    keyword   = curProxyModel.keyword
                    timeRange = curProxyModel.timeRange
                    sortOrder = curProxyModel.sortOrder
                }

                onKeywordChanged:   curProxyModel.keyword   = keyword
                onTimeRangeChanged: curProxyModel.timeRange = timeRange
                onSortOrderChanged: curProxyModel.sortOrder = sortOrder
            }

            GridView {
                id: historyGridView

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

                model: curProxyModel

                delegate: Item {
                    width: historyGridView.cellWidth
                    height: historyGridView.cellHeight

                    DataCard {
                        width: parent.width - 8
                        height: 148
                        anchors.centerIn: parent

                        dataId: model.id
                        dataText: model.text
                        dataType: model.type
                        dataTag: model.tag
                        dataTimestamp: model.timestamp
                        dataFavorite: model.favorite
                    }
                }
            }
        }
    }
}
