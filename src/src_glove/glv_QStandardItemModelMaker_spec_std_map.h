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
#include "std_map.h"
#include "misc/spec/SlvDataName_spec_std_map.h"

/*! Specialization of QStandardItemModelMaker for std::map.*/
#include "GlvStandardItem.h"
template <class Tkey, class Tvalue>
struct glv::tdata::QStandardItemModelMaker< std::map<Tkey, Tvalue> > {
    static constexpr bool is_specialized = true;
    typedef Tvalue Tdata_sub;
private:
    static QString get_root_text(unsigned int _size) {
        return glv::toQString(SlvDataName< std::map<Tkey, Tvalue> >::name()) + " : " + QString::number(_size);
    }
public:
    static void make(const std::map<Tkey, Tvalue>& _map, QStandardItemModel* _model, const QModelIndex _index = QModelIndex(), const Qt::ItemFlag _flag_additional = Qt::NoItemFlags) {

        if (_model && (_index == QModelIndex() || _index.model() == _model)) {

            glv::resize(_model, (unsigned int)_map.size(), 2, _index);

            QModelIndex index;
            int i = 0;
            for (typename std::map<Tkey, Tvalue>::const_iterator it = _map.begin(); it != _map.end(); ++it, i++) {
                index = _model->index(i, 0, _index);
                glv::tdata::toQStandardItem(it->first, _model->itemFromIndex(index));

                _model->itemFromIndex(index)->setFlags(_model->itemFromIndex(index)->flags() | _flag_additional);
                
                // If Tvalue is specialized, disable Tkey editing
                static bool condition = glv::tdata::QStandardItemModelMaker<Tkey>::is_specialized || (glv::tdata::QStandardItemModelMaker<Tvalue>::is_specialized && !glv::tdata::l_allow_type_mismatch_edit);
                // C4127
                if (condition) {
                    _model->itemFromIndex(index)->setFlags(_model->itemFromIndex(index)->flags() ^ Qt::ItemIsEditable);
                }
                if (!std::is_same<Tkey, Tvalue>::value) {
                    _model->itemFromIndex(index)->setFlags(_model->itemFromIndex(index)->flags() | glv::tdata::type_mismatch_flag);
                }

                index = _model->index(i, 1, _index);
                glv::tdata::toQStandardItem(it->second, _model->itemFromIndex(index));
                _model->itemFromIndex(index)->setFlags(_model->itemFromIndex(index)->flags() | _flag_additional);
            }

            if (_index != QModelIndex()) {
                QString root_text = get_root_text((unsigned int)_map.size());
                if (_model->itemFromIndex(_index)->text() != root_text) {
                    _model->itemFromIndex(_index)->setText(root_text);
                }
            }

        }

    }

    static std::map<Tkey, Tvalue> get_value(const QStandardItemModel* _model, const QModelIndex& _index, const int _Mrows, const int _Ncols) {

        std::map<Tkey, Tvalue> map;

        if (_index == QModelIndex() || _index.model() == _model) {

            int N = (_Mrows == -1) ? _model->rowCount(_index) : std::min(_model->rowCount(_index), _Mrows);

            if (_model->columnCount(_index) >= 2) {

                QStandardItem* item;
                Tkey key;
                Tvalue value;
                typename std::map<Tkey, Tvalue>::iterator it;
                for (int i = 0; i < N; i++) {
                    item = _model->itemFromIndex(_model->index(i, 0, _index));
                    key = glv::tdata::fromQStandardItem<Tkey>(item);
                    it = map.find(key);
                    if (it == map.end()) {
                        item = _model->itemFromIndex(_model->index(i, 1, _index));
                        value = glv::tdata::fromQStandardItem<Tvalue>(item);
                        map[key] = value;
                    } else {
                        // key already exists
                    }
                }

            } else {
                slv::flag::ISSUE(slv::flag::Critical, "std::map requires two columns in the model");
            }

        } else {
            slv::flag::ISSUE(slv::flag::Critical, "index's model is different from the one it is supposed to belong to");
        }

        return map;
    }

    static std::vector<int> get_coordinates(QModelIndex& _index) {

        std::vector<int> coordinates = glv::tdata::QStandardItemMaker<Tvalue>::get_coordinates(_index);
        coordinates.insert(coordinates.begin(), _index.column());
        coordinates.insert(coordinates.begin(), _index.row());

        _index = _index.parent();

        return coordinates;
    }

};
