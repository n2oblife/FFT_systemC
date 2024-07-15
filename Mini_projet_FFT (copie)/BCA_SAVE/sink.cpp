/* fichier sink.cpp */
#include "sink.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

// DECLARATION DES BOOLS A FALSE


void SINK::COMPORTEMENT()
{  
  std::ofstream realStream("out_real.txt");
  std::ofstream imagStream("out_imag.txt");

  std::ifstream realStream_ref("out_real_ref_valid.txt");
  std::ifstream imagStream_ref("out_imag_ref_valid.txt");
		
  float real, imag, real_ref, imag_ref, diff, max_error=0.;

  if(!realStream||!imagStream||!realStream_ref||!imagStream_ref)
	cout<<"[SINK] "<<"Un des fichiers d'entree n'est pas ouvert"<<endl;
	

  data_req.write(true);
  wait();
  while(true)
    { 
		wait();

		if ( data_valid.read() ){

			real= in_real.read();	
			imag= in_img.read();

			realStream<<real<<endl;
			imagStream<<imag<<endl;

			realStream_ref>>real_ref;
			imagStream_ref>>imag_ref;

			diff=abs(real-real_ref);
			max_error= diff>max_error ? diff : max_error;
			diff=abs(imag-imag_ref);
			max_error= diff>max_error ? diff : max_error;
		}
	}
}
