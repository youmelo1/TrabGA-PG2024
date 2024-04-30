/* Hello Triangle - código adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gráfico - Unisinos
 * Versão inicial: 7/4/2017
 * Última atualização em 14/08/2023
 *
 */

#include <iostream>
#include <string>
#include <assert.h>

 //STB IMAGE
#include<stb_image.h>


using namespace std;
//using namespace glm; //para não usar glm::

//Classe para manipulação dos shaders
#include "Shader.h"

//Classe para manipulação das sprites
#include "Sprite.h"
#include <vector>

#include <random>

// Protótipo da função de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Protótipos das funções
GLuint loadTexture(string texturePath);

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 800, HEIGHT = 600;




//Variaveis globais
Sprite spr;
Sprite moeda1;
Sprite moeda2;
Sprite moeda3;
Sprite explosao;
Sprite loot;
Sprite background;
Sprite bau;
Sprite power;
Sprite trofeu; 
Sprite caveira;

bool m1 = false;
bool m2 = false;
bool m3 = false;

bool kabum = false;
bool ganhou = false;
bool powerUp = false;
bool fimDeJogoRuim = false;
bool fimDeJogoBom = false;
bool jogo = true;

int cont = 0;
int boom = 0;
int ponto = 0;
int addVel = 0;
int temporizador = 0;



// Função MAIN
int main()
{


	// Inicialização da GLFW
	glfwInit();

	// Inicialização da semente para geração de nros aleatórios
	
	std::random_device rd;
	std::uniform_int_distribution<int> dist(10, 790);
	

	//Muita atenção aqui: alguns ambientes não aceitam essas configurações
	//Você deve adaptar para a versão do OpenGL suportada por sua placa
	//Sugestão: comente essas linhas de código para desobrir a versão e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	//Essencial para computadores da Apple
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif

	// Criação da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Jogo", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;

	}

	// Obtendo as informações de versão
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	//Habilitar teste de profundidade
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS); //a cada ciclo

	//Habilitar o modo de transparância (blend - mistura de cores)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	// Compilando e buildando o programa de shader
	//Shader shader("../shaders/helloTriangle.vs", "../shaders/helloTriangle.fs");
	Shader shader("../shaders/tex.vs", "../shaders/tex.fs");



	GLuint texID = loadTexture("../../Textures/craftpix-net-159039-free-pirate-stuff-pixel-art-icons/PNG/Transperent/Icon31.png");
	GLuint texID3 = loadTexture("../../Textures/oceanos/Ocean_4/5.png");
	GLuint texID4 = loadTexture("../../Textures/craftpix-net-159039-free-pirate-stuff-pixel-art-icons/PNG/Transperent/Icon41.png");
	GLuint texID5 = loadTexture("../../Textures/craftpix-net-159039-free-pirate-stuff-pixel-art-icons/PNG/Transperent/Icon31.png");
	GLuint bauIcon = loadTexture("../../Textures/craftpix-net-159039-free-pirate-stuff-pixel-art-icons/PNG/Transperent/Icon10.png");
	GLuint lootIcon = loadTexture("../../Textures/4 Examples/8Loot.png");
	GLuint beNice = loadTexture("../../Textures/4 Examples/6Benice.png");
	GLuint rumIcon = loadTexture("../../Textures/craftpix-net-159039-free-pirate-stuff-pixel-art-icons/PNG/Transperent/Icon48.png");

	GLuint caveiraIcon = loadTexture("../../Textures/fimDeJogo/PNG/Transperent/Icon1.png");
	GLuint trofeuIcon = loadTexture("../../Textures/fimDeJogo/PNG/4.png");

	GLuint a1 = loadTexture("../../Textures/PNG/1/1_entity_000_WALK_000.png"); 
	GLuint a2 = loadTexture("../../Textures/PNG/1/1_entity_000_WALK_001.png");
	GLuint a3 = loadTexture("../../Textures/PNG/1/1_entity_000_WALK_002.png");
	GLuint a4 = loadTexture("../../Textures/PNG/1/1_entity_000_WALK_003.png");
	GLuint a5 = loadTexture("../../Textures/PNG/1/1_entity_000_WALK_004.png");
	GLuint a6 = loadTexture("../../Textures/PNG/1/1_entity_000_WALK_005.png");
	GLuint a7 = loadTexture("../../Textures/PNG/1/1_entity_000_WALK_006.png");

	GLuint ex1 = loadTexture("../../Textures/PNG/Explosion_1/Explosion_1.png");
	GLuint ex2 = loadTexture("../../Textures/PNG/Explosion_1/Explosion_2.png");
	GLuint ex3 = loadTexture("../../Textures/PNG/Explosion_1/Explosion_3.png");
	GLuint ex4 = loadTexture("../../Textures/PNG/Explosion_1/Explosion_4.png");
	GLuint ex5 = loadTexture("../../Textures/PNG/Explosion_1/Explosion_5.png");
	GLuint ex6 = loadTexture("../../Textures/PNG/Explosion_1/Explosion_6.png");
	GLuint ex7 = loadTexture("../../Textures/PNG/Explosion_1/Explosion_7.png");
	GLuint ex8 = loadTexture("../../Textures/PNG/Explosion_1/Explosion_8.png");
	GLuint ex9 = loadTexture("../../Textures/PNG/Explosion_1/Explosion_9.png");
	GLuint ex10 = loadTexture("../../Textures/PNG/Explosion_1/Explosion_10.png");


	GLuint passaro1 = loadTexture("../../Textures/bird/p1.png");
	GLuint passaro2 = loadTexture("../../Textures/bird/p2.png");
	GLuint passaro3 = loadTexture("../../Textures/bird/p3.png");
	GLuint passaro4 = loadTexture("../../Textures/bird/p4.png");
	GLuint passaro5 = loadTexture("../../Textures/bird/p5.png");
	GLuint passaro6 = loadTexture("../../Textures/bird/p6.png");



	//Criação de uma sprite
	std::vector<GLuint> animacaoTexIDs = { a1, a2, a3, a4, a5, a6, a7 };

	std::vector<GLuint> animacaoBomba = { ex1,ex2,ex3,ex4,ex5,ex6,ex7,ex8,ex9,ex10 };

	std::vector<GLuint> animacaoPassaro = { passaro1, passaro2, passaro3, passaro4, passaro5, passaro6 };

	spr.setShader(&shader);
	spr.inicializarComAnimacao(animacaoTexIDs, glm::vec3(400.0, 90.0, 0.0), glm::vec3(120, 120, 1.0));

	

	
	background.setShader(&shader);
	background.inicializar(texID3, glm::vec3(400.0, 300.0, 0.0), glm::vec3(1920.0 / 2.0, 1080.0 / 2.0, 1.0));


	Sprite bomba;
	bomba.setShader(&shader);
	bomba.inicializar(texID4, glm::vec3(dist(rd), (900 + rand() % 70), 0.0), glm::vec3(32.0, 32.0, 1.0));

	Sprite bomba2;
	bomba2.setShader(&shader);
	bomba2.inicializar(texID4, glm::vec3(dist(rd), (900 + rand() % 70), 0.0), glm::vec3(32.0, 32.0, 1.0));

	Sprite moeda;
	moeda.setShader(&shader);
	moeda.inicializar(texID5, glm::vec3(dist(rd), (900 + rand() % 70), 0.0), glm::vec3(32.0, 32.0, 1.0));

	Sprite rum;
	rum.setShader(&shader);
	rum.inicializar(rumIcon, glm::vec3(dist(rd), (900 + rand() % 20), 0.0), glm::vec3(32.0, 32.0, 1.0));

	Sprite passaro;
	passaro.setShader(&shader);
	passaro.inicializarComAnimacao(animacaoPassaro, glm::vec3(50, 500, 0.0), glm::vec3(32.0, 32.0, 1.0));


	bau.setShader(&shader);
	bau.inicializar(bauIcon, glm::vec3(70.0, 55.0, 0.0), glm::vec3(50.0, 50.0, 1.0));


	caveira.setShader(&shader);
	caveira.inicializar(caveiraIcon, glm::vec3(380, 325, 0.0), glm::vec3(250.0, 250.0, 1.0));

	trofeu.setShader(&shader);
	trofeu.inicializar(trofeuIcon, glm::vec3(380, 325, 0.0), glm::vec3(250.0, 250.0, 1.0));
	


	//Ativando o buffer de textura 0 da opengl
	glActiveTexture(GL_TEXTURE0);

	shader.Use();

	//Matriz de projeção paralela ortográfica
	glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	//Enviando para o shader a matriz como uma var uniform
	shader.setMat4("projection", glm::value_ptr(projection));

	//Matriz de transformação do objeto (matriz de modelo)
	shader.setInt("texBuffer", 0);

	// Loop da aplicação - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
		glfwPollEvents();

		// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height); //unidades de tela: pixel

		// Limpa o buffer de cor
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);



		background.desenhar();

		
		spr.desenhar();

		bau.desenhar();

		if (jogo) {
			bomba.cair();
			bomba.desenhar();

			bomba2.cair();
			bomba2.desenhar();

			moeda.cair();
			moeda.desenhar();

			rum.cair();
			rum.desenhar();

			passaro.desenhar();
			passaro.voar();




			if (moeda.CheckCollision(spr, moeda)) {

				loot.setShader(&shader);
				loot.inicializar(lootIcon, glm::vec3(moeda.getX(), moeda.getY() + 60, 0.0), glm::vec3(80.0, 80.0, 1.0));
				ganhou = true;
				moeda.removeBomba();

				if (cont == 0) {
					moeda1.setShader(&shader);
					moeda1.inicializar(texID, glm::vec3(750.0, 40.0, 0.0), glm::vec3(32.0, 32.0, 1.0));
					m1 = true;
				}
				if (cont == 1) {
					moeda2.setShader(&shader);
					moeda2.inicializar(texID, glm::vec3(700.0, 40.0, 0.0), glm::vec3(32.0, 32.0, 1.0));
					m2 = true;
				}
				if (cont == 2) {
					moeda3.setShader(&shader);
					moeda3.inicializar(texID, glm::vec3(650.0, 40.0, 0.0), glm::vec3(32.0, 32.0, 1.0));
					m3 = true;
					fimDeJogoBom = true;
					jogo = false;
				}


				cont++;

			}

			if (rum.CheckCollision(spr, rum)) {
				addVel += 8;

				power.setShader(&shader);
				power.inicializar(beNice, glm::vec3(60, 525, 0.0), glm::vec3(60.0, 60.0, 1.0));
				powerUp = true;

				rum.removeBomba();
			}

			if (moeda.chegouNoChao() || bomba.CheckCollision(spr, bomba) || bomba2.CheckCollision(spr, bomba2)) {
				if (bomba.CheckCollision(spr, bomba)) {

					explosao.setShader(&shader);
					explosao.inicializarComAnimacao(animacaoBomba, glm::vec3(bomba.getX(), bomba.getY() - 45, 0.0), glm::vec3(200.0, 200.0, 1.0));
					kabum = true;

					bomba.removeBomba();

				}
				if (bomba2.CheckCollision(spr, bomba2)) {

					explosao.setShader(&shader);
					explosao.inicializarComAnimacao(animacaoBomba, glm::vec3(bomba2.getX(), bomba2.getY() - 45, 0.0), glm::vec3(200.0, 200.0, 1.0));
					kabum = true;

					bomba2.removeBomba();

				}

				if (cont == 1) {
					m1 = false;
				}
				if (cont == 2) {
					m2 = false;
				}
				if (cont == 3) {
					m3 = false;
				}
				if (!m1 && !m2 && !m3 && cont == 0) {
					//break;
					fimDeJogoRuim = true;
					jogo = false;

				}
				cont--;
			}

			if (kabum) {
				explosao.desenhar();
				explosao.animar();
				boom++;
			}
			if (boom >= 10) {
				kabum = false;
				boom = 0;
			}


			if (ganhou) {
				loot.desenhar();
				ponto++;
			}
			if (ponto >= 90) {
				ganhou = false;
				ponto = 0;
			}


			if (powerUp) {
				power.desenhar();
				temporizador++;
			}
			if (temporizador >= 250) {
				powerUp = false;
				temporizador = 0;
				addVel -= 8;
			}


			//printf("%d", cont);

			if (m1) {
				moeda1.desenhar();
			}
			if (m2) {
				moeda2.desenhar();
			}
			if (m3) {
				moeda3.desenhar();
			}
		}

		if (fimDeJogoRuim) {
			caveira.desenhar();
		}

		if (fimDeJogoBom) {
			trofeu.desenhar();
		}

		if (m1) {
			moeda1.desenhar();
		}
		if (m2) {
			moeda2.desenhar();
		}
		if (m3) {
			moeda3.desenhar();
		}

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}

	// Finaliza a execução da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Função de callback de teclado - só pode ter uma instância (deve ser estática se
// estiver dentro de uma classe) - É chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_D || key == GLFW_KEY_RIGHT)
	{
		if (spr.getX() < 790 && jogo) { // Verifica se o personagem pode ir para a direita
			spr.moveRight(addVel);

			background.moveBackgorundLeft();
			bau.moveBackgorundLeft();
		}
	}

	if (key == GLFW_KEY_A || key == GLFW_KEY_LEFT)
	{
		

		if (spr.getX() > 30 && jogo) { // Verifica se o personagem pode ir para a esquerda
			spr.moveLeft(addVel);

			background.moveBackgorundRight();
			bau.moveBackgorundRight();
		}
	}

}


GLuint loadTexture(string texturePath)
{
	GLuint texID;

	// Gera o identificador da textura na memória 
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//Configuração do parâmetro WRAPPING nas coords s e t
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Confirugação do parâmetro FILTERING na minificação e magnificação da textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

