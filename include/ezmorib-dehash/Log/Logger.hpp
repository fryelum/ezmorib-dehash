#ifndef LOG_LOGGER_HPP
#define LOG_LOGGER_HPP
// Includes
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <deque>
#include <ezmorib-dehash/Log/BasicLogEvent.hpp>

// Namespaces
namespace Log {
	/// Classes
	class Logger {
		public:
			//// Constructor / Destructor
			Logger(QString DataPath);
			~Logger();

			//// Functions
			QString GetAllEventsAsString(LogEventTypes TypeFilter = LogEventTypes::PLEASEGETALLEVENTSBUTDEBUG);
			void LogEvent(LogEventTypes EventType, QString Data, bool AddNewLine = true);
			void SetMaximumEventsAllowedInMemory(int NewLimit);

		private:
			//// Variables
			QString LogFilePath;
			bool RealFileAvailable = true;
			int MaximumEventsInMemoryAllowed = 100;
			std::deque<BasicLogEvent> LogEvents;
	};
}

#endif // LOG_LOGGER_HPP
