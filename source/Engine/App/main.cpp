#include "../Core/Root.hpp"

int main ()
{
	KFTG::Root root;
	while (!(root.isQuit ()))
		root.loop ();
	return 0;
}