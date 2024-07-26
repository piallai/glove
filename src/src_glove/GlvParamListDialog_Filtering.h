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

#include "SlvStatus.h"
#include <QStandardItemModel>
#include <QComboBox>

/*! Default filtering structure. Any Toption is compatible with any Telement.*/
template <class Telement, class Toption, typename = void>
struct GlvListFilterDefault {
    static constexpr bool is_compatible = true;//whether Toption is compatible with Telement
};

/*! Structure in charge of filtering (disabling) QComboBox items in GlvParamListDialog and GlvListDialogTlist.
* If the type associated to a QComboBox item name is not compatible with another type (Toption), then the item is being disabled.*/
struct GlvParamListDialog_Filtering {

public:

    /*! Filters.
    * \p _combo_list : QComboBox to process.
    * \p _Nitems : if not NULL, returns the number of enabled items.*/
    template <class Tlist, template <class Tlist_item, class Toption, class _Tenable> class Tfiltering, class Toption>
    static SlvStatus filter_list(QComboBox* _combo_list, int* _Nitems);

private:

    /*! Specialization with Tlist to use dedicated macro. See example in sample003_1 and sample003_2.*/
    template <class Tlist>
    struct Spec;

    /*! Returns true if set as enabled. False if the item is filtered (disabled).
    * Tfiltering is the filtering structure
    * T1 is the type associated to item cointained in _combo_list at index
    * T2 is the filtering argument.*/
    template < template <class T1, class T2, typename = void> class Tfiltering, class T1, class T2 >
    static bool filter(QComboBox* _combo_list, unsigned int _index);

    /*! Sets current index to first item not deactivated.*/
    static void update_current_item(QComboBox* _combo_list);

};

template <class Tlist, template <class Tlist_item, class Toption, class _Tenable> class Tfiltering, class Toption>
SlvStatus GlvParamListDialog_Filtering::filter_list(QComboBox* _combo_list, int* _Nitems) {

    SlvStatus status;
    std::string item_name;
    bool l_enabled;
    if (_Nitems) *_Nitems = 0;
    for (int i = 0; i < _combo_list->count(); i++) {

        item_name = _combo_list->itemText(i).toStdString();
        l_enabled = Spec<Tlist>::template filter<Tfiltering, Toption>(item_name, _combo_list, i);

        if (l_enabled && _Nitems) (*_Nitems)++;
    }

    update_current_item(_combo_list);

    return status;
}

template <class Tlist>
struct GlvParamListDialog_Filtering::Spec {
    template <template <class Tlist_item, class Toption, class _Tenable> class Tfiltering, class Toption>
    static bool filter(const std::string& _item_name, QComboBox* _combo_list, int i) {
        return true;
    }
};

template < template <class T1, class T2, typename = void> class Tfiltering, class T1, class T2 >
bool GlvParamListDialog_Filtering::filter(QComboBox* _combo_list, unsigned int _index) {

    if (!Tfiltering<T1, T2>::is_compatible) {
        qobject_cast<QStandardItemModel*>(_combo_list->model())->item(_index)->setEnabled(false);
        return false;
    } else {
        qobject_cast<QStandardItemModel*>(_combo_list->model())->item(_index)->setEnabled(true);
        return true;
    }

}
