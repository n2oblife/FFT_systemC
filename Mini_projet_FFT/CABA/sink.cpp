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
		
  d_type real, imag;
  float real_ref, imag_ref, diff, max_error=0.;

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

			realStream<<real.to_double()<<endl;
			imagStream<<imag.to_double()<<endl;

			// realStream_ref>>real_ref;
			// imagStream_ref>>imag_ref;

			// diff= real-real_ref > 0 ? real-real_ref : real_ref-real;
			// max_error= diff>max_error ? diff : max_error;
			// diff= imag-imag_ref > 0 ? imag-imag_ref : imag_ref-imag;
			// max_error= diff>max_error ? diff : max_error;
		}
	}
}
