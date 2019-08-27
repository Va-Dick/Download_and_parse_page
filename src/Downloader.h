#pragma once
//#include <QtNetwork/QNetworkAccessManager>
//#include <QtNetwork/QNetworkRequest>
//#include <QtNetwork/QNetworkReply>
//#include <QUrl>
//#include <QSslSocket>

#include <QtNetwork>
#include <QObject>
#include <QEventLoop>
#include <qfile.h>

#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <exception>

#define _REGEX_MAX_STACK_COUNT 200'000 // Необходим для того, чтобы увеличить максимальный стек
#include <regex>

class Downloader : public QObject {
	Q_OBJECT
public:
	Downloader(const QUrl& url_) : url(url_) {}
	~Downloader();
	void SendGet();
	void GetResponse();
	void ParsePage();
private:
	const QUrl url = "http://www.google.com";	//url страница
	QNetworkAccessManager* manager;				//Менеджер сетевого доступа
	QNetworkReply* reply;
};