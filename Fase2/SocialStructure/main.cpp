#include "login.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int id = QFontDatabase::addApplicationFont(":/new/prefix1/fonts/BurbankSmall-Medium.otf");
    if (id != -1) {
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        QFont miFuentePersonalizada(family);
        a.setFont(miFuentePersonalizada);  // se establece la fuente para toda la aplicación
    }
    Login w;
    w.show();
    return a.exec();
}
