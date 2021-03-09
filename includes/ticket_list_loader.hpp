#ifndef TICKET_LIST_LOADER_HPP
#define TICKET_LIST_LOADER_HPP

#include "abstract_requester.hpp"
#include "authenticator.hpp"

class TicketListLoader : public AbstractRequester {
 Q_OBJECT
 public:
    Q_DISABLE_COPY(TicketListLoader)

    static TicketListLoader &GetInstance();

    void DownloadTicketList(const QString &token, int id) const;

 private:
    explicit TicketListLoader(QObject *parent = nullptr);
};

#endif