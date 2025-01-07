### Space Defense Game

This is a simple space defense game developed in C for the terminal. The player controls a turret to defend against enemy ships using rockets.

### Features:

- **Tower Movement:** Use the 'a' and 'd' keys to move the turret left and right, respectively.
- **Rocket Direction Movement:** Use the 'left' and 'right' keys to adjust the rocket direction before firing.
- **Rocket Firing:** Press the spacebar to fire rockets in the current direction of the turret.
- **Tower Reload:** Press 'r' to reload the available rockets.
- **Game Interface:** Dynamically updates to show the number of rockets, destroyed ships, and hit ships.

### Thread Usage:

During gameplay, the following threads are created to ensure a smooth experience:

- **thread_ships:** Controls the movement of enemy ships
- **thread_interface:** Updates the game interface
- **thread_input:** Captures player input
- **thread_collision:** Checks for collisions
- **rocket_thread:** Controls rocket movement

#### Compilation:
   ```bash
   make
   ```
   ```bash
   ./game
   ```
