<h1 align="center">Processos em Memória</h1>

<p align="center">Simulador rudimentar que demonstra como é feita a permutação de dados entre memória e disco durante o processamento de dados </p>

- Compilador
                
       gcc version 9.3.0
- OS
       
       Ubuntu 20.04.2 LTS

- Executar
 
        terminal:
        ./memoria-simulador-teste/
        ./make clean
        ./make
        ./make run
  
- Entrada de dados dos arquivos devem seguir este padrão
        
        A1, 04, 01, 08, 03, 02, 05, 07, 06
  
- Entrada de dados dos processos devem seguir este padrão
            
        P1, <A1,04>, <A3,05>, <A1,04>, <A4,08>, <A1,07>, <A5,07>

  No Menu principal existe a opção de Carregar Disco e Executar Processos. A operação de Carregar Disco deve ser realizada primeiro. Essa operação faz a leitura do arquivo "arquivos_exemplos.txt", na pasta dataset, que sofre o processo de tokenização, onde a instrução <A3, 04> é subdividida em duas partes: A1 e 04. A primeira parte da instrução corresponde ao arquivo que será buscado durante o processamento, enquanto que A4 corresponde ao pedaço do arquivo que será lido do arquivo A1. Essas partes são salvas na matriz de disco onde vão permanecer até serem solicitadas pelos processos. 
