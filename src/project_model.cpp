#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "../includes/project_model.hpp"
#include "../includes/project_list_loader.hpp"
#include "../includes/authenticator.hpp"

ProjectModel::ProjectModel(QObject *parent)
    : QAbstractListModel{parent} {

    Initialize();
}

void ProjectModel::Initialize() {
    auto &project_list_loader = ProjectListLoader::GetInstance();
    connect(&project_list_loader, &ProjectListLoader::ResponseReady, this, &ProjectModel::ParseProjectsToList);
    UpdateSelf();
}

void ProjectModel::UpdateSelf() {
    emit UpdatingBegin();

    auto &project_list_loader = ProjectListLoader::GetInstance();
    auto &authenticator = Authenticator::GetInstance();

    project_list_loader.DownloadProjectList(authenticator.GetCurrentToken());
}

int ProjectModel::rowCount(const QModelIndex &index) const {
    return m_project_list.count();
}

QVariant ProjectModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        QVariant{};
    }
    switch (role) {
        case Qt::DisplayRole: {
            return QVariant::fromValue(m_project_list.at(index.row()));
        }
        case ChosenProjectRole: {
            return m_chosen_project;
        }
        default: {
            return QVariant{};
        }
    }
}

bool ProjectModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    switch (role) {
        case Roles::ChosenProjectRole: {
            m_chosen_project = qvariant_cast<QModelIndex>(value);
        }
    }
    return false;
}

Qt::ItemFlags ProjectModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }
    return QAbstractListModel::flags(index);
}

void ProjectModel::ParseProjectsToList(const QByteArray &json_to_parse) {
    const auto json_object = QJsonDocument::fromJson(json_to_parse).object();
    const auto projects = json_object["projects"].toArray();

    beginInsertRows(QModelIndex(), 0, projects.count() - 1);
    for (const QJsonValue &project : projects) {
        const auto project_object = project.toObject();
        const auto name = project_object["name"].toString();
        const auto icon = QUrl{project_object["icon"].toString()};
        const auto id = project_object["id"].toString().toInt();
        m_project_list.emplace_back(id, name, icon);
        connect(m_project_list.back().GetIcon(), &Image::Updated, [=] {
            emit ImageUpdated();
        });
    }
    endInsertRows();

    emit UpdatingEnd();
}
