import QtQuick 2.15
import QtQuick.Layouts
import BetterClipboard
import QtQuick.Controls
import HuskarUI.Basic
import "../component"

Rectangle{
    id: recentPage
    anchors.fill: parent
    radius: 8

    SearchBar{
        id: searchBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 40

        keyword:   recentSearchProxyModel.keyword
        timeRange: recentSearchProxyModel.timeRange
        sortOrder: recentSearchProxyModel.sortOrder

        onKeywordChanged:   recentSearchProxyModel.keyword   = keyword
        onTimeRangeChanged: recentSearchProxyModel.timeRange = timeRange
        onSortOrderChanged: recentSearchProxyModel.sortOrder = sortOrder
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

        model: recentSearchProxyModel

        delegate: Item {
            width: recentGridView.cellWidth
            height: recentGridView.cellHeight

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
