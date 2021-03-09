#include "../includes/ticket_edit_window.hpp"
#include "../includes/config.hpp"
#include "../includes/header.hpp"

TicketEditWindow::TicketEditWindow(Stack &stack, QWidget *parent)
    : AbstractWindow{stack, parent}
    , m_name_line_edit{new QLineEdit{this}}
    , m_description_text_edit{new QTextEdit{this}}
    , m_save_button{new QPushButton{QString{config::ticket_edit_window::SAVE_BUTTON_LABEL}.toUpper(), this}}
    , m_cancel_button{new QPushButton{config::ticket_edit_window::CANCEL_BUTTON_LABEL, this}}
    , m_up_arrow_button{new Image(config::ticket_edit_window::UP_ARROW_PATH,
                                  config::ticket_edit_window::ARROW_SPINBOX_WIDTH,
                                  config::ticket_edit_window::ARROW_SPINBOX_HEIGHT,
                                  Image::HighQuality,
                                  this)}
    , m_down_arrow_button{new Image(config::ticket_edit_window::DOWN_ARROW_PATH,
                                    config::ticket_edit_window::ARROW_SPINBOX_WIDTH,
                                    config::ticket_edit_window::ARROW_SPINBOX_HEIGHT,
                                    Image::HighQuality,
                                    this)}
    , m_priority_widget{new PriorityWidget{this}} {

    Initialize();
}

void TicketEditWindow::Initialize() {
    using namespace config;
    using namespace config::ticket_edit_window;

    SetStyleSheet(STYLESHEET_PATH);

    auto *const form_vertical_layout = new QVBoxLayout{this};
    form_vertical_layout->setContentsMargins(MAIN_LAYOUT_MARGINS);
    form_vertical_layout->setSpacing(MAIN_LAYOUT_SPACING);

    auto *const priority_spin_box_layout = new QGridLayout;
    priority_spin_box_layout->setVerticalSpacing(SPINBOX_VERTICAL_SPACING);
    priority_spin_box_layout->setHorizontalSpacing(SPINBOX_HORIZONTAL_SPACING);

    m_priority_widget->SetRadius(PRIORITY_WIDGET_RADIUS);
    m_priority_widget->SetVerticalSpacing(PRIORITY_WIDGET_VERTICAL_SPACING);

    priority_spin_box_layout->addWidget(m_priority_widget, 0, 0, 2, 1, Qt::AlignCenter);
    priority_spin_box_layout->addWidget(m_up_arrow_button, 0, 1, 1, 1, Qt::AlignBottom);
    priority_spin_box_layout->addWidget(m_down_arrow_button, 1, 1, 1, 1, Qt::AlignTop);

    auto *const name_and_priority_layout = new QHBoxLayout;

    name_and_priority_layout->addWidget(m_name_line_edit, 0, Qt::AlignLeft);
    priority_spin_box_layout->setAlignment(Qt::AlignRight);
    name_and_priority_layout->addLayout(priority_spin_box_layout);

    form_vertical_layout->addLayout(name_and_priority_layout);
    form_vertical_layout->addWidget(m_description_text_edit, 0, Qt::AlignVCenter);

    m_save_button->setObjectName(SAVE_BUTTON_LABEL);
    m_cancel_button->setObjectName(CANCEL_BUTTON_LABEL);

    auto *const buttons_layout = new QHBoxLayout;
    buttons_layout->setAlignment(Qt::AlignRight);
    buttons_layout->addWidget(m_cancel_button);
    buttons_layout->addWidget(m_save_button);
    buttons_layout->setSpacing(BUTTON_LAYOUT_SPACING);

    form_vertical_layout->addLayout(buttons_layout);
    form_vertical_layout->setAlignment(Qt::AlignCenter);

    connect(m_up_arrow_button, &Image::clicked, [=]() {
        m_priority_widget->Increment();
        m_priority_widget->update();
    });
    connect(m_down_arrow_button, &Image::clicked, [=]() {
        m_priority_widget->Decrement();
        m_priority_widget->update();
    });
    connect(m_cancel_button, &QPushButton::clicked, this, &TicketEditWindow::RemoveSelfFromStack);
    connect(m_save_button, &QPushButton::clicked, this, &TicketEditWindow::SaveChanges);
}

int TicketEditWindow::GetHeaderFlags() const {
    return Header::ShowHeader | Header::ShowTitle | Header::ShowBackArrow;
}

QString TicketEditWindow::GetHeaderTitle() const {
    using namespace config::ticket_edit_window;
    return HEADER_TITLE;
}

void TicketEditWindow::SetupTicketsModel(TicketModel *ticket_model) {
    m_ticket_model = ticket_model;
    InitializeFormFields();
}

void TicketEditWindow::InitializeFormFields() {
    const auto current_index =
        qvariant_cast<QModelIndex>(m_ticket_model->data(QModelIndex{}, TicketModel::ChosenTicketRole));
    const auto current_ticket =
        qvariant_cast<Ticket>(m_ticket_model->data(current_index, Qt::DisplayRole));

    m_name_line_edit->setText(current_ticket.GetName());
    m_description_text_edit->setText(current_ticket.GetDescription());
    m_priority_widget->SetPriority(current_ticket.GetPriority());
}

void TicketEditWindow::SaveChanges() {
    const auto current_index =
        qvariant_cast<QModelIndex>(m_ticket_model->data(QModelIndex{}, TicketModel::ChosenTicketRole));
    auto current_ticket = qvariant_cast<Ticket>(m_ticket_model->data(current_index, Qt::DisplayRole));
    current_ticket.SetName(m_name_line_edit->text());
    current_ticket.SetDescription(m_description_text_edit->toPlainText());
    current_ticket.SetPriority(m_priority_widget->GetPriority());
    m_ticket_model->setData(current_index, QVariant::fromValue(current_ticket), Qt::EditRole);
    RemoveSelfFromStack();

    // TODO: Add post request to save changes on server
}
