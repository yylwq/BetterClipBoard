import QtQuick
import HuskarUI.Basic
import BetterClipboard

HusWindow {
    id: betterClipboardWindow
    width: 1400
    height: 900
    // opacity: 0
    minimumWidth: 800
    minimumHeight: 600
    visible: true
    title: qsTr("Better Clipboard")

    followThemeSwitch: true

    // CaptionBar 配置
    captionBar.visible: true
    captionBar.height: 30
    captionBar.showThemeButton: true
    captionBar.showTopButton: true
    // captionBar.themeCallback: () => themeSwitchLoader.active = true
    captionBar.topCallback:   (checked) => HusApi.setWindowStaysOnTopHint(galleryWindow, checked)

    Global { id: global }

    Item {
        id: content
        anchors.top: captionBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.margins: 5

        Rectangle {
            id: betterClipboardBackground
            anchors.fill: parent
            color: HusTheme.isDark ? '#181818' : '#f5f5f5'
            opacity: 0.2
        }


        // 路由
        QtObject {
            id: betterClipboardRouter
            property var urlDataMap: new Map

            signal sourceChanged(string source)

            function push(source)
            {
                sourceChanged(source)
            }
        }

        // // 左侧

        // 作者卡片
        Rectangle {
            id: authorCard
            width: visible ? mainMenu.defaultMenuWidth : 0
            height: visible ? 80 : 0
            anchors.top: parent.top
            anchors.topMargin: 3
            radius: HusTheme.Primary.radiusPrimary

            color: hovered ? HusTheme.isDark ? '#10ffffff' : '#10000000' : 'transparent'
            visible: mainMenu.compactMode === HusMenu.Mode_Relaxed
            clip: true

            property bool hovered: authorCardHover.hovered

            Item {
                height: parent.height
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 5
                anchors.rightMargin: 5

                HusAvatar {
                    id: avatarIcon
                    size: 60
                    anchors.verticalCenter: parent.verticalCenter
                    imageSource: Qt.resolvedUrl("images/header.jpg")
                }

                Column {
                    anchors.left: avatarIcon.right
                    anchors.leftMargin: 10
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter

                    spacing: 4

                    HusText {
                        text: "愿应怜为淇"
                        font.weight: Font.DemiBold
                        font.italic: true
                        font.pixelSize: HusTheme.Primary.fontPrimarySize + 1
                    }

                    HusText {
                        text: "2640883708@qq.com"
                        font.pixelSize: HusTheme.Primary.fontPrimarySize - 1
                        color: HusTheme.Primary.colorTextSecondary
                    }

                    HusText {
                        width: parent.width
                        text: "https://github.com/yylwq/BetterClipBoard"
                        font.pixelSize: HusTheme.Primary.fontPrimarySize - 1
                        color: HusTheme.Primary.colorTextSecondary
                        wrapMode: HusText.WrapAnywhere
                    }
                }
            }

            HoverHandler {
                id: authorCardHover
            }

            TapHandler {
                onTapped: {
                    Qt.openUrlExternally("https://github.com/yylwq/BetterClipBoard")
                }
            }
        }
        // 菜单
        HusMenu {
            id: mainMenu
            anchors.left: parent.left
            anchors.top: authorCard.bottom
            anchors.bottom: parent.bottom
            defaultMenuWidth: 300
            defaultSelectedKeys: ["recentPage"]
            compactMode: HusMenu.Mode_Relaxed
            showEdge: true
            initModel: global.betterCBMenuModel

            property var model: parent.model
            property var menuButton: parent.menuButton

            menuLabelDelegate: HusText {
                text: menuButton.text
                font: menuButton.font
                color: menuButton.colorText
                elide: Text.ElideRight
            }

            menuBgDelegate: Rectangle {
                radius: menuButton.radiusBg.all
                color: menuButton.colorBg
                border.color: menuButton.borderBg.color
                border.width: 1
            }

            onClickMenu: function(deep, key, keyPath, data)
            {
                if (!data)
                {
                    return;
                }

                if (data.hasOwnProperty('menuChildren') && data.menuChildren.length > 0)
                {
                    setDataProperty(key, 'badgeState', '');
                } else {
                    betterClipboardRouter.urlDataMap.set(data.key, data);
                    betterClipboardRouter.push(data.key);
                }
            }
        }

        Loader{
            id: pageLoader
            anchors.left: mainMenu.right
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            anchors.leftMargin: 5
            anchors.topMargin: 5
            anchors.bottomMargin: 5
            anchors.rightMargin: 5

            function loadBySource(source)
            {
                switch (source)
                {
                case "recentPage":
                    pageLoader.setSource(Qt.resolvedUrl("Home/RecentPage.qml"));
                    break;
                case "historyPage":
                    pageLoader.setSource(Qt.resolvedUrl("Home/HistoryPage.qml"));
                    break;
                case "favoritePage":
                    pageLoader.setSource(Qt.resolvedUrl("Home/FavoritePage.qml"));
                    break;
                default:
                    console.warn("Unknown source:", source);
                }
            }
        }

        Connections {
            target: betterClipboardRouter
            function onSourceChanged(source)
            {
                pageLoader.loadBySource(source)
            }
        }
    }
}
