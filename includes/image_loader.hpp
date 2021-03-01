#ifndef IMAGE_LOADER_HPP
#define IMAGE_LOADER_HPP

#include "abstract_requester.hpp"

class ImageLoader : public AbstractRequester {
 Q_OBJECT
 public:
    ImageLoader(const ImageLoader &) = delete;
    ImageLoader &operator=(const ImageLoader &) = delete;

    static ImageLoader &GetInstance();

    void LoadImage(const QUrl &url) const;

 private:
    explicit ImageLoader(QObject *parent = nullptr);
};

#endif