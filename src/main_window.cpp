#include "../includes/main_window.hpp"
#include "../includes/config.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
    , m_stack{new QStackedLayout{this}} {

    Initialize();
}

void MainWindow::Initialize() {
    using namespace config;

    setMinimumSize(MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT);
    setWindowIcon(QIcon{LOGOTYPE_PATH});
    setWindowTitle(WINDOW_TITLE);
    new LoginWindow{*m_stack, this};
}
