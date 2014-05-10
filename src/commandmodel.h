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
        CommandModel(QString workingDirectory, QString consolePath, QObject *parent = 0);
        QHash<int, QByteArray> roleNames() const;

    public slots:
        QString getName();
        QString getVersion();
        QString getCompleteDescription(int row);
        void runCommand(int command, QString parameters);
        void startProcess();

    signals:
        void populated();

    private slots:
        void getXmlCommandList(int code);
        void processXml();

    private:
        void symfonyInformations(QDomElement symfony);
        QVariant data(const QModelIndex &index, int role) const;
        QString convertTextStyle(QString text);

        QProcess *process;
        QDomDocument *dom;
        QString name, version, workDir, console;
};

#endif // COMMANDLIST_H
