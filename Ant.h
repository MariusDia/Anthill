
#ifndef ANT_H_
#define ANT_H_

#include <AntBasePheromone.h>

class Ant : public AntBasePheromone {
public:
	//Constructeur
	Ant(Environment * ptrEnvInit, const Vector2<float> & posInit, Anthill * maisonInit);

	/**Actualise le comportement de la fourmi
	 *
	 */
	void update();
};

#endif
