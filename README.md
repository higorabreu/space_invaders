### Space Defense Game

Este é um jogo simples de defesa espacial desenvolvido em C para terminal. O jogador controla uma torre para defender contra naves inimigas usando foguetes.

Alunos: Higor Abreu e Igor Zimmer

### Funcionalidades:

- **Movimento da Torre:** Use as teclas 'a' e 'd' para mover a torre para a esquerda e direita, respectivamente.
- **Movimento da Direção do Foguete:** Use as teclas 'left' (esquerda) e 'right' (direita) para mover a direção do foguete antes de disparar.
- **Disparo de Foguetes:** Pressione a tecla de espaço para disparar foguetes na direção atual da torre.
- **Recarga da Torre:** Pressione 'r' para recarregar os foguetes disponíveis.
- **Interface de Jogo:** Atualiza dinamicamente mostrando o número de foguetes, naves destruídas e atingidas.

### Uso de Threads:

Durante a execução do jogo, as seguintes threads são criadas garantindo uma experiência de jogo fluida:

- thread_ships: Movimento das Naves
- thread_interface: Atualização da Interface
- thread_input: Captura de Entrada
- thread_collision: Verificação de Colisões
- rocket_thread: Movimento dos Foguetes

#### Compilação:
   ```bash
   make
   ```
   ```bash
   ./game
   ```
