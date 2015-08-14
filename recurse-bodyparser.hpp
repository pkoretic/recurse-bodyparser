#ifndef RECURSE_BODYPARSER_HPP
#define RECURSE_BODYPARSER_HPP

#include <QJsonDocument>
#include <QJsonObject>

auto bodyparser()
{
    return [](auto &ctx, auto next) {
        auto &req = ctx.request;

        if (req.body.isEmpty())
            return next();

        if (req.header["content-type"] == "application/json") {
            QJsonDocument json = QJsonDocument::fromJson(req.body.toUtf8());
            const QVariantMap map = json.object().toVariantMap();
            QMap<QString, QVariant>::const_iterator i;

            for (i = map.constBegin(); i != map.constEnd(); ++i) {
                req.body_parsed[i.key()] = i.value();
            }
        }
        else if (req.header["content-type"] == "application/x-www-form-urlencoded") {
        }

        next();
    };
}

#endif // RECURSE_BODYPARSER_HPP
