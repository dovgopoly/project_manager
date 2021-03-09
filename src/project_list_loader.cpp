#include <QString>

#include "../includes/private_config.hpp"
#include "../includes/project_list_loader.hpp"

ProjectListLoader::ProjectListLoader(QObject *parent)
    : AbstractRequester{parent} {
}

ProjectListLoader &ProjectListLoader::GetInstance() {
    static ProjectListLoader project_list_loader;
    return project_list_loader;
}

void ProjectListLoader::DownloadProjectList(const QString &token) const {
    using namespace private_config;
    auto *const response = Api::GetInstance().Get(
        QString{"%1/project/projects/"}.arg(LINK_PREFIX),
        {{"authorization", token}}
        );
    connect(response, &QNetworkReply::finished, this, &ProjectListLoader::ReceiveData);
}
