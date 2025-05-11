/*
* This file is part of the Glove distribution (https://github.com/piallai/glove).
* Copyright (C) 2024 - 2025 Pierre Allain.
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

/*! Example of how to save a QTreeView expansion state.
! glv::view::get_tree_expansions
! glv::view::set_tree_expansions*/

#include <QApplication>

#include <QTreeWidget>
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "glv_QTreeView.h"
#else
#include "glove.h"
#endif

void recursion(QTreeWidgetItem* _item, int _Nchildren_max, int _depth = 0) {

    int Nchildren;
    if (_depth < 2) {
        Nchildren = _Nchildren_max;
    } else {
        //std::cout << "_Nchildren_max = " << _Nchildren_max << std::endl;
        //std::cout << "rand() = " << rand() << std::endl;
        Nchildren = rand() % (_Nchildren_max + 1);
        //std::cout << "Nchildren = " << Nchildren << std::endl;
    }
    
    for (int i = 0; i < Nchildren; i++) {
        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0, QString::number(i));
        _item->addChild(item);
        recursion(item, _Nchildren_max, _depth + 1);
    }

}

#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
class QTreeWidgetDialog : public QDialog {
public:
    QTreeWidget* tree_widget;
    QTreeWidgetDialog() {
        QVBoxLayout* layout = new QVBoxLayout;
        setLayout(layout);
        tree_widget = new QTreeWidget;
        QTreeWidgetItem* item = new QTreeWidgetItem;
        srand(time(NULL));
        recursion(item, 2);
        tree_widget->addTopLevelItem(item);
        layout->addWidget(tree_widget);

        QDialogButtonBox* button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        layout->addWidget(button_box);
        connect(button_box, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
    }

};

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    QTreeWidgetDialog tree_dialog_widget;

    int result = tree_dialog_widget.exec();
    if (result == QDialog::Accepted) {

        glv::view::Ttree_expansions tree_expansions = glv::view::get_tree_expansions(tree_dialog_widget.tree_widget);

        tree_dialog_widget.tree_widget->collapseAll();

        result = tree_dialog_widget.exec();
        if (result == QDialog::Accepted) {

            glv::view::set_tree_expansions(tree_dialog_widget.tree_widget, tree_expansions);

            tree_dialog_widget.exec();
        }

    }

    return app.exec();

}

