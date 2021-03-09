#include <QApplication>

#include "includes/main_window.hpp"

int main(int argv, char **args) {
    QApplication application(argv, args);

    MainWindow main_window;
    main_window.show();

    return QApplication::exec();
}
