#pragma once

#include "Shader.h"
#include <vector>

class Sprite
{
public:
	Sprite() {}
	~Sprite();
	void inicializar(GLuint texID,glm::vec3 pos = glm::vec3(0.0,0.0,0.0), glm::vec3 escala = glm::vec3(1.0,1.0,1.0),float angulo = 0.0);
	void inicializarComAnimacao(std::vector<GLuint> animacaoTexIDs, glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0), glm::vec3 escala = glm::vec3(1.0, 1.0, 1.0), float angulo = 0.0);
	void desenhar();
	void moveRight(int addVel);
	float getY();
	float getX();
	void moveLeft(int addVel);
	void moveBackgorundLeft();
	void moveBackgorundRight();
	void animar();
	void removeBomba();
	void cair();
	bool chegouNoChao();
	bool CheckCollision(Sprite& one, Sprite& two);

	void voar();
	

	inline void setShader(Shader* shader) { this->shader = shader; }
protected:
	
	void atualizar();
	GLuint VAO; //identificador do buffer de geometria, indicando os atributos dos vértices
	GLuint texID; //identificador do buffer de textura



	//Variáveis com as infos para aplicar as transformações no objeto
	glm::vec3 pos, escala;
	float angulo;

	//Uma referência ao programa de shader que a sprite irá usar para seu desenho
	Shader *shader;

	std::vector<GLuint> animacaoTexIDs;
	int currentFrame;
	bool animacao; // Indica se a sprite tem animação


	

};

