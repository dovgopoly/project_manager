#ifndef IMAGE_LOADER_HPP
#define IMAGE_LOADER_HPP

#include "abstract_requester.hpp"

class ImageLoader : public AbstractRequester {
 Q_OBJECT
 public:
    explicit ImageLoader(QObject *parent = nullptr);

    void LoadImage(const QUrl &url) const;
};

#endif