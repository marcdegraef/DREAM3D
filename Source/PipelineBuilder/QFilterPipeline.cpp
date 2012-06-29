/* ============================================================================
 * Copyright (c) 2012 Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2012 Dr. Michael A. Groeber (US Air Force Research Laboratories)
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
 * Neither the name of Michael A. Groeber, Michael A. Jackson, the US Air Force,
 * BlueQuartz Software nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written
 * permission.
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
 *
 *  This code was written under United States Air Force Contract number
 *                           FA8650-07-D-5800
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include "QFilterPipeline.h"




// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QFilterPipeline::QFilterPipeline(QObject* parent) :
    QObject(parent), FilterPipeline()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QFilterPipeline::~QFilterPipeline()
{
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QFilterPipeline::updateProgressAndMessage(ErrorMessage::Pointer msg, int progress)
{
  emit updateProgress(progress);
  emit progressMessage(QString::fromStdString(msg->generateStatusString()));
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QFilterPipeline::updateProgressAndMessage(std::vector<ErrorMessage::Pointer> &messages, int progress)
{
  for (std::vector<ErrorMessage::Pointer>::iterator iter = messages.begin(); iter != messages.end(); ++iter)
  {
    updateProgressAndMessage(*iter, progress);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QFilterPipeline::pipelineProgress(int value)
{
  emit updateProgress(value);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QFilterPipeline::pipelineProgressMessage(ErrorMessage::Pointer msg)
{
  emit progressMessage(QString::fromStdString(msg->generateStatusString()));
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QFilterPipeline::pipelineProgressMessage(std::vector<ErrorMessage::Pointer> &messages)
{
  for (std::vector<ErrorMessage::Pointer>::iterator iter = messages.begin(); iter != messages.end(); ++iter)
  {
    pipelineProgressMessage(*iter);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QFilterPipeline::pipelineWarningMessage(ErrorMessage::Pointer msg)
{
  emit warningMessage(QString::fromStdString(msg->generateStatusString()));
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QFilterPipeline::pipelineWarningMessage(std::vector<ErrorMessage::Pointer> &messages)
{
  for (std::vector<ErrorMessage::Pointer>::iterator iter = messages.begin(); iter != messages.end(); ++iter)
  {
    pipelineWarningMessage(*iter);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QFilterPipeline::pipelineErrorMessage(ErrorMessage::Pointer msg)
{
  emit errorMessage(QString::fromStdString(msg->generateStatusString()));
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QFilterPipeline::pipelineErrorMessage(std::vector<ErrorMessage::Pointer> &messages)
{
  for (std::vector<ErrorMessage::Pointer>::iterator iter = messages.begin(); iter != messages.end(); ++iter)
  {
    pipelineErrorMessage(*iter);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QFilterPipeline::on_CancelWorker()
{
  setCancel(true);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QFilterPipeline::run()
{
  FilterPipeline::run(); // Execute the pipeline
  setDataContainer(DataContainer::NullPointer()); // This _should_ clean up the memory as nothing else should have
  // a reference to the DataContainer
}


