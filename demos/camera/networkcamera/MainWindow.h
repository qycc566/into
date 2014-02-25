/* This file is part of Into.
 * Copyright (C) Intopii 2013.
 * All rights reserved.
 *
 * Licensees holding a commercial Into license may use this file in
 * accordance with the commercial license agreement. Please see
 * LICENSE.commercial for commercial licensing terms.
 *
 * Alternatively, this file may be used under the terms of the GNU
 * Affero General Public License version 3 as published by the Free
 * Software Foundation. In addition, Intopii gives you special rights
 * to use Into as a part of open source software projects. Please
 * refer to LICENSE.AGPL3 for details.
 */

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <DemoMainWindow.h>
#include "ui_mainwindow.h"

#include <PiiEngine.h>
#include <PiiOperation.h>
#include <PiiProbeInput.h>
#include <QTime>

class MainWindow : public DemoMainWindow, private Ui::MainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);

protected:
  QStringList requiredPlugins() const { return QStringList() << "piiimage" << "piicamera" << "piibase" << "piiflowcontrol"; }
  PiiEngine* createEngine();

private slots:
  void urlActivated(const QString& imageUrl);
  void updateButtonStates(PiiOperation::State state);
  void startButtonClicked();
  void setFps(PiiVariant fpsObject);

private:
  void init();

  PiiProbeInput *_pProbeInput, *_pFpsProbeInput;
  PiiOperation *_pNetworkCameraOperation;
};



#endif //_MAINWINDOW_H
