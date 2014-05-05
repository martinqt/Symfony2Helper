#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtCore/QString>
#include <QtGui/QGuiApplication>
#include "commandmodel.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QEventLoop loop;
    CommandModel *list = new CommandModel();
    QObject::connect(list, SIGNAL(populated()), &loop, SLOT(quit()));
    loop.exec();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("commandModel",list);

    engine.load(QUrl("qrc:/main.qml"));
    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    if(!window) {
        qWarning("Error: Your root item has to be a Window.");
        return -1;
    }

    window->show();

    return app.exec();
}
