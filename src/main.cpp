#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtCore/QString>
#include <QtGui/QGuiApplication>
#include "commandmodel.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QEventLoop loop;
    CommandModel *list = new CommandModel();
    // TODO: not the best way but as of now, it will do.
    QObject::connect(list, SIGNAL(populated()), &loop, SLOT(quit()));
    loop.exec();

    //qDebug(list->item(0,1)->text().toStdString().c_str());
    /*QHash<int, QByteArray> roles = list->roleNames();
    QHashIterator<int, QByteArray> i(roles);
    while (i.hasNext()) {
        i.next();
        qDebug(i.value());
        //cout << i.key() << ": " << i.value() << endl;
    }*/

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("commandModel",list);
    engine.load(QUrl("qrc:/main.qml"));

    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    window->show();

    return app.exec();
}
