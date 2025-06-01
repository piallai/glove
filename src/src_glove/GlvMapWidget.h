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

#include "GlvMapWidget_base.h"

#define _Tdata_ std::map<Tkey, Tvalue>

class QVBoxLayout;
template <class Tkey, class Tvalue, class Tcompare>
class GlvMapWidgetItem;
template <class Tvalue>
class GlvWidget;

/*! Widget to manage interface of std::map.*/
template <class Tkey, class Tvalue, class Tcompare = std::less<Tkey> >
class GlvMapWidget : public GlvMapWidget_base {

private:

    std::vector<GlvMapWidgetItem<Tkey, Tvalue, Tcompare>*> widgets;

    Tcompare compare_function;

    bool l_editable_key;

public:

    GlvMapWidget(_Tdata_ _map = _Tdata_(), QWidget* _parent = 0);
    ~GlvMapWidget();

    /*! Set map.*/
    void set_value(const _Tdata_& _map);
    /*! Get map.*/
    _Tdata_ get_value() const;

    /*! Whether key is editable or not (default: false).*/
    void set_key_editable(bool _l_editable);

    /*! New value at current key.*/
    void insertValue();
    /*! Return true if inserted, false otherwise (key already exsists).*/
    bool insertValue(const Tkey& _key, const Tvalue& _value);

    /*! Get widget of key \p _key.*/
    GlvWidget<Tvalue>* operator[] (const Tkey _key);

private:

    void insertValue(const int _i, const Tkey& _key, const Tvalue& _value);

    void valueChanged_slot();
    typename std::vector<GlvMapWidgetItem<Tkey, Tvalue, Tcompare>*>::const_iterator removeWidget(const unsigned int i);
    /*! Return index of the corresponding key. Second of pair for existence of the key (true).*/
    std::pair<int, bool> find(const Tkey& _key) const;

    friend class GlvMapWidgetItem<Tkey, Tvalue, Tcompare>;
};

#include <QVBoxLayout>
#include "GlvWidget.h"
#include "GlvMapWidgetItem.h"

template <class Tkey, class Tvalue, class Tcompare>
GlvMapWidget<Tkey, Tvalue, Tcompare>::GlvMapWidget(_Tdata_ _map, QWidget* _parent) : GlvMapWidget_base(_parent) {

    /*! Widget of the key for insert.*/
    insert_key_widget = new GlvWidget<Tkey>();
    QString info = QString(tr("Key"));
    insert_key_widget->setWhatsThis(info);
    insert_key_widget->setToolTip(info);
    insert_key_widget->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
    this->insert_layout->addWidget(insert_key_widget);
    l_editable_key = false;
    set_value(_map);

    edit_set_checked(false);

}

template <class Tkey, class Tvalue, class Tcompare>
GlvMapWidget<Tkey, Tvalue, Tcompare>::~GlvMapWidget() {

}

template <class Tkey, class Tvalue, class Tcompare>
void GlvMapWidget<Tkey, Tvalue, Tcompare>::set_value(const _Tdata_& _map) {

    compare_function = _map.key_comp();

    for (typename std::vector<GlvMapWidgetItem<Tkey, Tvalue, Tcompare>*>::const_iterator it = widgets.begin(); it != widgets.end();) {

        if (_map.find((*it)->get_key_widget()->get_value()) == _map.end()) {
            it = removeWidget((*it)->index);
        } else {
            ++it;
        }

    }

    std::pair<int, bool> index;
    for (typename _Tdata_::const_iterator it = _map.begin(); it != _map.end(); ++it) {

        index = find(it->first);
        if (index.second) {
            widgets[index.first]->get_value_widget()->set_value(it->second);
        } else {
            insertValue(index.first, it->first, it->second);
        }

    }

    if (_map.empty()) {// If no map item exists, then the map is indicated as fully displayed for reading convenience
        set_checked(true);
    } else if (!QWidget::isVisible()) {// If a value is set before the widget is visible, and the map widget is checkable, then the default display hides the map items
        set_checked(false);
    }

}

template <class Tkey, class Tvalue, class Tcompare>
_Tdata_ GlvMapWidget<Tkey, Tvalue, Tcompare>::get_value() const {

    _Tdata_ value;
    for (int i = 0; i < widgets.size(); i++) {
        value[widgets[i]->get_key()] = widgets[i]->get_value();
    }
    return value;

}

template <class Tkey, class Tvalue, class Tcompare>
void GlvMapWidget<Tkey, Tvalue, Tcompare>::set_key_editable(bool _l_editable) {

    l_editable_key = _l_editable;

    for (int i = 0; i < widgets.size(); i++) {
        widgets[i]->get_key_widget()->set_editable(l_editable_key);
    }

}

template <class Tkey, class Tvalue, class Tcompare>
void GlvMapWidget<Tkey, Tvalue, Tcompare>::insertValue() {

    Tkey key = static_cast<GlvWidget<Tkey>*>(insert_key_widget)->get_value();

    insertValue(key, Tvalue());

}

template <class Tkey, class Tvalue, class Tcompare>
bool GlvMapWidget<Tkey, Tvalue, Tcompare>::insertValue(const Tkey& _key, const Tvalue& _value) {

    std::pair<int, bool> index = find(_key);

    if (!index.second) {
        insertValue(index.first, _key, _value);
        return true;
    } else {
        return false;
    }

}

template <class Tkey, class Tvalue, class Tcompare>
void GlvMapWidget<Tkey, Tvalue, Tcompare>::insertValue(const int _i, const Tkey& _key, const Tvalue& _value) {

    GlvMapWidgetItem<Tkey, Tvalue, Tcompare>* widget = new GlvMapWidgetItem<Tkey, Tvalue, Tcompare>(_key, _value, _i, this);
    widget->get_key_widget()->set_editable(l_editable_key);
    layout_items->insertWidget(_i, widget);
    widgets.insert(widgets.begin() + _i, widget);
    connect(widget, SIGNAL(valueChanged()), this, SLOT(valueChanged_slot()));

    for (unsigned int k = _i + 1; k < widgets.size(); k++) {
        widgets[k]->increment_index();
    }

}

template <class Tkey, class Tvalue, class Tcompare>
GlvWidget<Tvalue>* GlvMapWidget<Tkey, Tvalue, Tcompare>::operator[] (const Tkey _key) {

    std::pair<int, bool> index = find(_key);

    if (index.second) {
        return (*this)[index.first];
    } else {
        return NULL;
    }

}

template <class Tkey, class Tvalue, class Tcompare>
void GlvMapWidget<Tkey, Tvalue, Tcompare>::valueChanged_slot() {

    GlvMapWidgetItem<Tkey, Tvalue, Tcompare>* item = dynamic_cast<GlvMapWidgetItem<Tkey, Tvalue, Tcompare>*>(QObject::sender());
    if (item) {
        emit valueChanged(item->index);
    }

}

template <class Tkey, class Tvalue, class Tcompare>
typename std::vector<GlvMapWidgetItem<Tkey, Tvalue, Tcompare>*>::const_iterator GlvMapWidget<Tkey, Tvalue, Tcompare>::removeWidget(const unsigned int i) {

    typename std::vector<GlvMapWidgetItem<Tkey, Tvalue, Tcompare>*>::const_iterator it;

    if (!widgets.empty()) {

        layout_items->removeWidget(widgets[i]);
        delete widgets[i];
        it = widgets.erase(widgets.begin() + i);

        for (unsigned int j = i; j < widgets.size(); j++) {
            widgets[j]->decrement_index();
        }
    } else {
        it = widgets.end();
    }

    if (widgets.empty()) {
        set_checked(true);// If no map item exists, then the map is indicated as fully displayed for reading convenience
    }

    return it;
}

template <class Tkey, class Tvalue, class Tcompare>
std::pair<int, bool> GlvMapWidget<Tkey, Tvalue, Tcompare>::find(const Tkey& _key) const {

    std::pair<int, bool> result(0, false);

    bool l_found = false;
    for (typename std::vector<GlvMapWidgetItem<Tkey, Tvalue, Tcompare>*>::const_iterator it = widgets.begin(); it != widgets.end() && !l_found; ++it, result.first++) {
        l_found = !compare_function((*it)->get_key_widget()->get_value(), _key);
        if (l_found) {
            result.second = ((*it)->get_key_widget()->get_value() == _key);
        }
    }

    if (l_found) result.first--;

    return result;

}

#undef _Tdata_
