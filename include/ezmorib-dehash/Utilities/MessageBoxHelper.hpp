#ifndef UTILITIES_MESSAGEBOXHELPER_HPP
#define UTILITIES_MESSAGEBOXHELPER_HPP
// Includes
#include <QMessageBox>

// Namespaces
namespace Utilities {
	int ShowWarningPrompt(QString Title, QString WarningAbout, bool HasYesNoToAll = false);
	void ShowWarning(QString Title, QString WarningAbout);
}

#endif // UTILITIES_MESSAGEBOXHELPER_HPP
