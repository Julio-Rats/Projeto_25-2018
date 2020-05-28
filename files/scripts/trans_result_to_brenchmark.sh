# Transforma um resultado em um dataset para entrada (remove cabeçalho)
cat $1 | sed -e /^[^0-9]/d | sed -e /^$/d > $2
