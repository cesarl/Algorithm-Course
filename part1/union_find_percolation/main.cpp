#include			"UF.hh"

// improuved take more time - strange ;)

int				main()
{
  UF<5000>			uf(false);

  uf.run(false);

  UF<500>			uf1(false);

  uf1.run(false);

  UF<100>			uf2(false);

  uf2.run(false);

  UF<50>			uf3(false);

  uf3.run(false);
  return 0;
}
