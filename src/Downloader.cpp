#include "Downloader.h"

#include <QObject>
#include <QEventLoop>
#include <qfile.h>

#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <exception>

#define _REGEX_MAX_STACK_COUNT 200'000										 // Increase the maximum stack
#include <regex>

void Downloader::SendGet() {
	manager = new QNetworkAccessManager(this);								// Initialize manager
	reply = manager->get(QNetworkRequest(url));								// Make get request
	
	QEventLoop loop;
	connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));	
	loop.exec();												// Waiting for a response and receiving a page

	GetResponse();												// Read the received data

	ParsePage();												// Search url links
}

void Downloader::GetResponse() {										// Writing received data to a file
	if (reply->error() != QNetworkReply::NoError) {
		throw std::runtime_error("message not received\n");
	}

	QFile file("file.txt");
	if (!file.open(QFile::WriteOnly)) {
		throw std::runtime_error("unable to open or create \"file.txt\" file\n");
	}
	if (!file.write(reply->readAll())) {
		throw std::runtime_error("unable to wright to file \"file.txt\" file\n");
	}
	if (!file.flush()) {
		throw std::runtime_error("unable to flush \"file.txt\" file\n");
	}
	file.close();
	std::cout << "Page has been downloaded\n";
}

void Downloader::ParsePage() {
	std::regex regular("(http)([|s?]{0,1})(://)([^ ;\"<)']+)");						//Regular Expression Pattern (for finding internal links)

	std::ifstream file("file.txt");
	std::ofstream url("url.txt");
	if (!file) {
		throw std::runtime_error("unable to open \"file.txt\" file\n");
	}
	if (!url) {
		throw std::runtime_error("unable to open \"url.txt\" file\n");
	}

	std::string line;
	while (getline(file, line)) {										//Writing url links to a file
		for (auto it = std::sregex_iterator(line.begin(), line.end(), regular);
			it != std::sregex_iterator();++it){
			url << it->str() << "\n";
		}
	}
	std::cout << "Page has been parsed\n";
}

Downloader::~Downloader() {
	delete manager;
}
