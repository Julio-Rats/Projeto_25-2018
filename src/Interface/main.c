#include "main.h"

int main(int argc, char *argv[])
{
    /* Inicializa gerador de numeros aleatorios com semente dada pelo timestamp do sistema */
    srand(time(NULL));

    if (argc == 1)
  	{
		help_prog(argv[0]);
		exit(0);
  	}
  	RESULTS=FALSE;
  	decod_menu(argc, argv);

  	if (SA_ONLY_SIM)
  	{
        if (SA_GRAVA_LOGSIM)
        {
            Arq_Log_Best = fopen(SaArqLogSim, "w+");
            logframes = true;
        }
        if (SA_GRAVA_OBJ)
        {
			printf("\n================================================================================");
			printf("\n  [Alerta] Parâmetro -g (F.Objetivo) utilizado somente na otimização");
			printf("\n================================================================================\n\n");
        }

        #if SA_TIMER
			/* Contabiliza tempo de execucao */
			TmrAlocaTemporizador(SA_TIMER_SIMULATED, TRUE, "Principal SA");
			TmrStart(SA_TIMER_SIMULATED);
      	#endif

  		main_simulated(SaSimFile, TIME_CAN_SIMULATED);

        #if SA_TIMER
			/* Contabiliza tempo de execucao */
			TmrStop(SA_TIMER_SIMULATED);
			printf("\n [INFO] Runtime Simulation Only (s): %f\n\n", TmrObtemTemporizador(SA_TIMER_SIMULATED));
      	#endif

		if (SA_GRAVA_WCRT)
			print_wcrt(SaWCRTFile);
		exit(0); //Ending Only Simulation (-s)
  	}

    if (SA_HAVE_CONF)
    	/* Carrega o conteudo do arquivo de configuracao informado */
  	    SaAbreArquivoConfiguracao(SaArqConfiguracao);

  	get_candb(SaCANDBFile);

  	if (SA_GRAVA_OBJ)
  	{
		Arq_OBJ = fopen(SaArqLogEvolOBJ, "w");
		if (!Arq_OBJ)
        {
			printf("\n================================================================================");
			printf("\n [ERRO] arquivo '%s' não pode ser criado em main()", SaArqLogEvolOBJ);
			printf("\n================================================================================\n\n");
			exit(SA_ERRO_IO);
  		}
        fprintf(Arq_OBJ, "Iteração\tF.Objetivo\tWCRT\tSoma-Offsets\n");
  	}

  	/* Exibe os parametros do método */
  	printf("\n [INFO] Simulated Annealing Parameters:\n\n");
  	printf("# of Neighbors      : %u\n",  SaNumIteracao);
  	printf("# of reheating      : %d\n",  SaNumReaquecimento);
  	printf("# of Perturbations  : %ld\n", SaNumSlotsPerturbacao);
  	printf("Initial Temperature : %lf\n", SaTempInicial);
  	printf("Final Temperature   : %lf\n", SaTempFinal);
  	printf("Cooling Factor      : %lf\n", SaAlpha);
  	printf("\n\n");

    main_simulated_annealing(argc, argv);

    return 0;
}

/*****************************************************************************************/
/*                                                                                       */
/* Funcao para decodificação dos argumentos do menu                                       */
/*                                                                                       */
/*****************************************************************************************/
void decod_menu(u_int8_t argc, char *argv[])
{
	char opt;
    bool dbc = FALSE;
	while((opt = getopt(argc, argv, ":p:c:d:g:hr:s:t:l:vw:")) != -1)
    {
        switch(opt)
        {
            case 'p': // LOG_SIM
                strcpy(SaArqLogSim, optarg);
				SA_GRAVA_LOGSIM = TRUE;
            break;
            case 'c': // CONFIG
                SA_HAVE_CONF = TRUE;
                strcpy(SaArqConfiguracao, optarg);
                break;
				case 'd': // CANDB
                dbc = TRUE;
				strcpy(SaCANDBFile, optarg);
			break;
			case 'g': // Log FRAMES
	            strcpy(SaArqLogEvolOBJ, optarg);
				SA_GRAVA_OBJ = TRUE;
	        break;
            case 'h':
                help_prog(argv[0]);
                exit(0);
            break;
			case 'r': // Result
				SA_RESULT = FALSE;
				strcpy(SaArqSaida, optarg);
			break;
			case 'v': // verbose prob
                if (!SA_VERBOSE)
                	SA_VERBOSE = TRUE;
                else
                	SA_VERBOSE_FULL = TRUE;
	        break;
			case 't': // Time
				TIME_CAN_SIMULATED = atof(optarg);
	        break;
			case 's': // Simulation
				strcpy(SaSimFile, optarg);
				RESULTS 		= TRUE;
				SA_ONLY_SIM = TRUE;
			break;
			case 'l': // Limit delay
				LIMIT_DELAY 		= atof(optarg);
	            SET_LIMIT_DELAY = TRUE;
	        break;
			case 'w': // print wcrt cada ID
				strcpy(SaWCRTFile, optarg);
	            SA_GRAVA_WCRT  = TRUE;
	        break;
            case ':':
                printf("Argumento necessita de um valor: %c\n", optopt);
				exit(1);
            break; // kkk melhor break
            case '?':
                printf("Argumento invalido: %c\n", optopt);
				exit(1);
            break; // :( vai lê o manual usuario do carai.
        }
    }
    if (!(SA_ONLY_SIM || dbc))
    {
		printf("\n===============================================================================================================================================");
		printf("\n [ERRO] Arquivo dbc tabular não informado, forneça utilizando -d <CANdb tabular> (Otimização) ou -s <CANdb tabular> (apenas Simulação)\n");
		printf("===============================================================================================================================================\n\n");
		exit(1);
    }
    if (SA_ONLY_SIM && dbc)
    {
		printf("\n================================================================================");
		printf("\n [ERRO] Conflitos entre os parâmetros -s e -d, use somente um entre eles\n");
		printf("================================================================================\n\n");
		exit(1);
    }
}

/*****************************************************************************************/
/*                                                                                       */
/* Help do programa (-h, ou sem nenhum argumento)                                        */
/*                                                                                       */
/*****************************************************************************************/
void help_prog(char prog_name[])
{
    printf("\n\tOtimizador e Simulador de rede CANbus\n");
    printf("\nUso: %s [Opções] <Tipo de Execução>\n\n", prog_name);
    printf("Opções:\n\n\t\t-c <Arquivo>\t(Arquivo com parâmetros do otimizador)\n");
    printf("\t\t-g <Arquivo>\t(Log do Otimizador)\n");
    printf("\t\t-l <valor(ms)>\t(Limite inferior para o start delay (offset), default: 0 ms)\n");
    printf("\t\t-p <Arquivo>\t(Log da simulação)\n");
    printf("\t\t-r <Arquivo>\t(Arquivo final onde será armazenado os resultados da otimização)\n");
    printf("\t\t-t <valor(ms)>\t(Valor do tempo da simulação, default: 120000 ms)\n" );
    printf("\t\t-w <Arquivo>\t(Salva em arquivo o caso de pior tempo de cada mensagem (ID))\n");
    printf("\t\t-v\t\t(Habilita modo verbose)\n\n");
	printf("Tipo de Execução:\n\n");
	printf("\t\t-s <CANdb tabular>\t(Arquivo com dataset para modo de somente simulação)\n");
	printf("\t\t-d <CANdb tabular>\t(Arquivo com dataset tabular para otimização)\n");
    printf("\n\n");
}
