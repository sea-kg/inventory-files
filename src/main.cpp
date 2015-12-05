#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QDir>

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	
	// init work directory
	QDir dir(QDir::homePath());
	{
		if (!dir.exists(".inventory-files")) {
			if (dir.mkdir(".inventory-files")) {
				dir.cd(".inventory-files");
				std::cout << "created work directory ~/.inventory-files\n";
			} else {
				std::cout << "could not create ~/.inventory-files\n";
				return -1;
			}
		} else {
			dir.cd(".inventory-files");
		}
	}
	std::cout << "Work directory: " << dir.canonicalPath().toStdString() <<" \n";

	MainWindow w(dir.canonicalPath());
	w.show();
	return app.exec();
}
