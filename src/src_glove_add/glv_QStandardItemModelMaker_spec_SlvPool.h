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

#pragma once

#include "glv_QStandardItem.h"
#include "SlvPool.h"
#include "misc/spec/SlvDataName_spec_SlvPool.h"

/*! Specialization of QStandardItemModelMaker for SlvPool.
First column: label.
Second colum: value.*/
#include "GlvStandardItem.h"
template <class Tvalue, class Tlabel>
struct glv::tdata::QStandardItemModelMaker< SlvPool<Tvalue, Tlabel> > {
    static constexpr bool is_specialized = true;
    typedef Tvalue Tdata_sub;
private:
    static QString get_root_text(unsigned int _size) {
        return glv::toQString(SlvDataName< SlvPool<Tvalue> >::name()) + " : " + QString::number(_size);
    }
public:
    static void make(const SlvPool<Tvalue, Tlabel>& _pool, QStandardItemModel* _model, const QModelIndex _index = QModelIndex(), const Qt::ItemFlag _flag_additional = Qt::NoItemFlags) {

        if (_model && (_index == QModelIndex() || _index.model() == _model)) {

            glv::resize(_model, (unsigned int)(_pool.psize()), 2, _index);

            QModelIndex index;
            for (unsigned int i = 0; i < _pool.psize(); i++) {
                index = _model->index(i, 0, _index);
                glv::tdata::toQStandardItem(_pool[i]->get_label(), _model->itemFromIndex(index));
                _model->itemFromIndex(index)->setFlags(_model->itemFromIndex(index)->flags() | _flag_additional);

                // If Tvalue is specialized, disable Tkey editing
                static bool condition = glv::tdata::QStandardItemModelMaker<Tlabel>::is_specialized || (glv::tdata::QStandardItemModelMaker<Tvalue>::is_specialized && !glv::tdata::l_allow_type_mismatch_edit);
                // C4127
                if (condition) {
                    _model->itemFromIndex(index)->setFlags(_model->itemFromIndex(index)->flags() ^ Qt::ItemIsEditable);
                }
                if (!std::is_same<Tlabel, Tvalue>::value) {
                    _model->itemFromIndex(index)->setFlags(_model->itemFromIndex(index)->flags() | glv::tdata::type_mismatch_flag);
                }
                index = _model->index(i, 1, _index);
                glv::tdata::toQStandardItem(*_pool[i], _model->itemFromIndex(index));
                _model->itemFromIndex(index)->setFlags(_model->itemFromIndex(index)->flags() | _flag_additional);
            }

            if (_index != QModelIndex()) {
                QString root_text = get_root_text((unsigned int)(_pool.psize()));
                if (_model->itemFromIndex(_index)->text() != root_text) {
                    _model->itemFromIndex(_index)->setText(root_text);
                }
            }

        }

    }

    static SlvPool<Tvalue, Tlabel> get_value(const QStandardItemModel* _model, const QModelIndex& _index, const int _Mrows, const int _Ncols) {

        SlvPool<Tvalue, Tlabel> pool;

        if (_index == QModelIndex() || _index.model() == _model) {

            int N = (_Mrows == -1) ? _model->rowCount(_index) : std::min(_model->rowCount(_index), _Mrows);

            if (_model->columnCount(_index) >= 2) {

                QStandardItem* item;
                Tvalue* value;
                for (int i = 0; i < N; i++) {
                    item = _model->itemFromIndex(_model->index(i, 0, _index));
                    value = pool.new_element(glv::tdata::fromQStandardItem<Tlabel>(item));
                    item = _model->itemFromIndex(_model->index(i, 1, _index));
                    *value = glv::tdata::fromQStandardItem<Tvalue>(item);
                }

            } else {
                slv::flag::ISSUE(slv::flag::Critical, "SlvPool requires two columns in the model");
            }

        } else {
            slv::flag::ISSUE(slv::flag::Critical, "index's model is different from the one it is supposed to belong to");
        }

        return pool;
    }

    static std::vector<int> get_coordinates(QModelIndex& _index) {

        std::vector<int> coordinates = glv::tdata::QStandardItemMaker<Tvalue>::get_coordinates(_index);
        coordinates.insert(coordinates.begin(), _index.column());
        coordinates.insert(coordinates.begin(), _index.row());

        _index = _index.parent();

        return coordinates;
    }

};
