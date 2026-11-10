// Includes
#include <ezmorib-dehash/Windows/MainWindow.hpp>
#include "./ui_MainWindow.h"

// Namespaces
namespace Windows {
	/// Constructor / Destructor
	MainWindow::MainWindow(QWidget *Parent): QMainWindow(Parent), ui(new Ui::MainWindow) {
		ui->setupUi(this);

		RuntimeLog = new Log::Logger(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/fryelum/ezmorib-dehash/");
		Log = new LogWindow(RuntimeLog);
		About = new AboutWindow();

		if(!SetupHashData())
			close();

		SetupButtonsAndStuff();
	}

	MainWindow::~MainWindow() {
		delete ui;
	}

	/// Functions
	bool MainWindow::SetupHashData() {
		QFile *HashJSONFile = new QFile(":/Data/Hashes.json");
		if(!HashJSONFile->open(QIODevice::ReadOnly | QIODevice::Text))
			return false;

		QJsonDocument *HashJSON = new QJsonDocument(QJsonDocument::fromJson(HashJSONFile->readAll()));
		delete HashJSONFile;

		for(const QJsonValue CurrentHash : HashJSON->object()["Names"].toArray()) {
			Hashes.append(new Data::HashData{.HashedName = CurrentHash["HashedName"].toString(), .RealName = CurrentHash["RealName"].toString()});
		}
		delete HashJSON;

		return true;
	}

	void MainWindow::OpenFolder(QLineEdit *&TargetLineEdit) {
		QString OpenedFolder = QFileDialog::getExistingDirectory(this, "Open a folder!", "", QFileDialog::ShowDirsOnly);
		if(OpenedFolder.isNull() || OpenedFolder.isEmpty()) {
			RuntimeLog->LogEvent(Log::LogEventTypes::LOG_WARNING, "FAILED to open folder with reason: no folder chosen.");

			return;
		}

		TargetLineEdit->setText(OpenedFolder);
	}

	void MainWindow::RunDehash() {
		if((ui->DehashInputFolder->text().isNull() || ui->DehashInputFolder->text().isEmpty()) || (ui->DehashOutputFolder->text().isNull() || ui->DehashOutputFolder->text().isEmpty())) {
			RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, "FAILED to run ezmorib-dehash! One of the inputs were empty or null. Ensure everything looks right!");
			Utilities::ShowWarning("FAILED to run ezmorib-dehash!", "Ensure every box is filled and looks right!");

			return;
		}

		if(ui->DehashInputFolder->text() == ui->DehashOutputFolder->text()) {
			switch(Utilities::ShowWarningPrompt("HEY!!!", "Both the input and output folders for dehashing are the same! Are you sure you want to do this?")) {
				case QMessageBox::Yes:
					RuntimeLog->LogEvent(Log::LogEventTypes::LOG_WARNING, "Using same folder for input and output (dehash).");

					break;

				default:
					return;
			}
		}

		Actions::Dehash(RuntimeLog, Hashes, ui->DehashInputFolder->text(), ui->DehashOutputFolder->text());
	}

	void MainWindow::RunRehash() {
		if((ui->RehashInputFolder->text().isNull() || ui->RehashInputFolder->text().isEmpty()) || (ui->RehashOutputFolder->text().isNull() || ui->RehashOutputFolder->text().isEmpty())) {
			RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, "FAILED to run ezmorib-dehash! One of the inputs were empty or null. Ensure everything looks right!");
			Utilities::ShowWarning("FAILED to run ezmorib-dehash!", "Ensure every box is filled and looks right!");

			return;
		}

		if(ui->RehashInputFolder->text() == ui->RehashOutputFolder->text()) {
			switch(Utilities::ShowWarningPrompt("HEY!!!", "Both the input and output folders for rehashing are the same! Are you sure you want to do this?")) {
				case QMessageBox::Yes:
					RuntimeLog->LogEvent(Log::LogEventTypes::LOG_WARNING, "Using same folder for input and output (rehash).");
					break;

				default:
					return;
			}
		}

		Actions::Rehash(RuntimeLog, Hashes, ui->RehashInputFolder->text(), ui->RehashOutputFolder->text());
	}

	void MainWindow::SetupButtonsAndStuff() {
		//// Menubar
		connect(ui->MenubarAbout, &QAction::triggered, this, [&]() { About->show(); });
		connect(ui->MenubarExit, &QAction::triggered, this, &MainWindow::close);
		connect(ui->MenubarLog, &QAction::triggered, this, [&]() { Log->show(); });

		//// Buttons
		connect(ui->DehashOpenInputFolder, &QPushButton::pressed, this, [&]() { MainWindow::OpenFolder(ui->DehashInputFolder); });
		connect(ui->DehashOpenOutputFolder, &QPushButton::pressed, this, [&]() { MainWindow::OpenFolder(ui->DehashOutputFolder); });
		connect(ui->RehashOpenInputFolder, &QPushButton::pressed, this, [&]() { MainWindow::OpenFolder(ui->RehashInputFolder); });
		connect(ui->RehashOpenOutputFolder, &QPushButton::pressed, this, [&]() { MainWindow::OpenFolder(ui->RehashOutputFolder); });
		connect(ui->DehashRun, &QPushButton::pressed, this, &MainWindow::RunDehash);
		connect(ui->RehashRun, &QPushButton::pressed, this, &MainWindow::RunRehash);
	}

	void MainWindow::closeEvent(QCloseEvent *Event) {
		Log->close();
		delete Log;
		delete RuntimeLog;

		About->close();
		delete About;
	}
}
