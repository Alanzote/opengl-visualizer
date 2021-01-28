-> Visualizador OpenGL
--> Trabalho de Construção Software Gráfico 3D
--> Aluno: Alan Renato Bunese, Turma U

Para Abrir uma Cena, basta abrir a aplicação com o Arquivo. (Drag and Drop)

Controles:
W, A, S, D - Rotacionar Camera ao redor do Centro da Cena. (0, 0, 0)
Barra de Espaço - Pausar/Continuar Animação.
Q, E - Zoom +/-.
R - Recarregar última Cena.
L - Ativar/Desativar Iluminação.
O - Ativar/Desativar Modo de Objeto.

Controles Adicionais no Modo de Objeto:
Setas do Teclado - Movar Grupo de Objetos Selectionados.
CTRL Direito - Circular entre Objetos Disponíveis.
Page Down - Entrar 1 Nível na Hierarquia de Objetos.
Page Up - Sair 1 Nível na Hierarquia de Objetos.
END - Ativar/Desativar Visualização do Grupo de Objetos Selecionados.

Fazendo Build do Projeto:
Foi utilizado o IDE Visual Studio. O projeto se encontra em: OpenGLApp\OpenGLApp.sln.

Por causa da biblioteca exprtk, que realiza o parse dos parâmetros matemáticos de um Display File,
é necessária a opção /bigobj na compilação. O Projeto incluso já possue todos os caminhos de inclusão (Relativo)
e parâmetros de compilação corretos e pronto para serem rodados.

Foi incluso uma build x64 debug em OpenGLApp\x64\Debug\OpenGLApp.exe, não sendo necessário fazer uma build do Visual Studio.

Rodar o projeto diretamente pelo IDE irá abrir a cena de exemplo "PIXAR", que está inclusa na pasta OpenGLApp\DisplayFiles\DisplayFile.sdf.
É também recomendado rodar o programa com o DisplayFile_Animation.sdf, para verificar as capacidades de animação da aplicação.

Criando Um Display File:
Para definir um objeto, basta utilizar a syntaxe:

objeto(param, param, param...) { }

Objetos disponíveis:
cube(solid/wireframe, Size)
cone(solid/wireframe, Base, Height, Slices, Stacks)
sphere(solid/wireframe, Radius, Slices, Stacks)
cylinder(solid/wireframe, Radius, Height, Slices, Stacks)
teapot(solid/wireframe, Size)
customcube(Size) -> Função Cubo com Cálculo Manual de Normais.
torus(solid/wireframe, Inner Radius, Outer Radius, Slices, Stacks)
tetrahedron(solid/wireframe)
dodecahedron(solid/wireframe)
octahedron(solid/wireframe)
icosahedron(solid/wireframe)

Para objetos que não são identificados, é criado um objeto Pai vazio,
este objeto é ótimo para criar estruturas hierarquias sem necessariamente
desenhar um objeto novo.

Dentro das chaves para definir um objeto, podemos colocar vários comandos,
assim como mais objetos filho. Para comandos, temos esta syntaxe:

comando(param, param, param...)

Comandos Disponíveis:
translate(X, Y, Z)
rotate(X, Y, Z)
scale(X, Y, Z)
color(R, G, B)

Então, é possível realizar o seguinte:
(Comentários não aceitos no arquivo de Display, são apenas demonstração para
este tutorial)

cube(solid, 1) { // Cria um Cubo Sólido com Tamanho 1.
	translate(10, 3, 5) // Modifica a posição do Cubo em 10 unidades X, 4 unidades Y e 5 unidades Z.
	rotate(30, 30, 30) // Rotaciona o Cubo 30 graus em cada eixo.
	scale(10, 1, 1) // Modifica o tamanho do Cubo.
	color(1, 0, 0) // Modifica a cor do Cubo como Vermelho. (A cor vai para os filhos)
	// Estes comandos não são necessários e caso não inclusos, tem valores padrão.

	cube(solid, 2) { // Cria um Cubo Filho que vai ser o dobro do tamanho do pai.
		// Posição RELATIVA: 0, 0, 0.
		// Rotação RELATIVA: 30, 30, 30.
		// Escala RELATIVA: 1, 1, 1.
		// Cor: 1, 0, 0.
		// Continuar relação de Pai/Filho...
	}

	// Mais Objetos...
}

Em qualquer parâmetro que tem seu valor como sendo um número, foi utilizado a biblioteca exprtk.
Esta biblioteca realiza um parse da expressão matemática direto em string e retorna um valor.
Ou seja, um Display File é válido também:

cube(solid, 1) { // Cria um Cubo Sólido com Tamanho 1.
	rotate(0, Frame/Frames * 360, 0) // Cubo Rotaciona 360 graus no eixo Y pelo tempo de toda animação.
}

Variáveis Disponíveis:
DeltaTime // Tempo entre Frames.
Frame // Número da Frame Atual.
Frames // Quantidade de Frames na Animação.
TargetFPS // Constante da quantidade de Frames por Segundo.

Também existe o objeto scene(). Este objeto tem informações específicas em relação a animação.

scene() {
	frames(X)
}

Entretanto, só existe um comando, que seria o "frames". Este indica a quantidade de FRAMES TOTAIS que a
animação tem. Lembrando que o aplicativo roda a 60 FRAMES POR SEGUNDO. Padrão são 600 frames, ou seja,
10 segundos de animação.

Caso a constante TARGET_FPS (linha 17) seja alterada, o programa funcionará normalmente executando na
quantidade desejada. Animações terão a constante TargetFPS alterada de acordo.