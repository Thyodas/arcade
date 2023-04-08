<!-- PROJECT LOGO -->
<br />
<div align="center">

  <h1 align="center">Arcade</h1>
  <h3 align="center">A Retro Platform</h3>

  <img src="https://static.vecteezy.com/system/resources/thumbnails/002/185/779/small/arcade-neon-signs-style-text-free-vector.jpg" alt="Logo" width="250" height="250">
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Exemple</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[Subject PDF](https://intra.epitech.eu/module/2022/B-OOP-400/STG-4-1/acti-591517/project/file/B-OOP-400_arcade.pdf)

<p align="left">Arcade is a gaming platform: a program that lets the user choose a game to play and keeps a register of player scores.</p>
<p align="left">To be able to deal with the elements of your gaming platform at run-time, your graphics libraries and your games must be implemented as dynamic libraries, loaded at runtime.</p>


### Built With

This project use:


* CPP &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C%2B%2B_Logo.svg/1822px-ISO_C%2B%2B_Logo.svg.png" width="35" height="35" />](https://fr.wikipedia.org/wiki/C%2B%2B)
* SFML&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/a/a0/SFML_Logo.svg/1200px-SFML_Logo.svg.png" width="35" height="35" />](https://www.sfml-dev.org/index-fr.php)
* Ncurse&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[<img src="https://avatars.githubusercontent.com/u/15212165?v=4&s=160" width="35" height="35" />](https://fr.wikipedia.org/wiki/Ncurses)
* SDL2&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; [<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/16/Simple_DirectMedia_Layer%2C_Logo.svg/800px-Simple_DirectMedia_Layer%2C_Logo.svg.png" width="65" height="30" />](https://discourse.libsdl.org/)



<!-- GETTING STARTED -->
## Getting Started

### Installation

_How to run the arcade project and play fun video games_

1. Clone the repo
   ```sh
   git clone git@github.com:EpitechPromo2026/B-OOP-400-STG-4-1-arcade-marie.giacomel.git
   ```
2. Compile files
   ```sh
   mkdir build; cd build/; cmake .; make -j; cd ..
   ```
3. Run the program
   ```sh
   ./arcade ./[graphicLib-name].so
   ```

<!-- ADDING A LIB -->
## Adding a graphic library
If you wish to add a graphic library, your library must implement the IDisplayModule interface, otherwise it wont work.
Also, your library should implement an entry point named *entryPointDisplay*.
This function should return a new instance of your graphical library.
If everything is correctly setup, your new graphical library should be present in the menu when starting the arcade.
Please refer to the documentation for more in-depth explanation.

## Adding a game library
If you wish to add a game library, your library must implement the IGameModule interface, otherwise it wont work.
Also, your library should implement an entry point named *entryPointGame*.
This function should return a new instance of your game library.
If everything is correctly setup, your game should appear in the menu when starting the arcade.
Please refer to the documentation for more in-depth explanation.

<!-- Controls -->
## About controls
Controls are very basic, here's an exhaustive list :
- Z (upward movement)
- Q (move to the left)
- S (downward movement)
- D (move to the right)
- F (F key)
- E (E key)
- Space (Spacebar)
- Escape (Escape key)
- F1 (Previous graphic library)
- F2 (Next grahpic library)
- F3 (Previous game)
- F4 (Next game)
- F5 (Restart the game)
- F6 (Go back to menu)
- F7 (Exit the arcade)

<!-- USAGE EXAMPLES -->
## Exemple

This project is still under development

_For more information, please refer to the [Documentation](https://example.com)_



<!-- LICENSE -->
## License

This project belongs to its authors, copying it will be sanctioned by Marvin



<!-- CONTACT -->
## Contact

Guillaume Hein - [[GitHub]](https://github.com/Thyodas) - guillaume.hein@epitech.eu

Marie Giacomel - [[GitHub]](https://github.com/Sauterelle57) - marie.giacomel@epitech.eu

Mehdy morvan - [[GitHub]](https://github.com/iMeaNz) - mehdy.morvan@epitech.eu

Project Link: [https://github.com/EpitechPromo2026/B-OOP-400-STG-4-1-arcade](https://github.com/EpitechPromo2026/B-OOP-400-STG-4-1-arcade-marie.giacomel)


<!-- MARKDOWN LINKS & IMAGES -->
[Sfml]: https://upload.wikimedia.org/wikipedia/commons/thumb/b/bf/SFML2.svg/1200px-SFML2.svg.png
[Sfml-url]: https://www.sfml-dev.org/index-fr.php
[Ncurse]: https://terminalroot.com.br/assets/img/cpp/ncurses.jpg
[Ncurse-url]: https://fr.wikipedia.org/wiki/Ncurses
