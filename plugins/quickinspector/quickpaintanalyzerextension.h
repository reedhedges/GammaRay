/*
  quickpaintanalyzerextension.h

  This file is part of GammaRay, the Qt application inspection and manipulation tool.

  SPDX-FileCopyrightText: 2016-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Volker Krause <volker.krause@kdab.com>

  SPDX-License-Identifier: GPL-2.0-or-later

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef GAMMARAY_QUICKPAINTANALYZEREXTENSION_H
#define GAMMARAY_QUICKPAINTANALYZEREXTENSION_H

#include <core/propertycontrollerextension.h>

namespace GammaRay {
class PaintAnalyzer;
class PropertyController;

class QuickPaintAnalyzerExtension : public PropertyControllerExtension
{
public:
    explicit QuickPaintAnalyzerExtension(PropertyController *controller);
    ~QuickPaintAnalyzerExtension();

    bool setQObject(QObject *object) override;

private:
    PaintAnalyzer *m_paintAnalyzer;
};
}

#endif // GAMMARAY_QUICKPAINTANALYZEREXTENSION_H
