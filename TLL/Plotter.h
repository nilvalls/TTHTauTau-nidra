#ifndef TLLPlotter_h
#define TLLPlotter_h

#include "Branches.h"
#include "../Plotter.h"

using namespace std;

class TLLPlotter : public Plotter {

	public:
		TLLPlotter(map<string,string> const &);
		~TLLPlotter();

	protected:

	private:
		void	FillHistos(HContainer*, Branches*, bool const, Trigger const *, weightCounter *);

};

#endif










