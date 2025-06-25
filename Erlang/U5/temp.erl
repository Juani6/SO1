-module(temp).
-export([tmp/1]).
-export([cronometro/3]).

tmp (N) -> timer:sleep(N).

% Implemente un cronometro que reciba tres argumentos, Fun, Hasta y Periodo y ejecute Fun/0 cada
% Periodo milisegundos hasta que hayan pasado Hasta milisegundos

cronometro (Fun, 0, _Periodo) -> Fun();
cronometro(Fun,Hasta,Periodo) -> 
	Fun(),
	tmp(Periodo),
	cronometro(Fun,Hasta-Periodo,Periodo).

