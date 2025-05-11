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

#include <QComboBox>

class GlvEnumWidget_base : public QComboBox {
protected:
    GlvEnumWidget_base(QWidget* _parent = 0) : QComboBox(_parent) {}
    virtual ~GlvEnumWidget_base() {}
public:
    void set_editable(bool l_editable) {
        QComboBox::setEnabled(l_editable);
    }
};

template <class T, typename = void>
class GlvEnumWidget;

#include "SlvEnum.h"

/*! Widget managing an enum type.
* The enum must be created using the macro: glvm_SlvEnum. See sample001 for example.*/
template <class Tenum>
class GlvEnumWidget<Tenum, typename std::enable_if<std::is_enum<Tenum>::value>::type> : public GlvEnumWidget_base {

public:

    GlvEnumWidget(Tenum _enum = Tenum(), QWidget* _parent = 0);
    ~GlvEnumWidget();

    /*! Set the enum value.*/
    void set_value(const Tenum _enum);
    /*! Get the enum value.*/
    Tenum get_value() const;

};

#include "glv_QString.h"

template <class Tenum>
GlvEnumWidget<Tenum, typename std::enable_if<std::is_enum<Tenum>::value>::type>::GlvEnumWidget(Tenum _enum, QWidget* _parent) : GlvEnumWidget_base(_parent) {

    for (unsigned int i = 0; i < SlvEnum<Tenum>::size(); i++) {
        QString enum_name = glv::toQString(SlvEnum<Tenum>::get_name(i));
        QComboBox::addItem(enum_name);
    }
    set_value(_enum);

}

template <class Tenum>
GlvEnumWidget<Tenum, typename std::enable_if<std::is_enum<Tenum>::value>::type>::~GlvEnumWidget() {

}

template <class Tenum>
void GlvEnumWidget<Tenum, typename std::enable_if<std::is_enum<Tenum>::value>::type>::set_value(const Tenum _enum) {

    QComboBox::setCurrentIndex(SlvEnum<Tenum>::enum_positions().at(_enum));

}

template <class Tenum>
Tenum GlvEnumWidget<Tenum, typename std::enable_if<std::is_enum<Tenum>::value>::type>::get_value() const {

    return SlvEnum<Tenum>::enum_positions_inv()[QComboBox::currentIndex()];

}