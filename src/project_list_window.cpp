#include <QLabel>
#include <QHBoxLayout>

#include "../includes/project_list_window.hpp"
#include "../includes/config.hpp"
#include "../includes/ticket_list_window.hpp"
#include "../includes/header.hpp"

#include "../other/waiting_spinner/waiting_spinner_widget.h"

ProjectListWindow::ProjectListWindow(Stack &stack, QWidget *parent)
    : AbstractWindow{stack, parent}
    , m_project_list_view{new QListView{this}}
    , m_project_model{new ProjectModel{this}}
    , m_project_delegate{new ProjectDelegate{this}} {

    Initialize();
}

void ProjectListWindow::Initialize() {
    using namespace config;
    using namespace config::project_list_window;

    SetStyleSheet(STYLESHEET_PATH);

    auto *const waiting_spinner = new WaitingSpinnerWidget{this, true, false};
    waiting_spinner->start();

    m_project_list_view->setSpacing(PROJECT_LIST_VIEW_SPACING);
    m_project_list_view->setFrameStyle(QFrame::NoFrame);

    m_project_list_view->setModel(m_project_model);
    m_project_list_view->setItemDelegate(m_project_delegate);

    auto *const main_layout = new QVBoxLayout{this};
    main_layout->setSpacing(ZERO_SPACING);
    main_layout->setContentsMargins(ZERO_MARGINS);
    main_layout->addWidget(m_project_list_view);

    connect(m_project_list_view, &QListView::doubleClicked, this, &ProjectListWindow::ProjectDoubleClicked);
    connect(m_project_model, &ProjectModel::UpdatingBegin, waiting_spinner, &WaitingSpinnerWidget::start);
    connect(m_project_model, &ProjectModel::UpdatingEnd, waiting_spinner, &WaitingSpinnerWidget::stop);
    connect(m_project_list_view, &QListView::clicked, this, &ProjectListWindow::ProjectClicked);
}

int ProjectListWindow::GetHeaderFlags() const {
    return Header::ShowHeader | Header::ShowTitle | Header::ShowBackArrow;
}

QString ProjectListWindow::GetHeaderTitle() const {
    using namespace config::project_list_window;
    return HEADER_TITLE;
}

void ProjectListWindow::ProjectClicked(const QModelIndex &index) {
    m_project_model->setData(QModelIndex{}, index, ProjectModel::ChosenProjectRole);
    m_project_list_view->viewport()->update();
}

void ProjectListWindow::ProjectDoubleClicked(const QModelIndex &index) {
    auto *const ticket_list_window = new TicketListWindow(GetStack(), parentWidget());
    ticket_list_window->SetupProjectModel(m_project_model);
    ticket_list_window->PutSelfToStack();
}
