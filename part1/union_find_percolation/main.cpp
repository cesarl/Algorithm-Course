#include			"UF.hh"

int				main()
{
  // 500 max

  UF<500>			uf;

  uf.run(false);

  UF<100>			uf2;

  uf2.run(false);

  UF<50>			uf3;

  uf3.run(true);
  return 0;
}
