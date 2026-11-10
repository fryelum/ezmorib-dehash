// Includes
#include <QApplication>
#include <ezmorib-dehash/Windows/MainWindow.hpp>

// Functions
int main(int argc, char *argv[]) {
	QApplication MainApplication(argc, argv);

	Windows::MainWindow MoribDehashWindow;
	MoribDehashWindow.show();

	return MainApplication.exec();
}
