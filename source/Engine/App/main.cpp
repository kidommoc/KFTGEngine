#include "../Common/Root.hpp"

int main ()
{
	KFTG::Root &root = KFTG::Root::instance ();
	while (!(root.isQuit ()))
		root.loop ();
	return 0;
}