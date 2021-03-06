#ifndef TICKET_LIST_WINDOW_HPP
#define TICKET_LIST_WINDOW_HPP

#include <QWidget>
#include <QListView>

#include "abstract_window.hpp"
#include "ticket_delegate.hpp"
#include "ticket_model.hpp"
#include "project_model.hpp"
#include "project_icon_delegate.hpp"

#include "../other/waiting_spinner/waiting_spinner_widget.h"

class TicketListWindow : public AbstractWindow {
 Q_OBJECT
 public:
    TicketListWindow(Stack &stack, QWidget *parent = nullptr);

    void SetupProjectModel(ProjectModel *project_model);

    int GetHeaderFlags() const override;
    QString GetHeaderTitle() const override;

 private:
    void Initialize();

    QListView *const m_project_icon_view;
    ProjectIconDelegate *const m_project_icon_delegate;

    QListView *const m_ticket_view;
    TicketDelegate *const m_ticket_delegate;
    TicketModel *const m_ticket_model;

    WaitingSpinnerWidget *const m_waiting_spinner_widget;

 private slots:
    void ShowTicketsForChosenProject(const QModelIndex &index);
    void ProjectIconClicked(const QModelIndex &index);
    void TicketClicked(const QModelIndex &index);
};

#endif