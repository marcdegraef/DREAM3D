/* ============================================================================
 * Copyright (c) 2011 Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2011 Dr. Michael A. Groeber (US Air Force Research Laboratories)
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


#include "PhReader.h"



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
PHReader::PHReader()
{

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
PHReader::~PHReader()
{

}

void  PHReader::readFile(std::string FileName, std::vector<int> &data, int &nx, int &ny, int &nz)
{
  std::string line;
  std::string delimeters(", ;\t"); /* delimeters to split the data */
  std::vector<string> tokens; /* vector to store the split data */
  //std::vector<int> data; /* vector to store the data */

  int error, spin; /* dummy variables */
  //int nx, ny, nz;

  std::ifstream InFile;
  InFile.open(FileName.c_str());
  if(!InFile)
    {
    std::cout << "Failed to open: " << FileName << endl;
      exit(0);
    }

  getline(InFile, line, '\n');
  tokenize(line,tokens,delimeters);

  // Process the header information from the PH file.
  error = 0;
  error += sscanf(tokens[0].c_str(), "%d", &nx);
  error += sscanf(tokens[1].c_str(), "%d", &ny);
  error += sscanf(tokens[2].c_str(), "%d", &nz);
  tokens.clear();

  //  cout << "INFO: PH file grid size: " << nx << "\t" << ny << "\t" << nz << endl;;

  //MCgrid3D* grid = new grid(nx,ny,nz);

  // Get the remaining two lines of the header and ignore
  getline(InFile, line, '\n');
  getline(InFile, line, '\n');

  //The PH file has a unique format of 20 entries on each line. I have
  //now idea who initiated this insanity but I am about to propetuate
  //it.
  //
  //The most simple thing todo is to read the entire dataset into one
  //long vector and then read that vector to assign values to the grid

  while(getline(InFile, line, '\n') != NULL)
    {
      tokens.clear();
      error = 0;
      tokenize(line,tokens,delimeters);
      //        cout << line << endl;
      //        for(int i=0; i < tokens.size(); i++ )
      //              cout << setw(6) << tokens[i];
      //        cout << endl;

      for(int in_spins=0; in_spins < tokens.size(); in_spins++)
  {
    error += sscanf(tokens[in_spins].c_str(), "%d", &spin);
    data.push_back(spin);
  }
      //        if(error != 20)
      //              {
      //                cout << "ERROR: Invalid number of line entries in PH file" << endl;
      //              }
    }

  tokens.clear();

  InFile.close();
  //  return();
}
