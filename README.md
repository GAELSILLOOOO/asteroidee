# asteroidee

Este proyecto es un juego desarrollado con la biblioteca SFML (Simple and Fast Multimedia Library) en C++. El juego presenta una nave que debe esquivar meteoritos que caen del cielo. La nave puede moverse hacia arriba, abajo, izquierda y derecha para evitar los meteoritos. Si un meteorito golpea la nave, el juego termina.

Requisitos del Proyecto
SFML: Esta biblioteca se usa para manejar gráficos, audio y eventos. Asegúrate de tenerla correctamente instalada en tu entorno de desarrollo.

Archivos de recursos:

Imágenes: Se deben colocar en la carpeta assets/images/:
menu.jpg: Fondo del menú principal.
Designer_30_.jpg: Fondo de la pantalla de inicio del juego.
nave.png: Imagen de la nave espacial.
a.png: Imagen del meteorito.
Fuentes: Deben estar en la carpeta assets/fonts/:
space.ttf: Fuente para los textos en el juego.
Música: Los archivos de música deben colocarse en la carpeta assets/music/:
intro.ogg: Música de introducción.
musica.ogg: Música durante el juego.
click.ogg: Sonido del clic para comenzar el juego.
gameover.ogg: Sonido de fin de juego.
Estructura del Proyecto
Archivos y Clases Importadas
SFML/Graphics.hpp: Maneja los gráficos, como la ventana, las imágenes y los objetos visuales.
SFML/Audio.hpp: Maneja el sonido, como música de fondo y efectos de sonido.
Personaje.hpp: Clase que representa a la nave espacial.
Fondo.hpp: Clase para gestionar los fondos que se desplazan.
Meteoro.hpp: Clase para los meteoritos que caen del cielo.
Musica.hpp: Clase que gestiona la reproducción de música y sonidos.
Texto.hpp: Clase que gestiona los textos que aparecen en pantalla.
iostream, cstdlib, ctime: Bibliotecas estándar de C++ para operaciones de entrada/salida, generación de números aleatorios y manejo de tiempo.
Flujo Principal del Juego
Inicialización:

Se define el tamaño de la ventana de juego (1920x1080).
Se configura el límite de fotogramas por segundo a 60 para que el juego corra a una velocidad constante.
Se cargan las fuentes y las imágenes necesarias para los elementos visuales del juego.
Se inicializan los objetos como la nave, los meteoritos y los fondos.
Eventos del Juego:

Cierre de ventana: El juego se cierra cuando el usuario cierra la ventana.
Interacciones en el menú principal: El jugador puede hacer clic en el botón "JUGAR" para iniciar el juego.
Interacciones durante el juego: La nave puede moverse con las teclas de flecha. Si un meteorito golpea la nave, el juego termina y muestra la pantalla de "GAME OVER".
Lógica del Juego:

Movimiento de fondo: El fondo se mueve constantemente para simular el desplazamiento de la nave.
Movimiento de la nave: La nave se mueve en respuesta a las teclas de flecha, pero no puede salir de los límites de la pantalla.
Meteoritos: Los meteoritos caen desde la parte superior de la pantalla y se generan aleatoriamente. Si un meteorito alcanza el fondo de la pantalla o colisiona con la nave, se cuenta como un meteorito esquivado y la nave se reinicia.
Detección de colisiones: Se verifica si la nave colide con un meteorito. Si ocurre, el juego termina y se muestra el puntaje.
Pantallas del Juego:

Pantalla de Menú Principal: Muestra un fondo con un texto que invita a jugar.
Pantalla de Juego: Muestra la nave, los meteoritos y el fondo en movimiento. También se muestra el contador de meteoritos esquivados.
Pantalla de Game Over: Muestra un mensaje de "GAME OVER", el puntaje final (número de meteoritos esquivados) y una opción para volver al menú principal.
Clases del Proyecto
Clase Personaje
Representa a la nave espacial. Tiene métodos para mover la nave y dibujarla en pantalla.

Métodos principales:
mover(float dx, float dy): Mueve la nave en el espacio 2D.
getPosition(): Devuelve la posición actual de la nave.
getBounds(): Devuelve los límites de la nave para la detección de colisiones.
resetPosition(float x, float y): Reinicia la posición de la nave.
Clase Fondo
Gestiona el fondo que se mueve durante el juego. El fondo se mueve para simular el movimiento de la nave.

Métodos principales:
mover(float speed, float deltaTime): Mueve el fondo a una velocidad determinada.
dibujar(sf::RenderWindow& window): Dibuja el fondo en la ventana de SFML.
Clase Meteoro
Representa los meteoritos que caen. Cada meteorito tiene una velocidad y una posición aleatoria en la pantalla.

Métodos principales:
mover(float dx, float dy): Mueve el meteorito.
getPosition(): Devuelve la posición del meteorito.
getBounds(): Devuelve los límites del meteorito para la detección de colisiones.
resetPosition(float x, float y): Reinicia la posición del meteorito.
Clase Musica
Gestiona la música y los efectos de sonido en el juego.

Métodos principales:
cargarMusica(const std::string& intro, const std::string& gameMusic, const std::string& click, const std::string& gameOver): Carga los archivos de música y sonidos.
reproducirIntro(): Reproduce la música de introducción.
reproducirJuego(): Reproduce la música durante el juego.
detenerJuego(): Detiene la música del juego.
reproducirGameOver(): Reproduce el sonido de fin de juego.
reproducirClick(): Reproduce el sonido de clic.
Clase Texto
Gestiona los textos que aparecen en la pantalla. Permite mostrar mensajes como "JUGAR", "GAME OVER" y los contadores de meteoritos esquivados.

Métodos principales:
setContenido(const std::string& contenido): Establece el texto que se mostrará.
dibujar(sf::RenderWindow& window): Dibuja el texto en la ventana de SFML.
Lógica de la Colisión
La colisión se detecta usando el método getBounds() de las clases Personaje y Meteoro. Si los límites de la nave y un meteorito se superponen, se considera que ha ocurrido una colisión y se termina el juego.
Detalles Adicionales
Control de FPS: Se utiliza sf::Clock y sf::Time para controlar el tiempo entre fotogramas y mantener la jugabilidad fluida.
Puntaje: El puntaje se calcula según el número de meteoritos esquivados, y se muestra en tiempo real en la parte superior izquierda de la pantalla.
Reinicio del juego: Después de que el juego termina, el jugador puede hacer clic en la pantalla para reiniciar el juego desde el menú principal.