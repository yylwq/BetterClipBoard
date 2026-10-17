#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDateTime>
#include <QObject>

#include "include/const.h"
#include "include/classify.h"
#include "include/data.h"
#include "include/listener.h"
#include "include/const.h"
#include "include/database.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/BetterClipboard/qml/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    // Listener listener;
    // listener.start();

    // DataBase database;

    // QObject::connect(&listener, &Listener::textCopied, [&](const QString &text){
    //     Data data;
    //     data.text_ = text;
    //     data.favorite = false;
    //     data.image_ = QImage();
    //     data.timestamp_ = QDateTime::currentDateTime();
    //     data.type_ = Classify::classify(data.text_);
    //     data.tag_ = getTag(data.type_);

    //     qDebug() << "[CREATE] "<<"[" << data.timestamp_.toString(Qt::ISODate) << "] " << "捕获到文本: " << text;

    //     database.insertData(data);
    // });
    // QObject::connect(&listener, &Listener::imageCopied, &classify, &Classify::getImage);

    return QGuiApplication::exec();
}
