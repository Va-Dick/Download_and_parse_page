#include "Downloader.h"

void Downloader::SendGet() {
	manager = new QNetworkAccessManager(this);					// Инициализируем менеджер
	reply = manager->get(QNetworkRequest(url));					// Запрашиваем get запрос
	
	QEventLoop loop;
	connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));	
	loop.exec();												// Ждем получение ответа

	GetResponse();												// Считываем полученные данные

	ParsePage();												// Ищем в txt файле url ссылки
}

void Downloader::GetResponse() {								// Запись полученных данных в файл
	if (reply->error() == QNetworkReply::NoError){
		QFile file("file.txt");
		if (file.open(QFile::WriteOnly)){
			file.write(reply->readAll());
			file.flush();
			file.close();
			std::cout << "Page has been downloaded\n";
		}
		else{
			throw std::runtime_error("unable to open or create \"file.txt\" file\n");
		}
	}
	else{
		throw std::runtime_error("message not received\n");
	}
}

void Downloader::ParsePage() {
	std::regex regular("([\\http\\https?]{4,5})(://)(.)*?([\\s\\;\"\\<\\)\'])");	//Шаблон регулярных овыражений (для поиска внутренних сылок)

	std::ifstream file("file.txt");
	std::ofstream url("url.txt");
	if (!file) {
		throw std::runtime_error("unable to open or create \"file.txt\" file\n");
	}
	if (!url) {
		throw std::runtime_error("unable to open or create \"url.txt\" file\n");
	}

	std::string line;
	while (getline(file, line)) {													//Запись в файл подходящих по шаблону выражений
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