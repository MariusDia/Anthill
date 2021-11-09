/*
 * Agent.cpp
 *
 *  Created on: 20 févr. 2021
 *      Author: jce
 */

#include "Agent.h"
#include <Environment.h>
#include <Vector2.h>


//Constructeur
Agent::Agent(Environment * ptrEnvInit, const Vector2<float> & posInit, float radiusInit, Status initStatut)
:
Environment::LocalizedEntity(ptrEnvInit,posInit, radiusInit),
statut(initStatut)
{
	listeAgents.insert(this);
}

//Destructeur
Agent::~Agent(){
}

std::set<Agent*> Agent::listeAgents;

//Accesseur statut
Agent::Status Agent::getStatus(){
	return statut;
}

//Setter statut
void Agent::setStatus(Agent::Status newStatut){
	statut = newStatut;
}


void Agent::simulate(){
	//for (std::set<Agent*>::iterator it = Agent::listeAgents.begin(); it!=Agent::listeAgents.end(); ++it){
	std::set<Agent*>::iterator it = Agent::listeAgents.begin();
	while(it != Agent::listeAgents.end()){
		if((*it)->statut==running){//si l'agent est en cours d'execution
			(*it)->update();	//on l'actualise
			++it;				//on passe au prochain agent
		}
		else if((*it)->statut==destroy){//si l'agent est à détuire
			delete (*it);//détruit l'objet pointé par it
			it = Agent::listeAgents.erase(it);//detruit le POINTEUR et on le remplace par le suivant
		}
	}
}


void Agent::finalize(){
	std::set<Agent*>::iterator it = Agent::listeAgents.begin();
	while(it != Agent::listeAgents.end()){
		delete (*it);//détruit l'objet pointé par it
		it = Agent::listeAgents.erase(it);//detruit le POINTEUR et on le remplace par le suivant
	}
}
