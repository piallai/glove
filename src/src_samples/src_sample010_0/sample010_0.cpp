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

#include <QLayout>// to change GlvProgressMgr layout behaviour for example

#include <chrono>// for computation simulation
#include <thread>// for computation simulation

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "SlvProgressionQt.h"
#include <QtConcurrent/QtConcurrentRun>
#include <QFutureWatcher>
#else
#include "glove.h"
#endif

SlvProgressionQt progression0("Loop 0");
SlvProgressionQt progression1("Loop 1");
SlvProgressionQt progression2("Loop 2");
SlvProgressionQt progression3("Loop 3");

void process1(unsigned int _Niterations) {

	progression0.start();// No progress bar for this one
	// Simulates computation
	std::this_thread::sleep_for(std::chrono::milliseconds(_Niterations * 50));
	progression0.end();

	if (!progression0.was_canceled()) {

		progression1.set_message("Processing");
		SlvProgressionQt& i = progression1;
		for (i = 0; i << _Niterations; i++) {

			progression2.set_message("Processing");
			SlvProgressionQt& j = progression2;
			for (j = 0; j << _Niterations; j++) {

				progression3.set_message("Processing");
				SlvProgressionQt& k = progression3;
				for (k = 0; k << _Niterations; k++) {

					// Simulates computation
					std::this_thread::sleep_for(std::chrono::milliseconds(10));

				}

			}

		}

	}

}

void process2(unsigned int _Niterations) {

	progression0.start();// No progress bar for this one
	// Simulates computation
	std::this_thread::sleep_for(std::chrono::milliseconds(_Niterations * 50));
	progression0.end();

	if (!progression0.was_canceled()) {

		std::size_t i = 0;
		progression1.set_message("Processing");
		progression1.start(&i, _Niterations);
		for (i = 0; i < _Niterations; i++) {

			unsigned int j = 0;
			progression2.set_message("Processing");
			progression2.start(&j, _Niterations);
			for (j = 0; j < _Niterations; j++) {

				std::size_t k = 0;
				progression3.set_message("Processing");
				progression3.start(&k, _Niterations);
				for (k = 0; k < _Niterations; k++) {

					// Simulates computation
					std::this_thread::sleep_for(std::chrono::milliseconds(10));

					progression3.update();

				}

				progression2.update();

			}

			progression1.update();

		}

	}

}

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvProgressMgr.h"
#endif

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

	GlvProgressMgr progress_mgr;
	progress_mgr.add_progression(&progression0, true);
	progress_mgr.add_progression(&progression1);
	progress_mgr.add_progression(&progression2);
	progress_mgr.add_progression(&progression3);
	progress_mgr.show();

	QFuture<void> future = QtConcurrent::run(&process1, 100);// use process1 or process2
	QFutureWatcher<void> future_watcher;

	future_watcher.setFuture(future);

    return app.exec();

}

