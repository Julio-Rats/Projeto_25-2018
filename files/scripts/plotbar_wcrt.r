argv <- commandArgs(trailingOnly = TRUE)

png(paste(argv[1],"png",sep="."), width=980, height=480)

dados <- read.table(file=argv[1], header=T)

wcrt <- sum(dados$WCRT)
titulo <- paste("Pior atraso experimentado por cada mensagem da rede CAN\n WCRT = ", toString(wcrt), " ms")
a <- barplot(dados$WCRT, dados$ID, xlab="Identificadores de Prioridade (ID)", ylab="WCRT (ms)",main=titulo)

axis(1, at = a, label = dados$ID)

dev.off()
