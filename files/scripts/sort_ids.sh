# Deixa em ordem crescente os id do arquivo de saida do pior WCRT (necessario para criar graficos)
cat $1 | sort -nk1 > /tmp/temp
mv /tmp/temp $1
