#include "./include/listener.h"

#include <QGuiApplication>

Listener::Listener(QObject *parent)
    : QObject{parent}
{
    connect(QGuiApplication::clipboard(), &QClipboard::dataChanged, this, &Listener::listened);
}

Listener::~Listener()
{
    close();
}

void Listener::start()
{
    is_listen = true;
}

void Listener::close()
{
    is_listen = false;
}

void Listener::listened()
{
    if (!is_listen)
        return;

    const QClipboard *clipboard = QGuiApplication::clipboard();

    if (clipboard->ownsClipboard())
    {
        qDebug() << "未检测到数据！";
        return;
    }

    QString copy_text = clipboard->text();

    if (copy_text != last_text)
    {
        qDebug() << "[监听器] 捕获到文本: " << copy_text;
        last_text = copy_text;

        emit textCopied(copy_text);

        return;
    }

    QImage copy_image = clipboard->image();
    if (copy_image != last_image)
    {
        qDebug() << "[监听器] 捕获到图片 ";
        last_image = copy_image;

        emit imageCopied(copy_image);
    }
}
