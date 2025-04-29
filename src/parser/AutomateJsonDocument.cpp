#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QString>
#include <QMap>
#include <QDebug>

class AutomateJsonDocument
{
public:
    bool loadAutomateFromJsonFile(const QString &fileName)
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning() << "Error in opening file !" << fileName;
            return false;
        }

        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isNull())
        {
            qWarning() << "Failed loading json.";
            return false;
        }

        QJsonObject jsonObj = doc.object();

        // QJsonObject statesObj = jsonObj["states"].toObject();

        return true;
    }
};
