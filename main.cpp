#include <QApplication>

#include "includes/main_window.hpp"
#include "includes/ticket_edit_window.hpp"

/*
 * TODO:
 *   3. Sign out button like in an example
 *   4. Shadows
 *   6. Try to do animation
 *   7. Splitter in ticket window which displays ticket's description
 *   8. Add waiting spinner
 */

int main(int argv, char **args) {
    QApplication application(argv, args);

    MainWindow main_window;
    main_window.show();

    return QApplication::exec();
}
