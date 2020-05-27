Diretório contendo subdiretórios para armazenar resultados da ferramenta.

[Arquivos locais]:
  -config_parametros.txt: arquivo para entrada de parâmetros da otimização (-c).
  -makefile: arquivo de compilação (linguagem C).
  -run-exp.sh: script para automação da ferramenta na fase de geração
              e analise dos resultados  

[Diretórios locais]:
  -CANdb: diretório de armazenagem de CANdb já em formato tabular dos
            encontrados na literatura e usado no desenvolvimento do mesmo.

  -LogObj: diretório usado para armazenar arquivos da otimização, com a evolução
             da função objetiva (parâmetro -g).

  -LogSim: diretório usado para armazenar arquivos da simulação, com o timestamp
            da simulação (parâmetro -p).

  -Resultados: resultados da otimização do CANdb (parâmetro -r).

  -scripts: diretório com os scripts utilizado no desenvolvimento do projeto.

  -wcrt_ids: diretório com os piores atrasos de cada mensagem (parâmetro -w).
