/* fichier source.cpp */
#include "source.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

// DECLARATION DES BOOLS A FALSE

void SOURCE::COMPORTEMENT()
{ 
  std::ifstream realStream("in_real.txt");
  std::ifstream imagStream("in_imag.txt");
		
  float tmp_val;

  if(!realStream||!imagStream)
    cout<<"[SOURCE] "<<"Un des fichiers d'entree n'est pas ouvert"<<endl;

  wait();

  while(true)
    {
      // TEST BCA A FAIRE
      if(!realStream.eof()&&!imagStream.eof()){
	realStream>>tmp_val;
	out.write(tmp_val);
	wait();
	imagStream>>tmp_val;
	out.write(tmp_val);
	wait();
  // RAZ BOOL BCA
      }
      else
	{ 
	  cout<<"[SOURCE] "<< "Fin des fichiers d'entree atteinte." << endl;
	  wait();
	}
    }
}	
