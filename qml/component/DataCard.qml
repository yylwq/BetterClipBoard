import QtQuick 2.15
import QtQuick.Layouts
import HuskarUI.Basic

Rectangle {
    id: dataCard

    height: 200
    width: 400

    anchors.leftMargin: 5
    anchors.rightMargin: 5
    anchors.topMargin: 8
    anchors.bottomMargin: 5

    property string dataText: "123"
    property color dataColor: "pink"
    property string dataTag: "123"

    color: dataColor
    radius: 8
    border.width: 1

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 6

        // 左侧
        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 4

            HusText {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: dataText
                font.pixelSize: 18          // 字体加大
                font.bold: true
                elide: Text.ElideRight
                maximumLineCount: 2
                wrapMode: Text.WrapAnywhere
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter   // 垂直居中
            }

            HusDivider {
                height: 3
                orientation: Qt.Vertical
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 6

                HusTag {
                    text: dataTag
                    presetColor: 'magenta'
                }

                Item {
                    Layout.fillWidth: true
                }

                HusSpace {
                    layout: 'Row'

                    HusIconButton {
                        iconSource: HusIcon.CopyOutlined
                        HusToolTip { showArrow: true; visible: parent.hovered; text: '复制' }
                    }

                    HusIconButton {
                        iconSource: HusIcon.StarOutlined
                        HusToolTip { showArrow: true; visible: parent.hovered; text: '收藏' }
                    }

                    HusIconButton {
                        iconSource: HusIcon.DeleteOutlined
                        HusToolTip { showArrow: true; visible: parent.hovered; text: '删除' }
                    }
                }
            }
        }
    }
}
