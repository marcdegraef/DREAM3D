/* ============================================================================
* Copyright (c) 2009-2016 BlueQuartz Software, LLC
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
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
* contributors may be used to endorse or promote products derived from this software
* without specific prior written permission.
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
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#pragma once

#include <QtCore/QString>

#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/DataArrays/IDataArray.h"
#include "SIMPLib/Filtering/AbstractFilter.h"
#include "SIMPLib/SIMPLib.h"

#include "IO/IODLLExport.h"

/**
 * @class GoldfeatherReader GoldfeatherReader.h /IOFilters/GoldfeatherReader.h
 * @brief
 * @author
 * @date
 * @version 1.0
 */
class IO_EXPORT GoldfeatherReader : public AbstractFilter
{
  Q_OBJECT
    PYB11_CREATE_BINDINGS(GoldfeatherReader SUPERCLASS AbstractFilter)
    PYB11_PROPERTY(QString SurfaceDataContainerName READ getSurfaceDataContainerName WRITE setSurfaceDataContainerName)
    PYB11_PROPERTY(QString VertexAttributeMatrixName READ getVertexAttributeMatrixName WRITE setVertexAttributeMatrixName)
    PYB11_PROPERTY(QString FaceAttributeMatrixName READ getFaceAttributeMatrixName WRITE setFaceAttributeMatrixName)
    PYB11_PROPERTY(QString SurfaceMeshPrincipalCurvature1sArrayName READ getSurfaceMeshPrincipalCurvature1sArrayName WRITE setSurfaceMeshPrincipalCurvature1sArrayName)
    PYB11_PROPERTY(QString SurfaceMeshPrincipalCurvature2sArrayName READ getSurfaceMeshPrincipalCurvature2sArrayName WRITE setSurfaceMeshPrincipalCurvature2sArrayName)
    PYB11_PROPERTY(QString SurfaceMeshPrincipalDirection1sArrayName READ getSurfaceMeshPrincipalDirection1sArrayName WRITE setSurfaceMeshPrincipalDirection1sArrayName)
    PYB11_PROPERTY(QString SurfaceMeshPrincipalDirection2sArrayName READ getSurfaceMeshPrincipalDirection2sArrayName WRITE setSurfaceMeshPrincipalDirection2sArrayName)
    PYB11_PROPERTY(QString SurfaceMeshNodeNormalsArrayName READ getSurfaceMeshNodeNormalsArrayName WRITE setSurfaceMeshNodeNormalsArrayName)
    PYB11_PROPERTY(QString SurfaceMeshFaceLabelsArrayName READ getSurfaceMeshFaceLabelsArrayName WRITE setSurfaceMeshFaceLabelsArrayName)
    PYB11_PROPERTY(QString SurfaceMeshFaceNormalsArrayName READ getSurfaceMeshFaceNormalsArrayName WRITE setSurfaceMeshFaceNormalsArrayName)
    PYB11_PROPERTY(QString InputFile READ getInputFile WRITE setInputFile)
public:
  SIMPL_SHARED_POINTERS(GoldfeatherReader)
  SIMPL_FILTER_NEW_MACRO(GoldfeatherReader)
  SIMPL_TYPE_MACRO_SUPER_OVERRIDE(GoldfeatherReader, AbstractFilter)

  ~GoldfeatherReader() override;

  SIMPL_FILTER_PARAMETER(QString, SurfaceDataContainerName)
  Q_PROPERTY(QString SurfaceDataContainerName READ getSurfaceDataContainerName WRITE setSurfaceDataContainerName)
  SIMPL_FILTER_PARAMETER(QString, VertexAttributeMatrixName)
  Q_PROPERTY(QString VertexAttributeMatrixName READ getVertexAttributeMatrixName WRITE setVertexAttributeMatrixName)
  SIMPL_FILTER_PARAMETER(QString, FaceAttributeMatrixName)
  Q_PROPERTY(QString FaceAttributeMatrixName READ getFaceAttributeMatrixName WRITE setFaceAttributeMatrixName)

  SIMPL_FILTER_PARAMETER(QString, SurfaceMeshPrincipalCurvature1sArrayName)
  Q_PROPERTY(QString SurfaceMeshPrincipalCurvature1sArrayName READ getSurfaceMeshPrincipalCurvature1sArrayName WRITE setSurfaceMeshPrincipalCurvature1sArrayName)
  SIMPL_FILTER_PARAMETER(QString, SurfaceMeshPrincipalCurvature2sArrayName)
  Q_PROPERTY(QString SurfaceMeshPrincipalCurvature2sArrayName READ getSurfaceMeshPrincipalCurvature2sArrayName WRITE setSurfaceMeshPrincipalCurvature2sArrayName)
  SIMPL_FILTER_PARAMETER(QString, SurfaceMeshPrincipalDirection1sArrayName)
  Q_PROPERTY(QString SurfaceMeshPrincipalDirection1sArrayName READ getSurfaceMeshPrincipalDirection1sArrayName WRITE setSurfaceMeshPrincipalDirection1sArrayName)
  SIMPL_FILTER_PARAMETER(QString, SurfaceMeshPrincipalDirection2sArrayName)
  Q_PROPERTY(QString SurfaceMeshPrincipalDirection2sArrayName READ getSurfaceMeshPrincipalDirection2sArrayName WRITE setSurfaceMeshPrincipalDirection2sArrayName)
  SIMPL_FILTER_PARAMETER(QString, SurfaceMeshNodeNormalsArrayName)
  Q_PROPERTY(QString SurfaceMeshNodeNormalsArrayName READ getSurfaceMeshNodeNormalsArrayName WRITE setSurfaceMeshNodeNormalsArrayName)
  SIMPL_FILTER_PARAMETER(QString, SurfaceMeshFaceLabelsArrayName)
  Q_PROPERTY(QString SurfaceMeshFaceLabelsArrayName READ getSurfaceMeshFaceLabelsArrayName WRITE setSurfaceMeshFaceLabelsArrayName)
  SIMPL_FILTER_PARAMETER(QString, SurfaceMeshFaceNormalsArrayName)
  Q_PROPERTY(QString SurfaceMeshFaceNormalsArrayName READ getSurfaceMeshFaceNormalsArrayName WRITE setSurfaceMeshFaceNormalsArrayName)

  SIMPL_FILTER_PARAMETER(QString, InputFile)
  Q_PROPERTY(QString InputFile READ getInputFile WRITE setInputFile)

  /**
   * @brief getCompiledLibraryName Reimplemented from @see AbstractFilter class
   */
  const QString getCompiledLibraryName() const override;

  /**
   * @brief getBrandingString Returns the branding string for the filter, which is a tag
   * used to denote the filter's association with specific plugins
   * @return Branding string
  */
  const QString getBrandingString() const override;

  /**
   * @brief getFilterVersion Returns a version string for this filter. Default
   * value is an empty string.
   * @return
   */
  const QString getFilterVersion() const override;

  /**
   * @brief newFilterInstance Reimplemented from @see AbstractFilter class
   */
  AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters) const override;

  /**
   * @brief getGroupName Reimplemented from @see AbstractFilter class
   */
  const QString getGroupName() const override;

  /**
   * @brief getSubGroupName Reimplemented from @see AbstractFilter class
   */
  const QString getSubGroupName() const override;

  /**
   * @brief getUuid Return the unique identifier for this filter.
   * @return A QUuid object.
   */
  const QUuid getUuid() override;

  /**
   * @brief getHumanLabel Reimplemented from @see AbstractFilter class
   */
  const QString getHumanLabel() const override;

  /**
   * @brief setupFilterParameters Reimplemented from @see AbstractFilter class
   */
  void setupFilterParameters() override;

  /**
   * @brief readFilterParameters Reimplemented from @see AbstractFilter class
   */
  void readFilterParameters(AbstractFilterParametersReader* reader, int index) override;

  /**
   * @brief execute Reimplemented from @see AbstractFilter class
   */
  void execute() override;

  /**
  * @brief preflight Reimplemented from @see AbstractFilter class
  */
  void preflight() override;

signals:
  /**
   * @brief updateFilterParameters Emitted when the Filter requests all the latest Filter parameters
   * be pushed from a user-facing control (such as a widget)
   * @param filter Filter instance pointer
   */
  void updateFilterParameters(AbstractFilter* filter);

  /**
   * @brief parametersChanged Emitted when any Filter parameter is changed internally
   */
  void parametersChanged();

  /**
   * @brief preflightAboutToExecute Emitted just before calling dataCheck()
   */
  void preflightAboutToExecute();

  /**
   * @brief preflightExecuted Emitted just after calling dataCheck()
   */
  void preflightExecuted();

protected:
  GoldfeatherReader();
  /**
   * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
   */
  void dataCheck();

  /**
   * @brief Initializes all the private instance variables.
   */
  void initialize();

  void updateVertexInstancePointers();
  void updateFaceInstancePointers();

private:
  DEFINE_DATAARRAY_VARIABLE(double, SurfaceMeshPrincipalCurvature1s)
  DEFINE_DATAARRAY_VARIABLE(double, SurfaceMeshPrincipalCurvature2s)
  DEFINE_DATAARRAY_VARIABLE(double, SurfaceMeshPrincipalDirection1s)
  DEFINE_DATAARRAY_VARIABLE(double, SurfaceMeshPrincipalDirection2s)
  DEFINE_DATAARRAY_VARIABLE(double, SurfaceMeshNodeNormals)
  DEFINE_DATAARRAY_VARIABLE(double, SurfaceMeshFaceNormals)
  DEFINE_DATAARRAY_VARIABLE(int32_t, SurfaceMeshFaceLabels)

public:
  GoldfeatherReader(const GoldfeatherReader&) = delete; // Copy Constructor Not Implemented
  GoldfeatherReader(GoldfeatherReader&&) = delete;      // Move Constructor
  GoldfeatherReader& operator=(const GoldfeatherReader&) = delete; // Copy Assignment Not Implemented
  GoldfeatherReader& operator=(GoldfeatherReader&&) = delete;      // Move Assignment Not Implemented
};

