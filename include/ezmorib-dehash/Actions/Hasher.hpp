#ifndef ACTIONS_HASHER_HPP
#define ACTIONS_HASHER_HPP
// Includes
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QList>
#include <ezmorib-dehash/Data/HashData.hpp>
#include <ezmorib-dehash/Log/Logger.hpp>
#include <ezmorib-dehash/Utilities/MessageBoxHelper.hpp>

// Namespaces
namespace Actions {
	void Dehash(Log::Logger *&RuntimeLog, QList<Data::HashData*> &Data, QString InputDirectory, QString OutputDirectory);
	void Rehash(Log::Logger *&RuntimeLog, QList<Data::HashData*> &Data, QString InputDirectory, QString OutputDirectory);
}

#endif // ACTIONS_HASHER_HPP
