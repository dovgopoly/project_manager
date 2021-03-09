#ifndef PROJECT_LIST_WINDOW_HPP
#define PROJECT_LIST_WINDOW_HPP

#include <QWidget>
#include <QTimer>
#include <QListView>
#include <QPushButton>

#include "abstract_window.hpp"
#include "project_list_loader.hpp"
#include "project_model.hpp"
#include "project_delegate.hpp"

class ProjectListWindow : public AbstractWindow {
 Q_OBJECT
 public:
    explicit ProjectListWindow(Stack &stack, QWidget *parent = nullptr);

    int GetHeaderFlags() const override;
    QString GetHeaderTitle() const override;

 private:
    void Initialize();

    QListView *const m_project_list_view;
    ProjectModel *const m_project_model;
    ProjectDelegate *const m_project_delegate;

 private slots:
    void ProjectClicked(const QModelIndex &index);
    void ProjectDoubleClicked(const QModelIndex &index);
};

#endif