/*! This enum is used to identify the input mode of the console. */
enum InputMode{
    /*! This mode is at the beginning of the game. You have options to start, load and close*/
    GAME_START,
    /*! This is a basic mode when the player has no action to take. The player can save, close, saveas, help exit and move*/
    EMPTY_MOVE,
    /*! In this mode the player has found a treasure and has to decide what to do with it*/
    TREASURE,
    /*! In this mode the player is fighting a monster*/
    FIGHT,
    /*! Game over mode. The player has options to start from the last save, start new game and exit*/
    GAME_OVER,
    /*! In this mode the player has passed a level. The player is given points to add to their abilities*/
    LEVEL_COMPLETED
};