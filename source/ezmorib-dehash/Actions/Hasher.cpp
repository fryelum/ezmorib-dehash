// Includes
#include <ezmorib-dehash/Actions/Hasher.hpp>

// Namespaces
namespace Actions {
	void Dehash(Log::Logger *&RuntimeLog, QList<Data::HashData*> &Data, QString InputDirectory, QString OutputDirectory) {
		bool NoToAllWarnings = false;
		bool YesToAllWarnings = false;

		if(!InputDirectory.endsWith("/"))
			InputDirectory += "/";

		if(!OutputDirectory.endsWith("/"))
			OutputDirectory += "/";

		for(const Data::HashData *CurrentHash : Data) {
			QFile *CurrentFile = new QFile();
			CurrentFile->setFileName(InputDirectory + CurrentHash->HashedName);
			if(!CurrentFile->exists()) {
				RuntimeLog->LogEvent(Log::LogEventTypes::LOG_WARNING, QString("Source file %1 doesn't exist! Ignoring and continuing...").arg(CurrentFile->fileName()));

				delete CurrentFile;
				continue;
			}

			QString *TargetDirectoryPath = new QString((OutputDirectory + CurrentHash->RealName).left((OutputDirectory + CurrentHash->RealName).lastIndexOf("/")));
			QDir *TargetDirectory = new QDir(*TargetDirectoryPath);
			if(!TargetDirectory->exists()) { 
				if(!TargetDirectory->mkpath(*TargetDirectoryPath)) {
					RuntimeLog->LogEvent(Log::LogEventTypes::LOG_WARNING, QString("Failed to make path at %1! Skipping this file (%2) and continuing...").arg(*TargetDirectoryPath, CurrentFile->fileName()));

					delete CurrentFile, TargetDirectory, TargetDirectoryPath;
					continue;
				}
			}

			delete TargetDirectory, TargetDirectoryPath;

			QFile *TargetFile = new QFile();
			TargetFile->setFileName(OutputDirectory + CurrentHash->RealName);
			if(TargetFile->exists()) {
				RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, QString("Target file %1 already exists... Using user input on what to do.").arg(TargetFile->fileName()));

				if(!NoToAllWarnings && !YesToAllWarnings) {
					RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, "User hasn't chosen what to do for this file (and/or all instances of existing files) yet. Getting choice.");

					switch(Utilities::ShowWarningPrompt("Target file already exists!", "Do you want to allow it to be overwritten? (To allow or deny all other cases of existing files, use \"Yes to All\" or \"No to All\")", true)) {
						case QMessageBox::NoToAll:
							NoToAllWarnings = true;
							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, "User chose to ignore all cases where the target file already exists.");

							delete CurrentFile, TargetFile;
							continue;

						case QMessageBox::No:
							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, "User chose to ignore this case where the target file already exists.");

							delete CurrentFile, TargetFile;
							continue;

						case QMessageBox::YesToAll:
							YesToAllWarnings = true;
							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, "User chose to overwrite in all cases where the target file already exists.");

							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, QString("Removing existing file %1...").arg(TargetFile->fileName()));
							if(!TargetFile->remove()) {
								RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, QString("FAILED to delete existing file at %1! Continuing with the other files...").arg(TargetFile->fileName()));

								delete CurrentFile, TargetFile;
								continue;
							}

							break;

						case QMessageBox::Yes:
							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, "User chose to overwrite in this case where the target file already exists.");

							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, QString("Removing existing file %1...").arg(TargetFile->fileName()));
							if(!TargetFile->remove()) {
								RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, QString("FAILED to delete existing file at %1! Continuing with the other files...").arg(TargetFile->fileName()));

								delete CurrentFile, TargetFile;
								continue;
							}

							break;

						default:
							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, "User gave no choice! Defaulting to single use No for this case.");

							delete CurrentFile, TargetFile;
							continue;
					}
				} else {
					if(NoToAllWarnings) {
						RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, QString("Skipping this file (%1) since the target already exists and the user said to ignore all cases where files exist...").arg(TargetFile->fileName()));

						delete CurrentFile, TargetFile;
						continue;
					} else if(YesToAllWarnings)
						RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, QString("Removing existing file %1...").arg(TargetFile->fileName()));
						if(!TargetFile->remove()) {
							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, QString("FAILED to delete existing file at %1! Continuing with the other files...").arg(TargetFile->fileName()));

							delete CurrentFile, TargetFile;
							continue;
						}
				}
			}

			RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, QString("Copying %1 to %2...").arg(CurrentFile->fileName(), TargetFile->fileName()));
			if(!CurrentFile->copy(TargetFile->fileName()))
				RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, QString("Failed to copy! Error: %1. Continuing with the other files...").arg(CurrentFile->errorString()));

			delete CurrentFile, TargetFile;
		}
	}

	void Rehash(Log::Logger *&RuntimeLog, QList<Data::HashData*> &Data, QString InputDirectory, QString OutputDirectory) {
		bool NoToAllWarnings = false;
		bool YesToAllWarnings = false;

		if(!InputDirectory.endsWith("/"))
			InputDirectory += "/";

		if(!OutputDirectory.endsWith("/"))
			OutputDirectory += "/";

		for(const Data::HashData *CurrentHash : Data) {
			QFile *CurrentFile = new QFile();
			CurrentFile->setFileName(InputDirectory + CurrentHash->RealName);
			if(!CurrentFile->exists()) {
				RuntimeLog->LogEvent(Log::LogEventTypes::LOG_WARNING, QString("Source file %1 doesn't exist! Ignoring and continuing...").arg(CurrentFile->fileName()));

				delete CurrentFile;
				continue;
			}

			QString *TargetDirectoryPath = new QString((OutputDirectory + CurrentHash->HashedName).left((OutputDirectory + CurrentHash->HashedName).lastIndexOf("/")));
			QDir *TargetDirectory = new QDir(*TargetDirectoryPath);
			if(!TargetDirectory->exists()) { 
				if(!TargetDirectory->mkpath(*TargetDirectoryPath)) {
					RuntimeLog->LogEvent(Log::LogEventTypes::LOG_WARNING, QString("Failed to make path at %1! Skipping this file (%2) and continuing...").arg(*TargetDirectoryPath, CurrentFile->fileName()));

					delete CurrentFile, TargetDirectory, TargetDirectoryPath;
					continue;
				}
			}

			delete TargetDirectory, TargetDirectoryPath;

			QFile *TargetFile = new QFile();
			TargetFile->setFileName(OutputDirectory + CurrentHash->HashedName);
			if(TargetFile->exists()) {
				RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, QString("Target file %1 already exists... Using user input on what to do.").arg(TargetFile->fileName()));

				if(!NoToAllWarnings && !YesToAllWarnings) {
					RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, "User hasn't chosen what to do for this file (and/or all instances of existing files) yet. Getting choice.");

					switch(Utilities::ShowWarningPrompt("Target file already exists!", "Do you want to allow it to be overwritten? (To allow or deny all other cases of existing files, use \"Yes to All\" or \"No to All\")", true)) {
						case QMessageBox::NoToAll:
							NoToAllWarnings = true;
							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, "User chose to ignore all cases where the target file already exists.");

							delete CurrentFile, TargetFile;
							continue;

						case QMessageBox::No:
							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, "User chose to ignore this case where the target file already exists.");

							delete CurrentFile, TargetFile;
							continue;

						case QMessageBox::YesToAll:
							YesToAllWarnings = true;
							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, "User chose to overwrite in all cases where the target file already exists.");

							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, QString("Removing existing file %1...").arg(TargetFile->fileName()));
							if(!TargetFile->remove()) {
								RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, QString("FAILED to delete existing file at %1! Continuing with the other files...").arg(TargetFile->fileName()));

								delete CurrentFile, TargetFile;
								continue;
							}

							break;

						case QMessageBox::Yes:
							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, "User chose to overwrite in this case where the target file already exists.");

							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, QString("Removing existing file %1...").arg(TargetFile->fileName()));
							if(!TargetFile->remove()) {
								RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, QString("FAILED to delete existing file at %1! Continuing with the other files...").arg(TargetFile->fileName()));

								delete CurrentFile, TargetFile;
								continue;
							}

							break;

						default:
							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, "User gave no choice! Defaulting to single use No for this case.");

							delete CurrentFile, TargetFile;
							continue;
					}
				} else {
					if(NoToAllWarnings) {
						RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, QString("Skipping this file (%1) since the target already exists and the user said to ignore all cases where files exist...").arg(TargetFile->fileName()));

						delete CurrentFile, TargetFile;
						continue;
					} else if(YesToAllWarnings)
						RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, QString("Removing existing file %1...").arg(TargetFile->fileName()));
						if(!TargetFile->remove()) {
							RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, QString("FAILED to delete existing file at %1! Continuing with the other files...").arg(TargetFile->fileName()));

							delete CurrentFile, TargetFile;
							continue;
						}
				}
			}

			RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, QString("Copying %1 to %2...").arg(CurrentFile->fileName(), TargetFile->fileName()));
			if(!CurrentFile->copy(TargetFile->fileName()))
				RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, QString("Failed to copy! Error: %1. Continuing with the other files...").arg(CurrentFile->errorString()));

			delete CurrentFile, TargetFile;
		}
	}
}
