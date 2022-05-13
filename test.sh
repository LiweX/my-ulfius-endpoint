(seq 50 | parallel -n0 curl -X POST http://localhost:8537/increment) &
(seq 50 | parallel -n0 curl -X GET http://localhost:8537/imprimir) & 