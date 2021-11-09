#ifndef ANTHILL_H_
#define ANTHILL_H_

#include "Agent.h"
#include <MathUtils.h>
#include <Renderer.h>
#include <vector>

class Anthill : public Agent{

public:
	//Attributs
	float nourrDepose;

	/**Constructeur
	 *
	 */
	Anthill(Environment * ptrEnvInit, const Vector2<float> & posInit, float radiusInit = 10);

	/**Destructeur
	 *
	 */
	~Anthill();

	/**
	 *
	 */
	void update();

	/** Permet aux fourmis de déposer la nourriture qu'elles transportent
	 *
	 */
	void depositFood(float quantity);
};

#endif
