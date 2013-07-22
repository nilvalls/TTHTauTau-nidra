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
		virtual double	FillHistos(const std::string&, HContainer*, Branches*, bool const, Trigger const *, weightCounter *);

};

#endif










