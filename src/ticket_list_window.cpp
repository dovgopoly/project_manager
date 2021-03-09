#include <QVBoxLayout>
#include <QListView>
#include <QTimer>

#include "../includes/ticket_list_window.hpp"
#include "../includes/config.hpp"
#include "../includes/ticket_edit_window.hpp"
#include "../includes/header.hpp"

TicketListWindow::TicketListWindow(Stack &stack, QWidget *parent)
    : AbstractWindow{stack, parent}
    , m_project_icon_view{new QListView{this}}
    , m_project_icon_delegate{new ProjectIconDelegate{this}}
    , m_ticket_view{new QListView{this}}
    , m_ticket_delegate{new TicketDelegate{this}}
    , m_ticket_model{new TicketModel{this}} {

    Initialize();
}

void TicketListWindow::SetupProjectModel(ProjectModel *project_model) {
    m_project_icon_view->setModel(project_model);
    m_project_icon_view->setItemDelegate(m_project_icon_delegate);
    ShowTicketsForChosenProject(
        qvariant_cast<QModelIndex>(project_model->data(QModelIndex{}, ProjectModel::ChosenProjectRole)));
}

void TicketListWindow::Initialize() {
    using namespace config;
    using namespace config::ticket_list_window;

    SetStyleSheet(STYLESHEET_PATH);
    m_project_icon_view->setObjectName("ProjectView");
    m_ticket_view->setObjectName("TicketView");

    auto *const main_layout = new QHBoxLayout{this};
    main_layout->setContentsMargins(ZERO_MARGINS);
    main_layout->setSpacing(ZERO_SPACING);

    m_project_icon_view->setFrameStyle(QFrame::NoFrame);
    m_project_icon_view->setFixedWidth(70);

    m_ticket_view->setItemDelegate(m_ticket_delegate);
    m_ticket_view->setModel(m_ticket_model);

    m_ticket_view->setFrameStyle(QFrame::NoFrame);
    m_ticket_view->setSpacing(15);
    m_ticket_view->setFixedWidth(600);


    main_layout->addWidget(m_project_icon_view);
    main_layout->addWidget(m_ticket_view);
    main_layout->setAlignment(Qt::AlignLeft);

    connect(m_project_icon_view, &QListView::clicked, this, &TicketListWindow::ShowTicketsForChosenProject);
    connect(m_project_icon_view, &QListView::clicked, this, [=](const QModelIndex &index) {
        m_project_icon_view->model()->setData(QModelIndex{}, index, ProjectModel::ChosenProjectRole);
        m_project_icon_view->viewport()->update();
    });
    connect(m_ticket_view, &QListView::clicked, this, [=](const QModelIndex &index) {
        m_ticket_model->setData(QModelIndex{}, index, TicketModel::ChosenTicketRole);
        auto *const ticket_edit_window = new TicketEditWindow(GetStack(), parentWidget());
        ticket_edit_window->SetupTicketsModel(m_ticket_model);
        ticket_edit_window->PutSelfToStack();
    });
}

int TicketListWindow::GetHeaderFlags() const {
    return Header::ShowHeader | Header::ShowTitle | Header::ShowBackArrow;
}

QString TicketListWindow::GetHeaderTitle() const {
    using namespace config::ticket_list_window;
    return HEADER_TITLE;
}

void TicketListWindow::ShowTicketsForChosenProject(const QModelIndex &index) {
    m_ticket_model->LoadTicketsForProject(index.row());
}
