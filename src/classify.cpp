#include "./include/classify.h"

Classify::Classify(QObject *parent)
    : QObject{parent}
{}

DataType Classify::classify(QString &text)
{
    return DataType::Text;
}


