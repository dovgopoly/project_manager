#ifndef TICKET_EDIT_WINDOW_HPP
#define TICKET_EDIT_WINDOW_HPP

#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QListView>
#include <QPushButton>

#include "abstract_window.hpp"
#include "ticket.hpp"
#include "ticket_model.hpp"
#include "priority_widget.hpp"
#include "image.hpp"

class TicketEditWindow : public AbstractWindow {
Q_OBJECT
 public:
    explicit TicketEditWindow(Stack &stack, QWidget *parent = nullptr);

    void SetupTicketsModel(TicketModel *ticket_model);

    int GetHeaderFlags() const override;
    QString GetHeaderTitle() const override;

 private:
    void Initialize();
    void InitializeFormFields();

    TicketModel *m_ticket_model;

    QLineEdit *const m_name_line_edit;
    QTextEdit *const m_description_text_edit;
    QPushButton *const m_save_button;
    QPushButton *const m_cancel_button;
    Image *const m_up_arrow_button;
    Image *const m_down_arrow_button;
    PriorityWidget *const m_priority_widget;

 private slots:
    void SaveChanges();

};

#endif