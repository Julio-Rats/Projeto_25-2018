# Projeto IFMG Edital 25/2018                             

## Simulação e Otimização do barramento CAN

Este projeto consistente no desenvolvimento de uma ferramenta para
otimização e/ou  Simulação de rede automotiva CAN.

Foi dividido em duas partes, um otimizador e um simulador
onde ambos se comunicam por variáveis globais.


Arquitetura dos diretórios

./
  |
  |--bin: diretório com o código compilado, destino de makefile para
  |        gerar o executável
  |
  |--files: diretório onde localiza o makefile, CANdbs e
  |         pastas para resultado da ferramenta.
  |
  |--src: diretório com o código fonte do otimizador, simulador e a interface (CLI)
