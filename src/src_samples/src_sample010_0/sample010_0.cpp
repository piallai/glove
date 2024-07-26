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

/*! Example to monitor the progress feedback of an algorithm using a function and progressions.*/

#include <QApplication>

#include <QtConcurrent/QtConcurrentRun>
#include <QFutureWatcher>
#include <QLayout>// to change GlvProgressMgr layout behaviour for example

#include <chrono>// for computation simulation
#include <thread>// for computation simulation

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "SlvProgressionQt.h"
#else
#include "glove.h"
#endif

SlvProgressionQt progression1("Loop 1");
SlvProgressionQt progression2("Loop 2");
SlvProgressionQt progression3("Loop 3");

void process(unsigned int _Niterations) {

	unsigned int i = 0;
	progression1.emit_start("Processing", &i, _Niterations);
	for (i = 0; i < _Niterations; i++) {

		unsigned int j = 0;
		progression2.emit_start("Processing", &j, _Niterations);
		for (j = 0; j < _Niterations; j++) {

			unsigned int k = 0;
			progression3.emit_start("Processing", &k, _Niterations);
			for (k = 0; k < _Niterations; k++) {

				// Simulates computation
				std::this_thread::sleep_for(std::chrono::milliseconds(10));

				progression3.emit_progress();

			}

			progression2.emit_progress();

		}

		progression1.emit_progress();

	}

}

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvProgressMgr.h"
#endif

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

	GlvProgressMgr progress_mgr;
	progress_mgr.add_progression(&progression1);
	progress_mgr.add_progression(&progression2);
	progress_mgr.add_progression(&progression3);
	progress_mgr.show();

	// Example for fixed size
	progress_mgr.setFixedWidth(420);
	progress_mgr.layout()->setSizeConstraint(QLayout::SetFixedSize);

	QFuture<void> future = QtConcurrent::run(&process, 100);
	QFutureWatcher<void> future_watcher;

	future_watcher.setFuture(future);

    return app.exec();

}

