// Includes
#include <ezmorib-dehash/Utilities/MessageBoxHelper.hpp>

// Namespaces
namespace Utilities {
	/// Functions
	int ShowWarningPrompt(QString Title, QString WarningAbout, bool HasYesNoToAll) {
		QMessageBox WarningMessage;
		WarningMessage.setWindowTitle(Title);
		WarningMessage.setText(WarningAbout);

		if(HasYesNoToAll)
			WarningMessage.setStandardButtons(QMessageBox::Yes |QMessageBox::YesToAll| QMessageBox::No | QMessageBox::NoToAll);
		else
			WarningMessage.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

		WarningMessage.setDefaultButton(QMessageBox::No);

		return WarningMessage.exec();
	}

	void ShowWarning(QString Title, QString WarningAbout) {
		QMessageBox WarningMessage;
		WarningMessage.setWindowTitle(Title);
		WarningMessage.setText(WarningAbout);

		WarningMessage.exec();
	}
}
