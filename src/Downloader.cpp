#include "Downloader.h"

void Downloader::SendGet() {
	manager = new QNetworkAccessManager(this);					// �������������� ��������
	reply = manager->get(QNetworkRequest(url));					// ����������� get ������
	
	QEventLoop loop;
	connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));	
	loop.exec();												// ���� ��������� ������

	GetResponse();												// ��������� ���������� ������

	ParsePage();												// ���� � txt ����� url ������
}

void Downloader::GetResponse() {								// ������ ���������� ������ � ����
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
	std::regex regular("([\\http\\https?]{4,5})(://)(.)*?([\\s\\;\"\\<\\)\'])");	//������ ���������� ���������� (��� ������ ���������� �����)

	std::ifstream file("file.txt");
	std::ofstream url("url.txt");
	if (!file) {
		throw std::runtime_error("unable to open or create \"file.txt\" file\n");
	}
	if (!url) {
		throw std::runtime_error("unable to open or create \"url.txt\" file\n");
	}

	std::string line;
	while (getline(file, line)) {													//������ � ���� ���������� �� ������� ���������
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