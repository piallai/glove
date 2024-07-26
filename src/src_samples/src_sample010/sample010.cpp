/*
* This file is part of the Glove distribution (https://github.com/piallai/glove).
* Copyright (C) 2024 Pierre Allain.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/*! Example to monitor the progress feedback of an algorithm in a method of a class.*/

#include <QApplication>

#include "ClassC.h"
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvProgressMgr.h"
#endif
#include <QtConcurrent/QtConcurrentRun>
#include <QFutureWatcher>
#include "FutureWrapper.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

	ClassC classC(100);
	GlvProgressMgr progress_mgr;
	progress_mgr.add_progression(classC.get_progression());
	progress_mgr.show();

#if QT_VERSION_MAJOR < 6
	QFuture<void> future = QtConcurrent::run(&classC, &ClassC::process);
#else
	QFuture<void> future = QtConcurrent::run(&ClassC::process, &classC);
#endif
	FutureWrapper future_wrapper(&progress_mgr);
	QFutureWatcher<void> future_watcher;
	// Optional : hide progress manager interface when finished
	QObject::connect(&future_watcher, SIGNAL(finished()), &future_wrapper, SLOT(hide()));

	future_watcher.setFuture(future);

    return app.exec();

}

