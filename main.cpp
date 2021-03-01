#include <QApplication>

#include "includes/main_window.hpp"
#include "includes/image.hpp"

int main(int argv, char **args) {
    QApplication app(argv, args);

    MainWindow main_window;
    main_window.show();

    return app.exec();
}
