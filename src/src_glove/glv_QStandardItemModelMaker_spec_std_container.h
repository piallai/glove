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

#pragma once

#include "glv_QStandardItem.h"
#include "slv_flag.h"
#include "SlvIsContainer.h"
#include "SlvIsMap.h"

// Containers, except std::map, std::unordered_map and std::string
#define Tenable typename std::enable_if<SlvIsContainer<Tcontainer>::value && !SlvIsMap<Tcontainer>::value && !std::is_same<Tcontainer, std::string>::value>::type
#define Tenable_sub typename std::enable_if<SlvIsContainer<typename _Tcontainer::value_type>::value && !SlvIsMap<typename _Tcontainer::value_type>::value && !std::is_same<typename _Tcontainer::value_type, std::string>::value>::type

/*! Specialization of QStandardItemModelMaker for std::vector, std::list, std::deque, std::array.*/
template <class Tcontainer>
struct glv::tdata::QStandardItemModelMaker<Tcontainer, Tenable> {
    static constexpr bool is_specialized = true;
private:
    template <class _Tcontainer, typename = void>
    struct ContainerHandler;
    template <class _Tcontainer, typename = void>
    struct ContainerHandlerResize;
public:
    typedef typename ContainerHandler<Tcontainer>::Tdata_sub Tdata_sub;
private:
    static QString get_root_text(unsigned int _Mrows, unsigned int _Ncols);
public:
    static void make(const Tcontainer& _container, QStandardItemModel* _model, const QModelIndex _index = QModelIndex(), const Qt::ItemFlag _flag_additional = Qt::NoItemFlags);

    static Tcontainer get_value(const QStandardItemModel* _model, const QModelIndex& _index, const int _Mrows, const int _Ncols);

    static std::vector<int> get_coordinates(QModelIndex& _index);
};

template <class Tcontainer>
template <class _Tcontainer, typename>
struct glv::tdata::QStandardItemModelMaker<Tcontainer, Tenable>::ContainerHandlerResize {
    static void resize(_Tcontainer& _container, int _size) {
        _container.resize(_size);
    }
};

#include "SlvHasMethod.h"
glvm_SlvHasMethodSignature(SlvHasResize, void, resize, 0)

template <class Tcontainer>
template <class _Tcontainer>
struct glv::tdata::QStandardItemModelMaker<Tcontainer, Tenable>::ContainerHandlerResize<_Tcontainer, typename std::enable_if<!SlvHasResize<_Tcontainer>::value>::type> {
    static void resize(_Tcontainer& _container, int _size) {
        
    }
};

template <class Tcontainer>
template <class _Tcontainer, typename>
struct glv::tdata::QStandardItemModelMaker<Tcontainer, Tenable>::ContainerHandler {

    typedef typename Tcontainer::value_type Tdata_sub;

    static std::size_t get_size(const Tcontainer& _container) {
        return 1;
    }

    static void set_model(const typename Tcontainer::value_type& _value, int _i, QStandardItemModel* _model, const QModelIndex& _index, const Qt::ItemFlag _flag_additional) {

        QModelIndex index;
        index = _model->index(_i, 0, _index);
        glv::tdata::toQStandardItem(_value, _model->itemFromIndex(index));
        _model->itemFromIndex(index)->setFlags(_model->itemFromIndex(index)->flags() | _flag_additional);

    }

    static void resize(typename Tcontainer::value_type& _value, int _Ncols) {

    }

    static void get_value(typename Tcontainer::value_type& _value, int _i, const QStandardItemModel* _model, const QModelIndex& _index) {

        QStandardItem* item = _model->itemFromIndex(_model->index(_i, 0, _index));
        _value = glv::tdata::fromQStandardItem<typename Tcontainer::value_type>(item);

    }

    static void add_coordinate(std::vector<int>& _coordinates, QModelIndex& _index) {

    }

};

template <class Tcontainer>
template <class _Tcontainer>
struct glv::tdata::QStandardItemModelMaker<Tcontainer, Tenable>::ContainerHandler<_Tcontainer, Tenable_sub> {

    typedef typename Tcontainer::value_type::value_type Tdata_sub;

    static std::size_t get_size(const Tcontainer& _data) {
        std::size_t size = 0;
        for (typename Tcontainer::const_iterator it = _data.begin(); it != _data.end(); ++it) {
            if (it->size() > size) {
                size = it->size();
            }
        }
        return size;
    }

    static void set_model(const typename Tcontainer::value_type& _value, int _i, QStandardItemModel* _model, const QModelIndex& _index, const Qt::ItemFlag _flag_additional) {

        QModelIndex index;
        int j = 0;
        for (typename Tcontainer::value_type::const_iterator it = _value.begin(); it != _value.end(); ++it, j++) {
            index = _model->index(_i, j, _index);
            glv::tdata::toQStandardItem(*it, _model->itemFromIndex(index));
            _model->itemFromIndex(index)->setFlags(_model->itemFromIndex(index)->flags() | _flag_additional);
        }

    }

    static void resize(typename Tcontainer::value_type& _value, int _Ncols) {

        ContainerHandlerResize<typename Tcontainer::value_type>::resize(_value, _Ncols);

    }

    static void get_value(typename Tcontainer::value_type& _value, int _i, const QStandardItemModel* _model, const QModelIndex& _index) {

        QStandardItem* item;
        int j = 0;
        for (typename Tcontainer::value_type::iterator it = _value.begin(); it != _value.end(); ++it, j++) {
            item = _model->itemFromIndex(_model->index(_i, j, _index));
            *it = glv::tdata::fromQStandardItem<typename Tcontainer::value_type::value_type>(item);
        }

    }

    static void add_coordinate(std::vector<int>& _coordinates, QModelIndex& _index) {

        _coordinates.insert(_coordinates.begin(), _index.column());

    }

};


template <class Tcontainer>
QString glv::tdata::QStandardItemModelMaker<Tcontainer, Tenable>::get_root_text(unsigned int _Mrows, unsigned int _Ncols) {
    return QString::number(_Mrows) + "x" + QString::number(_Ncols);
}

template <class Tcontainer>
void glv::tdata::QStandardItemModelMaker<Tcontainer, Tenable>::make(const Tcontainer& _container, QStandardItemModel* _model, const QModelIndex _index, const Qt::ItemFlag _flag_additional) {

    if (_model) {

        if (_index == QModelIndex() || _index.model() == _model) {

            unsigned int Mrows = (unsigned int)_container.size();
            glv::resize_rows(_model, Mrows, _index);
            unsigned int Ncols = (unsigned int)ContainerHandler<Tcontainer>::get_size(_container);
            glv::resize_cols(_model, Ncols, _index);

            QModelIndex index;
            typename Tcontainer::const_iterator it = _container.begin();
            for (int i = 0; i < (int)Mrows; i++, ++it) {
                ContainerHandler<Tcontainer>::set_model(*it, i, _model, _index, _flag_additional);
            }

            if (_index != QModelIndex()) {
                QString root_text = get_root_text(Mrows, Ncols);
                if (_model->itemFromIndex(_index)->text() != root_text) {
                    _model->itemFromIndex(_index)->setText(root_text);
                }
            }

        } else {
            slv::flag::ISSUE(slv::flag::Critical, "index's model is different from the one it is supposed to belong to");
        }

    } else {
        slv::flag::ISSUE(slv::flag::Critical, "_model is NULL");
    }

}

template <class Tcontainer>
Tcontainer glv::tdata::QStandardItemModelMaker<Tcontainer, Tenable>::get_value(const QStandardItemModel* _model, const QModelIndex& _index, const int _Mrows, const int _Ncols) {

    Tcontainer container;

    if (_index == QModelIndex() || _index.model() == _model) {

        int Mrows = (_Mrows == -1) ? _model->rowCount(_index) : std::min(_model->rowCount(_index), _Mrows);
        int Ncols = (_Ncols == -1) ? _model->columnCount(_index) : std::min(_model->columnCount(_index), _Ncols);

        ContainerHandlerResize<Tcontainer>::resize(container, Mrows);
        for (typename Tcontainer::iterator it = container.begin(); it != container.end(); ++it) {
            ContainerHandler<Tcontainer>::resize(*it, Ncols);
        }

        typename Tcontainer::iterator it = container.begin();
        for (int i = 0; i < Mrows; i++, ++it) {
            ContainerHandler<Tcontainer>::get_value(*it, i, _model, _index);
        }

    } else {
        slv::flag::ISSUE(slv::flag::Critical, "index's model is different from the one it is supposed to belong to");
    }

    return container;

}

template <class Tcontainer>
std::vector<int> glv::tdata::QStandardItemModelMaker<Tcontainer, Tenable>::get_coordinates(QModelIndex& _index) {

    std::vector<int> coordinates = glv::tdata::QStandardItemMaker<Tdata_sub>::get_coordinates(_index);
    ContainerHandler<Tcontainer>::add_coordinate(coordinates, _index);
    coordinates.insert(coordinates.begin(), _index.row());
    _index = _index.parent();

    return coordinates;
}

#undef Tenable
