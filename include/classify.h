#ifndef CLASSIFY_H
#define CLASSIFY_H

#include <QObject>

#include "const.h"
#include "listener.h"
#include "data.h"

class Classify : public QObject
{
    Q_OBJECT
public:
    explicit Classify(QObject *parent = nullptr);

    static DataType classify(QString &text);
    static DataType classify(QImage &image);

private:
    static bool isCode(QString &text);
    static bool isEmail(QString &text);
    static bool isUrl(QString &text);
    static bool isMagneticSeed(QString &text);
};

#endif // CLASSIFY_H
