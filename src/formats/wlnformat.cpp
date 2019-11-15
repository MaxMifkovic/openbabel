/**********************************************************************
Copyright (C) 2019 by NextMove Software

This file is part of the Open Babel project.
For more information, see <http://openbabel.org/>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
***********************************************************************/

#include <openbabel/babelconfig.h>
#include <openbabel/obmolecformat.h>

#include <openbabel/base.h>
#include <openbabel/mol.h>

bool NMReadWLN(const char *ptr, OpenBabel::OBMol* mol);

using namespace std;
namespace OpenBabel
{

  class WLNFormat : public OBMoleculeFormat
  {
  public:
    //Register this format type ID
    WLNFormat()
    {
      OBConversion::RegisterFormat("wln", this);
    }

    virtual const char* Description() //required
    {
      return
        "Wisswesser Line Notation\n"
        "Note that this reader does not yet offer complete support of all of WLN.\n";
    };

    virtual unsigned int Flags()
    {
      return NOTWRITABLE;
    }

    //*** This section identical for most OBMol conversions ***
    ////////////////////////////////////////////////////
    /// The "API" interface functions
    virtual bool ReadMolecule(OBBase* pOb, OBConversion* pConv);
  };
  //***

  //Make an instance of the format class
  WLNFormat theWLNFormat;

  /////////////////////////////////////////////////////////////////
  bool WLNFormat::ReadMolecule(OBBase* pOb, OBConversion* pConv)
  {
    OBMol* pmol = pOb->CastAndClear<OBMol>();
    if(pmol==NULL)
      return false;

    //Define some references so we can use the old parameter names
    istream &ifs = *pConv->GetInStream();
    const char* title = pConv->GetTitle();
    char buffer[BUFF_SIZE];

    if (!ifs.getline(buffer,BUFF_SIZE))
      return false;

    NMReadWLN(buffer, pmol);

    return true;
  }

  ////////////////////////////////////////////////////////////////

} //namespace OpenBabel
