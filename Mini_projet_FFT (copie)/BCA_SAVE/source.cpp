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

  float tmp_val_real;
  float tmp_val_imag;

  if(!realStream||!imagStream)
    cout<<"[SOURCE] "<<"Un des fichiers d'entree n'est pas ouvert"<<endl;


  data_valid.write(false);

  while(true)
    { 
      wait();
      // TEST BCA A FAIRE      // TEST BCA A FAIRE
      
      if(!realStream.eof()&&!imagStream.eof()){

        if(data_req.read()){
          realStream>>tmp_val_real;
                    // cout<< "[SOURCE]"<<"tmp_val_real"<<tmp_val_real << endl;

          imagStream>>tmp_val_imag;
                    // cout<< "[SOURCE]"<<"tmp_val_imag"<<tmp_val_imag << endl;

          out_real.write(tmp_val_real);
          out_img.write(tmp_val_imag);
          data_valid.write(true)         ;
          // cout<< "[SOURCE]"<<"Lecture" << endl;
        }

      }
      else 
      {
        data_valid.write(false) ;
        // cout<<"[SOURCE] "<< "Fin des fichiers d'entree atteinte." << endl;
        
      }
    }
}


   

