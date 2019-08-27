#include "Downloader.h"

#include <QCoreApplication>
#include <memory>
#include <iostream>

template <typename T>
void deleter(T* value) {
	delete value;
}

int main(int argc, char* argv[])
{
	try {
		QCoreApplication a(argc, argv);

		std::string url_page;
		std::cout << "Enter the link to the site:\n";
		std::cin >> url_page;
		Downloader download_page(QString::fromUtf8(url_page.c_str()));
		download_page.SendGet();
	}
	catch (std::runtime_error& ex) {
		std::cout << "Error: " << ex.what() << std::endl;
	}
	catch (std::bad_alloc&) {
		std::cout << "Memory overflow" << std::endl;
	}
	return 0;
}