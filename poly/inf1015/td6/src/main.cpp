#include <iostream>
#include <string>
#include <QApplication>
#include <QPushButton>

int main(int argc) {
	char *name[] = {"chess"};
  QApplication app(argc, name);

	QPushButton play("Play");
	play.show();

	return app.exec();
}