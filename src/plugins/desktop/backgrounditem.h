/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2011-2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#ifndef BACKGROUNDITEM_H
#define BACKGROUNDITEM_H

#include <QObject>

class BackgroundItem : public QObject
{
    Q_OBJECT
    Q_ENUMS(Type)
public:
    enum Type {
        WallpaperType,
        ColorType
    };

    explicit BackgroundItem(Type type);

    Type type() const;

    virtual QVariant data(int role) const;

private:
    class Private;
    Private *d;
};

#endif // BACKGROUNDITEM_H
