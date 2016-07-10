# MIST: MySQL Index Suggestion Tool

Trabalho de Conclusão do curso de Graduação em Ciência da Computação pela Universidade de Santa Cruz do Sul.

* **[TRABALHO](docs/TCC_II.pdf)**
* **[SLIDES](https://docs.zoho.com/show/publish/enphvc99b57e91e89494488de7772078d821b)**

## Compilação

O MIST é desenvolvido com Qt 5.3+ e utiliza o **qmake** para o processo de compilação. Para compilar o MIST a partir do código-fonte, os comandos são:

    $ mkdir build
    $ cd build
    $ qmake ../mist.pro
    $ make

O MIST pode ser executado diretamente do diretório de compilação com `./mist`. Opcionalmente, o MIST também pode ser instalado no sistema (por padrão em `/usr/local/bin/mist`):

    $ sudo make install

Para alterar o diretório de instalação, pode ser especificado um prefixo diferente para o comando `qmake`:

    $ qmake ../mist.pro PREFIX=/usr      # Será instalado em /usr/bin/mist

## License

Copyright (C) 2015-2016 Eduardo Weiland<br/>
Copyright (C) 2015-2016 Universidade de Santa Cruz do Sul

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation version 3., or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

A copy of the GNU General Public License is available in the [LICENSE](LICENSE) file.
