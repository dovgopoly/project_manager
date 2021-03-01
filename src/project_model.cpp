#include "../includes/project_model.hpp"

ProjectModel::ProjectModel(QObject *parent)
    : QAbstractListModel{parent} {
    // mocked data
    for (int i = 0; i < 20; ++i) {
        m_list.append(Project(0, QString{"project %1"}.arg(i), QUrl{"https://i.ibb.co/xLHd5mZ/4.jpg"}));
    }
}

int ProjectModel::rowCount(const QModelIndex &) const {
    return m_list.count();
}

QVariant ProjectModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        QVariant{};
    }
    switch (role) {
        case Qt::DisplayRole: {
            return QVariant::fromValue(m_list.at(index.row()));
        }
        default: {
            return QVariant{};
        }
    }
}

bool ProjectModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    switch (role) {
        case Qt::EditRole: {
            m_list.replace(index.row(), qvariant_cast<Project>(value));
            return true;
        }
        default: {
            return false;
        }
    }
}

Qt::ItemFlags ProjectModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }
    return QAbstractListModel::flags(index);
}
