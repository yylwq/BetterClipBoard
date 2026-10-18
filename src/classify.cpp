#include "./include/classify.h"

#include <QRegularExpression>

Classify::Classify(QObject *parent)
    : QObject{parent}
{}

DataType Classify::classify(QString &text)
{
    if (isCode(text)) return DataType::Code;
    if (isEmail(text)) return DataType::Email;
    if (isUrl(text)) return DataType::Url;
    if (isMagneticSeed(text)) return DataType::MagneticSeed;

    return DataType::Text;
}

bool Classify::isCode(QString &text)
{
    bool hasSemicolon = text.contains(';');
    bool hasBraces = text.contains('{') || text.contains('}');
    bool hasNewline = text.contains('\n');
    return hasSemicolon && hasBraces && hasNewline;
}

bool Classify::isEmail(QString &text)
{
    static QRegularExpression pattern("^[\\w.+-]+@[\\w-]+\\.[\\w.-]+$");
    return pattern.match(text).hasMatch();
}

bool Classify::isUrl(QString &text)
{
    static QRegularExpression pattern("^https?://\\S+$");
    return pattern.match(text).hasMatch();
}

bool Classify::isMagneticSeed(QString &text)
{
    return text.contains("magnet:?xt=urn:btih:");
}


