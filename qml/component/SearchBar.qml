import QtQuick 2.15
import HuskarUI.Basic
import QtQuick.Layouts

HusRectangle{
    id: searchBar
    anchors.leftMargin: 5
    anchors.rightMargin: 5
    anchors.topMargin: 8
    anchors.bottomMargin: 5

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 16
        anchors.rightMargin: 12
        spacing: 8

        HusInput {
            id:searchInput
            Layout.fillWidth: true
            placeholderText: "搜索"
            clearEnabled: true
            onTextChanged: {
                // ...
            }
        }

        HusSelect{
            Layout.preferredWidth: 120
            placeholderText: "时间范围"
            showToolTip: true
            model: [
                { value: "all", label: "全部"      },
                { value: "today", label: "今天"    },
                { value: "week" , label: "本周"    },
                { value: "7days", label: "近7天"   },
                { value: "14days", label: "近14天" }
            ]
        }

        HusSelect {
            Layout.preferredWidth: 110
            placeholderText: "排序"
            showToolTip: true
            model: [
                { value: "newest", label: "最新优先" },
                { value: "oldest", label: "最旧优先" }
            ]
        }
    }

}
