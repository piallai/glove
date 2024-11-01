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

#include <QApplication>

#include <QtGlobal>//for Qt version

#ifdef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "glove.h"
#else
#include "GlvWidgetData_spec_std_pair.h"
#include "GlvParametrizationDialog.h"
#include "GlvWidgetData_spec_AT.h"
#include "GlvWidgetData_spec_std_string.h"
#include "GlvWidgetData_spec_SlvParametrization.h"
#include "GlvWidgetData_spec_SlvProportion.h"
#include "GlvWidgetData_spec_SlvFile.h"
#include "GlvWidgetData_spec_SlvEnum.h"
#include "GlvWidgetData_spec_SlvDirectory.h"

//#include "GlvWidgetData_spec_std_pair.h"
#include "GlvWidgetData_spec_std_vector.h"
#endif

#include "ClassA.h"
#include "ClassB.h"

// Progression example
#include "ClassC.h"
#include "ClassD.h"

#ifdef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "glove.h"
#else
#include "GlvProgressMgr.h"
#include <QtConcurrent/QtConcurrentRun>
#include <QFutureWatcher>
#endif
#include "FutureWrapper.h"

// Parametrization widget connections
#include "QtSlotsExample.h"

/* The main program provides examples using the library as a developer sandbox.*/

glvm_SlvEnum(EnumTest, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)

typedef std::pair<int, double> Tpair;

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrizationMacro.h"
#endif
glvm_parametrization(ClassW, "ClassW",	paramA, std::string, "paramA", "comment parameterA", "default")
glvm_parametrization(ClassX, "ClassX",
										paramA, ClassW, "paramA", "comment parameterA", ClassW(),
										paramB, Tpair, "paramB", "comment parameter B", Tpair())
glvm_parametrization(ClassT, "ClassT",
										paramA, ClassW, "paramA", "comment parameterA", ClassW(),
										paramB, std::vector<double>, "paramB", "comment parameter B", {},
										paramC, std::string, "paramC", "comment parameter C", "default",
										paramD, EnumTest, "paramD", "comment parameter D", EnumTest::a,
										paramE, std::string, "paramE", "comment parameter E", "default",
										paramF, double, "paramF", "comment parameter F", 0.,
										paramG, std::string, "paramG", "comment parameter G", "default",
										paramH, double, "paramH", "comment parameter H", 0.,
										paramI, std::string, "paramI", "comment parameter I", "default",
										paramJ, int, "paramJ", "comment parameter J", 0,
										paramK, double, "paramK", "comment parameter K", 0.,
										paramL, ClassX, "paramL", "comment parameter L", ClassX(),
										paramM, std::string, "paramM", "comment parameter M", "default",
										paramN, std::string, "paramN", "comment parameter N", "default")

glvm_parametrization(ClassK, "ClassK",	paramA, ClassW, "paramA", "comment parameterA", ClassW())
glvm_parametrization(ClassL, "ClassL",
										paramA, ClassW, "paramA", "comment parameterA", ClassW(),
										paramB, double, "paramB", "comment parameter B", 0.)
glvm_parametrization(ClassM, "ClassM", 
										paramA, ClassW, "paramA", "comment parameterA", ClassW(),
										paramB, double, "paramB", "comment parameter B", 0.,
										paramC, double, "paramC", "comment parameter C", 0.)

glvm_parametrization(ClassBig, "ClassBig",
	paramA, float, "big", "comment parameter", 0.f,
	paramB, float, "big", "comment parameter", 0.f,
	paramC, float, "big", "comment parameter", 0.f,
	paramD, float, "big", "comment parameter", 0.f,
	paramE, float, "big", "comment parameter", 0.f,
	paramF, float, "big", "comment parameter", 0.f,
	paramG, float, "big", "comment parameter", 0.f,
	paramH, float, "big", "comment parameter", 0.f,
	paramI, float, "big", "comment parameter", 0.f,
	paramJ, float, "big", "comment parameter", 0.f,
	paramK, float, "big", "comment parameter", 0.f,
	paramL, float, "big", "comment parameter", 0.f,
	paramM, float, "big", "comment parameter", 0.f,
	paramN, float, "big", "comment parameter", 0.f,
	paramO, float, "big", "comment parameter", 0.f,
	paramP, float, "big", "comment parameter", 0.f,
	paramQ, float, "big", "comment parameter", 0.f,
	paramR, float, "big", "comment parameter", 0.f,
	paramS, float, "big", "comment parameter", 0.f,
	paramT, float, "big", "comment parameter", 0.f,
	paramU, float, "big", "comment parameter", 0.f,
	paramV, float, "big", "comment parameter", 0.f,
	paramW, float, "big", "comment parameter", 0.f,
	paramX, float, "big", "comment parameter", 0.f)

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvParametrizationSaveLoad.h"
#endif

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

	GlvParametrizationDialog<ClassM>* parametrization_classM = new GlvParametrizationDialog<ClassM>();
	parametrization_classM->show();

	GlvParametrizationDialog<ClassT>* parametrization_classT = new GlvParametrizationDialog<ClassT>();
	parametrization_classT->show();

	GlvParametrizationDialog<ClassBig>* parametrization_classBig = new GlvParametrizationDialog<ClassBig>();
	parametrization_classBig->show();

	QtSlotsExample qtslots;
	auto widget1 = glvm_get_parameter_GlvWidgetData(parametrization_classT->get_parametrization_widget(), 4);
	auto widgetx = glvm_get_parameter_GlvWidget(parametrization_classT->get_parametrization_widget(), 4);
	QObject::connect(widget1, SIGNAL(currentTextChanged(QString)), &qtslots, SLOT(get(QString)));
	QObject::connect(parametrization_classT->get_parametrization_widget(), SIGNAL(parameterChanged(std::string)), &qtslots, SLOT(get(std::string)));
	//parametrization_classT->get_parametrization_widget()->enable_data_type_info(false);

	/*GlvParametrizationDialog<ClassW>* parametrization_classW = new GlvParametrizationDialog<ClassW>();
	parametrization_classW->show();

	GlvParametrizationDialog<ClassX>* parametrization_classX = new GlvParametrizationDialog<ClassX>();
	parametrization_classX->show();*/

	GlvParametrizationDialog<ClassZ>* parametrization_classZ = new GlvParametrizationDialog<ClassZ>();
	parametrization_classZ->show();

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Main example
	GlvParametrizationDialog<ClassA>* parametrization_classA = new GlvParametrizationDialog<ClassA>();
	parametrization_classA->show();


	GlvParametrizationDialog<ClassB>* parametrization_classB = new GlvParametrizationDialog<ClassB>();
	GlvParametrizationSaveLoad<ClassB>* save_load_widget = new GlvParametrizationSaveLoad<ClassB>(parametrization_classB->get_parametrization_widget());

	int result = parametrization_classB->exec();

	if (result == QDialog::Accepted) {

		ClassB classB = parametrization_classB->get_parametrization();

		std::cout << "classB : " << classB << std::endl;

	}
	////////////////////////////////////////////////////////////////////////////////////////////////

	// Watching example

#ifdef other_example
	// Second example
	// ////////////////////////////////////////////////////////////////////////////////////////////////
	// Double Watching example
	ClassD classD(10);
	// Warning : in this example, closing the progress_mgr widget will go to the end of the main where classD is destroyed, causing crash with QtConcurrent::run
	GlvProgressMgr progress_mgr;
	//progress_mgr.show();
	progress_mgr.add_progression(classD.progression);
	progress_mgr.add_progression(classD.classC.progression);
	progress_mgr.show();
	//QtConcurrent::run(&classD, &ClassD::process);

	QFuture<void> future = QtConcurrent::run(&classD, &ClassD::process);
	FutureWrapper future_wrapper(&progress_mgr);
	QFutureWatcher<void> future_watcher;
	QObject::connect(&future_watcher, SIGNAL(finished()), &future_wrapper, SLOT(hide()));

	future_watcher.setFuture(future);
	////////////////////////////////////////////////////////////////////////////////////////////////
#endif


	ClassD classD(10);
	GlvProgressMgr progress_mgr;
	progress_mgr.add_progression(classD.get_progression());
	progress_mgr.add_progression(classD.classC.get_progression());
	progress_mgr.show();


#if QT_VERSION_MAJOR < 6
	QFuture<void> future = QtConcurrent::run(&classD, &ClassD::process);
#else
	QFuture<void> future = QtConcurrent::run(&ClassD::process, &classD);
#endif
	FutureWrapper future_wrapper(&progress_mgr);
	QFutureWatcher<void> future_watcher;

	future_watcher.setFuture(future);


    return app.exec();

}

