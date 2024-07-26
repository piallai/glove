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

/*! Example to monitor the progress feedback of an algorithm in a method of a class.
* Advanced example, using multiple progressions, OMP, and progression deletion.
* 
ClassD::process | ClassE::process | 
                |                 | Loop/progress
                | Extra progression being deleted |
                |                             |  Loop/progress
                | Loop/progress | 
                                | ClassC::process |
                                                  | Loop/progress
*/

#include <QApplication>

#include "ClassD.h"
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvProgressMgr.h"
#endif
#include <QtConcurrent/QtConcurrentRun>
#include <QFutureWatcher>
#include "FutureWrapper.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

	ClassD classD(1000);
	GlvProgressMgr progress_mgr;
	progress_mgr.add_progression(classD.get_progression());
	progress_mgr.add_progression(classD.classC.get_progression(), true);// Up to the user, but can create glitches by continuously hiding/displaying the progression
	progress_mgr.add_progression(classD.classE.get_progression());
	progress_mgr.add_progression(classD.progression_ptr);
	progress_mgr.show(); 
	progress_mgr.setFixedWidth(420);

#if QT_VERSION_MAJOR < 6
	QFuture<void> future = QtConcurrent::run(&classD, &ClassD::processOMP);// or &ClassD::processOMP
#else
	QFuture<void> future = QtConcurrent::run( &ClassD::processOMP, &classD);// or &ClassD::processOMP
#endif
	FutureWrapper future_wrapper(&progress_mgr);
	QFutureWatcher<void> future_watcher;
	// Optional : hide progress manager interface when finished
	QObject::connect(&future_watcher, SIGNAL(finished()), &future_wrapper, SLOT(hide()));

	future_watcher.setFuture(future);

    return app.exec();

}

