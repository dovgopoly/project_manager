#include <QGraphicsDropShadowEffect>
#include "../includes/main_window.hpp"
#include "../includes/config.hpp"
#include "../includes/project_list_window.hpp"
#include "../includes/header.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
    , m_stack{new Stack}
    , m_header{new Header{this}} {

    Initialize();
}

void MainWindow::Initialize() {
    using namespace config;
    using namespace config::main_window;

    setMinimumSize(MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT);
    setWindowIcon(QIcon{LOGOTYPE_PATH});
    setWindowTitle(WINDOW_TITLE);

    auto *const main_layout = new QVBoxLayout{this};
    main_layout->setSpacing(ZERO_SPACING);
    main_layout->setContentsMargins(ZERO_MARGINS);
    main_layout->addWidget(m_header);
    main_layout->addLayout(m_stack);
    connect(m_stack, &Stack::CurrentWidgetChanged, this, &MainWindow::SetupWindow);
    connect(m_header->m_back_arrow_icon, &Image::Clicked, m_stack, &Stack::Pop);

    auto *const login_window = new LoginWindow{*m_stack};
    login_window->PutSelfToStack();
}

void MainWindow::SetupWindow(AbstractWindow *current_top_window) {
    SetupHeader(current_top_window);
}

void MainWindow::SetupHeader(AbstractWindow *current_top_window) {
    m_header->SetProperties(current_top_window->GetHeaderFlags());
    m_header->SetTitle(current_top_window->GetHeaderTitle());
}
