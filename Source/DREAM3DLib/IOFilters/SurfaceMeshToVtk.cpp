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

#include "SurfaceMeshToVtk.h"


#include "MXA/Common/MXAEndian.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
SurfaceMeshToVtk::SurfaceMeshToVtk() :
AbstractFilter(),
m_WriteBinaryFile(false),
m_WriteConformalMesh(true)
{
  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
SurfaceMeshToVtk::~SurfaceMeshToVtk()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SurfaceMeshToVtk::setupFilterParameters()
{
  std::vector<FilterParameter::Pointer> options;
{
     FilterParameter::Pointer option = FilterParameter::New();
     option->setHumanLabel("Output Vtk File");
     option->setPropertyName("OutputVtkFile");
     option->setWidgetType(FilterParameter::OutputFileWidget);
     option->setValueType("string");
     options.push_back(option);
   }
   {
     FilterParameter::Pointer option = FilterParameter::New();
     option->setHumanLabel("Write Binary Vtk File");
     option->setPropertyName("WriteBinaryFile");
     option->setWidgetType(FilterParameter::BooleanWidget);
     option->setValueType("bool");
     options.push_back(option);
   }
   {
     FilterParameter::Pointer option = FilterParameter::New();
     option->setHumanLabel("Write Conformal Mesh");
     option->setPropertyName("WriteConformalMesh");
     option->setWidgetType(FilterParameter::BooleanWidget);
     option->setValueType("bool");
     options.push_back(option);
   }

  setFilterParameters(options);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SurfaceMeshToVtk::writeFilterParameters(AbstractFilterParametersWriter* writer)
{
  writer->writeValue("OutputVtkFile", getOutputVtkFile() );
  writer->writeValue("WriteBinaryFile", getWriteBinaryFile() );
  writer->writeValue("WriteConformalMesh", getWriteConformalMesh() );
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SurfaceMeshToVtk::dataCheck(bool preflight, size_t voxels, size_t fields, size_t ensembles)
{
  setErrorCondition(0);

  if (m_OutputVtkFile.empty() == true)
  {
    setErrorCondition(-1003);
    addErrorMessage(getHumanLabel(), "Vtk Output file is Not set correctly", -1003);
  }
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SurfaceMeshToVtk::preflight()
{
  /* Place code here that sanity checks input arrays and input values. Look at some
  * of the other DREAM3DLib/Filters/.cpp files for sample codes */
  dataCheck(true, 1, 1, 1);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SurfaceMeshToVtk::execute()
{
  int err = 0;
  std::stringstream ss;
  setErrorCondition(err);
  SurfaceMeshDataContainer* m = getSurfaceMeshDataContainer();
  if(NULL == m)
  {
    setErrorCondition(-999);
    notifyErrorMessage("The SurfaceMesh DataContainer Object was NULL", -999);
    return;
  }
  if (NULL == m->getNodes())
  {
      setErrorCondition(-555);
    notifyErrorMessage("The SurfaceMesh DataContainer Does NOT contain Nodes", -555);
    return;
  }
    if (NULL == m->getTriangles())
  {
      setErrorCondition(-556);
    notifyErrorMessage("The SurfaceMesh DataContainer Does NOT contain Triangles", -556);
    return;
  }

  setErrorCondition(0);

  /* Place all your code to execute your filter here. */
  StructArray<Node>& nodes = *(m->getNodes());
  int nNodes = nodes.GetNumberOfTuples();

// Open the output VTK File for writing
  FILE* vtkFile = NULL;
  vtkFile = fopen(getOutputVtkFile().c_str(), "wb");
  if (NULL == vtkFile)
  {
    ss.str("");
    ss  << ": Error creating Triangles VTK Visualization '" << getOutputVtkFile() << "'";
    setErrorCondition(-1);
    PipelineMessage em(getHumanLabel(), ss.str(), -666);
    addErrorMessage(em);
    return;
  }
  fprintf(vtkFile, "# vtk DataFile Version 2.0\n");
  fprintf(vtkFile, "Data set from DREAM.3D Surface Meshing Module\n");
  if (m_WriteBinaryFile) {
    fprintf(vtkFile, "BINARY\n");
  }
  else {
    fprintf(vtkFile, "ASCII\n");
  }
  fprintf(vtkFile, "DATASET POLYDATA\n");

  int numberWrittenNodes = 0;
  for (int i = 0; i < nNodes; i++)
  {
    Node& n = nodes[i]; // Get the current Node
    if (n.nodeKind > 0) { ++numberWrittenNodes; }
  }


  fprintf(vtkFile, "POINTS %d float\n", numberWrittenNodes);

  float pos[3] = {0.0f, 0.0f, 0.0f};

  size_t totalWritten = 0;
  // Write the POINTS data (Vertex)
  for (int i = 0; i < nNodes; i++)
  {
    Node& n = nodes[i]; // Get the current Node
    if (n.nodeKind > 0)
    {
      pos[0] = n.coord[0];
      pos[1] = n.coord[1];
      pos[2] = n.coord[2];
      if (m_WriteBinaryFile == true)
      {
        MXA::Endian::FromSystemToBig::convert<float>(pos[0]);
        MXA::Endian::FromSystemToBig::convert<float>(pos[1]);
        MXA::Endian::FromSystemToBig::convert<float>(pos[2]);
        totalWritten = fwrite(pos, sizeof(float), 3, vtkFile);
        if (totalWritten != sizeof(float) * 3)
        {

        }
      }
      else {
        fprintf(vtkFile, "%f %f %f\n", pos[0], pos[1], pos[2]); // Write the positions to the output file
      }
    }
  }

  // Write the triangle indices into the vtk File
  StructArray<Triangle>& triangles = *(m->getTriangles());

  int tData[4];
  int nT = triangles.GetNumberOfTuples();
  int triangleCount = nT;
//  int tn1, tn2, tn3;
  if (false == m_WriteConformalMesh)
  {
    triangleCount = nT * 2;
  }
  // Write the CELLS Data
  fprintf(vtkFile, "POLYGONS %d %d\n", triangleCount, (triangleCount * 4));
  for (int j = 0; j < nT; j++)
  {
  //  Triangle& t = triangles[j];
    tData[1] = triangles[j].node_id[0];
    tData[2] = triangles[j].node_id[1];
    tData[3] = triangles[j].node_id[2];

//    tData[1] = nodes[tn1].newID;
//    tData[2] = nodes[tn2].newID;
//    tData[3] = nodes[tn3].newID;
    if (m_WriteBinaryFile == true)
    {
      tData[0] = 3; // Push on the total number of entries for this entry
      MXA::Endian::FromSystemToBig::convert<int>(tData[0]);
      MXA::Endian::FromSystemToBig::convert<int>(tData[1]); // Index of Vertex 0
      MXA::Endian::FromSystemToBig::convert<int>(tData[2]); // Index of Vertex 1
      MXA::Endian::FromSystemToBig::convert<int>(tData[3]); // Index of Vertex 2
      fwrite(tData, sizeof(int), 4, vtkFile);
      if (false == m_WriteConformalMesh)
      {
        tData[0] = tData[1];
        tData[1] = tData[3];
        tData[3] = tData[0];
        tData[0] = 3;
        MXA::Endian::FromSystemToBig::convert<int>(tData[0]);
        fwrite(tData, sizeof(int), 4, vtkFile);
      }
    }
    else
    {
      fprintf(vtkFile, "3 %d %d %d\n", tData[1], tData[2], tData[3]);
      if (false == m_WriteConformalMesh)
      {
        fprintf(vtkFile, "3 %d %d %d\n", tData[3], tData[2], tData[1]);
      }
    }
  }


  // Write the CELL_DATA section
  err = writeCellData(vtkFile);
  err = writePointData(vtkFile);

  fprintf(vtkFile, "\n");
  // Free the memory
  // Close the input and output files
  fclose(vtkFile);

  setErrorCondition(0);
  notifyStatusMessage("Complete");

}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int SurfaceMeshToVtk::writePointData(FILE* vtkFile)
{
  int err = 0;
  if (NULL == vtkFile)
  {
    return -1;
  }

  // Write the triangle indices into the vtk File
//  StructArray<Triangle>& triangles = *(getSurfaceMeshDataContainer()->getTriangles());

  StructArray<Node>& nodes = *(getSurfaceMeshDataContainer()->getNodes());
  int numNodes = nodes.GetNumberOfTuples();
  int nNodes = 0;
  int swapped;
  for (int i = 0; i < numNodes; i++)
  {
    Node& n = nodes[i]; // Get the current Node
    if (n.nodeKind > 0) { ++nNodes; }
  }
  fprintf(vtkFile, "\n");
  fprintf(vtkFile, "POINT_DATA %d\n", nNodes);
  fprintf(vtkFile, "SCALARS Node_Type int 1\n");
  fprintf(vtkFile, "LOOKUP_TABLE default\n");


  for(int i = 0; i < numNodes; ++i)
  {
    Node& n = nodes[i]; // Get the current Node
    if(n.nodeKind > 0)
    {
      if(m_WriteBinaryFile == true)
      {
        swapped = n.nodeKind;
        MXA::Endian::FromSystemToBig::convert<int>(swapped);
        fwrite(&swapped, sizeof(int), 1, vtkFile);
      }
      else
      {
        fprintf(vtkFile, "%d\n", n.nodeKind);
      }

    }
  }
  return err;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int SurfaceMeshToVtk::writeCellData(FILE* vtkFile)
{
  int err = 0;
  if (NULL == vtkFile)
  {
    return -1;
  }

  // Write the triangle region ids
  StructArray<Triangle>& triangles = *(getSurfaceMeshDataContainer()->getTriangles());

  int nT = triangles.GetNumberOfTuples();
  int triangleCount = nT;
  int swapped;
  if (false == m_WriteConformalMesh)
  {
    triangleCount = nT * 2;
  }

  // Write the GrainId Data to the file
  fprintf(vtkFile, "\n");
  fprintf(vtkFile, "CELL_DATA %d\n", triangleCount);
  fprintf(vtkFile, "SCALARS GrainID int 1\n");
  fprintf(vtkFile, "LOOKUP_TABLE default\n");


  for(int i = 0; i < nT; ++i)
  {
    Triangle& t = triangles[i]; // Get the current Node

    if(m_WriteBinaryFile == true)
    {
      swapped = t.nSpin[0];
      MXA::Endian::FromSystemToBig::convert<int>(swapped);
      fwrite(&swapped, sizeof(int), 1, vtkFile);
      if(false == m_WriteConformalMesh)
      {
        swapped = t.nSpin[1];
        MXA::Endian::FromSystemToBig::convert<int>(swapped);
        fwrite(&swapped, sizeof(int), 1, vtkFile);
      }
    }
    else
    {
      fprintf(vtkFile, "%d\n", t.nSpin[0]);
      if(false == m_WriteConformalMesh)
      {
        fprintf(vtkFile, "%d\n", t.nSpin[1]);
      }
    }

  }
  return err;
}
