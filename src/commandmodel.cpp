#include "commandmodel.h"

CommandModel::CommandModel(QObject *parent) :
    QStandardItemModel(parent) {

    process = new QProcess(this);
    dom = new QDomDocument();
    name = version = "";

    connect(process, SIGNAL(finished(int)), this, SLOT(getXmlCommandList(int)));

    this->startProcess();
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

QString CommandModel::convertTextStyle(QString text) {
    //qDebug(QString("Command : " + cmd.attribute("id")).toStdString().c_str());
    text.replace("<comment>", "<span style=\"color: #004DD1\">");
    text.replace("</comment>", "</span>");
    text.replace("<info>", "<span style=\"color: #919191; font-style:italic;\">");
    text.replace("</info>", "</span>");
    text.replace(QRegExp("\n"), "<br/>");

    return text;
}

QString CommandModel::getName() {
    return name;
}

QString CommandModel::getVersion() {
    return version;
}

QString CommandModel::getCompleteDescription(int row) {
    return this->item(row, 2)->text();
}

void CommandModel::runCommand(int command, QString parameters) {
    qDebug(QString("Run: "+this->item(command, 0)->text()+" "+parameters).toStdString().c_str());
}

void CommandModel::startProcess() {
    process->start("php", QStringList() << "C:/wamp/www/SWTOR/app/console" << "list" << "--format=xml");
}

void CommandModel::getXmlCommandList(int code) {
    dom->setContent(process->readAll());

    this->processXml();
}

void CommandModel::processXml() {
    //qDebug(QString("Command : " + cmd.attribute("id")).toStdString().c_str());
    QDomElement symfony = dom->namedItem("symfony").toElement();
    this->symfonyInformations(symfony);

    QDomElement cmd = symfony.firstChildElement("commands").firstChildElement("command");

    for( ; !cmd.isNull(); cmd = cmd.nextSiblingElement("command") ) {
        QList<QStandardItem*> command;

        if(cmd.hasAttribute("id")) {
            command << new QStandardItem(cmd.attribute("id"));
        }

        command << new QStandardItem(cmd.firstChildElement("description").text());
        command << new QStandardItem(this->convertTextStyle(cmd.firstChildElement("help").text()));
        this->appendRow(command);
    }

    emit populated();
}

void CommandModel::symfonyInformations(QDomElement symfony) {
    if(symfony.hasAttribute("name")) {
        name = symfony.attribute("name");
    }
    if(symfony.hasAttribute("version")) {
        version = symfony.attribute("version");
    }
}
