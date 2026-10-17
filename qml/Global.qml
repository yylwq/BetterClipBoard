import QtQuick 2.15
import HuskarUI.Basic

QtObject {
    id: root

    property var betterCBMenuModel: [
        { key: "recentPage", label: "最近记录", iconSource: HusIcon.HistoryOutlined},
        { key: "historyPage", label: "历史记录", iconSource: HusIcon.BarsOutlined},
        { key: "favoritePage", label: "收藏", iconSource: HusIcon.HeartOutlined}
    ]
}
