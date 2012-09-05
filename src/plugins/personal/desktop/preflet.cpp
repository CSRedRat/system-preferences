/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (c) 2011-2012 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:GPL$
 *
 * System Preferences is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * System Preferences is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with System Preferences.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QDirIterator>

#include <VSettings>
#include <VDesktopFile>
#include <VStandardDirectories>

#include "preflet.h"
#include "ui_desktoppreflet.h"
#include "wallpapermodel.h"

using namespace VStandardDirectories;

Preflet::Preflet(QWidget *parent)
    : VPreferencesModule(parent)
    , ui(new Ui::DesktopPreflet)
{
    ui->setupUi(this);

    // Settings
    m_settings = new VSettings("org.maui.desktop.background");

    // Wallpapers model
    m_wallpaperModel = new WallpaperModel(this);
    ui->bgList->setModel(m_wallpaperModel);

    // Connect signals
    connect(ui->launcherIconSizeSlider, SIGNAL(valueChanged(int)),
            ui->launcherIconSizeSpin, SLOT(setValue(int)));
    connect(ui->launcherIconSizeSpin, SIGNAL(valueChanged(int)),
            ui->launcherIconSizeSlider, SLOT(setValue(int)));
    connect(ui->bgCategory, SIGNAL(currentIndexChanged(int)),
            this, SLOT(slotBackgroundCategoryChanged(int)));
    connect(ui->bgList, SIGNAL(activate(QModelIndex)),
            this, SLOT(slotBackgroundSelected(QModelIndex)));
}

Preflet::~Preflet()
{
    delete ui;
    delete m_wallpaperModel;
    delete m_settings;
}

QString Preflet::name() const
{
    return tr("Desktop");
}

QString Preflet::comment() const
{
    return tr("Configure desktop, wallpaper and screen saver.");
}

QString Preflet::iconName() const
{
    return "preferences-desktop";
}

QStringList Preflet::keywords() const
{
    return tr("desktop;launcher;wallpaper;screen saver;hot corner").split(";");
}

VPreferencesModule::Category Preflet::category() const
{
    return VPreferencesModule::PersonalCategory;
}

int Preflet::weight() const
{
    return 50;
}

void Preflet::slotBackgroundCategorySelected(int index)
{
    switch (index) {
        case 0: {
            QString path = QString("%1/wallpapers").arg(findDirectory(SystemDataDirectory));
            QDirIterator it(path, QDir::Dirs | QDir::Readable | QDir::NoDotAndDotDot,
                            QDirIterator::FollowSymlinks);
            while (it.hasNext()) {
                QDir dir(it.next());
                if (dir.exists("metadata.desktop"))
                    m_wallpaperModel->addPath(dir.absolutePath());
            }
        }
        break;
        default:
            break;
    }
}

void Preflet::slotBackgroundModeSelected(int index)
{
}

void Preflet::slotBackgroundSelected(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    //QString path = m_model->data(index, BackgroundsModel::AbsolutePath).toString();
}

#include "moc_preflet.cpp"