#include "commandmodel.h"

CommandModel::CommandModel(QObject *parent) :
    QStandardItemModel(parent) {

    /*QHash<int, QByteArray> roles;

    roles[Qt::UserRole + 0] = "name";
    roles[Qt::UserRole + 1] = "description";

    setItemRoleNames(roles);*/

    process = new QProcess(this);
    dom = new QDomDocument();
    name = version = "";

    connect(process, SIGNAL(finished(int)), this, SLOT(getXmlCommandList(int)));

    this->startProcess();
}

QString CommandModel::getName() {
    return name;
}

QString CommandModel::getVersion() {
    return version;
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
    qDebug("process");
    QDomElement symfony = dom->namedItem("symfony").toElement();
    this->symfonyInformations(symfony);

    QDomElement cmd = symfony.firstChildElement("commands").firstChildElement("command");

    for( ; !cmd.isNull(); cmd = cmd.nextSiblingElement("command") ) {
        QList<QStandardItem*> command;

        if(cmd.hasAttribute("id")) {
            command << new QStandardItem(cmd.attribute("id"));
        }

        QDomElement desc = cmd.firstChildElement("description");
        command << new QStandardItem(desc.text());
        this->appendRow(command);
    }

    qDebug("end process");
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
