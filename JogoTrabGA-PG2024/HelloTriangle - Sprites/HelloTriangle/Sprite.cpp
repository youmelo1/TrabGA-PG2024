#include "Sprite.h"
#include <random>

Sprite::~Sprite()
{
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);

	
}

void Sprite::inicializar(GLuint texID, glm::vec3 pos, glm::vec3 escala, float angulo)
{
	this->texID = texID;
	this->pos = pos;
	this->escala = escala;
	this->angulo = angulo;
	this->animacao = false;



	// Aqui setamos as coordenadas x, y e z do tri�ngulo e as armazenamos de forma
	// sequencial, j� visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do v�rtice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO �nico ou em VBOs separados
	GLfloat vertices[] = {
		//x     y    z    r    g    b    s    t
		//Triangulo 0
		-0.5 , 0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0,  //v0
		-0.5 ,-0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,  //v1
		 0.5 , 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,  //v2
		 //Triangulo 1	
	    -0.5 ,-0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,  //v1
		 0.5 ,-0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,  //v3
		 0.5 , 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0   //v2
		
	};

	GLuint VBO;
	//Gera��o do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conex�o (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//                                              vertices.data()  
	//Gera��o do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de v�rtices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localiza��o no shader * (a localiza��o dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se est� normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 

	//Atributo 0 - posi��o
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo 1 - cor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Atributo 2 - coordenadas de textura
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// Observe que isso � permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de v�rtice 
	// atualmente vinculado - para que depois possamos desvincular com seguran�a
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (� uma boa pr�tica desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

}

void Sprite::inicializarComAnimacao(std::vector<GLuint> animacaoTexIDs, glm::vec3 pos, glm::vec3 escala, float angulo)
{
	this->animacaoTexIDs = animacaoTexIDs;
	this->pos = pos;
	this->escala = escala;
	this->angulo = angulo;
	this->currentFrame = 0;
	this->animacao = true;



	GLfloat vertices[] = {
		//x     y    z    r    g    b    s    t
		//Triangulo 0
		-0.5 , 0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0,  //v0
		-0.5 ,-0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,  //v1
		 0.5 , 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,  //v2
		 //Triangulo 1	
		-0.5 ,-0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,  //v1
		 0.5 ,-0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,  //v3
		 0.5 , 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0   //v2

	};

	GLuint VBO;
	//Gera��o do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conex�o (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//                                              vertices.data()  
	//Gera��o do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de v�rtices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localiza��o no shader * (a localiza��o dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se est� normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 

	//Atributo 0 - posi��o
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo 1 - cor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Atributo 2 - coordenadas de textura
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// Observe que isso � permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de v�rtice 
	// atualmente vinculado - para que depois possamos desvincular com seguran�a
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (� uma boa pr�tica desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);
}

std::random_device rd;
std::uniform_int_distribution<int> dist(10, 790);

void Sprite::desenhar()
{
	atualizar();

	if (animacao)
	{
		glBindTexture(GL_TEXTURE_2D, animacaoTexIDs[currentFrame]);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, texID);
	}

	glBindVertexArray(VAO); // Conectando ao buffer de geometria
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind
	glBindVertexArray(0); // Unbind
}

void Sprite::moveRight(int addVel)
{

	pos.x += 7.0 + addVel;
	escala.x = abs(escala.x); // Garante que a escala no eixo x seja positiva


	if (animacao) {
		currentFrame = (currentFrame + 1) % animacaoTexIDs.size();// Avan�a para o pr�ximo frame da anima��o
	}
	
	
}

void Sprite::moveLeft(int addVel)
{
	

	pos.x -= 7.0 + addVel;
	escala.x = -abs(escala.x); // Inverte a escala no eixo x para espelhar o sprite

	if (animacao) {
		currentFrame = (currentFrame + 1) % animacaoTexIDs.size();// Avan�a para o pr�ximo frame da anima��o

	}

	
}

void Sprite::moveBackgorundLeft()
{
	pos.x -= 0.7;
}

void Sprite::moveBackgorundRight()
{
	pos.x += 0.7;
}


void Sprite::animar()
{

	if (animacao) {
		currentFrame = (currentFrame + 1) % animacaoTexIDs.size();
		Sleep(10);
	}
}


float Sprite::getY()
{
	return pos.y;
}

float Sprite::getX()
{
	return pos.x;
}


void Sprite::removeBomba()
{
	pos.x = dist(rd);
	pos.y = 1000.0;
}

void Sprite::cair()
{
	if (pos.y >= 55.0)
	{
		pos.y -= 1.5;
	}
	else
	{
		pos.x = dist(rd);
		pos.y = 1000.0;
	}
}

bool Sprite::chegouNoChao()
{
	return pos.y < 55;
}

bool Sprite::CheckCollision(Sprite& one, Sprite& two)
{
	// Define a margem de erro
	float errorMargin = 20;


	// Calcula as bordas considerando a escala positiva ou negativa
	float one_xmax = one.pos.x + abs(one.escala.x) / 2 - errorMargin;
	float one_ymax = one.pos.y + one.escala.y / 2 - errorMargin;
	float one_xmin = one.pos.x - abs(one.escala.x) / 2 + errorMargin;
	float one_ymin = one.pos.y - one.escala.y / 2 + errorMargin;

	float two_xmax = two.pos.x + two.escala.x / 2 - errorMargin;
	float two_ymax = two.pos.y + two.escala.y / 2 - errorMargin;
	float two_xmin = two.pos.x - two.escala.x / 2 + errorMargin;
	float two_ymin = two.pos.y - two.escala.y / 2 + errorMargin;

	// Verifica a colis�o no eixo x
	bool collisionX = one_xmax >= two_xmin && two_xmax >= one_xmin;
	// Verifica a colis�o no eixo y
	bool collisionY = one_ymax >= two_ymin && two_ymax >= one_ymin;

	// A colis�o ocorre apenas se houver colis�o em ambos os eixos
	return collisionX && collisionY;


}

void Sprite::voar()
{
	// Verifica se o p�ssaro est� dentro dos limites da tela
	if (pos.x >= 50.0 && pos.x<=900)
	{
		pos.x += 1.5;
		if (animacao) {
			currentFrame = (currentFrame + 1) % animacaoTexIDs.size(); // Avan�a para o pr�ximo frame da anima��o
		}
	}
	else
	{
		pos.y = 200 + rand() % 600;
		pos.x = 50;
	}

}


void Sprite::atualizar()
{
	glm::mat4 model = glm::mat4(1); //matriz identidade
	model = glm::translate(model, pos);
	model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0, 0.0, 1.0));
	model = glm::scale(model, escala);
	shader->setMat4("model", glm::value_ptr(model));

}
