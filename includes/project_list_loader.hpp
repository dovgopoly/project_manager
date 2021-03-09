#ifndef PROJECT_LIST_LOADER_HPP
#define PROJECT_LIST_LOADER_HPP

#include "abstract_requester.hpp"

class ProjectListLoader : public AbstractRequester {
 Q_OBJECT
 public:
    Q_DISABLE_COPY(ProjectListLoader)

    static ProjectListLoader &GetInstance();

    void DownloadProjectList(const QString &token) const;

 private:
    explicit ProjectListLoader(QObject *parent = nullptr);
};

#endif
