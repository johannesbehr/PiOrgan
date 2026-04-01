#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <piorganInterface.h>
#include <QQmlContext>
#include <QtWidgets>
#include <iostream>
#include <cstdlib>

#include <QDBusInterface>
#include <QDBusReply>

#include <linux/uinput.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#include "virtualKeyboard.h"

VirtualKeyboard vk;

void resetScreenSaver()
{
    static QElapsedTimer last;
    if (!last.isValid() || last.elapsed() > 5000) {
        vk.sendShiftTap();
        qDebug() << "Reset via virtual keyboard";
        last.restart();
    }
}


PiOrganInterface piorgan;  // A class containing my functions

bool locked = false;

int main(int argc, char *argv[])
{

    if(vk.init()){
        qDebug() << "Virtual Keyboard created";
    }else{
        qDebug() << "Error creating Virtual Keyboard";
    }
    locked = true;
    piorgan.setEventsEnabled(false);

    piorgan.setResetScreenSaver(resetScreenSaver);
    /*
    const char* display = std::getenv("DISPLAY");
    if (display == nullptr) {
        std::cout << "Die Umgebungsvariable existiert nicht." << std::endl;
        if (setenv("DISPLAY", ":0.0", 1) != 0) {
            std::cerr << "Fehler beim Setzen der Umgebungsvariable." << std::endl;
            return 1;
        }
    }*/

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/untitled6/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    QScreen *targetScreen = nullptr;

    const QList<QScreen*> screens = QGuiApplication::screens();


    for (QScreen *screen : screens) {
    qDebug() << screen->name() << screen->geometry();
        if (screen->name() == "DSI-2") {
            targetScreen = screen;
            //break;
        }
    }

    if (!targetScreen) {
        targetScreen = QGuiApplication::primaryScreen();
    }

    QSize screenSize = targetScreen->size();
    int screenWidth = screenSize.width();
    int screenHeight = screenSize.height();
    
    engine.rootContext()->setContextProperty("screenWidth",screenWidth);
    engine.rootContext()->setContextProperty("screenHeight",screenHeight);
    engine.rootContext()->setContextProperty("_myClass", &piorgan);


    engine.load(url);

    QObject *rootObject = engine.rootObjects().first();
    QWindow *window = qobject_cast<QWindow *>(rootObject);
    window->setScreen(targetScreen);
    window->setPosition(targetScreen->geometry().topLeft());
    
    piorgan.setRootObject(rootObject);

    locked = false;
    piorgan.setEventsEnabled(true);

    return app.exec();
}


