#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDateTime>
#include <QObject>
#include <QQmlEngine>
#include <QQmlContext>
#include <QPoint>

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

#include "include/DataModel/favoriteDataModel/codeFavoriteDataModel.hpp"
#include "include/DataModel/favoriteDataModel/emailFavoriteDataModel.hpp"
#include "include/DataModel/favoriteDataModel/magneticseedFavoriteDataModel.hpp"
#include "include/DataModel/favoriteDataModel/textFavoriteDataModel.hpp"
#include "include/DataModel/favoriteDataModel/urlFavoriteDataModel.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    DataBase database;

    Listener listener;
    listener.start();

    engine.rootContext()->setContextProperty("database", &database);
    engine.rootContext()->setContextProperty("listener", &listener);

    DataModel* recent_model = new RecentDataModel(&database, &engine);
    // DataModel* favorite_model = new FavoriteDataModel(&database, &engine);
    DataModel* text_model = new TextDataModel(&database, &engine);
    DataModel* email_model = new EmailDataModel(&database, &engine);
    DataModel* url_model = new UrlDataModel(&database, &engine);
    DataModel* code_model = new CodeDataModel(&database, &engine);
    DataModel* magneticseed_model = new MagneticSeedDataModel(&database, &engine);

    engine.rootContext()->setContextProperty("recentDataModel", recent_model);
    // engine.rootContext()->setContextProperty("favoriteDataModel", favorite_model);
    engine.rootContext()->setContextProperty("textDataModel", text_model);
    engine.rootContext()->setContextProperty("emailDataModel", email_model);
    engine.rootContext()->setContextProperty("urlDataModel", url_model);
    engine.rootContext()->setContextProperty("codeDataModel", code_model);
    engine.rootContext()->setContextProperty("magneticseedDataModel", magneticseed_model);

    DataModel* all_favorite_model = new FavoriteDataModel(&database, &engine);
    DataModel* text_favorite_model = new TextFavoriteDataModel(&database, &engine);
    DataModel* email_favorite_model = new EmailFavoriteDataModel(&database, &engine);
    DataModel* url_favorite_model = new UrlFavoriteDataModel(&database, &engine);
    DataModel* code_favorite_model = new CodeFavoriteDataModel(&database, &engine);
    DataModel* magneticseed_favorite_model = new MagneticSeedFavoriteDataModel(&database, &engine);

    engine.rootContext()->setContextProperty("allFavoriteDataModel", all_favorite_model);
    engine.rootContext()->setContextProperty("textFavoriteDataModel", text_favorite_model);
    engine.rootContext()->setContextProperty("emailFavoriteDataModel", email_favorite_model);
    engine.rootContext()->setContextProperty("urlFavoriteDataModel", url_favorite_model);
    engine.rootContext()->setContextProperty("codeFavoriteDataModel", code_favorite_model);
    engine.rootContext()->setContextProperty("magneticseedFavoriteDataModel", magneticseed_favorite_model);

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
