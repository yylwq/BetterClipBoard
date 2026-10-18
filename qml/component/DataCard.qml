import QtQuick 2.15
import QtQuick.Layouts
import HuskarUI.Basic

Rectangle {
    id: dataCard

    property string dataText: ""
    property string dataTag: ""
    property string dataType: ""
    property string dataTimestamp: ""
    property string dataColor: getColor(dataType)

    function getColor(type)
    {
        if (type === "文本") return "#90CAFF";
        if (type === "代码") return "#B0C8FF";
        if (type === "邮箱") return "#FFD9E9";
        return "white";
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
                    text: dataTimestamp
                    presetColor: '#D9B3FF'
                }

                HusTag {
                    text: dataTag
                    presetColor: '#D9B3FF'
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
