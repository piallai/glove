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

/*! Example of how to use table view with SlvPool.*/

#include <QApplication>

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "SlvPool.h"
#include "GlvTableView.h"
#include "glv_QStandardItemModelMaker_spec_SlvPool.h"
#else
#include "glove.h"
#endif

// Simple SlvPool element: must inherit SlvLabeling. Here, int is the 'key'.
// Input/output in item view depends on operator>> and operator<<
struct Element : public SlvLabeling<int> {
    std::string value;
    Element(int _label = 0):SlvLabeling(_label) {}
    Element& operator=(const Element& _element) {
        value = _element.value;
        return *this;
    }

    friend std::istream& operator>>(std::istream& _is, Element& _element) {
        _is >> _element.value;
        return _is;
    }

private:
    // Because inherits SlvOS
    void ostream(std::ostream& _os) const {
        _os << value;
    }

};

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvTableDialog.h"
#endif

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    SlvPool<Element> pool;
    pool.new_element(10)->value = "CCC";
    pool.new_element(0)->value = "AAA";
    pool.new_element(2)->value = "BBB";

    // Simple display of a pool
    GlvTableView< SlvPool<Element> >* table_view = new GlvTableView< SlvPool<Element> >(pool);
    table_view->show();

    //////////////////////////////////////////////////////////////////////////////////////

    // Display of a pool with edited output after validation (hence the QDialog)
    GlvTableDialog< SlvPool<Element> > pool_widget;
    pool_widget.get_widget()->set_value(pool);

    if (pool_widget.exec()) {
        std::cout << pool_widget.get_widget()->get_value() << std::endl;
    }

    return app.exec();

}

