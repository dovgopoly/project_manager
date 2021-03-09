#include "../includes/image_loader.hpp"

ImageLoader::ImageLoader(QObject *parent)
    : AbstractRequester{parent} {
}

void ImageLoader::LoadImage(const QUrl &url) const {
    auto *const response = Api::GetInstance().Get(url);
    connect(response, &QNetworkReply::finished, this, &ImageLoader::ReceiveData);
}
