#ifndef AGENT_H_
#define AGENT_H_

#include <Environment.h>
#include <set>
#include <vector>
#include <iostream>



class Agent : public Environment::LocalizedEntity{//Agent hérite de LocalizedEntity (public ?)

private:
	static std::set<Agent*> listeAgents;//contient un pointeur vers tous les agents créés

public:
	typedef enum { running, destroy } Status;//en cours d'écécution ou peut être détruit

	Status statut;


	/**Constructeur
	 * @param ptrEnvInit : pointeur sur une instance de la classe Environnement
	 * @param posInit : sa position initiale
	 * @param radiusInit : son rayon initial
	 */
	Agent(Environment * ptrEnvInit, const Vector2<float> & posInit, float radiusInit = Environment::LocalizedEntity::defaultRadius(), Status initStatut = running);

	/**Destructeur
	 *
	 */
	~Agent();


	/**implémente le comportement de l'agent
	 * appelée à intervalles de temps réguliers afin de permettre
	 * à l’agent de réaliser des actions telles qu’un déplacement,
	 * ramasser de la nourriture etc...
	 *
	 *Propriété de cette classe ?
	 *abstraite
	 */
	virtual void update()=0;

	/**
	 * @return statut de l'agent
	 */
	Status getStatus();

	/**
	 * @pre Status de l'agent changé en "statut"
	 */
	void setStatus(Status statut);


	/**Parcourt tous les agents
	 * Si son statut est running, update() appelée
	 * si destroy, agent à détruire par delete sur son pointeur et sortie de l'ensemble des agents actifs
	 *
	 */
	static void simulate();

	/**Détruit tous les agents actifs de la simulation
	 *
	 */
	static void finalize();
};

#endif
