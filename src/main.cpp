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

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("commandModel",list);
    engine.load(QUrl("qrc:/main.qml"));

    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    window->show();

    return app.exec();
}
