#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include <QDomDocument>
#include <QProcess>
#include <QStandardItemModel>
#include <QFile>
#include <QStandardItem>
#include <QDir>
#include <QXmlSimpleReader>
#include <QMap>
#include <QMapIterator>

class CommandModel : public QStandardItemModel {

    Q_OBJECT

    public:
        CommandModel(QString workingDirectory, QString consolePath, QObject *parent = 0);
        QHash<int, QByteArray> roleNames() const;
        /**
         * @brief Add paramters.
         *
         * If one of the parameters already exists, it will be overwritten.
         *
         * @param params
         */
        void addParameters(QMap<QString, QString> params);

    public slots:
        void writeCommand(QString text);
        QString getCompleteDescription(int row);
        /**
         * @brief Run a command that is present in the model (i.e: obtained with the "list" command).
         * @param command
         * @param params
         */
        void runCommand(int command, QString params);
        /**
         * @brief Allow to run a completly arbitrary command.
         * @param prog
         * @param cmd
         * @param params
         */
        void runCustomCommand(QString prog, QString cmd, QString params);
        void startProcess();
        QString getName();
        QString getVersion();

    signals:
        /**
         * @brief Emitted when the model has been populated.
         */
        void populated();
        /**
         * @brief Emitted when the requested command has been excuted.
         */
        void completed();
        /**
         * @brief Request the displaying of the message in the QML context.
         * @param type The message type.
         * @param text The text of the message.
         */
        void print(int type, QString text);

    private slots:
        void readCommand();
        void commandCompleted(int code);
        void getXmlCommandList(int code);
        void processXml();

    private:
        QVariant data(const QModelIndex &index, int role) const;
        void symfonyInformations(QDomElement symfony);
        QString convertXmlTextStyle(QString text);
        QString convertAnsiTextStyle(QString text);

        QProcess *process, *cmd;
        QDomDocument *dom;
        /**
         * @brief Store the parameters.
         */
        QMap<QString, QString> parameters;
};

#endif // COMMANDLIST_H
