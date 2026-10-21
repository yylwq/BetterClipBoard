import QtQuick 2.15
import QtQuick.Layouts
import BetterClipboard
import QtQuick.Controls
import HuskarUI.Basic
import "../component"

Rectangle{
    id: favoritePage
    anchors.fill: parent
    radius: 8

    Global { id: global2 }

    HusTabView {
        id: favoriteTabView

        anchors.top: favoritePage.top
        anchors.bottom: favoritePage.bottom
        anchors.left: favoritePage.left
        anchors.right: favoritePage.right

        anchors.topMargin: 8
        anchors.bottomMargin: 5
        anchors.leftMargin: 5
        anchors.rightMargin: 5

        initModel: global2.favoritePageTabModel

        contentDelegate: Rectangle{
            id: favoritePageDelegate
            anchors.fill: parent
            radius: 8

            SearchBar{
                id: favoriteSearchBar
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                height: 40
            }

            GridView {
                id: favoriteGridView

                anchors.top: favoriteSearchBar.bottom
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
                    switch (favoriteTabView.currentIndex) {
                    case 0: return allFavoriteDataModel
                    case 1: return textFavoriteDataModel
                    case 2: return codeFavoriteDataModel
                    case 3: return emailFavoriteDataModel
                    case 4: return urlFavoriteDataModel
                    case 5: return magneticseedFavoriteDataModel
                    default: return allFavoriteDataModel
                    }
                }

                delegate: Item {
                    width: favoriteGridView.cellWidth
                    height: favoriteGridView.cellHeight

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




