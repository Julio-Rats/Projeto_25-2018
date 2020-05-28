# Deixa em ordem os IDs com seus WCRTs e chama script para criar grafico (multi graficos).
sh sort_ids.sh $1
Rscript plotbar_wcrt.r $1
