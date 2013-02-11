#ifndef TTEPlotter_h
#define TTEPlotter_h

#include "Branches.h"
#include "../Plotter.h"

using namespace std;

class TTEPlotter : public Plotter {

	public:
		TTEPlotter(map<string,string> const &);
		~TTEPlotter();

	protected:

	private:
		void	FillHistos(HContainer*, Branches*, bool const, Trigger const *, weightCounter *);

};

#endif










