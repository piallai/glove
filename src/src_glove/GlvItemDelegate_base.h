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

#include <QStyledItemDelegate>
#include "GlvWidget.h"
class GlvAbstractItemView;

class GlvItemDelegate_base : public QStyledItemDelegate {

    Q_OBJECT

protected:

    GlvAbstractItemView* abstract_view;
    QModelIndex current_index;
    /*! Whether to update model data when value changes.*/
    bool l_dynamically_update_data;

    GlvItemDelegate_base(GlvAbstractItemView* _abstract_view, QObject* _parent = 0);
    virtual ~GlvItemDelegate_base();

    void editor_size_changed(QWidget* _editor) const;

    /*! Returns true if the flag of model's index is flagged as type mismatch.*/
    static bool is_mismatch_type(const QModelIndex& _index);

public:

    /*! Whether to update model data when value changes.*/
    void set_dynamically_update_data(bool _l_dynamically_update_data);
    /*! Return whether data is dynamically updated or not.*/
    bool is_dynamically_updating_data() const;

private slots:

    void resize_text_editor();//only for General delegate

protected slots:

    void value_changed_slot_dynamic_check();
    void value_changed_slot();
    /*! Slot catching event when editor's size changed.*/
    void item_changed_slot();
    /*! Slot catching event when editor's size changed. Also commits data.*/
    void item_changed_slot(const QString& _text);

};
