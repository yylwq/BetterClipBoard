#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>
#include <QClipboard>

#include "const.h"

class Listener : public QObject
{
    Q_OBJECT
public:
    explicit Listener(QObject *parent = nullptr);
    ~Listener();

    void start();
    void close();

public slots:
    void listened();

private:
    bool is_listen;

    QString last_text;
    QImage last_image;

signals:
    void imageCopied(QImage image);
    void textCopied(QString text);
};

#endif // LISTENER_H
