#include "../includes/image_loader.hpp"

ImageLoader::ImageLoader(QObject *parent)
    : AbstractRequester{parent} {
}

ImageLoader &ImageLoader::GetInstance() {
    static ImageLoader image_loader;
    return image_loader;
}

void ImageLoader::LoadImage(const QUrl &url) const {
    connect(Api::GetInstance().Get(url), &QNetworkReply::finished, this, &ImageLoader::ReceiveData);
}
