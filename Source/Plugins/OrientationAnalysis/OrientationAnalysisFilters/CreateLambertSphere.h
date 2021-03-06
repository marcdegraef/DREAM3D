/* ============================================================================
 * Copyright (c) 2017 BlueQuartz Software, LLC
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
 * Neither the names of any of the BlueQuartz Software contributors
 * may be used to endorse or promote products derived from this software without
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
 *
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#pragma once

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/Filtering/AbstractFilter.h"
#include "SIMPLib/Math/SIMPLibMath.h"
#include "SIMPLib/SIMPLib.h"

class QuadGeom;

#include "OrientationAnalysis/OrientationAnalysisDLLExport.h"

/**
 * @brief The CreateLambertSphere fitler creates an equal area mesh on a unit
 * sphere.
 */
class OrientationAnalysis_EXPORT CreateLambertSphere : public AbstractFilter
{
  Q_OBJECT
    PYB11_CREATE_BINDINGS(CreateLambertSphere SUPERCLASS AbstractFilter)
    PYB11_PROPERTY(int Hemisphere READ getHemisphere WRITE setHemisphere)
    PYB11_PROPERTY(DataArrayPath ImageDataArrayPath READ getImageDataArrayPath WRITE setImageDataArrayPath)
    PYB11_PROPERTY(QString QuadDataContainerName READ getQuadDataContainerName WRITE setQuadDataContainerName)
    PYB11_PROPERTY(QString TriangleDataContainerName READ getTriangleDataContainerName WRITE setTriangleDataContainerName)
    PYB11_PROPERTY(QString EdgeDataContainerName READ getEdgeDataContainerName WRITE setEdgeDataContainerName)
    PYB11_PROPERTY(QString VertexDataContainerName READ getVertexDataContainerName WRITE setVertexDataContainerName)
    PYB11_PROPERTY(QString VertexAttributeMatrixName READ getVertexAttributeMatrixName WRITE setVertexAttributeMatrixName)
    PYB11_PROPERTY(QString EdgeAttributeMatrixName READ getEdgeAttributeMatrixName WRITE setEdgeAttributeMatrixName)
    PYB11_PROPERTY(QString FaceAttributeMatrixName READ getFaceAttributeMatrixName WRITE setFaceAttributeMatrixName)
    //  PYB11_PROPERTY(QString ImageFaceDataArrayName READ getImageFaceDataArrayName WRITE setImageFaceDataArrayName)
    PYB11_PROPERTY(bool CreateVertexGeometry READ getCreateVertexGeometry WRITE setCreateVertexGeometry)
    PYB11_PROPERTY(bool CreateEdgeGeometry READ getCreateEdgeGeometry WRITE setCreateEdgeGeometry)
    PYB11_PROPERTY(bool CreateTriangleGeometry READ getCreateTriangleGeometry WRITE setCreateTriangleGeometry)
    PYB11_PROPERTY(bool CreateQuadGeometry READ getCreateQuadGeometry WRITE setCreateQuadGeometry)
public:
  SIMPL_SHARED_POINTERS(CreateLambertSphere)
  SIMPL_FILTER_NEW_MACRO(CreateLambertSphere)
  SIMPL_TYPE_MACRO_SUPER_OVERRIDE(CreateLambertSphere, AbstractFilter)

  ~CreateLambertSphere() override;

  SIMPL_FILTER_PARAMETER(int, Hemisphere)
  Q_PROPERTY(int Hemisphere READ getHemisphere WRITE setHemisphere)

  SIMPL_FILTER_PARAMETER(DataArrayPath, ImageDataArrayPath)
  Q_PROPERTY(DataArrayPath ImageDataArrayPath READ getImageDataArrayPath WRITE setImageDataArrayPath)

  SIMPL_FILTER_PARAMETER(QString, QuadDataContainerName)
  Q_PROPERTY(QString QuadDataContainerName READ getQuadDataContainerName WRITE setQuadDataContainerName)

  SIMPL_FILTER_PARAMETER(QString, TriangleDataContainerName)
  Q_PROPERTY(QString TriangleDataContainerName READ getTriangleDataContainerName WRITE setTriangleDataContainerName)

  SIMPL_FILTER_PARAMETER(QString, EdgeDataContainerName)
  Q_PROPERTY(QString EdgeDataContainerName READ getEdgeDataContainerName WRITE setEdgeDataContainerName)

  SIMPL_FILTER_PARAMETER(QString, VertexDataContainerName)
  Q_PROPERTY(QString VertexDataContainerName READ getVertexDataContainerName WRITE setVertexDataContainerName)

  SIMPL_FILTER_PARAMETER(QString, VertexAttributeMatrixName)
  Q_PROPERTY(QString VertexAttributeMatrixName READ getVertexAttributeMatrixName WRITE setVertexAttributeMatrixName)

  SIMPL_FILTER_PARAMETER(QString, EdgeAttributeMatrixName)
  Q_PROPERTY(QString EdgeAttributeMatrixName READ getEdgeAttributeMatrixName WRITE setEdgeAttributeMatrixName)

  SIMPL_FILTER_PARAMETER(QString, FaceAttributeMatrixName)
  Q_PROPERTY(QString FaceAttributeMatrixName READ getFaceAttributeMatrixName WRITE setFaceAttributeMatrixName)

  //  SIMPL_FILTER_PARAMETER(QString, ImageFaceDataArrayName)
  //  Q_PROPERTY(QString ImageFaceDataArrayName READ getImageFaceDataArrayName WRITE setImageFaceDataArrayName)

  SIMPL_FILTER_PARAMETER(bool, CreateVertexGeometry)
  Q_PROPERTY(bool CreateVertexGeometry READ getCreateVertexGeometry WRITE setCreateVertexGeometry)

  SIMPL_FILTER_PARAMETER(bool, CreateEdgeGeometry)
  Q_PROPERTY(bool CreateEdgeGeometry READ getCreateEdgeGeometry WRITE setCreateEdgeGeometry)

  SIMPL_FILTER_PARAMETER(bool, CreateTriangleGeometry)
  Q_PROPERTY(bool CreateTriangleGeometry READ getCreateTriangleGeometry WRITE setCreateTriangleGeometry)

  SIMPL_FILTER_PARAMETER(bool, CreateQuadGeometry)
  Q_PROPERTY(bool CreateQuadGeometry READ getCreateQuadGeometry WRITE setCreateQuadGeometry)

  SIMPL_FILTER_PARAMETER(bool, UseExistingImage)
  Q_PROPERTY(bool UseExistingImage READ getUseExistingImage WRITE setUseExistingImage)
  
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
  /**
   * @brief CreateLambertSphere
   */
  CreateLambertSphere();

  /**
   * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
   */
  void dataCheck();

  /**
   * @brief Initializes all the private instance variables.
   */
  void initialize();

  /**
   * @brief createVertices
   */
  void createVertices();

  /**
   * @brief CreateVertexGeometry
   */
  void createVertexGeometry();

  /**
   * @brief CreateEdgeGeometry
   */
  void createEdgeGeometry();

  /**
   * @brief CreateTriangleGeometry
   */
  void createTriangleGeometry();

  /**
   * @brief CreateQuadGeometry
   */
  void createQuadGeometry();

private:
  DEFINE_DATAARRAY_VARIABLE(uint8_t, ImageData)

  // DEFINE_DATAARRAY_VARIABLE(uint8_t, VertexData)
  DEFINE_DATAARRAY_VARIABLE(uint8_t, EdgeData)
  DEFINE_DATAARRAY_VARIABLE(uint8_t, TriangleFaceData)
  DEFINE_DATAARRAY_VARIABLE(uint8_t, QuadFaceData)

  SharedVertexList::Pointer m_Vertices;

  QString m_VertexDataName;
  QString m_EdgeDataName;
  QString m_TriangleDataName;
  QString m_QuadDataName;

  /**
   * @brief Transforms the initial flat grid to a sphere using equations from
   * D. Rosca's paper.
   * @param verts The vertices to transform.
   */
  void transformFromLambertSquareToSphere(SharedVertexList* verts);

  /**
   * @brief Internal helper function
   * @param p The float to adjust.
   * @return
   */
  float cp(float p);

public:
  CreateLambertSphere(const CreateLambertSphere&) = delete; // Copy Constructor Not Implemented
  CreateLambertSphere(CreateLambertSphere&&) = delete;      // Move Constructor
  CreateLambertSphere& operator=(const CreateLambertSphere&) = delete; // Copy Assignment Not Implemented
  CreateLambertSphere& operator=(CreateLambertSphere&&) = delete;      // Move Assignment Not Implemented
};

