##########################################################################
#                                                                        #
# run-exp.sh                                                             #
#                                                                        #
# Executa o experimento do simulated annealing com o Simulador com 	 #
# 		quantidade de repeticoes especificadas. 		 #
#                                                                        #
##########################################################################

#Verifica argumentos
if [ $# -lt 2 ]; then
	 echo "\nSintaxe de uso do script:\n\n\tsh $0 [Input] [Results] [Nº Replicações]\n"
	 echo "\nArgumentos:\n"
	 echo "[Input]: Arquivo CANdb para simulação ou otimização."
	 echo "[Results]: Diretorio e arquivo base para geração dos resultados"
	 echo "[Nº Replicações]: Número de execuções\n"
	 exit
fi

# Quantidade de repeticoes desejada
Results=$2
NUM_REPETICOES=$3

#Alguns arquivos e diretorio necessarios
ARQ_CONFIG="config_parametros.txt"
Otimizador="../bin/otimizador"

# Executa a aplicacao a quantidade de repeticoes especificada
CONTADOR=1
until [ $CONTADOR -gt $NUM_REPETICOES ];
do
	data=$(date +%s)
	echo "\nExecução Nº: $CONTADOR de $NUM_REPETICOES Execuções \t Time Start = $data \n"

	$Otimizador -c $ARQ_CONFIG -d $1 -r $Results-$data.txt

	CONTADOR=$(($CONTADOR+1))
done
