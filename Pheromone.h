
#ifndef PHEROMONE_H_
#define PHEROMONE_H_


#include <Vector2.h>
#include <Timer.h>
#include <cmath>
#include <MathUtils.h>
#include <Agent.h>
#include <Food.h>
#include <Environment.h>
#include <Anthill.h>

class Pheromone : public Agent {
public:

	//Attributs
	float qtePheDeposee;

	//Constructeur
	Pheromone(Environment * ptrEnvInit, const Vector2<float> & posInit, float qtePheInit);

	//Destructeur
	~Pheromone();

	/**Accesseur
	 * @return qtePheDeposee
	 */
	float getQuantity() const;

	/**Setter
	 * @pre qte > 0
	 * @post qtePheDeposee modifiée
	 */
	void addQuantity(const float qte);

	/**actualise le comportement de la pheromone
	 *
	 */
	void update();

};

#endif
