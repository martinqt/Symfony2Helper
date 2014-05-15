#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include <QDomDocument>
#include <QProcess>
#include <QStandardItemModel>
#include <QFile>
#include <QStandardItem>
#include <QDir>

class CommandModel : public QStandardItemModel {

    Q_OBJECT

    public:
        CommandModel(QString workingDirectory, QString consolePath, QObject *parent = 0);
        QHash<int, QByteArray> roleNames() const;

    public slots:
        QString getCompleteDescription(int row);
        void runCommand(int cmd, QString parameters);
        void startProcess();
        QString getName();
        QString getVersion();

    signals:
        void populated();
        void completed();
        void print(int type, QString text);

    private slots:
        void commandCompleted(int code);
        void getXmlCommandList(int code);
        void processXml();

    private:
        QVariant data(const QModelIndex &index, int role) const;
        void symfonyInformations(QDomElement symfony);
        QString convertXmlTextStyle(QString text);
        QString convertAnsiTextStyle(QString text);

        QProcess *process;
        QProcess *cmd;
        QDomDocument *dom;
        QString name, version, workDir, console;
};

#endif // COMMANDLIST_H
