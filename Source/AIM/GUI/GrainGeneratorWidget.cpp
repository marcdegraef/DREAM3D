/* ============================================================================
 * Copyright (c) 2010, Michael A. Jackson (BlueQuartz Software)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of Michael A. Jackson nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "GrainGeneratorWidget.h"


//-- Qt Includes
#include <QtCore/QFileInfo>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtCore/QThread>
#include <QtCore/QFileInfoList>
#include <QtGui/QFileDialog>
#include <QtGui/QCloseEvent>
#include <QtGui/QMessageBox>
#include <QtGui/QListWidget>

#include "AIM/Common/Constants.h"
#include "AIM/GrainGenerator/GrainGenerator.h"
#include "QtSupport/AIM_QtMacros.h"
#include "QtSupport/QR3DFileCompleter.h"


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
GrainGeneratorWidget::GrainGeneratorWidget(QWidget *parent) :
AIMPluginFrame(parent),
m_WorkerThread(NULL),
#if defined(Q_WS_WIN)
m_OpenDialogLastDirectory("C:\\")
#else
m_OpenDialogLastDirectory("~/")
#endif
{
  setupUi(this);
  setupGui();
  checkIOFiles();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
GrainGeneratorWidget::~GrainGeneratorWidget()
{
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::readSettings(QSettings &prefs)
{
  QString val;
  bool ok;
  qint32 i;
  double d;

  prefs.beginGroup("GrainGenerator");
  READ_FILEPATH_SETTING(prefs, gg_H5InputStatisticsFile, "");
  READ_FILEPATH_SETTING(prefs, gg_OutputDir, "");
  READ_SETTING(prefs, gg_XResolution, ok, d, 0.25 , Double);
  READ_SETTING(prefs, gg_YResolution, ok, d, 0.25 , Double);
  READ_SETTING(prefs, gg_ZResolution, ok, d, 0.25 , Double);
  READ_SETTING(prefs, gg_FillingErrorWeight, ok, d, 1.0 , Double);
  READ_SETTING(prefs, gg_NeighborhoodErrorWeight, ok, d, 1.0 , Double);
  READ_SETTING(prefs, gg_SizeDistErrorWeight, ok, d, 1.0 , Double);
  READ_SETTING(prefs, gg_NumGrains, ok, i, 1000 , Int);

  READ_BOOL_SETTING(prefs, gg_, AlreadyFormed, false);
  gg_AlreadyFormed->blockSignals(false);
  READ_COMBO_BOX(prefs, gg_ShapeClass)
  prefs.endGroup();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::writeSettings(QSettings &prefs)
{
  prefs.beginGroup("GrainGenerator");
  WRITE_STRING_SETTING(prefs, gg_H5InputStatisticsFile)
  WRITE_STRING_SETTING(prefs, gg_OutputDir)
  WRITE_SETTING(prefs, gg_XResolution )
  WRITE_SETTING(prefs, gg_YResolution )
  WRITE_SETTING(prefs, gg_ZResolution )
  WRITE_SETTING(prefs, gg_FillingErrorWeight )
  WRITE_SETTING(prefs, gg_NeighborhoodErrorWeight )
  WRITE_SETTING(prefs, gg_SizeDistErrorWeight )
  WRITE_SETTING(prefs, gg_NumGrains )

  WRITE_BOOL_SETTING(prefs, gg_AlreadyFormed, gg_AlreadyFormed->isChecked())
  WRITE_COMBO_BOX(prefs, gg_ShapeClass)
  prefs.endGroup();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::setWidgetListEnabled(bool b)
{
  foreach (QWidget* w, m_WidgetList) {
    w->setEnabled(b);
  }
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::setupGui()
{
  messageLabel->setText("");

  QR3DFileCompleter* com = new QR3DFileCompleter(this, false);
  gg_H5InputStatisticsFile->setCompleter(com);
  QObject::connect( com, SIGNAL(activated(const QString &)),
           this, SLOT(on_gg_H5InputStatisticsFile_textChanged(const QString &)));



  QR3DFileCompleter* com2 = new QR3DFileCompleter(this, true);
  gg_OutputDir->setCompleter(com2);
  QObject::connect( com2, SIGNAL(activated(const QString &)),
           this, SLOT(on_gg_OutputDir_textChanged(const QString &)));

  QString msg ("All files will be over written that appear in the output directory.");

  QFileInfo fi (gg_OutputDir->text() + QDir::separator() +  AIM::SyntheticBuilder::VisualizationFile.c_str() );
  if (gg_AlreadyFormed->isChecked() == true && fi.exists() == false)
  {
    gg_AlreadyFormed->setChecked(false);
  }

  if (gg_AlreadyFormed->isChecked())
  {
    msg += QString("\nThe 'Cube.vtk' file will be used as an import and NOT over written with new data");
  }
  messageLabel->setText(msg);

  m_WidgetList << gg_H5StatisticsFile << gg_InputH5StatisticsFileBtn << gg_OutputDir << gg_OutputDirBtn;
  m_WidgetList << gg_NumGrains << gg_XResolution << gg_YResolution << gg_ZResolution << gg_FillingErrorWeight;
  m_WidgetList << gg_NeighborhoodErrorWeight << gg_SizeDistErrorWeight;
  m_WidgetList << gg_ShapeClass << gg_AlreadyFormed;

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::on_gg_LoadSettingsBtn_clicked()
{
  QString file = QFileDialog::getOpenFileName(this, tr("Select Settings File"),
                                                 m_OpenDialogLastDirectory,
                                                 tr("Settings File (*.txt)") );
  if ( true == file.isEmpty() ){return;  }
  QSettings prefs(file, QSettings::IniFormat, this);
  readSettings(prefs);
  if (verifyPathExists(gg_OutputDir->text(), gg_OutputDir) )
  {
    checkIOFiles();
  }
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::on_gg_SaveSettingsBtn_clicked()
{
  QString proposedFile = m_OpenDialogLastDirectory + QDir::separator() + "GrainGeneratorSettings.txt";
  QString file = QFileDialog::getSaveFileName(this, tr("Save Grain Generator Settings"),
                                              proposedFile,
                                              tr("*.txt") );
  if ( true == file.isEmpty() ){ return;  }

  QSettings prefs(file, QSettings::IniFormat, this);
  writeSettings(prefs);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::checkIOFiles()
{
  CHECK_QLABEL_OUTPUT_FILE_EXISTS(AIM::SyntheticBuilder, gg_, CrystallographicErrorFile)
  CHECK_QLABEL_OUTPUT_FILE_EXISTS(AIM::SyntheticBuilder, gg_, EulerFile)
  CHECK_QLABEL_OUTPUT_FILE_EXISTS(AIM::SyntheticBuilder, gg_, GrainDataFile)
  CHECK_QLABEL_OUTPUT_FILE_EXISTS(AIM::SyntheticBuilder, gg_, H5StatisticsFile)
  CHECK_QLABEL_OUTPUT_FILE_EXISTS(AIM::SyntheticBuilder, gg_, VisualizationFile)
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::on_gg_AlreadyFormed_stateChanged(int currentState)
{

  QString absPath = gg_OutputDir->text() + QDir::separator() + AIM::SyntheticBuilder::VisualizationFile.c_str();
  absPath = QDir::toNativeSeparators(absPath);
  QFileInfo fi (absPath);
  QString msg ("All files will be over written that appear in the output directory.");
  if (gg_AlreadyFormed->isChecked() == true && fi.exists() == false)
  {
    QMessageBox::critical(this, tr("AIM Representation"),
      tr("You have selected the 'Already Formed' check box \nbut the correct output file does not exist.\n"
      "The checkbox will revert to an unchecked state.?"),
      QMessageBox::Ok,
      QMessageBox::Ok);
      gg_AlreadyFormed->setChecked(false);
      CHECK_QLABEL_OUTPUT_FILE_EXISTS(AIM::SyntheticBuilder, gg_, VisualizationFile)
  }

  if (gg_AlreadyFormed->isChecked())
  {
    msg += QString("\nThe 'reconstructed_data.txt' file will be used as an import and NOT over written with new data");
  }
  messageLabel->setText(msg);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::on_gg_InputH5StatisticsFileBtn_clicked()
{
  QString file = QFileDialog::getOpenFileName(this, tr("Select Input File"),
                                                 m_OpenDialogLastDirectory,
                                                 tr("HDF5 Stats Files (*.h5 *.hdf5)") );
  if ( true == file.isEmpty() ){return;  }
  QFileInfo fi (file);
  QString ext = fi.suffix();
  gg_H5InputStatisticsFile->setText(fi.absoluteFilePath());
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::on_gg_OutputDirBtn_clicked()
{
  QString outputFile = this->m_OpenDialogLastDirectory + QDir::separator();
  outputFile = QFileDialog::getExistingDirectory(this, tr("Select Grain Generator Output Directory"), outputFile);
  if (!outputFile.isNull())
  {
    this->gg_OutputDir->setText(outputFile);
    if (verifyPathExists(outputFile, gg_OutputDir) == true )
    {
      checkIOFiles();
      QFileInfo fi (gg_OutputDir->text() + QDir::separator() +  AIM::SyntheticBuilder::VisualizationFile.c_str() );
      if (gg_AlreadyFormed->isChecked() == true && fi.exists() == false)
      {
        gg_AlreadyFormed->setChecked(false);
      }
    }
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::on_gg_OutputDir_textChanged(const QString &text)
{
  if (verifyPathExists(gg_OutputDir->text(), gg_OutputDir) )
  {
    checkIOFiles();
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::on_gg_H5InputStatisticsFile_textChanged(const QString &text)
{
  verifyPathExists(gg_H5InputStatisticsFile->text(), gg_H5InputStatisticsFile);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::on_gg_GoBtn_clicked()
{

  if (gg_GoBtn->text().compare("Cancel") == 0)
  {
    if(m_GrainGenerator.get() != NULL)
    {
      //std::cout << "canceling from GUI...." << std::endl;
      emit cancelProcess();
    }
    return;
  }


  if (false == sanityCheckOutputDirectory(gg_OutputDir, QString("Grain Generator")) )
  {
    return;
  }
  SANITY_CHECK_INPUT(gg_, OutputDir)


  if (m_WorkerThread != NULL)
  {
    m_WorkerThread->wait(); // Wait until the thread is complete
    delete m_WorkerThread; // Kill the thread
    m_WorkerThread = NULL;
  }
  m_WorkerThread = new QThread(); // Create a new Thread Resource

  m_GrainGenerator = GrainGenerator::New(NULL);

  // Move the GrainGenerator object into the thread that we just created.
  m_GrainGenerator->moveToThread(m_WorkerThread);


  m_GrainGenerator->setH5StatsFile(gg_H5InputStatisticsFile->text().toStdString() );
  m_GrainGenerator->setOutputDirectory(gg_OutputDir->text().toStdString());
  m_GrainGenerator->setNumGrains(gg_NumGrains->value());

  int shapeclass = gg_ShapeClass->currentIndex() + 1;
  m_GrainGenerator->setShapeClass(shapeclass);

  m_GrainGenerator->setXResolution(gg_XResolution->value());
  m_GrainGenerator->setYResolution(gg_YResolution->value());
  m_GrainGenerator->setZResolution(gg_ZResolution->value());
  m_GrainGenerator->setFillingErrorWeight(gg_FillingErrorWeight->value());
  m_GrainGenerator->setNeighborhoodErrorWeight(gg_NeighborhoodErrorWeight->value());
  m_GrainGenerator->setSizeDistErrorWeight(gg_SizeDistErrorWeight->value());

  m_GrainGenerator->setAlreadyFormed(gg_AlreadyFormed->isChecked() );

  /* Connect the signal 'started()' from the QThread to the 'run' slot of the
   * Reconstruction object. Since the Reconstruction object has been moved to another
   * thread of execution and the actual QThread lives in *this* thread then the
   * type of connection will be a Queued connection.
   */
  // When the thread starts its event loop, start the Reconstruction going
  connect(m_WorkerThread, SIGNAL(started()),
          m_GrainGenerator.get(), SLOT(compute()));

  // When the Reconstruction ends then tell the QThread to stop its event loop
  connect(m_GrainGenerator.get(), SIGNAL(finished() ),
          m_WorkerThread, SLOT(quit()) );

  // When the QThread finishes, tell this object that it has finished.
  connect(m_WorkerThread, SIGNAL(finished()),
          this, SLOT( threadFinished() ) );

  // Send Progress from the Reconstruction to this object for display
  connect(m_GrainGenerator.get(), SIGNAL (updateProgress(int)),
    this, SLOT(threadProgressed(int) ) );

  // Send progress messages from Reconstruction to this object for display
  connect(m_GrainGenerator.get(), SIGNAL (updateMessage(QString)),
          this, SLOT(threadHasMessage(QString) ) );

  // If the use clicks on the "Cancel" button send a message to the Reconstruction object
  // We need a Direct Connection so the
  connect(this, SIGNAL(cancelProcess() ),
          m_GrainGenerator.get(), SLOT (on_CancelWorker() ) , Qt::DirectConnection);


  setWidgetListEnabled(false);
  emit processStarted();
  m_WorkerThread->start();
  gg_GoBtn->setText("Cancel");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::threadFinished()
{
 // std::cout << "GrainGeneratorWidget::grainGenerator_Finished()" << std::endl;
  gg_GoBtn->setText("Go");
  setWidgetListEnabled(true);
  this->gg_progressBar->setValue(0);
  emit processEnded();
  checkIOFiles();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::threadProgressed(int val)
{
  this->gg_progressBar->setValue( val );
}



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GrainGeneratorWidget::threadHasMessage(QString message)
{
  if (NULL != this->statusBar()) {
    this->statusBar()->showMessage(message);
  }
}
