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
    qDebug("here");
    QHash<int, QByteArray> roles;

    roles[Qt::UserRole] = "name";
    roles[Qt::UserRole+1] = "description";

    return roles;
}

QVariant CommandModel::data(const QModelIndex &index, int role) const {
    qDebug("there");
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
