/*
* This file is part of the Glove distribution (https://github.com/piallai/glove).
* Copyright (C) 2022 Pierre Allain.
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

#ifdef OPTION_SINGLE_HEADER
#include "glove.h"
#else
#include "param/SlvParametrization5.h"
#include "SlvProgression.h"
#include "filestream/SlvFile.h"
#endif
#include "CImg.h"

glvm_SlvEnum(BoundaryCondition, Dirichlet, Neumann, Periodic, Mirror)

class ImageConvolution : public SlvParametrization5<SlvFile, unsigned int, std::vector< std::vector<float> >, bool, BoundaryCondition>, public SlvProgression {

	glvm_parametrization5_init("Image convolution")

	glvm_parameter(1, image_path, SlvFile, "Image to load", "Path to image. Allowed extensions: .jpg and .png", SlvFile(SlvFileExtensions(std::vector<SlvFileExtension>({ ".jpg", ".png"})), SlvFile::IO::Read, std::string("Image file")))
	glvm_parameter_ruled(2, Niterations, unsigned int, "Number of iterations", "Number of times the convolution will be processed on the image.", 100)
	glvm_parameter_add_rule(max, 1000)
	glvm_parameter_end
	glvm_staticVariable(const, std::vector< std::vector<float> >, default_kernel, std::vector< std::vector<float> >({ {0.5, 1., 0.5}, {1., 2., 1.}, {0.5, 1., 0.5} }))
	glvm_parameter(3, kernel, std::vector< std::vector<float> >, "Kernel", "Convolution kernel.", default_kernel())
	glvm_parameter(4, normalization, bool, "Kernel normalization", "Normalize the kernel by the sum of the weights.", true)
	glvm_parameter(5, boundary_condition, BoundaryCondition, "Boundary conditions", "Boundary conditions applied to the kernel.", BoundaryCondition::Neumann)

public:

	cimg_library::CImg<float> image;//for processing
	cimg_library::CImg<unsigned char> image_permuted;//for direct display refresh

	ImageConvolution() : glvm_parametrization_constructor(image_path, Niterations, kernel, normalization, boundary_condition) {}

	void load_image() {
		image.load(get_image_path().get_path().c_str());
		image_permuted = image.get_permute_axes("cxyz");
	}
	
	void process() {

		cimg_library::CImg<float> kernel_img((unsigned int)get_kernel()[0].size(), (unsigned int)get_kernel().size());
		float sum = 0.f;
		for (int i = 0; i < get_kernel()[0].size(); i++) {
			for (int j = 0; j < get_kernel().size(); j++) {
				kernel_img(j, i) = get_kernel()[i][j];
				if (get_normalization()) {
					sum += kernel_img(j, i);
				}
			}
		}
		if (get_normalization()) {
			for (int i = 0; i < get_kernel()[0].size(); i++) {
				for (int j = 0; j < get_kernel().size(); j++) {
					kernel_img(j, i) /= sum;
				}
			}
		}

		unsigned int i = 0;
		get_progression()->emit_start("Processing ClassC", &i, get_Niterations());
		for (i = 0; i < get_Niterations(); i++) {
			image.convolve(kernel_img, (int)get_boundary_condition(), false);
			image.cut(0.f, 255.f);
			image_permuted = image.get_permute_axes("cxyz");
			get_progression()->emit_progress();

		}
	}

};

// No Qt up to here

#ifndef OPTION_SINGLE_HEADER
#include "GlvParametrizationDialog.h"
#include "GlvProgressMgr.h"

#include "GlvWidgetData_spec_SlvFile.h"
#include "GlvWidgetData_spec_AT.h"
#include "GlvWidgetData_spec_std_container_container.h"
#include "GlvWidgetData_spec_SlvEnum.h"

#include <QPainter>
#include <QApplication>
#endif

#include <QtConcurrent/QtConcurrentRun>
#include <QFutureWatcher>

class ImageWidget : public QWidget {
	QImage qimage;
public :
	ImageWidget(unsigned char* _data, int _width, int _height, QImage::Format _format):qimage(_data, _width, _height, _format) {}
	void paintEvent(QPaintEvent*) {
		QPainter painter(this);
		painter.drawImage(QPoint(0, 0), qimage);
		painter.end();
	}
};

#ifndef OPTION_SINGLE_HEADER
// Optional : display image values in a table
#include "GlvTableView.h"
#include "glv_QStandardItemModelMaker_spec_std_container.h"
#endif

int main(int argc, char* argv[]) {

	QApplication app(argc, argv);

	GlvParametrizationDialog<ImageConvolution> dialog;

	QFuture<void> future;
	QFutureWatcher<void> future_watcher;

	ImageWidget* image_widget;
	
	if (dialog.exec() == 1) {

		ImageConvolution* image_convolution = new ImageConvolution;
		*image_convolution = dialog.get_parametrization();

		if (image_convolution->get_image_path().exists()) {

			image_convolution->load_image();


			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Optional : display image values in a table
			if (false) {
				typedef std::vector< std::vector< std::vector<unsigned short int> > > Timage_table;
				Timage_table image_table;
				image_table.resize(image_convolution->image.width());
				for (int i = 0; i < image_table.size(); i++) {
					image_table[i].resize(image_convolution->image.height());
					for (int j = 0; j < image_table[i].size(); j++) {
						image_table[i][j].resize(image_convolution->image.spectrum());
					}
				}
				cimg_forXYC(image_convolution->image, i, j, c) {
					image_table[i][j][c] = image_convolution->image(i, j, c);
				}
				GlvTableView<Timage_table>* image_table_widget = new GlvTableView<Timage_table>(image_table);
				image_table_widget->show();
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////////


			
			image_widget = new ImageWidget((unsigned char*)image_convolution->image_permuted.data(), image_convolution->image.width(), image_convolution->image.height(), QImage::Format_RGB888);
			image_widget->show();

			GlvProgressMgr* progress = new GlvProgressMgr;
			progress->add_progression(image_convolution->get_progression());
			progress->show();
#if QT_VERSION_MAJOR < 6
			future = QtConcurrent::run(image_convolution, &ImageConvolution::process);
#else
			future = QtConcurrent::run(&ImageConvolution::process, image_convolution);
#endif
			QObject::connect(image_convolution->get_progression(), SIGNAL(progress_signal(int)), image_widget, SLOT(update()));
			future_watcher.setFuture(future);
		}

		
	}
	 
	return app.exec();
}
