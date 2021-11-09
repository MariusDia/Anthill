
#ifndef SILLYANT_H_
#define SILLYANT_H_

#include <AntBase.h>


class SillyAnt : public AntBase{
public:

	//Constructeur
	SillyAnt(Environment * ptrEnvInit, const Vector2<float> & posInit, Anthill * maisonInit);

	//Destructeur
	~SillyAnt();


	/**actualise le comportement de la fourmi
	 *
	 */
	void update();
};

#endif
