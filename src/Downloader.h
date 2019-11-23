#pragma once
//#include <QtNetwork/QNetworkAccessManager>
//#include <QtNetwork/QNetworkRequest>
//#include <QtNetwork/QNetworkReply>
//#include <QUrl>
//#include <QSslSocket>

#include <QtNetwork>

class Downloader : public QObject {
	Q_OBJECT
public:
	Downloader(const QUrl& url_) : url(url_) {}
	~Downloader();
	void SendGet();
private:
	void GetResponse();
        void ParsePage();
	const QUrl url = "http://www.google.com";	//url link
	QNetworkAccessManager* manager;			//Network access manager
	QNetworkReply* reply;
};
