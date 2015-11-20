#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QMessageBox>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Localization stuff
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
        QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    if (!app.installTranslator(&qtTranslator))
        QMessageBox::warning(0, "Warning", "Unable to load Qt translation for the " + QLocale::system().name() + " locale");

    QTranslator myappTranslator;
    if (!myappTranslator.load("example_" + QLocale::system().name()))
        QMessageBox::warning(0, "Warning", "Unable to load application translation for the " + QLocale::system().name() + " locale");
    app.installTranslator(&myappTranslator);

    // Retina display support for Mac OS, iOS and X11:
    // http://blog.qt.digia.com/blog/2013/04/25/retina-display-support-for-mac-os-ios-and-x11/
    //
    // AA_UseHighDpiPixmaps attribute is off by default in Qt 5.1 but will most
    // likely be on by default in a future release of Qt.
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

    QIcon appIcon;
    appIcon.addFile(":/Icons/AppIcon32");
    appIcon.addFile(":/Icons/AppIcon128");
    app.setWindowIcon(appIcon);

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
