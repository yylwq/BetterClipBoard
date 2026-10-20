import QtQuick 2.15
import QtQuick.Layouts
import QtQuick.Controls
import HuskarUI.Basic

Rectangle {
    id: dataCard

    property int dataId: -1
    property string dataText: ""
    property string dataTag: ""
    property string dataType: ""
    property string dataTimestamp: ""
    property string dataColor: "white"
    property bool dataFavorite: false

    HusMessage {
        id: copyMessage
        z: 999
        parent: betterClipboardWindow.captionBar
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.bottom
    }


    color: dataColor
    radius: 8
    border.width: 1

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 6

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 4

            HusText {
                id: contentText
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: dataText
                font.pixelSize: 18
                font.bold: true
                elide: Text.ElideRight
                wrapMode: Text.WrapAnywhere
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        if (fullTextPopup.opened)
                            fullTextPopup.close()
                        else if (contentText.truncated && !fullTextPopup.opened){
                             fullTextPopup.open()
                        } else {}
                    }
                }
            }

            HusDivider {
                height: 3
                orientation: Qt.Vertical
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 6

                HusTag {
                    text: dataTimestamp
                    colorText: '#EF0A84'
                    presetColor: '#83A8DC'
                }

                Item {
                    Layout.fillWidth: true
                }

                HusSpace {
                    layout: 'Row'

                    HusIconButton {
                        iconSource: HusIcon.CopyOutlined
                        HusToolTip { showArrow: true; visible: parent.hovered; text: '复制' }
                        onClicked: function()
                        {
                            listener.qmlClickCopy(dataText)
                            copyMessage.success("成功复制到剪切板！")
                        }
                    }

                    HusIconButton {
                        iconSource: dataFavorite ? HusIcon.StarFilled : HusIcon.StarOutlined
                        HusToolTip { showArrow: true; visible: parent.hovered; text: '收藏' }

                        onClicked: function()
                        {
                            database.qmlClickChangeFavorite(dataId, dataFavorite, dataType)
                        }
                    }

                    HusIconButton {
                        iconSource: HusIcon.DeleteOutlined
                        HusToolTip { showArrow: true; visible: parent.hovered; text: '删除' }

                        onClicked: function()
                        {
                            database.qmlDeleteData(dataId, dataType)
                        }
                    }
                }
            }
        }
    }

    HusPopup {
        id: fullTextPopup
        width: 500
        height: 500

        x: (parent.width - width) * 0.5
        y: (parent.height - height) * 0.5

        parent: Overlay.overlay
        closePolicy: Popup.NoAutoClose

        movable: true
        resizable: true
        modal: false

        contentItem: Item {
            anchors.fill: parent

            HusCaptionButton {
                id: popCloseButton
                anchors.right: parent.right
                radiusBg.topRight: fullTextPopup.radiusBg.topRight
                colorText: colorIcon
                iconSource: HusIcon.CloseOutlined
                onClicked: fullTextPopup.close()
            }

            HusText {
                anchors.top: popCloseButton.bottom
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left

                text: dataText
                font.pixelSize: 25
                wrapMode: Text.WrapAnywhere
                color: HusTheme.isDark ? '#e0e0e0' : '#333'
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
