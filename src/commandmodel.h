#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include <QDomDocument>
#include <QProcess>
#include <QStandardItemModel>
#include <QFile>
#include <QStandardItem>
#include <QList>
#include <QVariant>

class CommandModel : public QStandardItemModel {

    Q_OBJECT

    public:
        CommandModel(QObject *parent = 0);
        //QHash<int, QByteArray> roleNames();

    public slots:
        QString getName();
        QString getVersion();

    signals:
        void populated();

    private slots:
        void startProcess();
        void getXmlCommandList(int code);
        void processXml();

    private:
        void symfonyInformations(QDomElement symfony);

        QProcess *process;
        QDomDocument *dom;
        QString name, version;
};

#endif // COMMANDLIST_H
