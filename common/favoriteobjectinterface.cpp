/*
  favoriteobjectinterface.cpp

  This file is part of GammaRay, the Qt application inspection and manipulation tool.

  SPDX-FileCopyrightText: 2013-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Waqar Ahmed <waqar.ahmed@kdab.com>

  SPDX-License-Identifier: GPL-2.0-or-later

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "favoriteobjectinterface.h"

using namespace GammaRay;

FavoriteObjectInterface::FavoriteObjectInterface(QObject *parent)
    : QObject(parent)
{
}

FavoriteObjectInterface::~FavoriteObjectInterface() = default;
