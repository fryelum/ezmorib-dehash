#ifndef WINDOWS_MAINWINDOW_HPP
#define WINDOWS_MAINWINDOW_HPP
// Includes
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLineEdit>
#include <QList>
#include <QMainWindow>
#include <QPushButton>
#include <QStandardPaths>
#include <ezmorib-dehash/Actions/Hasher.hpp>
#include <ezmorib-dehash/Data/HashData.hpp>
#include <ezmorib-dehash/Log/Logger.hpp>
#include <ezmorib-dehash/Utilities/MessageBoxHelper.hpp>
#include <ezmorib-dehash/Windows/About/AboutWindow.hpp>
#include <ezmorib-dehash/Windows/Log/LogWindow.hpp>

// Namespaces
QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

namespace Windows {
	/// Classes
	class MainWindow: public QMainWindow {
		Q_OBJECT
		public:
			//// Constructor / Destructor
			MainWindow(QWidget *Parent = nullptr);
			~MainWindow();

		private slots:
			//// Functions
			void closeEvent(QCloseEvent *Event);

		private:
			//// Variables
			AboutWindow *About;
			LogWindow *Log;
			Log::Logger *RuntimeLog;
			QList<Data::HashData*> Hashes;
			Ui::MainWindow *ui;

			//// Functions
			bool SetupHashData();
			void OpenFolder(QLineEdit *&TargetLineEdit);
			void RunDehash();
			void RunRehash();
			void SetupButtonsAndStuff();
	};
}

#endif // WINDOWS_MAINWINDOW_HPP
