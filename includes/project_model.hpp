#ifndef PROJECT_MODEL_HPP
#define PROJECT_MODEL_HPP

#include <QAbstractListModel>

#include "project.hpp"

class ProjectModel : public QAbstractListModel {
 Q_OBJECT
 public:
    explicit ProjectModel(QObject *parent = nullptr);
    ~ProjectModel() override = default;

    int rowCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

 private:
    QList<Project> m_list;
};

#endif