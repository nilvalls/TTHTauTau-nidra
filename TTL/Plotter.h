#ifndef TTLPlotter_h
#define TTLPlotter_h

#include "Branches.h"
#include "../Plotter.h"

using namespace std;

class TTLPlotter : public Plotter {

	public:
		TTLPlotter(map<string,string> const &);
		~TTLPlotter();

	protected:

	private:
		void	FillHistos(HContainer*, Branches*, bool const, Trigger const *, weightCounter *);

};

#endif










