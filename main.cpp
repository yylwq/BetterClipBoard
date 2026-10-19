#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDateTime>
#include <QObject>
#include <QQmlEngine>
#include <QQmlContext>

#include "include/const.h"
#include "include/classify.h"
#include "include/data.h"
#include "include/listener.h"
#include "include/database.h"

#include "include/DataModel/datamodel.h"
#include "include/DataModel/recentdatamodel.h"
#include "include/DataModel/emaildatamodel.h"
#include "include/DataModel/textdatamodel.h"
#include "include/DataModel/urldatamodel.h"
#include "include/DataModel/favoritedatamodel.h"
#include "include/DataModel/magneticseeddatamodel.h"
#include "include/DataModel/codedatamodel.h"

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

    Listener listener;
    listener.start();

    DataBase database;
    DataModel* recent_model = new RecentDataModel(&database);
    DataModel* favorite_model = new FavoriteDataModel(&database);
    DataModel* text_model = new TextDataModel(&database);
    DataModel* email_model = new EmailDataModel(&database);
    DataModel* url_model = new UrlDataModel(&database);
    DataModel* code_model = new CodeDataModel(&database);
    DataModel* magneticseed_model = new MagneticSeedDataModel(&database);

    engine.rootContext()->setContextProperty("recentDataModel", recent_model);
    engine.rootContext()->setContextProperty("favoriteDataModel", favorite_model);
    engine.rootContext()->setContextProperty("textDataModel", text_model);
    engine.rootContext()->setContextProperty("emailDataModel", email_model);
    engine.rootContext()->setContextProperty("urlDataModel", url_model);
    engine.rootContext()->setContextProperty("codeDataModel", code_model);
    engine.rootContext()->setContextProperty("magneticseedDataModel", magneticseed_model);

    QObject::connect(&listener, &Listener::textCopied, [&](const QString &text){
        Data data;
        data.text_ = text;
        data.favorite = false;
        data.image_ = QImage();
        data.timestamp_ = QDateTime::currentDateTime();
        data.type_ = Classify::classify(data.text_);
        data.tag_ = getTag(data.type_);

        qDebug() << "[CREATE] "<<"[" << data.timestamp_.toString(Qt::ISODate) << "] " << "捕获到文本: " << text << " 类型：" << data.typeToString();

        database.insertData(data);
    });

    return QGuiApplication::exec();
}
