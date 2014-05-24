#include "commandmodel.h"

CommandModel::CommandModel(QString workingDirectory, QString consolePath, QObject *parent) :
    QStandardItemModel(parent) {

    process = new QProcess(this);
    cmd = new QProcess(this);
    cmd->setProcessChannelMode(QProcess::MergedChannels);
    dom = new QDomDocument();
    name = version = "";
    workDir = workingDirectory;
    console = consolePath;
    QDir::setCurrent(workDir);


    connect(process, SIGNAL(finished(int)), this, SLOT(getXmlCommandList(int)));
    connect(cmd, SIGNAL(finished(int)), this, SLOT(commandCompleted(int)));
    connect(cmd, SIGNAL(readyRead()), this, SLOT(readCommand()));
}

QHash<int, QByteArray> CommandModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[Qt::UserRole] = "name";
    roles[Qt::UserRole+1] = "description";

    return roles;
}

QVariant CommandModel::data(const QModelIndex &index, int role) const {
    switch (role) {
        case Qt::UserRole:
            return QVariant(this->item(index.row(), 0)->text());
        break;
        case Qt::UserRole+1:
            return QVariant(this->item(index.row(), 1)->text());
        break;
        default:
            return QVariant();
        break;
    }
}

QString CommandModel::getCompleteDescription(int row) {
    return this->item(row, 2)->text();
}

void CommandModel::runCommand(int command, QString parameters) {
    cmd->start("php", QStringList() << console << this->item(command, 0)->text() << parameters << "--ansi");
    emit print(1, QString("Run: "+this->item(command, 0)->text()+" "+parameters+" --ansi"));
}

void CommandModel::readCommand() {
    emit print(0, this->convertAnsiTextStyle(cmd->readAll()));
}

void CommandModel::writeCommand(QString text) {
    cmd->write(QString(text+"\n").toStdString().c_str());
}

void CommandModel::commandCompleted(int code) {
    Q_UNUSED(code);

    emit print(0, this->convertAnsiTextStyle(cmd->readAll()));
    emit print(2, "Completed");
    emit completed();
}

void CommandModel::startProcess() {
    process->start("php", QStringList() << console << "list" << "--format=xml");
}

void CommandModel::getXmlCommandList(int code) {
    Q_UNUSED(code);

    dom->setContent(process->readAll());

    this->processXml();
}

void CommandModel::processXml() {
    QDomElement symfony = dom->namedItem("symfony").toElement();
    this->symfonyInformations(symfony);

    QDomElement cmd = symfony.firstChildElement("commands").firstChildElement("command");

    for( ; !cmd.isNull(); cmd = cmd.nextSiblingElement("command") ) {
        QList<QStandardItem*> command;

        if(cmd.hasAttribute("id")) {
            command << new QStandardItem(cmd.attribute("id"));
        }

        command << new QStandardItem(cmd.firstChildElement("description").text());
        command << new QStandardItem(this->convertXmlTextStyle(cmd.firstChildElement("help").text()));
        this->appendRow(command);
    }

    emit populated();
}

QString CommandModel::convertXmlTextStyle(QString text) {
    text.replace("<comment>", "<span style=\"color: #004DD1\">");
    text.replace("</comment>", "</span>");
    text.replace("<info>", "<span style=\"color: #919191; font-style:italic;\">");
    text.replace("</info>", "</span>");
    text.replace(QRegExp("\n"), "<br/>");

    return text;
}

QString CommandModel::convertAnsiTextStyle(QString text) {
    text.replace("[32m", "<span style=\"color: #3BCF00\">");
    text.replace("[33m", "<span style=\"color: #009AD6\">");
    text.replace("[39m", "</span>");
    text.replace(QRegExp("\n"), "<br/>");
    text.replace(QRegExp("\t"), "!");

    return text;
}

void CommandModel::symfonyInformations(QDomElement symfony) {
    if(symfony.hasAttribute("name")) {
        name = symfony.attribute("name");
    }
    if(symfony.hasAttribute("version")) {
        version = symfony.attribute("version");
    }
}

QString CommandModel::getName() {
    return name;
}

QString CommandModel::getVersion() {
    return version;
}
